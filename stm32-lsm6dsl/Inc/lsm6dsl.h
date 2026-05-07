/******************************************************************************************* */
/*                                                                                           */
/* LSM6DSL library                                                                           */
/*                                                                                           */
/* This library provides functions to interface an STM32 microcontroller with the ST LSM6DSL */
/* sensor through SPI.                                                                       */
/*                                                                                           */
/* Florian TOPEZA & Merlin KOOSHMANIAN - 2025                                                */
/*                                                                                           */
/******************************************************************************************* */

#ifndef __LSM6DSL_H
// Header guard to prevent multiple inclusions
#define __LSM6DSL_H

/******************************* INCLUDES BEGIN ******************************************** */

/** Include standard libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/** Include STM32 HAL */
#include "stm32h7xx_hal.h"

/** Include error types */
#include "errors.h"

/******************************* INCLUDES END ********************************************** */

/******************************* DEFINE BEGIN ********************************************** */

/* Debug LSM6DSL */
#ifdef DEBUG_LSM6DSL
#define logs_lsm6dsl(...) printf(__VA_ARGS__)
#else
#define logs_lsm6dsl(...)
#endif

/* SPI 3-Wire Mode */

#define LSM6DSL_SPI_3WIRE

/************** I2C Address *****************/

#define LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW 0xD4  // SAD[0] = 0
#define LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH 0xD6 // SAD[0] = 1

/************** Who am I  *******************/

#define LSM6DSL_ACC_GYRO_WHO_AM_I 0x6A // This is the value of WHO_AM_I register (address 0x0F)

/********************* START LSM303AGR REGISTER MAPPING  **********************/

#define LSM6DSL_ACC_GYRO_FUNC_CFG_ACCESS 0x01

#define LSM6DSL_ACC_GYRO_SENSOR_SYNC_TIME 0x04
#define LSM6DSL_ACC_GYRO_SENSOR_RES_RATIO 0x05

#define LSM6DSL_ACC_GYRO_FIFO_CTRL1 0x06
#define LSM6DSL_ACC_GYRO_FIFO_CTRL2 0x07
#define LSM6DSL_ACC_GYRO_FIFO_CTRL3 0x08
#define LSM6DSL_ACC_GYRO_FIFO_CTRL4 0x09
#define LSM6DSL_ACC_GYRO_FIFO_CTRL5 0x0A

#define LSM6DSL_ACC_GYRO_DRDY_PULSE_CFG_G 0x0B
#define LSM6DSL_ACC_GYRO_INT1_CTRL 0x0D
#define LSM6DSL_ACC_GYRO_INT2_CTRL 0x0E
#define LSM6DSL_ACC_GYRO_WHO_AM_I_REG 0x0F
#define LSM6DSL_ACC_GYRO_CTRL1_XL 0x10
#define LSM6DSL_ACC_GYRO_CTRL2_G 0x11
#define LSM6DSL_ACC_GYRO_CTRL3_C 0x12
#define LSM6DSL_ACC_GYRO_CTRL4_C 0x13
#define LSM6DSL_ACC_GYRO_CTRL5_C 0x14
#define LSM6DSL_ACC_GYRO_CTRL6_C 0x15
#define LSM6DSL_ACC_GYRO_CTRL7_G 0x16
#define LSM6DSL_ACC_GYRO_CTRL8_XL 0x17
#define LSM6DSL_ACC_GYRO_CTRL9_XL 0x18
#define LSM6DSL_ACC_GYRO_CTRL10_C 0x19

#define LSM6DSL_ACC_GYRO_MASTER_CONFIG 0x1A
#define LSM6DSL_ACC_GYRO_WAKE_UP_SRC 0x1B
#define LSM6DSL_ACC_GYRO_TAP_SRC 0x1C
#define LSM6DSL_ACC_GYRO_D6D_SRC 0x1D
#define LSM6DSL_ACC_GYRO_STATUS_REG 0x1E

