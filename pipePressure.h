#ifndef __PIPEPRESSURE_H__
#define __PIPEPRESSURE_H__


/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "I2CInterface.h"
/* USER CODE END Includes */


/* USER CODE BEGIN PD */
//Some macro for slave register's address
#define PIPEPRESSURE_ADDRESS_W 										0XDA
#define PIPEPRESSURE_ADDRESS_R 										0XDB
#define PIPEPRESSURE_PRESSUREVALUE_REGISTER_STARTADDRESS 			0X06
#define PRESSURE_VALUE_SIZE 										3 					//bytes
#define PIPEPRESSURE_TEMPERVALUE_REGISTER_STARTADDRESS 				0X09
#define TEMPER_VALUE_SIZE 											2 					//bytes

#define X_FOR_CALCULATION 											1600
/* USER CODE END PD */


/* USER CODE BEGIN PF */
void pipePressureInit(void);
TypeI2CxStatus pipePressureGetData(float *pressure, float *temper);
/* USER CODE END PF */

#endif
