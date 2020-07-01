/**
 *******************************************************************************
 * @file  hc32m423_adc.h
 * @brief This file contains all the functions prototypes of the ADC driver
 *        library.
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
#ifndef __HC32M423_ADC_H__
#define __HC32M423_ADC_H__

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
 * @addtogroup DDL_ADC
 * @{
 */

#if (DDL_ADC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Types ADC Global Types
 * @{
 */

/**
 * @brief Structure definition of ADC initialization.
 */
typedef struct
{
    uint16_t u16ScanMode;       /*!< Configures the scan convert mode of ADC.
                                     This parameter can be a value of @ref ADC_Scan_Convert_Mode */
    uint16_t u16Resolution;     /*!< Configures the ADC resolution.
                                     This parameter can be a value of @ref ADC_Resolution */
    uint16_t u16AutoClrCmd;     /*!< Configures whether the ADC data register is
                                     automatically cleared after the data is read.
                                     This parameter can be a value of @ref ADC_Data_Auto_Clear_Cmd */
    uint16_t u16DataAlign;      /*!< Specifies ADC data alignment to right or to left.
                                     This parameter can be a value of @ref ADC_Data_Align */
    uint16_t u16SAResumePos;    /*!< Specifies the resume channel position of sequence A.
                                     Sequence A can be interrupted by sequence B. After the
                                     the ending of sequence B, sequence A resumes from the
                                     specified channel position.
                                     This parameter can be a value of @ref ADC_Sequence_A_Resume_Channel_Position */
} stc_adc_init_t;

/**
 * @brief Structure definition of ADC trigger source configuration.
 */
typedef struct
{
    uint16_t u16TrigSrc;        /*!< Specifies the trigger source type for the specified sequence.
                                     This parameter can be a value of @ref ADC_Trigger_Source_Type */
    en_event_src_t enEvent0;    /*!< An @ref en_event_src_t enumeration value. */
    en_event_src_t enEvent1;    /*!< An @ref en_event_src_t enumeration value. */
} stc_adc_trig_cfg_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ADC_Global_Macros ADC Global Macros
 * @{
 */

/**
 * @defgroup ADC_Sequence ADC Sequence
 * @{
 */
#define ADC_SEQ_A                       ((uint8_t)0U)
#define ADC_SEQ_B                       ((uint8_t)1U)
/**
 * @}
 */

/**
 * @defgroup ADC_Scan_Convert_Mode ADC Scan Convert Mode
 * @{
 */
#define ADC_MODE_SA_SSHOT               (0x0U)              /*!< Sequence A single shot. */
#define ADC_MODE_SA_CONT                (ADC_CR0_MS_0)      /*!< Sequence A continuous. */
#define ADC_MODE_SA_SB_SSHOT            (ADC_CR0_MS_1)      /*!< Sequence A and B both single shot. */
#define ADC_MODE_SA_CONT_SB_SSHOT       (ADC_CR0_MS_1 | \
                                         ADC_CR0_MS_0)      /*!< Sequence A continuous and sequence B single shot. */
/**
 * @}
 */

/**
 * @defgroup ADC_Resolution ADC Resolution
 * @{
 */
#define ADC_RESOLUTION_12BIT            (0x0U)              /*!< Resolution is 12 bit. */
#define ADC_RESOLUTION_10BIT            (ADC_CR0_ACCSEL_0)  /*!< Resolution is 10 bit. */
#define ADC_RESOLUTION_8BIT             (ADC_CR0_ACCSEL_1)  /*!< Resolution is 8 bit. */
/**
 * @}
 */

/**
 * @defgroup ADC_Data_Auto_Clear_Command ADC Data Auto Clear Command
 * @{
 */
#define ADC_AUTO_CLR_DISABLE            (0x0U)
#define ADC_AUTO_CLR_ENABLE             (ADC_CR0_CLREN)     /*!< ADC data register is automatically cleared after the data is read. */
/**
 * @}
 */

/**
 * @defgroup ADC_Data_Alignment ADC Data Alignment
 * @{
 */
#define ADC_DATA_ALIGN_RIGHT            (0x0U)
#define ADC_DATA_ALIGN_LEFT             (ADC_CR0_DFMT)
/**
 * @}
 */

/**
 * @defgroup ADC_Average_Count ADC Average Count
 * @{
 */
#define ADC_AVG_CNT_2                   (0x0U)
#define ADC_AVG_CNT_4                   (ADC_CR0_AVCNT_0)
#define ADC_AVG_CNT_8                   (ADC_CR0_AVCNT_1)
#define ADC_AVG_CNT_16                  (ADC_CR0_AVCNT_1 | ADC_CR0_AVCNT_0)
#define ADC_AVG_CNT_32                  (ADC_CR0_AVCNT_2)
#define ADC_AVG_CNT_64                  (ADC_CR0_AVCNT_2 | ADC_CR0_AVCNT_0)
#define ADC_AVG_CNT_128                 (ADC_CR0_AVCNT_2 | ADC_CR0_AVCNT_1)
#define ADC_AVG_CNT_256                 (ADC_CR0_AVCNT_2 | ADC_CR0_AVCNT_1 | ADC_CR0_AVCNT_0)
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_A_Resume_Channel_Position ADC Sequence A Resume Channel Position
 * @{
 */
#define ADC_SA_RESUME_POS_INT_CH        (0x0U)                      /*!< Resumes from the interrupt channel of the sequence. */
#define ADC_SA_RESUME_POS_FIRST_CH      (ADC_CR1_RSCHSEL)           /*!< Resumes from the first channel of the sequence. */
/**
 * @}
 */

/**
 * @defgroup ADC_Trigger_Source_Type ADC Trigger Source Type
 * @{
 */
#define ADC_TRIG_SRC_ADTRG              (0x0U)                      /*!< The trigger source is the falling edge(the low level of the should \
                                                                         hold at least 1.5*PCLK cycle) of external pin ADTRGx(x=1, 2, 3). */
#define ADC_TRIG_SRC_EVENT0             (ADC_TRGSR_TRGSELA_0)       /*!< The trigger source is a internal event from other periperl. \
                                                                         Only one event can be configured to trigger ADC. */
#define ADC_TRIG_SRC_EVENT1             (ADC_TRGSR_TRGSELA_1)       /*!< The trigger source is a internal event from other periperl. \
                                                                         Only one event can be configured to trigger ADC. */
#define ADC_TRIG_SRC_EVENT0_EVENT1      (ADC_TRGSR_TRGSELA_0 | \
                                         ADC_TRGSR_TRGSELA_1)       /*!< The trigger source are two internal events from other periperl(s). \
                                                                         Two events can be configured to trigger ADC and one of which can trigger the ADC. */
