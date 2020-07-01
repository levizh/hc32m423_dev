/**
 *******************************************************************************
 * @file  emb/emb_sw_brake_timerb/source/main.c
 * @brief This example demonstrates how to use the software brake function of 
 *        EMB function.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-13       Hongjh          First version
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
 * @addtogroup EMB_Software_Brake_Timerb
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief Key state definition
 */
typedef enum
{
    KeyIdle,
    KeyRelease,
} en_key_state_t;

/**
 * @brief Key instance structure definition
 */
typedef struct
{
    uint8_t u8Port;                     /*!< GPIO_PORT_x: x can be (0~7, 12~14) to select the GPIO peripheral */

    uint8_t u8Pin;                      /*!< GPIO_PIN_x: x can be (0~7) to select the PIN index */

    en_pin_state_t enPressPinState;     /*!< Pin level state when key is pressed */
} stc_key_t;

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/* Function clock gate definition */
#define FUNCTION_CLK_GATE               (CLK_FCG_EMB | CLK_FCG_TIMB)

/* Key Port/Pin definition */
#define KEY_PORT                        (GPIO_PORT_D)
#define KEY_PIN                         (GPIO_PIN_7)

/* TIMERB unit */
#define TIMERB_UNIT                     (M4_TMRB)

/* TIMERB channel definition */
#define TIMERB_ODD_CH                   (TIMERB_CH1)
#define TIMERB_EVEN_CH                  (TIMERB_CH2)
#define TIMERB_UNIT_PERIOD_VALUE        (SystemCoreClock/512UL)

/* TIMERB TIMB_t_PWMn(t=1, n=1~4 Port/Pin definition */
#define TIMERB_ODD_CH_PWM_PORT          (GPIO_PORT_7)     /* P72: TIMB_1_PWM1 */
#define TIMERB_ODD_CH_PWM_PIN           (GPIO_PIN_1)
#define TIMERB_ODD_CH_PWM_GPIO_FUNC     (GPIO_FUNC_3_TIMB)
    
#define TIMERB_EVEN_CH_PWM_PORT         (GPIO_PORT_7)     /* P75: TIMB_1_PWM2 */
#define TIMERB_EVEN_CH_PWM_PIN          (GPIO_PIN_5)
#define TIMERB_EVEN_CH_PWM_GPIO_FUNC    (GPIO_FUNC_3_TIMB)


/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static en_key_state_t KeyGetState(const stc_key_t *pstcKey);
static void TimerbPwmConfig(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Configure system clock
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    /* Configure the system clock to HRC32MHz. */
    CLK_HRCInit(CLK_HRC_ON, CLK_HRCFREQ_32);
}

/**
 * @brief  Get key state
 * @param  [in] pstcKey    Pointer to stc_key_t structure
 * @retval An en_result_t enumeration value:
 *           - KeyIdle: Key isn't pressed
 *           - KeyRelease: Released after key is pressed
 */
static en_key_state_t KeyGetState(const stc_key_t *pstcKey)
{
    en_key_state_t enKeyState = KeyIdle;

    DDL_ASSERT(NULL != pstcKey);

    if (pstcKey->enPressPinState == GPIO_ReadInputPortPin(pstcKey->u8Port, pstcKey->u8Pin))
    {
        DDL_Delay1ms(20UL);

        if (pstcKey->enPressPinState == GPIO_ReadInputPortPin(pstcKey->u8Port, pstcKey->u8Pin))
        {
            while (pstcKey->enPressPinState == GPIO_ReadInputPortPin(pstcKey->u8Port, pstcKey->u8Pin))
            {
                ;
            }
            enKeyState = KeyRelease;
        }
    }

    return enKeyState;
}

/**
 * @brief  Configure Timerb PWM
 * @param  None
 * @retval None
 */
static void TimerbPwmConfig(void)
{
    stc_timerb_init_t stcTimerbInit;
    stc_timerb_oc_init_t stcTimerbUnitOcInit = {
        .u16CompareVal = 0U,
        .u16PortOutputState = TIMERB_OC_PORT_OUTPUT_ENABLE,
        .u16StartCntOutput = TIMERB_OC_STARTCNT_OUTPUT_HIGH,
        .u16StopCntOutput = TIMERB_OC_STOPCNT_OUTPUT_HIGH,
        .u16CompareMatchOutput = TIMERB_OC_CMPMATCH_OUTPUT_INVERTED,
        .u16PeriodMatchOutput = TIMERB_OC_PERIODMATCH_OUTPUT_HOLD,
    };

    /* Configure TIM_<t>_PWM1. */
    GPIO_SetFunc(TIMERB_ODD_CH_PWM_PORT, TIMERB_ODD_CH_PWM_PIN, TIMERB_ODD_CH_PWM_GPIO_FUNC);
    GPIO_SetFunc(TIMERB_EVEN_CH_PWM_PORT, TIMERB_EVEN_CH_PWM_PIN, TIMERB_EVEN_CH_PWM_GPIO_FUNC);

    /* Initialize TIMERB odd unit. */
    TIMERB_StructInit(&stcTimerbInit);
    stcTimerbInit.u16PeriodVal = (uint16_t)TIMERB_UNIT_PERIOD_VALUE;
    stcTimerbInit.u16ClkDiv = TIMERB_CLKDIV_DIV512;
    TIMERB_Init(TIMERB_UNIT, &stcTimerbInit);

    /* Initialize TIMERB odd channel output compare function . */
    stcTimerbUnitOcInit.u16CompareVal = (uint16_t)(TIMERB_UNIT_PERIOD_VALUE/2U);
    TIMERB_OC_Init(TIMERB_UNIT, TIMERB_ODD_CH, &stcTimerbUnitOcInit);

    /* Initialize TIMERB even channel output compare function . */
    stcTimerbUnitOcInit.u16CompareVal = (uint16_t)(TIMERB_UNIT_PERIOD_VALUE/2U);
    TIMERB_OC_Init(TIMERB_UNIT, TIMERB_EVEN_CH, &stcTimerbUnitOcInit);
}

/**
 * @brief  Main function of EMB software brake Timerb
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_key_t stcKeySw = {
        .u8Port = KEY_PORT,
        .u8Pin = KEY_PIN,
        .enPressPinState = Pin_Reset,
    };

    /* Configure system clock. */
    SystemClockConfig();

    /* Enable peripheral clock */
    CLK_FcgPeriphClockCmd(FUNCTION_CLK_GATE, Enable);

    /* Configure Timer4 PWM. */
    TimerbPwmConfig();

    /* Start TIMERB counter. */
    TIMERB_Start(TIMERB_UNIT);

    while (1U)
    {
        while (KeyRelease != KeyGetState(&stcKeySw))
        {
            ;
        }

        /* Software start brake signal */
        EMB_SwBrake(Enable);

        while (KeyRelease != KeyGetState(&stcKeySw))
        {
            ;
        }

        /* Software stop brake signal */
        EMB_SwBrake(Disable);
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
