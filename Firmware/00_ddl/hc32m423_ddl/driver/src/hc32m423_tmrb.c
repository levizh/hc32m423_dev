/**
 *******************************************************************************
 * @file  hc32m423_tmrb.c
 * @brief This file provides firmware functions to manage the TimerB.
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
#include "hc32m423_tmrb.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TIMERB TIMERB
 * @brief TimerB Driver Library
 * @{
 */

#if (DDL_TMRB_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRB_Local_Macros TimerB Local Macros
 * @{
 */

/**
 * @defgroup TMRB_Hardware_Trigger_Condition_Mask TIMERB Hardware Trigger Condition Mask
 * @{
 */
#define TMRB_CCONR_HICP                 (TMRB_CCONR_HICP2 |                    \
                                         TMRB_CCONR_HICP1 |                    \
                                         TMRB_CCONR_HICP0)
#define TMRB_HCONR_HSTA                 (TMRB_HCONR_HSTA2 |                    \
                                         TMRB_HCONR_HSTA1 |                    \
                                         TMRB_HCONR_HSTA0)
#define TMRB_HCONR_HSTP                 (TMRB_HCONR_HSTP2 |                    \
                                         TMRB_HCONR_HSTP1 |                    \
                                         TMRB_HCONR_HSTP0)
#define TMRB_HCONR_HCLE                 (TMRB_HCONR_HCLE6 |                    \
                                         TMRB_HCONR_HCLE5 |                    \
                                         TMRB_HCONR_HCLE2 |                    \
                                         TMRB_HCONR_HCLE1 |                    \
                                         TMRB_HCONR_HCLE0)
#define TMRB_HCUPR_HCUP                 (TMRB_HCUPR_HCUP10 |                   \
                                         TMRB_HCUPR_HCUP9  |                   \
                                         TMRB_HCUPR_HCUP8)
#define TMRB_HCDOR_HCDO                 (TMRB_HCDOR_HCDO10 |                   \
                                         TMRB_HCDOR_HCDO9  |                   \
                                         TMRB_HCDOR_HCDO8)
/**
 * @}
 */

/**
 * @defgroup TMRB_Flag_Mask TIMERB Flag Mask
 * @{
 */
#define TMRB_CNT_FLAG_MASK               (TMRB_FLAG_OVF |                      \
                                          TMRB_FLAG_UDF)

#define TMRB_CMP_FLAG_MASK               (TMRB_FLAG_CMP1 |                     \
                                          TMRB_FLAG_CMP2 |                     \
                                          TMRB_FLAG_CMP3 |                     \
                                          TMRB_FLAG_CMP4 |                     \
                                          TMRB_FLAG_CMP5 |                     \
                                          TMRB_FLAG_CMP6)

#define TMRB_FLAG_MASK                  (TMRB_CNT_FLAG_MASK | TMRB_CMP_FLAG_MASK)
/**
 * @}
 */

/**
 * @defgroup TMRB_Interrupt_Mask TIMERB Interrupt Mask
 * @{
 */
#define TMRB_CNT_INT_MASK               (TMRB_INT_OVF |                        \
                                         TMRB_INT_UDF)

#define TMRB_CMP_INT_MASK               (TMRB_INT_CMP1 |                       \
                                         TMRB_INT_CMP2 |                       \
                                         TMRB_INT_CMP3 |                       \
                                         TMRB_INT_CMP4 |                       \
                                         TMRB_INT_CMP5 |                       \
                                         TMRB_INT_CMP6)

#define TMRB_INT_MASK                   (TMRB_CNT_INT_MASK | TMRB_CMP_INT_MASK)
/**
 * @}
 */

/**
 * @defgroup TMRB_Check_Parameters_Validity TIMERB Check Parameters Validity
 * @{
 */

#define IS_TMRB_INSTANCE(x)                     (M4_TMRB == (x))

#define IS_TMRB_CH(x)                                                          \
(   (TMRB_CH1 == (x))                           ||                             \
    (TMRB_CH2 == (x))                           ||                             \
    (TMRB_CH3 == (x))                           ||                             \
    (TMRB_CH4 == (x))                           ||                             \
    (TMRB_CH5 == (x))                           ||                             \
    (TMRB_CH6 == (x)))

#define IS_TMRB_PWM_CH(x)                                                      \
(   (TMRB_PWM_CH1 == (x))                       ||                             \
    (TMRB_PWM_CH2 == (x))                       ||                             \
    (TMRB_PWM_CH3 == (x))                       ||                             \
    (TMRB_PWM_CH4 == (x)))

#define IS_TMRB_BUF_CH(x)                                                      \
(   (TMRB_BUF_CH12 == (x))                      ||                             \
    (TMRB_BUF_CH34 == (x))                      ||                             \
    (TMRB_BUF_CH56 == (x)))

#define IS_TMRB_CNT_DIRECTION(x)                                               \
(   (TMRB_CNT_UP == (x))                        ||                             \
    (TMRB_CNT_DOWN == (x)))

#define IS_TMRB_CNT_MODE(x)                                                    \
(   (TMRB_SAWTOOTH_WAVE == (x))                 ||                             \
    (TMRB_TRIANGLE_WAVE == (x)))

#define IS_TMRB_CLOCK_DIV(x)                                                   \
(   (TMRB_CLKDIV_DIV1 == (x))                   ||                             \
    (TMRB_CLKDIV_DIV2 == (x))                   ||                             \
    (TMRB_CLKDIV_DIV4 == (x))                   ||                             \
    (TMRB_CLKDIV_DIV8 == (x))                   ||                             \
    (TMRB_CLKDIV_DIV16 == (x))                  ||                             \
    (TMRB_CLKDIV_DIV32 == (x))                  ||                             \
    (TMRB_CLKDIV_DIV64 == (x))                  ||                             \
    (TMRB_CLKDIV_DIV128 == (x))                 ||                             \
    (TMRB_CLKDIV_DIV256 == (x))                 ||                             \
    (TMRB_CLKDIV_DIV512 == (x))                 ||                             \
    (TMRB_CLKDIV_DIV1024 == (x)))

#define IS_TMRB_OVERFLOW_STATE(x)                                              \
(   (TMRB_OVERFLOW_STOP == (x))                 ||                             \
    (TMRB_OVERFLOW_COUNT == (x)))

#define IS_TMRB_FLAG(x)                                                        \
(   !((x) & (uint16_t)(~TMRB_FLAG_MASK)))


#define IS_TMRB_INT(x)                                                         \
(   !((x) & (uint16_t)(~TMRB_INT_MASK)))

#define IS_TMRB_EVT(x)                                                         \
(   (TMRB_EVT_CMP1 == (x))                      ||                             \
    (TMRB_EVT_CMP2 == (x))                      ||                             \
    (TMRB_EVT_CMP3 == (x))                      ||                             \
    (TMRB_EVT_CMP4 == (x))                      ||                             \
    (TMRB_EVT_CMP5 == (x))                      ||                             \
    (TMRB_EVT_CMP6 == (x)))

#define IS_TMRB_CMP_EVT_STATE(x)                                             \
(   (TMRB_CMP_EVT_ENABLE == (x))                ||                             \
    (TMRB_CMP_EVT_DISABLE == (x)))

