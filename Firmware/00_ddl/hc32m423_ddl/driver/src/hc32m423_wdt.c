/**
 *******************************************************************************
 * @file  hc32m423_wdt.c
 * @brief This file provides firmware functions to manage the Watch Dog
 *        Timer(WDT).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32m423_wdt.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_WDT WDT
 * @brief Special Watch Dog Timer
 * @{
 */

#if (DDL_WDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup WDT_Local_Macros WDT Local Macros
 * @{
 */

/**
 * @defgroup WDT_Registers_Clear_Mask WDT Registers Clear Mask
 * @{
 */
#define WDT_CR_CLEAR_MASK               (WDT_CR_PERI | WDT_CR_CKS | WDT_CR_WDPT | \
                                         WDT_CR_SLPOFF | WDT_CR_ITS)
/**
 * @}
 */

/**
 * @defgroup WDT_Refresh_Key WDT Refresh Key
 * @{
 */
#define WDT_REFRESH_KEY_START          ((uint16_t)0x0123U)
#define WDT_REFRESH_KEY_END            ((uint16_t)0x3210U)
/**
 * @}
 */

/**
 * @defgroup WDT_Check_Parameters_Validity WDT Check Parameters Validity
 * @{
 */
#define IS_WDT_COUNTER_CYCLE(x)                                               \
(   (WDT_COUNTER_CYCLE_256 == (x))             ||                             \
    (WDT_COUNTER_CYCLE_4096 == (x))            ||                             \
    (WDT_COUNTER_CYCLE_16384 == (x))           ||                             \
    (WDT_COUNTER_CYCLE_65536 == (x)))

#define IS_WDT_CLOCK_DIVISION(x)                                              \
(   (WDT_CLOCK_DIV4 == (x))                    ||                             \
    (WDT_CLOCK_DIV64 == (x))                   ||                             \
    (WDT_CLOCK_DIV128 == (x))                  ||                             \
    (WDT_CLOCK_DIV256 == (x))                  ||                             \
    (WDT_CLOCK_DIV512 == (x))                  ||                             \
    (WDT_CLOCK_DIV1024 == (x))                 ||                             \
    (WDT_CLOCK_DIV2048 == (x))                 ||                             \
    (WDT_CLOCK_DIV8192 == (x)))

#define IS_WDT_ALLOW_REFRESH_RANGE(x)                                         \
(   (WDT_RANGE_100PCT == (x))                  ||                             \
    (WDT_RANGE_0TO25PCT == (x))                ||                             \
    (WDT_RANGE_25TO50PCT == (x))               ||                             \
    (WDT_RANGE_0TO50PCT == (x))                ||                             \
    (WDT_RANGE_50TO75PCT == (x))               ||                             \
    (WDT_RANGE_0TO25PCT_50TO75PCT == (x))      ||                             \
    (WDT_RANGE_25TO75PCT == (x))               ||                             \
    (WDT_RANGE_0TO75PCT == (x))                ||                             \
    (WDT_RANGE_75TO100PCT == (x))              ||                             \
    (WDT_RANGE_0TO25PCT_75TO100PCT == (x))     ||                             \
    (WDT_RANGE_25TO50PCT_75TO100PCT == (x))    ||                             \
    (WDT_RANGE_0TO50PCT_75TO100PCT == (x))     ||                             \
    (WDT_RANGE_50TO100PCT == (x))              ||                             \
    (WDT_RANGE_0TO25PCT_50TO100PCT == (x))     ||                             \
    (WDT_RANGE_25TO100PCT == (x))              ||                             \
    (WDT_RANGE_0TO100PCT == (x)))

#define IS_WDT_LPW_MODE_COUNT(x)                                              \
(   (WDT_LPW_MODE_COUNT_CONTINUE == (x))       ||                             \
    (WDT_LPW_MODE_COUNT_STOP == (x)))

#define IS_WDT_REQUEST_TYPE(x)                                                \
(   (WDT_TRIG_EVENT_INT == (x))                ||                             \
    (WDT_TRIG_EVENT_RESET == (x)))

#define IS_WDT_FLAG(x)                                                        \
(   (WDT_FLAG_COUNT_UNDERFLOW == (x))          ||                             \
    (WDT_FLAG_REFRESH_ERROR == (x)))
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
 * @defgroup WDT_Global_Functions WDT Global Functions
 * @{
 */

/**
 * @brief  Initialize WDT.
 * @param  [in] pstcWdtInit             Pointer to a stc_wdt_init_t structure
 *                                      that contains configuration information.
 *   @arg  See the struct @ref stc_wdt_init_t.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t WDT_Init(const stc_wdt_init_t *pstcWdtInit)
{
    en_result_t enRet = Ok;

    if(NULL == pstcWdtInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_WDT_COUNTER_CYCLE(pstcWdtInit->u32CountCycle));
        DDL_ASSERT(IS_WDT_CLOCK_DIVISION(pstcWdtInit->u32ClockDivision));
        DDL_ASSERT(IS_WDT_ALLOW_REFRESH_RANGE(pstcWdtInit->u32RefreshRange));
        DDL_ASSERT(IS_WDT_LPW_MODE_COUNT(pstcWdtInit->u32LPModeCountEn));
        DDL_ASSERT(IS_WDT_REQUEST_TYPE(pstcWdtInit->u32RequestType));

        /* WDT CR Configuration(Software Start Mode) */
        MODIFY_REG32(M4_WDT->CR, WDT_CR_CLEAR_MASK,
                    (pstcWdtInit->u32CountCycle   | pstcWdtInit->u32ClockDivision |
                     pstcWdtInit->u32RefreshRange | pstcWdtInit->u32LPModeCountEn |
                     pstcWdtInit->u32RequestType));
    }

    return enRet;
}

/**
 * @brief  WDT reload counter
 * @note   In software startup mode, Start counter when refreshing for the first time.
 * @param  None
 * @retval None
 */
void WDT_ReloadCounter(void)
{
    WRITE_REG32(M4_WDT->RR, WDT_REFRESH_KEY_START);
    WRITE_REG32(M4_WDT->RR, WDT_REFRESH_KEY_END);
}

/**
 * @brief  Get WDT flag status.
 * @param  [in] u32Flag                 Specifies the WDT flag type.
 *                                      This parameter can be one of the following values:
 *   @arg  WDT_FLAG_COUNT_UNDERFLOW: Count Underflow flag
 *   @arg  WDT_FLAG_REFRESH_ERROR:   Refresh Error flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t WDT_GetFlag(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_WDT_FLAG(u32Flag));

    if (Reset != (READ_REG32_BIT(M4_WDT->SR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear WDT flag.
 * @param  [in] u32Flag                 Specifies the WDT flag type.
 *                                      This parameter can be one or a combination of the following values:
 *   @arg  WDT_FLAG_COUNT_UNDERFLOW: Count Underflow flag
 *   @arg  WDT_FLAG_REFRESH_ERROR:   Refresh Error flag
 * @retval An en_result_t enumeration value:
 *           - Ok: Clear flag success
 *           - ErrorTimeout: Clear flag timeout
 */
en_result_t WDT_ClearFlag(uint32_t u32Flag)
{
    uint32_t u32Timeout = 0UL;
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_WDT_FLAG(u32Flag));

    /* Waiting for FLAG bit clear */
    u32Timeout = SystemCoreClock >> 8U;
    do
    {
        CLEAR_REG32_BIT(M4_WDT->SR, u32Flag);
    } while ((Reset != (READ_REG32_BIT(M4_WDT->SR, u32Flag))) && (--u32Timeout));

    if (0U == u32Timeout)
    {
        enRet = ErrorTimeout;
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
