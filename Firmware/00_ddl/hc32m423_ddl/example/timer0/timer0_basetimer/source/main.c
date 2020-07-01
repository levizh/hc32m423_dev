/**
 *******************************************************************************
 * @file  timer0/basetimer/source/main.c
 * @brief Main program of TIMER0 for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-03       Heqb         First version
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
 * @addtogroup TMR0_Basetimer
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Define for RGB LED */
#define LED_G_PORT      (GPIO_PORT_A)
#define LED_G_PIN       (GPIO_PIN_5)
#define LED_G_TOGGLE()  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))

#define KEY1_PORT       (GPIO_PORT_0)
#define KEY1_PIN        (GPIO_PIN_2)

#define TMR0x           (M4_TMR01)
#define CHx             (TMR0_CH_B)
#define EVENT_SRC       (EVT_PORT_EIRQ5)

#define HCLK_FRQ        (1000000UL)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);
static void IRQ_Config(void);
static void TMR0Config(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of example project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configure system clock. */
    SystemClockConfig();
    /* Configure RGB LED. */
    LedConfig();
    /* Configure EXINT && NVIC */
    IRQ_Config();
    /* Enable AOS function */
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);
    /* Configure TMR0 */
    TMR0Config();
    /* Tmr0 function kick start */
    TMR0_Cmd(TMR0x, CHx, Enable);

    while(1)
    {
        ;
    }
}

/**
 * @brief  TMR0 compare IRQ callback
 * @param  None
 * @retval None
 */
void TMR0_1_CmpB_IrqHandler(void)
{
    LED_G_TOGGLE();
    TMR0_ClearStatus(TMR0x, CHx);
}

/**
 * @brief  Configure EXINT && NVIC.
 * @param  None
 * @retval None
 */
static void IRQ_Config(void)
{
    stc_irq_signin_config_t stcIrqRegCfg;
    stc_gpio_init_t stcGpioInit;
    stc_exint_config_t stcExintCfg;

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegCfg.enIRQn = Tmr01GCMB_IRQn;
    NVIC_ClearPendingIRQ(stcIrqRegCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegCfg.enIRQn, DDL_IRQ_PRIORITY_02);
    NVIC_EnableIRQ(stcIrqRegCfg.enIRQn);
    
    /* Config EXINT (INT5 Key1)function for hardware trigger */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(KEY1_PORT, KEY1_PIN, &stcGpioInit);
    EXINT_StructInit(&stcExintCfg);
    stcExintCfg.u32ExIntCh    = EXINT_CH05;
    stcExintCfg.u32ExIntFAE   = EXINT_FILTER_A_ON;
    stcExintCfg.u32ExIntFAClk = EXINT_FACLK_HCLK_DIV32;
    stcExintCfg.u32ExIntLvl   = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExintCfg);
}

/**
 * @brief  Configure TMR0.
 * @param  None
 * @retval None
 */
static void TMR0Config(void)
{
    stc_tmr0_init_t stcTmr0Init;
    /* Enable timer0 peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_TIM0_1, Enable);

    /* TMR0 basetimer function initialize */
    TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockDivision = TMR0_CLK_DIV256;/* Config clock division */
    stcTmr0Init.u32ClockSource = TMR0_CLK_SRC_HCLK; /* Chose clock source */
    stcTmr0Init.u32Tmr0Func = TMR0_FUNC_CMP;        /* Tmr0 compare mode */
    stcTmr0Init.u32HwTrigFunc = TMR0_HWTRG_FUNC_STOP; /* Config Hardware trigger function */
    stcTmr0Init.u16CmpValue =  HCLK_FRQ / 2U / 256U;     /* Set compara register data */
    TMR0_Init(TMR0x, CHx, &stcTmr0Init);

    /* Set internal hardware capture source */
    TMR0_SetTriggerSrc(TMR0x, EVENT_SRC);
    /* Tmr0 interrupt function enable */
    TMR0_IntCmd(TMR0x, CHx, Enable);
}

/**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_xtal_init_t stcXTALInit;
    stc_clk_div_cfg_t stcSysClkDiv;

    /* Configure XTAL */
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTALMODE_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTALDRV_HIGH;
    stcXTALInit.u8XtalSupDrv = CLK_XTAL_SUPDRV_OFF;
    stcXTALInit.u8XtalStb = CLK_XTALSTB_8;
    /* Initialize XTAL clock */
    CLK_XTALInit(&stcXTALInit);

    /* Set bus clk div. */
    stcSysClkDiv.u32HclkDiv = CLK_HCLK_DIV8;   /* HCLK = 1MHZ */
    stcSysClkDiv.u32Pclk1Div = CLK_PCLK1_DIV8; /* PCLK1 = 1MHZ */
    stcSysClkDiv.u32Pclk4Div = CLK_PCLK4_DIV8; /* PCLK4 = 1MHZ */
    CLK_SetSysclkDiv(&stcSysClkDiv);

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysclkSrc(CLK_SYSCLKSOURCE_XTAL);
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
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