#define IS_TMRB_IC_NOISE_FILTER_CLKDIV(x)                                      \
(   (TMRB_IC_NOFICLKDIV_NONE == (x))            ||                             \
    (TMRB_IC_NOFICLKDIV_DIV1 == (x))            ||                             \
    (TMRB_IC_NOFICLKDIV_DIV4 == (x))            ||                             \
    (TMRB_IC_NOFICLKDIV_DIV16 == (x))           ||                             \
    (TMRB_IC_NOFICLKDIV_DIV64 == (x)))

#define IS_TMRB_OC_START_CNT_OUTPUT_POLARITY(x)                                \
(   (TMRB_OC_STARTCNT_OUTPUT_LOW == (x))        ||                             \
    (TMRB_OC_STARTCNT_OUTPUT_HIGH == (x))       ||                             \
    (TMRB_OC_STARTCNT_OUTPUT_HOLD == (x)))

#define IS_TMRB_OC_STOP_CNT_OUTPUT_POLARITY(x)                                 \
(   (TMRB_OC_STOPCNT_OUTPUT_LOW == (x))         ||                             \
    (TMRB_OC_STOPCNT_OUTPUT_HIGH == (x))        ||                             \
    (TMRB_OC_STOPCNT_OUTPUT_HOLD == (x)))

#define IS_TMRB_OC_CMPMATCH_OUTPUT_POLARITY(x)                                 \
(   (TMRB_OC_CMPMATCH_OUTPUT_LOW == (x))        ||                             \
    (TMRB_OC_CMPMATCH_OUTPUT_HIGH == (x))       ||                             \
    (TMRB_OC_CMPMATCH_OUTPUT_HOLD == (x))       ||                             \
    (TMRB_OC_CMPMATCH_OUTPUT_INVERTED == (x)))

#define IS_TMRB_OC_PERIODMATCH_OUTPUT_POLARITY(x)                              \
(   (TMRB_OC_PERIODMATCH_OUTPUT_LOW == (x))     ||                             \
    (TMRB_OC_PERIODMATCH_OUTPUT_HIGH == (x))    ||                             \
    (TMRB_OC_PERIODMATCH_OUTPUT_HOLD == (x))    ||                             \
    (TMRB_OC_PERIODMATCH_OUTPUT_INVERTED == (x)))

#define IS_TMRB_OC_FORCE_OUTPUT_POLARITY(x)                                    \
(   (TMRB_OC_FORCE_OUTPUT_LOW == (x))           ||                             \
    (TMRB_OC_FORCE_OUTPUT_HIGH == (x))          ||                             \
    (TMRB_OC_FORCE_OUTPUT_INVALID == (x)))

#define IS_TMRB_OC_PORT_OUTPUT_STATE(x)                                        \
(   (TMRB_OC_PORT_OUTPUT_ENABLE == (x))         ||                             \
    (TMRB_OC_PORT_OUTPUT_DISABLE == (x)))

#define IS_TMRB_IC_CAPTURE_CONDITION(x) ((!((x) & ((uint16_t)(~TMRB_CCONR_HICP)))) || ((x) == TMRB_IC_INVALID))

#define IS_TMRB_HWSTART_CONDITION(x)    ((!((x) & ((uint16_t)(~TMRB_HCONR_HSTA)))) || ((x) == TMRB_HWSTART_INVALID))

#define IS_TMRB_HWSTOP_CONDITION(x)     ((!((x) & ((uint16_t)(~TMRB_HCONR_HSTP)))) || ((x) == TMRB_HWSTOP_INVALID))

#define IS_TMRB_HWCLEAR_CONDITION(x)    ((!((x) & ((uint16_t)(~TMRB_HCONR_HCLE)))) || ((x) == TMRB_HWCLEAR_INVALID))

#define IS_TMRB_HWUP_CONDITION(x)       ((!((x) & ((uint16_t)(~TMRB_HCUPR_HCUP)))) || ((x) == TMRB_HWUP_INVALID))

#define IS_TMRB_HWDOWN_CONDITION(x)     ((!((x) & ((uint16_t)(~TMRB_HCDOR_HCDO)))) || ((x) == TMRB_HWDOWN_INVALID))
/**
 * @}
 */

/**
 * @defgroup TMRB_Function_Mode TimerB Function Mode
 * @{
 */
#define TMRB_INPUT_CAPTURE                  (TMRB_CCONR_CAPMDA)     /*!< Capture input function */
#define TMRB_OUTPUT_COMPARE                 ((uint16_t)0x0000U)     /*!< Comare output function */
/**
 * @}
 */

/**
 * @defgroup TMRB_PWM_Channel TIMERB PWM Channel
 * @{
 */
#define TMRB_PWM_CH1                        (TMRB_CH1)
#define TMRB_PWM_CH2                        (TMRB_CH2)
#define TMRB_PWM_CH3                        (TMRB_CH3)
#define TMRB_PWM_CH4                        (TMRB_CH4)
/**
 * @}
 */

/**
 * @defgroup TMRB_BCONRx_Register TIMERB BCONRx Register(x = 1 ~ 3)
 * @brief Get the specified BCONR register address of the specified TIMERB unit
 * @{
 */