#define LSM6DSL_ACC_GYRO_OUT_TEMP_L 0x20
#define LSM6DSL_ACC_GYRO_OUT_TEMP_H 0x21
#define LSM6DSL_ACC_GYRO_OUTX_L_G 0x22
#define LSM6DSL_ACC_GYRO_OUTX_H_G 0x23
#define LSM6DSL_ACC_GYRO_OUTY_L_G 0x24
#define LSM6DSL_ACC_GYRO_OUTY_H_G 0x25
#define LSM6DSL_ACC_GYRO_OUTZ_L_G 0x26
#define LSM6DSL_ACC_GYRO_OUTZ_H_G 0x27
#define LSM6DSL_ACC_GYRO_OUTX_L_XL 0x28
#define LSM6DSL_ACC_GYRO_OUTX_H_XL 0x29
#define LSM6DSL_ACC_GYRO_OUTY_L_XL 0x2A
#define LSM6DSL_ACC_GYRO_OUTY_H_XL 0x2B
#define LSM6DSL_ACC_GYRO_OUTZ_L_XL 0x2C
#define LSM6DSL_ACC_GYRO_OUTZ_H_XL 0x2D
#define LSM6DSL_ACC_GYRO_SENSORHUB1_REG 0x2E
#define LSM6DSL_ACC_GYRO_SENSORHUB2_REG 0x2F
#define LSM6DSL_ACC_GYRO_SENSORHUB3_REG 0x30
#define LSM6DSL_ACC_GYRO_SENSORHUB4_REG 0x31
#define LSM6DSL_ACC_GYRO_SENSORHUB5_REG 0x32
#define LSM6DSL_ACC_GYRO_SENSORHUB6_REG 0x33
#define LSM6DSL_ACC_GYRO_SENSORHUB7_REG 0x34
#define LSM6DSL_ACC_GYRO_SENSORHUB8_REG 0x35
#define LSM6DSL_ACC_GYRO_SENSORHUB9_REG 0x36
#define LSM6DSL_ACC_GYRO_SENSORHUB10_REG 0x37
#define LSM6DSL_ACC_GYRO_SENSORHUB11_REG 0x38
#define LSM6DSL_ACC_GYRO_SENSORHUB12_REG 0x39
#define LSM6DSL_ACC_GYRO_FIFO_STATUS1 0x3A
#define LSM6DSL_ACC_GYRO_FIFO_STATUS2 0x3B
#define LSM6DSL_ACC_GYRO_FIFO_STATUS3 0x3C
#define LSM6DSL_ACC_GYRO_FIFO_STATUS4 0x3D
#define LSM6DSL_ACC_GYRO_FIFO_DATA_OUT_L 0x3E
#define LSM6DSL_ACC_GYRO_FIFO_DATA_OUT_H 0x3F
#define LSM6DSL_ACC_GYRO_TIMESTAMP0_REG 0x40
#define LSM6DSL_ACC_GYRO_TIMESTAMP1_REG 0x41
#define LSM6DSL_ACC_GYRO_TIMESTAMP2_REG 0x42

#define LSM6DSL_ACC_GYRO_TIMESTAMP_L 0x49
#define LSM6DSL_ACC_GYRO_TIMESTAMP_H 0x4A

#define LSM6DSL_ACC_GYRO_STEP_COUNTER_L 0x4B
#define LSM6DSL_ACC_GYRO_STEP_COUNTER_H 0x4C

#define LSM6DSL_ACC_GYRO_SENSORHUB13_REG 0x4D
#define LSM6DSL_ACC_GYRO_SENSORHUB14_REG 0x4E
#define LSM6DSL_ACC_GYRO_SENSORHUB15_REG 0x4F
#define LSM6DSL_ACC_GYRO_SENSORHUB16_REG 0x50
#define LSM6DSL_ACC_GYRO_SENSORHUB17_REG 0x51
#define LSM6DSL_ACC_GYRO_SENSORHUB18_REG 0x52

#define LSM6DSL_ACC_GYRO_FUNC_SRC 0x53
#define LSM6DSL_ACC_GYRO_TAP_CFG1 0x58
#define LSM6DSL_ACC_GYRO_TAP_THS_6D 0x59
#define LSM6DSL_ACC_GYRO_INT_DUR2 0x5A
#define LSM6DSL_ACC_GYRO_WAKE_UP_THS 0x5B
#define LSM6DSL_ACC_GYRO_WAKE_UP_DUR 0x5C
#define LSM6DSL_ACC_GYRO_FREE_FALL 0x5D
#define LSM6DSL_ACC_GYRO_MD1_CFG 0x5E
#define LSM6DSL_ACC_GYRO_MD2_CFG 0x5F

