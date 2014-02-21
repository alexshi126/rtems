/**
 * @file
 *
 * @ingroup lpc24xx_io
 *
 * @brief Input and output module.
 */

/*
 * Copyright (c) 2009-2012 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef LIBBSP_ARM_LPC24XX_IO_H
#define LIBBSP_ARM_LPC24XX_IO_H

#include <rtems.h>

#include <bsp/lpc24xx.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @defgroup lpc24xx_io IO Support and Configuration
 *
 * @ingroup lpc24xx
 *
 * @brief Input and output module.
 *
 * @{
 */

#define LPC24XX_IO_PORT_COUNT 5U

#define LPC24XX_IO_INDEX_MAX (LPC24XX_IO_PORT_COUNT * 32U)

#define LPC24XX_IO_INDEX_BY_PORT(port, bit) (((port) << 5U) + (bit))

#define LPC24XX_IO_PORT(index) ((index) >> 5U)

#define LPC24XX_IO_PORT_BIT(index) ((index) & 0x1fU)

typedef enum {
  #ifdef ARM_MULTILIB_ARCH_V4
    LPC24XX_MODULE_ACF,
  #endif
    LPC24XX_MODULE_ADC,
  #ifdef ARM_MULTILIB_ARCH_V4
    LPC24XX_MODULE_BAT_RAM,
  #endif
  LPC24XX_MODULE_CAN_0,
  LPC24XX_MODULE_CAN_1,
  LPC24XX_MODULE_DAC,
  LPC24XX_MODULE_EMC,
  LPC24XX_MODULE_ETHERNET,
  LPC24XX_MODULE_GPDMA,
  LPC24XX_MODULE_GPIO,
  LPC24XX_MODULE_I2C_0,
  LPC24XX_MODULE_I2C_1,
  LPC24XX_MODULE_I2C_2,
  LPC24XX_MODULE_I2S,
  LPC24XX_MODULE_LCD,
  LPC24XX_MODULE_MCI,
  #ifdef ARM_MULTILIB_ARCH_V7M
    LPC24XX_MODULE_MCPWM,
  #endif
  LPC24XX_MODULE_PCB,
  LPC24XX_MODULE_PWM_0,
  LPC24XX_MODULE_PWM_1,
  #ifdef ARM_MULTILIB_ARCH_V7M
    LPC24XX_MODULE_QEI,
  #endif
  LPC24XX_MODULE_RTC,
  #ifdef ARM_MULTILIB_ARCH_V4
    LPC24XX_MODULE_SPI,
  #endif
  LPC24XX_MODULE_SSP_0,
  LPC24XX_MODULE_SSP_1,
  #ifdef ARM_MULTILIB_ARCH_V7M
    LPC24XX_MODULE_SSP_2,
  #endif
  LPC24XX_MODULE_SYSCON,
  LPC24XX_MODULE_TIMER_0,
  LPC24XX_MODULE_TIMER_1,
  LPC24XX_MODULE_TIMER_2,
  LPC24XX_MODULE_TIMER_3,
  LPC24XX_MODULE_UART_0,
  LPC24XX_MODULE_UART_1,
  LPC24XX_MODULE_UART_2,
  LPC24XX_MODULE_UART_3,
  #ifdef ARM_MULTILIB_ARCH_V7M
    LPC24XX_MODULE_UART_4,
  #endif
  #ifdef ARM_MULTILIB_ARCH_V4
    LPC24XX_MODULE_WDT,
  #endif
  LPC24XX_MODULE_USB
} lpc24xx_module;

#define LPC24XX_MODULE_COUNT (LPC24XX_MODULE_USB + 1)

typedef enum {
  LPC24XX_MODULE_PCLK_DEFAULT = 0x4U,
  LPC24XX_MODULE_CCLK = 0x1U,
  LPC24XX_MODULE_CCLK_2 = 0x2U,
  LPC24XX_MODULE_CCLK_4 = 0x0U,
  LPC24XX_MODULE_CCLK_6 = 0x3U,
  LPC24XX_MODULE_CCLK_8 = 0x3U
} lpc24xx_module_clock;

#define LPC24XX_MODULE_CLOCK_MASK 0x3U

typedef enum {
  LPC24XX_GPIO_DEFAULT = 0x0U,
  LPC24XX_GPIO_RESISTOR_PULL_UP = 0x0U,
  LPC24XX_GPIO_RESISTOR_NONE = 0x1U,
  LPC24XX_GPIO_RESISTOR_PULL_DOWN = 0x2U,
  LPC24XX_GPIO_INPUT = 0x0U,
  #ifdef ARM_MULTILIB_ARCH_V7M
    LPC17XX_GPIO_REPEATER = 0x3U,
    LPC17XX_GPIO_HYSTERESIS = IOCON_HYS,
    LPC17XX_GPIO_INPUT_INVERT = IOCON_INV,
    LPC17XX_GPIO_FAST_MODE = IOCON_SLEW,
    LPC17XX_GPIO_OPEN_DRAIN = IOCON_OD,
    LPC17XX_GPIO_INPUT_FILTER = IOCON_FILTER,
  #endif
  LPC24XX_GPIO_OUTPUT = 0x8000U
} lpc24xx_gpio_settings;

rtems_status_code lpc24xx_module_enable(
  lpc24xx_module module,
  lpc24xx_module_clock clock
);