#define TMRB_BCONRx(__TMRBx__, __CH__)      ((__IO uint16_t *)((uint32_t)(&((__TMRBx__)->BCONR1)) + ((uint32_t)(__CH__) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMRB_CMPARx_Register TIMERB CMPARx Register(x = 1 ~ 6)
 * @brief Get the specified CMPAR register address of the specified TIMERB unit
 * @{
 */
#define TMRB_CMPARx(__TMRBx__, __CH__)      ((__IO uint16_t *)((uint32_t)(&((__TMRBx__)->CMPAR1)) + ((uint32_t)(__CH__) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMRB_CCONRx_Register TIMERB CCONRx Register(x = 1 ~ 4)
 * @brief Get the specified CCONR register address of the specified TIMERB unit
 * @{
 */
#define TMRB_CCONRx(__TMRBx__, __CH__)      ((__IO uint16_t *)((uint32_t)(&((__TMRBx__)->CCONR1)) + ((uint32_t)(__CH__) << 2UL)))
/**
 * @}
 */

/**
 * @defgroup TMRB_PCONRx_Register TIMERB PCONRx Register(x = 1 ~ 4)
 * @brief Get the specified PCONR register address of the specified TIMERB unit
 * @{
 */
#define TMRB_PCONRx(__TMRBx__, __CH__)      ((__IO uint16_t *)((uint32_t)(&((__TMRBx__)->PCONR1)) + ((uint32_t)(__CH__) << 2UL)))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static __IO uint32_t* TMRB_TRGSELx(const M4_TMRB_TypeDef *DCUx);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/** 
 * @defgroup TMRB_Global_Functions TimerB Global Functions
 * @{
 */

/**
 * @brief  Initialize TimerB base function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_tmrb_init_t structure (TMRBx unit base function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: TMRBx is invalid instance or pstcInit = NULL
 */
en_result_t TMRB_Init(M4_TMRB_TypeDef *TMRBx, const stc_tmrb_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check pstcInit */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
        DDL_ASSERT(0U != pstcInit->u16PeriodVal);
        DDL_ASSERT(IS_TMRB_CNT_MODE(pstcInit->u16CntMode));
        DDL_ASSERT(IS_TMRB_CLOCK_DIV(pstcInit->u16ClkDiv));
        DDL_ASSERT(IS_TMRB_CNT_DIRECTION(pstcInit->u16CntDir));
        DDL_ASSERT(IS_TMRB_OVERFLOW_STATE(pstcInit->u16OverflowAction));
        DDL_ASSERT(IS_TMRB_HWSTART_CONDITION(pstcInit->u16HwStartCondition));
        DDL_ASSERT(IS_TMRB_HWSTOP_CONDITION(pstcInit->u16HwStopCondition));
        DDL_ASSERT(IS_TMRB_HWCLEAR_CONDITION(pstcInit->u16HwClearCondition));
        DDL_ASSERT(IS_TMRB_HWUP_CONDITION(pstcInit->u16HwUpCondition));
        DDL_ASSERT(IS_TMRB_HWDOWN_CONDITION(pstcInit->u16HwDownCondition));

        WRITE_REG16(TMRBx->CNTER, 0U);
        WRITE_REG16(TMRBx->PERAR, pstcInit->u16PeriodVal);
        MODIFY_REG16(TMRBx->BCSTR,                                             \
                     (TMRB_BCSTR_DIR   | TMRB_BCSTR_MODE |                     \
                      TMRB_BCSTR_CKDIV | TMRB_BCSTR_OVSTP),                    \
                     (pstcInit->u16CntDir | pstcInit->u16CntMode |             \
                      pstcInit->u16ClkDiv | pstcInit->u16OverflowAction));

        /* Set hardware trigger event */
        WRITE_REG16(TMRBx->HCONR,                                              \
                    (pstcInit->u16HwStartCondition |                           \
                     pstcInit->u16HwStopCondition  |                           \
                     pstcInit->u16HwClearCondition));
        WRITE_REG16(TMRBx->HCUPR, pstcInit->u16HwUpCondition);
        WRITE_REG16(TMRBx->HCDOR, pstcInit->u16HwDownCondition);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmrb_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_tmrb_init_t structure (TMRBx unit base function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t TMRB_StructInit(stc_tmrb_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcInit)
    {
        pstcInit->u16PeriodVal = 0xFFFFU;
        pstcInit->u16CntDir = TMRB_CNT_UP;
        pstcInit->u16CntMode = TMRB_SAWTOOTH_WAVE;
        pstcInit->u16ClkDiv = TMRB_CLKDIV_DIV1;
        pstcInit->u16OverflowAction = TMRB_OVERFLOW_COUNT;
        pstcInit->u16HwStartCondition = TMRB_HWSTART_INVALID;
        pstcInit->u16HwStopCondition = TMRB_HWSTOP_INVALID;
        pstcInit->u16HwClearCondition = TMRB_HWCLEAR_INVALID;
        pstcInit->u16HwUpCondition = TMRB_HWUP_INVALID;
        pstcInit->u16HwDownCondition = TMRB_HWDOWN_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize TimerB unit base function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 *           - ErrorInvalidParameter: TMRBx is invalid instance
 */
en_result_t TMRB_DeInit(M4_TMRB_TypeDef *TMRBx)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check TMRBx instance */
    if (IS_TMRB_INSTANCE(TMRBx))
    {
        /* Configures the registers to reset value. */
        WRITE_REG16(TMRBx->CNTER, 0x0000U);
        WRITE_REG16(TMRBx->PERAR, 0xFFFFU);
        WRITE_REG16(TMRBx->BCSTR, 0x0002U);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set TimerB count direction.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Direction            TimerB count direction
 *         This parameter can be one of the following values:
 *           @arg TMRB_CNT_UP:          TimerB count up
 *           @arg TMRB_CNT_DOWN:        TimerB count down
 * @retval None
 */
void TMRB_SetCntDirection(M4_TMRB_TypeDef *TMRBx, uint16_t u16Direction)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_DIRECTION(u16Direction));

    MODIFY_REG16(TMRBx->BCSTR, TMRB_BCSTR_DIR, u16Direction);
}

/**
 * @brief  Get TimerB count direction.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_CNT_UP:          TimerB count up
 *           @arg TMRB_CNT_DOWN:        TimerB count down
 */
uint16_t TMRB_GetCntDirection(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_DIR);
}

/**
 * @brief  Set TimerB count mode.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Mode                 TimerB count mode
 *         This parameter can be one of the following values:
 *           @arg TMRB_TRIANGLE_WAVE:   TimerB triangle wave mode
 *           @arg TMRB_SAWTOOTH_WAVE:   TimerB sawtooth wave mode
 * @retval None
 */
void TMRB_SetCntMode(M4_TMRB_TypeDef *TMRBx, uint16_t u16Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_CNT_MODE(u16Mode));

    MODIFY_REG16(TMRBx->BCSTR, TMRB_BCSTR_MODE, u16Mode);
}

/**
 * @brief  Get TimerB count mode.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_TRIANGLE_WAVE:   TimerB triangle wave mode
 *           @arg TMRB_SAWTOOTH_WAVE:   TimerB sawtooth wave mode
 */
uint16_t TMRB_GetCntMode(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_MODE);
}

/**
 * @brief  Set TimerB clock division.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Div                  TimerB clock division
 *         This parameter can be one of the following values:
 *           @arg TMRB_CLKDIV_DIV1:     HCLK
 *           @arg TMRB_CLKDIV_DIV2:     HCLK/2
 *           @arg TMRB_CLKDIV_DIV4:     HCLK/4
 *           @arg TMRB_CLKDIV_DIV8:     HCLK/8
 *           @arg TMRB_CLKDIV_DIV16:    HCLK/16
 *           @arg TMRB_CLKDIV_DIV32:    HCLK/32
 *           @arg TMRB_CLKDIV_DIV64:    HCLK/64
 *           @arg TMRB_CLKDIV_DIV128:   HCLK/128
 *           @arg TMRB_CLKDIV_DIV256:   HCLK/256
 *           @arg TMRB_CLKDIV_DIV512:   HCLK/512
 *           @arg TMRB_CLKDIV_DIV1024:  HCLK/1024
 * @retval None
 */
void TMRB_SetClkDiv(M4_TMRB_TypeDef *TMRBx, uint16_t u16Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_CLOCK_DIV(u16Div));

    MODIFY_REG16(TMRBx->BCSTR, TMRB_BCSTR_CKDIV, u16Div);
}

/**
 * @brief  Get TimerB clock division.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_CLKDIV_DIV1:     HCLK
 *           @arg TMRB_CLKDIV_DIV2:     HCLK/2
 *           @arg TMRB_CLKDIV_DIV4:     HCLK/4
 *           @arg TMRB_CLKDIV_DIV8:     HCLK/8
 *           @arg TMRB_CLKDIV_DIV16:    HCLK/16
 *           @arg TMRB_CLKDIV_DIV32:    HCLK/32
 *           @arg TMRB_CLKDIV_DIV64:    HCLK/64
 *           @arg TMRB_CLKDIV_DIV128:   HCLK/128
 *           @arg TMRB_CLKDIV_DIV256:   HCLK/256
 *           @arg TMRB_CLKDIV_DIV512:   HCLK/512
 *           @arg TMRB_CLKDIV_DIV1024:  HCLK/1024
 */
uint16_t TMRB_GetClkDiv(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->BCSTR, TMRB_BCSTR_CKDIV);
}

