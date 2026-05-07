/******************************************************************************************* */
/*                                                                                           */
/* LSM303AGR library                                                                         */
/*                                                                                           */
/* This library provides functions to interface an STM32 microcontroller with the ST         */
/* LSM303AGR sensor through I2C.                                                             */
/*                                                                                           */
/* Florian TOPEZA & Merlin KOOSHMANIAN - 2025                                                */
/*                                                                                           */
/******************************************************************************************* */

#ifndef __LSM303AGR_H
// Header guard to prevent multiple inclusions
#define __LSM303AGR_H

/******************************* INCLUDES BEGIN ******************************************** */

/** Include standard libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/** Include STM32 HAL */
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_def.h"

/** Include error enum type */
#include "errors.h"

/******************************* INCLUDES END ********************************************** */

/******************************* DEFINE BEGIN ********************************************** */

#ifdef DEBUG_LSM303AGR
#include "console.h"
#define logs_lsm303agr(...) printf(__VA_ARGS__)
#else
#define logs_lsm303agr(...)
#endif

/*############################# ACCELEROMETER ################################*/
/* Read/Write command */
#define READWRITE_CMD                     ((uint8_t)0x80)
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD                  ((uint8_t)0x40)
/* Dummy Byte Send by the SPI Master device in order to generate the Clock to the Slave device */
#define DUMMY_BYTE                        ((uint8_t)0x00)

/********************* START LSM303AGR REGISTER MAPPING  **********************/

/* Exported constant IO ------------------------------------------------------*/
#define ACC_I2C_ADDRESS                      0x32
#define MAG_I2C_ADDRESS                      0x3C
#define I2C_BUFFER_MAX_SIZE                  32U

/* Temperature sensor Registers (New vs lsm303dlhc.h) */
#define LSM303AGR_STATUS_REG_AUX_A          0x07  /* status register */
#define LSM303AGR_OUT_TEMP_L_A              0x0C  /* output temperature register */
#define LSM303AGR_OUT_TEMP_H_A              0x0D  /* output temperature register */
#define LSM303AGR_IN_COUNTER_REG_A          0x0E  /* register */
/* Acceleration Registers */
#define LSM303AGR_WHO_AM_I_A                0x0F  /* device identification register (0x33) */
/* Temperature sensor Registers (New vs lsm303dlhc.h) */
#define LSM303AGR_TEMP_CFG_REG_A            0x1F  /* temperature configuration register */
/* Acceleration Registers */
#define LSM303AGR_CTRL_REG1_A               0x20  /* Control register 1 acceleration */
#define LSM303AGR_CTRL_REG2_A               0x21  /* Control register 2 acceleration */
#define LSM303AGR_CTRL_REG3_A               0x22  /* Control register 3 acceleration */
#define LSM303AGR_CTRL_REG4_A               0x23  /* Control register 4 acceleration */
#define LSM303AGR_CTRL_REG5_A               0x24  /* Control register 5 acceleration */
#define LSM303AGR_CTRL_REG6_A               0x25  /* Control register 6 acceleration */
#define LSM303AGR_REFERENCE_A               0x26  /* Reference register acceleration */
#define LSM303AGR_STATUS_REG_A              0x27  /* Status register acceleration */
#define LSM303AGR_OUT_X_L_A                 0x28  /* Output Register X acceleration */
#define LSM303AGR_OUT_X_H_A                 0x29  /* Output Register X acceleration */
#define LSM303AGR_OUT_Y_L_A                 0x2A  /* Output Register Y acceleration */
#define LSM303AGR_OUT_Y_H_A                 0x2B  /* Output Register Y acceleration */
#define LSM303AGR_OUT_Z_L_A                 0x2C  /* Output Register Z acceleration */
#define LSM303AGR_OUT_Z_H_A                 0x2D  /* Output Register Z acceleration */
#define LSM303AGR_FIFO_CTRL_REG_A           0x2E  /* Fifo control Register acceleration */
#define LSM303AGR_FIFO_SRC_REG_A            0x2F  /* Fifo src Register acceleration */

