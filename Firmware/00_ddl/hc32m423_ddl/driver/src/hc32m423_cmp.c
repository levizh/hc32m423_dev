/**
 *******************************************************************************
 * @file  hc32m423_cmp.c
 * @brief This file provides firmware functions to manage the Comparator(CMP).
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-05       Wangmin         First version
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
#include "hc32m423_cmp.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CMP CMP
 * @brief CMP Driver Library
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CMP_Local_Macros CMP Local Macros
 * @{
 */


/**
 * @defgroup CMP_Check_Parameters_Validity CMP Check Parameters Validity
 * @{
 */

#define IS_CMP_INSTANCE(x)                                                     \
(   (M4_CMP1 == (x))                            ||                             \
    (M4_CMP2 == (x))                            ||                             \
    (M4_CMP3 == (x)))

#define IS_CMP_MODE(x)                                                         \
(   (CMP_MODE_NORMAL == (x))                    ||                             \
    (CMP_MODE_WINDOW == (x)))

#define IS_CMP_CVSL(x)                                                         \
(   (CMP_CVSL_NONE == (x))                      ||                             \
    (CMP_CVSL_IVCMPx_0 == (x))                  ||                             \
    (CMP_CVSL_IVCMPx_1 == (x))                  ||                             \
    (CMP_CVSL_IVCMPx_2 == (x))                  ||                             \
    (CMP_CVSL_VREF == (x)))

#define IS_CMP_RVSL(x)                                                         \
(   (CMP_RVSL_NONE == (x))                      ||                             \
    (CMP_RVSL_IVREF1 == (x))                    ||                             \
    (CMP_RVSL_IVREF2 == (x))                    ||                             \
    (CMP_RVSL_DAC == (x)))

#define IS_CMP_OUT_POLARITY(x)                                                 \
(   (CMP_OUT_REVERSE_OFF == (x))                ||                             \
    (CMP_OUT_REVERSE_ON == (x)))

#define IS_CMP_OUT_DETECT_EDGE(x)                                              \
(   (CMP_DETECT_EDGS_NONE == (x))               ||                             \
    (CMP_DETECT_EDGS_RISING == (x))             ||                             \
    (CMP_DETECT_EDGS_FALLING == (x))            ||                             \
    (CMP_DETECT_EDGS_BOTH == (x)))

#define IS_CMP_OUT_FILTER(x)                                                   \
(   (CMP_OUT_FILTER_NONE == (x))                ||                             \
    (CMP_OUT_FILTER_PCLK == (x))                ||                             \
    (CMP_OUT_FILTER_PCLKDIV8 == (x))            ||                             \
    (CMP_OUT_FILTER_PCLKDIV32 == (x)))

#define IS_CMP_TIMWIN_FUNC(x)                                                  \
(   (CMP_TIMERWIN_OFF == (x))                   ||                             \
    (CMP_TIMERWIN_ON == (x)))

#define IS_CMP_TIMWIN_SELECT(x)                                                \
(   (CMP_TIMERWIN_TIMB_1_PWM1_3_5 == (x))       ||                             \
    (CMP_TIMERWIN_TIMB_1_PWM2_4_6 == (x))       ||                             \
    (CMP_TIMERWIN_TIM4_OWL == (x))              ||                             \
    (CMP_TIMERWIN_TIM4_OWH == (x))              ||                             \
    (CMP_TIMERWIN_TIM4_OVL == (x))              ||                             \
    (CMP_TIMERWIN_TIM4_OVH == (x))              ||                             \
    (CMP_TIMERWIN_TIM4_OUL == (x))              ||                             \
    (CMP_TIMERWIN_TIM4_OUH == (x)))

#define IS_CMP_TIMWIN_INVALIDLEVEL(x)                                          \
(   (CMP_TIMERWIN_INVALID_LEVEL_LOW == (x))     ||                             \
    (CMP_TIMERWIN_INVALID_LEVEL_HIGH == (x)))

#define IS_CMP_TIMWIN_OUT_LEVEL(x)                                             \
(   (CMP_TIMERWIN_OUT_LEVEL_LOW == (x))         ||                             \
    (CMP_TIMERWIN_OUT_LEVEL_HIGH == (x)))