/**
 * @brief  Get TimerB flag status.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Flag                 TimerB flag type
 *         This parameter can be one of the following values:
 *           @arg TMRB_FLAG_OVF:        Overflow flag
 *           @arg TMRB_FLAG_UDF:        Underflow flag
 *           @arg TMRB_FLAG_CMP1:       Channel1 compare match flag
 *           @arg TMRB_FLAG_CMP2:       Channel2 compare match flag
 *           @arg TMRB_FLAG_CMP3:       Channel3 compare match flag
 *           @arg TMRB_FLAG_CMP4:       Channel4 compare match flag
 *           @arg TMRB_FLAG_CMP5:       Channel5 compare match flag
 *           @arg TMRB_FLAG_CMP6:       Channel6 compare match flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t TMRB_GetFlag(const M4_TMRB_TypeDef *TMRBx, uint16_t u16Flag)
{
    uint16_t u16CntFlag = (u16Flag & TMRB_CNT_FLAG_MASK);
    uint16_t u16CmpFlag = (u16Flag & TMRB_CMP_FLAG_MASK);
    en_flag_status_t enCntStatus = Reset;
    en_flag_status_t enCmpStatus = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_FLAG(u16Flag));

    if (u16CntFlag == READ_REG16_BIT(TMRBx->BCSTR, u16CntFlag))
    {
        enCntStatus = Set;
    }

    if (u16CmpFlag == READ_REG16_BIT(TMRBx->STFLR, u16CmpFlag))
    {
        enCmpStatus = Set;
    }

    return (enCntStatus && enCmpStatus) ? Set : Reset;
}

/**
 * @brief  Clear TimerB flag.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Flag                 TimerB flag type
 *         This parameter can be one of the following values:
 *           @arg TMRB_FLAG_OVF:        Overflow flag
 *           @arg TMRB_FLAG_UDF:        Underflow flag
 *           @arg TMRB_FLAG_CMP1:       Channel1 compare match flag
 *           @arg TMRB_FLAG_CMP2:       Channel2 compare match flag
 *           @arg TMRB_FLAG_CMP3:       Channel3 compare match flag
 *           @arg TMRB_FLAG_CMP4:       Channel4 compare match flag
 *           @arg TMRB_FLAG_CMP5:       Channel5 compare match flag
 *           @arg TMRB_FLAG_CMP6:       Channel6 compare match flag
 * @retval None
 */
void TMRB_ClearFlag(M4_TMRB_TypeDef *TMRBx, uint16_t u16Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_FLAG(u16Flag));

    if (u16Flag & TMRB_CNT_FLAG_MASK)
    {
        CLEAR_REG16_BIT(TMRBx->BCSTR, (u16Flag & TMRB_CNT_FLAG_MASK));
    }

    if (u16Flag & TMRB_CMP_FLAG_MASK)
    {
        CLEAR_REG16_BIT(TMRBx->STFLR, (u16Flag & TMRB_CMP_FLAG_MASK));
    }
}

/**
 * @brief  Enable or disable specified TimerB interrupt.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16IntSource            TimerB interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMRB_INT_OVF:         Overflow interrupt
 *           @arg TMRB_INT_UDF:         Underflow interrupt
 *           @arg TMRB_INT_CMP1:        Channel 1 compare match interrupt
 *           @arg TMRB_INT_CMP2:        Channel 2 compare match interrupt
 *           @arg TMRB_INT_CMP3:        Channel 3 compare match interrupt
 *           @arg TMRB_INT_CMP4:        Channel 4 compare match interrupt
 *           @arg TMRB_INT_CMP5:        Channel 5 compare match interrupt
 *           @arg TMRB_INT_CMP6:        Channel 6 compare match interrupt
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRB_IntCmd(M4_TMRB_TypeDef *TMRBx,
                    uint16_t u16IntSource,
                    en_functional_state_t enNewState)
{
    uint16_t u16CntIntSource = (u16IntSource & TMRB_CNT_INT_MASK);
    uint16_t u16CmpIntSource = (u16IntSource & TMRB_CMP_INT_MASK);

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_INT(u16IntSource));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG16_BIT(TMRBx->BCSTR, u16CntIntSource);
        SET_REG16_BIT(TMRBx->ICONR, u16CmpIntSource);
    }
    else
    {
        CLEAR_REG16_BIT(TMRBx->BCSTR, u16CntIntSource);
        CLEAR_REG16_BIT(TMRBx->ICONR, u16CmpIntSource);
    }
}

/**
 * @brief  Enable/disable TimerB event function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16IntSource            TimerB interrupt source
 *         This parameter can be one of the following values:
 *           @arg TMRB_EVT_CMP1:        Channel 1 compare match/capture event
 *           @arg TMRB_EVT_CMP2:        Channel 2 compare match/capture event
 *           @arg TMRB_EVT_CMP3:        Channel 3 compare match/capture event
 *           @arg TMRB_EVT_CMP4:        Channel 4 compare match/capture event
 *           @arg TMRB_EVT_CMP5:        Channel 5 compare match/capture event
 *           @arg TMRB_EVT_CMP6:        Channel 6 compare match/capture event
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRB_EventCmd(M4_TMRB_TypeDef *TMRBx,
                            uint32_t u32EvtSource,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_EVT(u32EvtSource));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG16(TMRBx->ECONR, u32EvtSource, (Enable == enNewState) ? u32EvtSource : 0U);
}

/**
 * @brief Set the specified event trigger source for TMRB.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param [in] enEventSrc               The trigger external event source source.
 *           @arg This parameter can be any value of @ref en_event_src_t
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: TMRBx is invalid
 */
en_result_t TMRB_SetTriggerSrc(const M4_TMRB_TypeDef *TMRBx,
                                    en_event_src_t enEventSrc)
{
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint32_t *TRGSELx = TMRB_TRGSELx(TMRBx);

    if (NULL != TRGSELx)
    {
        WRITE_REG32(*TRGSELx, ((uint32_t)enEventSrc) & 0x1FFUL);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set TimerB hardware trigger counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Condition            TimerB hardware start counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg @ref TMRB_Hardware_Start_Count_Condition
 *           @arg @ref TMRB_Hardware_Stop_Count_Condition
 *           @arg @ref TMRB_Hardware_Clear_Count_Condition
 * @retval  None
 */
void TMRB_SetHwTriggerCondition(M4_TMRB_TypeDef *TMRBx,
                                        uint16_t u16Condition)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    WRITE_REG16(TMRBx->HCONR, u16Condition);
}

/**
 * @brief  Set TimerB hardware start counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Condition            TimerB hardware start counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_HWSTART_INVALID:             Hardware start is invalid
 *           @arg TMRB_HWSTART_TIMB_T_PWM1_RISING:  Hardware start counter by rising edge on timer input TIMB_<t>_PWM1 (t = 1~8) when sysnc start function is invalid or
 *                                                  hardware start counter by rising edge on timer input TIMB_n_PWM1 (n = 1,3,5,7) when sysnc start function is invalid
 *           @arg TMRB_HWSTART_TIMB_T_PWM1_FALLING: Hardware start counter by falling edge on timer input TIMB_<t>_PWM1 (t = 1~8) when sysnc start function is invalid or
 *                                                  hardware start counter by falling edge on timer input TIMB_n_PWM1 (n = 1,3,5,7) when sysnc start function is invalid
 *           @arg TMRB_HWSTART_EVT:                 Hardware start counter by the timer TMRB_HTSSR specified event
 * @retval  None
 */
void TMRB_SetHwStartCondition(M4_TMRB_TypeDef *TMRBx,
                                        uint16_t u16Condition)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_HWSTART_CONDITION(u16Condition));

    MODIFY_REG16(TMRBx->HCONR, TMRB_HCONR_HSTA, u16Condition);
}

