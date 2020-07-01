/**
 *******************************************************************************
 * @file  timer0/capture/source/main.c
 * @brief Main program of TIMER0 for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-03       Heqb          First version
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
 * @addtogroup TMR0_Capture
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

/* TIMER0 interrupt source and number define */
#define TIMER0_IRQn     (Int014_IRQn)
#define TIMER0_SOURCE   (INT_TMR0_GCMP)

#define KEY1_PORT       (GPIO_PORT_0)
#define KEY1_PIN        (GPIO_PIN_2)

#define TMR0x           (M4_TMR02)
#define Chx             (TMR0_ChannelB)

#define HCLK_FRQ        (1000000U)
#define CAPTURE_CNT_MAX (2U)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
__IO static uint16_t CaptureData[CAPTURE_CNT_MAX] = {0U};
__IO static uint16_t CaptureCnt = 0U;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  TMR0 compare IRQ callback
 * @param  None
 * @retval None
 */
void TMR0_2_CmpB_IrqHandler(void)
{
    if(CaptureCnt != CAPTURE_CNT_MAX)
    {
        CaptureData[CaptureCnt] = TMR0_GetCmpReg(TMR0x, Chx);
        CaptureCnt++;
    }
    else
    {
        /* Finish tmr0 capture */
        TMR0_Cmd(TMR0x, Chx, Disable);
    }
    TMR0_ClearFlag(TMR0x, Chx);
}

/**
 * @brief  Main function of example project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_regi_config_t stcIrqRegiCfg;
    stc_exint_config_t  stcExintCfg;
    stc_tmr0_init_t stcTmr0Init;
    stc_gpio_init_t stcGpioIni;

    /* Configure system clock. */
    SystemClockConfig();

    /* Configure RGB LED. */
    LedConfig();

    /* Config EXINT (INTP1 SW2)function for hardware trigger */
    GPIO_StructInit(&stcGpioIni);
    stcGpioIni.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(KEY1_PORT, KEY1_PIN, &stcGpioIni);
    EXINT_StructInit(&stcExintCfg);
    stcExintCfg.u32ExIntCh    = EXINT_CH05;
    stcExintCfg.u32ExIntFAE   = EXINT_FILTER_A_ON;
    stcExintCfg.u32ExIntFAClk = EXINT_FACLK_HCLK_DIV32;
    stcExintCfg.u32ExIntLvl   = EXINT_TRIGGER_BOTH;
    EXINT_Init(&stcExintCfg);

    /* Enable AOS function */
    CLK_FcgPeriphClockCmd(CLK_FCG_AOS, Enable);

    /* Enable timer0 peripheral clock */
    CLK_FcgPeriphClockCmd(CLK_FCG_TIM0_2, Enable);

    /* TMR0 capture function initialize */
    TMR0_StructInit(&stcTmr0Init);
    stcTmr0Init.u32ClockDivision = TMR0_CLK_DIV256; /* Config clock division */
    stcTmr0Init.u32ClockSource = TMR0_CLK_SRC_HCLK;  /* Chose clock source */
    stcTmr0Init.u32Tmr0Func = TMR0_FUNC_CAPTURE;     /* Chose capture mode */
    TMR0_Init(TMR0x, Chx, &stcTmr0Init);

    /* Set internal hardware capture source */
    TMR0_SetTriggerSrc(TMR0x, EVT_PORT_EIRQ5);

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegiCfg.enIRQn = Tmr02GCMB_IRQn;
    NVIC_ClearPendingIRQ(stcIrqRegiCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegiCfg.enIRQn, DDL_IRQ_PRIORITY_02);
    NVIC_EnableIRQ(stcIrqRegiCfg.enIRQn);

    /* Timer0 interrupt function enable */
    TMR0_IntCmd(TMR0x, Chx, Enable);
    /* Timer function kick start */
    TMR0_Cmd(TMR0x, Chx, Enable);

    while(CAPTURE_CNT_MAX != CaptureCnt)
    {

    };

    LED_G_TOGGLE();
    while(1)
    {
    
    };
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

    /* Set clock division */
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
