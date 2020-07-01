/**
 *******************************************************************************
 * @file  dcu/dcu_hw_trigger_sub/source/main.c
 * @brief This example demonstrates DCU hardware signal trigger DCU sub function.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-01       Hongjh          First version
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
#include "hc32_ddl.h"

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup DCU_HW_Trigger_Sub
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* DCU unit definition */
#define DCU_UNIT                        (M4_DCU)

/* DCU hardware trigger signal number */
#define EVT_SRC_TRIG_DCU                (EVT_AOS_STRG)

/* Function clock gate definition */
#define FUNCTION_CLK_GATE               (CLK_FCG_DCU)

/* LED Red Color Port/Pin definition */
#define LED_R_PORT                      (GPIO_PORT_A)
#define LED_R_PIN                       (GPIO_PIN_4)

/* LED Green Color Port/Pin definition */
#define LED_G_PORT                      (GPIO_PORT_A)
#define LED_G_PIN                       (GPIO_PIN_5)

/* LED green & red */
#define LED_R_ON()                      (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_OFF()                     (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_ON()                      (GPIO_SetPins(LED_G_PORT, LED_G_PIN))
#define LED_G_OFF()                     (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void LedConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Configure red/green LED.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_SET;
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
}

/**
 * @brief  Main function of DCU sub project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    stc_dcu_init_t stcDcuInit;
    en_result_t enTestResult = Ok;
    uint32_t au32Data0Val[4];
    uint32_t au32Data2Val[4];
    uint32_t au32Data1Val[4] = {0x00000000, 0x22222222, 0x22222222, 0x22222222};
    uint32_t u32CalTimes = ARRAY_SZ(au32Data1Val);

    /* Initialize LED */
    LedConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(PWC_FCG0_PERIPH_PTDIS | PWC_FCG0_PERIPH_DCU, Enable);

    /* Initialize DCU */
    stcDcuInit.u32Mode = DCU_HW_TRIG_SUB;
    stcDcuInit.u32DataSize = DCU_DATA_BITS_32;
    DCU_Init(DCU_UNIT, &stcDcuInit);
    DCU_WriteReg32Data0(DCU_UNIT, 0x88888888UL);
    DCU_SetTriggerSrc(DCU_UNIT, EVT_SRC_TRIG_DCU);

    for (i = 0ul; i < u32CalTimes; i++)
    {
        DCU_WriteReg32Data1(DCU_UNIT, au32Data1Val[i]);

        /* Start soft trigger event */
        AOS_SW_Trigger();

        au32Data0Val[i] = DCU_WriteReg32Data0(DCU_UNIT);
        au32Data2Val[i] = DCU_WriteReg32Data2(DCU_UNIT);

        /* Compare DCU regisger DATA0 && DATA2 value: DATA0 value == 2 * DATA2 value */
        if (au32Data0Val[i] != (2ul * au32Data2Val[i]))
        {
            enTestResult = Error;
            break;
        }
        else
        {
        }
    }

    if (Ok == enTestResult)
    {
        LED_G_ON();  /* Test pass && meet the expected */
    }
    else
    {
        LED_R_ON();  /* Test fail && don't meet the expected */
    }

    while (1)
    {
    }
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