/**
 * @brief  Get TimerB hardware start counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be any composed value of the following values:
 *           @arg TMRB_HWSTART_INVALID:             Hardware start is invalid
 *           @arg TMRB_HWSTART_TIMB_T_PWM1_RISING:  Hardware start counter by rising edge on timer input TIMB_<t>_PWM1 (t = 1~8) when sysnc start function is invalid or
 *                                                  hardware start counter by rising edge on timer input TIMB_n_PWM1 (n = 1,3,5,7) when sysnc start function is invalid
 *           @arg TMRB_HWSTART_TIMB_T_PWM1_FALLING: Hardware start counter by falling edge on timer input TIMB_<t>_PWM1 (t = 1~8) when sysnc start function is invalid or
 *                                                  hardware start counter by falling edge on timer input TIMB_n_PWM1 (n = 1,3,5,7) when sysnc start function is invalid
 *           @arg TMRB_HWSTART_EVT:                 Hardware start counter by the timer TMRB_HTSSR specified event
 */
uint16_t TMRB_GetHwStartCondition(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->HCONR, TMRB_HCONR_HSTA);
}

/**
 * @brief  Set TimerB hardware stop counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Condition            TimerB hardware stop counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_HWSTOP_INVALID:              Hardware stop is invalid
 *           @arg TMRB_HWSTOP_TIMB_T_PWM1_RISING:   Hardware stop counter by rising edge on timer input TIMB_<t>_PWM1 (t = 1~8)
 *           @arg TMRB_HWSTOP_TIMB_T_PWM1_FALLING:  Hardware stop counter by falling edge on timer input TIMB_<t>_PWM1 (t = 1~8)
 *           @arg TMRB_HWSTOP_EVT:                  Hardware stop counter by the timer TMRB_HTSSR specified event
 * @retval  None
 */
void TMRB_SetHwStopCondition(M4_TMRB_TypeDef *TMRBx,
                                        uint16_t u16Condition)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_HWSTOP_CONDITION(u16Condition));

    MODIFY_REG16(TMRBx->HCONR, TMRB_HCONR_HSTP, u16Condition);
}

/**
 * @brief  Get TimerB hardware stop counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be any composed value of the following values:
 *           @arg TMRB_HWSTOP_INVALID:              Hardware stop is invalid
 *           @arg TMRB_HWSTOP_TIMB_T_PWM1_RISING:   Hardware stop counter by rising edge on timer input TIMB_<t>_PWM1 (t = 1~8)
 *           @arg TMRB_HWSTOP_TIMB_T_PWM1_FALLING:  Hardware stop counter by falling edge on timer input TIMB_<t>_PWM1 (t = 1~8)
 *           @arg TMRB_HWSTOP_EVT:                  Hardware stop counter by the timer TMRB_HTSSR specified event
 */
uint16_t TMRB_GetHwStopCondition(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->HCONR, TMRB_HCONR_HSTP);
}

/**
 * @brief  Set TimerB hardware clear counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Condition            TimerB hardware clear counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_HWCLEAR_INVALID:             Hardware clear is invalid
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM1_RISING:  Hardware clear counter by rising edge on timer input TIMB_<t>_PWM1 (t = 1)
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM1_FALLING: Hardware clear counter by falling edge on timer input TIMB_<t>_PWM1 (t = 1)
 *           @arg TMRB_HWCLEAR_EVT:                 Hardware clear counter by the timer TMRB_HTSSR specified event
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM3_RISING:  Hardware clear count by rising edge on timer input TIMB_<t>_PWM3 (t = 1)
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM3_FALLING: Hardware clear count by falling edge on timer input TIMB_<t>_PWM3 (t = 1)
 * @retval  None
 */
void TMRB_SetHwClearCondition(M4_TMRB_TypeDef *TMRBx,
                                        uint16_t u16Condition)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_HWCLEAR_CONDITION(u16Condition));

    MODIFY_REG16(TMRBx->HCONR, TMRB_HCONR_HCLE, u16Condition);
}

/**
 * @brief  Get TimerB hardware clear counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be any composed value of the following values:
 *           @arg TMRB_HWCLEAR_INVALID:             Hardware clear is invalid
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM1_RISING:  Hardware clear counter by rising edge on timer input TIMB_<t>_PWM1 (t = 1~8)
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM1_FALLING: Hardware clear counter by falling edge on timer input TIMB_<t>_PWM1 (t = 1~8)
 *           @arg TMRB_HWCLEAR_EVT:                 Hardware clear counter by the timer TMRB_HTSSR specified event
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM3_RISING:  Hardware clear count by rising edge on timer input TIMB_<t>_PWM3 (t = 1)
 *           @arg TMRB_HWCLEAR_TIMB_T_PWM3_FALLING: Hardware clear count by falling edge on timer input TIMB_<t>_PWM3 (t = 1)
 */
uint16_t TMRB_GetHwClearCondition(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->HCONR, TMRB_HCONR_HCLE);
}

/**
 * @brief  Set TimerB hardware up counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Condition            TimerB hardware up counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_HWUP_INVALID:            Hardware count up is invalid
 *           @arg TMRB_HWUP_TIMB_T_PWM1_RISING: Hardware count up by rising edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWUP_TIMB_T_PWM1_FALLING:Hardware count up by falling edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWUP_EVT:                Hardware count up by the timer TMRB_HTSSR specified event
 * @retval  None
 */
void TMRB_SetHwUpCondition(M4_TMRB_TypeDef *TMRBx,
                                    uint16_t u16Condition)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_HWUP_CONDITION(u16Condition));

    MODIFY_REG16(TMRBx->HCUPR, TMRB_HCUPR_HCUP, u16Condition);
}

/**
 * @brief  Get TimerB hardware up counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be any composed value of the following values:
 *           @arg TMRB_HWUP_INVALID:            Hardware count up is invalid
 *           @arg TMRB_HWUP_TIMB_T_PWM1_RISING: Hardware count up by rising edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWUP_TIMB_T_PWM1_FALLING:Hardware count up by falling edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWUP_EVT:                Hardware count up by the timer TMRB_HTSSR specified event
 */
uint16_t TMRB_GetHwUpCondition(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->HCUPR, TMRB_HCUPR_HCUP);
}

/**
 * @brief  Set TimerB hardware down counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u16Condition            TimerB hardware down counter condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_HWDOWN_INVALID:             Hardware count down is invalid
 *           @arg TMRB_HWDOWN_TIMB_T_PWM1_RISING:  Hardware count down by rising edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWDOWN_TIMB_T_PWM1_FALLING: Hardware count down by falling edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWDOWN_EVT:                 Hardware count down by the timer TMRB_HTSSR specified event
 * @retval  None
 */