#define LSM303AGR_INT1_CFG_A                0x30  /* Interrupt 1 configuration Register acceleration */
#define LSM303AGR_INT1_SOURCE_A             0x31  /* Interrupt 1 source Register acceleration */
#define LSM303AGR_INT1_THS_A                0x32  /* Interrupt 1 Threshold register acceleration */
#define LSM303AGR_INT1_DURATION_A           0x33  /* Interrupt 1 DURATION register acceleration */

#define LSM303AGR_INT2_CFG_A                0x34  /* Interrupt 2 configuration Register acceleration */
#define LSM303AGR_INT2_SOURCE_A             0x35  /* Interrupt 2 source Register acceleration */
#define LSM303AGR_INT2_THS_A                0x36  /* Interrupt 2 Threshold register acceleration */
#define LSM303AGR_INT2_DURATION_A           0x37  /* Interrupt 2 DURATION register acceleration */

#define LSM303AGR_CLICK_CFG_A               0x38  /* Click configuration Register acceleration */
#define LSM303AGR_CLICK_SOURCE_A            0x39  /* Click 2 source Register acceleration */
#define LSM303AGR_CLICK_THS_A               0x3A  /* Click 2 Threshold register acceleration */

#define LSM303AGR_TIME_LIMIT_A              0x3B  /* Time Limit Register acceleration */
#define LSM303AGR_TIME_LATENCY_A            0x3C  /* Time Latency Register acceleration */
#define LSM303AGR_TIME_WINDOW_A             0x3D  /* Time window register acceleration */

/* System Registers(New vs lsm303dlhc.h) */
#define LSM303AGR_Act_THS_A                 0x3E  /* return to sleep activation threshold register */
#define LSM303AGR_Act_DUR_A                 0x3F  /* return to sleep duration register */
/* Magnetometer */
#define LSM303AGR_X_REG_L_M                 0x45  /* Hard-iron X magnetic field */
#define LSM303AGR_X_REG_H_M                 0x46  /* Hard-iron X magnetic field */
#define LSM303AGR_Y_REG_L_M                 0x47  /* Hard-iron Y magnetic field */
#define LSM303AGR_Y_REG_H_M                 0x48  /* Hard-iron Y magnetic field */
#define LSM303AGR_Z_REG_L_M                 0x49  /* Hard-iron Z magnetic field */

#define LSM303AGR_Z_REG_H_M                 0x4A  /* Hard-iron Z magnetic field */
/* Legacy Define */
#define LSM303AGR_Z_REH_H_M                 LSM303AGR_Z_REG_H_M

#define LSM303AGR_WHO_AM_I_M                0x4F  /* Who am i register magnetic field (0x40) */
#define LSM303AGR_CFG_REG_A_M               0x60  /* Configuration register A magnetic field */
#define LSM303AGR_CFG_REG_B_M               0x61  /* Configuration register B magnetic field */
#define LSM303AGR_CFG_REG_C_M               0x62  /* Configuration register C magnetic field */
#define LSM303AGR_INT_CTRL_REG_M            0x63  /* interrupt control register magnetic field */
#define LSM303AGR_INT_SOURCE_REG_M          0x64  /* interrupt source register magnetic field */
#define LSM303AGR_INT_THS_L_REG_M           0x65  /* interrupt threshold register magnetic field */
#define LSM303AGR_INT_THS_H_REG_M           0x66  /* interrupt threshold register magnetic field*/
#define LSM303AGR_STATUS_REG_M              0x67  /* Status Register magnetic field */
#define LSM303AGR_OUTX_L_REG_M              0x68  /* Output Register X magnetic field */
#define LSM303AGR_OUTX_H_REG_M              0x69  /* Output Register X magnetic field */
#define LSM303AGR_OUTY_L_REG_M              0x6A  /* Output Register X magnetic field */
#define LSM303AGR_OUTY_H_REG_M              0x6B  /* Output Register X magnetic field */
#define LSM303AGR_OUTZ_L_REG_M              0x6C  /* Output Register X magnetic field */
#define LSM303AGR_OUTZ_H_REG_M              0x6D  /* Output Register X magnetic field */

/**************************** END REGISTER MAPPING  ***************************/

#define I_AM_LSM303AGR                   ((uint8_t)0x33)

/** Acc_Power_Mode_selection */
#define LSM303AGR_NORMAL_MODE            ((uint8_t)0x00)
#define LSM303AGR_LOWPOWER_MODE          ((uint8_t)0x08)


