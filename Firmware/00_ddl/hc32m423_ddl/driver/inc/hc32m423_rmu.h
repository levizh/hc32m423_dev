/**
 *******************************************************************************
 * @file  hc32m423_rmu.h
 * @brief Head file for RMU module.
 *
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-05       Heqb         First version
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
#ifndef __HC32M423_RMU_H__
#define __HC32M423_RMU_H__

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
 * @addtogroup DDL_RMU
 * @{
 */

#if (DDL_RMU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RMU_Global_Macros RMU Global Macros
 * @{
 */

/**
 * @defgroup RMU_ResetCause Rmu reset cause
 * @{
 */
#define RMU_RST_POWER_ON              (RMU_RSTF0_PORF)        /*!< Power on reset */
#define RMU_RST_RESET_PIN             (RMU_RSTF0_PINRF)       /*!< Reset pin reset */
#define RMU_RST_LVD0                  (RMU_RSTF0_LV0RF)       /*!< Low voltage Detection 0 reset */
#define RMU_RST_LVD1                  (RMU_RSTF0_LV1RF)       /*!< Low voltage Detection 1 reset */
#define RMU_RST_LVD2                  (RMU_RSTF0_LV2RF)       /*!< Low voltage Detection 2 reset */
#define RMU_RST_WDT                   (RMU_RSTF0_WDRF)        /*!< Watchdog timer reset */
#define RMU_RST_SWDT                  (RMU_RSTF0_SWDRF)       /*!< Special watchdog timer reset */
#define RMU_RST_SOFTWARE              (RMU_RSTF0_SWRF)        /*!< Software reset */
#define RMU_RST_RAM_PARITY_ERR        (RMU_RSTF0_RAPERF)      /*!< Ram parity error reset */
#define RMU_RST_CLK_ERR               (RMU_RSTF0_CKFERF)      /*!< Clk frequence error reset */
#define RMU_RST_XTAL_ERR              (RMU_RSTF0_XTALERF)     /*!< Xtal error reset */
#define RMU_RST_CPU_LOCKUP            (RMU_RSTF0_CPULKUPRF)   /*!< M4 Lockup reset */
#define RMU_RST_MUULTI                (RMU_RSTF0_MULTIRF)     /*!< Multiply reset cause */
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
 * @addtogroup RMU_Global_Functions
 * @{
 */
en_result_t RMU_GetResetCause(uint32_t u32RmuRstCause);
en_result_t RMU_ClrResetFlag(void);
/**
 * @}
 */

#endif /* DDL_RMU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_RMU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