void TMRB_SetHwDownCondition(M4_TMRB_TypeDef *TMRBx,
                                        uint16_t u16Condition)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_HWDOWN_CONDITION(u16Condition));

    MODIFY_REG16(TMRBx->HCDOR, TMRB_HCDOR_HCDO, u16Condition);
}

/**
 * @brief  Get TimerB hardware down counter condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval Returned value can be any composed value of the following values:
 *           @arg TMRB_HWDOWN_INVALID:             Hardware count down is invalid
 *           @arg TMRB_HWDOWN_TIMB_T_PWM1_RISING:  Hardware count down by rising edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWDOWN_TIMB_T_PWM1_FALLING: Hardware count down by falling edge on timer input TIMB_<t>_PWM1, t = 1~8
 *           @arg TMRB_HWDOWN_EVT:                 Hardware count down by the timer TMRB_HTSSR specified event
 */
uint16_t TMRB_GetHwDownCondition(const M4_TMRB_TypeDef *TMRBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    return READ_REG16_BIT(TMRBx->HCDOR, TMRB_HCDOR_HCDO);
}

/**
 * @brief  Set TimerB triangle wave buffer mode.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32BufCh                TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_BUF_CH12:        TimerB channel 1
 *           @arg TMRB_BUF_CH34:        TimerB channel 2
 *           @arg TMRB_BUF_CH56:        TimerB channel 3
 * @param  [in] u16Mode                 TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_TRIANGLE_WAVE_BUF_PEAK:  Transfer buffer value when TimerB count peak
 *           @arg TMRB_TRIANGLE_WAVE_BUF_ZERO:  Transfer buffer value when TimerB count zero
 * @retval None
 */
 void TMRB_SetTriangleWaveBufMode(M4_TMRB_TypeDef *TMRBx,
                                    uint32_t u32BufCh,
                                    uint16_t u16Mode)
{
    __IO uint16_t *TMRB_BCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_BUF_CH(u32BufCh));
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    TMRB_BCONR = TMRB_BCONRx(TMRBx, u32BufCh);
    MODIFY_REG16(*TMRB_BCONR, (TMRB_BCONR_BSE0 | TMRB_BCONR_BSE1), u16Mode);
}

/**
 * @brief  Set TimerB compare register value.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 *           @arg TMRB_CH5:             TimerB channel 5
 *           @arg TMRB_CH6:             TimerB channel 6
 * @param  [in] u16Value Compare value (between Min_Data=0 and Max_Data=0xFFFF)
 * @retval None
 */
void TMRB_SetCompare(M4_TMRB_TypeDef *TMRBx,
                                uint32_t u32Ch,
                                uint16_t u16Value)
{
    __IO uint16_t *TMRB_CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);
    WRITE_REG16(*TMRB_CMPAR, u16Value);
}

/**
 * @brief  Get TimerB compare register value.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 *           @arg TMRB_CH5:             TimerB channel 5
 *           @arg TMRB_CH6:             TimerB channel 6
 * @retval Compare value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t TMRB_GetCompare(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_CMPAR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));

    TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);
    return READ_REG16(*TMRB_CMPAR);
}

/**
 * @brief  Enable/disable TimerB buffer function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_BUF_CH12:        TimerB channel 1
 *           @arg TMRB_BUF_CH34:        TimerB channel 2
 *           @arg TMRB_BUF_CH56:        TimerB channel 3
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void TMRB_BufCmd(M4_TMRB_TypeDef *TMRBx,
                        uint32_t u32BufCh,
                        en_functional_state_t enNewState)
{
    __IO uint16_t *TMRB_BCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_BUF_CH(u32BufCh));
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    TMRB_BCONR = TMRB_BCONRx(TMRBx, u32BufCh);
    MODIFY_REG16(*TMRB_BCONR, TMRB_BCONR_BEN, (Enable == enNewState) ? TMRB_BCONR_BEN : 0U);
}

/**
 * @brief  Initialize TimerB input capture function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] pstcIcInit              Pointer to a @ref stc_tmrb_ic_init_t structure (TMRBx unit input capture function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: TMRBx is invalid instance or pstcIcInit == NULL
 * @note TimerB channel 5&6 don't support this function.
 */
en_result_t TMRB_IC_Init(M4_TMRB_TypeDef *TMRBx,
                            uint32_t u32Ch,
                            const stc_tmrb_ic_init_t *pstcIcInit)
{
    __IO uint16_t *TMRB_CCONR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check TMRBx instance and pstcIcInit */
    if (NULL != pstcIcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
        DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
        DDL_ASSERT(IS_TMRB_IC_CAPTURE_CONDITION(pstcIcInit->u16CaptureCondition));
        DDL_ASSERT(IS_TMRB_IC_NOISE_FILTER_CLKDIV(pstcIcInit->u16NoiseFilterClkDiv));

        TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);

        MODIFY_REG16(*TMRB_CCONR,                                              \
                     (TMRB_CCONR_CAPMDA   | TMRB_CCONR_HICP |                  \
                      TMRB_CCONR_NOFIENCP | TMRB_CCONR_NOFICKCP),              \
                     (TMRB_INPUT_CAPTURE              |                        \
                      pstcIcInit->u16CaptureCondition |                        \
                      pstcIcInit->u16NoiseFilterClkDiv));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmrb_ic_init_t to default values.
 * @param  [out] pstcIcInit             Pointer to a @ref stc_tmrb_ic_init_t structure (TMRBx unit input capture function configuration data structure).
 * @retval None
 */
en_result_t TMRB_IC_StructInit(stc_tmrb_ic_init_t *pstcIcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcIcInit)
    {
        pstcIcInit->u16NoiseFilterClkDiv = TMRB_IC_NOFICLKDIV_NONE;
        pstcIcInit->u16CaptureCondition = TMRB_IC_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize TimerB unit input capture.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 *           - ErrorInvalidParameter: TMRBx is invalid instance
 * @note TimerB channel 5&6 don't support this function.
 */
en_result_t TMRB_IC_DeInit(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_CCONR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check TMRBx instance */
    if (IS_TMRB_INSTANCE(TMRBx))
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

        TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);

        /* Configures the registers to reset value. */
        WRITE_REG16(TMRBx->PERAR, 0xFFFFU);
        WRITE_REG16(*TMRB_CCONR, 0x0001U);
        WRITE_REG16(TMRBx->HCONR, 0x0000U);
        WRITE_REG16(TMRBx->HCUPR, 0x0000U);
        WRITE_REG16(TMRBx->HCDOR, 0x0000U);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set TimerB input capture condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Condition            TimerB input capture condition
 *         This parameter can be any composed value of the following values:
 *           @arg TMRB_IC_RISING:       Capture triggered by rising edge on timer input TIMB_<t>_PWMn(t=1,n=1~4)
 *           @arg TMRB_IC_FALLING:      Capture triggered by falling edge on timer input TIMB_<t>_PWMn(t=1,n=1~4)
 *           @arg TMRB_IC_EVT:          Capture triggered by the timer TMRB_HTSSR specified event
 *           @arg TMRB_IC_INVALID:      Don't occur capture action
 * @retval None
 * @note TimerB channel 5&6 don't support this function.
 */
void TMRB_IC_SetCaptureCondition(M4_TMRB_TypeDef *TMRBx,
                                        uint32_t u32Ch,
                                        uint16_t u16Condition)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_IC_CAPTURE_CONDITION(u16Condition));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_CCONR, TMRB_CCONR_HICP, u16Condition);
}

