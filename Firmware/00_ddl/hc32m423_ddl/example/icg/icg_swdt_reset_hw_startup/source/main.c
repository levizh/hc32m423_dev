/**
 *******************************************************************************
 * @file  icg/icg_swdt_reset_hw_startup/source/main.c
 * @brief Main program of ICG SWDT Reset for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-10       Yangjp          First version
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
 * @addtogroup ICG_SWDT_Reset
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* LED_R Port/Pin definition */
#define LED_R_PORT                      (GPIO_PORT_A)
#define LED_R_PIN                       (GPIO_PIN_4)

#define LED_R_ON()                      (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_OFF()                     (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_R_TOGGLE()                  (GPIO_TogglePins(LED_R_PORT, LED_R_PIN))

/* SW1 Port/Pin definition */
#define SW1_PORT                        (GPIO_PORT_D)
#define SW1_PIN                         (GPIO_PIN_7)

/* SWDT count cycle definition */
#define SWDT_COUNT_CYCLE                (256U)

/* Reset source definition */
#define RESET_SOURCE_SWDT               (0U)
#define RESET_SOURCE_OTHER              (1U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8ResetSource;
static uint8_t u8ExIntFlag = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  SW1 interrupt callback function.
 * @param  None
 * @retval None
 */
void EXINT07_SWINT15_IrqHandler(void)
{
    if (Set == EXINT_GetExIntSrc(EXINT_CH07))
    {
        u8ExIntFlag = 1U;
        EXINT_ClrExIntSrc(EXINT_CH07);
    }
}

/**
 * @brief  SW1 configuration.
 * @param  None
 * @retval None
 */
static void SW1_Config(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_exint_config_t stcExIntInit;

    /* configure structure initialization */
    GPIO_StructInit(&stcGpioInit);
    EXINT_StructInit(&stcExIntInit);

    /* External interrupt initialize */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(SW1_PORT, SW1_PIN, &stcGpioInit);

    /* External interrupt configure */
    stcExIntInit.u32ExIntCh     = EXINT_CH07;
    stcExIntInit.u32ExIntFAE    = EXINT_FILTER_A_ON;
    stcExIntInit.u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV8;
    stcExIntInit.u32ExIntFBE    = EXINT_FILTER_B_ON;
    stcExIntInit.u32ExIntFBTime = NMI_EXINT_FBTIM_2US;
    stcExIntInit.u32ExIntLvl    = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExIntInit);

    /* Clear pending */
    NVIC_ClearPendingIRQ(ExInt7_IRQn);
    /* Set priority */
    NVIC_SetPriority(ExInt7_IRQn, DDL_IRQ_PRIORITY_DEFAULT);
    /* Enable NVIC */
    NVIC_EnableIRQ(ExInt7_IRQn);
}

/**
 * @brief  Main function of ICG SWDT Reset.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /**
     ***************************************************************************
     @brief Modify hc32m423_icg.h file of define
     @verbatim
     #define ICG0_SWDT_HARDWARE_START         ICG_FUNCTION_ON

     #define ICG0_SWDT_AUTST                  ICG_SWDT_AFTER_RESET_AUTOSTART
     #define ICG0_SWDT_ITS                    ICG_SWDT_TRIG_EVENT_RESET
     #define ICG0_SWDT_PERI                   ICG_SWDT_COUNTER_CYCLE_256
     #define ICG0_SWDT_CKS                    ICG_SWDT_CLOCK_DIV64
     #define ICG0_SWDT_WDPT                   ICG_SWDT_RANGE_0TO25PCT
     #define ICG0_SWDT_SLTPOFF                ICG_SWDT_LPW_MODE_COUNT_STOP
     @endverbatim
     ***************************************************************************
     */
    uint16_t u16CmpVal;
    stc_gpio_init_t stcGpioInit;
    stc_rmu_rstcause_t stcRmuRstCause;

    /* Configure structure initialization */
    GPIO_StructInit(&stcGpioInit);

    /* LED Port/Pin initialization */
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    LED_R_OFF();

    /* Get RMU information */
    RMU_GetResetCause(&stcRmuRstCause);
    if (Set == stcRmuRstCause.SwdtRst)
    {
        u8ResetSource = RESET_SOURCE_SWDT;
        LED_R_ON();
    }
    else
    {
        u8ResetSource = RESET_SOURCE_OTHER;
    }
    RMU_ClrResetFlag();

    /* SW1 configuration */
    SW1_Config();
    /* Wait for SWDT module to complete initial load */
    DDL_Delay1ms(200U);
    /* Count cycle=256,range=0%-25% */
    u16CmpVal = SWDT_COUNT_CYCLE / 4U;

    while (1)
    {
        if (1U == u8ExIntFlag)
        {
            u8ExIntFlag = 0U;
            u16CmpVal = SWDT_COUNT_CYCLE / 2U;
        }

        if (SWDT_GetCountValue() < u16CmpVal)
        {
            SWDT_ReloadCounter();
            /* Wait for the count value to update */
            DDL_Delay1ms(10U);
            if (RESET_SOURCE_OTHER == u8ResetSource)
            {
                LED_R_TOGGLE();
            }
        }
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
