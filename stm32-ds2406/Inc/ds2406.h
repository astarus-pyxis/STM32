#ifndef DS2406_H
#define DS2406_H

// Adapt the following include to your STM32 series
#include "stm32f1xx_hal.h"

// Include error type
#include "errors.h"

#include <stdint.h>
#include <stdbool.h>

/* DS2406 Commands */
#define DS2406_CMD_READ_ROM           0x33U
#define DS2406_CMD_MATCH_ROM          0x55U
#define DS2406_CMD_SKIP_ROM           0xCCU
#define DS2406_CMD_SEARCH_ROM         0xF0U
#define DS2406_CMD_CONDITIONAL_SEARCH 0xECU
#define DS2406_CMD_WRITE_SCRATCHPAD   0x0FU
#define DS2406_CMD_READ_SCRATCHPAD    0xAAU
#define DS2406_CMD_COPY_SCRATCHPAD    0x55U
#define DS2406_CMD_READ_MEMORY        0xF0U
#define DS2406_CMD_CHANNEL_ACCESS     0xF5U

/* Handle structure */
typedef struct {
    GPIO_TypeDef *GPIO_Port;
    uint16_t GPIO_Pin;
    uint8_t ROM[8U];
} DS2406_HandleTypeDef;

/* Function prototypes */
error_t DS2406_Init(DS2406_HandleTypeDef *hds2406, GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin);
error_t DS2406_ReadROM(DS2406_HandleTypeDef *hds2406);
error_t DS2406_WriteMemory(DS2406_HandleTypeDef *hds2406, uint16_t address, const uint8_t *data, uint8_t length);
error_t DS2406_ReadMemory(DS2406_HandleTypeDef *hds2406, uint16_t address, uint8_t *data, uint8_t length);
error_t DS2406_SetPIO(DS2406_HandleTypeDef *hds2406, bool pioA, bool pioB);
error_t DS2406_GetPIO(DS2406_HandleTypeDef *hds2406, bool *pioA, bool *pioB);

#endif /* DS2406_H */