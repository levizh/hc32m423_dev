/**
 *******************************************************************************
 * @file  hc32m423_adc.c
 * @brief This file provides firmware functions to manage the Analog-to-Digital
 *        Converter(ADC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-03       Wuze            First version
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
#include "hc32m423_adc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_ADC ADC
 * @brief Analog-to-Digital Converter Driver Library
 * @{
 */

#if (DDL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Local_Macros ADC Local Macros
 * @{
 */
/**
 * @defgroup ADC_Configuration_Bit_Mask ADC Configuration Bit Mask
 * @{
 */
#define ADC_TRIG_SRC_MSK                    (ADC_TRGSR_TRGSELA)
#define ADC_EOC_FLAG_MSK                    (ADC_FLAG_EOCA | ADC_FLAG_EOCB)
#define ADC_SH_CFG_MSK                      (ADC_SHCR_SHT | ADC_SHCR_SHSEL)
/**
 * @}
 */

/**
 * @defgroup ADC_Trigger_Event_Register
 * @{
 */
#define ADC_TRG_EVT0_REG                    (M4_AOS->ADC_ITRGSELR0)
#define ADC_TRG_EVT1_REG                    (M4_AOS->ADC_ITRGSELR1)
/**
 * @}
 */

/**
 * @defgroup ADC_Register_Bit_Band ADC Register Bit Band
 * @{
 */
#define __PERIP_BASE                        (0x40000000UL)
#define __REG_OFS(__reg__)                  ((uint32_t)&(__reg__) - __PERIP_BASE)
#define __BIT_BAND_ADDR(__reg__, __pos__)   ((__REG_OFS(__reg__) << 5U) + ((uint32_t)(__pos__) << 2UL))
#define BIT_BAND(__reg__, __pos__)          (*(__IO uint32_t *)__BIT_BAND_ADDR(__reg__, __pos__))
/**
 * @}
 */

/**
 * @defgroup ADC_Check_Parameters_Validity ADC check parameters validity
 * @{
 */
#define IS_ADC_SCAN_MODE(x)                                                    \
(   ((x) == ADC_MODE_SA_SSHOT)              ||                                 \
    ((x) == ADC_MODE_SA_CONT)               ||                                 \
    ((x) == ADC_MODE_SA_SB_SSHOT)           ||                                 \
    ((x) == ADC_MODE_SA_CONT_SB_SSHOT))

#define IS_ADC_RESOLUTION(x)                                                   \
(   ((x) == ADC_RES_8BIT)                   ||                                 \
    ((x) == ADC_RES_10BIT)                  ||                                 \
    ((x) == ADC_RES_12BIT))

#define IS_ADC_AUTO_CLEAR_CMD(x)                                               \
(   ((x) == ADC_AUTO_CLR_DISABLE)           ||                                 \
    ((x) == ADC_AUTO_CLR_ENABLE))

#define IS_ADC_DATA_ALIGN(x)                                                   \
(   ((x) == ADC_DATA_ALIGN_RIGHT)           ||                                 \
    ((x) == ADC_DATA_ALIGN_LEFT))

#define IS_ADC_SA_RESTRT_POS(x)                                                \
(   ((x) == ADC_SA_RESTRT_POS_INT_CH)       ||                                 \
    ((x) == ADC_SA_RESTRT_POS_FIRST_CH))

#define IS_ADC_PIN_NUMBER(x)                                                   \
(   ((x) <= ADC_ANI9))

#define IS_ADC_SEQUENCE(x)                                                     \
(   ((x) == ADC_SEQ_A)                      ||                                 \
    ((x) == ADC_SEQ_B))

#define IS_ADC_SPL_TIME(x)                                                     \
(   ((x) >= 5U) && ((x) <= 255U))

#define IS_ADC_AVG_CNT(x)                                                      \
(   ((x) == ADC_AVG_CNT_2)                  ||                                 \
    ((x) == ADC_AVG_CNT_4)                  ||                                 \
    ((x) == ADC_AVG_CNT_8)                  ||                                 \
    ((x) == ADC_AVG_CNT_16)                 ||                                 \
    ((x) == ADC_AVG_CNT_32)                 ||                                 \
    ((x) == ADC_AVG_CNT_64)                 ||                                 \
    ((x) == ADC_AVG_CNT_128)                ||                                 \
    ((x) == ADC_AVG_CNT_256))

#define IS_ADC_TRIG_SRC(x)                                                     \
(   ((x) == ADC_TRIG_SRC_ADTRG)             ||                                 \
    ((x) == ADC_TRIG_SRC_EVT0)              ||                                 \
    ((x) == ADC_TRIG_SRC_EVT1)              ||                                 \
    ((x) == ADC_TRIG_SRC_EVT0_EVT1))

#define IS_ADC_EXCH_SRC(x)                                                     \
(   ((x) == ADC_EXCH_SRC_ADC_PIN)           ||                                 \
    ((x) == ADC_EXCH_SRC_INTERNAL))

#define IS_ADC_SH_CH(x)                                                        \
(   ((x) <= (ADC_CH0 | ADC_CH1 | ADC_CH2)))

#define IS_ADC_SH_CYCLE(x)                                                     \
(   ((x) >= 4U) && ((x) <= 255U))

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
 * @defgroup ADC_Global_Functions ADC Global Functions
 * @{
 */

/**
 * @brief  Initializes the ADC peripheral according to the specified parameters
 *         in the structure stc_adc_init.
 * @param  [in]  pstcInit           Pointer to a stc_adc_init_t structure value that
 *                                  contains the configuration information for the ADC.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pstcInit == NULL.
 */
en_result_t ADC_Init(const stc_adc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        DDL_ASSERT(IS_ADC_SCAN_MODE(pstcInit->u16ScanMode));
        DDL_ASSERT(IS_ADC_RESOLUTION(pstcInit->u16Resolution));
        DDL_ASSERT(IS_ADC_AUTO_CLEAR_CMD(pstcInit->u16AutoClrCmd));
        DDL_ASSERT(IS_ADC_DATA_ALIGN(pstcInit->u16DataAlign));
        DDL_ASSERT(IS_ADC_SA_RESTRT_POS(pstcInit->u16SARestrtPos));

        /* Configures scan convert mode, resolution, data automatically cleared cmd
           and data alignment. */
        M4_ADC->CR0 = pstcInit->u16ScanMode   | \
                      pstcInit->u16Resolution | \
                      pstcInit->u16AutoClrCmd | \
                      pstcInit->u16DataAlign;

        /* Configures the channel sequence A restart from. */
        M4_ADC->CR1  = pstcInit->u16SARestrtPos;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the ADC peripheral.
 * @param  None
 * @retval None
 */
void ADC_DeInit(void)
{
    uint8_t i;
    __IO uint8_t *ioSSTR;

    /* Stop the ADC. */
    ADC_Stop();

    /* Set the registers to reset value. */
    M4_ADC->CR0       = 0x0U;
    M4_ADC->CR1       = 0x0U;
    M4_ADC->TRGSR     = 0x0U;
    M4_ADC->CHSELRA0  = 0x0U;
    M4_ADC->CHSELRB0  = 0x0U;
    M4_ADC->AVCHSELR0 = 0x0U;
    M4_ADC->EXCHSELR  = 0x0U;
    M4_ADC->SHCR      = 0x0U;
    M4_ADC->ICR       = 0x0U;

    ioSSTR = (__IO uint8_t *)((uint32_t)&M4_ADC->SSTR0);
    for (i=0; i<ADC_CH_CNT; i++)
    {
        ioSSTR[i] = (uint8_t)0x0BU;
    }
}

/**
 * @brief  Set a default value for the ADC initialization structure.
 * @param  [in]  pstcInit           Pointer to a stc_adc_init_t structure that
 *                                  contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pstcInit == NULL.
 */
en_result_t ADC_StructInit(stc_adc_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u16ScanMode    = ADC_MODE_SA_SSHOT;
        pstcInit->u16Resolution  = ADC_RES_12BIT;
        pstcInit->u16AutoClrCmd  = ADC_AUTO_CLR_DISABLE;
        pstcInit->u16DataAlign   = ADC_DATA_ALIGN_RIGHT;
        pstcInit->u16SARestrtPos = ADC_SA_RESTRT_POS_INT_CH;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void ADC_SetScanMode(uint16_t u16Mode)
{
    DDL_ASSERT(IS_ADC_SCAN_MODE(u16Mode));
    MODIFY_REG16(M4_ADC->TRGSR, ADC_TRIG_SRC_MSK, u16Mode);
}

/**
 * @brief  Enable or disable ADC channel(s).
 * @param  [in]  u8Seq              The specified sequence for the channel(s) to be added in.
 *                                  This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A:               Add channels to sequence A.
 *   @arg  ADC_SEQ_B:               Add channels to sequence B.
 * @param  [in]  u16AdcCh           The specified channel(s) to be added in the specified sequence.
 *                                  This parameter can be values of @ref ADC_Channels
 * @param  [in]  pu8SplTime         
 * @param  [in]  enNewState
 *   @arg  ADC_CH0 ~ ADC_CH9
 * @retval None.
 * @note  -(1) ADC must be stoped.
 *        -(2) Sequence A and Sequence B cannot contain the same channel.
 */
en_result_t ADC_ChannelCmd(uint8_t u8Seq, uint16_t u16AdcCh, uint8_t *pu8SplTime, en_functional_state_t enNewState)
{
    uint8_t i = 0U;
    uint8_t j = 0U;
    __IO uint16_t *ioCHSELR;
    __IO uint8_t *ioSSTR;
    en_result_t enRet = ErrorInvalidParameter;

    if (pu8SplTime != NULL)
    {
        DDL_ASSERT(IS_ADC_SEQUENCE(u8Seq));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

        ioCHSELR = (__IO uint16_t *)((uint32_t)&M4_ADC->CHSELRA0);
        ioSSTR   = (__IO uint8_t *)((uint32_t)&M4_ADC->SSTR0);

        if (enNewState == Enable)
        {
            ioCHSELR[u8Seq] |= u16AdcCh;

            while (u16AdcCh)
            {
                if (u16AdcCh & (uint16_t)0x1U)
                {
                    DDL_ASSERT(IS_ADC_SPL_TIME(pu8SplTime[j]));
                    ioSSTR[i] = pu8SplTime[j++];
                }
                u16AdcCh >>= 1U;
                i++;
            }
        }
        else
        {
            ioCHSELR[u8Seq] &= (uint16_t)(~u16AdcCh);
        }

        enRet = Ok;
    }

    return enRet;

}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void ADC_AvgSetCnt(uint16_t u16AvgCnt)
{
    DDL_ASSERT(IS_ADC_AVG_CNT(u16AvgCnt));
    MODIFY_REG16(M4_ADC->CR0, ADC_CR0_AVCNT, u16AvgCnt);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void ADC_AvgChannelCmd(uint16_t u16AdcCh, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == Enable)
    {
        SET_REG16_BIT(M4_ADC->AVCHSELR0, u16AdcCh);
    }
    else
    {
        CLEAR_REG16_BIT(M4_ADC->AVCHSELR0, u16AdcCh);
    }
}

/**
 * @brief  ADC set extend channel source.
 * @param  [in]  u8ExChSrc          The specified source for the extend channel(channel 8).
 *                                  This parameter can be a value of @ref ADC_Extend_Channel_Source
 *   @arg  ADC_EXCH_SRC_ADC_PIN:    Select the pin P11(ADC_IN8) as the extend channel analog input source.
 *   @arg  ADC_EXCH_SRC_INTERNAL:   Select the internal analog source as the extend channel analog input source.
 * @retval None.
 * @note   ADC must be stoped.
 */
void ADC_SetExChannelSrc(uint8_t u8ExChSrc)
{
    DDL_ASSERT(IS_ADC_EXCH_SRC(u8ExChSrc));
    M4_ADC->EXCHSELR = u8ExChSrc;
}

/**
 * @brief  Set a default value for the trigger source configuration structure.
 * @param  [in]  pstcTrgCfg         Pointer to a stc_adc_trig_cfg_t structure that
 *                                  contains configuration information.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pstcTrgCfg == NULL.
 */
en_result_t ADC_TrigSrcStructInit(stc_adc_trig_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u16TrigSrc = ADC_TRIG_SRC_EVT0;
        pstcCfg->enEvent0   = EVT_AOS_STRG;
        pstcCfg->enEvent1   = EVT_AOS_STRG;

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Configures trigger source for the specified sequence.
 * @param  [in]  u8Seq              The sequence to be configured.
 *                                  This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A
 *   @arg  ADC_SEQ_B
 * @param  [in]  pstcTrgCfg         Pointer to a stc_adc_trig_cfg_t structure that contains
 *                                  the configuration information of the trigger source.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pstcCfg == NULL.
 * @note   ADC must be stoped.
 */
en_result_t ADC_TrigSrcConfig(uint8_t u8Seq, const stc_adc_trig_cfg_t *pstcCfg)
{
    uint8_t u8Offset  = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_ADC_SEQUENCE(u8Seq));
        DDL_ASSERT(IS_ADC_TRIG_SRC(pstcCfg->u16TrigSrc));

        if (u8Seq == ADC_SEQ_B)
        {
            u8Offset = 8U;
        }

        switch (pstcCfg->u16TrigSrc)
        {
            case ADC_TRIG_SRC_EVT0:
                ADC_TRG_EVT0_REG = pstcCfg->enEvent0;
                break;

            case ADC_TRIG_SRC_EVT1:
                ADC_TRG_EVT1_REG = pstcCfg->enEvent1;
                break;

            case ADC_TRIG_SRC_EVT0_EVT1:
                ADC_TRG_EVT0_REG = pstcCfg->enEvent0;
                ADC_TRG_EVT1_REG = pstcCfg->enEvent1;
                break;

            default:
                break;
        }

        MODIFY_REG16(M4_ADC->TRGSR, \
                     (ADC_TRIG_SRC_MSK << u8Offset), \
                     (pstcCfg->u16TrigSrc << u8Offset));
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the trigger source of the specified sequence.
 * @param  [in]  u8Seq              The sequence to be configured.
 *                                  This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A
 *   @arg  ADC_SEQ_B
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *   @arg  Enable:                  Enable the trigger source of the specified sequence.
 *   @arg  Disable:                 Disable the trigger source of the specified sequence.
 * @retval None
 * @note   ADC must be stoped.
 */
void ADC_TrigSrcCmd(uint8_t u8Seq, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_SEQUENCE(u8Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (u8Seq == ADC_SEQ_A)
    {
        bM4_ADC->TRGSR_b.TRGENA = (uint32_t)enNewState;
    }
    else
    {
        bM4_ADC->TRGSR_b.TRGENB = (uint32_t)enNewState;
    }
}

/**
 * @brief  Enable or disable the interrupt of the specified sequence.
 * @param  [in]  u8Seq              The sequence to be configured.
 *                                  This parameter can be a value of @ref ADC_Sequence
 *   @arg  ADC_SEQ_A
 *   @arg  ADC_SEQ_B
 * @param  [in]  enNewState         An en_functional_state_t enumeration value.
 *   @arg  Enable:                  Enable the interrupt of the specified sequence.
 *   @arg  Disable:                 Disable the interrupt of the specified sequence.
 * @retval None
 * @note   ADC must be stoped.
 */
void ADC_SeqIntCmd(uint8_t u8Seq, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_ADC_SEQUENCE(u8Seq));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    BIT_BAND(M4_ADC->ICR, u8Seq) = (uint32_t)enNewState;
}

/**
 * @brief  Gets the EOC(End Of Conversion) flag.
 * @param  [in]  u8Flag         ADC EOC flag.
 *                              This parameter can be a value of @ref ADC_Eoc_Flag
 *   @arg  ADC_FLAG_EOCA
 *   @arg  ADC_FLAG_EOCB
 *   @arg  ADC_FLAG_SA_INTED
 * @retval An en_flag_status_t enumeration.
 *   @arg  Set: The specified flag has set.
 *   @arg  Reset: The specified flag has not set.
 */
en_flag_status_t ADC_SeqGetStatus(uint8_t u8Flag)
{
    return (en_flag_status_t)((M4_ADC->ISR & u8Flag) != 0U);
}

/**
 * @brief  Clear the EOC(End Of Conversion) flag.
 * @param  [in]  u8Flag             An 8bit data that containing EOCA(End Of Conversion of Sequence A)
 *                                  flag and EOCB flag. This parameter can be values of @ref ADC_Eoc_Flag
 *                                  except ADC_FLAG_SA_INTED.
 *   @arg  ADC_FLAG_EOCA
 *   @arg  ADC_FLAG_EOCB
 * @retval None
 */
void ADC_SeqClrStatus(uint8_t u8Flag)
{
    u8Flag &= ADC_EOC_FLAG_MSK;
    M4_ADC->ISCLRR |= u8Flag;
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void ADC_SH_Config(uint16_t u16AdcCh, uint8_t u8ShCycle)
{
    uint16_t u16Temp;

    DDL_ASSERT(IS_ADC_SH_CH(u16AdcCh));
    DDL_ASSERT(IS_ADC_SH_CYCLE(u8ShCycle));

    u16Temp  = (uint16_t)(u16AdcCh << ADC_SHCR_SHSEL_POS);
    u16Temp |= (uint16_t)u8ShCycle;
    MODIFY_REG16(M4_ADC->SHCR, ADC_SH_CFG_MSK, u16Temp);
}

/**
 * @brief  
 * @param  [in]  
 * @param  [out] 
 * @retval None
 */
void ADC_ContSplCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    bM4_ADC->SHCR_b.SHMD = (uint32_t)enNewState;
}

/**
 * @brief  Starts ADC conversion of sequence A.
 * @param  [out] pu16AdcData        Pointer to the buffer the ADC data to be stored.
 * @param  [in]  u8Length           The length of the array pointed by pu16AdcData.
 * @param  [in]  u32Timeout         Timeout value(millisecond).
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pu16AdcData == NULL or u32Timeout == 0.
 *   @arg  ErrorTimeout:            ADC works timeout.
 */
en_result_t ADC_PollingSA(uint16_t *pu16AdcData, uint8_t u8Length, uint32_t u32Timeout)
{
    uint16_t    u16AdcCh;
    uint32_t    u32TimeCnt;
    en_result_t enRet = ErrorInvalidParameter;

    if ((pu16AdcData != NULL) && (u8Length != 0U) && (u32Timeout != 0U))
    {
        /* 10 is the number of required instructions cycles for the below loop statement. */
        u32TimeCnt = u32Timeout * (SystemCoreClock / 10U / 1000U);

        ADC_Start();

        /* Polling and check timeout. */
        enRet = ErrorTimeout;
        while (u32TimeCnt--)
        {
            if (bM4_ADC->ISR_b.EOCAF != 0U)
            {
                if (u8Length < ADC_CH_CNT)
                {
                    u16AdcCh = M4_ADC->CHSELRA0;
                    ADC_GetChannelData(u16AdcCh, pu16AdcData, u8Length);
                }
                else
                {
                    ADC_GetAllData(pu16AdcData, ADC_CH_CNT);
                }
                enRet = Ok;
                break;
            }
        }

        bM4_ADC->ISCLRR_b.CLREOCAF = (uint32_t)1U;
    }

    return enRet;
}

/**
 * @brief  Get all of the ADC data.
 * @param  [out] pu16AdcData        Pointer to the buffer the ADC data to be stored.
 * @param  [in]  u8Length           The length of the array pointed by the pointer pu16AdcData.
 *                                  It must be no less than @ref ADC_Channel_Count
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   pu16AdcData == NULL or u8Length < ADC_CH_CNT.
 */
en_result_t ADC_GetAllData(uint16_t *pu16AdcData, uint8_t u8Length)
{
    uint8_t  i;
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint16_t *io16AdcDr = (__IO uint16_t *)((uint32_t)&M4_ADC->DR0);

    if ((pu16AdcData != NULL) && (u8Length >= ADC_CH_CNT))
    {
        for (i = 0U; i < ADC_CH_CNT; i++)
        {
            pu16AdcData[i] = io16AdcDr[i];
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the ADC data of the specified channel(s).
 * @param  [in]  u16AdcCh           The specified Channel(s).
 *                                  This parameter can be values of @ref ADC_Channels
 *   @arg  ADC_CH0 ~ ADC_CH11
 * @param  [out] pu16AdcData        Pointer to the buffer the ADC data to be stored.
 * @param  [in]  u8Length           The length of the array pointed by pu16AdcData.
 * @retval An en_result_t enumeration value.
 *   @arg  Ok:                      No errors occurred.
 *   @arg  ErrorInvalidParameter:   u16AdcCh == 0 or pu16AdcData == NULL or u8Length == 0
 */
en_result_t ADC_GetChannelData(uint16_t u16AdcCh, uint16_t *pu16AdcData, uint8_t u8Length)
{
    uint8_t i;
    uint8_t j;
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint16_t *io16AdcDr;

    if ((u16AdcCh != 0U) && (pu16AdcData != NULL) && (u8Length != 0U))
    {
        i = 0U;
        j = 0U;
        io16AdcDr = (__IO uint16_t *)((uint32_t)&M4_ADC->DR0);
        u16AdcCh &= ADC_CH_ALL;
        while (u16AdcCh && u8Length)
        {
            if (u16AdcCh & 0x1U)
            {
                pu16AdcData[j++] = io16AdcDr[i];
                u8Length--;
            }

            u16AdcCh >>= 1U;
            i++;
        }

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Get the ADC value of the specified ADC pin.
 * @param  [in]  u8AdcPin           The ADC pin number.
 *                                  This parameter can be a value of @ref ADC_Pin_Number
 * @retval An uint16_t value -- the ADC value of the specified ADC pin.
 */
uint16_t ADC_GetValue(uint8_t u8AdcPin)
{
    uint16_t u16Ret = (uint16_t)0xFFFF;
    __IO uint16_t *io16AdcDr = (__IO uint16_t *)((uint32_t)&M4_ADC->DR0);

    if (u8AdcPin <= ADC_PIN_NUM_MAX)
    {
        u16Ret = io16AdcDr[u8AdcPin];
    }

    return u16Ret;
}

/**
 * @}
 */

#endif /* DDL_ADC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
