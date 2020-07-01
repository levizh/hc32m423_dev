/**
 *******************************************************************************
 * @file  timera/timera_input_capture/source/main.c
 * @brief This example demonstrates TIMERA input capture function.
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
 * @addtogroup TIMERA_Input_Capture
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

/* LED_G Port/Pin definition */
#define LED_G_PORT                      (GPIO_PORT_A)
#define LED_G_PIN                       (GPIO_PIN_5)

#define LED_G_ON()                      (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))
#define LED_G_OFF()                     (GPIO_SetPins(LED_G_PORT, LED_G_PIN))
#define LED_G_TOGGLE()                  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))

/* SW1 Port/Pin definition */
#define SW1_PORT                        (GPIO_PORT_D)
#define SW1_PIN                         (GPIO_PIN_7)
#define SW1_TRIGGER_EVENT               (EVT_PORT_EIRQ7)

/* TIMERA unit definition */
#define TIMERA_UNIT3                    (M4_TMRA3)
#define TIMERA_UNIT3_CLOCK              (CLK_FCG_TIMA3)
#define TIMERA_UNIT3_PERIOD_VALUE       ((uint16_t)(SystemCoreClock/256U/100U))

/* TIMERA channel 1 Port/Pin definition */
#define TIMERA_UNIT3_CH1_PORT           (GPIO_PORT_7)
#define TIMERA_UNIT3_CH1_PIN            (GPIO_PIN_1)
#define TIMERA_UNIT3_CH1_FUNC           (GPIO_FUNC_4_TIMA)

/* TIMERA channel 2 Port/Pin definition */
#define TIMERA_UNIT3_CH2_PORT           (GPIO_PORT_7)
#define TIMERA_UNIT3_CH2_PIN            (GPIO_PIN_2)
#define TIMERA_UNIT3_CH2_FUNC           (GPIO_FUNC_4_TIMA)

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
 * @brief  TIMERA unit 3 compare interrupt callback function.
 * @param  None
 * @retval None
 */
void TIMERA_3_Cmp_IrqHandler(void)
{
    /* Capture channel 1 */
    if (Set == TIMERA_GetFlag(TIMERA_UNIT3, TIMERA_FLAG_CMP1))
    {
        LED_R_TOGGLE();
        TIMERA_ClearFlag(TIMERA_UNIT3, TIMERA_FLAG_CMP1);
    }
    /* Capture channel 2 */
    if (Set == TIMERA_GetFlag(TIMERA_UNIT3, TIMERA_FLAG_CMP2))
    {
        LED_G_TOGGLE();
        TIMERA_ClearFlag(TIMERA_UNIT3, TIMERA_FLAG_CMP2);
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
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    LED_R_OFF();
    LED_G_OFF();
}

/**
 * @brief  Configure TimerA function.
 * @param  None
 * @retval None
 */
static void Timera_Config(void)
{
    stc_timera_init_t stcTimeraInit;
    stc_timera_ic_init_t stcTimeraICInit;
    stc_gpio_init_t stcGpioInit;

    /* Configuration structure initialization */
    TIMERA_StructInit(&stcTimeraInit);
    GPIO_StructInit(&stcGpioInit);

    /* Configuration peripheral clock */
    CLK_FcgPeriphClockCmd(TIMERA_UNIT3_CLOCK, Enable);
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);

    /* Configuration TIMERA capture Port */
    GPIO_SetFunc(TIMERA_UNIT3_CH1_PORT, TIMERA_UNIT3_CH1_PIN, TIMERA_UNIT3_CH1_FUNC);
    GPIO_SetFunc(TIMERA_UNIT3_CH2_PORT, TIMERA_UNIT3_CH2_PIN, TIMERA_UNIT3_CH2_FUNC);

    /* Configuration timera unit 1 structure */
    stcTimeraInit.u16CountMode = TIMERA_SAWTOOTH_WAVE;
    stcTimeraInit.u16CountDir = TIMERA_COUNT_UP;
    stcTimeraInit.u16ClkDiv = TIMERA_CLKDIV_DIV256;
    /* Period_Value(10ms) = SystemClock(SystemCoreClock) / TimerA_Clock_Division(256) / Frequency(100) */
    stcTimeraInit.u16PeriodVal = TIMERA_UNIT3_PERIOD_VALUE;
    TIMERA_Init(TIMERA_UNIT3, &stcTimeraInit);

    /* Configuration timera unit 1 capture structure */
    stcTimeraICInit.u16PwmFilterState = TIMERA_IC_PWM_FILTER_DISABLE;
    stcTimeraICInit.u16CaptureCondition = TIMERA_IC_PWM_RISING | TIMERA_IC_SPECIFY_EVT;
    /* Enable channel 1 */
    TIMERA_IC_Init(TIMERA_UNIT3, TIMERA_CHANNEL_CH1, &stcTimeraICInit);
    /* Enable channel 2 */
    TIMERA_IC_Init(TIMERA_UNIT3, TIMERA_CHANNEL_CH2, &stcTimeraICInit);
    TIMERA_IntCmd(TIMERA_UNIT3, TIMERA_INT_CMP1 | TIMERA_INT_CMP2, Enable);

    /* Configuration timera unit 1 interrupt */
    NVIC_ClearPendingIRQ(TmrA3CMP_IRQn);
    NVIC_SetPriority(TmrA3CMP_IRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(TmrA3CMP_IRQn);

    /* Set external Int Ch.0 trigger timera compare */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(SW1_PORT, SW1_PIN, &stcGpioInit);
    TIMERA_SetCaptureTriggerSrc(SW1_TRIGGER_EVENT);

    /* Start TIMERA counter */
    TIMERA_Cmd(TIMERA_UNIT3, Enable);
}

/**
 * @brief  Main function of TIMERA input capture.
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configure system clock. */
    SystemClk_Config();

    /* Configure LED. */
    Led_Config();

    /* Configure TimerA */
    Timera_Config();

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