/** Acc_OutPut_DataRate_Selection */
#define LSM303AGR_ODR_1_HZ                ((uint8_t)0x10)  /*!< Output Data Rate = 1 Hz */
#define LSM303AGR_ODR_10_HZ               ((uint8_t)0x20)  /*!< Output Data Rate = 10 Hz */
#define LSM303AGR_ODR_25_HZ               ((uint8_t)0x30)  /*!< Output Data Rate = 25 Hz */
#define LSM303AGR_ODR_50_HZ               ((uint8_t)0x40)  /*!< Output Data Rate = 50 Hz */
#define LSM303AGR_ODR_100_HZ              ((uint8_t)0x50)  /*!< Output Data Rate = 100 Hz */
#define LSM303AGR_ODR_200_HZ              ((uint8_t)0x60)  /*!< Output Data Rate = 200 Hz */
#define LSM303AGR_ODR_400_HZ              ((uint8_t)0x70)  /*!< Output Data Rate = 400 Hz */
#define LSM303AGR_ODR_1620_HZ_LP          ((uint8_t)0x80)  /*!< Output Data Rate = 1620 Hz only in Low Power Mode */
#define LSM303AGR_ODR_1344_HZ             ((uint8_t)0x90)  /*!< Output Data Rate = 1344 Hz in Normal mode and 5376 Hz in Low Power Mode */

/** Acc_Axes_Selection */
#define LSM303AGR_X_ENABLE                ((uint8_t)0x01)
#define LSM303AGR_Y_ENABLE                ((uint8_t)0x02)
#define LSM303AGR_Z_ENABLE                ((uint8_t)0x04)
#define LSM303AGR_AXES_ENABLE             ((uint8_t)0x07)
#define LSM303AGR_AXES_DISABLE            ((uint8_t)0x00)

/** Acc_High_Resolution */
#define LSM303AGR_HR_ENABLE               ((uint8_t)0x08)
#define LSM303AGR_HR_DISABLE              ((uint8_t)0x00)


/** Acc_Full_Scale_Selection */
#define LSM303AGR_FULLSCALE_2G            ((uint8_t)0x00)  /*!< ±2 g */
#define LSM303AGR_FULLSCALE_4G            ((uint8_t)0x10)  /*!< ±4 g */
#define LSM303AGR_FULLSCALE_8G            ((uint8_t)0x20)  /*!< ±8 g */
#define LSM303AGR_FULLSCALE_16G           ((uint8_t)0x30)  /*!< ±16 g */

/** Acc_Full_Scale_Selection */
#define LSM303AGR_ACC_SENSITIVITY_2G     ((uint8_t)1)  /*!< accelerometer sensitivity with 2 g full scale [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_4G     ((uint8_t)2)  /*!< accelerometer sensitivity with 4 g full scale [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_8G     ((uint8_t)4)  /*!< accelerometer sensitivity with 8 g full scale [mg/LSB] */
#define LSM303AGR_ACC_SENSITIVITY_16G    ((uint8_t)12) /*!< accelerometer sensitivity with 12 g full scale [mg/LSB] */


/** Acc_Block_Data_Update */
#define LSM303AGR_BlockUpdate_Continous   ((uint8_t)0x00) /*!< Continuos Update */
#define LSM303AGR_BlockUpdate_Single      ((uint8_t)0x80) /*!< Single Update: output registers not updated until MSB and LSB reading */

/** @ Acc_Endian_Data_selection */
#define LSM303AGR_BLE_LSB                 ((uint8_t)0x00) /*!< Little Endian: data LSB @ lower address */
#define LSM303AGR_BLE_MSB                 ((uint8_t)0x40) /*!< Big Endian: data MSB @ lower address */


/** @ Acc_Boot_Mode_selection */
#define LSM303AGR_BOOT_NORMALMODE         ((uint8_t)0x00)
#define LSM303AGR_BOOT_REBOOTMEMORY       ((uint8_t)0x80)


/** Acc_High_Pass_Filter_Mode */
#define LSM303AGR_HPM_NORMAL_MODE_RES     ((uint8_t)0x00)
#define LSM303AGR_HPM_REF_SIGNAL          ((uint8_t)0x40)
#define LSM303AGR_HPM_NORMAL_MODE         ((uint8_t)0x80)
#define LSM303AGR_HPM_AUTORESET_INT       ((uint8_t)0xC0)


