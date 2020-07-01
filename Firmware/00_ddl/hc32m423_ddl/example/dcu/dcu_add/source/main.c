/**
 *******************************************************************************
 * @file  dcu/dcu_add/source/main.c
 * @brief This example demonstrates DCU add function.
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
 * @addtogroup DCU_Add
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
static void DcuIrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static en_int_status_t m_enOpIntStatus = Reset;

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
 * @brief  DCU irq callback function.
 * @param  None
 * @retval None
 */
static void DcuIrqCallback(void)
{
    if (Set == DCU_GetFlag(DCU_UNIT, DCU_FLAG_OPERATION))
    {
        m_enOpIntStatus = Set;
        DCU_ClearFlag(DCU_UNIT, DCU_FLAG_OPERATION);
    }
}

/**
 * @brief  Main function of DCU add project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;
    stc_dcu_init_t stcDcuInit;
    en_result_t enTestResult = Ok;
    stc_irq_regi_config_t stcIrqRegiCfg;
    uint32_t u32OverflowData0;
    uint32_t u32OverflowData2;
    uint16_t au16Data0Val[4];
    uint16_t au16Data2Val[4];
    uint16_t au16Data1Val[4] = {0x0000, 0x2222, 0x4444, 0x8888};
    uint32_t u32CalTimes = ARRAY_SZ(au16Data1Val);

    /* Initialize LED */
    LedConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNCTION_CLK_GATE, Enable);

    /* Initialize DCU */
    DCU_StructInit(&stcDcuInit);
    stcDcuInit.u32IntCmd = DCU_INT_ENABLE;
    stcDcuInit.u32IntSel = DCU_INT_OPERATION;
    stcDcuInit.u32Mode = DCU_ADD;
    stcDcuInit.u32DataSize = DCU_DATA_BITS_16;
    DCU_Init(DCU_UNIT, &stcDcuInit);

    /* Set DCU IRQ */
    stcIrqRegiCfg.enIRQn = Int000_IRQn;
    stcIrqRegiCfg.pfnCallback = &DcuIrqCallback;
    stcIrqRegiCfg.enIntSrc = INT_DCU;
    INTC_IrqSignIn(&stcIrqRegiCfg);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);

    DCU_WriteReg16Data0(DCU_UNIT, 0x0000UL);

    for (i = 0UL; i < u32CalTimes - 1UL; i++)
    {
        DCU_WriteReg16Data1(DCU_UNIT, au16Data1Val[i]);

        au16Data0Val[i] = DCU_ReadReg16Data0(DCU_UNIT);
        au16Data2Val[i] = DCU_ReadReg16Data2(DCU_UNIT);

        /* Compare DCU regisger DATA0 && DATA2 value: DATA0 value == 2 * DATA2 value */
        if (au16Data0Val[i] != (2u * au16Data2Val[i]))
        {
            enTestResult = Error;
            break;
        }
    }

    DCU_WriteReg16Data1(DCU_UNIT, 0x2222UL);

    while (Set != m_enOpIntStatus)    /* Wait add overflow */
    {
    }

    u32OverflowData0 = (uint32_t)DCU_ReadReg16Data0(DCU_UNIT) + 0xFFFFUL;
    u32OverflowData2 = 2UL * ((uint32_t)DCU_ReadReg16Data2(DCU_UNIT));

    /* Compare DCU regisger DATA0 && DATA2 value: DATA0 value + 0xFFFF == 2 * DATA2 value */
    if (u32OverflowData0 != u32OverflowData2)
    {
        enTestResult = Error;
        break;
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