#define IS_CMP_DAC_ALIGN_MODE(x)                                               \
(   (CMP_DAC_ALIGN_RIGHT == (x))                ||                             \
    (CMP_DAC_ALIGN_LEFT == (x)))

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
static void CMP_Delay300ns(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup CMP_Global_Functions CMP Global Functions
 * @{
 */

/**
 * @brief  Voltage compare function command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [in] enNewSta          The function new state.
 *              @arg              This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *              - Ok:             Set successfully
 *              - ErrorInvalidParameter: CMPx is invalid instance
 */
en_result_t CMP_FuncCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance */
    if (!IS_CMP_INSTANCE(CMPx))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        if(Enable == enNewSta)
        {
            SET_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
            /* Delay 300ns*/
            CMP_Delay300ns();
        }
        else
        {
            CLEAR_REG8_BIT(CMPx->MDR, CMP_MDR_CENB);
        }
    }
    return enRet;
}

/**
 * @brief  Voltage compare interrupt function command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [in] enNewSta          The function new state.
 *              @arg              This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *              - Ok:             Set successfully
 *              - ErrorInvalidParameter: CMPx is invalid instance
 */
en_result_t CMP_IntCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance */
    if (!IS_CMP_INSTANCE(CMPx))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        (Enable == enNewSta) ?
          SET_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN) :
           CLEAR_REG8_BIT(CMPx->FIR, CMP_FIR_CIEN);
    }
    return enRet;
}

/**
 * @brief  Voltage compare output command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [in] enNewSta          The function new state.
 *              @arg              This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *              - Ok:             Set successfully
 *              - ErrorInvalidParameter: CMPx is invalid instance
 */
en_result_t CMP_OutputCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance */
    if (!IS_CMP_INSTANCE(CMPx))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        (Enable == enNewSta) ?
          SET_REG8_BIT(CMPx->OCR, CMP_OCR_COEN) :
           CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_COEN);
    }
    return enRet;
}

/**
 * @brief  Voltage compare output port VCOUT function command
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [in] enNewSta          The function new state.
 *              @arg              This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *              - Ok:             Set successfully
 *              - ErrorInvalidParameter: CMPx is invalid instance
 */
en_result_t CMP_VCOUTCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance */
    if (!IS_CMP_INSTANCE(CMPx))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

        (Enable == enNewSta) ?
          SET_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE) :
           CLEAR_REG8_BIT(CMPx->OCR, CMP_OCR_CPOE);
    }
    return enRet;
}

/**
 * @brief  Voltage compare result flag read
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [out] penFunSta        Return the CMON flag status.
 *              @arg  This parameter can be: Set or Reset.
 *              In normal mode
 *              - Reset:          compare voltage < reference voltage
 *              - Set:            compare voltage > reference voltage
 *              In Window mode
 *              - Reset:          compare voltage < reference low voltage or
 *                                compare voltage > reference high voltage
 *              - Set:            compare voltage > reference low voltage and
 *                                compare voltage < reference high voltage
 * @retval An en_result_t enumeration value:
 *              - Ok:             Read successfully
 *              - ErrorInvalidParameter: CMPx is invalid instance
 */
en_result_t CMP_ResultGet(M4_CMP_TypeDef *CMPx, en_flag_status_t* penFunSta)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance */
    if ((!IS_CMP_INSTANCE(CMPx)) || (NULL == penFunSta))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        *penFunSta = READ_BIT(CMPx->MDR, CMP_MDR_CMON) ? Reset : Set;
    }

    return enRet;
}

