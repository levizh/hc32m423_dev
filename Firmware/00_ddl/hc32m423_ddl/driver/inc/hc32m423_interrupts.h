/**
 *******************************************************************************
 * @file  hc32m423_interrupts.h
 * @brief This file contains all the functions prototypes of the interrupt driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-01       Zhangxl         First version
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
#ifndef __HC32M423_INTERRUPTS_H__
#define __HC32M423_INTERRUPTS_H__

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
 * @addtogroup DDL_INTERRUPTS
 * @{
 */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON) || (DDL_EXINT_NMI_SWI_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Types INTC Global Types
 * @{
 */
/**
 * @brief  Interrupt registration structure definition
 */
typedef struct
{
    en_int_src_t enIntSrc;    /*!< Peripheral interrupt number, can be any value @ref en_int_src_t */
    IRQn_Type    enIRQn;      /*!< Peripheral IRQ type, can be any value @ref IRQn_Type */
    func_ptr_t   pfnCallback; /*!< Callback function for corresponding peripheral IRQ */
}stc_irq_signin_config_t;

/**
 * @brief  NMI initialize configuration structure definition
 */
typedef struct
{
    uint32_t   u32NmiFAE;       /*!< NMI pin filter A function, @ref NMI_FilterAClock_Sel for details */
    uint32_t   u32NmiFAClk;     /*!< NMI pin filter A clock  division, @ref NMI_FilterAClock_Div for details */
    uint32_t   u32NmiFBE;       /*!< NMI pin filter B function, @ref NMI_FilterBClock_Sel for details */
    uint32_t   u32NmiFBTime;    /*!< Nmi/ExInt filter B time, @ref NMI_EXINT_FilterBTim_Sel for details*/
    uint32_t   u32NmiTigger;    /*!< NMI pin trigger edge, @ref NMI_Trigger_Sel for details */
    uint32_t   u32NmiSrc;       /*!< NMI trigger source, @ref NMI_TriggerSrc_Sel for details */
    func_ptr_t pfnNmiCallback;  /*!< NMI Callback function pointers */
}stc_nmi_config_t;

/**
 * @brief  EXINT initialize configuration structure definition
 */
typedef struct
{
    uint32_t u32ExIntCh;    /*!< ExInt CH.0~7 @ref EXINT_Channel_Sel */
    uint32_t u32ExIntFAE;   /*!< ExInt filter clock, @ref EXINT_FilterAClock_Sel for details */
    uint32_t u32ExIntFAClk; /*!< ExInt filter clock division, @ref EXINT_FilterAClock_Div for details */
    uint32_t u32ExIntFBE;   /*!< ExInt filter clock, @ref EXINT_FilterBClock_Sel for details */
    uint32_t u32ExIntFBTime;/*!< Nmi/ExInt filter B time, @ref NMI_EXINT_FilterBTim_Sel for details */
    uint32_t u32ExIntLvl;   /*!< ExInt trigger edge, @ref EXINT_Trigger_Sel for details */
}stc_exint_config_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup INTC_Global_Macros INTC Global Macros
 * @{
 */
/**
 * @defgroup INTC_DefaultPriority_Sel Interrupt default priority level
 * Possible values are 0 (high priority) to 15 (low priority)
 * @{
 */
#define DDL_IRQ_PRIORITY_DEFAULT    (15U)
/**
 * @}
 */

/**
 * @defgroup INTC_Priority_Sel Interrupt priority level 0 ~ 15
 * @{
 */
#define DDL_IRQ_PRIORITY_00         (0U)
#define DDL_IRQ_PRIORITY_01         (1U)
#define DDL_IRQ_PRIORITY_02         (2U)
#define DDL_IRQ_PRIORITY_03         (3U)
#define DDL_IRQ_PRIORITY_04         (4U)
#define DDL_IRQ_PRIORITY_05         (5U)
#define DDL_IRQ_PRIORITY_06         (6U)
#define DDL_IRQ_PRIORITY_07         (7U)
#define DDL_IRQ_PRIORITY_08         (8U)
#define DDL_IRQ_PRIORITY_09         (9U)
#define DDL_IRQ_PRIORITY_10         (10U)
#define DDL_IRQ_PRIORITY_11         (11U)
#define DDL_IRQ_PRIORITY_12         (12U)
#define DDL_IRQ_PRIORITY_13         (13U)
#define DDL_IRQ_PRIORITY_14         (14U)
#define DDL_IRQ_PRIORITY_15         (15U)
/**
 * @}
 */

/**
 * @defgroup INTC_Bit_mask definition Bit Mask
 * @{
 */
#define     BIT_MASK_00             (uint32_t)(1UL << 0U)
#define     BIT_MASK_01             (uint32_t)(1UL << 1U)
#define     BIT_MASK_02             (uint32_t)(1UL << 2U)
#define     BIT_MASK_03             (uint32_t)(1UL << 3U)
#define     BIT_MASK_04             (uint32_t)(1UL << 4U)
#define     BIT_MASK_05             (uint32_t)(1UL << 5U)
#define     BIT_MASK_06             (uint32_t)(1UL << 6U)
#define     BIT_MASK_07             (uint32_t)(1UL << 7U)
#define     BIT_MASK_08             (uint32_t)(1UL << 8U)
#define     BIT_MASK_09             (uint32_t)(1UL << 9U)
#define     BIT_MASK_10             (uint32_t)(1UL << 10U)
#define     BIT_MASK_11             (uint32_t)(1UL << 11U)
#define     BIT_MASK_12             (uint32_t)(1UL << 12U)
#define     BIT_MASK_13             (uint32_t)(1UL << 13U)
#define     BIT_MASK_14             (uint32_t)(1UL << 14U)
#define     BIT_MASK_15             (uint32_t)(1UL << 15U)
#define     BIT_MASK_16             (uint32_t)(1UL << 16U)
#define     BIT_MASK_17             (uint32_t)(1UL << 17U)
#define     BIT_MASK_18             (uint32_t)(1UL << 18U)
#define     BIT_MASK_19             (uint32_t)(1UL << 19U)
#define     BIT_MASK_20             (uint32_t)(1UL << 20U)
#define     BIT_MASK_21             (uint32_t)(1UL << 21U)
#define     BIT_MASK_22             (uint32_t)(1UL << 22U)
#define     BIT_MASK_23             (uint32_t)(1UL << 23U)
#define     BIT_MASK_24             (uint32_t)(1UL << 24U)
#define     BIT_MASK_25             (uint32_t)(1UL << 25U)
#define     BIT_MASK_26             (uint32_t)(1UL << 26U)
#define     BIT_MASK_27             (uint32_t)(1UL << 27U)
#define     BIT_MASK_28             (uint32_t)(1UL << 28U)
#define     BIT_MASK_29             (uint32_t)(1UL << 29U)
#define     BIT_MASK_30             (uint32_t)(1UL << 30U)
#define     BIT_MASK_31             (uint32_t)(1UL << 31U)
/**
 * @}
 */

/**
 * @defgroup NMI_FilterAClock_Sel NMI pin filter A selection
 * @{
 */
#define NMI_FILTER_A_OFF            (uint32_t)(0UL << INTC_NMICR_NMIFEN_POS)
#define NMI_FILTER_A_ON             (uint32_t)(1UL << INTC_NMICR_NMIFEN_POS)
/**
 * @}
 */

/**
 * @defgroup NMI_FilterBClock_Sel External interrupt filter B function selection
 * @{
 */
#define NMI_FILTER_B_OFF           (uint32_t)(0UL << INTC_NMICR_NOCEN_POS)
#define NMI_FILTER_B_ON            (uint32_t)(1UL << INTC_NMICR_NOCEN_POS)
/**
 * @}
 */

/**
 * @defgroup NMI_FilterAClock_Div NMI pin filter A sampling clock division selection
 * @{
 */
#define NMI_FACLK_HCLK_DIV1         (uint32_t)(0UL << INTC_NMICR_NMIFCLK_POS)
#define NMI_FACLK_HCLK_DIV8         (uint32_t)(1UL << INTC_NMICR_NMIFCLK_POS)
#define NMI_FACLK_HCLK_DIV32        (uint32_t)(2UL << INTC_NMICR_NMIFCLK_POS)
#define NMI_FACLK_HCLK_DIV64        (uint32_t)(3UL << INTC_NMICR_NMIFCLK_POS)
/**
 * @}
 */

/**
 * @defgroup NMI_Trigger_Sel NMI pin trigger method selection
 * @{
 */
#define NMI_TRIGGER_FALLING         (uint32_t)(0UL << INTC_NMICR_NMITRG_POS)
#define NMI_TRIGGER_RISING          (uint32_t)(1UL << INTC_NMICR_NMITRG_POS)
/**
 * @}
 */

/**
 * @defgroup NMI_TriggerSrc_Sel NMI trigger source selection
 * @{
 */
#define NMI_SRC_NMI_PIN             (uint32_t)(1UL << INTC_NMIER_NMIENR_POS)
#define NMI_SRC_SWDT                (uint32_t)(1UL << INTC_NMIER_SWDTENR_POS)
#define NMI_SRC_LVD1                (uint32_t)(1UL << INTC_NMIER_PVD1ENR_POS)
#define NMI_SRC_LVD2                (uint32_t)(1UL << INTC_NMIER_PVD2ENR_POS)
#define NMI_SRC_XTAL_STP            (uint32_t)(1UL << INTC_NMIER_XTALSTPENR_POS)
#define NMI_SRC_RAMPE               (uint32_t)(1UL << INTC_NMIER_REPENR_POS)
#define NMI_SRC_WDT                 (uint32_t)(1UL << INTC_NMIER_WDTENR_POS)
#define NMI_SRC_MASK                (NMI_SRC_NMI_PIN    | NMI_SRC_SWDT  |       \
                                    NMI_SRC_LVD1        | NMI_SRC_LVD2  |       \
                                    NMI_SRC_XTAL_STP    | NMI_SRC_RAMPE |       \
                                    NMI_SRC_WDT)
/**
 * @}
 */

/**
 * @defgroup MNI_Register_Msk NMI register mask
 * @{
 */
#define INTC_NMICR_MASK     (uint32_t)(INTC_NMICR_NMITRG | INTC_NMICR_NMIFCLK | \
                            INTC_NMICR_NMIFEN | INTC_NMICR_NOCSEL | INTC_NMICR_NOCEN)
#define INTC_NMIER_MASK     (uint32_t)(INTC_NMIER_NMIENR | INTC_NMIER_SWDTENR | \
                            INTC_NMIER_PVD1ENR    | INTC_NMIER_PVD2ENR |        \
                            INTC_NMIER_XTALSTPENR | INTC_NMIER_REPENR  |        \
                            INTC_NMIER_WDTENR)
