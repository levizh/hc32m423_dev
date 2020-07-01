/**
 *******************************************************************************
 * @file  hc32m423_dcu.h
 * @brief This file contains all the functions prototypes of the DCU driver
 *        library.
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
#ifndef __HC32M423_DCU_H__
#define __HC32M423_DCU_H__

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
 * @addtogroup DDL_DCU
 * @{
 */

#if (DDL_DCU_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup DCU_Global_Types DCU Global Types
 * @{
 */

/**
 * @brief DCU initialization structure definition
 */
typedef struct stc_dcu_init
{
    uint32_t    u32IntCmd;          /*!< Select DCU interrupt function.
                                         This parameter can be a value of @ref DCU_Interrupt_State */

    uint32_t    u32IntSel;          /*!< Specifies interrupt selection.
                                         This parameter can be a value of @ref DCU_Interrupt_Selection */

    uint32_t    u32DataSize;        /*!< Specifies DCU data size.
                                         This parameter can be a value of @ref DCU_Data_Size */

    uint32_t    u32Mode;            /*!< Specifies DCU operation.
                                         This parameter can be a value of @ref DCU_Mode */

    uint32_t    u32CmpTriggerMode;  /*!< Specifies DCU compare operation trigger mode size.
                                         This parameter can be a value of @ref DCU_Compare_Trigger_Mode */
} stc_dcu_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup DCU_Global_Macros DCU Global Macros
 * @{
 */

/**
 * @defgroup DCU_Data_Size DCU Data Size
 * @{
 */
#define DCU_DATA_BITS_8                         ((uint32_t)0UL)         /*!< DCU data size: 8 bit */
#define DCU_DATA_BITS_16                        (DCU_CTL_DATASIZE_0)    /*!< DCU data size: 16 bit */
#define DCU_DATA_BITS_32                        (DCU_CTL_DATASIZE_1)    /*!< DCU data size: 32 bit */
/**
 * @}
 */

/**
 * @defgroup DCU_Compare_Trigger_Mode DCU Compare Trigger Mode
 * @{
 */
#define DCU_CMP_TRIG_BY_DATA0                   ((uint32_t)0UL)         /*!< DCU compare triggered by DATA0 */
#define DCU_CMP_TRIG_BY_DATA012                 (DCU_CTL_DATASIZE_0)    /*!< DCU compare triggered by DATA0 or DATA1 or DATA2 */
/**
 * @}
 */

/**
 * @defgroup DCU_Mode DCU Mode
 * @{
 */
#define DCU_INVALID                             ((uint32_t)0UL)         /*!< DCU invalid */
#define DCU_ADD                                 (DCU_CTL_MODE_0)        /*!< DCU add operation */
#define DCU_SUB                                 (DCU_CTL_MODE_1)        /*!< DCU sub operation */
#define DCU_HW_TRIG_ADD                         (DCU_CTL_MODE_1 | \
                                                 DCU_CTL_MODE_0)        /*!< DCU hardware trigger add */
#define DCU_HW_TRIG_SUB                         (DCU_CTL_MODE_2 | \
                                                 DCU_CTL_MODE_0)        /*!< DCU hardware trigger sub */
#define DCU_CMP                                 (DCU_CTL_MODE_2 | \
                                                 DCU_CTL_MODE_1)        /*!< DCU compare */
/**
 * @}
 */

/**
 * @defgroup DCU_Interrupt_State DCU Interrupt State
 * @{
 */
#define DCU_INT_DISABLE                         ((uint32_t)0UL)     /*!< Disable DCU interrupt */
#define DCU_INT_ENABLE                          (DCU_CTL_INTEN)     /*!< Enable DCU interrupt */
/**
 * @}
 */

/**
 * @defgroup DCU_Flag DCU Flag
 * @{
 */
