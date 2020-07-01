/**
 *******************************************************************************
 * @file  hc32m423_swdt.c
 * @brief This file provides firmware functions to manage the Special Watch Dog
 *        Timer(SWDT).
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
#include "hc32m423_swdt.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_SWDT SWDT
 * @brief Special Watch Dog Timer
 * @{
 */

#if (DDL_SWDT_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SWDT_Local_Macros SWDT Local Macros
 * @{
 */

/**
 * @defgroup SWDT_Refresh_Key SWDT Refresh Key
 * @{
 */
#define SWDT_REFRESH_KEY_START          ((uint16_t)0x0123U)
#define SWDT_REFRESH_KEY_END            ((uint16_t)0x3210U)
/**
 * @}
 */

/**
 * @defgroup SWDT_Check_Parameters_Validity SWDT Check Parameters Validity
 * @{
 */
#define IS_SWDT_FLAG(x)                                                        \
(   (SWDT_FLAG_COUNT_UNDERFLOW == (x))          ||                             \
    (SWDT_FLAG_REFRESH_ERROR == (x)))
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
 * @defgroup SWDT_Global_Functions SWDT Global Functions
 * @{
 */

/**
 * @brief  SWDT reload counter
 * @note   In software startup mode, Start counter when refreshing for the first time.
 * @param  None
 * @retval None
 */
void SWDT_ReloadCounter(void)
{
    WRITE_REG32(M4_SWDT->RR, SWDT_REFRESH_KEY_START);
    WRITE_REG32(M4_SWDT->RR, SWDT_REFRESH_KEY_END);
}

/**
 * @brief  Get SWDT flag status.
 * @param  [in] u32Flag                 Specifies the SWDT flag type.
 *                                      This parameter can be one of the following values:
 *   @arg  SWDT_FLAG_COUNT_UNDERFLOW: Count Underflow flag
 *   @arg  SWDT_FLAG_REFRESH_ERROR:   Refresh Error flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t SWDT_GetFlag(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_SWDT_FLAG(u32Flag));

    if (Reset != (READ_REG32_BIT(M4_SWDT->SR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear SWDT flag.
 * @param  [in] u32Flag                 Specifies the SWDT flag type.
 *                                      This parameter can be one or a combination of the following values:
 *   @arg  SWDT_FLAG_COUNT_UNDERFLOW: Count Underflow flag
 *   @arg  SWDT_FLAG_REFRESH_ERROR:   Refresh Error flag
 * @retval An en_result_t enumeration value:
 *           - Ok: Clear flag success
 *           - ErrorTimeout: Clear flag timeout
 */
en_result_t SWDT_ClearFlag(uint32_t u32Flag)
{
    uint32_t u32Timeout = 0UL;
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_SWDT_FLAG(u32Flag));

    /* Waiting for FLAG bit clear */
    u32Timeout = SystemCoreClock >> 8U;
    do
    {
        CLEAR_REG32_BIT(M4_SWDT->SR, u32Flag);
    } while ((Reset != (READ_REG32_BIT(M4_SWDT->SR, u32Flag))) && (--u32Timeout));

    if (0U == u32Timeout)
    {
        enRet = ErrorTimeout;
    }

    return enRet;
}

/**
 * @}
 */

#endif /* DDL_SWDT_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