/**
 * @brief  Voltage compare timer windows function configuration
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [in] pstcCMP_TimerWinStruct Configuration structure for timer windows function
 *              pstcCMP_TimerWinStruct->u8TWMode
 *                                Timer windows mode on or off @ref CMP_TimerWin_func
 *              @arg              This parameter can be: CMP_TIMERWIN_OFF or CMP_TIMERWIN_ON.
 *              pstcCMP_TimerWinStruct->u8TWInvalidLevel
 *                                The output level when timer windows valid.@ref CMP_TimerWin_Invalid_Level
 *              @arg              This parameter can be: CMP_TIMERWIN_INVALID_LEVEL_LOW or CMP_TIMERWIN_INVALID_LEVEL_HIGH.
 *              pstcCMP_TimerWinStruct->u8TWSelect
 *                                The timer event for timer windows function.
 *              @arg              This parameter can be one of the values @ref CMP_TimerWin_Select
 *              pstcCMP_TimerWinStruct->u8TWOutLevel
 *                                Timer windows mode output level.@ref CMP_TimerWin_output_Level
 *              @arg              This parameter can be: CMP_TIMERWIN_OUT_LEVEL_LOW or CMP_TIMERWIN_OUT_LEVEL_HIGH.
 * @retval An en_result_t enumeration value:
 *              - Ok:             Successfully
 *              - ErrorInvalidParameter: CMPx or pointer of structure is invalid
 */
en_result_t CMP_TimerWindowsCfg(M4_CMP_TypeDef *CMPx,
                                 const stc_cmp_timerwindows_t* pstcCMP_TimerWinStruct)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance and configuration structure*/
    if ((!IS_CMP_INSTANCE(CMPx)) || (NULL == pstcCMP_TimerWinStruct))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_TIMWIN_INVALIDLEVEL(pstcCMP_TimerWinStruct->u8TWInvalidLevel));
        DDL_ASSERT(IS_CMP_TIMWIN_FUNC(pstcCMP_TimerWinStruct->u8TWMode));
        DDL_ASSERT(IS_CMP_TIMWIN_OUT_LEVEL(pstcCMP_TimerWinStruct->u8TWOutLevel));
        DDL_ASSERT(IS_CMP_TIMWIN_SELECT(pstcCMP_TimerWinStruct->u8TWSelect));

        /* Write TWR2 register and TWR1 register */
        pstcCMP_TimerWinStruct->u8TWOutLevel ?
          SET_REG8_BIT(CMPx->TWR2, pstcCMP_TimerWinStruct->u8TWSelect):
            CLEAR_REG8_BIT(CMPx->TWR2, pstcCMP_TimerWinStruct->u8TWSelect);

        WRITE_REG(CMPx->TWR1, pstcCMP_TimerWinStruct->u8TWSelect);

        /* Enable timer windows mode and configuration output level in windows invalid */
        MODIFY_REG8(CMPx->OCR,
                   CMP_OCR_TWOL | CMP_OCR_TWOE,
                   pstcCMP_TimerWinStruct->u8TWMode | pstcCMP_TimerWinStruct->u8TWInvalidLevel);
    }
    return enRet;
}


/**
 * @brief  CMP normal mode initialize
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @param  [in] pstcCMP_InitStruct Configuration structure for normal mode initialize
 *              pstcCMP_InitStruct->u8CmpVol
 *                                Compare voltage, @ref CMP_CVSL_Source
 *              pstcCMP_InitStruct->u8RefVol
 *                                Reference voltage, @ref CMP_RVSL_Source
 *              pstcCMP_InitStruct->u8OutPolarity
 *                                Output polarity select, @ref CMP_Out_Polarity_Select
 *              pstcCMP_InitStruct->u8OutDetectEdges
 *                                Output detect edge, @ref CMP_Out_Detect_Edge
 *              pstcCMP_InitStruct->u8OutFilter
 *                                Output Filter, @ref CMP_Out_Filter
 *
 * @retval An en_result_t enumeration value:
 *              - Ok:             Successfully
 *              - ErrorInvalidParameter: CMPx or pointer of structure is invalid
 */
