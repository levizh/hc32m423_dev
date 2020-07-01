/**
 *******************************************************************************
 * @file  hc32m423_emb.c
 * @brief This file provides firmware functions to manage the EMB
 *        (Emergency Brake).
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
#include "hc32m423_emb.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EMB EMB
 * @brief Emergency Brake Driver Library
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Local_Macros EMB Local Macros
 * @{
 */

/**
 * @defgroup EMB_Check_Parameters_Validity EMB Check Parameters Validity
 * @{
 */

#define IS_VALID_EMB_GROUP(x)                                                  \
(   ((x) == EMB_GROUP0_TMR4)                    ||                             \
    ((x) == EMB_GROUP1_TMRB))

#define IS_VALID_EMB_CMP1_SEL(x)                                               \
(   ((x) == EMB_CMP1_ENABLE)                    ||                             \
    ((x) == EMB_CMP1_DISABLE))

#define IS_VALID_EMB_CMP2_SEL(x)                                               \
(   ((x) == EMB_CMP2_ENABLE)                    ||                             \
    ((x) == EMB_CMP2_DISABLE))

#define IS_VALID_EMB_CMP3_SEL(x)                                               \
(   ((x) == EMB_CMP3_ENABLE)                    ||                             \
    ((x) == EMB_CMP3_DISABLE))

#define IS_VALID_EMB_OSC_SEL(x)                                                \
(   ((x) == EMB_OSC_ENABLE)                     ||                             \
    ((x) == EMB_OSC_DISABLE))

#define IS_VALID_EMB_TMR4_PWMU_SEL(x)                                          \
(   ((x) == EMB_TMR4_PWMU_ENABLE)               ||                             \
    ((x) == EMB_TMR4_PWMU_DISABLE))

#define IS_VALID_EMB_TMR4_PWMV_SEL(x)                                          \
(   ((x) == EMB_TMR4_PWMV_ENABLE)               ||                             \
    ((x) == EMB_TMR4_PWMV_DISABLE))

#define IS_VALID_EMB_TMR4_PWMW_SEL(x)                                          \
(   ((x) == EMB_TMR4_PWMW_ENABLE)               ||                             \
    ((x) == EMB_TMR4_PWMW_DISABLE))

#define IS_VALID_EMB_PORT_EMBIN1_SEL(x)                                        \
(   ((x) == EMB_PORT_EMBIN1_ENABLE)             ||                             \
    ((x) == EMB_PORT_EMBIN1_DISABLE))

#define IS_VALID_EMB_PORT_EMBIN2_SEL(x)                                        \
(   ((x) == EMB_PORT_EMBIN2_ENABLE)             ||                             \
    ((x) == EMB_PORT_EMBIN2_DISABLE))

#define IS_VALID_EMB_PORT_EMBIN3_SEL(x)                                        \
(   ((x) == EMB_PORT_EMBIN3_ENABLE)             ||                             \
    ((x) == EMB_PORT_EMBIN3_DISABLE))

#define IS_VALID_EMB_PORT_EMBIN1_LEVEL(x)                                      \
(   ((x) == EMB_PORT_EMBIN1_LEVEL_HIGH)         ||                             \
    ((x) == EMB_PORT_EMBIN1_LEVEL_LOW))

#define IS_VALID_EMB_PORT_EMBIN2_LEVEL(x)                                      \
(   ((x) == EMB_PORT_EMBIN2_LEVEL_HIGH)         ||                             \
    ((x) == EMB_PORT_EMBIN2_LEVEL_LOW))

#define IS_VALID_EMB_PORT_EMBIN3_LEVEL(x)                                      \
(   ((x) == EMB_PORT_EMBIN3_LEVEL_HIGH)         ||                             \
    ((x) == EMB_PORT_EMBIN3_LEVEL_LOW))

#define IS_VALID_EMB_DETECT_TIMER4_PWMU_LEVEL(x)                               \
(   ((x) == EMB_DETECT_TIMER4_PWMU_LEVEL_LOW)   ||                             \
    ((x) == EMB_DETECT_TIMER4_PWMU_LEVEL_HIGH))