rtems_status_code lpc24xx_module_disable(
  lpc24xx_module module
);

bool lpc24xx_module_is_enabled(lpc24xx_module module);

rtems_status_code lpc24xx_gpio_config(
  unsigned index,
  lpc24xx_gpio_settings settings
);

static inline void lpc24xx_gpio_set(unsigned index)
{
  if (index <= LPC24XX_IO_INDEX_MAX) {
    unsigned port = LPC24XX_IO_PORT(index);
    unsigned bit = LPC24XX_IO_PORT_BIT(index);

    LPC24XX_FIO [port].set = 1U << bit;
  }
}

static inline void lpc24xx_gpio_clear(unsigned index)
{
  if (index <= LPC24XX_IO_INDEX_MAX) {
    unsigned port = LPC24XX_IO_PORT(index);
    unsigned bit = LPC24XX_IO_PORT_BIT(index);

    LPC24XX_FIO [port].clr = 1U << bit;
  }
}

static inline void lpc24xx_gpio_write(unsigned index, bool value)
{
  if (value) {
    lpc24xx_gpio_set(index);
  } else {
    lpc24xx_gpio_clear(index);
  }
}

static inline bool lpc24xx_gpio_get(unsigned index)
{
  if (index <= LPC24XX_IO_INDEX_MAX) {
    unsigned port = LPC24XX_IO_PORT(index);
    unsigned bit = LPC24XX_IO_PORT_BIT(index);

    return (LPC24XX_FIO [port].pin & (1U << bit)) != 0;
  } else {
    return false;
  }
}

typedef enum {
  /**
   * @brief Sets the pin function.
   */
  LPC24XX_PIN_SET_FUNCTION,

  /**
   * @brief Checks if all pins are configured with the specified function.
   */
  LPC24XX_PIN_CHECK_FUNCTION,

  /**
   * @brief Configures the pins as input.
   */
  LPC24XX_PIN_SET_INPUT,

  /**
   * @brief Checks if all pins are configured as input.
   */
  LPC24XX_PIN_CHECK_INPUT
} lpc24xx_pin_action;

typedef union {
  struct {
    uint16_t port : 3;
    uint16_t port_bit : 5;
    uint16_t function : 3;
    uint16_t type : 4;
    uint16_t range : 1;
  } fields;
  uint16_t value;
} lpc24xx_pin_range;

typedef enum {
  LPC24XX_PIN_FUNCTION_00,
  LPC24XX_PIN_FUNCTION_01,
  LPC24XX_PIN_FUNCTION_10,
  LPC24XX_PIN_FUNCTION_11
} lpc24xx_pin_function;

typedef enum {
  LPC17XX_PIN_TYPE_DEFAULT,
  LPC17XX_PIN_TYPE_ADC,
  LPC17XX_PIN_TYPE_DAC,
  LPC17XX_PIN_TYPE_I2C,
  LPC17XX_PIN_TYPE_I2C_FAST_PLUS,
  LPC17XX_PIN_TYPE_OPEN_DRAIN
} lpc17xx_pin_type;

#ifdef ARM_MULTILIB_ARCH_V4
  #define LPC24XX_PIN(p, i, f0, f1) { { p, i, f0, 0, 0 } }
  #define LPC24XX_PIN_WITH_TYPE(p, i, f0, f1, t) { { p, i, f0, t, 0 } }
  #define LPC24XX_PIN_RANGE(p, i, j, f0, f1) \
    { { p, i, f0, 0, 0 } }, { { p, j, f0, 0, 1 } }
#else
  #define LPC24XX_PIN(p, i, f0, f1) { { p, i, f1, 0, 0 } }
  #define LPC24XX_PIN_WITH_TYPE(p, i, f0, f1, t) { { p, i, f1, t, 0 } }
  #define LPC24XX_PIN_RANGE(p, i, j, f0, f1) \
    { { p, i, f1, 0, 0 } }, { { p, j, f1, 0, 1 } }
#endif

#define LPC24XX_PIN_TERMINAL { { 0x7, 0x1f, 0x7, 0xf, 0x1 } }

/**
 * @brief Performs the @a action with the @a pins
 *
 * @code
 * #include <assert.h>
 * #include <bsp/io.h>
 * 
 * void example(void)
 * {
 *   static const lpc24xx_pin_range pins [] = {
 *     LPC24XX_PIN_I2S_RX_CLK_P0_4,
 *     LPC24XX_PIN_I2S_RX_WS_P0_5,
 *     LPC24XX_PIN_I2S_RX_SDA_P0_6,
 *     LPC24XX_PIN_I2S_TX_CLK_P0_7,
 *     LPC24XX_PIN_I2S_TX_WS_P0_8,
 *     LPC24XX_PIN_I2S_TX_SDA_P0_9,
 *     LPC24XX_PIN_TERMINAL
 *   };
 *   rtems_status_code sc = RTEMS_SUCCESSFUL;
 * 
 *   sc = lpc24xx_module_enable(LPC24XX_MODULE_I2S, LPC24XX_MODULE_CCLK_8);
 *   assert(sc == RTEMS_SUCCESSFUL);
 *   sc = lpc24xx_pin_config(&pins [0], LPC24XX_PIN_SET_FUNCTION);
 *   assert(sc == RTEMS_SUCCESSFUL);
 * }
 * @endcode
 *
 * @retval RTEMS_SUCCESSFUL Successful operation.
 * @retval RTEMS_IO_ERROR Check failed.
 * @retval RTEMS_NOT_DEFINED Invalid action.
 */