/**
 * @}
 */

/**
 * @defgroup ADC_Extend_Channel_Source ADC Extend Channel Source
 * @{
 */
#define ADC_EXCH_SRC_ADC_PIN        (0x0U)                      /*!< The input source of the extended channel is analog input pin. */
#define ADC_EXCH_SRC_INTERNAL       (ADC_EXCHSELR_EXCHSEL)      /*!< The input source of the extended channel is internal analog signal. */
/**
 * @}
 */

/**
 * @defgroup ADC_Sequence_Status_Flag ADC Sequence Status Flag
 * @{
 */
#define ADC_SEQ_FLAG_EOCA           (ADC_ISR_EOCAF)             /*!< Status flag of the end of conversion of sequence A. */
#define ADC_SEQ_FLAG_EOCB           (ADC_ISR_EOCBF)             /*!< Status flag of the end of conversion of sequence B. */
#define ADC_SEQ_FLAG_SA_INTED       (ADC_ISR_SASTPDF)           /*!< Status flag of sequence A was interrupted by sequence B. */
/**
 * @}
 */

/**
 * @defgroup ADC_Pin_Number ADC Pin Number
 * @{
 */
#define ADC_ANI0                    (0U)       /*!< Pin P40 */
#define ADC_ANI1                    (1U)       /*!< Pin P41 */
#define ADC_ANI2                    (2U)       /*!< Pin P42 */
#define ADC_ANI3                    (3U)       /*!< Pin P43 */
#define ADC_ANI4                    (4U)       /*!< Pin P44 */
#define ADC_ANI5                    (5U)       /*!< Pin P45 */
#define ADC_ANI6                    (6U)       /*!< Pin P46 */
#define ADC_ANI7                    (7U)       /*!< Pin P47 */
#define ADC_ANI8                    (8U)       /*!< Pin P11 */
#define ADC_ANI9                    (9U)       /*!< Pin P10 */
#define ADC_PIN_NUM_MAX             (ADC_ANI9)
#define ADC_CH_NUM_MAX              (ADC_ANI9)
/**
 * @}
 */

