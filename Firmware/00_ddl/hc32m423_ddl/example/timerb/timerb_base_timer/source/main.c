/**
 *******************************************************************************
 * @file  timerb/timerb_base_timer/source/main.c
 * @brief This example demonstrates TIMERB base count function.
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
 * @addtogroup TIMERB_Base_Timer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Green LED Port/Pin definition */
#define LED_G_PORT                      (GPIO_PORT_A)
#define LED_G_PIN                       (GPIO_PIN_5)
#define LED_G_TOGGLE()                  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))

/* TIMERB unit && interrupt number && counter period value definition */
#define TMRB_UNIT                       (M4_TMRB)
#define TMRB_OVF_INT_SRC                (INT_TMRB_OVF)
#define TMRB_OVF_INT_IRQn               (Int000_IRQn)
#define TMRB_CNT_1S_VAL(div)            ((TmrbPclkFreq() / (uint32_t)(div))) /* Period_Value(1000ms) */

/* TIMERB TIMB_t_PWMn(t=1, n=1~4 Port/Pin definition */
#define TMRB_T_PWM1_PORT                (GPIO_PORT_7)     /* P72: TIMB_1_PWM1 */
#define TMRB_T_PWM1_PIN                 (GPIO_PIN_2)
#define TMRB_T_PWM1_GPIO_FUNC           (GPIO_FUNC_3_TIMB)

#define TMRB_T_PWM3_PORT                (GPIO_PORT_7)     /* P71: TIMB_1_PWM3 */
#define TMRB_T_PWM3_PIN                 (GPIO_PIN_1)
#define TMRB_T_PWM3_GPIO_FUNC           (GPIO_FUNC_3_TIMB)

/* Function clock gate definition */
#define FUNCTION_CLK_GATE               (CLK_FCG_TIMB_1)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void TMRB_OverflowIrqCallback(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_pll_cfg_t stcPllCfg;
    stc_clk_div_cfg_t stcSysClkDiv;
    stc_clk_xtal_init_t stcXTALInit;

    /* Set bus clk div. */
    stcSysClkDiv.u32HclkDiv = CLK_HCLK_DIV1;   /* Max 80MHz */
    stcSysClkDiv.u32Pclk1Div = CLK_PCLK1_DIV1; /* Max 80MHz */
    stcSysClkDiv.u32Pclk4Div = CLK_PCLK4_DIV1; /* Max 80MHz */
    CLK_SetSysclkDiv(&stcSysClkDiv);

    /* Configure XTAL */
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTALMODE_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTALDRV_HIGH;
    stcXTALInit.u8XtalSupDrv = CLK_XTAL_SUPDRV_OFF;
    stcXTALInit.u8XtalStb = CLK_XTALSTB_8;
    CLK_XTALInit(&stcXTALInit);

    CLK_SetPllSource(CLK_PLL_SRC_XTAL);

    /* PLL config (XTAL / pllmDiv * plln / PllpDiv = 80M). */
    stcPllCfg.pllmDiv = 2UL;
    stcPllCfg.plln = 60UL;
    stcPllCfg.PllpDiv = 3UL;
    CLK_PllConfig(&stcPllCfg);

    /* Set flash wait */
    EFM_Unlock();
    EFM_SetWaitCycle(EFM_WAIT_CYCLE_3);
    EFM_Lock();

    /* Switch system clock to PLL */
    CLK_SetSysclkSrc(CLK_SYSCLKSOURCE_PLL);
}

/**
 * @brief  Get TIMERB PCLK frequency.
 * @param  None
 * @retval None
 */
static uint32_t TmrbPclkFreq(void)
{
    stc_clk_freq_t stcClkFreq;

    CLK_GetClockFreq(&stcClkFreq);
    return stcClkFreq.pclk1Freq;
}

/**
 * @brief  Configure RGB LED.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
    stc_gpio_init_t stcGpioInit = {0};

    stcGpioInit.u16PinDir = PIN_DIR_OUT;
    stcGpioInit.u16PinState = PIN_STATE_SET;
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
}

/**
 * @brief  TIMERB unit overflow IRQ callback.
 * @param  None
 * @retval None
 */
static void TMRB_OverflowIrqCallback(void)
{
    LED_G_TOGGLE();

    TMRB_ClearFlag(TMRB_UNIT, TMRB_FLAG_OVF);
}

/**
 * @brief  Main function of TIMERB base timer project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_tmrb_init_t stcTmrbInit;
    stc_irq_signin_config_t stcIrqRegiConf;

    /* Configure system clock. */
    SystemClockConfig();

    /* Configure RGB LED. */
    LedConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNCTION_CLK_GATE, Enable);

    /* Configure TIM_<t>_PWM1/TIM_<t>_PWM3. */
    GPIO_SetFunc(TMRB_T_PWM1_PORT, TMRB_T_PWM1_PIN, TMRB_T_PWM1_GPIO_FUNC);
    GPIO_SetFunc(TMRB_T_PWM3_PORT, TMRB_T_PWM3_PIN, TMRB_T_PWM3_GPIO_FUNC);

    /* Initialize TIMERB structure. */
    TMRB_StructInit(&stcTmrbInit);
    stcTmrbInit.u16ClkDiv = TMRB_CLKDIV_DIV1024;
    stcTmrbInit.u16PeriodVal = (uint16_t)(TMRB_CNT_1S_VAL(1024UL)/2UL);
    stcTmrbInit.u16HwStartCondition = TMRB_HWSTART_TIMB_T_PWM1_RISING;
    stcTmrbInit.u16HwClearCondition = (TMRB_HWCLEAR_TIMB_T_PWM3_RISING | TMRB_HWCLEAR_TIMB_T_PWM3_FALLING);

    /* Initialize TIMERB unit. */
    TMRB_Init(TMRB_UNIT, &stcTmrbInit);
    TMRB_IntCmd(TMRB_UNIT, TMRB_INT_OVF, Enable);

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegiConf.enIRQn = TMRB_OVF_INT_IRQn;
    stcIrqRegiConf.enIntSrc = TMRB_OVF_INT_SRC;
    stcIrqRegiConf.pfnCallback = &TMRB_OverflowIrqCallback;
    INTC_IrqSignIn(&stcIrqRegiConf);
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

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
