/**
 *******************************************************************************
 * @file  system_hc32m423.c
 * @brief This file provides two functions and one global variable to be called
 *        from  user application
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-01       Zhangxl         First version
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
#include "hc32_common.h"

/**
 * @addtogroup CMSIS
 * @{
 */

/**
 * @addtogroup HC32M423_System
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/**
 * @addtogroup HC32M423_System_Global_Variable
 * @{
 */

/*!< System clock frequency (Core clock) */
#if defined ( __GNUC__ ) && !defined (__CC_ARM) /*!< GNU Compiler */
__NO_INIT uint32_t SystemCoreClock;
#elif defined (__ICCARM__)                      /*!< IAR Compiler */
__NO_INIT uint32_t SystemCoreClock;
#else
uint32_t SystemCoreClock = HRC_VALUE;
#endif

/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @addtogroup HC32M423_System_Global_Functions
 * @{
 */

/**
 * @brief  Setup the microcontroller system. Initialize the System and update
 *         the SystemCoreClock variable.
 * @param  None
 * @retval None
 */
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif
    SystemCoreClockUpdate();
}

/**
 * @brief  Update HRC frequency according to Clock Register Values.
 * @param  None
 * @retval HRC frequency
 */
static uint32_t HrcUpdate(void)
{
    uint32_t Hrc_value = 0UL;
    uint8_t tmp = M4_EFM->HRCCFGR & 0x07U;

    if(EFM_HRCCFGR_HRCFREQS_3 == (M4_EFM->HRCCFGR & EFM_HRCCFGR_HRCFREQS_3))
    {
        switch(tmp)
        {
            case 0x00:
                Hrc_value = (uint32_t)32000000UL * 3UL / 2UL;
                break;
            case 0x01:
                Hrc_value = (uint32_t)16000000UL * 3UL / 2UL;
                break;
            case 0x02:
                Hrc_value = (uint32_t)8000000UL * 3UL / 2UL;
                break;
            case 0x03:
                Hrc_value = (uint32_t)4000000UL * 3UL / 2UL;
                break;
            case 0x04:
                Hrc_value = (uint32_t)2000000UL * 3UL / 2UL;
                break;
            default:
                Hrc_value = (uint32_t)1000000UL * 3UL / 2UL;
                break;
        }
    }
    else
    {
        switch(tmp)
        {
            case 0x00:
                Hrc_value = (uint32_t)32000000UL;
                break;
            case 0x01:
                Hrc_value = (uint32_t)16000000UL;
                break;
            case 0x02:
                Hrc_value = (uint32_t)8000000UL;
                break;
            case 0x03:
                Hrc_value = (uint32_t)4000000UL;
                break;
            case 0x04:
                Hrc_value = (uint32_t)2000000UL;
                break;
            default:
                Hrc_value = (uint32_t)1000000UL;
                break;
        }
    }

    return Hrc_value;
}

/**
 * @brief  Update PLL frequency according to Clock Register Values.
 * @param  None
 * @retval PLL frequency
 */
static uint32_t PllUpdate(void)
{
    uint32_t pll_value = 0UL;
    uint32_t pllsrc_value = 0UL;
    uint32_t plln = 0UL, pllp = 0UL, pllm = 0UL;

    /* PLL clock source frequency */
    pllsrc_value = (0UL == (M4_CMU->PLLCFGR & CMU_PLLCFGR_PLLSRC)) ? XTAL_VALUE : HrcUpdate();

    /* PLLPCLK = ((pllsrc / pllm) * plln) / pllp */
    plln = (M4_CMU->PLLCFGR & CMU_PLLCFGR_PLLN) >> CMU_PLLCFGR_PLLN_POS;
    pllp = (M4_CMU->PLLCFGR & CMU_PLLCFGR_PLLP) >> CMU_PLLCFGR_PLLP_POS;
    pllm = (M4_CMU->PLLCFGR & CMU_PLLCFGR_PLLM);
    pll_value = (pllsrc_value) / (pllm + 1UL) * (plln + 1UL) / (pllp + 1UL);

    return pll_value;
}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 * @param  None
 * @retval None
 */
void SystemCoreClockUpdate(void)
{
    uint8_t u8SysClkSrc = 0U;
    uint32_t u32SysClk = 0UL;
    uint32_t u32SysClkDiv = 0UL;

    u8SysClkSrc = M4_CMU->CKSWR & CMU_CKSWR_CKSW;
    switch(u8SysClkSrc)
    {
        case 0x00U:  /* use internal high speed RC */
            u32SysClk = HrcUpdate();
            break;
        case 0x01U:  /* use internal middle speed RC */
            u32SysClk = MRC_VALUE;
            break;
        case 0x02U:  /* use internal low speed RC */
            u32SysClk = LRC_VALUE;
            break;
        case 0x03U:  /* use external high speed RC */
            u32SysClk = XTAL_VALUE;
            break;
        case 0x05U:  /* use external high speed RC */
            u32SysClk = PllUpdate();
            break;
    }

    u32SysClkDiv = ((M4_CMU->SCFGR & CMU_SCFGR_HCLKS) >> CMU_SCFGR_HCLKS_POS);
    SystemCoreClock = (u32SysClk << u32SysClkDiv);
}

#if defined (__CC_ARM) || defined (__CLANG_ARM)
extern int32_t $Super$$main(void);
/* re-define main function: keil */
int $Sub$$main(void)
{
    SystemCoreClockUpdate();
    $Super$$main();
    return 0;
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
