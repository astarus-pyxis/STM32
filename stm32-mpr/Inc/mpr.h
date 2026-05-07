/******************************************************************************************* */
/*                                                                                           */
/* MPR.h                                                                                     */
/*                                                                                           */
/* Minimal driver to interface MPR pressure sensors with STM32H7 microcontroller             */
/*                                                                                           */
/* Florian TOPEZA & Merlin KOOSHMANIAN - 2025                                                */
/*                                                                                           */
/******************************************************************************************* */

#ifndef INC_MPR_H_
// Header guard to prevent multiple inclusions
#define INC_MPR_H_

/** Include standard libraries */
#include <stdbool.h> 		// Required to use booleans
#include <stdint.h> 		// Required to use uint8_t and uint16_t
#include <stdlib.h>			// To dynamically allocate memory

/** Include STM32 HAL */
#include "stm32h7xx_hal.h" 	// HAL functions for GPIO and Timers used here are declared in the HAL files

/** Private include to use the console serial port  */
#include "console.h"

/** Private include to return error type */
#include "errors.h"

/******************************* INCLUDES BEGIN ******************************************** */

/******************************* DEFINE BEGIN ********************************************** */

/* Debug MPR */

#define DEBUG_MPR

#ifdef DEBUG_MPR
#define logs_mpr(...) printf(__VA_ARGS__)
#else
#define logs_mpr(...)
#endif

#define MPR_I2C_ADDRESS	            0x30	// 7-bit address shifted to the left
#define MPR_PRESSURE_READ_CMD_SIZE	3		// MPR Pressure read command size
#define MPR_NOP_CMD_SIZE		    1		// MPR NOP command size
#define MPR_DATA_SIZE		        4		// MPR data size (4 bytes)

#define MPR_PMAX                    25.0f   // MPR maximum pressure (PSI)
#define MPR_PMIN                    0.0f    // MPR minimum pressure (PSI)

/*********************************** DEFINE END ******************************************** */

/******************************** TYPEDEF BEGIN ******************************************** */

typedef struct {

    I2C_HandleTypeDef *p_hi2c;                  // I2C TypeDef instance pointer

} MPR_t;

/******************************** TYPEDEF END ********************************************** */

/************************** FUNCTION PROTOTYPES BEGIN ************************************** */

error_t MPR_Receive_Data(MPR_t* sensor, uint8_t* data);
float MPR_Calculate_Pressure(const uint8_t* raw_data);

/************************** FUNCTION PROTOTYPES END **************************************** */

 #endif /* INC_MPR_H_ */

/********************************** END OF FILE ******************************************** */
