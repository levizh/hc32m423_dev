/**
 *******************************************************************************
 * @file  hc32m423_interrupts.c
 * @brief This file provides firmware functions to manage the Interrupt Controller
 *        (INTC).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32m423_interrupts.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_INTERRUPTS INTERRUPTS
 * @brief INTC Driver Library
 * @{
 */

#if (DDL_INTERRUPTS_ENABLE == DDL_ON) || (DDL_EXINT_NMI_SWI_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup INTC_Local_Macros INTC Local Macros
 * @{
 */
/**
 * @brief   Maximum IRQ handler number
 */
#define IRQ_NUM_MAX         8U

/**
 * @defgroup INTC_Check_Parameters_Validity INTC Check Parameters Validity
 * @{
 */
/*  Parameter validity check for wakeup source from stop mode. */
#define IS_INTC_WKUP_SRC(src)                                                   \
(   ((src) & (INTC_WUPEN_EIRQWUEN   | INTC_WUPEN_SWDTWUEN   |                   \
             INTC_WUPEN_PVD1WUEN    | INTC_WUPEN_PVD2WUEN   |                   \
             INTC_WUPEN_CMPI0WUEN   | INTC_WUPEN_TMR0WUEN   |                   \
             INTC_WUPEN_RXWUEN)) != (uint32_t)0x00000000UL)

/*  Parameter validity check for event number. */
#define IS_INTC_EVENT(event)                                                    \
(   ((event) & (INTC_EVTER_EVTE0    | INTC_EVTER_EVTE1      |                   \
                INTC_EVTER_EVTE2    | INTC_EVTER_EVTE3      |                   \
                INTC_EVTER_EVTE4    | INTC_EVTER_EVTE5      |                   \
                INTC_EVTER_EVTE6    | INTC_EVTER_EVTE7      |                   \
                INTC_EVTER_EVTE8    | INTC_EVTER_EVTE9      |                   \
                INTC_EVTER_EVTE10   | INTC_EVTER_EVTE11     |                   \
                INTC_EVTER_EVTE12   | INTC_EVTER_EVTE13     |                   \
                INTC_EVTER_EVTE14   | INTC_EVTER_EVTE15)) != (uint32_t)0x00000000UL)

/*  Parameter validity check for interrupt index. */
#define IS_INTC_INT(int)                                                        \
(   ((int) &    (INTC_IER_IER0      | INTC_IER_IER1         |                   \
                INTC_IER_IER2       | INTC_IER_IER3         |                   \
                INTC_IER_IER4       | INTC_IER_IER5         |                   \
                INTC_IER_IER6       | INTC_IER_IER7         |                   \
                INTC_IER_IER8       | INTC_IER_IER9         |                   \
                INTC_IER_IER10      | INTC_IER_IER11        |                   \
                INTC_IER_IER12      | INTC_IER_IER13        |                   \
                INTC_IER_IER14      | INTC_IER_IER15)) != (uint32_t)0x00000000UL)

/*  Parameter validity check for software interrupt index. */
#define IS_INTC_SWI(swi)                                                        \
(   ((swi) &   (INTC_SWIER_SWIE0    | INTC_SWIER_SWIE1      |                   \
                INTC_SWIER_SWIE2    | INTC_SWIER_SWIE3      |                   \
                INTC_SWIER_SWIE4    | INTC_SWIER_SWIE5      |                   \
                INTC_SWIER_SWIE6    | INTC_SWIER_SWIE7      |                   \
                INTC_SWIER_SWIE8    | INTC_SWIER_SWIE9      |                   \
                INTC_SWIER_SWIE10   | INTC_SWIER_SWIE11     |                   \
                INTC_SWIER_SWIE12   | INTC_SWIER_SWIE13     |                   \
                INTC_SWIER_SWIE14   | INTC_SWIER_SWIE15)) != (uint32_t)0x00000000UL)

/*  Parameter validity check for NMI pin filter A function. */
#define IS_NMI_FAE(fae)                                                         \
(   ((fae) == NMI_FILTER_A_OFF)                 ||                              \
    ((fae) == NMI_FILTER_A_ON))

/*  Parameter validity check for NMI pin filter B function. */
#define IS_NMI_FBE(fbe)                                                         \
(   ((fbe) == NMI_FILTER_B_OFF)                 ||                              \
    ((fbe) == NMI_FILTER_B_ON))

/*  Parameter validity check for MNI pin filter A clock division. */
#define IS_NMI_FACLK(faclk)                                                     \
(   ((faclk) == NMI_FACLK_HCLK_DIV1)            ||                              \
    ((faclk) == NMI_FACLK_HCLK_DIV8)            ||                              \
    ((faclk) == NMI_FACLK_HCLK_DIV32)           ||                              \
    ((faclk) == NMI_FACLK_HCLK_DIV64))

/*  Parameter validity check for NMI pin trigger edge. */
#define IS_NMI_TRIGGER(trigger)                                                 \
(   ((trigger) == NMI_TRIGGER_FALLING)          ||                              \
    ((trigger) == NMI_TRIGGER_RISING))

/*  Parameter validity check for NMI trigger souce. */
#define IS_NMI_SRC(src) (((src) & NMI_SRC_MASK) != (uint32_t)0x00000000UL)

/*  Parameter validity check for get NMI trigger source. */
#define IS_GET_NMI_SRC(src)                                                     \
(   ((src) == NMI_SRC_NMI_PIN)                  ||                              \
    ((src) == NMI_SRC_SWDT)                     ||                              \
    ((src) == NMI_SRC_LVD1)                     ||                              \
    ((src) == NMI_SRC_LVD2)                     ||                              \
    ((src) == NMI_SRC_XTAL_STP)                 ||                              \
    ((src) == NMI_SRC_RAMPE)                    ||                              \
    ((src) == NMI_SRC_WDT))

/*  Parameter validity check for EXINT filter A function. */
#define IS_EXINT_FAE(fae)                                                       \
(   ((fae) == EXINT_FILTER_A_OFF)               ||                              \
    ((fae) == EXINT_FILTER_A_ON))

/*  Parameter validity check for EXINT filter B function. */
#define IS_EXINT_FBE(fbe)                                                       \
(   ((fbe) == EXINT_FILTER_B_OFF)               ||                              \
    ((fbe) == EXINT_FILTER_B_ON))

/*  Parameter validity check for EXINT filter clock division. */
#define IS_EXINT_FACLK(faclk)                                                   \
(   ((faclk) == EXINT_FACLK_HCLK_DIV1)           ||                             \
    ((faclk) == EXINT_FACLK_HCLK_DIV8)           ||                             \
    ((faclk) == EXINT_FACLK_HCLK_DIV32)          ||                             \
    ((faclk) == EXINT_FACLK_HCLK_DIV64))

/*  Parameter validity check for EXINT filter clock division. */
#define IS_NMI_EXINT_FBTIM(fbtim)                                               \
(   ((fbtim) == NMI_EXINT_FBTIM_500NS)           ||                             \
    ((fbtim) == NMI_EXINT_FBTIM_1US)             ||                             \
    ((fbtim) == NMI_EXINT_FBTIM_2US)             ||                             \
    ((fbtim) == NMI_EXINT_FBTIM_4US))

/*  Parameter validity check for EXINT trigger edge. */
#define IS_EXINT_TRIGGER(trigger)                                               \
(   ((trigger) == EXINT_TRIGGER_LOW)            ||                              \
    ((trigger) == EXINT_TRIGGER_RISING)         ||                              \
    ((trigger) == EXINT_TRIGGER_FALLING)        ||                              \
    ((trigger) == EXINT_TRIGGER_BOTH))

/*  Parameter validity check for EXINT channel. */
#define IS_EXINT_CH(ch)     (((ch) & EXINT_CH_MASK) != (uint16_t)0x0000U)

/*  Parameter validity check for get EXINT channel. */
#define IS_GET_EXINT_CH(ch)                                                     \
(   ((ch) == EXINT_CH00)                        ||                              \
    ((ch) == EXINT_CH01)                        ||                              \
    ((ch) == EXINT_CH02)                        ||                              \
    ((ch) == EXINT_CH03)                        ||                              \
    ((ch) == EXINT_CH04)                        ||                              \
    ((ch) == EXINT_CH05)                        ||                              \
    ((ch) == EXINT_CH06)                        ||                              \
    ((ch) == EXINT_CH07))

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
/**
 * @defgroup INTC_Local_Variable INTC Local Variable
 * @{
 */
static func_ptr_t pfnIrqHandler[IRQ_NUM_MAX] = {NULL};
static func_ptr_t pfnNmiCallback;
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
 * @defgroup INTC_Global_Functions INTC Global Functions
 * @{
 */
/**
 * @brief  IRQ sign in function
 * @param  [in] pstcIrqSignConfig: pointer of IRQ registration structure
 *   @arg  enIntSrc: can be any value @ref en_int_src_t
 *   @arg  enIRQn: can be any value from Int000~Int007 @ref IRQn_Type
 *   @arg  pfnCallback: Callback function
 * @retval Ok: IRQ register successfully
 *         ErrorInvalidParameter: ErrorInvalidParameter: IRQ No. is out of range;
 *                                NULL pointer.
 *         ErrorUninitialized: Specified IRQ entry was signed before.
 */
en_result_t INTC_IrqSignIn(const stc_irq_signin_config_t *pstcIrqSignConfig)
{
    __IO uint32_t *INTC_SELx;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if ((NULL == pstcIrqSignConfig) || (pstcIrqSignConfig->enIRQn > Int007_IRQn))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        INTC_SELx = (uint32_t *)((uint32_t)(&M4_INTC->SEL0) + (4U * (pstcIrqSignConfig->enIRQn)));
        if ((0x1FFUL == ((*INTC_SELx) & 0x1FFUL)) || ((uint32_t)(pstcIrqSignConfig->enIRQn) == ((*INTC_SELx) & 0x1FFUL)))
        {
            WRITE_REG32(*INTC_SELx, pstcIrqSignConfig->enIntSrc);
            /* Callback function */
            pfnIrqHandler[pstcIrqSignConfig->enIRQn] = pstcIrqSignConfig->pfnCallback;
        }
        else
        {
            enRet = ErrorUninitialized;
        }

    }
    return enRet;
}

/**
 * @brief  IRQ sign out function
 * @param  [in] enIRQn: can be any value from Int000~Int007 @ref IRQn_Type
 * @retval Ok: IRQ sign out successfully
 *         ErrorInvalidParameter: IRQ No. is out of range
 */
en_result_t INTC_IrqSignOut(IRQn_Type enIRQn)
{
    __IO uint32_t *INTC_SELx;
    en_result_t enRet = Ok;

    if ((enIRQn < Int000_IRQn) || (enIRQn > Int007_IRQn))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        INTC_SELx = (uint32_t *)((uint32_t)(&M4_INTC->SEL0) + (4UL * enIRQn));
        WRITE_REG32(*INTC_SELx, 0x1FFUL);
        pfnIrqHandler[enIRQn] = NULL;
    }
    return enRet;
}

