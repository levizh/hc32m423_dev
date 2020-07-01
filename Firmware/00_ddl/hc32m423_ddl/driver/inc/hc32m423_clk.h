/**
 *******************************************************************************
 * @file  hc32m423_clk.h
 * @brief This file contains all the functions prototypes of the CLK driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-06-24       Chengy          First version
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
#ifndef __HC32M423_CLK_H__
#define __HC32M423_CLK_H__

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
 * @addtogroup DDL_CLK
 * @{
 */

#if (DDL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Types CLK Global Types
 * @{
 */
/**
 * @brief  CLK XTAL configuration structure definition
 */
typedef struct
{
    uint8_t u8XtalState;      /*!< The new state of the XTAL.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalDrv;        /*!< The XTAL drive ability.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalMode;       /*!< The XTAL mode selection osc or exclk.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalSupDrv;     /*!< The XTAL super drive on or off.
                                This parameter can be a value of @ref CLK_XTAL_Config   */

    uint8_t u8XtalStb;        /*!< The XTAL stable time selection.
                                This parameter can be a value of @ref CLK_XTAL_Config   */
} stc_clk_xtal_init_t;


/**
 * @brief  CLK XTALSTD configuration structure definition
 */
typedef struct
{
    uint8_t u8XtalStdState;   /*!< Specifies the new state of XTALSTD.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8XtalStdMode;    /*!< Specifies the XTALSTD mode.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8XtalStdInt;     /*!< Specifies the XTALSTD interrupt on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */

    uint8_t u8XtalStdRst;     /*!< Specifies the XTALSTD reset on or off.
                                This parameter can be a value of @ref CLK_XTALSTD_Config    */
} stc_clk_xtalstd_init_t;

/**
 * @brief  Configuration structure of system clock divider.
 */
typedef struct stc_clk_div_cfg
{
    uint32_t      u32HclkDiv;        ///< Division for hclk. @ref CLK_Hclk_Divider
    uint32_t      u32Pclk1Div;       ///< Division for pclk1.@ref CLK_Pclk1_Divider
    uint32_t      u32Pclk4Div;       ///< Division for pclk4.@ref CLK_Pclk4_Divider
}stc_clk_div_cfg_t;

/**
 * @brief  Configuration structure of PLL.
 */
typedef struct stc_clk_pll_cfg
{
    uint32_t         PllpDiv;        ///< Pllp clk, division factor of VCO out.
    uint32_t         plln;           ///< Multiplication factor of vco out, ensure between 120M~240M
    uint32_t         pllmDiv;        ///< Division factor of VCO in, ensure between 4M~12.5M.
}stc_clk_pll_cfg_t;

/**
 * @brief  Clock frequency structure.
 */
typedef struct stc_clk_freq
{
    uint32_t            sysclkFreq;         ///< System clock frequency.
    uint32_t            hclkFreq;           ///< Hclk frequency.
    uint32_t            pclk1Freq;          ///< Pclk1 frequency.
    uint32_t            pclk4Freq;          ///< Pclk4 frequency.
}stc_clk_freq_t;


/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Global_Macros CLK Global Macros
 * @{
 */

/**
 * @defgroup CLK_XTAL_Config XTAL Config
 * @{
 */
#define CLK_XTAL_OFF                (CMU_XTALCR_XTALSTP)
#define CLK_XTAL_ON                 ((uint8_t)0x00U)

/**
 * @brief XTAL mode selection osc or exclk
 */

#define CLK_XTALMODE_OSC            ((uint8_t)0x00U)
#define CLK_XTALMODE_EXCLK          (CMU_XTALCFGR_XTALMS)

/**
 * @brief XTAL super driver on or off
 */
#define CLK_XTAL_SUPDRV_ON          (CMU_XTALCFGR_SUPDRV)
#define CLK_XTAL_SUPDRV_OFF         ((uint8_t)0x00U)

/**
 * @brief XTAL driver ability
 * @note  High suggest OSC 20MHz, Mid bettween 10~20MHz, Low bettween 4~10MHz, ULow 4MHz.
 */
#define CLK_XTALDRV_HIGH            ((uint8_t)0x00U)
#define CLK_XTALDRV_MID             (CMU_XTALCFGR_XTALDRV_0)
#define CLK_XTALDRV_LOW             (CMU_XTALCFGR_XTALDRV_1)
#define CLK_XTALDRV_ULOW            (CMU_XTALCFGR_XTALDRV)

/**
 * @brief XTAL stable time selection.
 * @note  a cycle of stable counter = a cycle of XTAL
 */
#define CLK_XTALSTB_8               ((uint8_t)0x00U)       /*!< 2^8 * XTAL cycle.  */
#define CLK_XTALSTB_9               ((uint8_t)0x01U)       /*!< 2^9 * XTAL cycle.  */
#define CLK_XTALSTB_10              ((uint8_t)0x02U)       /*!< 2^10 * XTAL cycle. */
#define CLK_XTALSTB_11              ((uint8_t)0x03U)       /*!< 2^11 * XTAL cycle. */
#define CLK_XTALSTB_13              ((uint8_t)0x04U)       /*!< 2^13 * XTAL cycle. */
#define CLK_XTALSTB_15              ((uint8_t)0x05U)       /*!< 2^15 * XTAL cycle. */
#define CLK_XTALSTB_16              ((uint8_t)0x06U)       /*!< 2^16 * XTAL cycle. */
#define CLK_XTALSTB_17              ((uint8_t)0x07U)       /*!< 2^17 * XTAL cycle. */
/**
 * @}
 */

/**
 * @defgroup CLK_XTALSTD_Config XTALSTD Config
 * @{
 */

/**
 * @brief XTAL trouble detection on or off
 */
#define CLK_XTALSTD_OFF             ((uint8_t)0x00U)
#define CLK_XTALSTD_ON              (CMU_XTALSTDCR_XTALSTDE)

/**
 * @brief XTALSTD mode selection
 */
#define CLK_XTALSTD_MODE_RST        (CMU_XTALSTDCR_XTALSTDRIS)
#define CLK_XTALSTD_MODE_INT        ((uint8_t)0x00U)

/**
 * @brief XTALSTD reset on or off
 */
#define CLK_XTALSTD_RST_OFF         ((uint8_t)0x00U)
#define CLK_XTALSTD_RST_ON          (CMU_XTALSTDCR_XTALSTDRE)

/**
 * @brief XTALSTD interrupt on or off
 */
#define CLK_XTALSTD_INT_OFF         ((uint8_t)0x00U)
#define CLK_XTALSTD_INT_ON          (CMU_XTALSTDCR_XTALSTDIE)
/**
 * @}
 */

/**
 * @defgroup CLK_HRC_Config HRC Config
 * @{
 */
#define CLK_HRC_OFF                 (CMU_HRCCR_HRCSTP)
#define CLK_HRC_ON                  ((uint8_t)0x00U)
/**
 * @}
 */


/**
 * @defgroup CLK_HRCFreq_Sel HRC Config
 * @{
 */
#define CLK_HRCFREQ_32              ((uint8_t)0x00U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRCFREQ_16              ((uint8_t)0x01U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRCFREQ_8               ((uint8_t)0x02U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRCFREQ_4               ((uint8_t)0x03U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRCFREQ_2               ((uint8_t)0x04U)   /*!< ICG.HRCFREQS[3] = 0. */
#define CLK_HRCFREQ_1               ((uint8_t)0x05U)   /*!< ICG.HRCFREQS[3] = 0. */

#define CLK_HRCFREQ_48              ((uint8_t)0x00U)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRCFREQ_24              ((uint8_t)0x01U)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRCFREQ_12              ((uint8_t)0x02U)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRCFREQ_6               ((uint8_t)0x03U)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRCFREQ_3               ((uint8_t)0x04U)   /*!< ICG.HRCFREQS[3] = 1. */
#define CLK_HRCFREQ_1P5             ((uint8_t)0x05U)   /*!< ICG.HRCFREQS[3] = 1. */

/**
 * @}
 */

/**
 * @defgroup CLK_LRC_Config LRC Config
 * @{
 */
#define CLK_LRC_OFF                 (CMU_LRCCR_LRCSTP)
#define CLK_LRC_ON                  ((uint8_t)0x00U)
/**
 * @}
 */

/**
 * @defgroup CLK_STB_Flag CLK stable Flags
 * @{
 */
#define CLK_FLAG_HRCSTB             (CMU_OSCSTBSR_HRCSTBF)
#define CLK_FLAG_XTALSTB            (CMU_OSCSTBSR_XTALSTBF)
#define CLK_FLAG_PLLSTB             (CMU_OSCSTBSR_PLLSTBF)
/**
 * @}
 */

/**
 * @defgroup CLK_System_Clock_Source System Clock Source
 * @{
 */
#define CLK_SYSCLKSOURCE_HRC        ((uint8_t)0x00U)
#define CLK_SYSCLKSOURCE_MRC        ((uint8_t)0x01U)
#define CLK_SYSCLKSOURCE_LRC        ((uint8_t)0x02U)
#define CLK_SYSCLKSOURCE_XTAL       ((uint8_t)0x03U)
#define CLK_SYSCLKSOURCE_PLL        ((uint8_t)0x05U)
/**
 * @}
 */

/**
 * @defgroup CLK_Hclk_Divider System HCLK divider
 * @{
 */
#define CLK_HCLK_DIV1             ((uint32_t)0x00UL << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV2             ((uint32_t)0x01UL << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV4             ((uint32_t)0x02UL << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV8             ((uint32_t)0x03UL << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV16            ((uint32_t)0x04UL << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV32            ((uint32_t)0x05UL << CMU_SCFGR_HCLKS_POS)
#define CLK_HCLK_DIV64            ((uint32_t)0x06UL << CMU_SCFGR_HCLKS_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK1_Divider System PCLK1 divider
 * @{
 */
#define CLK_PCLK1_DIV1             ((uint32_t)0x00UL << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV2             ((uint32_t)0x01UL << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV4             ((uint32_t)0x02UL << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV8             ((uint32_t)0x03UL << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV16            ((uint32_t)0x04UL << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV32            ((uint32_t)0x05UL << CMU_SCFGR_PCLK1S_POS)
#define CLK_PCLK1_DIV64            ((uint32_t)0x06UL << CMU_SCFGR_PCLK1S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_PCLK4_Divider System PCLK4 divider
 * @{
 */
#define CLK_PCLK4_DIV1             ((uint32_t)0x00UL << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV2             ((uint32_t)0x01UL << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV4             ((uint32_t)0x02UL << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV8             ((uint32_t)0x03UL << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV16            ((uint32_t)0x04UL << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV32            ((uint32_t)0x05UL << CMU_SCFGR_PCLK4S_POS)
#define CLK_PCLK4_DIV64            ((uint32_t)0x06UL << CMU_SCFGR_PCLK4S_POS)
/**
 * @}
 */

/**
 * @defgroup CLK_ADCCLK_Divider ADC clock divider
 * @{
 */
#define CLK_ADCCLK_PCLK4_DIV1               ((uint8_t)0x00U)
#define CLK_ADCCLK_PCLK4_DIV2               ((uint8_t)0x01U)
#define CLK_ADCCLK_PCLK4_DIV3               ((uint8_t)0x02U)
#define CLK_ADCCLK_PCLK4_DIV4               ((uint8_t)0x03U)
#define CLK_ADCCLK_PCLK4_DIV5               ((uint8_t)0x04U)
#define CLK_ADCCLK_PCLK4_DIV6               ((uint8_t)0x05U)
#define CLK_ADCCLK_PCLK4_DIV7               ((uint8_t)0x06U)
#define CLK_ADCCLK_PCLK4_DIV8               ((uint8_t)0x07U)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Source CLK MCO Clock Source
 * @{
 */
#define CLK_MCOSOURCCE_HRC          ((uint8_t)0x00U)
#define CLK_MCOSOURCCE_MRC          ((uint8_t)0x01U)
#define CLK_MCOSOURCCE_LRC          ((uint8_t)0x02U)
#define CLK_MCOSOURCCE_XTAL         ((uint8_t)0x03U)
#define CLK_MCOSOURCCE_PLLP         ((uint8_t)0x05U)
#define CLK_MCOSOURCCE_HCLK         ((uint8_t)0x06U)
#define CLK_MCOSOURCCE_SWDT         ((uint8_t)0x07U)
/**
 * @}
 */

/**
 * @defgroup CLK_MCO_Clock_Prescaler CLK MCO Clock Prescaler
 * @{
 */
#define CLK_MCODIV_1                ((uint8_t)0x00U)
#define CLK_MCODIV_2                ((uint8_t)0x10U)
#define CLK_MCODIV_4                ((uint8_t)0x20U)
#define CLK_MCODIV_8                ((uint8_t)0x30U)
#define CLK_MCODIV_16               ((uint8_t)0x40U)
#define CLK_MCODIV_32               ((uint8_t)0x50U)
#define CLK_MCODIV_64               ((uint8_t)0x60U)
#define CLK_MCODIV_128              ((uint8_t)0x70U)
/**
 * @}
 */

/**
 * @defgroup CLK_FCG_Peripheral_Control CLK FCG Peripheral function control
 * @{
 */
#define CLK_FCG_ADC                     (CMU_FCG_ADC   )
#define CLK_FCG_CTC                     (CMU_FCG_CTC   )
#define CLK_FCG_CMP                     (CMU_FCG_CMP   )
#define CLK_FCG_AOS                     (CMU_FCG_AOS   )
#define CLK_FCG_DMA                     (CMU_FCG_DMA   )
#define CLK_FCG_CRC                     (CMU_FCG_CRC   )
#define CLK_FCG_TIMA1                   (CMU_FCG_TIMA1 )
#define CLK_FCG_TIMA2                   (CMU_FCG_TIMA2 )
#define CLK_FCG_TIMA3                   (CMU_FCG_TIMA3 )
#define CLK_FCG_TIMA4                   (CMU_FCG_TIMA4 )
#define CLK_FCG_TIM0_1                  (CMU_FCG_TIM0_1)
#define CLK_FCG_TIM0_2                  (CMU_FCG_TIM0_2)
#define CLK_FCG_TIM4_1                  (CMU_FCG_TIM4_1)
#define CLK_FCG_TIMB_1                  (CMU_FCG_TIMB_1)
#define CLK_FCG_EMB                     (CMU_FCG_EMB   )
#define CLK_FCG_FCM                     (CMU_FCG_FCM   )
#define CLK_FCG_DCU                     (CMU_FCG_DCU   )
#define CLK_FCG_UART1                   (CMU_FCG_UART1 )
#define CLK_FCG_UART2                   (CMU_FCG_UART2 )
#define CLK_FCG_UART3                   (CMU_FCG_UART3 )
#define CLK_FCG_UART4                   (CMU_FCG_UART4 )
#define CLK_FCG_IIC_1                   (CMU_FCG_IIC_1 )
#define CLK_FCG_SPI_1                   (CMU_FCG_SPI_1 )
/**
 * @}
 */

/**
 * @defgroup CLK_PLL_Clock_Source CLK PLL Clock Source
 * @{
 */
#define CLK_PLL_SRC_HRC             ((uint32_t)CMU_PLLCFGR_PLLSRC)
#define CLK_PLL_SRC_XTAL            ((uint32_t)0UL)
/**
 * @}
 */



/**
 * @}
 */

/**
 * @defgroup CLK_REG_Write_Configuration CLK register write Configuration
 * @{
 */
#define CLK_REG_WRITE_ENABLE()      (M4_PWC->FPRC = 0xa501U)
#define CLK_REG_WRITE_DISABLE()     (M4_PWC->FPRC = 0xa500U)

#define CLK_HRCCFGR_WRITE_ENBALE()  {M4_EFM->FAPRT = 0x0123U; \
                                     M4_EFM->FAPRT = 0x3210U;}

#define CLK_HRCCFGR_WRITE_DISABLE() (M4_EFM->FAPRT = 0x0U)
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
 * @addtogroup CLK_Global_Functions
 * @{
 */

void CLK_DeInit(void);

en_result_t CLK_XtalStrucInit(stc_clk_xtal_init_t* pstcXtal);
en_result_t CLK_XTALInit(const stc_clk_xtal_init_t* pstcXtal);
en_result_t CLK_HRCInit(uint8_t HRCState, uint8_t HRCFreq);
en_result_t CLK_LRCInit(uint8_t LRCState);

en_result_t CLK_XtalStdStrucInit(stc_clk_xtalstd_init_t* pstcXtalStd);
en_result_t CLK_XTALStdInit(const stc_clk_xtalstd_init_t* pstcXtalStd);

void CLK_SetSysclkSrc(uint8_t u8Src);
void CLK_SetSysclkDiv(const stc_clk_div_cfg_t *pstcClkDivCfg);
void CLK_SetADClkDiv(uint8_t u8Div);

void CLK_FcgPeriphClockCmd(uint32_t u32FcgPeriph, en_functional_state_t enNewState);

void CLK_MCOConfig(uint8_t CLK_MCOSource, uint8_t CLK_MCODiv);
void CLK_MCOCmd(en_functional_state_t enNewState);

void CLK_ClearXtalStdFlag(void);
en_flag_status_t CLK_GetStableFlag(uint8_t u8Flag);

void CLK_SetPllSource(uint32_t u32PllSrc);
void CLK_PllConfig(const stc_clk_pll_cfg_t *pstcPllCfg);
en_result_t CLK_PllCmd(en_functional_state_t enNewState);

void CLK_GetClockFreq(stc_clk_freq_t *pstcClkFreq);
/**
 * @}
 */

#endif /* DDL_CLK_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_CLK_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