#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_X_L 0x66
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_X_H 0x67
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Y_L 0x68
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Y_H 0x69
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Z_L 0x6A
#define LSM6DSL_ACC_GYRO_OUT_MAG_RAW_Z_H 0x6B

#define LSM6DSL_ACC_GYRO_X_OFS_USR 0x73
#define LSM6DSL_ACC_GYRO_Y_OFS_USR 0x74
#define LSM6DSL_ACC_GYRO_Z_OFS_USR 0x75

/**************************** END REGISTER MAPPING  ***************************/

/* Accelero Full_Scale Selection */
#define LSM6DSL_ACC_FULLSCALE_2G ((uint8_t)0x00)  /*!< 2 g */
#define LSM6DSL_ACC_FULLSCALE_4G ((uint8_t)0x08)  /*!< 4 g */
#define LSM6DSL_ACC_FULLSCALE_8G ((uint8_t)0x0C)  /*!< 8 g */
#define LSM6DSL_ACC_FULLSCALE_16G ((uint8_t)0x04) /*!< 16 g */

/* Accelero Full Scale Sensitivity */
#define LSM6DSL_ACC_SENSITIVITY_2G ((float)0.061f)  /*!< accelerometer sensitivity with 2 g full scale  [mgauss/LSB] */
#define LSM6DSL_ACC_SENSITIVITY_4G ((float)0.122f)  /*!< accelerometer sensitivity with 4 g full scale  [mgauss/LSB] */
#define LSM6DSL_ACC_SENSITIVITY_8G ((float)0.244f)  /*!< accelerometer sensitivity with 8 g full scale  [mgauss/LSB] */
#define LSM6DSL_ACC_SENSITIVITY_16G ((float)0.488f) /*!< accelerometer sensitivity with 12 g full scale [mgauss/LSB] */

/* Accelero Power Mode selection */
#define LSM6DSL_ACC_GYRO_LP_XL_DISABLED ((uint8_t)0x00) /* LP disabled*/
#define LSM6DSL_ACC_GYRO_LP_XL_ENABLED ((uint8_t)0x10)  /* LP enabled*/

/* Output Data Rate */
#define LSM6DSL_ODR_BITPOSITION ((uint8_t)0xF0) /*!< Output Data Rate bit position */
#define LSM6DSL_ODR_POWER_DOWN ((uint8_t)0x00)  /* Power Down mode       */
#define LSM6DSL_ODR_13Hz ((uint8_t)0x10)        /* Low Power mode        */
#define LSM6DSL_ODR_26Hz ((uint8_t)0x20)        /* Low Power mode        */
#define LSM6DSL_ODR_52Hz ((uint8_t)0x30)        /* Low Power mode        */
#define LSM6DSL_ODR_104Hz ((uint8_t)0x40)       /* Normal mode           */
#define LSM6DSL_ODR_208Hz ((uint8_t)0x50)       /* Normal mode           */
#define LSM6DSL_ODR_416Hz ((uint8_t)0x60)       /* High Performance mode */
#define LSM6DSL_ODR_833Hz ((uint8_t)0x70)       /* High Performance mode */
#define LSM6DSL_ODR_1660Hz ((uint8_t)0x80)      /* High Performance mode */
#define LSM6DSL_ODR_3330Hz ((uint8_t)0x90)      /* High Performance mode */
#define LSM6DSL_ODR_6660Hz ((uint8_t)0xA0)      /* High Performance mode */

/* Gyro Full Scale Selection */
#define LSM6DSL_GYRO_FS_245 ((uint8_t)0x00)
#define LSM6DSL_GYRO_FS_500 ((uint8_t)0x04)
#define LSM6DSL_GYRO_FS_1000 ((uint8_t)0x08)
#define LSM6DSL_GYRO_FS_2000 ((uint8_t)0x0C)