/**
 * @brief  Stop mode wake-up source configure
 * @param  [in] u32WakeupSrc: Wake-up source
 *   @arg  INTC_WUPEN_EIRQWUEN
 *   @arg  INTC_WUPEN_EIRQWUEN_0
 *   @arg  INTC_WUPEN_EIRQWUEN_1
 *   @arg  INTC_WUPEN_EIRQWUEN_2
 *   @arg  INTC_WUPEN_EIRQWUEN_3
 *   @arg  INTC_WUPEN_EIRQWUEN_4
 *   @arg  INTC_WUPEN_EIRQWUEN_5
 *   @arg  INTC_WUPEN_EIRQWUEN_6
 *   @arg  INTC_WUPEN_EIRQWUEN_7
 *   @arg  INTC_WUPEN_SWDTWUEN
 *   @arg  INTC_WUPEN_PVD1WUEN
 *   @arg  INTC_WUPEN_PVD2WUEN
 *   @arg  INTC_WUPEN_CMPI0WUEN
 *   @arg  INTC_WUPEN_TMR0WUEN
 *   @arg  INTC_WUPEN_RXWUEN
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding wake up source
 *   @arg  Disable: Disable corresponding wake up source
 * @retval None
 */
void INTC_WakeupSrcCmd(uint32_t u32WakeupSrc, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_WKUP_SRC(u32WakeupSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->WUPEN, u32WakeupSrc);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->WUPEN, u32WakeupSrc);
    }
}