#define DCU_FLAG_OPERATION                      (DCU_FLAG_FLAG_OP)      /*!< DCU addition overflow or subtraction underflow flag */
#define DCU_FLAG_DATA0_LS_DATA2                 (DCU_FLAG_FLAG_LS2)     /*!< DCU DATA0 < DATA2 flag */
#define DCU_FLAG_DATA0_EQ_DATA2                 (DCU_FLAG_FLAG_EQ2)     /*!< DCU DATA0 = DATA2 flag */
#define DCU_FLAG_DATA0_GT_DATA2                 (DCU_FLAG_FLAG_GT2)     /*!< DCU DATA0 > DATA2 flag */
#define DCU_FLAG_DATA0_LS_DATA1                 (DCU_FLAG_FLAG_LS1)     /*!< DCU DATA0 < DATA1 flag */
#define DCU_FLAG_DATA0_EQ_DATA1                 (DCU_FLAG_FLAG_EQ1)     /*!< DCU DATA0 = DATA1 flag */
#define DCU_FLAG_DATA0_GT_DATA1                 (DCU_FLAG_FLAG_GT1)     /*!< DCU DATA0 > DATA1 flag */
/**
 * @}
 */

/**
 * @defgroup DCU_Interrupt_Selection DCU Interrupt Selection
 * @{
 */
#define DCU_INT_OPERATION                       (DCU_INTSEL_INT_OP)     /*!< DCU addition overflow or subtraction underflow interrupt */
#define DCU_INT_DATA0_LS_DATA2                  (DCU_INTSEL_INT_LS2)    /*!< DCU DATA0 < DATA2 interrupt */
#define DCU_INT_DATA0_EQ_DATA2                  (DCU_INTSEL_INT_EQ2)    /*!< DCU DATA0 = DATA2 interrupt */
#define DCU_INT_DATA0_GT_DATA2                  (DCU_INTSEL_INT_GT2)    /*!< DCU DATA0 > DATA2 interrupt */
#define DCU_INT_DATA0_LS_DATA1                  (DCU_INTSEL_INT_LS1)    /*!< DCU DATA0 < DATA1 interrupt */
#define DCU_INT_DATA0_EQ_DATA1                  (DCU_INTSEL_INT_EQ1)    /*!< DCU DATA0 = DATA1 interrupt */
#define DCU_INT_DATA0_GT_DATA1                  (DCU_INTSEL_INT_GT1)    /*!< DCU DATA0 > DATA1 interrupt */
#define DCU_INT_DATA0_INSIDE_WINDOW             (DCU_INTSEL_INT_WIN_0)  /*!< DCU (DATA0 > DATA1& DATA0 < DATA2) interrupt */
#define DCU_INT_DATA0_OUTSIDE_WINDOW            (DCU_INTSEL_INT_WIN_1)  /*!< DCU (DATA0 < DATA1& DATA0 > DATA2) interrupt */
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
 * @addtogroup DCU_Global_Functions
 * @{
 */

/**
 * @brief  Read DCU register DATA0 for byte.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA0 value for byte
 */
__STATIC_INLINE uint8_t DCU_ReadReg8Data0(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint8_t *)(&DCUx->DATA0);
}

/**
 * @brief  Read DCU register DATA0 for byte.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u8Data                   The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint8_t DCU_WriteReg8Data0(M4_DCU_TypeDef *DCUx,
                                                    uint8_t u8Data)
{
    *(__IO uint8_t *)(&DCUx->DATA0) = u8Data;
}

/**
 * @brief  Read DCU register DATA1 for byte.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA1 value for byte
 */
__STATIC_INLINE uint8_t DCU_ReadReg8Data1(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint8_t *)(&DCUx->DATA1);
}

/**
 * @brief  Read DCU register DATA1 for byte.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u8Data                   The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint8_t DCU_WriteReg8Data1(M4_DCU_TypeDef *DCUx,
                                                    uint8_t u8Data)
{
    *(__IO uint8_t *)(&DCUx->DATA1) = u8Data;
}

/**
 * @brief  Read DCU register DATA2 for byte.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA2 value for byte
 */
__STATIC_INLINE uint8_t DCU_ReadReg8Data2(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint8_t *)(&DCUx->DATA2);
}

/**
 * @brief  Read DCU register DATA2 for byte.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u8Data                   The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint8_t DCU_WriteReg8Data2(M4_DCU_TypeDef *DCUx,
                                                    uint8_t u8Data)
{
    *(__IO uint8_t *)(&DCUx->DATA2) = u8Data;
}

/**
 * @brief  Read DCU register DATA0 for half-word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA0 value for half-word
 */
__STATIC_INLINE uint16_t DCU_ReadReg16Data0(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint16_t *)(&DCUx->DATA0);
}

