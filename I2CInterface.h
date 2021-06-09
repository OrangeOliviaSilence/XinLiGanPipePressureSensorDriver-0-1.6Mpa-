#ifndef __I2CINTERFACE_H__
#define __I2CINTERFACE_H__


/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdint.h"
/* USER CODE END Includes */

/* USER CODE BEGIN PD */
#define I2C_COMMUNICATION_TIMEOUT 	100		//100ms
/* USER CODE END PD */

/* USER CODE BEGIN PTD */
/*!
 * I2Cx type
 * I2Cx: x with choices of 1, 2 and 3, choose the serial number of I2C interface you used in your application.
 */
typedef enum enumTypeI2Cx{
	I2Cx1 = 0x01,
	I2Cx2 = 0x02,
	I2Cx3 = 0x03,
}TypeI2Cx;

/*!
 * I2Cx communication status
 */
typedef enum enumTypeI2CxStatus{
	statusOK       = 0x00,
	statusERROR    = 0x01,
	statusBUSY     = 0x02,
	statusTIMEOUT  = 0x03
}TypeI2CxStatus;
/* USER CODE END PTD */

/* USER CODE BEGIN PF */
TypeI2CxStatus I2CInterfaceConfirm(void);
TypeI2CxStatus I2CWrite(uint16_t DevAddress, uint8_t *pData, uint16_t dataSize);
TypeI2CxStatus I2CRead(uint16_t DevAddress, uint8_t *pData, uint16_t dataSize);
/* USER CODE END PF */


#endif