#define IS_VALID_EMB_DETECT_TIMER4_PWMV_LEVEL(x)                               \
(   ((x) == EMB_DETECT_TIMER4_PWMV_LEVEL_LOW)   ||                             \
    ((x) == EMB_DETECT_TIMER4_PWMV_LEVEL_HIGH))

#define IS_VALID_EMB_DETECT_TIMER4_PWMW_LEVEL(x)                               \
(   ((x) == EMB_DETECT_TIMER4_PWMW_LEVEL_LOW)   ||                             \
    ((x) == EMB_DETECT_TIMER4_PWMW_LEVEL_HIGH))

#define IS_VALID_EMB_SET_TMRB_PWM_OUTPUT_STATE(x)                              \
(   ((x) == EMB_SET_TMRB_PWM_OUTPUT_NORMAL)     ||                             \
    ((x) == EMB_SET_TMRB_PWM_OUTPUT_HIZ)        ||                             \
    ((x) == EMB_SET_TMRB_PWM_OUTPUT_LOW)        ||                             \
    ((x) == EMB_SET_TMRB_PWM_OUTPUT_HIGH))

#define IS_VALID_EMB_PORT_EMBIN1_FILTER_DIV(x)                                 \
(   ((x) == EMB_PORT_EMBIN1_FILTER_NONE)        ||                             \
    ((x) == EMB_PORT_EMBIN1_FILTER_CLK_DIV1)    ||                             \
    ((x) == EMB_PORT_EMBIN1_FILTER_CLK_DIV8)    ||                             \
    ((x) == EMB_PORT_EMBIN1_FILTER_CLK_DIV32)   ||                             \
    ((x) == EMB_PORT_EMBIN1_FILTER_CLK_DIV128))

#define IS_VALID_EMB_PORT_EMBIN2_FILTER_DIV(x)                                 \
(   ((x) == EMB_PORT_EMBIN2_FILTER_NONE)        ||                             \
    ((x) == EMB_PORT_EMBIN2_FILTER_CLK_DIV1)    ||                             \
    ((x) == EMB_PORT_EMBIN2_FILTER_CLK_DIV8)    ||                             \
    ((x) == EMB_PORT_EMBIN2_FILTER_CLK_DIV32)   ||                             \
    ((x) == EMB_PORT_EMBIN2_FILTER_CLK_DIV128))

#define IS_VALID_EMB_PORT_EMBIN3_FILTER_DIV(x)                                 \
(   ((x) == EMB_PORT_EMBIN3_FILTER_NONE)        ||                             \
    ((x) == EMB_PORT_EMBIN3_FILTER_CLK_DIV1)    ||                             \
    ((x) == EMB_PORT_EMBIN3_FILTER_CLK_DIV8)    ||                             \
    ((x) == EMB_PORT_EMBIN3_FILTER_CLK_DIV32)   ||                             \
    ((x) == EMB_PORT_EMBIN3_FILTER_CLK_DIV128))

#define IS_VALID_EMB_INT(x)                                                    \
(   ((x) == EMB_INT_PWM)                        ||                             \
    ((x) == EMB_INT_CMP)                        ||                             \
    ((x) == EMB_INT_OSC)                        ||                             \
    ((x) == EMB_INT_PORT_EMBIN1)                ||                             \
    ((x) == EMB_INT_PORT_EMBIN2)                ||                             \
    ((x) == EMB_INT_PORT_EMBIN3))

#define IS_VALID_EMB_FLAG(x)                                                   \
(   ((x) == EMB_FLAG_PWM)                       ||                             \
    ((x) == EMB_FLAG_CMP)                       ||                             \
    ((x) == EMB_FLAG_OSC)                       ||                             \
    ((x) == EMB_FLAG_PORT_EMBIN1)               ||                             \
    ((x) == EMB_FLAG_PORT_EMBIN2)               ||                             \
    ((x) == EMB_FLAG_PORT_EMBIN3)               ||                             \
    ((x) == EMB_FLAG_PWM_STATE)                 ||                             \
    ((x) == EMB_FLAG_PORT_EMBIN1_STATE)         ||                             \
    ((x) == EMB_FLAG_PORT_EMBIN2_STATE)         ||                             \
    ((x) == EMB_FLAG_PORT_EMBIN3_STATE))