/**
 * @brief  Read DCU register DATA0 for half-word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u16Data                  The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint16_t DCU_WriteReg16Data0(M4_DCU_TypeDef *DCUx,
                                                    uint16_t u16Data)
{
    *(__IO uint16_t *)(&DCUx->DATA0) = u16Data;
}

/**
 * @brief  Read DCU register DATA1 for half-word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA1 value for half-word
 */
__STATIC_INLINE uint16_t DCU_ReadReg16Data1(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint16_t *)(&DCUx->DATA1);
}

/**
 * @brief  Read DCU register DATA1 for half-word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u16Data                  The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint16_t DCU_WriteReg16Data1(M4_DCU_TypeDef *DCUx,
                                                    uint16_t u16Data)
{
    *(__IO uint16_t *)(&DCUx->DATA1) = u16Data;
}

/**
 * @brief  Read DCU register DATA2 for half-word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA2 value for half-word
 */
__STATIC_INLINE uint16_t DCU_ReadReg16Data2(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint16_t *)(&DCUx->DATA2);
}

/**
 * @brief  Read DCU register DATA2 for half-word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u16Data                  The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint16_t DCU_WriteReg16Data2(M4_DCU_TypeDef *DCUx,
                                                    uint16_t u16Data)
{
    *(__IO uint16_t *)(&DCUx->DATA2) = u16Data;
}

/**
 * @brief  Read DCU register DATA0 for word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA0 value for word
 */
__STATIC_INLINE uint32_t DCU_ReadReg32Data0(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint32_t *)(&DCUx->DATA0);
}

/**
 * @brief  Read DCU register DATA0 for word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u32Data                  The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint32_t DCU_WriteReg32Data0(M4_DCU_TypeDef *DCUx,
                                                    uint32_t u32Data)
{
    *(__IO uint32_t *)(&DCUx->DATA0) = u32Data;
}

/**
 * @brief  Read DCU register DATA1 for word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA1 value for word
 */
__STATIC_INLINE uint32_t DCU_ReadReg32Data1(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint32_t *)(&DCUx->DATA1);
}

/**
 * @brief  Read DCU register DATA1 for word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u32Data                  The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint32_t DCU_WriteReg32Data1(M4_DCU_TypeDef *DCUx,
                                                    uint32_t u32Data)
{
    *(__IO uint32_t *)(&DCUx->DATA1) = u32Data;
}

/**
 * @brief  Read DCU register DATA2 for word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @retval DCU register DATA2 value for word
 */
__STATIC_INLINE uint32_t DCU_ReadReg32Data2(M4_DCU_TypeDef *DCUx)
{
    return *(__IO uint32_t *)(&DCUx->DATA2);
}

/**
 * @brief  Read DCU register DATA2 for word.
 * @param [in] DCUx                     Pointer to DCU instance register base
 *           @arg M4_DCU:               DCU unit 1 instance register base
 * @param [in] u32Data                  The data to wirte.
 * @retval None
 */
__STATIC_INLINE uint32_t DCU_WriteReg32Data2(M4_DCU_TypeDef *DCUx,
                                                    uint32_t u32Data)
{
    *(__IO uint32_t *)(&DCUx->DATA2) = u32Data;
}

/* Initialization and configuration DCU functions */
en_result_t DCU_Init(M4_DCU_TypeDef *DCUx, const stc_dcu_init_t *pstcInit);
en_result_t DCU_StructInit(stc_dcu_init_t *pstcInit);
en_result_t DCU_DeInit(void);

void DCU_SetMode(M4_DCU_TypeDef *DCUx, uint32_t u32Mode);
uint32_t DCU_GetMode(M4_DCU_TypeDef *DCUx);
void DCU_SetDataSize(M4_DCU_TypeDef *DCUx, uint32_t u32DataSize);
uint32_t DCU_GetDataSize(M4_DCU_TypeDef *DCUx);
en_flag_status_t DCU_GetFlag(M4_DCU_TypeDef *DCUx, uint32_t u32Flag);
void DCU_ClearFlag(M4_DCU_TypeDef *DCUx, uint32_t u32Flag);
void DCU_IntFunctionCmd(M4_DCU_TypeDef *DCUx,
                                en_functional_state_t enNewSta);
void DCU_IntCmd(M4_DCU_TypeDef *DCUx,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewSta);
en_result_t DCU_SetTriggerSrc(M4_DCU_TypeDef *DCUx,
                                en_event_src_t enTriggerSrc);

/**
 * @}
 */

#endif /* DDL_CTC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_DCU_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
