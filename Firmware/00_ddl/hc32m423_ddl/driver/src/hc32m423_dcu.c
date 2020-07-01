/**
 *******************************************************************************
 * @file  hc32m423_dcu.c
 * @brief This file provides firmware functions to manage the DCU.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-01       Hongjh          First version
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
#include "hc32m423_ctc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_DCU Data Computing Unit(DCU)
 * @brief DCU Driver Library
 * @{
 */

#if (DDL_DCU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DCU_Local_Macros DCU Local Macros
 * @{
 */

/**
 * @defgroup DCU_Check_Parameters_Validity DCU Check Parameters Validity
 * @{
 */
#define IS_DCU_UNIT(x)                          (M4_DCU == (x))

#define IS_DCU_FLAG(x)                          ((x) & DCU_FLAG_MASK))

#define IS_DCU_MODE(x)                                                         \
(   DCU_CMP == (x)                              ||                             \
    DCU_ADD == (x)                              ||                             \
    DCU_SUB == (x)                              ||                             \
    DCU_INVALID == (x)                          ||                             \
    DCU_HW_TRIG_ADD == (x)                      ||                             \
    DCU_HW_TRIG_SUB == (x))

#define IS_DCU_INTERRUPT_SEL(x)                 ((x) & DCU_INT_MASK))

#define IS_DCU_INTERRUPT_STATE(x)                                              \
(   DCU_INT_ENABLE == (x)                       ||                             \
    DCU_INT_DISABLE == (x))

#define IS_DCU_CMP_TRIG_MODE(x)                                                \
(   DCU_CMP_TRIG_BY_DATA0 == (x)                ||                             \
    DCU_CMP_TRIG_BY_DATA012 == (x))

#define IS_DCU_DATA_SIZE(x)                                                    \
(   DCU_DATA_BITS_8 == (x)                      ||                             \
    DCU_DATA_BITS_16 == (x)                     ||                             \
    DCU_DATA_BITS_32 == (x))
/**
 * @}
 */

/**
 * @defgroup DCU_Flag_Mask DCU Flag Mask
 * @{
 */
#define DCU_FLAG_MASK                                                          \
(   DCU_FLAG_OPERATION                          |                              \
    DCU_FLAG_DATA0_LS_DATA2                     |                              \
    DCU_FLAG_DATA0_EQ_DATA2                     |                              \
    DCU_FLAG_DATA0_GT_DATA2                     |                              \
    DCU_FLAG_DATA0_LS_DATA1                     |                              \
    DCU_FLAG_DATA0_EQ_DATA1                     |                              \
    DCU_FLAG_DATA0_GT_DATA1)
/**
 * @}
 */

/**
 * @defgroup DCU_Intterrupt_Mask DCU Intterrupt Mask
 * @{
 */
#define DCU_INT_MASK                                                           \
(   DCU_INT_OPERATION                           |                              \
    DCU_INT_DATA0_LS_DATA2                      |                              \
    DCU_INT_DATA0_EQ_DATA2                      |                              \
    DCU_INT_DATA0_GT_DATA2                      |                              \
    DCU_INT_DATA0_LS_DATA1                      |                              \
    DCU_INT_DATA0_EQ_DATA1                      |                              \
    DCU_INT_DATA0_GT_DATA1                      |                              \
    DCU_INT_DATA0_INSIDE_WINDOW                 |                              \
    DCU_INT_DATA0_OUTSIDE_WINDOW)
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
static __IO uint32_t* DCU_TRGSELx(const M4_DCU_TypeDef *DCUx);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/** 
 * @defgroup DCU_Global_Functions DCU Global Functions
 * @{
 */

/**
 * @brief  Initialize DCU function.
 * @param  [in] pstcInit                Pointer to a @ref stc_dcu_init_t structure (DCU function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit is NULL pointer
 */
en_result_t DCU_Init(M4_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcInit)
{
    uint32_t u32RegVal = 0UL;
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        DDL_ASSERT(IS_DCU_UNIT(DCUx));
        DDL_ASSERT(IS_DCU_MODE(pstcInit->u32Mode));
        DDL_ASSERT(IS_DCU_DATA_SIZE(pstcInit->u32DataSize));
        DDL_ASSERT(IS_DCU_INTERRUPT_SEL(pstcInit->u32IntSel));
        DDL_ASSERT(IS_DCU_INTERRUPT_STATE(pstcInit->u32IntCmd));
        DDL_ASSERT(IS_DCU_CMP_TRIG_MODE(pstcInit->u32CmpTriggerMode));

        /* De-initialize DCU */
        WRITE_REG32(M4_DCU->CTL, 0x00000000UL);
        WRITE_REG32(M4_DCU->INTSEL, 0x00000000UL);
        WRITE_REG32(M4_DCU->FLAGCLR, 0x0000007FUL);

        /* Set register: CTL */
        u32RegVal = pstcInit->u32Mode | \
                    pstcInit->u32DataSize | \
                    pstcInit->u32CmpTriggerMode | \
                    pstcInit->u32IntCmd;
        WRITE_REG32(DCUx->CTL, u32RegVal);

        /* Set register: INTSEL */
        WRITE_REG32(DCUx->INTSEL, pstcInit->u32IntSel);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_uart_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_dcu_init_t structure (DCU function configuration data structure).
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcInit is NULL pointer
 */
en_result_t DCU_StructInit(stc_dcu_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcInit)
    {
        pstcInit->u32Mode = DCU_INVALID;
        pstcInit->u32DataSize = DCU_DATA_BITS_8;
        pstcInit->u32CmpTriggerMode = DCU_CMP_TRIG_BY_DATA0;
        pstcInit->u32IntCmd = DCU_INT_DISABLE;
        pstcInit->u32IntSel = 0UL;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize DCU function.
 * @param  None
 * @retval None
 */
en_result_t DCU_DeInit(void)
{
    /* Configures the registers to reset value. */
    WRITE_REG32(M4_DCU->CTL, 0x00000000UL);
    WRITE_REG32(M4_DCU->INTSEL, 0x00000000UL);
    WRITE_REG32(M4_DCU->FLAGCLR, 0x0000007FUL);

    return Ok;
}

/**
 * @brief Set DCU operation mode.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param  [in] u16Mode                 DCU mode
 *         This parameter can be one of the following values:
 *           @arg DCU_INVALID:          DCU invalid
 *           @arg DCU_ADD:              DCU add operation
 *           @arg DCU_SUB:              DCU sub operation
 *           @arg DCU_HW_TRIG_ADD:      DCU hardware trigger add
 *           @arg DCU_HW_TRIG_SUB:      DCU hardware trigger sub
 *           @arg DCU_CMP:              DCU compare
 * @retval None
 */
void DCU_SetMode(M4_DCU_TypeDef *DCUx, uint32_t u32Mode)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_MODE(u32Mode));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_MODE, u32Mode);
}