/**
 * @brief  Get TimerB input capture condition.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be any composed value of the following values:
 *           @arg TMRB_IC_RISING:       Capture triggered by rising edge on timer input TIMB_<t>_PWMn(t=1,n=1~4)
 *           @arg TMRB_IC_FALLING:      Capture triggered by falling edge on timer input TIMB_<t>_PWMn(t=1,n=1~4)
 *           @arg TMRB_IC_EVT:          Capture triggered by the timer TMRB_HTSSR specified event
 *           @arg TMRB_IC_INVALID:      Don't occur capture action
 * @note TimerB channel 5&6 don't support this function.
 */
uint16_t TMRB_IC_GetCaptureCondition(M4_TMRB_TypeDef *TMRBx,
                                            uint32_t u32Ch)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_CCONR, TMRB_CCONR_HICP);
}

/**
 * @brief  Set TimerB input capture noise filter clock division.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Div                  TimerB input capture noise filter clock division
 *         This parameter can be one of the following values:
 *           @arg TMRB_IC_NOFICLKDIV_NONE:    Disable filter
 *           @arg TMRB_IC_NOFICLKDIV_DIV1:    HCLK
 *           @arg TMRB_IC_NOFICLKDIV_DIV4:    HCLK/4
 *           @arg TMRB_IC_NOFICLKDIV_DIV16:   HCLK/16
 *           @arg TMRB_IC_NOFICLKDIV_DIV64:   HCLK/64
 * @note TimerB channel 5&6 don't support this function.
 * @retval None
 */
void TMRB_IC_SetFilterClkDiv(M4_TMRB_TypeDef *TMRBx,
                                    uint32_t u32Ch,
                                    uint16_t u16Div)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_IC_NOISE_FILTER_CLKDIV(u16Div));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_CCONR, (TMRB_CCONR_NOFIENCP | TMRB_CCONR_NOFICKCP), u16Div);
}

/**
 * @brief  Get TimerB input capture noise filter clock division.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_IC_NOFICLKDIV_NONE:    Disable filter
 *           @arg TMRB_IC_NOFICLKDIV_DIV1:    HCLK
 *           @arg TMRB_IC_NOFICLKDIV_DIV4:    HCLK/4
 *           @arg TMRB_IC_NOFICLKDIV_DIV16:   HCLK/16
 *           @arg TMRB_IC_NOFICLKDIV_DIV64:   HCLK/64
 * @note TimerB channel 5&6 don't support this function.
 */
uint16_t TMRB_IC_GetFilterClkDiv(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_CCONR, (TMRB_CCONR_NOFIENCP | TMRB_CCONR_NOFICKCP));
}

/**
 * @brief  Enable TimerB input capture noise filter function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval None
 * @note TimerB channel 5&6 don't support this function.
 */
void TMRB_IC_EnableNoiseFilter(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    SET_REG16_BIT(*TMRB_CCONR, TMRB_CCONR_NOFIENCP);
}

/**
 * @brief  Disable TimerB input capture noise filter function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval None
 * @note TimerB channel 5&6 don't support this function.
 */
void TMRB_IC_DisableNoiseFilter(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_CCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_CCONR = TMRB_CCONRx(TMRBx, u32Ch);
    CLEAR_REG16_BIT(*TMRB_CCONR, TMRB_CCONR_NOFIENCP);
}

