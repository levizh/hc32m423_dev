/**
 *******************************************************************************
 * @file  clk/clk_switch_sysclk/source/main.c
 * @brief Main program of CLK for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-06-28       chengy          First version
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
 * @addtogroup CLK_Switch_sysclk
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 * @brief  Wait SW1 key short press.
 * @param  None
 * @retval None
 */
static void WaitSw1_ShortPress(void)
{
    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPortPin(GPIO_PORT_2, GPIO_PIN_2));
    DDL_Delay1ms(5);

    /* Wait key down */
    while(Pin_Reset != GPIO_ReadInputPortPin(GPIO_PORT_2, GPIO_PIN_2));
    DDL_Delay1ms(5);

    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPortPin(GPIO_PORT_2, GPIO_PIN_2));
    DDL_Delay1ms(5);
}

/**
 * @brief  Main function of CLK project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_clk_xtal_init_t     stcXTALInit;
    stc_clk_div_cfg_t       stcSysClkDiv;
    stc_clk_pll_cfg_t       stcPllCfg;
#if 1
    /* Confiure clock output system clock */
    CLK_MCOConfig(CLK_MCOSOURCCE_HCLK, CLK_MCODIV_8);
    /* Confiure clock output pin */
    GPIO_SetFunc(GPIO_PORT_7, GPIO_PIN_0, GPIO_FUNC_1_MCO);
    CLK_MCOCmd(Enable);

    /* Set bus clk div. */
    stcSysClkDiv.u32HclkDiv = CLK_HCLK_DIV1;   // Max 80MHz
    stcSysClkDiv.u32Pclk1Div = CLK_PCLK1_DIV2;  // Max 40MHz
    stcSysClkDiv.u32Pclk4Div = CLK_PCLK4_DIV2;  // Max 40MHz
    CLK_SetSysclkDiv(&stcSysClkDiv);

    /* SW1 */
    //WaitSw1_ShortPress();

    /* Update HRC to 32MHz */
    //CLK_HRCInit(CLK_HRC_ON, CLK_HRCFREQ_32);

    /* Configure XTAL */
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTALMODE_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTALDRV_HIGH;
    stcXTALInit.u8XtalSupDrv = CLK_XTAL_SUPDRV_OFF;
    stcXTALInit.u8XtalStb = CLK_XTALSTB_8;

    CLK_XTALInit(&stcXTALInit);

    /* SW1 */
    //WaitSw1_ShortPress();

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysclkSrc(CLK_SYSCLKSOURCE_XTAL);

    /* PLL config (XTAL / pllmDiv * plln / PllpDiv = 168M). */
    stcPllCfg.pllmDiv = 2ul;
    stcPllCfg.plln =60ul;
    stcPllCfg.PllpDiv = 3UL;
    CLK_SetPllSource(CLK_PLL_SRC_XTAL);
    CLK_PllConfig(&stcPllCfg);

    CLK_MCOCmd(Disable);
    CLK_PllCmd(Enable);
    //CLK_SetSysclkSrc(CLK_SYSCLKSOURCE_XTAL);
    CLK_MCOConfig(CLK_MCOSOURCCE_HCLK, CLK_MCODIV_8);
    CLK_MCOCmd(Enable);

    /* Set flash wait */
    M4_EFM->FAPRT = 0x00000123UL;
    M4_EFM->FAPRT = 0x00003210UL;
    MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT, 3UL);
    /* Switch system clock to PLL */
    CLK_SetSysclkSrc(CLK_SYSCLKSOURCE_PLL);
#endif
    while(1);
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