/**
 * @brief Get DCU operation mode.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg DCU_INVALID:          DCU invalid
 *           @arg DCU_ADD:              DCU add operation
 *           @arg DCU_SUB:              DCU sub operation
 *           @arg DCU_HW_TRIG_ADD:      DCU hardware trigger add
 *           @arg DCU_HW_TRIG_SUB:      DCU hardware trigger sub
 *           @arg DCU_CMP:              DCU compare
 */
uint32_t DCU_GetMode(M4_DCU_TypeDef *DCUx)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));

    return READ_REG32(DCUx->CTL) & DCU_CTL_MODE;
}

/**
 * @brief Set DCU data size.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param  [in] u32DataSize             DCU data size
 *         This parameter can be one of the following values:
 *           @arg DCU_DATA_BITS_8:      DCU data size 8 bits
 *           @arg DCU_DATA_BITS_16:     DCU data size 16 bits
 *           @arg DCU_DATA_BITS_32:     DCU data size 32 bits
 * @retval None
 */
void DCU_SetDataSize(M4_DCU_TypeDef *DCUx, uint32_t u32DataSize)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_DATA_SIZE(u32DataSize));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_DATASIZE, u32DataSize);
}

/**
 * @brief Get DCU data size.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg DCU_DATA_BITS_8:      DCU data size 8 bits
 *           @arg DCU_DATA_BITS_16:     DCU data size 16 bits
 *           @arg DCU_DATA_BITS_32:     DCU data size 32 bits
 */
uint32_t DCU_GetDataSize(M4_DCU_TypeDef *DCUx)
{
    /* Check for DCUx pointer */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));

    return READ_REG32(DCUx->CTL) & DCU_CTL_DATASIZE;
}

/**
 * @brief Get DCU flag.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u32Flag                  The specified DCU flag
 *           @arg DCU_FLAG_OPERATION:       DCU addition overflow or subtraction underflow flag
 *           @arg DCU_FLAG_DATA0_LS_DATA2:  DCU DATA0 < DATA2 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA2:  DCU DATA0 = DATA2 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA2:  DCU DATA0 > DATA2 flag
 *           @arg DCU_FLAG_DATA0_LS_DATA1:  DCU DATA0 < DATA1 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA1:  DCU DATA0 = DATA1 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA1:  DCU DATA0 > DATA1 flag
 * @retval Returned value can be one of the following values:
 *           @arg Set                         Flag is set.
 *           @arg Reset                       Flag is reset or enStatus is invalid.
 */
