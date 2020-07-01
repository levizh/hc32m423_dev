/**
 *******************************************************************************
 * @file  hc32m423_cmp.h
 * @brief Head file for CMP module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-06       Wangmin         First version
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
#ifndef __HC32M423_CMP_H__
#define __HC32M423_CMP_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_CMP
 * @{
 */

#if (DDL_CMP_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CMP_Global_Types CMP Global Types
 * @{
 */

/**
 * @brief CMP configuration structure
 */
typedef struct
{
    uint8_t u8CmpVol;              /*!< Compare voltage for normal mode
                                        @ref CMP_CVSL_Source */
    uint8_t u8RefVol;              /*!< Reference voltage for normal mode ,
                                        @ref CMP_RVSL_Source*/

    uint8_t u8WinVolLow;           /*!< CMP reference low voltage for window mode
                                        @ref CMP_RVSL_Source */
    uint8_t u8WinVolHigh;          /*!< CMP reference high voltage for window mode
                                        @ref CMP_RVSL_Source */

    uint8_t u8OutPolarity;         /*!< Output polarity select, @ref CMP_Out_Polarity_Select */
    uint8_t u8OutDetectEdges;      /*!< Output detecte edge, @ref CMP_Out_Detect_Edge */
    uint8_t u8OutFilter;           /*!< Output Filter, @ref CMP_Out_Filter */
}stc_cmp_init_t;


/**
 * @brief CMP timer windows function configuration structure
 */
typedef struct
{
    uint8_t u8TWMode;               /*!< Timer windows mode enable, @ref CMP_TimerWin_func */
    uint8_t u8TWSelect;             /*!< Timer windows source select, @ref CMP1_TimerWin_Select or @ref CMP2_TimerWin_Select */
    uint8_t u8TWOutLevel;           /*!< Timer windows mode output level @ref CMP_TimerWin_output_Level*/
    uint8_t u8TWInvalidLevel;       /*!< Output level when timer windows invalid, @ref CMP_TimerWin_Invalid_Level */
}stc_cmp_timerwindows_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/**
 * @defgroup CMP_Global_Macros CMP Global Macros
 * @{
 */

/** @defgroup CMP_Unit CMP Unit definition
  * @{
  */
#define CMP_UNIT1                (M0P_CMP1)
#define CMP_UNIT2                (M0P_CMP2)
/**
 * @}
 */

/** @defgroup CMP_Mode CMP compare mode
  * @{
  */
#define CMP_MODE_NORMAL          0U
#define CMP_MODE_WINDOW          (CMP_MDR_CWDE)
/**
 * @}
 */

/** @defgroup CMP_CVSL_Source CMP compare voltage selection for CMP1/CMP2/CMP3
  * @{
  */
/* Don't input compare voltage */
#define CMP_CVSL_NONE           0U
/* Select pin IVCMP1_0/IVCMP2_0/IVCMP3_0 as compare voltage */
#define CMP_CVSL_IVCMPx_0        (CMP_VSR_CVSL_0)
/* Select pin IVCMP1_1/IVCMP2_1/IVCMP3_1 as compare voltage */
#define CMP_CVSL_IVCMPx_1        (CMP_VSR_CVSL_1)
/* Select pin IVCMP1_2/IVCMP2_2/IVCMP3_2 as compare voltage */
#define CMP_CVSL_IVCMPx_2        (CMP_VSR_CVSL_2)
/* Select pin Vref as compare voltage */
#define CMP_CVSL_VREF           (CMP_VSR_CVSL_3)
/**
 * @}
 */

/** @defgroup CMP_RVSL_Source CMP reference voltage selection for CMP1/CMP2/CMP3
  * @{
  */
/* Don't input reference voltage */
#define CMP_RVSL_NONE           0U
/* Select pin IVREF1 as reference voltage */
#define CMP_RVSL_IVREF1         (CMP_VSR_RVSL_0)
/* Select pin IVREF2 as reference voltage */
#define CMP_RVSL_IVREF2         (CMP_VSR_RVSL_1)
/* Select 8 bit DAC as reference voltage */
#define CMP_RVSL_DAC            (CMP_VSR_RVSL_2)
/**
 * @}
 */

/** @defgroup CMP_Out_Polarity_Select CMP output polarity selection
  * @{
  */
/* CMP output don't reverse */
#define CMP_OUT_REVERSE_OFF          0U
/* CMP output level reverse */
#define CMP_OUT_REVERSE_ON           (CMP_OCR_COPS)
/**
 * @}
 */

/** @defgroup CMP_Out_Detect_Edge CMP output detect edge selection
  * @{
  */
#define CMP_DETECT_EDGS_NONE        ((uint8_t)0UL)
#define CMP_DETECT_EDGS_RISING      ((uint8_t)(1UL << CMP_FIR_EDGS_POS))
#define CMP_DETECT_EDGS_FALLING     ((uint8_t)(2UL << CMP_FIR_EDGS_POS))
#define CMP_DETECT_EDGS_BOTH        ((uint8_t)(3UL << CMP_FIR_EDGS_POS))
/**
 * @}
 */

/** @defgroup CMP_Out_Filter CMP output filter configuration
  * @{
  */
#define CMP_OUT_FILTER_NONE         0U
#define CMP_OUT_FILTER_PCLK         1U
#define CMP_OUT_FILTER_PCLKDIV8     2U
#define CMP_OUT_FILTER_PCLKDIV32    3U
/**
 * @}
 */

/** @defgroup CMP_TimerWin_func CMP timer window function configuration
  * @{
  */
#define CMP_TIMERWIN_OFF            0U
#define CMP_TIMERWIN_ON             (CMP_OCR_TWOE)
/**
 * @}
 */

/** @defgroup CMP_TimerWin_Select CMP output timer windows function control signal definition for CMP1
  * @{
  */
/* CMP1 chose TIMB_1_PWM1 as timer window signal; CMP2 chose TIMB_1_PWM3 as
   timer window signal; CMP3 chose TIMB_1_PWM5 as timer window signal */
#define CMP_TIMERWIN_TIMB_1_PWM1_3_5  (CMP_TWR1_CTWS0)
/* CMP1 chose TIMB_1_PWM2 as timer window signal; CMP2 chose TIMB_1_PWM4 as
   timer window signal; CMP3 chose TIMB_1_PWM6 as timer window signal */
#define CMP_TIMERWIN_TIMB_1_PWM2_4_6  (CMP_TWR1_CTWS1)
/* Chose TIM4_OWL as timer window signal */
#define CMP_TIMERWIN_TIM4_OWL         (CMP_TWR1_CTWS2)
/* Chose TIM4_OWH as timer window signal */
#define CMP_TIMERWIN_TIM4_OWH         (CMP_TWR1_CTWS3)
/* Chose TIM4_OVL as timer window signal */
#define CMP_TIMERWIN_TIM4_OVL         (CMP_TWR1_CTWS4)
/* Chose TIM4_OVH as timer window signal */
#define CMP_TIMERWIN_TIM4_OVH         (CMP_TWR1_CTWS5)
/* Chose TIM4_OUL as timer window signal */
#define CMP_TIMERWIN_TIM4_OUL         (CMP_TWR1_CTWS6)
/* Chose TIM4_OUH as timer window signal */
#define CMP_TIMERWIN_TIM4_OUH         (CMP_TWR1_CTWS7)
/**
 * @}
 */

/** @defgroup CMP_TimerWin_Invalid_Level CMP output level when timer window invalid
  * @{
  */
#define CMP_TIMERWIN_INVALID_LEVEL_LOW   0U
#define CMP_TIMERWIN_INVALID_LEVEL_HIGH  (CMP_OCR_TWOL)
/**
 * @}
 */

/** @defgroup CMP_TimerWin_output_Level CMP output level in timer windows mode
  * @{
  */
#define CMP_TIMERWIN_OUT_LEVEL_LOW       0U
#define CMP_TIMERWIN_OUT_LEVEL_HIGH      1U
/**
 * @}
 */

/** @defgroup CMP_DAC_Align_mode CMP DAC data align mode
  * @{
  */
#define CMP_DAC_ALIGN_RIGHT             0U
#define CMP_DAC_ALIGN_LEFT              (CMP_DACR1_ALGN)
/**
 * @}
 */


/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup CMP_Global_Functions
 * @{
 */
en_result_t CMP_StructInit(stc_cmp_init_t* pstcCMP_InitStruct);
en_result_t CMP_DeInit(M4_CMP_TypeDef *CMPx);
en_result_t CMP_NormalModeInit(M4_CMP_TypeDef *CMPx,
                     const stc_cmp_init_t* pstcCMP_InitStruct);
en_result_t CMP_WindowModeInit(const stc_cmp_init_t* pstcCMP_InitStruct);

en_result_t CMP_TimerWindowsCfg(M4_CMP_TypeDef *CMPx,
                                 const stc_cmp_timerwindows_t* pstcCMP_TimerWinStruct);

en_result_t CMP_FuncCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta);
en_result_t CMP_IntCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta);
en_result_t CMP_OutputCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta);
en_result_t CMP_VCOUTCmd(M4_CMP_TypeDef *CMPx, en_functional_state_t enNewSta);

en_result_t CMP_ResultGet(M4_CMP_TypeDef *CMPx, en_flag_status_t* penFunSta);

en_result_t CMP_8BitDACCfg(uint8_t u8DACData, uint16_t u16AlignMode);
en_result_t CMP_8BitDACCmd(en_functional_state_t enNewSta);

/**
 * @}
 */

#endif /* DDL_CMP_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_CMP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