/**
 * @brief  Event or Interrupt output configure
 * @param  [in] u8Event: Event index
 *   @arg  INTC_EVTER_EVTE0
 *   @arg  INTC_EVTER_EVTE1
 *   @arg  INTC_EVTER_EVTE2
 *   @arg  INTC_EVTER_EVTE3
 *   @arg  INTC_EVTER_EVTE4
 *   @arg  INTC_EVTER_EVTE5
 *   @arg  INTC_EVTER_EVTE6
 *   @arg  INTC_EVTER_EVTE7
 *   @arg  INTC_EVTER_EVTE8
 *   @arg  INTC_EVTER_EVTE9
 *   @arg  INTC_EVTER_EVTE10
 *   @arg  INTC_EVTER_EVTE11
 *   @arg  INTC_EVTER_EVTE12
 *   @arg  INTC_EVTER_EVTE13
 *   @arg  INTC_EVTER_EVTE14
 *   @arg  INTC_EVTER_EVTE15
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding event to NVIC
 *   @arg  Disable: Disable corresponding event but interrupt to NVIC
 * @retval None
 */
void INTC_EventCmd(uint32_t u32Event, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_EVENT(u32Event));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->EVTER, u32Event);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->EVTER, u32Event);
    }
}

/**
 * @brief  Interrupt function configure
 * @param  [in] u32Int: Interrupt index
 *   @arg  INTC_IER_IER0
 *   @arg  INTC_IER_IER1
 *   @arg  INTC_IER_IER2
 *   @arg  INTC_IER_IER3
 *   @arg  INTC_IER_IER4
 *   @arg  INTC_IER_IER5
 *   @arg  INTC_IER_IER6
 *   @arg  INTC_IER_IER7
 *   @arg  INTC_IER_IER8
 *   @arg  INTC_IER_IER9
 *   @arg  INTC_IER_IER10
 *   @arg  INTC_IER_IER11
 *   @arg  INTC_IER_IER12
 *   @arg  INTC_IER_IER13
 *   @arg  INTC_IER_IER14
 *   @arg  INTC_IER_IER15
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding interrupt to NVIC
 *   @arg  Disable: Disable corresponding interrupt to NVIC
 * @retval None
 */
