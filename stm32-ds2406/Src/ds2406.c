#include "ds2406.h"
#include "stm32f1xx_hal.h"

/* Private defines */
#define DELAY_US(us) do { volatile uint32_t i; for (i = 0U; i < ((us) * 8U); i++) { __NOP(); } } while(0)

/* Private function prototypes */
static void OneWire_WriteBit(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin, uint8_t bit);
static uint8_t OneWire_ReadBit(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin);
static void OneWire_WriteByte(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin, uint8_t byte);
static uint8_t OneWire_ReadByte(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin);
static uint8_t OneWire_Reset(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin);

/* Public functions */

/**
 * @brief  Initialize the DS2406 handle
 * @param  hds2406: Pointer to DS2406 handle
 * @param  GPIO_Port: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval error_t
 */
error_t DS2406_Init(DS2406_HandleTypeDef *hds2406, GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin) {
    
    error_t err = OK;

    if (hds2406 == NULL) {
        err = NULL_POINTER;
    }

    hds2406->GPIO_Port = GPIO_Port;
    hds2406->GPIO_Pin = GPIO_Pin;

    /* Configure GPIO as open drain output */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);

    /* Set pin high */
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_SET);

    return err;
}

/**
 * @brief  Read the ROM ID of the DS2406
 * @param  hds2406: Pointer to DS2406 handle
 * @retval error_t
 */
error_t DS2406_ReadROM(DS2406_HandleTypeDef *hds2406) {
    error_t err = OK;

    if (hds2406 == NULL) {
        err = NULL_POINTER;
    }

    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_READ_ROM);

    for (uint8_t i = 0U; i < 8U; i++) {
        hds2406->ROM[i] = OneWire_ReadByte(hds2406->GPIO_Port, hds2406->GPIO_Pin);
    }

    return err;
}

/**
 * @brief  Write data to DS2406 memory
 * @param  hds2406: Pointer to DS2406 handle
 * @param  address: Starting address
 * @param  data: Pointer to data
 * @param  length: Length of data
 * @retval error_t
 */
error_t DS2406_WriteMemory(DS2406_HandleTypeDef *hds2406, uint16_t address, const uint8_t *data, uint8_t length) {
    error_t err = OK;

    if ((hds2406 == NULL) || (data == NULL) || (length == 0U) || (length > 32U)) {
        err = INVALID_ARGUMENT;
    }

    /* Write to scratchpad */
    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_SKIP_ROM);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_WRITE_SCRATCHPAD);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, (uint8_t)(address & 0xFFU));
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, (uint8_t)(address >> 8U));

    for (uint8_t i = 0U; i < length; i++) {
        OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, data[i]);
    }

    /* Read scratchpad to verify */
    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_SKIP_ROM);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_READ_SCRATCHPAD);

    uint8_t ta1 = OneWire_ReadByte(hds2406->GPIO_Port, hds2406->GPIO_Pin);
    uint8_t ta2 = OneWire_ReadByte(hds2406->GPIO_Port, hds2406->GPIO_Pin);
    uint8_t es = OneWire_ReadByte(hds2406->GPIO_Port, hds2406->GPIO_Pin);

    /* Copy scratchpad to memory */
    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_SKIP_ROM);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_COPY_SCRATCHPAD);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, ta1);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, ta2);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, es);

    HAL_Delay(10U); /* Wait for copy operation */

    return err;
}

/**
 * @brief  Read data from DS2406 memory
 * @param  hds2406: Pointer to DS2406 handle
 * @param  address: Starting address
 * @param  data: Pointer to data buffer
 * @param  length: Length of data
 * @retval error_t
 */
error_t DS2406_ReadMemory(DS2406_HandleTypeDef *hds2406, uint16_t address, uint8_t *data, uint8_t length) {
    error_t err = OK;

    if ((hds2406 == NULL) || (data == NULL) || (length == 0U)) {
        err = INVALID_ARGUMENT;
    }

    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_SKIP_ROM);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_READ_MEMORY);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, (uint8_t)(address & 0xFFU));
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, (uint8_t)(address >> 8U));

    for (uint8_t i = 0U; i < length; i++) {
        data[i] = OneWire_ReadByte(hds2406->GPIO_Port, hds2406->GPIO_Pin);
    }

    return err;
}


