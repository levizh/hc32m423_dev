/**
 *******************************************************************************
 * @file  hc32m423_wdt.h
 * @brief This file contains all the functions prototypes of the WDT driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-04       Yangjp          First version
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
#ifndef __HC32M423_WDT_H__
#define __HC32M423_WDT_H__

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
 * @addtogroup DDL_WDT
 * @{
 */

#if (DDL_WDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup WDT_Global_Types WDT Global Types
 * @{
 */

/**
 * @brief WDT Init structure definition
 */
typedef struct
{
    uint32_t u32CountCycle;     /*!< Specifies the WDT Count Cycle.
                                     This parameter can be a value of @ref WDT_Counter_Cycle */
    uint32_t u32ClockDivision;  /*!< Specifies the WDT Clock Division.
                                     This parameter can be a value of @ref WDT_Clock_Division */
    uint32_t u32RefreshRange;   /*!< Specifies the WDT Allow Refresh Range.
                                     This parameter can be a value of @ref WDT_Refresh_Percent_Range */
    uint32_t u32LPModeCountEn;  /*!< Specifies the WDT Count Enable/Disable In Low Power Mode(Sleep Mode).
                                     This parameter can be a value of @ref WDT_LPW_Mode_Count */
    uint32_t u32RequestType;    /*!< Specifies the WDT Refresh Error or Count Underflow Request Type.
                                     This parameter can be a value of @ref WDT_Trigger_Event_Type */
} stc_wdt_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WDT_Global_Macros WDT Global Macros
 * @{
 */

/**
 * @defgroup WDT_Counter_Cycle WDT Counter Cycle
 * @{
 */
#define WDT_COUNTER_CYCLE_256                   ((uint32_t)0x00000000UL)   /*!< 256 clock cycle */
#define WDT_COUNTER_CYCLE_4096                  ((uint32_t)WDT_CR_PERI_0)  /*!< 4096 clock cycle */
#define WDT_COUNTER_CYCLE_16384                 ((uint32_t)WDT_CR_PERI_1)  /*!< 16384 clock cycle */
#define WDT_COUNTER_CYCLE_65536                 ((uint32_t)WDT_CR_PERI)    /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup WDT_Clock_Division WDT Clock Division
 * @{
 */
#define WDT_CLOCK_DIV4                          ((uint32_t)WDT_CR_CKS_1)                                  /*!< PCLK1/4 */
#define WDT_CLOCK_DIV64                         ((uint32_t)(WDT_CR_CKS_1 | WDT_CR_CKS_2))                 /*!< PCLK1/64 */
#define WDT_CLOCK_DIV128                        ((uint32_t)(WDT_CR_CKS_0 | WDT_CR_CKS_1 | WDT_CR_CKS_2))  /*!< PCLK1/128 */
#define WDT_CLOCK_DIV256                        ((uint32_t)WDT_CR_CKS_3)                                  /*!< PCLK1/256 */
#define WDT_CLOCK_DIV512                        ((uint32_t)(WDT_CR_CKS_0 | WDT_CR_CKS_3))                 /*!< PCLK1/512 */
#define WDT_CLOCK_DIV1024                       ((uint32_t)(WDT_CR_CKS_1 | WDT_CR_CKS_3))                  /*!< PCLK1/1024 */
#define WDT_CLOCK_DIV2048                       ((uint32_t)(WDT_CR_CKS_0 | WDT_CR_CKS_1 | WDT_CR_CKS_3))  /*!< PCLK1/2048 */
#define WDT_CLOCK_DIV8192                       ((uint32_t)(WDT_CR_CKS_0 | WDT_CR_CKS_2 | WDT_CR_CKS_3))  /*!< PCLK1/8192 */
/**
 * @}
 */

/**
 * @defgroup WDT_Refresh_Percent_Range WDT Refresh Percent Range
 * @{
 */
#define WDT_RANGE_100PCT                        ((uint32_t)0x00000000UL)                                     /*!< 100% */
#define WDT_RANGE_0TO25PCT                      ((uint32_t)WDT_CR_WDPT_0)                                    /*!< 0%~25% */
#define WDT_RANGE_25TO50PCT                     ((uint32_t)WDT_CR_WDPT_1)                                    /*!< 25%~50% */
#define WDT_RANGE_0TO50PCT                      ((uint32_t)(WDT_CR_WDPT_0 | WDT_CR_WDPT_1))                  /*!< 0%~50% */
#define WDT_RANGE_50TO75PCT                     ((uint32_t)WDT_CR_WDPT_2)                                    /*!< 50%~75% */
#define WDT_RANGE_0TO25PCT_50TO75PCT            ((uint32_t)(WDT_CR_WDPT_0 | WDT_CR_WDPT_2))                  /*!< 0%~25% & 50%~75% */
#define WDT_RANGE_25TO75PCT                     ((uint32_t)(WDT_CR_WDPT_1 | WDT_CR_WDPT_2))                  /*!< 25%~75% */
#define WDT_RANGE_0TO75PCT                      ((uint32_t)(WDT_CR_WDPT_0 | WDT_CR_WDPT_1 | WDT_CR_WDPT_2))  /*!< 0%~75% */
#define WDT_RANGE_75TO100PCT                    ((uint32_t)WDT_CR_WDPT_3)                                    /*!< 75%~100% */
#define WDT_RANGE_0TO25PCT_75TO100PCT           ((uint32_t)(WDT_CR_WDPT_0 | WDT_CR_WDPT_3))                  /*!< 0%~25% & 75%~100% */
#define WDT_RANGE_25TO50PCT_75TO100PCT          ((uint32_t)(WDT_CR_WDPT_1 | WDT_CR_WDPT_3))                  /*!< 25%~50% & 75%~100% */
#define WDT_RANGE_0TO50PCT_75TO100PCT           ((uint32_t)(WDT_CR_WDPT_0 | WDT_CR_WDPT_1 | WDT_CR_WDPT_3))  /*!< 0%~50% & 75%~100% */
#define WDT_RANGE_50TO100PCT                    ((uint32_t)(WDT_CR_WDPT_2 | WDT_CR_WDPT_3))                  /*!< 50%~100% */
#define WDT_RANGE_0TO25PCT_50TO100PCT           ((uint32_t)(WDT_CR_WDPT_0 | WDT_CR_WDPT_2 | WDT_CR_WDPT_3))  /*!< 0%~25% & 50%~100% */
#define WDT_RANGE_25TO100PCT                    ((uint32_t)(WDT_CR_WDPT_1 | WDT_CR_WDPT_2 | WDT_CR_WDPT_3))  /*!< 25%~100% */
#define WDT_RANGE_0TO100PCT                     ((uint32_t)WDT_CR_WDPT)                                      /*!< 0%~100% */
/**
 * @}
 */

/**
 * @defgroup WDT_LPW_Mode_Count WDT Low Power Mode Count
 * @brief WDT count control in the sleep mode
 * @{
 */
#define WDT_LPW_MODE_COUNT_CONTINUE             ((uint32_t)0x00000000UL)    /*!< WDT count continue in the sleep mode */
#define WDT_LPW_MODE_COUNT_STOP                 ((uint32_t)WDT_CR_SLPOFF)   /*!< WDT count stop in the sleep mode */
/**
 * @}
 */

/**
* @defgroup WDT_Trigger_Event_Type WDT Trigger Event Type
* @{
*/
#define WDT_TRIG_EVENT_INT                      ((uint32_t)0x00000000UL)  /*!< WDT trigger interrupt */
#define WDT_TRIG_EVENT_RESET                    ((uint32_t)WDT_CR_ITS)    /*!< WDT trigger reset */
/**
 * @}
 */

/**
 * @defgroup WDT_Flag WDT Flag
 * @{
 */
#define WDT_FLAG_COUNT_UNDERFLOW                ((uint32_t)WDT_SR_UDF)
#define WDT_FLAG_REFRESH_ERROR                  ((uint32_t)WDT_SR_REF)
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
 * @addtogroup WDT_Global_Functions
 * @{
 */

/**
 * @brief  Get WDT count value.
 * @param  None
 * @retval Count value
 */
__STATIC_INLINE uint16_t WDT_GetCountValue(void)
{
    return (uint16_t)(READ_REG32(M4_WDT->SR) & WDT_SR_CNT);
}

/* Initialization and configuration functions */
en_result_t WDT_Init(const stc_wdt_init_t *pstcWdtInit);
void WDT_ReloadCounter(void);

/* Flags management functions */
en_flag_status_t WDT_GetFlag(uint32_t u32Flag);
en_result_t WDT_ClearFlag(uint32_t u32Flag);

/**
 * @}
 */

#endif /* DDL_WDT_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_WDT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
