/**
 *******************************************************************************
 * @file  timer4/timer4_pwm_dead_timer_filter_mode/source/main.c
 * @brief This example demonstrates how to use the dead timer filter mode 
 *        function of Timer4 PWM function.
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
 * @addtogroup TIMER4_PWM_Dead_Timer_Filter_Mode
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* TIM4 PWM Port/Pin definition */
#define TIM4_OXH_PORT                   (GPIO_PORT_7)
#define TIM4_OXH_PIN                    (GPIO_PIN_1)
#define TIM4_OXH_GPIO_FUNC              (GPIO_FUNC_2_TIM4)

#define TIM4_OXL_PORT                   (GPIO_PORT_7)
#define TIM4_OXL_PIN                    (GPIO_PIN_4)
#define TIM4_OXL_GPIO_FUNC              (GPIO_FUNC_2_TIM4)

/* Function clock gate definition */
#define FUNCTION_CLK_GATE               (CLK_FCG_TIM4)

/* Timer4 Counter period value && interrupt number definition */
#define TIMER4_CNT_CYCLE_VAL            ((uint16_t)(SystemCoreClock/128UL/2UL))    /* 500 ms */

/* Timer4 OCO Channel definition */
#define TIMER4_OCO_LOW_CH               (TIMER4_OCO_UL)    /* only TIMER4_OCO_UL  TIMER4_OCO_VL  TIMER4_OCO_WL */
#define TIMER4_OCO_OCCR_BUF_SIZE        (4U)

/* Timer4 OCO get interrupt source number definition */
#define TIMER4_OCO_INT_SRC(x)           ((en_int_src_t)((uint32_t)INT_TMR4_GCMUH + ((uint32_t)((x) - TIMER4_OCO_UH))))

/* Timer4 PWM get channel by OCO low channel */
#define TIMER4_PWM_CH(x)                (((x) == TIMER4_OCO_UL) ? TIMER4_PWM_U : \
                                         (((x) == TIMER4_OCO_VL) ? TIMER4_PWM_V : TIMER4_PWM_W))

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void Timer4OcoMatchIrqCb(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_au16OccrVal[TIMER4_OCO_OCCR_BUF_SIZE];

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
    /* Configure the system clock to HRC8MHz. */
    CLK_HRCInit(CLK_HRC_ON, CLK_HRCFREQ_8);
}

/**
 * @brief  TIMER4 OCO match interrupt handler callback.
 * @param  None
 * @retval None
 */
static void Timer4OcoMatchIrqCb(void)
{
    static uint8_t u8CntOcoMatchIrq = 0U;

    if (++u8CntOcoMatchIrq >= TIMER4_OCO_OCCR_BUF_SIZE)
    {
        u8CntOcoMatchIrq = 0U;
    }

    TIMER4_OCO_ClearFlag(TIMER4_OCO_LOW_CH);
    TIMER4_OCO_SetOccrVal(TIMER4_OCO_LOW_CH, m_au16OccrVal[u8CntOcoMatchIrq]);
}