/**
 * @brief  Initialize TimerB output compare function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] pstcOcInit              Pointer to a @ref stc_tmrb_oc_init_t structure (TMRBx unit output compare function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcOcInit == NULL
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
en_result_t TMRB_OC_Init(M4_TMRB_TypeDef *TMRBx,
                            uint32_t u32Ch,
                            const stc_tmrb_oc_init_t *pstcOcInit)
{
    __IO uint16_t *TMRB_PCONR = NULL;
    __IO uint16_t *TMRB_CMPAR = NULL;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check TMRBx instance and pstcOcInit */
    if (NULL != pstcOcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
        DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
        DDL_ASSERT(IS_TMRB_OC_PORT_OUTPUT_STATE(pstcOcInit->u16PortOutputState));
        DDL_ASSERT(IS_TMRB_OC_START_CNT_OUTPUT_POLARITY(pstcOcInit->u16StartCntOutput));
        DDL_ASSERT(IS_TMRB_OC_STOP_CNT_OUTPUT_POLARITY(pstcOcInit->u16StopCntOutput));
        DDL_ASSERT(IS_TMRB_OC_CMPMATCH_OUTPUT_POLARITY(pstcOcInit->u16CompareMatchOutput));
        DDL_ASSERT(IS_TMRB_OC_PERIODMATCH_OUTPUT_POLARITY(pstcOcInit->u16PeriodMatchOutput));

        TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
        TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);

        WRITE_REG16(*TMRB_CMPAR, pstcOcInit->u16CompareVal);
        WRITE_REG16(*TMRB_PCONR,                                               \
                    (pstcOcInit->u16StartCntOutput     |                       \
                     pstcOcInit->u16StopCntOutput      |                       \
                     pstcOcInit->u16CompareMatchOutput |                       \
                     pstcOcInit->u16PeriodMatchOutput  |                       \
                     pstcOcInit->u16PortOutputState));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_tmrb_oc_init_t to default values.
 * @param  [out] pstcOcInit             Pointer to a @ref stc_tmrb_oc_init_t structure (TMRBx unit output compare function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcOcInit == NULL
 */
en_result_t TMRB_OC_StructInit(stc_tmrb_oc_init_t *pstcOcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcOcInit)
    {
        pstcOcInit->u16CompareVal = 0xFFFFU;
        pstcOcInit->u16PortOutputState = TMRB_OC_PORT_OUTPUT_DISABLE;
        pstcOcInit->u16StartCntOutput = TMRB_OC_STARTCNT_OUTPUT_LOW;
        pstcOcInit->u16StopCntOutput = TMRB_OC_STOPCNT_OUTPUT_LOW;
        pstcOcInit->u16CompareMatchOutput = TMRB_OC_CMPMATCH_OUTPUT_LOW;
        pstcOcInit->u16PeriodMatchOutput = TMRB_OC_PERIODMATCH_OUTPUT_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize TimerB unit output compare.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 *           - ErrorInvalidParameter: TMRBx is invalid instance
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
en_result_t TMRB_OC_DeInit(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;
    __IO uint16_t *TMRB_CMPAR;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check TMRBx instance */
    if (IS_TMRB_INSTANCE(TMRBx))
    {
        DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

        TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
        TMRB_CMPAR = TMRB_CMPARx(TMRBx, u32Ch);

        /* Configures the registers to reset value. */
        WRITE_REG16(*TMRB_PCONR, 0x0000U);
        WRITE_REG16(TMRBx->PERAR, 0xFFFFU);
        WRITE_REG16(*TMRB_CMPAR, 0xFFFFU);
        WRITE_REG16(TMRBx->BCSTR, 0x0000U);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable TimerB output compare port output function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_EnablePortOutput(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    SET_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_OUTEN);
}

/**
 * @brief  Disable TimerB output compare port output function.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_DisablePortOutput(M4_TMRB_TypeDef *TMRBx, uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    CLEAR_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_OUTEN);
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port output polarity when start count.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Polarity             TimerB TIMB_<t>_PWMn port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_OC_STARTCNT_OUTPUT_LOW:  TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB start count
 *           @arg TMRB_OC_STARTCNT_OUTPUT_HIGH: TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB start count
 *           @arg TMRB_OC_STARTCNT_OUTPUT_HOLD: TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB start count
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_SetStartCntOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                uint32_t u32Ch,
                                                uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_OC_START_CNT_OUTPUT_POLARITY(u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, TMRB_PCONR_STAC, u16Polarity);
}

/**
 * @brief  Get TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for start count.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_OC_STARTCNT_OUTPUT_LOW:  TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB start count
 *           @arg TMRB_OC_STARTCNT_OUTPUT_HIGH: TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB start count
 *           @arg TMRB_OC_STARTCNT_OUTPUT_HOLD: TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB start count
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
uint16_t TMRB_OC_GetStartCntOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                    uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_STAC);
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for stop count.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Polarity             TimerB TIMB_<t>_PWM1 port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_OC_STOPCNT_OUTPUT_LOW:   TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB stop count
 *           @arg TMRB_OC_STOPCNT_OUTPUT_HIGH:  TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB stop count
 *           @arg TMRB_OC_STOPCNT_OUTPUT_HOLD:  TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB stop count
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_SetStopCntOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                uint32_t u32Ch,
                                                uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_OC_STOP_CNT_OUTPUT_POLARITY(u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, TMRB_PCONR_STPC, u16Polarity);
}

/**
 * @brief  Get TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for stop count.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_OC_STOPCNT_OUTPUT_LOW:   TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB stop count
 *           @arg TMRB_OC_STOPCNT_OUTPUT_HIGH:  TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB stop count
 *           @arg TMRB_OC_STOPCNT_OUTPUT_HOLD:  TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB stop count
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
uint16_t TMRB_OC_GetStopCntOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                    uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_STPC);
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for compare match.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Polarity             TimerB TIMB_<t>_PWMn port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_LOW:      TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB comapre match
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_HIGH:     TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB comapre match
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_HOLD:     TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB comapre match
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_INVERTED: TIM_<t>_PWMn(t=1,n=1~4) output inverted level when TimerB comapre match
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_SetCmpMatchOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                uint32_t u32Ch,
                                                uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_OC_CMPMATCH_OUTPUT_POLARITY(u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, TMRB_PCONR_CMPC, u16Polarity);
}

/**
 * @brief  Get TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for compare match.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_LOW:      TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB comapre match
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_HIGH:     TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB comapre match
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_HOLD:     TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB comapre match
 *           @arg TMRB_OC_CMPMATCH_OUTPUT_INVERTED: TIM_<t>_PWMn(t=1,n=1~4) output inverted level when TimerB comapre match
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
uint16_t TMRB_OC_GetCmpMatchOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                    uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_CMPC);
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for period match.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Polarity             TimerB TIMB_<t>_PWMn port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_LOW:       TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB period match
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_HIGH:      TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB period match
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_HOLD:      TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB period match
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_INVERTED:  TIM_<t>_PWMn(t=1,n=1~4) output inverted level when TimerB period match
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_SetPeriodMatchOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                    uint32_t u32Ch,
                                                    uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_OC_PERIODMATCH_OUTPUT_POLARITY(u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, TMRB_PCONR_PERC, u16Polarity);
}

/**
 * @brief  Get TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for period match.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_LOW:       TIM_<t>_PWMn(t=1,n=1~4) output low level when TimerB period match
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_HIGH:      TIM_<t>_PWMn(t=1,n=1~4) output high level when TimerB period match
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_HOLD:      TIM_<t>_PWMn(t=1,n=1~4) output hold level when TimerB period match
 *           @arg TMRB_OC_PERIODMATCH_OUTPUT_INVERTED:  TIM_<t>_PWMn(t=1,n=1~4) output inverted level when TimerB period match
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
uint16_t TMRB_OC_GetPeriodMatchOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                        uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_PERC);
}

/**
 * @brief  Set TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for force.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @param  [in] u16Polarity             TimerB TIMB_<t>_PWMn port output polarity
 *         This parameter can be one of the following values:
 *           @arg TMRB_OC_FORCE_OUTPUT_LOW:     Force TIM_<t>_PWMn(t=1,n=1~4) output low level
 *           @arg TMRB_OC_FORCE_OUTPUT_HIGH:    Force TIM_<t>_PWMn(t=1,n=1~4) output high level
 *           @arg TMRB_OC_FORCE_OUTPUT_INVALID: Force invalid
 * @retval None
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
void TMRB_OC_SetForceOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                            uint32_t u32Ch,
                                            uint16_t u16Polarity)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));
    DDL_ASSERT(IS_TMRB_OC_FORCE_OUTPUT_POLARITY(u16Polarity));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    MODIFY_REG16(*TMRB_PCONR, TMRB_PCONR_FORC, u16Polarity);
}

/**
 * @brief  Get TIMB_<t>_PWMn(t=1,n=1~4) port output polarity for force.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @param  [in] u32Ch                   TimerB channel
 *         This parameter can be one of the following values:
 *           @arg TMRB_CH1:             TimerB channel 1
 *           @arg TMRB_CH2:             TimerB channel 2
 *           @arg TMRB_CH3:             TimerB channel 3
 *           @arg TMRB_CH4:             TimerB channel 4
 * @retval Returned value can be one of the following values:
 *           @arg TMRB_OC_FORCE_OUTPUT_LOW:     Force TIM_<t>_PWMn(t=1,n=1~4) output low level
 *           @arg TMRB_OC_FORCE_OUTPUT_HIGH:    Force TIM_<t>_PWMn(t=1,n=1~4) output high level
 *           @arg TMRB_OC_FORCE_OUTPUT_INVALID: Force invalid
 * @note TimerB channel 5&6 only output inner signal and don't support TIMB_t_PWMn port function.
 */
uint16_t TMRB_OC_GetForceOutputPolarity(M4_TMRB_TypeDef *TMRBx,
                                                uint32_t u32Ch)
{
    __IO uint16_t *TMRB_PCONR;

    /* Check parameters */
    DDL_ASSERT(IS_TMRB_INSTANCE(TMRBx));
    DDL_ASSERT(IS_TMRB_PWM_CH(u32Ch));

    TMRB_PCONR = TMRB_PCONRx(TMRBx, u32Ch);
    return READ_REG16_BIT(*TMRB_PCONR, TMRB_PCONR_FORC);
}

/**
 * @brief Get TMRB trigger selection register of the specified TMRB unit.
 * @param  [in] TMRBx                   Pointer to TimerB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_TMRB:              TimerB unit 1 instance register base
 * @retval TMRB trigger selection register
 */
static __IO uint32_t* TMRB_TRGSELx(const M4_TMRB_TypeDef *TMRBx)
{
    __IO uint32_t *TRGSELx;

    if (M4_TMRB == TMRBx)
    {
        TRGSELx = &M4_AOS->TMRB_HTSSR;
    }
    else
    {
        TRGSELx = NULL;
    }

    return TRGSELx;
}

/**
 * @}
 */

#endif /* DDL_TMRB_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