/** Acc_High_Pass_CUT OFF_Frequency */
#define LSM303AGR_HPFCF_8                 ((uint8_t)0x00)
#define LSM303AGR_HPFCF_16                ((uint8_t)0x10)
#define LSM303AGR_HPFCF_32                ((uint8_t)0x20)
#define LSM303AGR_HPFCF_64                ((uint8_t)0x30)


/** Acc_High_Pass_Filter_status */
#define LSM303AGR_HIGHPASSFILTER_DISABLE  ((uint8_t)0x00)
#define LSM303AGR_HIGHPASSFILTER_ENABLE   ((uint8_t)0x08)


/** Acc_High_Pass_Filter_Click_status */
#define LSM303AGR_HPF_CLICK_DISABLE       ((uint8_t)0x00)
#define LSM303AGR_HPF_CLICK_ENABLE        ((uint8_t)0x04)


/** Acc_High_Pass_Filter_AOI1_status */
#define LSM303AGR_HPF_AOI1_DISABLE        ((uint8_t)0x00)
#define LSM303AGR_HPF_AOI1_ENABLE	       ((uint8_t)0x01)


/** Acc_High_Pass_Filter_AOI2_status */
#define LSM303AGR_HPF_AOI2_DISABLE        ((uint8_t)0x00)
#define LSM303AGR_HPF_AOI2_ENABLE         ((uint8_t)0x02)


/** Acc_Interrupt1_Configuration_definition */
#define LSM303AGR_IT1_CLICK               ((uint8_t)0x80)
#define LSM303AGR_IT1_AOI1                ((uint8_t)0x40)
#define LSM303AGR_IT1_AOI2                ((uint8_t)0x20)
#define LSM303AGR_IT1_DRY1                ((uint8_t)0x10)
#define LSM303AGR_IT1_DRY2                ((uint8_t)0x08)
#define LSM303AGR_IT1_WTM                 ((uint8_t)0x04)
#define LSM303AGR_IT1_OVERRUN             ((uint8_t)0x02)


/** Acc_Interrupt2_Configuration_definition */
#define LSM303AGR_IT2_CLICK               ((uint8_t)0x80)
#define LSM303AGR_IT2_INT1                ((uint8_t)0x40)
#define LSM303AGR_IT2_INT2                ((uint8_t)0x20)
#define LSM303AGR_IT2_BOOT                ((uint8_t)0x10)
#define LSM303AGR_IT2_ACT                 ((uint8_t)0x08)
#define LSM303AGR_IT2_HLACTIVE            ((uint8_t)0x02)


/** Acc_INT_Combination_Status */
#define LSM303AGR_OR_COMBINATION          ((uint8_t)0x00)  /*!< OR combination of enabled IRQs */
#define LSM303AGR_AND_COMBINATION         ((uint8_t)0x80)  /*!< AND combination of enabled IRQs */
#define LSM303AGR_MOV_RECOGNITION         ((uint8_t)0x40)  /*!< 6D movement recognition */
#define LSM303AGR_POS_RECOGNITION         ((uint8_t)0xC0)  /*!< 6D position recognition */


/** Acc_INT_Axes */
#define LSM303AGR_Z_HIGH                  ((uint8_t)0x20)  /*!< Z High enabled IRQs */
#define LSM303AGR_Z_LOW                   ((uint8_t)0x10)  /*!< Z low enabled IRQs */
#define LSM303AGR_Y_HIGH                  ((uint8_t)0x08)  /*!< Y High enabled IRQs */
#define LSM303AGR_Y_LOW                   ((uint8_t)0x04)  /*!< Y low enabled IRQs */
#define LSM303AGR_X_HIGH                  ((uint8_t)0x02)  /*!< X High enabled IRQs */
#define LSM303AGR_X_LOW                   ((uint8_t)0x01)  /*!< X low enabled IRQs */