void INTC_IntCmd(uint32_t u32Int, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_INT(u32Int));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->IER, u32Int);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->IER, u32Int);
    }
}

/**
 * @brief  Software Interrupt function configure
 * @param  [in] u32SWI: Software Interrupt index
 *   @arg  INTC_SWIER_SWIE0
 *   @arg  INTC_SWIER_SWIE1
 *   @arg  INTC_SWIER_SWIE2
 *   @arg  INTC_SWIER_SWIE3
 *   @arg  INTC_SWIER_SWIE4
 *   @arg  INTC_SWIER_SWIE5
 *   @arg  INTC_SWIER_SWIE6
 *   @arg  INTC_SWIER_SWIE7
 *   @arg  INTC_SWIER_SWIE8
 *   @arg  INTC_SWIER_SWIE9
 *   @arg  INTC_SWIER_SWIE10
 *   @arg  INTC_SWIER_SWIE11
 *   @arg  INTC_SWIER_SWIE12
 *   @arg  INTC_SWIER_SWIE13
 *   @arg  INTC_SWIER_SWIE14
 *   @arg  INTC_SWIER_SWIE15
 * @param  [in] enNewState
 *   @arg  Enable: Enable corresponding software interrupt
 *   @arg  Disable: Disable corresponding software interrupt
 * @retval None
 */
void INTC_SWICmd(uint32_t u32SWI, en_functional_state_t enNewState)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_INTC_SWI(u32SWI));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(M4_INTC->SWIER, u32SWI);
    }
    else
    {
        CLEAR_REG32_BIT(M4_INTC->SWIER, u32SWI);
    }
}

/**
 * @brief  Initialize NMI. Fill each pstcNmiConfig with default value
 * @param  [in] pstcNmiConfig: Pointer to a stc_nmi_config_t structure that
 *                             contains configuration information.
 * @retval Ok: NMI structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t NMI_StructInit(stc_nmi_config_t *pstcNmiConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcNmiConfig)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcNmiConfig->u32NmiFAE        = NMI_FILTER_A_OFF;
        pstcNmiConfig->u32NmiFAClk      = NMI_FACLK_HCLK_DIV1;
        pstcNmiConfig->u32NmiFBE        = NMI_FILTER_B_OFF;
        pstcNmiConfig->u32NmiFBTime     = NMI_EXINT_FBTIM_500NS;
        pstcNmiConfig->u32NmiTigger     = NMI_TRIGGER_FALLING;
        pstcNmiConfig->u32NmiSrc        = NMI_SRC_NMI_PIN;
        pstcNmiConfig->pfnNmiCallback   = NULL;
    }
    return enRet;
}

/**
 * @brief  Initialize NMI.
 * @param  [in] pstcNmiConfig: Pointer to a pstcNmiConfig structure that
 *                             contains configuration information.
 * @retval Ok: NMI initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t NMI_Init(const stc_nmi_config_t *pstcNmiConfig)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if ((NULL == pstcNmiConfig) || (NULL == pstcNmiConfig->pfnNmiCallback))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_NMI_FAE(pstcNmiConfig->u32NmiFAE));
        DDL_ASSERT(IS_NMI_FACLK(pstcNmiConfig->u32NmiFAClk));
        DDL_ASSERT(IS_NMI_FBE(pstcNmiConfig->u32NmiFBE));
        DDL_ASSERT(IS_NMI_EXINT_FBTIM(pstcNmiConfig->u32NmiFBTime));
        DDL_ASSERT(IS_NMI_TRIGGER(pstcNmiConfig->u32NmiTigger));
        DDL_ASSERT(IS_NMI_SRC(pstcNmiConfig->u32NmiSrc));

        /* NMI pin interrupt configure */
        WRITE_REG32(M4_INTC->NMICR,                                             \
                  (pstcNmiConfig->u32NmiFAE         |                           \
                   pstcNmiConfig->u32NmiFAClk       |                           \
                   pstcNmiConfig->u32NmiFBE         |                           \
                   pstcNmiConfig->u32NmiFBTime      |                           \
                   pstcNmiConfig->u32NmiTigger));

        /* Clear all NMI trigger source before set */
        WRITE_REG32(M4_INTC->NMICFR, INTC_NMICFR_MASK);

        /* NMI trigger source configure */
        WRITE_REG32(M4_INTC->NMIER, pstcNmiConfig->u32NmiSrc);

        /* NMI callback function configure */
        pfnNmiCallback = pstcNmiConfig->pfnNmiCallback;
    }
    return enRet;
}

