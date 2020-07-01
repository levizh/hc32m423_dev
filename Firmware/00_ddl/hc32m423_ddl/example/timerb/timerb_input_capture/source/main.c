/**
 *******************************************************************************
 * @file  timerb/timerb_input_capture/source/main.c
 * @brief This example demonstrates TIMERB input capture function.
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
 * @addtogroup TIMERB_Input_Capture
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief  Buffer structure definition
 */
typedef struct
{
    uint16_t u16Capacity;
    uint16_t u16Index;
    uint16_t au16Buf[50];
} stc_buffer_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* EXINT channel/IRQn definition */
#define EXINT_CH                            (EXINT_CH05)
#define EXINT_INT                           (INT_PORT_EIRQ5)
#define EXINT_IRQn                          (Int000_IRQn)

/* EXINT Port/Pin definition */
#define EXINT_PORT                          (GPIO_PORT_0)
#define EXINT_PIN                           (GPIO_PIN_2)

/* Green LED Port/Pin definition */
#define LED_G_PORT                          (GPIO_PORT_A)
#define LED_G_PIN                           (GPIO_PIN_5)
#define LED_G_ON()                          (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))

/* TIMERB unit & interrupt number & counter period definition */
#define TMRB_UNIT                           (M4_TMRB)
#define TMRB_CNT_1S_VAL(div)                ((TmrbPclkFreq() / (uint32_t)(div))) /* Period_Value(1000ms) */
#define TMRB_CMP_INT                        (INT_TMRB_CMP)
#define TMRB_CMP_IRQn                       (Int001_IRQn)
#define EVT_TRIG_TMRB_CNT                   (EVT_PORT_EIRQ5)

/* TIMERB input capture channel definition */
#define TMRB_IC_ODD_CH                      (TMRB_CH1)
#define TMRB_IC_ODD_CH_FLAG                 (TMRB_FLAG_CMP1)
#define TMRB_IC_ODD_CH_INT_CMP              (TMRB_INT_CMP1)

#define TMRB_IC_EVEN_CH                     (TMRB_CH2)
#define TMRB_IC_EVEN_CH_FLAG                (TMRB_FLAG_CMP2)
#define TMRB_IC_EVEN_CH_INT_CMP             (TMRB_INT_CMP2)

/* TIMERB TIMB_t_PWM1 Port/Pin definition */
#define TMRB_IC_ODD_CH_PWM_PORT             (GPIO_PORT_7)     /* P72: TIMB_1_PWM1 */
#define TMRB_IC_ODD_CH_PWM_PIN              (GPIO_PIN_2)
#define TMRB_IC_ODD_CH_PWM_GPIO_FUNC        (GPIO_FUNC_3_TIMB)

#define TMRB_IC_EVEN_CH_PWM_PORT            (GPIO_PORT_7)     /* P75: TIMB_1_PWM2 */
#define TMRB_IC_EVEN_CH_PWM_PIN             (GPIO_PIN_5)
#define TMRB_IC_EVEN_CH_PWM_GPIO_FUNC       (GPIO_FUNC_3_TIMB)

/* Buffer size definition */
#define TMRB_IC_CMPBUF_SIZE                 (50U)

/* TIMERB output compare unit & counter period/compare value definition */
#define TMRB_OC_CH                          (TMRB_CH3)

#define TMRB_OC_CH_PWM_PORT                 (GPIO_PORT_7)     /* P71: TIMB_1_PWM3 */
#define TMRB_OC_CH_PWM_PIN                  (GPIO_PIN_1)
#define TMRB_OC_CH_PWM_GPIO_FUNC            (GPIO_FUNC_3_TIMB)

/* Function clock gate definition */
#define FUNCTION_CLK_GATE                   (CLK_FCG_TIMB_1 | CLK_FCG_AOS)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);
static void ExintIrqCallback(void);
static uint32_t TmrbPclkFreq(void);
static void TMRB_CmpIrqCallback(void);
static void BufferWrite(stc_buffer_t *pstcBuffer, uint16_t u16Data);

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
 * @brief  Configure EXINT.
 * @param  None
 * @retval None
 */
static void ExintConfig(void)
{
    stc_gpio_init_t stcGpioInit;
    stc_exint_config_t stcExIntInit;
    stc_irq_signin_config_t stcIrqRegiConf;

    /* External interrupt port initialize */
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(EXINT_PORT, EXINT_PIN, &stcGpioInit);

    /* EXINT Channel configure */
    EXINT_StructInit(&stcExIntInit);
    stcExIntInit.u32ExIntCh     = EXINT_CH;
    stcExIntInit.u32ExIntFAE    = EXINT_FILTER_A_ON;
    stcExIntInit.u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV8;
    stcExIntInit.u32ExIntFBE    = EXINT_FILTER_B_ON;
    stcExIntInit.u32ExIntFBTime = NMI_EXINT_FBTIM_2US;
    stcExIntInit.u32ExIntLvl    = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExIntInit);

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegiConf.enIRQn = EXINT_IRQn;
    stcIrqRegiConf.enIntSrc = EXINT_INT;
    stcIrqRegiConf.pfnCallback = &ExintIrqCallback;
    INTC_IrqSignIn(&stcIrqRegiConf);
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);
}

/**
 * @brief  External interrupt ISR
 * @param  None
 * @retval None
 */
static void ExintIrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(EXINT_CH))
   {
        EXINT_ClrExIntSrc(EXINT_CH);
        LED_G_ON();
   }
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
 * @brief  TIMERB unit compare match IRQ callback
 * @param  None
 * @retval None
 */