/**
 * @brief  Main function of TIMER4 PWM dead timer filter mode
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t u32PwmCh;
    stc_irq_regi_config_t stcIrqRegiConf;
    stc_timer4_cnt_init_t stcTimer4CntInit;
    stc_timer4_oco_init_t stcTimer4OcoInit;
    stc_timer4_pwm_init_t stcTimer4PwmInit;
    stc_oco_low_ch_compare_mode_t stcLowChCmpMode;

    /* Configure system clock. */
    SystemClockConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNCTION_CLK_GATE, Enable);

    /* Initialize TIMER4 Counter */
    TIMER4_CNT_StructInit(&stcTimer4CntInit);
    stcTimer4CntInit.u16ClkDiv = TIMER4_CNT_CLK_DIV128;
    /* Period_Value(500ms) = SystemClock(SystemCoreClock) / TIMER4_CNT_Clock_Division(128) / Frequency(2) */
    stcTimer4CntInit.u16CycleVal = TIMER4_CNT_CYCLE_VAL;
    TIMER4_CNT_Init(&stcTimer4CntInit);

    /* Initialize TIMER4 OCO high&&low channel */
    m_au16OccrVal[0] = (TIMER4_CNT_CYCLE_VAL / 8U);
    m_au16OccrVal[1] = (TIMER4_CNT_CYCLE_VAL / 4U);
    m_au16OccrVal[2] = (TIMER4_CNT_CYCLE_VAL / 2U);
    m_au16OccrVal[3] = (TIMER4_CNT_CYCLE_VAL / 2U);
    TIMER4_OCO_StructInit(&stcTimer4OcoInit);
    stcTimer4OcoInit.enOcoCmd = Enable;
    stcTimer4OcoInit.enOcoIntCmd = Enable;
    stcTimer4OcoInit.u16OccrVal = m_au16OccrVal[0];
    TIMER4_OCO_Init(TIMER4_OCO_LOW_CH, &stcTimer4OcoInit);

    if (TIMER4_OCO_LOW_CH % 2UL)
    {
        /* OCMR[31:0] 0x0FF0 0FFF = b 0000 1111 1111 0000   0000 1111 1111 1111 */
        stcLowChCmpMode.OCMRx_f.OCFDCL = TIMER4_OCO_OCF_SET;    /* bit[0] 1 */
        stcLowChCmpMode.OCMRx_f.OCFPKL = TIMER4_OCO_OCF_SET;    /* bit[1] 1 */
        stcLowChCmpMode.OCMRx_f.OCFUCL = TIMER4_OCO_OCF_SET;    /* bit[2] 1 */
        stcLowChCmpMode.OCMRx_f.OCFZRL = TIMER4_OCO_OCF_SET;    /* bit[3] 1 */

        stcLowChCmpMode.OCMRx_f.OPDCL = TIMER4_OCO_OP_INVERT;   /* bit[5:4]    11 */
        stcLowChCmpMode.OCMRx_f.OPPKL = TIMER4_OCO_OP_INVERT;   /* bit[7:6]    11 */
        stcLowChCmpMode.OCMRx_f.OPUCL = TIMER4_OCO_OP_INVERT;   /* bit[9:8]    11 */
        stcLowChCmpMode.OCMRx_f.OPZRL = TIMER4_OCO_OP_INVERT;   /* bit[11:10]  11 */
        stcLowChCmpMode.OCMRx_f.OPNPKL = TIMER4_OCO_OP_HOLD;    /* bit[13:12]  00 */
        stcLowChCmpMode.OCMRx_f.OPNZRL = TIMER4_OCO_OP_HOLD;    /* bit[15:14]  00 */
        stcLowChCmpMode.OCMRx_f.EOPNDCL = TIMER4_OCO_OP_HOLD;   /* bit[17:16]  00 */
        stcLowChCmpMode.OCMRx_f.EOPNUCL = TIMER4_OCO_OP_HOLD;   /* bit[19:18]  00 */
        stcLowChCmpMode.OCMRx_f.EOPDCL = TIMER4_OCO_OP_INVERT;  /* bit[21:20]  11 */
        stcLowChCmpMode.OCMRx_f.EOPPKL = TIMER4_OCO_OP_INVERT;  /* bit[23:22]  11 */
        stcLowChCmpMode.OCMRx_f.EOPUCL = TIMER4_OCO_OP_INVERT;  /* bit[25:24]  11 */
        stcLowChCmpMode.OCMRx_f.EOPZRL = TIMER4_OCO_OP_INVERT;  /* bit[27:26]  11 */
        stcLowChCmpMode.OCMRx_f.EOPNPKL = TIMER4_OCO_OP_HOLD;   /* bit[29:28]  00 */
        stcLowChCmpMode.OCMRx_f.EOPNZRL = TIMER4_OCO_OP_HOLD;   /* bit[31:30]  00 */

        stcLowChCmpMode.enExtendMatchCondCmd = Disable;

        TIMER4_OCO_SetLowChCompareMode(TIMER4_OCO_LOW_CH, &stcLowChCmpMode);  /* Set OCO low channel compare mode */
    }

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegiConf.enIRQn = Int000_IRQn;
    stcIrqRegiConf.enIntSrc =TIMER4_OCO_INT_SRC(TIMER4_OCO_LOW_CH);
    stcIrqRegiConf.pfnCallback = &Timer4OcoMatchIrqCb;
    INTC_IrqSignIn(&stcIrqRegiConf);
    NVIC_ClearPendingIRQ(stcIrqRegiConf.enIRQn);
    NVIC_SetPriority(stcIrqRegiConf.enIRQn, DDL_IRQ_PRIORITY_DEFAULT);
    NVIC_EnableIRQ(stcIrqRegiConf.enIRQn);

    /* Initialize PWM I/O */
    GPIO_SetFunc(TIM4_OXH_PORT, TIM4_OXH_PIN, TIM4_OXH_GPIO_FUNC);
    GPIO_SetFunc(TIM4_OXL_PORT, TIM4_OXL_PIN, TIM4_OXL_GPIO_FUNC);

    /* Timer4 PWM: Get pwm couple channel */
    u32PwmCh = TIMER4_PWM_CH(TIMER4_OCO_LOW_CH);

    /* Initialize Timer4 PWM */
    TIMER4_PWM_StructInit(&stcTimer4PwmInit);
    stcTimer4PwmInit.enRtIntMaskCmd = Enable;
    stcTimer4PwmInit.u16ClkDiv = TIMER4_PWM_CLK_DIV128;
    stcTimer4PwmInit.u16Mode = TIMER4_PWM_DEAD_TIMER_FILTER_MODE;
    TIMER4_PWM_Init(u32PwmCh, &stcTimer4PwmInit);
    TIMER4_PWM_SetDeadRegionValue(u32PwmCh, 1U, 1U);
    TIMER4_PWM_SetFilterCountValue(u32PwmCh, (m_au16OccrVal[1] + m_au16OccrVal[2])/2U);

    /* Start TIMER4 counter. */
    TIMER4_CNT_Start();

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
