/**
 *******************************************************************************
 * @file  ev_hc32m423_lqfp64.c
 * @brief This file provides firmware functions for EV_HC32M423_LQFP64 BSP
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-01       Zhangxl         First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2016, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software is owned and published by:
 * Huada Semiconductor Co., Ltd. ("HDSC").
 *
 * BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
 * BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
 *
 * This software contains source code for use with HDSC
 * components. This software is licensed by HDSC to be adapted only
 * for use in systems utilizing HDSC components. HDSC shall not be
 * responsible for misuse or illegal use of this software for devices not
 * supported herein. HDSC is providing this software "AS IS" and will
 * not be responsible for issues arising from incorrect user implementation
 * of the software.
 *
 * Disclaimer:
 * HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
 * REGARDING THE SOFTWARE (INCLUDING ANY ACCOMPANYING WRITTEN MATERIALS),
 * ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
 * WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
 * WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
 * WARRANTY OF NONINFRINGEMENT.
 * HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
 * NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
 * LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
 * LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
 * INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
 * SAVINGS OR PROFITS,
 * EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
 * INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
 * FROM, THE SOFTWARE.
 *
 * This software may be replicated in part or whole for the licensed use,
 * with the restriction that this Disclaimer and Copyright notice must be
 * included with each copy of this software, whether used in part or whole,
 * at all times.
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ev_hc32m423_lqfp64.h"

/**
 * @defgroup BSP BSP
 * @{
 */

/**
 * @defgroup EV_HC32M423_LQFP64 HC32M423_LQFP64_EVB
 * @{
 */

#if (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_Local_Macros EV_HC32M423_LQFP64 Local Macros
 * @{
 */

/** @defgroup EV_HC32M423_LQFP64_LED_PortPin_Sel EV_HC32M423_LQFP64 LED port/pin definition
 * @{
 */
#define LED_RED_PORT            (GPIO_PORT_A)
#define LED_RED_PIN             (GPIO_PIN_4)
#define LED_GREEN_PORT          (GPIO_PORT_A)
#define LED_GREEN_PIN           (GPIO_PIN_5)
#define LED_BLUE_PORT           (GPIO_PORT_1)
#define LED_BLUE_PIN            (GPIO_PIN_0)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup EV_HC32M423_LQFP64_Global_Functions EV_HC32M423_LQFP64 Global Functions
 * @{
 */

/**
 * @brief  LED initialize.
 * @param  None
 * @retval none
 */
void BSP_LED_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* Turn off LEDs*/
    BSP_LED_Off(LED_RED | LED_GREEN | LED_BLUE);

    /* Initilize GPIO structure */
    GPIO_StructInit(&stcGpioInit);

    /* Initialize RGB LED pin */
    GPIO_Init(LED_RED_PORT, LED_RED_PIN, &stcGpioInit);
    GPIO_Init(LED_GREEN_PORT, LED_GREEN_PIN, &stcGpioInit);
    GPIO_Init(LED_BLUE_PORT, LED_BLUE_PIN, &stcGpioInit);
}

/**
 * @brief  Turn on LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_GREEN
 *   @arg  LED_BLUE
 * @retval none
 */
void BSP_LED_On(uint8_t u8Led)
{
    if (u8Led & LED_RED == LED_RED)
    {
        GPIO_ResetPins(LED_RED_PORT, LED_RED_PIN);
    }

    if (u8Led & LED_GREEN == LED_GREEN)
    {
        GPIO_ResetPins(LED_GREEN_PORT, LED_GREEN_PIN);
    }

    if (u8Led & LED_BLUE == LED_BLUE)
    {
        GPIO_ResetPins(LED_BLUE_PORT, LED_BLUE_PIN);
    }
}

/**
 * @brief  Turn off LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_GREEN
 *   @arg  LED_BLUE
 * @retval none
 */
void BSP_LED_Off(uint8_t u8Led)
{
    if (u8Led & LED_RED == LED_RED)
    {
        GPIO_SetPins(LED_RED_PORT, LED_RED_PIN);
    }

    if (u8Led & LED_GREEN == LED_GREEN)
    {
        GPIO_SetPins(LED_GREEN_PORT, LED_GREEN_PIN);
    }

    if (u8Led & LED_BLUE == LED_BLUE)
    {
        GPIO_SetPins(LED_BLUE_PORT, LED_BLUE_PIN);
    }
}

/**
 * @brief  Toggle LEDs.
 * @param  [in] u8Led LED
 *   @arg  LED_RED
 *   @arg  LED_GREEN
 *   @arg  LED_BLUE
 * @retval none
 */
void BSP_LED_Toggle(uint8_t u8Led)
{
    if (u8Led & LED_RED == LED_RED)
    {
        GPIO_TogglePins(LED_RED_PORT, LED_RED_PIN);
    }

    if (u8Led & LED_GREEN == LED_GREEN)
    {
        GPIO_TogglePins(LED_GREEN_PORT, LED_GREEN_PIN);
    }

    if (u8Led & LED_BLUE == LED_BLUE)
    {
        GPIO_TogglePins(LED_BLUE_PORT, LED_BLUE_PIN);
    }
}

/**
 * @brief  BSP clock initialize.
 *         Set board system clock to PLLH@240MHz
 *         Flash: 5 wait
 *         SRAM_HS: 1 wait
 *         SRAM1_2_3_4_B: 2 wait
 *         PCLK0: 240MHz
 *         PCLK1: 120MHz
 *         PCLK2: 60MHz
 *         PCLK3: 60MHz
 *         PCLK4: 120MHz
 *         EXCLK: 120MHz
 *         HCLK:  240MHz
 * @param  None
 * @retval None
 */
void BSP_CLK_Init(void)
{

}

/**
 * @}
 */

#endif /* BSP_EV_HC32M423_LQFP64 */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