/**
 * @brief  Get NMI trigger source
 * @param  [in] u32NmiSrc: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_NMI_PIN
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_LVD1
 *   @arg  NMI_SRC_LVD2
 *   @arg  NMI_SRC_XTAL_STP
 *   @arg  NMI_SRC_RAMPE
 *   @arg  NMI_SRC_WDT
 * @retval Set: NMI is triggered by corresponding source
 *         Reset: NMI is not triggered by corresponding source
 */
en_flag_status_t NMI_GetNmiSrc(uint32_t u32NmiSrc)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_GET_NMI_SRC(u32NmiSrc));

    return ((READ_REG32(M4_INTC->NMIFR) & u32NmiSrc)) ? Set : Reset;
}

/**
 * @brief  Clear specified NMI trigger source
 * @param  [in] u32NmiSrc: NMI trigger source, @ref NMI_TriggerSrc_Sel for details
 *   @arg  NMI_SRC_NMI_PIN
 *   @arg  NMI_SRC_SWDT
 *   @arg  NMI_SRC_LVD1
 *   @arg  NMI_SRC_LVD2
 *   @arg  NMI_SRC_XTAL_STP
 *   @arg  NMI_SRC_RAMPE
 *   @arg  NMI_SRC_WDT
 * @retval None
 */
void NMI_ClrNmiSrc(uint32_t u32NmiSrc)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_NMI_SRC(u32NmiSrc));

    MODIFY_REG32(M4_INTC->NMICFR, INTC_NMICFR_MASK, u32NmiSrc);
}

/**
 * @brief  NMI IRQ handler
 * @param  None
 * @retval None
 */
void NMI_IrqHandler(void)
{
    if (NULL != pfnNmiCallback)
    {
        pfnNmiCallback();
    }
}

/**
 * @brief  Initialize External interrupt.
 * @param  [in] pstcExIntInit: Pointer to a pstcExIntInit structure that
 *                             contains configuration information.
 * @retval Ok:  EXINT initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t EXINT_Init(const stc_exint_config_t *pstcExIntInit)
{
    uint8_t u8ExIntPos = 0U;
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcExIntInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter validity checking */
        DDL_ASSERT(IS_EXINT_FAE(pstcExIntInit->u32ExIntFAE));
        DDL_ASSERT(IS_EXINT_FBE(pstcExIntInit->u32ExIntFBE));
        DDL_ASSERT(IS_EXINT_FACLK(pstcExIntInit->u32ExIntFAClk));
        DDL_ASSERT(IS_NMI_EXINT_FBTIM(pstcExIntInit->u32ExIntFBTime));
        DDL_ASSERT(IS_EXINT_TRIGGER(pstcExIntInit->u32ExIntLvl));
        DDL_ASSERT(IS_EXINT_CH(pstcExIntInit->u32ExIntCh));

        for (u8ExIntPos = 0U; u8ExIntPos < 10U; u8ExIntPos++)
        {
            if (pstcExIntInit->u32ExIntCh & (1UL << u8ExIntPos))
            {
                WRITE_REG32(*(uint32_t *)((uint32_t)(&M4_INTC->EIRQCR0) + 4U*u8ExIntPos),   \
                          (pstcExIntInit->u32ExIntFAE           |                           \
                           pstcExIntInit->u32ExIntFAClk         |                           \
                           pstcExIntInit->u32ExIntFBE           |                           \
                           pstcExIntInit->u32ExIntFBTime        |                           \
                           pstcExIntInit->u32ExIntLvl));
            }
        }
    }
    return enRet;
}

/**
 * @brief  Initialize ExInt. Fill each pstcExIntInit with default value
 * @param  [in] pstcExIntInit: Pointer to a pstcExIntInit structure
 *                              that contains configuration information.
 * @retval Ok: EXINT structure initialize successful
 *         ErrorInvalidParameter: NULL pointer
 */
