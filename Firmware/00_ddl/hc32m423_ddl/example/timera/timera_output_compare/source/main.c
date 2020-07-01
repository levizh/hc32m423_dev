/**
 *******************************************************************************
 * @file  timera/timera_output_compare/source/main.c
 * @brief This example demonstrates TIMERA output compare function.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-11       Yangjp          First version
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
 * @addtogroup TIMERA_Output_Compare
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

/* SW2 Port/Pin definition */
#define SW2_PORT                        (GPIO_PORT_2)
#define SW2_PIN                         (GPIO_PIN_1)
#define SW2_TRIGGER_EVENT               (EVT_PORT_EIRQ1)

/* TIMERA unit definition */
#define TIMERA_UNIT3                    (M4_TMRA3)
#define TIMERA_UNIT3_CLOCK              (CLK_FCG_TIMA3)
#define TIMERA_UNIT3_PERIOD_VALUE       ((uint16_t)(SystemCoreClock/256U/100U))

/* TIMERA channel 1 Port/Pin definition */
#define TIMERA_UNIT3_CH1_PORT           (GPIO_PORT_7)
#define TIMERA_UNIT3_CH1_PIN            (GPIO_PIN_1)
#define TIMERA_UNIT3_CH1_FUNC           (GPIO_FUNC_4_TIMA)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint8_t u8Sw1IntFlag = 0U, u8Sw2IntFlag = 0U;

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
        u8Sw1IntFlag = 1U;
        EXINT_ClrExIntSrc(EXINT_CH07);
    }
}

/**
 * @brief  SW2 interrupt callback function.
 * @param  None
 * @retval None
 */
void EXINT01_SWINT09_IrqHandler(void)
{
    if (Set == EXINT_GetExIntSrc(EXINT_CH01))
    {
        if (0U == u8Sw2IntFlag)
        {
            u8Sw2IntFlag = 1U;
            LED_R_ON();
            TIMERA_SetHwTriggerCondition(TIMERA_UNIT3, TIMERA_HWSTOP_SPECIFY_EVT);
        }
        else
        {
            u8Sw2IntFlag = 0U;
            LED_R_OFF();
            TIMERA_SetHwTriggerCondition(TIMERA_UNIT3, TIMERA_HWSTART_SPECIFY_EVT);
        }
        EXINT_ClrExIntSrc(EXINT_CH01);
    }
}

/**
 * @brief  Configure System clock.
 * @param  None
 * @retval None
 */
static void SystemClk_Config(void)
{
    /* Configure the system clock to HRC 48MHz. */
    CLK_HRCInit(CLK_HRC_ON, CLK_HRCFREQ_48);
}

/**
 * @brief  Configure LED.
 * @param  None
 * @retval None
 */
static void Led_Config(void)
{
    stc_gpio_init_t stcGpioInit;

    /* Configure structure initialization */
    GPIO_StructInit(&stcGpioInit);

    /* LED Port/Pin initialization */
    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    LED_R_OFF();
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
 * @brief  SW2 configuration.
 * @param  None
 * @retval None
 */
static void SW2_Config(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_exint_config_t stcExIntInit;

    /* configure structure initialization */
    GPIO_StructInit(&stcGpioInit);
    EXINT_StructInit(&stcExIntInit);

    /* External interrupt initialize */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(SW2_PORT, SW2_PIN, &stcGpioInit);

    /* External interrupt configure */
    stcExIntInit.u32ExIntCh     = EXINT_CH01;
    stcExIntInit.u32ExIntFAE    = EXINT_FILTER_A_ON;
    stcExIntInit.u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV8;
    stcExIntInit.u32ExIntFBE    = EXINT_FILTER_B_ON;
    stcExIntInit.u32ExIntFBTime = NMI_EXINT_FBTIM_2US;
    stcExIntInit.u32ExIntLvl    = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExIntInit);

    /* Clear pending */
    NVIC_ClearPendingIRQ(ExInt1_IRQn);
    /* Set priority */
    NVIC_SetPriority(ExInt1_IRQn, DDL_IRQ_PRIORITY_DEFAULT);
    /* Enable NVIC */
    NVIC_EnableIRQ(ExInt1_IRQn);
}