rtems_status_code lpc24xx_pin_config(
  const lpc24xx_pin_range *pins,
  lpc24xx_pin_action action
);

/**
 * @brief Returns the first pin index of a pin range.
 */
static inline unsigned lpc24xx_pin_get_first_index(
  const lpc24xx_pin_range *range
)
{
  return LPC24XX_IO_INDEX_BY_PORT(range->fields.port, range->fields.port_bit);
}

/**
 * @name ADC Pins
 *
 * @{
 */

#define LPC24XX_PIN_ADC_CHANNEL_0 \
  LPC24XX_PIN_WITH_TYPE(0, 23, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_1 \
  LPC24XX_PIN_WITH_TYPE(0, 24, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_2 \
  LPC24XX_PIN_WITH_TYPE(0, 25, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_3 \
  LPC24XX_PIN_WITH_TYPE(0, 26, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_4 \
  LPC24XX_PIN_WITH_TYPE(1, 30, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_5 \
  LPC24XX_PIN_WITH_TYPE(1, 31, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_6 \
  LPC24XX_PIN_WITH_TYPE(0, 12, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_ADC)
#define LPC24XX_PIN_ADC_CHANNEL_7 \
  LPC24XX_PIN_WITH_TYPE(0, 13, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_ADC)

/** @} */

/**
 * @name CAN 0 Pins
 *
 * @{
 */

#define LPC24XX_PIN_CAN_0_RD_P0_0 \
  LPC24XX_PIN(0, 0, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_CAN_0_RD_P0_21 \
  LPC24XX_PIN(0, 21, LPC24XX_PIN_FUNCTION_11, 4)

#define LPC24XX_PIN_CAN_0_TD_P0_1 \
  LPC24XX_PIN(0, 1, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_CAN_0_TD_P0_22 \
  LPC24XX_PIN(0, 22, LPC24XX_PIN_FUNCTION_11, 4)

/** @} */

/**
 * @name CAN 1 Pins
 *
 * @{
 */

#define LPC24XX_PIN_CAN_1_RD_P0_4 \
  LPC24XX_PIN(0, 4, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_CAN_1_RD_P2_7 \
  LPC24XX_PIN(2, 7, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_CAN_1_TD_P0_5 \
  LPC24XX_PIN(0, 5, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_CAN_1_TD_P2_8 \
  LPC24XX_PIN(2, 8, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/**
 * @name DAC Pins
 *
 * @{
 */

#define LPC24XX_PIN_DAC \
  LPC24XX_PIN_WITH_TYPE(0, 26, LPC24XX_PIN_FUNCTION_10, 2, LPC17XX_PIN_TYPE_DAC)

/** @} */

/**
 * @name Ethernet Pins
 *
 * @{
 */

#define LPC24XX_PIN_ETHERNET_MII \
  LPC24XX_PIN_RANGE(1, 0, 17, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_ETHERNET_RMII_0 \
  LPC24XX_PIN_RANGE(1, 0, 1, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_ETHERNET_RMII_1 \
  LPC24XX_PIN(1, 4, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_ETHERNET_RMII_2 \
  LPC24XX_PIN_RANGE(1, 8, 10, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_ETHERNET_RMII_3 \
  LPC24XX_PIN_RANGE(1, 14, 17, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/**
 * @name External Interrupt Pins
 *
 * @{
 */

#define LPC24XX_PIN_EINT_0 \
  LPC24XX_PIN(2, 10, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EINT_1 \
  LPC24XX_PIN(2, 11, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EINT_2 \
  LPC24XX_PIN(2, 12, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EINT_3 \
  LPC24XX_PIN(2, 13, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/**
 * @name External Memory Controller (EMC) Pins
 *
 * @{
 */

#define LPC24XX_PIN_EMC_CS_0 \
  LPC24XX_PIN(4, 30, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CS_1 \
  LPC24XX_PIN(4, 31, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CS_2 \
  LPC24XX_PIN(2, 14, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CS_3 \
  LPC24XX_PIN(2, 15, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_DYCS_0 \
  LPC24XX_PIN(2, 20, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_DYCS_1 \
  LPC24XX_PIN(2, 21, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_DYCS_2 \
  LPC24XX_PIN(2, 22, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_DYCS_3 \
  LPC24XX_PIN(2, 23, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_OE \
  LPC24XX_PIN(4, 24, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_WE \
  LPC24XX_PIN(4, 25, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CAS \
  LPC24XX_PIN(2, 16, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_RAS \
  LPC24XX_PIN(2, 17, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_CLK_0 \
  LPC24XX_PIN(2, 18, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CLK_1 \
  LPC24XX_PIN(2, 19, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_CKE_0 \
  LPC24XX_PIN(2, 24, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CKE_1 \
  LPC24XX_PIN(2, 25, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CKE_2 \
  LPC24XX_PIN(2, 26, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_CKE_3 \
  LPC24XX_PIN(2, 27, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_DQM_0 \
  LPC24XX_PIN(2, 28, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_DQM_1 \
  LPC24XX_PIN(2, 29, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_DQM_2 \
  LPC24XX_PIN(2, 30, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_DQM_3 \
  LPC24XX_PIN(2, 31, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_BLS0 \
  LPC24XX_PIN(4, 26, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_BLS1 \
  LPC24XX_PIN(4, 27, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_BLS2 \
  LPC24XX_PIN(4, 28, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_BLS3 \
  LPC24XX_PIN(4, 29, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_D_0_15 \
  LPC24XX_PIN_RANGE(3, 0, 15, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_D_15_31 \
  LPC24XX_PIN_RANGE(3, 15, 31, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_D_0_31 \
  LPC24XX_PIN_RANGE(3, 0, 31, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_EMC_A_0_12 \
  LPC24XX_PIN_RANGE(4, 0, 12, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_13 \
  LPC24XX_PIN_RANGE(4, 0, 13, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_14 \
  LPC24XX_PIN_RANGE(4, 0, 14, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_15 \
  LPC24XX_PIN_RANGE(4, 0, 15, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_16 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN(4, 16, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_17 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 17, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_18 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 18, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_19 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 19, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_20 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 20, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_21 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 21, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_22 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 22, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_23 \
  LPC24XX_PIN_EMC_A_0_15, \
  LPC24XX_PIN_RANGE(4, 16, 23, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_24 \
  LPC24XX_PIN_EMC_A_0_23, \
  LPC24XX_PIN(5, 24, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_EMC_A_0_25 \
  LPC24XX_PIN_EMC_A_0_23, \
  LPC24XX_PIN_RANGE(5, 24, 25, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/**
 * @name I2C 0 Pins
 *
 * @{
 */

#define LPC24XX_PIN_I2C_0_SDA \
  LPC24XX_PIN_WITH_TYPE(0, 27, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_0_SCL \
  LPC24XX_PIN_WITH_TYPE(0, 28, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_I2C)

/** @} */

/**
 * @name I2C 1 Pins
 *
 * @{
 */

#define LPC24XX_PIN_I2C_1_SDA_P0_0 \
  LPC24XX_PIN_WITH_TYPE(0, 0, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_1_SDA_P0_19 \
  LPC24XX_PIN_WITH_TYPE(0, 19, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_1_SDA_P2_14 \
  LPC24XX_PIN_WITH_TYPE(2, 14, LPC24XX_PIN_FUNCTION_11, 2, LPC17XX_PIN_TYPE_I2C)

#define LPC24XX_PIN_I2C_1_SCL_P0_1 \
  LPC24XX_PIN_WITH_TYPE(0, 1, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_1_SCL_P0_20 \
  LPC24XX_PIN_WITH_TYPE(0, 20, LPC24XX_PIN_FUNCTION_11, 3, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_1_SCL_P2_15 \
  LPC24XX_PIN_WITH_TYPE(2, 15, LPC24XX_PIN_FUNCTION_11, 2, LPC17XX_PIN_TYPE_I2C)

/** @} */

/**
 * @name I2C 2 Pins
 *
 * @{
 */

#define LPC24XX_PIN_I2C_2_SDA_P0_10 \
  LPC24XX_PIN_WITH_TYPE(0, 10, LPC24XX_PIN_FUNCTION_10, 2, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_2_SDA_P2_30 \
  LPC24XX_PIN_WITH_TYPE(2, 30, LPC24XX_PIN_FUNCTION_11, 2, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_2_SDA_P4_20 \
  LPC24XX_PIN_WITH_TYPE(4, 20, LPC24XX_PIN_FUNCTION_10, 2, LPC17XX_PIN_TYPE_I2C)

#define LPC24XX_PIN_I2C_2_SCL_P0_11 \
  LPC24XX_PIN_WITH_TYPE(0, 11, LPC24XX_PIN_FUNCTION_10, 2, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_2_SCL_P2_31 \
  LPC24XX_PIN_WITH_TYPE(2, 31, LPC24XX_PIN_FUNCTION_11, 2, LPC17XX_PIN_TYPE_I2C)
#define LPC24XX_PIN_I2C_2_SCL_P4_21 \
  LPC24XX_PIN_WITH_TYPE(4, 21, LPC24XX_PIN_FUNCTION_10, 2, LPC17XX_PIN_TYPE_I2C)

/** @} */

/**
 * @name I2S Pins
 *
 * @{
 */

#define LPC24XX_PIN_I2S_RX_CLK_P0_4 \
  LPC24XX_PIN(0, 4, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_I2S_RX_CLK_P0_23 \
  LPC24XX_PIN(0, 23, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_I2S_RX_WS_P0_5 \
  LPC24XX_PIN(0, 5, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_I2S_RX_WS_P0_24 \
  LPC24XX_PIN(0, 24, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_I2S_RX_SDA_P0_6 \
  LPC24XX_PIN(0, 6, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_I2S_RX_SDA_P0_25 \
  LPC24XX_PIN(0, 25, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_I2S_TX_CLK_P0_7 \
  LPC24XX_PIN(0, 7, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_I2S_TX_CLK_P2_11 \
  LPC24XX_PIN(2, 11, LPC24XX_PIN_FUNCTION_11, 3)

#define LPC24XX_PIN_I2S_TX_WS_P0_8 \
  LPC24XX_PIN(0, 8, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_I2S_TX_WS_P2_12 \
  LPC24XX_PIN(2, 12, LPC24XX_PIN_FUNCTION_11, 3)

#define LPC24XX_PIN_I2S_TX_SDA_P0_9 \
  LPC24XX_PIN(0, 9, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_I2S_TX_SDA_P2_13 \
  LPC24XX_PIN(2, 13, LPC24XX_PIN_FUNCTION_11, 3)

/** @} */

/**
 * @name LCD Pins
 *
 * @{
 */

#define LPC24XX_PIN_LCD_PWR \
  LPC24XX_PIN(2, 0, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_LE \
  LPC24XX_PIN(2, 1, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_DCLK \
  LPC24XX_PIN(2, 2, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_FP \
  LPC24XX_PIN(2, 3, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_ENAB_M \
  LPC24XX_PIN(2, 4, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_LP \
  LPC24XX_PIN(2, 5, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_CLKIN \
  LPC24XX_PIN(2, 11, LPC24XX_PIN_FUNCTION_01, 7)

#define LPC24XX_PIN_LCD_VD_0_P0_4 \
  LPC24XX_PIN(0, 4, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_0_P2_6 \
  LPC24XX_PIN(2, 6, LPC24XX_PIN_FUNCTION_11, 6)
#define LPC24XX_PIN_LCD_VD_1_P0_5 \
  LPC24XX_PIN(0, 5, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_1_P2_7 \
  LPC24XX_PIN(2, 7, LPC24XX_PIN_FUNCTION_11, 6)
#define LPC24XX_PIN_LCD_VD_2_P2_8 \
  LPC24XX_PIN(2, 8, LPC24XX_PIN_FUNCTION_11, 6)
#define LPC24XX_PIN_LCD_VD_2_P4_28 \
  LPC24XX_PIN(4, 28, LPC24XX_PIN_FUNCTION_10, 7)
#define LPC24XX_PIN_LCD_VD_3_P2_9 \
  LPC24XX_PIN(2, 9, LPC24XX_PIN_FUNCTION_11, 6)
#define LPC24XX_PIN_LCD_VD_3_P2_12 \
  LPC24XX_PIN(2, 12, LPC24XX_PIN_FUNCTION_01, 5)
#define LPC24XX_PIN_LCD_VD_3_P4_29 \
  LPC24XX_PIN(4, 29, LPC24XX_PIN_FUNCTION_10, 7)
#define LPC24XX_PIN_LCD_VD_4_P2_6 \
  LPC24XX_PIN(2, 6, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_VD_4_P2_12 \
  LPC24XX_PIN(2, 12, LPC24XX_PIN_FUNCTION_01, 4)
#define LPC24XX_PIN_LCD_VD_5_P2_7 \
  LPC24XX_PIN(2, 7, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_VD_5_P2_13 \
  LPC24XX_PIN(2, 13, LPC24XX_PIN_FUNCTION_01, 5)
#define LPC24XX_PIN_LCD_VD_6_P1_20 \
  LPC24XX_PIN(1, 20, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_6_P2_8 \
  LPC24XX_PIN(2, 8, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_VD_6_P4_28 \
  LPC24XX_PIN(4, 28, LPC24XX_PIN_FUNCTION_10, 5)
#define LPC24XX_PIN_LCD_VD_7_P1_21 \
  LPC24XX_PIN(1, 21, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_7_P2_9 \
  LPC24XX_PIN(2, 9, LPC24XX_PIN_FUNCTION_11, 7)
#define LPC24XX_PIN_LCD_VD_7_P4_29 \
  LPC24XX_PIN(4, 29, LPC24XX_PIN_FUNCTION_10, 5)
#define LPC24XX_PIN_LCD_VD_8_P0_6 \
  LPC24XX_PIN(0, 6, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_8_P1_22 \
  LPC24XX_PIN(1, 22, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_8_P2_12 \
  LPC24XX_PIN(2, 12, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_9_P0_7 \
  LPC24XX_PIN(0, 7, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_9_P1_23 \
  LPC24XX_PIN(1, 23, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_9_P2_13 \
  LPC24XX_PIN(2, 13, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_10_P1_20 \
  LPC24XX_PIN(1, 20, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_10_P1_24 \
  LPC24XX_PIN(1, 24, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_10_P4_28 \
  LPC24XX_PIN(4, 28, LPC24XX_PIN_FUNCTION_10, 6)
#define LPC24XX_PIN_LCD_VD_11_P1_21 \
  LPC24XX_PIN(1, 21, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_11_P1_25 \
  LPC24XX_PIN(1, 25, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_11_P4_29 \
  LPC24XX_PIN(4, 29, LPC24XX_PIN_FUNCTION_10, 6)
#define LPC24XX_PIN_LCD_VD_12_P1_22 \
  LPC24XX_PIN(1, 22, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_12_P1_26 \
  LPC24XX_PIN(1, 26, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_13_P1_23 \
  LPC24XX_PIN(1, 23, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_13_P1_27 \
  LPC24XX_PIN(1, 27, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_14_P1_24 \
  LPC24XX_PIN(1, 24, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_14_P1_28 \
  LPC24XX_PIN(1, 28, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_15_P1_25 \
  LPC24XX_PIN(1, 25, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_15_P1_29 \
  LPC24XX_PIN(1, 29, LPC24XX_PIN_FUNCTION_01, 6)
#define LPC24XX_PIN_LCD_VD_16_P0_8 \
  LPC24XX_PIN(0, 8, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_17_P0_9 \
  LPC24XX_PIN(0, 9, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_18_P2_12 \
  LPC24XX_PIN(2, 12, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_19_P2_13 \
  LPC24XX_PIN(2, 13, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_20_P1_26 \
  LPC24XX_PIN(1, 26, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_21_P1_27 \
  LPC24XX_PIN(1, 27, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_22_P1_28 \
  LPC24XX_PIN(1, 28, LPC24XX_PIN_FUNCTION_01, 7)
#define LPC24XX_PIN_LCD_VD_23_P1_29 \
  LPC24XX_PIN(1, 29, LPC24XX_PIN_FUNCTION_01, 7)

/** @} */

/**
 * @name PWM 0 Pins
 *
 * @{
 */

#define LPC24XX_PIN_PWM_0_CHANNEL_1_P1_2 \
  LPC24XX_PIN(1, 2, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CHANNEL_1_P3_16 \
  LPC24XX_PIN(3, 16, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_PWM_0_CHANNEL_2_P1_3 \
  LPC24XX_PIN(1, 3, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CHANNEL_2_P3_17 \
  LPC24XX_PIN(3, 17, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_PWM_0_CHANNEL_3_P1_5 \
  LPC24XX_PIN(1, 5, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CHANNEL_3_P3_18 \
  LPC24XX_PIN(3, 18, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_PWM_0_CHANNEL_4_P1_6 \
  LPC24XX_PIN(1, 6, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CHANNEL_4_P3_19 \
  LPC24XX_PIN(3, 19, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_PWM_0_CHANNEL_5_P1_7 \
  LPC24XX_PIN(1, 7, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CHANNEL_5_P3_20 \
  LPC24XX_PIN(3, 20, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_PWM_0_CHANNEL_6_P1_11 \
  LPC24XX_PIN(1, 11, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CHANNEL_6_P3_21 \
  LPC24XX_PIN(3, 21, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_PWM_0_CAPTURE_0_P1_12 \
  LPC24XX_PIN(1, 12, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_PWM_0_CAPTURE_0_P3_22 \
  LPC24XX_PIN(3, 22, LPC24XX_PIN_FUNCTION_10, 2)

/** @} */

/**
 * @name PWM 1 Pins
 *
 * @{
 */

#define LPC24XX_PIN_PWM_1_CHANNEL_1_P1_18 \
  LPC24XX_PIN(1, 18, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CHANNEL_1_P2_0 \
  LPC24XX_PIN(2, 0, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CHANNEL_1_P3_24 \
  LPC24XX_PIN(3, 24, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_PWM_1_CHANNEL_2_P1_20 \
  LPC24XX_PIN(1, 20, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CHANNEL_2_P2_1 \
  LPC24XX_PIN(2, 1, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CHANNEL_2_P3_25 \
  LPC24XX_PIN(3, 25, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_PWM_1_CHANNEL_3_P1_21 \
  LPC24XX_PIN(1, 21, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CHANNEL_3_P2_2 \
  LPC24XX_PIN(2, 2, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CHANNEL_3_P3_26 \
  LPC24XX_PIN(3, 26, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_PWM_1_CHANNEL_4_P1_23 \
  LPC24XX_PIN(1, 23, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CHANNEL_4_P2_3 \
  LPC24XX_PIN(2, 3, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CHANNEL_4_P3_27 \
  LPC24XX_PIN(3, 27, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_PWM_1_CHANNEL_5_P1_24 \
  LPC24XX_PIN(1, 24, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CHANNEL_5_P2_4 \
  LPC24XX_PIN(2, 4, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CHANNEL_5_P3_28 \
  LPC24XX_PIN(3, 28, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_PWM_1_CHANNEL_6_P1_26 \
  LPC24XX_PIN(1, 26, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CHANNEL_6_P2_5 \
  LPC24XX_PIN(2, 5, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CHANNEL_6_P3_29 \
  LPC24XX_PIN(3, 29, LPC24XX_PIN_FUNCTIO9_11, 2)

#define LPC24XX_PIN_PWM_1_CAPTURE_0_P1_28 \
  LPC24XX_PIN(1, 28, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_PWM_1_CAPTURE_0_P2_7 \
  LPC24XX_PIN(2, 6, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_PWM_1_CAPTURE_0_P3_23 \
  LPC24XX_PIN(3, 23, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_PWM_1_CAPTURE_1_P1_29 \
  LPC24XX_PIN(1, 29, LPC24XX_PIN_FUNCTION_10, 2)

/** @} */

#ifdef ARM_MULTILIB_ARCH_V4

/**
 * @name SPI Pins
 *
 * @{
 */

#define LPC24XX_PIN_SPI_SCK \
  LPC24XX_PIN(0, 15, LPC24XX_PIN_FUNCTION_11)
#define LPC24XX_PIN_SPI_SSEL \
  LPC24XX_PIN(0, 16, LPC24XX_PIN_FUNCTION_11)
#define LPC24XX_PIN_SPI_MISO \
  LPC24XX_PIN(0, 17, LPC24XX_PIN_FUNCTION_11)
#define LPC24XX_PIN_SPI_MOSI \
  LPC24XX_PIN(0, 18, LPC24XX_PIN_FUNCTION_11)

/** @} */

#endif /* ARM_MULTILIB_ARCH_V4 */

/**
 * @name SSP 0 Pins
 *
 * @{
 */

#define LPC24XX_PIN_SSP_0_SCK_P0_15 \
  LPC24XX_PIN(0, 15, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_0_SCK_P1_20 \
  LPC24XX_PIN(1, 20, LPC24XX_PIN_FUNCTION_11, 5)
#define LPC24XX_PIN_SSP_0_SCK_P2_22 \
  LPC24XX_PIN(2, 22, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_SSP_0_SSEL_P0_16 \
  LPC24XX_PIN(0, 16, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_0_SSEL_P1_21 \
  LPC24XX_PIN(1, 21, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_SSP_0_SSEL_P2_23 \
  LPC24XX_PIN(2, 23, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_SSP_0_MISO_P0_17 \
  LPC24XX_PIN(0, 17, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_0_MISO_P1_23 \
  LPC24XX_PIN(1, 23, LPC24XX_PIN_FUNCTION_11, 5)
#define LPC24XX_PIN_SSP_0_MISO_P2_26 \
  LPC24XX_PIN(2, 26, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_SSP_0_MOSI_P0_18 \
  LPC24XX_PIN(0, 18, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_0_MOSI_P1_24 \
  LPC24XX_PIN(1, 24, LPC24XX_PIN_FUNCTION_11, 5)
#define LPC24XX_PIN_SSP_0_MOSI_P2_27 \
  LPC24XX_PIN(2, 27, LPC24XX_PIN_FUNCTION_11, 2)

/** @} */

/**
 * @name SSP 1 Pins
 *
 * @{
 */

#define LPC24XX_PIN_SSP_1_SCK_P0_6 \
  LPC24XX_PIN(0, 7, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_SCK_P0_12 \
  LPC24XX_PIN(1, 31, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_SCK_P4_20 \
  LPC24XX_PIN(4, 20, LPC24XX_PIN_FUNCTION_11, 3)

#define LPC24XX_PIN_SSP_1_SSEL_P0_7 \
  LPC24XX_PIN(0, 6, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_SSEL_P0_13 \
  LPC24XX_PIN(0, 14, LPC24XX_PIN_FUNCTION_11, 2)
#define LPC24XX_PIN_SSP_1_SSEL_P4_21 \
  LPC24XX_PIN(4, 21, LPC24XX_PIN_FUNCTION_11, 3)

#define LPC24XX_PIN_SSP_1_MISO_P0_8 \
  LPC24XX_PIN(0, 8, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_MISO_P0_14 \
  LPC24XX_PIN(0, 12, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_MISO_P4_22 \
  LPC24XX_PIN(4, 22, LPC24XX_PIN_FUNCTION_11, 3)

#define LPC24XX_PIN_SSP_1_MOSI_P0_9 \
  LPC24XX_PIN(0, 9, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_MOSI_P1_31 \
  LPC24XX_PIN(0, 13, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_SSP_1_MOSI_P4_23 \
  LPC24XX_PIN(4, 23, LPC24XX_PIN_FUNCTION_11, 3)

/** @} */

#ifdef ARM_MULTILIB_ARCH_V7M

/**
 * @name SSP 2 Pins
 *
 * @{
 */

#define LPC24XX_PIN_SSP_2_SCK_P1_0 \
  LPC24XX_PIN(1, 0, LPC24XX_PIN_FUNCTION_00, 4)

#define LPC24XX_PIN_SSP_2_SSEL_P1_8 \
  LPC24XX_PIN(1, 8, LPC24XX_PIN_FUNCTION_00, 4)

#define LPC24XX_PIN_SSP_2_MISO_P1_4 \
  LPC24XX_PIN(1, 4, LPC24XX_PIN_FUNCTION_00, 4)

#define LPC24XX_PIN_SSP_2_MOSI_P1_1 \
  LPC24XX_PIN(1, 1, LPC24XX_PIN_FUNCTION_00, 4)

/** @} */

#endif /* ARM_MULTILIB_ARCH_V7M */

/**
 * @name UART 0 Pins
 *
 * @{
 */

#define LPC24XX_PIN_UART_0_TXD \
  LPC24XX_PIN(0, 2, LPC24XX_PIN_FUNCTION_01, 1)

#define LPC24XX_PIN_UART_0_RXD \
  LPC24XX_PIN(0, 3, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/**
 * @name UART 1 Pins
 *
 * @{
 */

#define LPC24XX_PIN_UART_1_TXD_P0_15 \
  LPC24XX_PIN(0, 15, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_UART_1_TXD_P2_0 \
  LPC24XX_PIN(2, 0, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_UART_1_TXD_P3_16 \
  LPC24XX_PIN(3, 16, LPC24XX_PIN_FUNCTION_11, 3)

#define LPC24XX_PIN_UART_1_RXD_P0_16 \
  LPC24XX_PIN(0, 16, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_UART_1_RXD_P2_1 \
  LPC24XX_PIN(2, 1, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_UART_1_RXD_P3_17 \
  LPC24XX_PIN(3, 17, LPC24XX_PIN_FUNCTION_11, 3)

/** @} */

/**
 * @name UART 2 Pins
 *
 * @{
 */

#define LPC24XX_PIN_UART_2_TXD_P0_10 \
  LPC24XX_PIN(0, 10, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_UART_2_TXD_P2_8 \
  LPC24XX_PIN(2, 8, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_UART_2_TXD_P4_22 \
  LPC24XX_PIN(4, 22, LPC24XX_PIN_FUNCTION_10, 2)

#define LPC24XX_PIN_UART_2_RXD_P0_11 \
  LPC24XX_PIN(0, 11, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_UART_2_RXD_P2_9 \
  LPC24XX_PIN(2, 9, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_UART_2_RXD_P4_23 \
  LPC24XX_PIN(4, 23, LPC24XX_PIN_FUNCTION_10, 2)

/** @} */

/**
 * @name UART 3 Pins
 *
 * @{
 */

#define LPC24XX_PIN_UART_3_TXD_P0_0 \
  LPC24XX_PIN(0, 0, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_UART_3_TXD_P0_25 \
  LPC24XX_PIN(0, 25, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_UART_3_TXD_P4_28 \
  LPC24XX_PIN(4, 28, LPC24XX_PIN_FUNCTION_11, 2)

#define LPC24XX_PIN_UART_3_RXD_P0_1 \
  LPC24XX_PIN(0, 1, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_UART_3_RXD_P0_26 \
  LPC24XX_PIN(0, 26, LPC24XX_PIN_FUNCTION_11, 3)
#define LPC24XX_PIN_UART_3_RXD_P4_29 \
  LPC24XX_PIN(4, 29, LPC24XX_PIN_FUNCTION_11, 2)

/** @} */

#ifdef ARM_MULTILIB_ARCH_V7M

/**
 * @name UART 4 Pins
 *
 * @{
 */

#define LPC24XX_PIN_UART_4_TXD_P0_22 \
  LPC24XX_PIN(0, 22, LPC24XX_PIN_FUNCTION_00, 3)
#define LPC24XX_PIN_UART_4_TXD_P1_29 \
  LPC24XX_PIN(1, 29, LPC24XX_PIN_FUNCTION_00, 5)
#define LPC24XX_PIN_UART_4_TXD_P5_4 \
  LPC24XX_PIN(5, 4, LPC24XX_PIN_FUNCTION_00, 4)

#define LPC24XX_PIN_UART_4_RXD_P2_9 \
  LPC24XX_PIN(2, 9, LPC24XX_PIN_FUNCTION_00, 3)
#define LPC24XX_PIN_UART_4_RXD_P5_3 \
  LPC24XX_PIN(5, 3, LPC24XX_PIN_FUNCTION_00, 4)

#define LPC24XX_PIN_UART_4_OE_P0_21 \
  LPC24XX_PIN(0, 21, LPC24XX_PIN_FUNCTION_00, 3)

#define LPC24XX_PIN_UART_4_SCLK_P0_21 \
  LPC24XX_PIN(0, 21, LPC24XX_PIN_FUNCTION_00, 5)

#endif /* ARM_MULTILIB_ARCH_V7M */

/** @} */

/**
 * @name USB Port 1 Pins
 *
 * @{
 */

#define LPC24XX_PIN_USB_D_PLUS_1\
  LPC24XX_PIN(0, 29, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_D_MINUS_1\
  LPC24XX_PIN(0, 30, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_UP_LED_1\
  LPC24XX_PIN(1, 18, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_TX_E_1\
  LPC24XX_PIN(1, 19, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_PPWR_1\
  LPC24XX_PIN(1, 19, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_USB_TX_DP_1\
  LPC24XX_PIN(1, 20, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_TX_DM_1\
  LPC24XX_PIN(1, 21, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_RCV_1\
  LPC24XX_PIN(1, 22, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_PWRD_1\
  LPC24XX_PIN(1, 22, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_USB_RX_DP_1\
  LPC24XX_PIN(1, 23, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_RX_DM_1\
  LPC24XX_PIN(1, 24, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_LS_1\
  LPC24XX_PIN(1, 25, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_HSTEN_1\
  LPC24XX_PIN(1, 25, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_USB_SSPND_1\
  LPC24XX_PIN(1, 26, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_INT_1\
  LPC24XX_PIN(1, 27, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_OVRCR_1\
  LPC24XX_PIN(1, 27, LPC24XX_PIN_FUNCTION_10, 2)
#define LPC24XX_PIN_USB_SCL_1\
  LPC24XX_PIN(1, 28, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_SDA_1 \
  LPC24XX_PIN_WITH_TYPE( \
    1, 29, LPC24XX_PIN_FUNCTION_01, 1, LPC17XX_PIN_TYPE_OPEN_DRAIN \
  )
#define LPC24XX_PIN_USB_CONNECT_1\
  LPC24XX_PIN(2, 9, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/**
 * @name USB Port 2 Pins
 *
 * @{
 */

#define LPC24XX_PIN_USB_PPWR_2\
  LPC24XX_PIN(0, 12, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_UP_LED_2\
  LPC24XX_PIN(0, 13, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_HSTEN_2\
  LPC24XX_PIN(0, 14, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_CONNECT_2\
  LPC24XX_PIN(0, 14, LPC24XX_PIN_FUNCTION_01, 3)
#define LPC24XX_PIN_USB_D_PLUS_2\
  LPC24XX_PIN(0, 31, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_PWRD_2\
  LPC24XX_PIN(1, 30, LPC24XX_PIN_FUNCTION_01, 1)
#define LPC24XX_PIN_USB_OVRCR_2\
  LPC24XX_PIN(1, 31, LPC24XX_PIN_FUNCTION_01, 1)

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_LPC24XX_IO_H */