/**
 * @}
 */

/**
 * @defgroup EMB_Groupx_Register_Base_Address EMB Groupx Register Base Address(x = 0 ~ 1)
 * @brief Get the specified EMB group register base address
 * @{
 */
#define EMB_GROUPx_BASE_ADDRESS(__GROUP__)    ((uint32_t)M4_EMB + ((uint32_t)(__GROUP__))*0x20UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Groupx_Register EMB Groupx Register (x = 0 ~ 1)
 * @brief Get the specified EMB group register
 * @{
 */
#define EMB_CTLx(__GROUP__)        ((volatile uint32_t *)(EMB_GROUPx_BASE_ADDRESS(__GROUP__) + 0x00UL))
#define EMB_PWMLVx(__GROUP__)      ((volatile uint32_t *)(EMB_GROUPx_BASE_ADDRESS(__GROUP__) + 0x04UL))
#define EMB_SOEx(__GROUP__)        ((volatile uint32_t *)(EMB_GROUPx_BASE_ADDRESS(__GROUP__) + 0x08UL))
#define EMB_STATx(__GROUP__)       ((volatile uint32_t *)(EMB_GROUPx_BASE_ADDRESS(__GROUP__) + 0x0CUL))
#define EMB_STATCLRx(__GROUP__)    ((volatile uint32_t *)(EMB_GROUPx_BASE_ADDRESS(__GROUP__) + 0x10UL))
#define EMB_INTENx(__GROUP__)      ((volatile uint32_t *)(EMB_GROUPx_BASE_ADDRESS(__GROUP__) + 0x14UL))
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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup EMB_Global_Functions EMB Global Functions
 * @{
 */

/**
 * @brief  Initialize EMB group0.
 * @param  [in] pstcInit                Pointer to a @ref stc_emb_group0_timer4_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EMB_Group0Timer4Init(const stc_emb_group0_timer4_init_t *pstcInit)
{
    uint32_t u32Ctl = 0UL;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_EMB_CMP1_SEL(pstcInit->u32Cmp1Enable));
        DDL_ASSERT(IS_VALID_EMB_CMP2_SEL(pstcInit->u32Cmp2Enable));
        DDL_ASSERT(IS_VALID_EMB_CMP3_SEL(pstcInit->u32Cmp3Enable));
        DDL_ASSERT(IS_VALID_EMB_OSC_SEL(pstcInit->u32OscEnable));
        DDL_ASSERT(IS_VALID_EMB_TMR4_PWMU_SEL(pstcInit->stcTimer4.u32Timer4PwmUEnable));
        DDL_ASSERT(IS_VALID_EMB_TMR4_PWMV_SEL(pstcInit->stcTimer4.u32Timer4PwmVEnable));
        DDL_ASSERT(IS_VALID_EMB_TMR4_PWMW_SEL(pstcInit->stcTimer4.u32Timer4PwmWEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN1_SEL(pstcInit->stcEmbIn1.u32PortEmbInEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN1_LEVEL(pstcInit->stcEmbIn1.u32PortEmbInLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN1_FILTER_DIV(pstcInit->stcEmbIn1.u32PortEmbInFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN2_SEL(pstcInit->stcEmbIn2.u32PortEmbInEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN2_LEVEL(pstcInit->stcEmbIn2.u32PortEmbInLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN2_FILTER_DIV(pstcInit->stcEmbIn2.u32PortEmbInFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN3_SEL(pstcInit->stcEmbIn3.u32PortEmbInEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN3_LEVEL(pstcInit->stcEmbIn3.u32PortEmbInLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN3_FILTER_DIV(pstcInit->stcEmbIn3.u32PortEmbInFilterDiv));

        /* Set default value */
        WRITE_REG32(M4_EMB->STATCLR0, 0x0Ful);
        WRITE_REG32(M4_EMB->INTEN0, 0x00UL);
        WRITE_REG32(M4_EMB->SOE0, 0x00UL);

        u32Ctl = pstcInit->u32Cmp1Enable | \
                 pstcInit->u32Cmp2Enable | \
                 pstcInit->u32Cmp3Enable | \
                 pstcInit->u32OscEnable | \
                 pstcInit->stcTimer4.u32Timer4PwmUEnable | \
                 pstcInit->stcTimer4.u32Timer4PwmVEnable | \
                 pstcInit->stcTimer4.u32Timer4PwmWEnable | \
                 pstcInit->stcEmbIn1.u32PortEmbInEnable | \
                 pstcInit->stcEmbIn1.u32PortEmbInLevel | \
                 pstcInit->stcEmbIn1.u32PortEmbInFilterDiv | \
                 pstcInit->stcEmbIn2.u32PortEmbInEnable | \
                 pstcInit->stcEmbIn2.u32PortEmbInLevel | \
                 pstcInit->stcEmbIn2.u32PortEmbInFilterDiv | \
                 pstcInit->stcEmbIn3.u32PortEmbInEnable | \
                 pstcInit->stcEmbIn3.u32PortEmbInLevel | \
                 pstcInit->stcEmbIn3.u32PortEmbInFilterDiv;

        WRITE_REG32(M4_EMB->CTL0, u32Ctl);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_emb_group0_timer4_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_emb_group0_timer4_init_t structure (M4_EMB unit function configuration data structure)
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EMB_Group0Timer4StructInit(stc_emb_group0_timer4_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Cmp1Enable = EMB_CMP1_DISABLE;
        pstcInit->u32Cmp2Enable = EMB_CMP2_DISABLE;
        pstcInit->u32Cmp3Enable = EMB_CMP3_DISABLE;

        pstcInit->u32OscEnable = EMB_OSC_DISABLE;

        pstcInit->stcTimer4.u32Timer4PwmUEnable = EMB_TMR4_PWMU_DISABLE;
        pstcInit->stcTimer4.u32Timer4PwmVEnable = EMB_TMR4_PWMV_DISABLE;
        pstcInit->stcTimer4.u32Timer4PwmWEnable = EMB_TMR4_PWMW_DISABLE;

        pstcInit->stcEmbIn1.u32PortEmbInFilterDiv = EMB_PORT_EMBIN1_FILTER_NONE;
        pstcInit->stcEmbIn1.u32PortEmbInLevel = EMB_PORT_EMBIN1_LEVEL_HIGH;
        pstcInit->stcEmbIn1.u32PortEmbInEnable = EMB_PORT_EMBIN1_DISABLE;

        pstcInit->stcEmbIn2.u32PortEmbInFilterDiv = EMB_PORT_EMBIN2_FILTER_NONE;
        pstcInit->stcEmbIn2.u32PortEmbInLevel = EMB_PORT_EMBIN2_LEVEL_HIGH;
        pstcInit->stcEmbIn2.u32PortEmbInEnable = EMB_PORT_EMBIN2_DISABLE;

        pstcInit->stcEmbIn3.u32PortEmbInFilterDiv = EMB_PORT_EMBIN3_FILTER_NONE;
        pstcInit->stcEmbIn3.u32PortEmbInLevel = EMB_PORT_EMBIN3_LEVEL_HIGH;
        pstcInit->stcEmbIn3.u32PortEmbInEnable = EMB_PORT_EMBIN3_DISABLE;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize EMB group1.
 * @param  [in] pstcInit                Pointer to a @ref stc_emb_group1_timerb_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EMB_Group1TimerbInit(const stc_emb_group1_timerb_init_t *pstcInit)
{
    uint32_t u32Ctl = 0UL;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_EMB_CMP1_SEL(pstcInit->u32Cmp1Enable));
        DDL_ASSERT(IS_VALID_EMB_CMP2_SEL(pstcInit->u32Cmp2Enable));
        DDL_ASSERT(IS_VALID_EMB_CMP3_SEL(pstcInit->u32Cmp3Enable));
        DDL_ASSERT(IS_VALID_EMB_OSC_SEL(pstcInit->u32OscEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN1_SEL(pstcInit->stcEmbIn1.u32PortEmbInEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN1_LEVEL(pstcInit->stcEmbIn1.u32PortEmbInLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN1_FILTER_DIV(pstcInit->stcEmbIn1.u32PortEmbInFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN2_SEL(pstcInit->stcEmbIn2.u32PortEmbInEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN2_LEVEL(pstcInit->stcEmbIn2.u32PortEmbInLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN2_FILTER_DIV(pstcInit->stcEmbIn2.u32PortEmbInFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN3_SEL(pstcInit->stcEmbIn3.u32PortEmbInEnable));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN3_LEVEL(pstcInit->stcEmbIn3.u32PortEmbInLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT_EMBIN3_FILTER_DIV(pstcInit->stcEmbIn3.u32PortEmbInFilterDiv));

        /* Set default value */
        WRITE_REG32(M4_EMB->STATCLR1, 0x0Ful);
        WRITE_REG32(M4_EMB->INTEN1, 0x00UL);
        WRITE_REG32(M4_EMB->SOE1, 0x00UL);

        u32Ctl = pstcInit->u32Cmp1Enable | \
                 pstcInit->u32Cmp2Enable | \
                 pstcInit->u32Cmp3Enable | \
                 pstcInit->u32OscEnable | \
                 pstcInit->stcEmbIn1.u32PortEmbInEnable | \
                 pstcInit->stcEmbIn1.u32PortEmbInLevel | \
                 pstcInit->stcEmbIn1.u32PortEmbInFilterDiv | \
                 pstcInit->stcEmbIn2.u32PortEmbInEnable | \
                 pstcInit->stcEmbIn2.u32PortEmbInLevel | \
                 pstcInit->stcEmbIn2.u32PortEmbInFilterDiv | \
                 pstcInit->stcEmbIn3.u32PortEmbInEnable | \
                 pstcInit->stcEmbIn3.u32PortEmbInLevel | \
                 pstcInit->stcEmbIn3.u32PortEmbInFilterDiv;

        WRITE_REG32(M4_EMB->CTL1, u32Ctl);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_emb_group1_timerb_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_emb_group1_timerb_init_t structure (M4_EMB unit function configuration data structure)
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EMB_Group1TimerbStructInit(stc_emb_group1_timerb_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Cmp1Enable = EMB_CMP1_DISABLE;
        pstcInit->u32Cmp2Enable = EMB_CMP2_DISABLE;
        pstcInit->u32Cmp3Enable = EMB_CMP3_DISABLE;

        pstcInit->u32OscEnable = EMB_OSC_DISABLE;

        pstcInit->stcEmbIn1.u32PortEmbInFilterDiv = EMB_PORT_EMBIN1_FILTER_NONE;
        pstcInit->stcEmbIn1.u32PortEmbInLevel = EMB_PORT_EMBIN1_LEVEL_HIGH;
        pstcInit->stcEmbIn1.u32PortEmbInEnable = EMB_PORT_EMBIN1_DISABLE;

        pstcInit->stcEmbIn2.u32PortEmbInFilterDiv = EMB_PORT_EMBIN2_FILTER_NONE;
        pstcInit->stcEmbIn2.u32PortEmbInLevel = EMB_PORT_EMBIN2_LEVEL_HIGH;
        pstcInit->stcEmbIn2.u32PortEmbInEnable = EMB_PORT_EMBIN2_DISABLE;

        pstcInit->stcEmbIn3.u32PortEmbInFilterDiv = EMB_PORT_EMBIN3_FILTER_NONE;
        pstcInit->stcEmbIn3.u32PortEmbInLevel = EMB_PORT_EMBIN3_LEVEL_HIGH;
        pstcInit->stcEmbIn3.u32PortEmbInEnable = EMB_PORT_EMBIN3_DISABLE;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize EMB function
 * @param  [in] u32Group                EMB group
 *         This parameter can be one of the following values:
 *           @arg EMB_GROUP0_TMR4:      EMB group 0 for Timer4
 *           @arg EMB_GROUP1_TMRB:      EMB group 1 for TimerB
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 */
en_result_t EMB_DeInit(uint32_t u32Group)
{
    __IO uint32_t *EMB_SOE = EMB_SOEx(u32Group);
    __IO uint32_t *EMB_INTEN = EMB_INTENx(u32Group);
    __IO uint32_t *EMB_STATCLR = EMB_STATCLRx(u32Group);

    DDL_ASSERT(IS_VALID_EMB_GROUP(u32Group));

    /* Configures the registers to reset value. */
    WRITE_REG32(*EMB_STATCLR, 0x0FUL);
    WRITE_REG32(*EMB_INTEN, 0x00UL);
    WRITE_REG32(*EMB_SOE, 0x00UL);

    return Ok;
}

/**
 * @brief  Set EMB detection port level
 * @param  [in] stcPwmLevel             Timer4 PWM level a @ref stc_emb_timer4_pwm_level_t structure
 * @retval None
 */
void EMB_SetDetectTimer4PwmLevel(stc_emb_timer4_pwm_level_t stcPwmLevel)
{
    uint32_t u32Pwmlv0;

    DDL_ASSERT(IS_VALID_EMB_DETECT_TIMER4_PWMU_LEVEL(stcPwmLevel.u32PwmULvl));
    DDL_ASSERT(IS_VALID_EMB_DETECT_TIMER4_PWMV_LEVEL(stcPwmLevel.u32PwmVLvl));
    DDL_ASSERT(IS_VALID_EMB_DETECT_TIMER4_PWMW_LEVEL(stcPwmLevel.u32PwmWLvl));

    u32Pwmlv0 = stcPwmLevel.u32PwmULvl | stcPwmLevel.u32PwmVLvl | stcPwmLevel.u32PwmWLvl;

    WRITE_REG32(M4_EMB->PWMLV0, u32Pwmlv0);
}

/**
 * @brief  Set Timerb PWM port output state when EMB event occurs
 * @param  [in] u32OutputState          Timerb PWM port output state
 *         This parameter can be one of the following values:
 *           @arg EMB_SET_TMRB_PWM_OUTPUT_NORMAL: TIMB_1_PWMn(n=1~4) output normal
 *           @arg EMB_SET_TMRB_PWM_OUTPUT_HIZ:    TIMB_1_PWMn(n=1~4) output Hi-z
 *           @arg EMB_SET_TMRB_PWM_OUTPUT_LOW:    TIMB_1_PWMn(n=1~4) output low level
 *           @arg EMB_SET_TMRB_PWM_OUTPUT_HIGH:   TIMB_1_PWMn(n=1~4) output high level
 * @retval None
 */
void EMB_SetTimerbOutputState(uint32_t u32OutputState)
{
    DDL_ASSERT(IS_VALID_EMB_SET_TMRB_PWM_OUTPUT_STATE(u32OutputState));

    WRITE_REG32(M4_EMB->ECSR, u32OutputState);
}

/**
 * @brief  Set the EMB interrupt function
 * @param  [in] u32Group                EMB group
 *         This parameter can be one of the following values:
 *           @arg EMB_GROUP0_TMR4:      EMB group 0 for Timer4
 *           @arg EMB_GROUP1_TMRB:      EMB group 1 for TimerB
 * @param  [in] u32IntSource            EMB interrupt source
 *         This parameter can be one of the following values:
 *           @arg EMB_INT_PWM:          PWM same phase trigger stop PWM
 *           @arg EMB_INT_CMP:          CMP trigger stop PWM
 *           @arg EMB_INT_OSC:          OSC trigger stop PWM
 *           @arg EMB_INT_PORT_EMBIN1:  Port EMB_IN1 stop PWM
 *           @arg EMB_INT_PORT_EMBIN2:  Port EMB_IN2 stop PWM
 *           @arg EMB_INT_PORT_EMBIN3:  Port EMB_IN3 stop PWM
 * @param  [in] enNewSta                The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void EMB_IntCmd(uint32_t u32Group,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewSta)
{
    __IO uint32_t *EMB_INTEN = EMB_INTENx(u32Group);

    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB_GROUP(u32Group));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));
    DDL_ASSERT(IS_VALID_EMB_INT(u32IntSource));

    MODIFY_REG32(*EMB_INTEN, u32IntSource, enNewSta);
}

/**
 * @brief  Get EMB status
 * @param  [in] u32Group                EMB group
 *         This parameter can be one of the following values:
 *           @arg EMB_GROUP0_TMR4:      EMB group 0 for Timer4
 *           @arg EMB_GROUP1_TMRB:      EMB group 1 for TimerB
 * @param  [in] u32Status               EMB flag
 *         This parameter can be one of the following values:
 *           @arg EMB_FLAG_PWM:  PWM same phase trigger stop PWM
 *           @arg EMB_FLAG_CMP: CMP trigger stop PWM
 *           @arg EMB_FLAG_OSC: OSC trigger stop PWM
 *           @arg EMB_FLAG_PORT_EMBIN1: Port EMB_IN1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT_EMBIN2: Port EMB_IN1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT_EMBIN3: Port EMB_IN1 input trigger stop PWM
 *           @arg EMB_FLAG_PWM_STATE: PWM same phase occur
 *           @arg EMB_FLAG_PORT_EMBIN1_STATE: Port EMB_IN1 input control state
 *           @arg EMB_FLAG_PORT_EMBIN2_STATE: Port EMB_IN2 input control state
 *           @arg EMB_FLAG_PORT_EMBIN3_STATE: Port EMB_IN3 input control state
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t EMB_GetStatus(uint32_t u32Group, uint32_t u32Status)
{
    __IO uint32_t *EMB_STAT = EMB_STATx(u32Group);

    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB_GROUP(u32Group));
    DDL_ASSERT(IS_VALID_EMB_FLAG(u32Status));

    return READ_REG32_BIT(*EMB_STAT, u32Status) ? Set : Reset;
}

/**
 * @brief  Clear EMB status
 * @param  [in] u32Group                EMB group
 *         This parameter can be one of the following values:
 *           @arg EMB_GROUP0_TMR4:      EMB group 0 for Timer4
 *           @arg EMB_GROUP1_TMRB:      EMB group 1 for TimerB
 * @param  [in] u32Status           EMB status
 *         This parameter can be one of the following values:
 *           @arg EMB_FLAG_PWM:  PWM same phase trigger stop PWM
 *           @arg EMB_FLAG_CMP: CMP trigger stop PWM
 *           @arg EMB_FLAG_OSC: OSC trigger stop PWM
 *           @arg EMB_FLAG_PORT_EMBIN1: Port EMB_IN1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT_EMBIN2: Port EMB_IN1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT_EMBIN3: Port EMB_IN1 input trigger stop PWM
 * @retval None
 */
void EMB_ClearStatus(uint32_t u32Group, uint32_t u32Status)
{
    __IO uint32_t *EMB_STAT = EMB_STATx(u32Group);

    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB_GROUP(u32Group));
    DDL_ASSERT(IS_VALID_EMB_FLAG(u32Status));

    SET_REG32_BIT(*EMB_STAT, u32Status);
}

/**
 * @brief  EMB software brake
 * @param  [in] u32Group                EMB group
 *         This parameter can be one of the following values:
 *           @arg EMB_GROUP0_TMR4:      EMB group 0 for Timer4
 *           @arg EMB_GROUP1_TMRB:      EMB group 1 for TimerB
 * @param  [in] enNewSta                The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void EMB_SwBrake(uint32_t u32Group, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB_GROUP(u32Group));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (EMB_GROUP0_TMR4 == u32Group)
    {
        WRITE_REG32(bM4_EMB->SOE0_b.SOE, enNewSta);
    }
    else
    {
        WRITE_REG32(bM4_EMB->SOE1_b.SOE, enNewSta);
    }
}

/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