/** Acc_INT_Click */
#define LSM303AGR_Z_DOUBLE_CLICK          ((uint8_t)0x20)  /*!< Z double click IRQs */
#define LSM303AGR_Z_SINGLE_CLICK          ((uint8_t)0x10)  /*!< Z single click IRQs */
#define LSM303AGR_Y_DOUBLE_CLICK          ((uint8_t)0x08)  /*!< Y double click IRQs */
#define LSM303AGR_Y_SINGLE_CLICK          ((uint8_t)0x04)  /*!< Y single click IRQs */
#define LSM303AGR_X_DOUBLE_CLICK          ((uint8_t)0x02)  /*!< X double click IRQs */
#define LSM303AGR_X_SINGLE_CLICK          ((uint8_t)0x01)  /*!< X single click IRQs */

/** Acc_INT1_Interrupt_status */
#define LSM303AGR_INT1INTERRUPT_DISABLE   ((uint8_t)0x00)
#define LSM303AGR_INT1INTERRUPT_ENABLE    ((uint8_t)0x80)


/** Acc_INT1_Interrupt_ActiveEdge */
#define LSM303AGR_INT1INTERRUPT_LOW_EDGE  ((uint8_t)0x20)
#define LSM303AGR_INT1INTERRUPT_HIGH_EDGE ((uint8_t)0x00)


/** Mag_Data_Rate */
#define LSM303AGR_ODR_0_75_HZ              ((uint8_t) 0x00)  /*!< Output Data Rate = 0.75 Hz */
#define LSM303AGR_ODR_1_5_HZ               ((uint8_t) 0x04)  /*!< Output Data Rate = 1.5 Hz */
#define LSM303AGR_ODR_3_0_HZ               ((uint8_t) 0x08)  /*!< Output Data Rate = 3 Hz */
#define LSM303AGR_ODR_7_5_HZ               ((uint8_t) 0x0C)  /*!< Output Data Rate = 7.5 Hz */
#define LSM303AGR_ODR_15_HZ                ((uint8_t) 0x10)  /*!< Output Data Rate = 15 Hz */
#define LSM303AGR_ODR_30_HZ                ((uint8_t) 0x14)  /*!< Output Data Rate = 30 Hz */
#define LSM303AGR_ODR_75_HZ                ((uint8_t) 0x18)  /*!< Output Data Rate = 75 Hz */
#define LSM303AGR_ODR_220_HZ               ((uint8_t) 0x1C)  /*!< Output Data Rate = 220 Hz */


/** Mag_Full_Scale */
#define  LSM303AGR_FS_1_3_GA               ((uint8_t) 0x20)  /*!< Full scale = ±1.3 Gauss */
#define  LSM303AGR_FS_1_9_GA               ((uint8_t) 0x40)  /*!< Full scale = ±1.9 Gauss */
#define  LSM303AGR_FS_2_5_GA               ((uint8_t) 0x60)  /*!< Full scale = ±2.5 Gauss */
#define  LSM303AGR_FS_4_0_GA               ((uint8_t) 0x80)  /*!< Full scale = ±4.0 Gauss */
#define  LSM303AGR_FS_4_7_GA               ((uint8_t) 0xA0)  /*!< Full scale = ±4.7 Gauss */
#define  LSM303AGR_FS_5_6_GA               ((uint8_t) 0xC0)  /*!< Full scale = ±5.6 Gauss */
#define  LSM303AGR_FS_8_1_GA               ((uint8_t) 0xE0)  /*!< Full scale = ±8.1 Gauss */


/** Magnetometer_Sensitivity */
#define LSM303AGR_M_SENSITIVITY_XY_1_3Ga     1100  /*!< magnetometer X Y axes sensitivity for 1.3 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_1_9Ga     855   /*!< magnetometer X Y axes sensitivity for 1.9 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_2_5Ga     670   /*!< magnetometer X Y axes sensitivity for 2.5 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_4Ga       450   /*!< magnetometer X Y axes sensitivity for 4 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_4_7Ga     400   /*!< magnetometer X Y axes sensitivity for 4.7 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_5_6Ga     330   /*!< magnetometer X Y axes sensitivity for 5.6 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_XY_8_1Ga     230   /*!< magnetometer X Y axes sensitivity for 8.1 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_1_3Ga      980   /*!< magnetometer Z axis sensitivity for 1.3 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_1_9Ga      760   /*!< magnetometer Z axis sensitivity for 1.9 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_2_5Ga      600   /*!< magnetometer Z axis sensitivity for 2.5 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_4Ga        400   /*!< magnetometer Z axis sensitivity for 4 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_4_7Ga      355   /*!< magnetometer Z axis sensitivity for 4.7 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_5_6Ga      295   /*!< magnetometer Z axis sensitivity for 5.6 Ga full scale [LSB/Ga] */
#define LSM303AGR_M_SENSITIVITY_Z_8_1Ga      205   /*!< magnetometer Z axis sensitivity for 8.1 Ga full scale [LSB/Ga] */