/* Gyro Full Scale Sensitivity */
#define LSM6DSL_GYRO_SENSITIVITY_245DPS ((float)8.750f)  /**< Sensitivity value for 245 dps full scale  [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_500DPS ((float)17.50f)  /**< Sensitivity value for 500 dps full scale  [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_1000DPS ((float)35.00f) /**< Sensitivity value for 1000 dps full scale [mdps/LSB] */
#define LSM6DSL_GYRO_SENSITIVITY_2000DPS ((float)70.00f) /**< Sensitivity value for 2000 dps full scale [mdps/LSB] */

/* Gyro Power Mode selection */
#define LSM6DSL_ACC_GYRO_LP_G_DISABLED ((uint8_t)0x00) /* LP disabled*/
#define LSM6DSL_ACC_GYRO_LP_G_ENABLED ((uint8_t)0x80)  /* LP enabled*/

/* Block Data Update */
#define LSM6DSL_BDU_CONTINUOS ((uint8_t)0x00)
#define LSM6DSL_BDU_BLOCK_UPDATE ((uint8_t)0x40)

/* Auto-increment */
#define LSM6DSL_ACC_GYRO_IF_INC_DISABLED ((uint8_t)0x00)
#define LSM6DSL_ACC_GYRO_IF_INC_ENABLED ((uint8_t)0x04)

/*********************************** DEFINE END ******************************************** */

/******************************** TYPEDEF BEGIN ******************************************** */

/* Sensor configuration structure */
typedef struct
{
    uint8_t BDU;    // Block Data Update. Default value: 0
    uint8_t IF_INC; // Register address automatically incremented during a multiple byte access with a serial interface (I2C or SPI). Default value: 1

} Sensor_Config_t;

/* ACCELERO struct*/
typedef struct
{
    uint8_t ODR;        // Output Data Rate Selection. Default value: 0000
    uint8_t Full_Scale; // Full Scale selection. Default value: 00

} ACCELERO_Config_t;

/* GYRO struct */
typedef struct
{
    uint8_t ODR;        // Output Data Rate Selection. Default value: 0000
    uint8_t Full_Scale; // Full Scale selection. Default value: 00

} GYRO_Config_t;

/* Sensor struct */
typedef struct
{
    SPI_HandleTypeDef *p_hspi;  // SPI TypeDef instance
    uint32_t cs_pin;            // Chip Select GPIO Pin number
    GPIO_TypeDef *cs_gpio_port; // Chip Select GPIO port

    Sensor_Config_t Config;
    ACCELERO_Config_t Accelero;
    GYRO_Config_t Gyro;

} LSM6DSL_t;

/******************************** TYPEDEF END ********************************************** */

/************************** FUNCTION PROTOTYPES BEGIN ************************************** */

error_t LSM6DSL_IO_Init(LSM6DSL_t *sensor);

error_t LSM6DSL_Write(LSM6DSL_t *sensor, uint8_t *pBuffer, uint8_t WriteAddr, uint16_t NumByteToWrite);
error_t LSM6DSL_Read(LSM6DSL_t *sensor, uint8_t *pBuffer, uint8_t ReadAddr, uint16_t NumByteToRead);

error_t LSM6DSL_ReadID(LSM6DSL_t *sensor, uint8_t *pBuffer);

error_t LSM6DSL_AccInit(LSM6DSL_t *sensor);
error_t LSM6DSL_AccDeInit(LSM6DSL_t *sensor);
error_t LSM6DSL_AccLowPower(LSM6DSL_t *sensor, uint16_t set_low_pwr);
error_t LSM6DSL_AccReadXYZ(LSM6DSL_t *sensor, int16_t *pData);

error_t LSM6DSL_GyroInit(LSM6DSL_t *sensor);
error_t LSM6DSL_GyroDeInit(LSM6DSL_t *sensor);
error_t LSM6DSL_GyroLowPower(LSM6DSL_t *sensor, uint16_t set_low_pwr);
error_t LSM6DSL_GyroReadXYZAngRate(LSM6DSL_t *sensor, uint8_t *pBuffer);
error_t LSM6DSL_GyroConvertAngRate(LSM6DSL_t *sensor, uint8_t *buffer, float *pfData);

/************************** FUNCTION PROTOTYPES END **************************************** */

#endif /* __LSM6DSL__H */

/********************************** END OF FILE ******************************************** */
