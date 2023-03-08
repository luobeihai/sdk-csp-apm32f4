/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-08     luobeihai    first version
 */

#include <rtthread.h>
#include "board.h"
#include "drv_common.h"
#include "apm32_msp.h"

/**
 * @brief apm32 spi gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the pins according to the specific hardware board.
 */
void apm32_msp_spi_init(void *Instance)
{
#ifdef BSP_USING_SPI1
    GPIO_Config_T gpioConfig;
    SPI_T *spi_x = (SPI_T *)Instance;

    if(spi_x == SPI1)
    {
        /* Enable related Clock */
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

        /* Config SPI1 PinAF */
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_3, GPIO_AF_SPI1);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_4, GPIO_AF_SPI1);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_5, GPIO_AF_SPI1);

        /* Config SPI GPIO, SCK=PB3, MISO=PB4, MOSI=PB5 */
        GPIO_ConfigStructInit(&gpioConfig);
        gpioConfig.pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
        gpioConfig.speed = GPIO_SPEED_100MHz;
        gpioConfig.mode = GPIO_MODE_AF;
        gpioConfig.otype = GPIO_OTYPE_PP;
        gpioConfig.pupd = GPIO_PUPD_NOPULL;
        GPIO_Config(GPIOB, &gpioConfig);
    }
#endif
}

/**
 * @brief apm32 timer gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the pins according to the specific hardware board.
 */
void apm32_msp_timer_init(void *Instance)
{
#ifdef BSP_USING_PWM3
    GPIO_Config_T gpio_config;
    TMR_T *tmr_x = (TMR_T *)Instance;

    if (tmr_x == TMR3)
    {
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC);
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

        /* TMR3 channel 1 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_6, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_6;
        gpio_config.mode = GPIO_MODE_AF;
        gpio_config.otype = GPIO_OTYPE_PP;
        gpio_config.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 2 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_7, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_7;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 3 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_8, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_8;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 4 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_9, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_9;
        GPIO_Config(GPIOC, &gpio_config);
    }
#endif
}

/**
 * @brief apm32 eth gpio init
 *
 * @note This function is only used as an example, please initialize
 *       the pins according to the specific hardware board.
 */
void apm32_msp_eth_init(void *Instance)
{
#ifdef BSP_USING_ETH
    GPIO_Config_T GPIO_ConfigStruct;

    /* Enable SYSCFG clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* Enable GPIOs clocks */
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA | RCM_AHB1_PERIPH_GPIOC | RCM_AHB1_PERIPH_GPIOG);

    /* MII/RMII Media interface selection */
    SYSCFG_ConfigMediaInterface(SYSCFG_INTERFACE_RMII);

    /*********************** Ethernet pins configuration ***************************/
    /*
        ETH_MDIO -------------------------> PA2
        ETH_MDC --------------------------> PC1
        ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1
        ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PA7
        ETH_MII_RXD0/ETH_RMII_RXD0 -------> PC4
        ETH_MII_RXD1/ETH_RMII_RXD1 -------> PC5
        ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PG11
        ETH_MII_TXD0/ETH_RMII_TXD0 -------> PG13
        ETH_MII_TXD1/ETH_RMII_TXD1 -------> PG14
    */
    /* Configure PC1, PC4 and PC5 */
    GPIO_ConfigStruct.pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_ConfigStruct.speed = GPIO_SPEED_100MHz;
    GPIO_ConfigStruct.mode  = GPIO_MODE_AF;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.pupd  = GPIO_PUPD_NOPULL;

    GPIO_Config(GPIOC, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_1, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_4, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_5, GPIO_AF_ETH);

    /* Configure PG11, PG13 and PG14 */
    GPIO_ConfigStruct.pin =  GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14;
    GPIO_Config(GPIOG, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOG, GPIO_PIN_SOURCE_11, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOG, GPIO_PIN_SOURCE_13, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOG, GPIO_PIN_SOURCE_14, GPIO_AF_ETH);

    /* Configure PA1, PA2 and PA7 */
    GPIO_ConfigStruct.pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_1, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_2, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_ETH);
#endif
}
