#include "I2CInterface.h"
#include "i2c.h"


/* USER CODE BEGIN PV */
/*!
 * change I2Cx interface here (by comment the related lines and cancel comment of related lines).
 * @Note : for instance, my project uses I2C3 for pipe-pressure sensor,
 * 		   so I comment "TypeI2Cx I2Cx = I2Cx1;" and "TypeI2Cx I2Cx = I2Cx2;".
 */
//TypeI2Cx I2Cx = I2Cx1;
//TypeI2Cx I2Cx = I2Cx2;
TypeI2Cx I2Cx = I2Cx3;

I2C_HandleTypeDef *hi2cx;
HAL_StatusTypeDef I2CStatus;
/* USER CODE END PV */


/**
  * @brief  confirm the specific I2C interface with choices of I2C1, I2C2 and I2C3.
  * @retval I2Cx Status
  */
TypeI2CxStatus I2CInterfaceConfirm(void)
{
	switch(I2Cx){
		//case I2Cx1: hi2cx = &hi2c1; return statusOK;
		case I2Cx1: break;
		//case I2Cx2: hi2cx = &hi2c2; return statusOK;
		case I2Cx2: break;
		case I2Cx3: hi2cx = &hi2c3; return statusOK;
		//case I2Cx3: break;
	}
	return statusERROR;
}


/**
  * @brief  I2C write slave function.
  * @param1 DevAddress： slave device address.
  * @param2 pData： the pointer pointing to variable which saving the data you wanting to send.
  * @param3 dataSize： data's size with unit[bytes].
  * @retval I2Cx Status
  */
TypeI2CxStatus I2CWrite( uint16_t DevAddress, uint8_t *pData, uint16_t dataSize)
{
	I2CStatus = HAL_I2C_Master_Transmit(hi2cx, DevAddress, pData, dataSize, I2C_COMMUNICATION_TIMEOUT);
	return I2CStatus;
}


/**
  * @brief  I2C read slave function.
  * @param1 DevAddress： slave device address.
  * @param2 pData： the pointer pointing to variable which will saving the data you gathering from sensor.
  * @param3 dataSize： data's size with unit[bytes].
  * @retval I2Cx Status
  */
TypeI2CxStatus I2CRead(uint16_t DevAddress, uint8_t *pData, uint16_t dataSize)
{
	I2CStatus = HAL_I2C_Master_Receive(hi2cx, DevAddress, pData, dataSize, I2C_COMMUNICATION_TIMEOUT);
	return I2CStatus;
}