en_result_t CMP_NormalModeInit(M4_CMP_TypeDef *CMPx,
                     const stc_cmp_init_t* pstcCMP_InitStruct)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance and configuration structure*/
    if ((!IS_CMP_INSTANCE(CMPx)) || (NULL == pstcCMP_InitStruct))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCMP_InitStruct->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCMP_InitStruct->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCMP_InitStruct->u8OutPolarity));
        DDL_ASSERT(IS_CMP_CVSL(pstcCMP_InitStruct->u8CmpVol));
        DDL_ASSERT(IS_CMP_RVSL(pstcCMP_InitStruct->u8RefVol));

        /* Stop CMP compare */
        WRITE_REG(CMPx->MDR, 0x00U);

        /* Set compare voltage and reference voltage */
        WRITE_REG(CMPx->VSR,
                  pstcCMP_InitStruct->u8CmpVol | pstcCMP_InitStruct->u8RefVol);
        /* Delay 300ns*/
        CMP_Delay300ns();

        /* Start CMP compare */
        WRITE_REG(CMPx->MDR, CMP_MDR_CENB);
        /* Delay 300ns*/
        CMP_Delay300ns();

        /* Set output filter and output detect edge and output polarity */
        WRITE_REG(CMPx->FIR,
                  pstcCMP_InitStruct->u8OutFilter | pstcCMP_InitStruct->u8OutDetectEdges);
        WRITE_REG(CMPx->OCR, pstcCMP_InitStruct->u8OutPolarity);
    }
    return enRet;
}

/**
 * @brief  CMP window mode initialize
 * @param  [in] pstcCMP_InitStruct Configuration structure for window mode initialize
 *              pstcCMP_InitStruct->u8WinVolLow
 *                                CMP reference low voltage for window mode,
 *                                @ref CMP_RVSL_Source
 *              pstcCMP_InitStruct->u8WinVolHigh
 *                                CMP reference high voltage for window mode,
 *                                @ref CMP_RVSL_Source
 *              pstcCMP_InitStruct->u8OutPolarity
 *                                Output polarity select, @ref CMP_Out_Polarity_Select
 *              pstcCMP_InitStruct->u8OutDetectEdges
 *                                Output detect edge, @ref CMP_Out_Detect_Edge
 *              pstcCMP_InitStruct->u8OutFilter
 *                                Output Filter, @ref CMP_Out_Filter
 *
 * @retval An en_result_t enumeration value:
 *              - Ok:             Successfully
 *              - ErrorInvalidParameter: CMPx or pointer of structure is invalid
 */
en_result_t CMP_WindowModeInit(const stc_cmp_init_t* pstcCMP_InitStruct)
{
    en_result_t enRet = Ok;
    /* Check configuration structure */
    if (NULL == pstcCMP_InitStruct)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_CMP_OUT_DETECT_EDGE(pstcCMP_InitStruct->u8OutDetectEdges));
        DDL_ASSERT(IS_CMP_OUT_FILTER(pstcCMP_InitStruct->u8OutFilter));
        DDL_ASSERT(IS_CMP_OUT_POLARITY(pstcCMP_InitStruct->u8OutPolarity));
        DDL_ASSERT(IS_CMP_RVSL(pstcCMP_InitStruct->u8WinVolLow));
        DDL_ASSERT(IS_CMP_RVSL(pstcCMP_InitStruct->u8WinVolHigh));

        /* Stop CMP compare */
        WRITE_REG(M4_CMP2->MDR, 0x00U);
        WRITE_REG(M4_CMP3->MDR, 0x00U);

        /* Set compare voltage and reference voltage */
        WRITE_REG(M4_CMP3->VSR,
                  CMP_CVSL_IVCMPx_2 | pstcCMP_InitStruct->u8WinVolLow);
        WRITE_REG(M4_CMP2->VSR,
                  CMP_CVSL_IVCMPx_2 | pstcCMP_InitStruct->u8WinVolHigh);

        /* Select window compare mode and start CMP compare function */
        WRITE_REG(M4_CMP2->MDR, CMP_MDR_CENB | CMP_MDR_CWDE);
        WRITE_REG(M4_CMP3->MDR, CMP_MDR_CENB);
        /* Delay 300ns*/
        CMP_Delay300ns();

        /* Set output filter and output detect edge and output polarity */
        WRITE_REG(M4_CMP2->FIR,
                  pstcCMP_InitStruct->u8OutFilter | pstcCMP_InitStruct->u8OutDetectEdges);
        WRITE_REG(M4_CMP2->OCR, pstcCMP_InitStruct->u8OutPolarity);
    }
    return enRet;
}