static void TMRB_CmpIrqCallback(void)
{
    static stc_buffer_t m_stcEvenUnitCmpBuf= {
        .u16Index = 0U,
        .u16Capacity = TMRB_IC_CMPBUF_SIZE,
    };

    static stc_buffer_t m_stcOddUnitCmpBuf = {
        .u16Index = 0U,
        .u16Capacity = TMRB_IC_CMPBUF_SIZE,
    };

    if (Set == TMRB_GetFlag(TMRB_UNIT, TMRB_IC_ODD_CH_FLAG))
    {
        BufferWrite(&m_stcOddUnitCmpBuf, TMRB_GetCompare(TMRB_UNIT, TMRB_IC_ODD_CH));
        TMRB_ClearFlag(TMRB_UNIT, TMRB_IC_ODD_CH_FLAG);
    }

    if (Set == TMRB_GetFlag(TMRB_UNIT, TMRB_IC_EVEN_CH_FLAG))
    {
        BufferWrite(&m_stcEvenUnitCmpBuf, TMRB_GetCompare(TMRB_UNIT, TMRB_IC_EVEN_CH));
        TMRB_ClearFlag(TMRB_UNIT, TMRB_IC_EVEN_CH_FLAG);
    }
}

/**
 * @brief  Push data into buffer.
 * @param  [in] pstcBuffer              Pointer to a @ref stc_buffer_t structure
 * @param  [in] u16Data                 Data to write into buffer
 * @retval None
 */
static void BufferWrite(stc_buffer_t *pstcBuffer, uint16_t u16Data)
{
    if (pstcBuffer->u16Index >= pstcBuffer->u16Capacity)
    {
        pstcBuffer->u16Index = 0U;
    }

    pstcBuffer->au16Buf[pstcBuffer->u16Index++] = u16Data;
}

/**
 * @brief  Main function of TIMERB input capture project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_irq_signin_config_t stcIrqRegiConf;
    stc_tmrb_init_t stcTmrbInit;
    stc_tmrb_oc_init_t stcTmrbOcInit;
    stc_tmrb_ic_init_t stcTmrbIcInit;

    /* Configure system clock. */
    SystemClockConfig();

    /* Configure RGB LED. */
    LedConfig();

    /* Configure EXINT. */
    ExintConfig();

    /* Configure TIM_<t>_PWM. */
    GPIO_SetFunc(TMRB_IC_ODD_CH_PWM_PORT, TMRB_IC_ODD_CH_PWM_PIN, TMRB_IC_ODD_CH_PWM_GPIO_FUNC);
    GPIO_SetFunc(TMRB_IC_EVEN_CH_PWM_PORT, TMRB_IC_EVEN_CH_PWM_PIN, TMRB_IC_EVEN_CH_PWM_GPIO_FUNC);
    GPIO_SetFunc(TMRB_OC_CH_PWM_PORT, TMRB_OC_CH_PWM_PIN, TMRB_OC_CH_PWM_GPIO_FUNC);

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNCTION_CLK_GATE, Enable);

    /* Initialize TIMERB unit. */
    TMRB_StructInit(&stcTmrbInit);
    stcTmrbInit.u16ClkDiv = TMRB_CLKDIV_DIV1024;
    stcTmrbInit.u16PeriodVal = (uint16_t)(TMRB_CNT_1S_VAL(1024UL)/2UL);
    TMRB_Init(TMRB_UNIT, &stcTmrbInit);

    /* Initialize TIMERB output compare function . */
    stcTmrbOcInit.u16CompareVal = stcTmrbInit.u16PeriodVal/2U;
    stcTmrbOcInit.u16PortOutputState = TMRB_OC_PORT_OUTPUT_ENABLE;
    stcTmrbOcInit.u16StartCntOutput = TMRB_OC_STARTCNT_OUTPUT_HIGH;
    stcTmrbOcInit.u16StopCntOutput = TMRB_OC_STOPCNT_OUTPUT_HIGH;
    stcTmrbOcInit.u16CompareMatchOutput = TMRB_OC_CMPMATCH_OUTPUT_INVERTED;
    stcTmrbOcInit.u16PeriodMatchOutput = TMRB_OC_PERIODMATCH_OUTPUT_INVERTED;
    TMRB_OC_Init(TMRB_UNIT, TMRB_OC_CH, &stcTmrbOcInit);

    /* Configure TimerB capture initialization structure */
    stcTmrbIcInit.u16CaptureCondition = TMRB_IC_FALLING;
    stcTmrbIcInit.u16NoiseFilterClkDiv = TMRB_IC_NOFICLKDIV_NONE;

    /* Initialize TIMERB odd unit input capture function. */
    TMRB_IC_Init(TMRB_UNIT, TMRB_IC_ODD_CH, &stcTmrbIcInit);
    TMRB_IntCmd(TMRB_UNIT, TMRB_IC_ODD_CH_INT_CMP, Enable);

    /* Initialize TIMERB even unit input capture function. */
    TMRB_IC_Init(TMRB_UNIT, TMRB_IC_EVEN_CH, &stcTmrbIcInit);
    TMRB_IntCmd(TMRB_UNIT, TMRB_IC_EVEN_CH_INT_CMP, Enable);

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegiConf.enIRQn = TMRB_CMP_IRQn;
    stcIrqRegiConf.enIntSrc = TMRB_CMP_INT;
    stcIrqRegiConf.pfnCallback = &TMRB_CmpIrqCallback;
    INTC_IrqSignIn(&stcIrqRegiConf);
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    /* Set trigger source. */
    TMRB_SetTriggerSrc(TMRB_UNIT, EVT_TRIG_TMRB_CNT);

    /* Start TIMERB start count condition. */
    TMRB_SetHwStartCondition(TMRB_UNIT, TMRB_HWSTART_EVT);

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