/**
 * @defgroup ADC_Channel_Count ADC Channel Count
 * @{
 */
#define ADC_CH_CNT                  (10U)
/**
 * @}
 */

/**
 * @defgroup ADC_Channels ADC Common Channels
 * @{
 */
#define ADC_CH0                     (0x1UL << ADC_ANI0)
#define ADC_CH1                     (0x1UL << ADC_ANI1)
#define ADC_CH2                     (0x1UL << ADC_ANI2)
#define ADC_CH3                     (0x1UL << ADC_ANI3)
#define ADC_CH4                     (0x1UL << ADC_ANI4)
#define ADC_CH5                     (0x1UL << ADC_ANI5)
#define ADC_CH6                     (0x1UL << ADC_ANI6)
#define ADC_CH7                     (0x1UL << ADC_ANI7)
#define ADC_CH8                     (0x1UL << ADC_ANI8)
#define ADC_CH9                     (0x1UL << ADC_ANI9)
#define ADC_CH_ALL                  (x03FFU)
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
 * @addtogroup ADC_Global_Functions
 * @{
 */

/**
 * @brief  Start ADC.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void ADC_Start(void)
{
    bM4_ADC->STR_b.STRT = 0x1U;
}

/**
 * @brief  Stop ADC.
 * @param  None
 * @retval None
 */
__STATIC_INLINE void ADC_Stop(void)
{
    bM4_ADC->STR_b.STRT = 0x0U;
}

/**
 * @brief  Get ADC run status.
 * @param  None
 * @retval An en_flag_status_t enumeration.
 *   @arg  Set: The ADC is running.
 *   @arg  Reset: The ADC is stop.
 */
__STATIC_INLINE en_flag_status_t ADC_GetRunStatus(void)
{
    return (en_flag_status_t)(bM4_ADC->STR_b.STRT);
}

en_result_t ADC_Init(const stc_adc_init_t *pstcInit);
void ADC_DeInit(void);

en_result_t ADC_StructInit(stc_adc_init_t *pstcInit);

void ADC_SetScanMode(uint16_t u16Mode);
en_result_t ADC_ChannelCmd(uint8_t u8Seq, uint16_t u16AdcCh, \
                           const uint8_t pu8SplTime[], \
                           en_functional_state_t enNewState);

void ADC_AvgChannelConfig(uint16_t u16AvgCnt);
void ADC_AvgChannelCmd(uint16_t u16AdcCh, en_functional_state_t enNewState);
void ADC_SetExChannelSrc(uint8_t u8ExChSrc);

en_result_t ADC_TrigSrcStructInit(stc_adc_trig_cfg_t *pstcCfg);
en_result_t ADC_TrigSrcConfig(uint8_t u8Seq, const stc_adc_trig_cfg_t *pstcCfg);
void ADC_TrigSrcCmd(uint8_t u8Seq, en_functional_state_t enNewState);

void ADC_SeqIntCmd(uint8_t u8Seq, en_functional_state_t enNewState);
en_flag_status_t ADC_SeqGetStatus(uint8_t u8Flag);
void ADC_SeqClrStatus(uint8_t u8Flag);

void ADC_SH_Config(uint16_t u16AdcCh, uint8_t u8ShCycle);
void ADC_ContSplCmd(en_functional_state_t enNewState);

en_result_t ADC_PollingSA(uint16_t *pu16AdcData, uint8_t u8Length, uint32_t u32Timeout);

en_result_t ADC_GetAllData(uint16_t *pu16AdcData, uint8_t u8Length);
en_result_t ADC_GetChannelData(uint16_t u16AdcCh, uint16_t *pu16AdcData, uint8_t u8Length);
uint16_t ADC_GetValue(uint8_t u8AdcPin);
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

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_ADC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