/**
 * @brief  CMP 8 bit DAC reference voltage configuration
 * @param  [in] u8DACData         DAC voltage data
 *              @arg              This parameter can be one data range 0x00~0xFF
 *                                DAC Voltage = VCCA x u8DACData / 255
 * @param  [in] u8AlignMode       DAC data register align mode
 *              @arg              This parameter @ref CMP_DAC_Align_mode
 * @retval An en_result_t enumeration value:
 *              - Ok:             Set successfully
 */
en_result_t CMP_8BitDACCfg(uint8_t u8DACData, uint16_t u16AlignMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_CMP_DAC_ALIGN_MODE(u16AlignMode));

    if(CMP_DAC_ALIGN_RIGHT == u16AlignMode)
    {
        WRITE_REG16(M4_DAC->DADR1, u8DACData);
        CLEAR_REG16_BIT(M4_DAC->DACR1, CMP_DACR1_ALGN);
    }
    else
    {
        WRITE_REG16(M4_DAC->DADR1, u8DACData<<8U);
        SET_REG16_BIT(M4_DAC->DACR1, CMP_DACR1_ALGN);
    }
    return Ok;
}

/**
 * @brief  CMP 8 bit DAC reference voltage function command
 * @param  [in] enNewSta          The function new state.
 *              @arg              This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *              - Ok:             Set successfully
 */
en_result_t CMP_8BitDACCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    (Enable == enNewSta) ?
      SET_REG16_BIT(M4_DAC->DACR1, CMP_DACR1_DAEN) :
       CLEAR_REG16_BIT(M4_DAC->DACR1, CMP_DACR1_DAEN);

    return Ok;
}

/**
 * @brief  De-initialize CMP unit
 * @param  [in] CMPx              Pointer to CMP instance register base,This
 *                                parameter can be one of the following values:
 *              @arg M4_CMP1:     CMP unit 1 instance register base
 *              @arg M4_CMP2:     CMP unit 2 instance register base
 *              @arg M4_CMP3:     CMP unit 3 instance register base
 * @retval An en_result_t enumeration value:
 *              - Ok:             Successfully
 *              - ErrorInvalidParameter: CMPx or pointer of structure is invalid
 */
en_result_t CMP_DeInit(M4_CMP_TypeDef *CMPx)
{
    en_result_t enRet = Ok;
    /* Check CMPx instance */
    if (!IS_CMP_INSTANCE(CMPx))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        CMPx->MDR = 0x00U;
        CMPx->FIR = 0x00U;
        CMPx->OCR = 0x00U;
        CMPx->VSR = 0x00U;
        CMPx->TWR1 = 0x00U;
        CMPx->TWR2 = 0x00U;
    }
    return enRet;
}

/**
 * @brief  Initialize structure stc_cmp_init_t variable with default value.
 * @param  [out] pstcCMP_InitStruct     Pointer to a stc_cmp_init_t structure variable
 *                                      which will be initialized.
 *   @arg  See the struct @ref stc_cmp_init_t.
 * @retval en_result_t
 */
en_result_t CMP_StructInit(stc_cmp_init_t* pstcCMP_InitStruct)
{
    en_result_t enRet = Ok;
    if (pstcCMP_InitStruct == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcCMP_InitStruct->u8CmpVol = CMP_CVSL_NONE;
        pstcCMP_InitStruct->u8RefVol = CMP_RVSL_NONE;
        pstcCMP_InitStruct->u8OutDetectEdges = (uint8_t)CMP_DETECT_EDGS_NONE;
        pstcCMP_InitStruct->u8OutFilter = CMP_OUT_FILTER_NONE;
        pstcCMP_InitStruct->u8OutPolarity = CMP_OUT_REVERSE_OFF;
        pstcCMP_InitStruct->u8WinVolLow = CMP_RVSL_NONE;
        pstcCMP_InitStruct->u8WinVolHigh = CMP_RVSL_NONE;
    }
    return enRet;
}

/**
 * @}
 */

/**
 * @brief  Software delay 300ns.
 * @param  None
 *
 * @retval None
 */
static void CMP_Delay300ns(void)
{
    for(uint32_t i=0UL; i<(SystemCoreClock/3333333UL + 1UL); i++)
    {
        __NOP();
    }
}

#endif /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