en_flag_status_t DCU_GetFlag(M4_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_FLAG(u32Flag));

    return READ_REG32(DCUx->FLAG) & u32Flag ? Set : Reset;
}

/**
 * @brief Get DCU flag.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u32Flag                  The specified DCU flag
 *           @arg DCU_FLAG_OPERATION:       DCU addition overflow or subtraction underflow flag
 *           @arg DCU_FLAG_DATA0_LS_DATA2:  DCU DATA0 < DATA2 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA2:  DCU DATA0 = DATA2 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA2:  DCU DATA0 > DATA2 flag
 *           @arg DCU_FLAG_DATA0_LS_DATA1:  DCU DATA0 < DATA1 flag
 *           @arg DCU_FLAG_DATA0_EQ_DATA1:  DCU DATA0 = DATA1 flag
 *           @arg DCU_FLAG_DATA0_GT_DATA1:  DCU DATA0 > DATA1 flag
 * @retval None
 */
void DCU_ClearFlag(M4_DCU_TypeDef *DCUx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_FLAG(u32Flag));

    WRITE_REG32(DCUx->FLAGCLR, u32Flag);
}

/**
 * @brief Enable/disable DCU interupt function.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param  [in] enNewSta                The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DCU_IntFunctionCmd(M4_DCU_TypeDef *DCUx,
                                en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    MODIFY_REG32(DCUx->CTL, DCU_CTL_INTEN, (Enable == enNewSta) ? DCU_CTL_INTEN : 0UL);
}

/**
 * @brief Enable/disable DCU the specified interupt source.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u32Flag                  The specified DCU flag
 *           @arg DCU_INT_OPERATION:       DCU addition overflow or subtraction underflow flag
 *           @arg DCU_INT_DATA0_LS_DATA2:  DCU DATA0 < DATA2 flag
 *           @arg DCU_INT_DATA0_EQ_DATA2:  DCU DATA0 = DATA2 flag
 *           @arg DCU_INT_DATA0_GT_DATA2:  DCU DATA0 > DATA2 flag
 *           @arg DCU_INT_DATA0_LS_DATA1:  DCU DATA0 < DATA1 flag
 *           @arg DCU_INT_DATA0_EQ_DATA1:  DCU DATA0 = DATA1 flag
 *           @arg DCU_INT_DATA0_GT_DATA1:  DCU DATA0 > DATA1 flag
 *           @arg DCU_INT_DATA0_INSIDE_WINDOW:  DCU DATA0 = DATA1 flag
 *           @arg DCU_INT_DATA0_OUTSIDE_WINDOW: DCU DATA0 > DATA1 flag
 * @param  [in] enNewSta                The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void DCU_IntCmd(M4_DCU_TypeDef *DCUx,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_DCU_UNIT(DCUx));
    DDL_ASSERT(IS_DCU_INTERRUPT_SEL(u32IntSource));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (Enable == enNewSta)
    {
        SET_REG32_BIT(DCUx->INTSEL, u32IntSource);
    }
    else
    {
        CLEAR_REG32_BIT(DCUx->INTSEL, u32IntSource);
    }
}

/**
 * @brief Enable/disable DCU the specified interupt source.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] enTriggerSrc             The trigger source.
 *           @arg This parameter can be any value of @ref en_event_src_t
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: DCUx is invalid
 */
en_result_t DCU_SetTriggerSrc(M4_DCU_TypeDef *DCUx,
                                en_event_src_t enTriggerSrc)
{
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint32_t *TRGSELx = DCU_TRGSELx(DCUx);

    if (NULL != TRGSELx)
    {
        WRITE_REG32(*TRGSELx, enTriggerSrc);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief Enable/disable DCU the specified interupt source.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU instanec pointer
 */
static __IO uint32_t* DCU_TRGSELx(const M4_DCU_TypeDef *DCUx)
{
    __IO uint32_t *TRGSELx;

    if (M4_DCU == DCUx)
    {
        TRGSELx = &M4_AOS->DCU_TRGSEL;
    }
    else
    {
        TRGSELx = NULL;
    }

    return TRGSELx;
}


/**
 * @}
 */

#endif /* DDL_DCU_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