en_result_t EXINT_StructInit(stc_exint_config_t *pstcExIntInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcExIntInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcExIntInit->u32ExIntCh     = (uint16_t)0UL;
        pstcExIntInit->u32ExIntFAE    = EXINT_FILTER_A_OFF;
        pstcExIntInit->u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV1;
        pstcExIntInit->u32ExIntFBE    = EXINT_FILTER_B_OFF;
        pstcExIntInit->u32ExIntFBTime = NMI_EXINT_FBTIM_500NS;
        pstcExIntInit->u32ExIntLvl    = EXINT_TRIGGER_FALLING;
    }
    return enRet;
}

/**
 * @brief  Clear specified External interrupt trigger source
 * @param  [in] u32ExIntCh: External interrupt channel, @ref EXINT_Channel_Sel for details
 *   @arg  EXINT_CH00
 *   @arg  EXINT_CH01
 *   @arg  EXINT_CH02
 *   @arg  EXINT_CH03
 *   @arg  EXINT_CH04
 *   @arg  EXINT_CH05
 *   @arg  EXINT_CH06
 *   @arg  EXINT_CH07
 * @retval None
 */
void EXINT_ClrExIntSrc(uint32_t u32ExIntCh)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXINT_CH(u32ExIntCh));

    SET_REG32_BIT(M4_INTC->EIRQCFR, u32ExIntCh);

}

/**
 * @brief  Get specified External interrupt trigger source
 * @param  [in] u32ExIntCh: External interrupt channel, @ref EXINT_Channel_Sel for details
 *   @arg  EXINT_CH00
 *   @arg  EXINT_CH01
 *   @arg  EXINT_CH02
 *   @arg  EXINT_CH03
 *   @arg  EXINT_CH04
 *   @arg  EXINT_CH05
 *   @arg  EXINT_CH06
 *   @arg  EXINT_CH07
 * @retval Set: Specified channel of external interrupt is triggered
 *         Reset: Specified channel of external interrupt is not triggered
 */
en_flag_status_t EXINT_GetExIntSrc(uint32_t u32ExIntCh)
{
    /* Parameter validity checking */
    DDL_ASSERT(IS_EXINT_CH(u32ExIntCh));

    return (READ_REG32(M4_INTC->EIRQFR) & u32ExIntCh) ? Set : Reset;
}

/**
 * @brief  NMI IRQ handler
 * @param  None
 * @retval None
 */
void NMI_Handler(void)
{
    NMI_IrqHandler();
}

/**
 * @brief  Hard Fault IRQ handler
 * @param  None
 * @retval None
 */
void HardFault_Handler(void)
{
    HardFault_IrqHandler();
}

/**
 * @brief  SVCall IRQ handler
 * @param  None
 * @retval None
 */
void SVC_Handler(void)
{
    SVC_IrqHandler();
}

/**
 * @brief  PendSV IRQ handler
 * @param  None
 * @retval None
 */
void PendSV_Handler(void)
{
    PendSV_IrqHandler();
}