/**
 * @brief  Configure TimerA function.
 * @param  None
 * @retval None
 */
static void Timera_Config(void)
{
    stc_timera_init_t stcTimeraInit;
    stc_timera_oc_init_t stcTimeraOCInit;
    stc_gpio_init_t stcGpioInit;

    /* Configuration structure initialization */
    TIMERA_StructInit(&stcTimeraInit);
    GPIO_StructInit(&stcGpioInit);

    /* Configuration peripheral clock */
    CLK_FcgPeriphClockCmd(TIMERA_UNIT3_CLOCK, Enable);
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);

    /* Configuration TIMERA capture Port */
    GPIO_SetFunc(TIMERA_UNIT3_CH1_PORT, TIMERA_UNIT3_CH1_PIN, TIMERA_UNIT3_CH1_FUNC);

    /* Configuration timera unit 3 structure */
    stcTimeraInit.u16CountMode = TIMERA_TRIANGLE_WAVE;
    stcTimeraInit.u16ClkDiv = TIMERA_CLKDIV_DIV256;
    /* Period_Value(10ms) = SystemClock(SystemCoreClock) / TimerA_Clock_Division(1024) / Frequency(100) */
    /* PWM output frequency = 1Sec / (Period_Value * 2) = 50Hz, Because the TimerA counting mode is triangle
       wave and Set the compare match to trigger PWM output inversion */
    stcTimeraInit.u16PeriodVal = TIMERA_UNIT3_PERIOD_VALUE;
    stcTimeraInit.u16HwStartCondition = TIMERA_HWSTART_SPECIFY_EVT;
    TIMERA_Init(TIMERA_UNIT3, &stcTimeraInit);

    /* Configuration timera unit 3 compare structure */
    stcTimeraOCInit.u16CompareVal = 0U;
    stcTimeraOCInit.u16StartCountOutput = TIMERA_OC_STARTCOUNT_OUTPUT_LOW;
    stcTimeraOCInit.u16StopCountOutput = TIMERA_OC_STOPCOUNT_OUTPUT_LOW;
    stcTimeraOCInit.u16CompareMatchOutput = TIMERA_OC_CMPMATCH_OUTPUT_INVERTED;
    stcTimeraOCInit.u16PeriodMatchOutput = TIMERA_OC_PERIODMATCH_OUTPUT_HOLD;
    stcTimeraOCInit.u16PortOutputState = TIMERA_OC_FORCE_OUTPUT_INVALID;
    stcTimeraOCInit.u16CacheState = TIMERA_OC_CACHE_ENABLE;
    stcTimeraOCInit.u16CacheTransmitCondition = TIMERA_OC_CACHE_TRANSMIT_CREST;
    /* Enable channel 1 */
    TIMERA_OC_Init(TIMERA_UNIT3, TIMERA_CHANNEL_CH1, &stcTimeraOCInit);
    TIMERA_OC_PwmCmd(TIMERA_UNIT3, TIMERA_CHANNEL_CH1, Enable);

    /* Set external Int trigger timera compare */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(SW2_PORT, SW2_PIN, &stcGpioInit);
    TIMERA_SetCaptureTriggerSrc(SW2_TRIGGER_EVENT);
}

/**
 * @brief  Main function of TIMERA output compare.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint16_t u16PeriodValue, u16CurrValue;

    /* Configure system clock. */
    SystemClk_Config();

    /* Configure LED. */
    Led_Config();

    /* Configure SW1 and SW2 */
    SW1_Config();
    SW2_Config();

    /* Configure TimerA */
    Timera_Config();

    u16CurrValue = 0U;
    u16PeriodValue = TIMERA_GetPeriod(TIMERA_UNIT3);

    while (1)
    {
        if (1U == u8Sw1IntFlag)
        {
            u8Sw1IntFlag = 0U;
            u16CurrValue += u16PeriodValue / 20U;
            if (u16CurrValue > u16PeriodValue)
            {
                u16CurrValue = 0U;
            }
            TIMERA_OC_SetCompare(TIMERA_UNIT3, TIMERA_CHANNEL_CH2, u16CurrValue);
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