/** Mag_Working_Mode */
#define LSM303AGR_CONTINUOUS_CONVERSION     ((uint8_t) 0x00)   /*!< Continuous-Conversion Mode */
#define LSM303AGR_SINGLE_CONVERSION         ((uint8_t) 0x01)   /*!< Single-Conversion Mode */
#define LSM303AGR_SLEEP                     ((uint8_t) 0x02)   /*!< Sleep Mode */


/** Mag_Temperature_Sensor */
#define LSM303AGR_TEMPSENSOR_ENABLE         ((uint8_t) 0x80)   /*!< Temp sensor Enable */
#define LSM303AGR_TEMPSENSOR_DISABLE        ((uint8_t) 0x00)   /*!< Temp sensor Disable */


/** Mag_Big_Little_Endian */
#define LSM303AGR_MAG_BLE_MSB               ((uint8_t) 0x08)  /*!< Invert high and low parts of the data */


/*********************************** DEFINE END ******************************************** */

/******************************** TYPEDEF BEGIN ******************************************** */

/* ACCELERO High Pass Filter struct */
typedef struct
{
  uint8_t HighPassFilter_Mode_Selection;      /* Internal filter mode */
  uint8_t HighPassFilter_CutOff_Frequency;    /* High pass filter cut-off frequency */
  uint8_t HighPassFilter_AOI1;                /* HPF_enabling/disabling for AOI function on interrupt 1 */
  uint8_t HighPassFilter_AOI2;                /* HPF_enabling/disabling for AOI function on interrupt 2 */
  uint8_t HighPassFilter_Data_Sel;
  uint8_t HighPassFilter_Stat;
} ACCELERO_FilterConfig_t;

/* ACCELERO Interrupt 1 struct */
typedef struct
{
  // Default values are all 0

  uint8_t Click_En;                         /* Click interrupt on INT1 pin */
  uint8_t AOI1_En;                          /*  AOI1 interrupt on INT1 pin */
  uint8_t AOI2_En;                          /*  AOI2 interrupt on INT1 pin */
  uint8_t DRY1_En;                          /*  DRDY1 interrupt on INT1 pin */
  uint8_t DRY2_En;                          /*  DRDY2 interrupt on INT1 pin */
  uint8_t WTM_En;                           /*  FIFO watermark interrupt on INT1 pin */
  uint8_t Overrun_En;                       /*  FIFO overrun interrupt on INT1 pin */
} ACCELERO_IT1Config_t;

/* ACCELERO Interrupt 2 struct */
typedef struct
{
  // Default values are all 0

  uint8_t Click_En;                         /* Click interrupt on INT2 pin */
  uint8_t IT1_En;                           /* Interrupt 1 function enable on INT2 pin */
  uint8_t IT2_En;                           /* Interrupt 2 function enable on INT2 pin */
  uint8_t Boot_En;                          /* Boot on INT2 pin enable */
  uint8_t Activity_En;                      /* Activity interrupt enable on INT2 pin */
  uint8_t High_Latency_Active_En;           /* Interrupt active */
} ACCELERO_IT2Config_t;

/* ACCELERO INT1 configuration struct */
typedef struct
{
  // Default values are all 0

  uint8_t AOI;
  uint8_t SixD;
  uint8_t ZHIE;                            /* Z High enable IRQs */
  uint8_t ZLIE;                            /* Z Low enable IRQs */
  uint8_t YHIE;                            /* Y High enable IRQs */
  uint8_t YLIE;                            /* Y Low enable IRQs */
  uint8_t XHIE;                            /* X High enable IRQs */
  uint8_t XLIE;                            /* X Low enable IRQs */

} ACCELERO_INT1Config_t;