/**
 * @brief  SysTick IRQ handler
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
    SysTick_IrqHandler();
}

/**
 * @brief  Interrupt No.000 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ000_Handler(void)
{
    pfnIrqHandler[Int000_IRQn]();
}

/**
 * @brief  Interrupt No.001 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ001_Handler(void)
{
    pfnIrqHandler[Int001_IRQn]();
}

/**
 * @brief  Interrupt No.002 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ002_Handler(void)
{
    pfnIrqHandler[Int002_IRQn]();
}

/**
 * @brief  Interrupt No.003 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ003_Handler(void)
{
    pfnIrqHandler[Int003_IRQn]();
}

/**
 * @brief  Interrupt No.004 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ004_Handler(void)
{
    pfnIrqHandler[Int004_IRQn]();
}

/**
 * @brief  Interrupt No.005 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ005_Handler(void)
{
    pfnIrqHandler[Int005_IRQn]();
}

/**
 * @brief  Interrupt No.006 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ006_Handler(void)
{
    pfnIrqHandler[Int006_IRQn]();
}

/**
 * @brief  Interrupt No.007 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ007_Handler(void)
{
    pfnIrqHandler[Int007_IRQn]();
}

/**
 * @brief  Interrupt No.008 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ008_Handler(void)
{
    EXINT00_SWINT08_IrqHandler();
}

/**
 * @brief  Interrupt No.009 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ009_Handler(void)
{
    EXINT01_SWINT09_IrqHandler();
}

/**
 * @brief  Interrupt No.010 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ010_Handler(void)
{
    EXINT02_SWINT10_IrqHandler();
}

/**
 * @brief  Interrupt No.011 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ011_Handler(void)
{
    EXINT03_SWINT11_IrqHandler();
}

/**
 * @brief  Interrupt No.012 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ012_Handler(void)
{
    EXINT04_SWINT12_IrqHandler();
}

/**
 * @brief  Interrupt No.013 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ013_Handler(void)
{
    EXINT05_SWINT13_IrqHandler();
}

/**
 * @brief  Interrupt No.014 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ014_Handler(void)
{
    EXINT06_SWINT14_IrqHandler();
}

/**
 * @brief  Interrupt No.015 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ015_Handler(void)
{
    EXINT07_SWINT15_IrqHandler();
}

/**
 * @brief  Interrupt No.016 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ016_Handler(void)
{
    DMA_Tc0_IrqHandler();
}

/**
 * @brief  Interrupt No.017 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ017_Handler(void)
{
    DMA_Tc1_IrqHandler();
}

/**
 * @brief  Interrupt No.018 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ018_Handler(void)
{
    DMA_Tc2_IrqHandler();
}

/**
 * @brief  Interrupt No.019 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ019_Handler(void)
{
    DMA_Tc3_IrqHandler();
}

/**
 * @brief  Interrupt No.020 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ020_Handler(void)
{
    DMA_Btc0_IrqHandler();
}

/**
 * @brief  Interrupt No.021 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ021_Handler(void)
{
    DMA_Btc1_IrqHandler();
}

/**
 * @brief  Interrupt No.022 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ022_Handler(void)
{
    DMA_Btc2_IrqHandler();
}

/**
 * @brief  Interrupt No.023 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ023_Handler(void)
{
    DMA_Btc3_IrqHandler();
}

/**
 * @brief  Interrupt No.024 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ024_Handler(void)
{
    DMA_Err_IrqHandler();
}

/**
 * @brief  Interrupt No.025 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ025_Handler(void)
{
    EFM_PgmEraseErr_IrqHandler();
}

/**
 * @brief  Interrupt No.026 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ026_Handler(void)
{
    EFM_ColErr_IrqHandler();
}

/**
 * @brief  Interrupt No.027 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ027_Handler(void)
{
    EFM_OpEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.028 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ028_Handler(void)
{
    DCU_IrqHandler();
}

/**
 * @brief  Interrupt No.029 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ029_Handler(void)
{
    TMR0_1_CmpA_IrqHandler();
}

/**
 * @brief  Interrupt No.030 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ030_Handler(void)
{
    TMR0_1_CmpB_IrqHandler();
}

/**
 * @brief  Interrupt No.031 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ031_Handler(void)
{
    TMR0_2_CmpA_IrqHandler();
}

/**
 * @brief  Interrupt No.032 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ032_Handler(void)
{
    TMR0_2_CmpB_IrqHandler();
}

/**
 * @brief  Interrupt No.033 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ033_Handler(void)
{
    CLK_XtalStop_IrqHandler();
}

/**
 * @brief  Interrupt No.034 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ034_Handler(void)
{
    SWDT_IrqHandler();
}

/**
 * @brief  Interrupt No.035 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ035_Handler(void)
{
    TMRA_1_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.036 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ036_Handler(void)
{
    TMRA_1_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.037 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ037_Handler(void)
{
    TMRA_1_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.038 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ038_Handler(void)
{
    TMRA_2_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.039 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ039_Handler(void)
{
    TMRA_2_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.040 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ040_Handler(void)
{
    TMRA_2_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.041 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ041_Handler(void)
{
    TMRA_3_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.042 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ042_Handler(void)
{
    TMRA_3_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.043 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ043_Handler(void)
{
    TMRA_3_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.044 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ044_Handler(void)
{
    TMRA_4_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.045 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ045_Handler(void)
{
    TMRA_4_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.046 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ046_Handler(void)
{
    TMRA_4_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.047 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ047_Handler(void)
{
    TMRB_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.048 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ048_Handler(void)
{
    TMRB_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.049 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ049_Handler(void)
{
    TMRB_Cmp_IrqHandler();
}

/**
 * @brief  Interrupt No.050 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ050_Handler(void)
{
    USART_1_RxErr_IrqHandler();
}

/**
 * @brief  Interrupt No.051 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ051_Handler(void)
{
    USART_1_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.052 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ052_Handler(void)
{
    USART_1_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.053 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ053_Handler(void)
{
    USART_1_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.054 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ054_Handler(void)
{
    USART_2_RxErr_IrqHandler();
}

/**
 * @brief  Interrupt No.055 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ055_Handler(void)
{
    USART_2_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.056 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ056_Handler(void)
{
    USART_2_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.057 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ057_Handler(void)
{
    USART_2_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.058 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ058_Handler(void)
{
    USART_3_RxErr_IrqHandler();
}

/**
 * @brief  Interrupt No.059 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ059_Handler(void)
{
    USART_3_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.060 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ060_Handler(void)
{
    USART_3_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.061 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ061_Handler(void)
{
    USART_3_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.062 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ062_Handler(void)
{
    USART_4_RxErr_IrqHandler();
}

/**
 * @brief  Interrupt No.063 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ063_Handler(void)
{
    USART_4_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.064 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ064_Handler(void)
{
    USART_4_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.065 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ065_Handler(void)
{
    USART_4_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.066 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ066_Handler(void)
{
    SPI_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.067 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ067_Handler(void)
{
    SPI_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.068 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ068_Handler(void)
{
    SPI_Idle_IrqHandler();
}

/**
 * @brief  Interrupt No.069 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ069_Handler(void)
{
    SPI_Err_IrqHandler();
}

/**
 * @brief  Interrupt No.070 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ070_Handler(void)
{
    TMR4_GCmpUH_IrqHandler();
}

/**
 * @brief  Interrupt No.071 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ071_Handler(void)
{
    TMR4_GCmpUL_IrqHandler();
}

/**
 * @brief  Interrupt No.072 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ072_Handler(void)
{
    TMR4_GCmpVH_IrqHandler();
}

/**
 * @brief  Interrupt No.073 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ073_Handler(void)
{
    TMR4_GCmpVL_IrqHandler();
}

/**
 * @brief  Interrupt No.074 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ074_Handler(void)
{
    TMR4_GCmpWH_IrqHandler();
}

/**
 * @brief  Interrupt No.075 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ075_Handler(void)
{
    TMR4_GCmpWL_IrqHandler();
}

/**
 * @brief  Interrupt No.076 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ076_Handler(void)
{
    TMR4_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.077 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ077_Handler(void)
{
    TMR4_Udf_IrqHandler();
}

/**
 * @brief  Interrupt No.078 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ078_Handler(void)
{
    TMR4_ReloadU_IrqHandler();
}

/**
 * @brief  Interrupt No.079 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ079_Handler(void)
{
    TMR4_ReloadV_IrqHandler();
}

/**
 * @brief  Interrupt No.080 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ080_Handler(void)
{
    TMR4_ReloadW_IrqHandler();
}

/**
 * @brief  Interrupt No.081 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ081_Handler(void)
{
    EMB_GR0_IrqHandler();
}

/**
 * @brief  Interrupt No.082 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ082_Handler(void)
{
    CMP_1_IrqHandler();
}

/**
 * @brief  Interrupt No.083 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ083_Handler(void)
{
    CMP_2_IrqHandler();
}

/**
 * @brief  Interrupt No.084 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ084_Handler(void)
{
    CMP_3_IrqHandler();
}

/**
 * @brief  Interrupt No.085 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ085_Handler(void)
{
    I2C_RxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.086 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ086_Handler(void)
{
    I2C_TxEnd_IrqHandler();
}

/**
 * @brief  Interrupt No.087 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ087_Handler(void)
{
    I2C_TxEmpty_IrqHandler();
}

/**
 * @brief  Interrupt No.088 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ088_Handler(void)
{
    I2C_Err_IrqHandler();
}

/**
 * @brief  Interrupt No.089 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ089_Handler(void)
{
    USART_1_WKUP_IrqHandler();
}

/**
 * @brief  Interrupt No.090 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ090_Handler(void)
{
    PWR_Lvd1_IrqHandler();
}

/**
 * @brief  Interrupt No.091 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ091_Handler(void)
{
    PWR_Lvd2_IrqHandler();
}

/**
 * @brief  Interrupt No.092 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ092_Handler(void)
{
    FCM_Err_IrqHandler();
}

/**
 * @brief  Interrupt No.093 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ093_Handler(void)
{
    FCM_End_IrqHandler();
}

/**
 * @brief  Interrupt No.094 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ094_Handler(void)
{
    FCM_Ovf_IrqHandler();
}

/**
 * @brief  Interrupt No.095 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ095_Handler(void)
{
    WDT_IrqHandler();
}

/**
 * @brief  Interrupt No.096 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ096_Handler(void)
{
    CTC_Err_IrqHandler();
}

/**
 * @brief  Interrupt No.097 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ097_Handler(void)
{
    ADC_SeqA_IrqHandler();
}

/**
 * @brief  Interrupt No.098 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ098_Handler(void)
{
    ADC_SeqB_IrqHandler();
}

/**
 * @brief  Interrupt No.099 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ099_Handler(void)
{
    ADC_ChCmp_IrqHandler();
}

/**
 * @brief  Interrupt No.100 IRQ handler
 * @param  None
 * @retval None
 */
void IRQ100_Handler(void)
{
    ADC_SeqCmp_IrqHandler();
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
