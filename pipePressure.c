#include "pipePressure.h"
#include "gpio.h"
#include "i2c.h"
#include "math.h"


extern I2C_HandleTypeDef hi2c3;
uint8_t pressureData[PRESSURE_VALUE_SIZE];
uint8_t temperData[TEMPER_VALUE_SIZE];


/**
  * @brief  Initialize the pipe pressure sensor by repowering.
  * @retval None
  */
void pipePressureInit(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
}


/**
  * @brief  Get the pipe pressure[Kpa] and temperature[°C] that were sampled by sensor.
  * @param1 pressure: return the pipe pressure with unit[Kpa].
  * @param2 temper： return the temperature with unit[°C].
  * @retval TypeI2CxStatus, for detect the types of function's problem.
  */
TypeI2CxStatus pipePressureGetData(float *pressure, float *temper)
{
	TypeI2CxStatus I2CxStatus;
	uint32_t intermediate = 0;
	uint8_t data[2]; 			//data[0] for slave's MemAddress, data[1] for data that wanted to be send or to be got

	/******************** LAUNCHING I2C data gathering process ********************/
	I2CxStatus = I2CInterfaceConfirm();				//confirm the I2C interface (I2C1, I2C2 or I2C3)
	if(I2CxStatus != statusOK)	return I2CxStatus;
	//step1
	data[0] = 0XA5;
	I2CxStatus = I2CWrite(PIPEPRESSURE_ADDRESS_W, data, 1);
	if(I2CxStatus != statusOK)	return I2CxStatus;
	I2CxStatus = I2CRead(PIPEPRESSURE_ADDRESS_R, data+1, 1);
	if(I2CxStatus != statusOK)	return I2CxStatus;
	data[1] &= 0XFD;
	I2CxStatus = I2CWrite(PIPEPRESSURE_ADDRESS_W, data, 2);
	if(I2CxStatus != statusOK)	return I2CxStatus;
	//step2
	data[0] = 0X30;
	data[1] = 0X0A;
	I2CxStatus = I2CWrite(PIPEPRESSURE_ADDRESS_W, data, 2);
	if(I2CxStatus != statusOK)	return I2CxStatus;
	//step3
	HAL_Delay(10);
	//step4
	data[0] = 0X06;
	for(uint8_t i=0; i<PRESSURE_VALUE_SIZE; i++){
		I2CxStatus = I2CWrite(PIPEPRESSURE_ADDRESS_W, data, 1);
		if(I2CxStatus != statusOK)	return I2CxStatus;
		I2CxStatus = I2CRead(PIPEPRESSURE_ADDRESS_R, pressureData+i, 1);
		if(I2CxStatus != statusOK)	return I2CxStatus;
		data[0]++;
	}
	//step5
	data[0] = 0X09;
	for(uint8_t j=0; j<TEMPER_VALUE_SIZE; j++){
		I2CxStatus = I2CWrite(PIPEPRESSURE_ADDRESS_W, data, 1);
		if(I2CxStatus != statusOK)	return I2CxStatus;
		I2CxStatus = I2CRead(PIPEPRESSURE_ADDRESS_R, temperData+j, 1);
		if(I2CxStatus != statusOK)	return I2CxStatus;
		data[0]++;
	}
	/******************** ENDING I2C data gathering process ********************/

	intermediate = ((uint32_t)pressureData[0]<<16) | ((uint32_t)pressureData[1]<<8) | pressureData[2];
	if(!(pressureData[0] >> 7))
		*pressure = (intermediate / pow(2, 23)) * 1.02 * X_FOR_CALCULATION;		//unnecessary to transform the type of "intermediate" to float, because of function pow's retval is double.
	else
		*pressure = ((intermediate-pow(2, 24)) / pow(2, 23)) * 1.02 * X_FOR_CALCULATION;

	intermediate = ((uint32_t)temperData[0]<<8) | temperData[1];
	if(!(temperData[0] >> 7))
		*temper = (float)intermediate / 256;
	else
		*temper = (float)(intermediate-pow(2,16)) / 256;

	return statusOK;
}