/* ACCELERO INT2 configuration struct */
typedef struct
{
  // Default values are all 0

  uint8_t AOI;
  uint8_t SixD;
  uint8_t ZDIE;                            /* Z Double click enable IRQs */
  uint8_t ZSIE;                            /* Z Single click enable IRQs */
  uint8_t YDIE;                            /* Y Double click enable IRQs */
  uint8_t YSIE;                            /* Y Single click enable IRQs */
  uint8_t XDIE;                            /* X Double click enable IRQs */
  uint8_t XSIE;                            /* X Single click enable IRQs */

} ACCELERO_INT2Config_t;

/* ACCELERO struct */
typedef struct
{
  uint8_t Power_Mode;                         /* Power-down/Normal Mode */
  uint8_t AccOutput_DataRate;                 /* OUT data rate */
  uint8_t Axes_Enable;                        /* Axes enable */
  uint8_t High_Resolution;                    /* High Resolution enabling/disabling */
  uint8_t BlockData_Update;                   /* Block Data Update */
  uint8_t Endianness;                         /* Endian Data selection */
  uint8_t AccFull_Scale;                      /* Full Scale selection */
  uint8_t Communication_Mode;

  ACCELERO_FilterConfig_t FilterStruct;

  ACCELERO_IT1Config_t    IT1Struct;
  ACCELERO_IT2Config_t    IT2Struct;

  ACCELERO_INT1Config_t   INT1Struct;
  ACCELERO_INT2Config_t   INT2Struct;

} ACCELERO_t;

/* MAGNETO struct */
typedef struct
{
  uint8_t Comp_Temp_En;                   /* Enable temperature compensation, default 0 */
  uint8_t Mag_ODR;                        /* Output Data Rate configuration, default 00 (10Hz ODR)*/
  uint8_t INT_MAG_Pin;                    /* If 1, the INTERRUPT signal (INT bit inside INT_SOURCE_REG_M) is driven on INT_MAG_PIN */
  uint8_t I2C_DIS;                        /* If 1, the I2C interface is disabled and only the SPI interface can be used, default 0 */
  uint8_t Self_test;                      /* Self test enabled if 1, default 0 */
  uint8_t INT_MAG;                        /* If 1, the DRDY pin is configured as digital output */
} MAGNETO_Init_t;

// Structure for LSM303AGR Sensor instance
typedef struct {
  I2C_HandleTypeDef *p_hi2c;                    // I2C TypeDef instance

  ACCELERO_t Accelero;                        // Accelerometer configuration
  MAGNETO_Init_t Magneto;                     // Magnetometer configuration

} LSM303AGR_t;

/******************************** TYPEDEF END ********************************************** */

/************************** FUNCTION PROTOTYPES BEGIN ************************************** */

error_t LSM303AGR_Init(LSM303AGR_t* sensor);

error_t LSM303AGR_AccReadID(LSM303AGR_t* sensor, uint8_t* pBuffer);
error_t LSM303AGR_AccFilterConfig(LSM303AGR_t* sensor, uint8_t* pBuffer, ACCELERO_FilterConfig_t FilterStruct);
error_t LSM303AGR_AccReadXYZ(LSM303AGR_t* sensor, int16_t* pnRawData);
error_t LSM303AGR_AccConvertXYZ(LSM303AGR_t* sensor, const int16_t* pnRawData, int16_t* pData);
error_t LSM303AGR_AccIT1Enable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccIT1Disable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccIT2Enable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccIT2Disable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccINT1InterruptEnable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccINT1InterruptDisable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccINT2InterruptEnable(LSM303AGR_t* sensor);
error_t LSM303AGR_AccINT2InterruptDisable(LSM303AGR_t* sensor);
error_t LSM303AGR_MagInit(LSM303AGR_t* sensor);
error_t LSM303AGR_MagReadID(LSM303AGR_t* sensor, uint8_t* pBuffer);
error_t LSM303AGR_MagGetDataStatus(LSM303AGR_t* sensor, uint8_t* pBuffer);
error_t LSM303AGR_MagReadXYZ(LSM303AGR_t* sensor, int16_t* pData);

/************************** FUNCTION PROTOTYPES END **************************************** */

 #endif /* __LSM303AGR_H */

/********************************** END OF FILE ******************************************** */