#define INTC_NMIFR_MASK     (uint32_t)(INTC_NMIFR_NMIFR  | INTC_NMIFR_SWDTFR  | \
                            INTC_NMIFR_PVD1FR     | INTC_NMIFR_PVD2FR  |        \
                            INTC_NMIFR_XTALSTPFR  | INTC_NMIFR_REPFR   |        \
                            INTC_NMIFR_WDTFR)
#define INTC_NMICFR_MASK    (uint32_t)(INTC_NMICFR_NMICFR| INTC_NMICFR_SWDTCFR| \
                            INTC_NMICFR_PVD1CFR   | INTC_NMICFR_PVD2CFR|        \
                            INTC_NMICFR_XTALSTPCFR| INTC_NMICFR_REPCFR |        \
                             INTC_NMICFR_WDTCFR)
/**
 * @}
 */

/**
 * @defgroup EXINT_Channel_Sel External interrupt channel selection
 * @{
 */
#define EXINT_CH00                  (uint32_t)(1UL << 0U)
#define EXINT_CH01                  (uint32_t)(1UL << 1U)
#define EXINT_CH02                  (uint32_t)(1UL << 2U)
#define EXINT_CH03                  (uint32_t)(1UL << 3U)
#define EXINT_CH04                  (uint32_t)(1UL << 4U)
#define EXINT_CH05                  (uint32_t)(1UL << 5U)
#define EXINT_CH06                  (uint32_t)(1UL << 6U)
#define EXINT_CH07                  (uint32_t)(1UL << 7U)
#define EXINT_CH_MASK   (EXINT_CH00 | EXINT_CH01 | EXINT_CH02 | EXINT_CH03 |    \
                         EXINT_CH04 | EXINT_CH05 | EXINT_CH06 | EXINT_CH07)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterAClock_Sel External interrupt filter A function selection
 * @{
 */
#define EXINT_FILTER_A_OFF          (uint32_t)(0UL << INTC_EIRQCR_EFEN_POS)
#define EXINT_FILTER_A_ON           (uint32_t)(1UL << INTC_EIRQCR_EFEN_POS)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterBClock_Sel External interrupt filter B function selection
 * @{
 */
#define EXINT_FILTER_B_OFF          (uint32_t)(0UL << INTC_EIRQCR_NOCEN_POS)
#define EXINT_FILTER_B_ON           (uint32_t)(1UL << INTC_EIRQCR_NOCEN_POS)
/**
 * @}
 */

/**
 * @defgroup EXINT_FilterAClock_Div External interrupt filter A sampling clock division selection
 * @{
 */
#define EXINT_FACLK_HCLK_DIV1        (uint32_t)(0UL << INTC_EIRQCR_EISMPCLK_POS)
#define EXINT_FACLK_HCLK_DIV8        (uint32_t)(1UL << INTC_EIRQCR_EISMPCLK_POS)
#define EXINT_FACLK_HCLK_DIV32       (uint32_t)(2UL << INTC_EIRQCR_EISMPCLK_POS)
#define EXINT_FACLK_HCLK_DIV64       (uint32_t)(3UL << INTC_EIRQCR_EISMPCLK_POS)
/**
 * @}
 */

/**
 * @defgroup NMI_EXINT_FilterBTim_Sel NMI/External pin interrupt filter B time selection
 * @{
 */
#define NMI_EXINT_FBTIM_500NS       (uint32_t)(0UL << INTC_NMICR_NOCSEL_POS)
#define NMI_EXINT_FBTIM_1US         (uint32_t)(1UL << INTC_NMICR_NOCSEL_POS)
#define NMI_EXINT_FBTIM_2US         (uint32_t)(2UL << INTC_NMICR_NOCSEL_POS)
#define NMI_EXINT_FBTIM_4US         (uint32_t)(3UL << INTC_NMICR_NOCSEL_POS)
/**
 * @}
 */

/**
 * @defgroup EXINT_Trigger_Sel External interrupt trigger method selection
 * @{
 */
#define EXINT_TRIGGER_FALLING       (uint32_t)(0UL << INTC_EIRQCR_EIRQTRG_POS)
#define EXINT_TRIGGER_RISING        (uint32_t)(1UL << INTC_EIRQCR_EIRQTRG_POS)
#define EXINT_TRIGGER_BOTH          (uint32_t)(2UL << INTC_EIRQCR_EIRQTRG_POS)
#define EXINT_TRIGGER_LOW           (uint32_t)(3UL << INTC_EIRQCR_EIRQTRG_POS)
/**
 * @}
 */

/**
 * @defgroup EXINT_Register_Msk EXINT register mask
 * @{
 */
#define INTC_EIRQF_MASK             (INTC_EIRQFR_EIRQFR)
#define INTC_EIRQCLR_MASK           (INTC_EIRQCFR_EIRQCFR)
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
 * @addtogroup INTC_Global_Functions
 * @{
 */

/**
 * @brief  AOS software trigger.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void AOS_SW_Trigger(void)
{
    WRITE_REG32(bM4_AOS->INTC_STRGCR_b.STRG, Set);
}

en_result_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig);
en_result_t INTC_IrqSignOut(IRQn_Type enIRQn);
void INTC_WakeupSrcCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewState);
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState);
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState);
void INTC_SWICmd(uint32_t u32SWI, en_functional_state_t enNewState);

en_result_t NMI_Init(const stc_nmi_config_t *pstcNmiConfig);
en_result_t NMI_StructInit(stc_nmi_config_t *pstcNmiConfig);
en_flag_status_t NMI_GetNmiSrc(uint32_t u32NmiSrc);
void NMI_ClrNmiSrc(uint32_t u32NmiSrc);

en_result_t EXINT_Init(const stc_exint_config_t *pstcExIntInit);
en_result_t EXINT_StructInit(stc_exint_config_t *pstcExIntInit);
en_flag_status_t EXINT_GetExIntSrc(uint32_t u32ExIntCh);
void EXINT_ClrExIntSrc(uint32_t u32ExIntCh);

__WEAKDEF void NMI_IrqHandler(void);
__WEAKDEF void HardFault_IrqHandler(void);
__WEAKDEF void MemManage_IrqHandler(void);
__WEAKDEF void BusFault_IrqHandler(void);
__WEAKDEF void UsageFault_IrqHandler(void);
__WEAKDEF void SVC_IrqHandler(void);
__WEAKDEF void DebugMon_IrqHandler(void);
__WEAKDEF void PendSV_IrqHandler(void);
__WEAKDEF void SysTick_IrqHandler(void);

__WEAKDEF void EXINT00_SWINT08_IrqHandler(void);
__WEAKDEF void EXINT01_SWINT09_IrqHandler(void);
__WEAKDEF void EXINT02_SWINT10_IrqHandler(void);
__WEAKDEF void EXINT03_SWINT11_IrqHandler(void);
__WEAKDEF void EXINT04_SWINT12_IrqHandler(void);
__WEAKDEF void EXINT05_SWINT13_IrqHandler(void);
__WEAKDEF void EXINT06_SWINT14_IrqHandler(void);
__WEAKDEF void EXINT07_SWINT15_IrqHandler(void);
__WEAKDEF void DMA_Tc0_IrqHandler(void);
__WEAKDEF void DMA_Tc1_IrqHandler(void);
__WEAKDEF void DMA_Tc2_IrqHandler(void);
__WEAKDEF void DMA_Tc3_IrqHandler(void);
__WEAKDEF void DMA_Btc0_IrqHandler(void);
__WEAKDEF void DMA_Btc1_IrqHandler(void);
__WEAKDEF void DMA_Btc2_IrqHandler(void);
__WEAKDEF void DMA_Btc3_IrqHandler(void);
__WEAKDEF void DMA_Err_IrqHandler(void);
__WEAKDEF void EFM_PgmEraseErr_IrqHandler(void);
__WEAKDEF void EFM_ColErr_IrqHandler(void);
__WEAKDEF void EFM_OpEnd_IrqHandler(void);
__WEAKDEF void DCU_IrqHandler(void);
__WEAKDEF void TMR0_1_CmpA_IrqHandler(void);
__WEAKDEF void TMR0_1_CmpB_IrqHandler(void);
__WEAKDEF void TMR0_2_CmpA_IrqHandler(void);
__WEAKDEF void TMR0_2_CmpB_IrqHandler(void);
__WEAKDEF void CLK_XtalStop_IrqHandler(void);
__WEAKDEF void SWDT_IrqHandler(void);
__WEAKDEF void TMRA_1_Ovf_IrqHandler(void);
__WEAKDEF void TMRA_1_Udf_IrqHandler(void);
__WEAKDEF void TMRA_1_Cmp_IrqHandler(void);
__WEAKDEF void TMRA_2_Ovf_IrqHandler(void);
__WEAKDEF void TMRA_2_Udf_IrqHandler(void);
__WEAKDEF void TMRA_2_Cmp_IrqHandler(void);
__WEAKDEF void TMRA_3_Ovf_IrqHandler(void);
__WEAKDEF void TMRA_3_Udf_IrqHandler(void);
__WEAKDEF void TMRA_3_Cmp_IrqHandler(void);
__WEAKDEF void TMRA_4_Ovf_IrqHandler(void);
__WEAKDEF void TMRA_4_Udf_IrqHandler(void);
__WEAKDEF void TMRA_4_Cmp_IrqHandler(void);
__WEAKDEF void TMRB_Ovf_IrqHandler(void);
__WEAKDEF void TMRB_Udf_IrqHandler(void);
__WEAKDEF void TMRB_Cmp_IrqHandler(void);
__WEAKDEF void USART_1_RxErr_IrqHandler(void);
__WEAKDEF void USART_1_RxEnd_IrqHandler(void);
__WEAKDEF void USART_1_TxEmpty_IrqHandler(void);
__WEAKDEF void USART_1_TxEnd_IrqHandler(void);
__WEAKDEF void USART_2_RxErr_IrqHandler(void);
__WEAKDEF void USART_2_RxEnd_IrqHandler(void);
__WEAKDEF void USART_2_TxEmpty_IrqHandler(void);
__WEAKDEF void USART_2_TxEnd_IrqHandler(void);
__WEAKDEF void USART_3_RxErr_IrqHandler(void);
__WEAKDEF void USART_3_RxEnd_IrqHandler(void);
__WEAKDEF void USART_3_TxEmpty_IrqHandler(void);
__WEAKDEF void USART_3_TxEnd_IrqHandler(void);
__WEAKDEF void USART_4_RxErr_IrqHandler(void);
__WEAKDEF void USART_4_RxEnd_IrqHandler(void);
__WEAKDEF void USART_4_TxEmpty_IrqHandler(void);
__WEAKDEF void USART_4_TxEnd_IrqHandler(void);
__WEAKDEF void SPI_RxEnd_IrqHandler(void);
__WEAKDEF void SPI_TxEmpty_IrqHandler(void);
__WEAKDEF void SPI_Idle_IrqHandler(void);
__WEAKDEF void SPI_Err_IrqHandler(void);
__WEAKDEF void TMR4_GCmpUH_IrqHandler(void);
__WEAKDEF void TMR4_GCmpUL_IrqHandler(void);
__WEAKDEF void TMR4_GCmpVH_IrqHandler(void);
__WEAKDEF void TMR4_GCmpVL_IrqHandler(void);
__WEAKDEF void TMR4_GCmpWH_IrqHandler(void);
__WEAKDEF void TMR4_GCmpWL_IrqHandler(void);
__WEAKDEF void TMR4_Ovf_IrqHandler(void);
__WEAKDEF void TMR4_Udf_IrqHandler(void);
__WEAKDEF void TMR4_ReloadU_IrqHandler(void);
__WEAKDEF void TMR4_ReloadV_IrqHandler(void);
__WEAKDEF void TMR4_ReloadW_IrqHandler(void);
__WEAKDEF void EMB_GR0_IrqHandler(void);
__WEAKDEF void CMP_1_IrqHandler(void);
__WEAKDEF void CMP_2_IrqHandler(void);
__WEAKDEF void CMP_3_IrqHandler(void);
__WEAKDEF void I2C_RxEnd_IrqHandler(void);
__WEAKDEF void I2C_TxEnd_IrqHandler(void);
__WEAKDEF void I2C_TxEmpty_IrqHandler(void);
__WEAKDEF void I2C_Err_IrqHandler(void);
__WEAKDEF void USART_1_WKUP_IrqHandler(void);
__WEAKDEF void PWR_Lvd1_IrqHandler(void);
__WEAKDEF void PWR_Lvd2_IrqHandler(void);
__WEAKDEF void FCM_Err_IrqHandler(void);
__WEAKDEF void FCM_End_IrqHandler(void);
__WEAKDEF void FCM_Ovf_IrqHandler(void);
__WEAKDEF void WDT_IrqHandler(void);
__WEAKDEF void CTC_Err_IrqHandler(void);
__WEAKDEF void ADC_SeqA_IrqHandler(void);
__WEAKDEF void ADC_SeqB_IrqHandler(void);
__WEAKDEF void ADC_ChCmp_IrqHandler(void);
__WEAKDEF void ADC_SeqCmp_IrqHandler(void);


/**
 * @}
 */

#endif /* DDL_INTERRUPTS_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_INTERRUPTS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