/**
 * @brief  Set the PIO pins
 * @param  hds2406: Pointer to DS2406 handle
 * @param  pioA: State for PIO A
 * @param  pioB: State for PIO B
 * @retval error_t
 */
error_t DS2406_SetPIO(DS2406_HandleTypeDef *hds2406, bool pioA, bool pioB) {
    error_t err = OK;

    if (hds2406 == NULL) {
        err = INVALID_ARGUMENT;;
    }

    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_SKIP_ROM);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_CHANNEL_ACCESS);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, 0x00U); /* Write control */

    uint8_t data = 0U;
    if (pioA) {
        data |= 0x01U;
    }
    if (pioB) {
        data |= 0x02U;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, data);

    return err;
}

/**
 * @brief  Get the PIO pins state
 * @param  hds2406: Pointer to DS2406 handle
 * @param  pioA: Pointer to PIO A state
 * @param  pioB: Pointer to PIO B state
 * @retval error_t
 */
error_t DS2406_GetPIO(DS2406_HandleTypeDef *hds2406, bool *pioA, bool *pioB) {
    error_t err = OK;

    if ((hds2406 == NULL) || (pioA == NULL) || (pioB == NULL)) {
        err = INVALID_ARGUMENT;
    }

    if (OneWire_Reset(hds2406->GPIO_Port, hds2406->GPIO_Pin) != 0U) {
        err = NO_DEVICE;
    }

    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_SKIP_ROM);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, DS2406_CMD_CHANNEL_ACCESS);
    OneWire_WriteByte(hds2406->GPIO_Port, hds2406->GPIO_Pin, 0x80U); /* Read control */

    uint8_t data = OneWire_ReadByte(hds2406->GPIO_Port, hds2406->GPIO_Pin);

    *pioA = ((data & 0x01U) != 0U);
    *pioB = ((data & 0x02U) != 0U);

    return err;
}

/* Private functions */

/**
 * @brief  Write a bit to 1-Wire bus
 * @param  GPIO_Port: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @param  bit: Bit to write
 */
static void OneWire_WriteBit(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin, uint8_t bit) {
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_RESET);
    DELAY_US(5U);
    if (bit != 0U) {
        HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_SET);
    }
    DELAY_US(55U);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_SET);
}

/**
 * @brief  Read a bit from 1-Wire bus
 * @param  GPIO_Port: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval Bit value
 */
static uint8_t OneWire_ReadBit(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin) {
    uint8_t bit = 0U;
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_RESET);
    DELAY_US(5U);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_SET);
    DELAY_US(5U);
    bit = (uint8_t)HAL_GPIO_ReadPin(GPIO_Port, GPIO_Pin);
    DELAY_US(50U);
    return bit;
}

/**
 * @brief  Write a byte to 1-Wire bus
 * @param  GPIO_Port: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @param  byte: Byte to write
 */
static void OneWire_WriteByte(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin, uint8_t byte) {
    for (uint8_t i = 0U; i < 8U; i++) {
        OneWire_WriteBit(GPIO_Port, GPIO_Pin, (byte & 0x01U));
        byte >>= 1U;
    }
}

/**
 * @brief  Read a byte from 1-Wire bus
 * @param  GPIO_Port: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval Byte value
 */
static uint8_t OneWire_ReadByte(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin) {
    uint8_t byte = 0U;
    for (uint8_t i = 0U; i < 8U; i++) {
        byte >>= 1U;
        if (OneWire_ReadBit(GPIO_Port, GPIO_Pin) != 0U) {
            byte |= 0x80U;
        }
    }
    return byte;
}

/**
 * @brief  Reset 1-Wire bus
 * @param  GPIO_Port: GPIO port
 * @param  GPIO_Pin: GPIO pin
 * @retval Presence pulse (0 = device present)
 */
static uint8_t OneWire_Reset(GPIO_TypeDef *GPIO_Port, uint16_t GPIO_Pin) {
    uint8_t presence = 1U;
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_RESET);
    DELAY_US(480U);
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, GPIO_PIN_SET);
    DELAY_US(70U);
    presence = (uint8_t)HAL_GPIO_ReadPin(GPIO_Port, GPIO_Pin);
    DELAY_US(410U);
    return presence;
}