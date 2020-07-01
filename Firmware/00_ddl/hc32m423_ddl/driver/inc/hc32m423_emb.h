/**
 *******************************************************************************
 * @file  hc32m423_emb.h
 * @brief Head file for EMB module.
 *
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
#ifndef __HC32M423_EMB_H__
#define __HC32M423_EMB_H__

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
 * @addtogroup DDL_EMB
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Types EMB Global Types
 * @{
 */

/**
 * @brief EMB detect Timer4 PWM level configuration
 */
typedef struct
{
    uint32_t    u32PwmWLvl;                 /*!< Enable or disable EMB detect Timer4 PWM W channel polarity level
                                                 This parameter can be a value of @ref EMB_Group0_Detect_Timer4_PWMW_Level */

    uint32_t    u32PwmVLvl;                 /*!< Enable or disable EMB detect Timer4 PWM V channel polarity level
                                                 This parameter can be a value of @ref EMB_Group0_Detect_Timer4_PWMV_Level */

    uint32_t    u32PwmULvl;                 /*!< Enable or disable EMB detect Timer4 PWM U channel polarity level
                                                 This parameter can be a value of @ref EMB_Group0_Detect_Timer4_PWMU_Level */
} stc_emb_timer4_pwm_level_t;

/**
 * @brief EMB control Timer4 configuration
 */
typedef struct
{
    uint32_t    u32Timer4PwmUEnable;        /*!< Enable or disable EMB detect Timer4 PWM U channel same phase function
                                                 This parameter can be a value of @ref EMB_Timer4_PWM_U_Selection */

    uint32_t    u32Timer4PwmVEnable;        /*!< Enable or disable EMB detect Timer4 PWM V channel same phase function
                                                 This parameter can be a value of @ref EMB_Timer4_PWM_V_Selection */

    uint32_t    u32Timer4PwmWEnable;        /*!< Enable or disable EMB detect Timer4 PWM W channel same phase function
                                                 This parameter can be a value of @ref EMB_Timer4_PWM_W_Selection */
} stc_emb_ctrl_timer4_t;

/**
 * @brief EMB control port EMB IN configuration
 */
typedef struct
{
    uint32_t    u32PortEmbInEnable;         /*!< Enable or disable EMB detect port in(EMB_IN1) control function
                                                 This parameter can be a value of @ref EMB_Port_EMBIN1_Selection 
                                                 or @ref EMB_Port_EMBIN2_Selection or EMB_Port_EMBIN3_Selection */

    uint32_t    u32PortEmbInLevel;          /*!< EMB detect port level
                                                 This parameter can be a value of @ref EMB_Port_EMBIN1_Level
                                                 or @ref EMB_Port_EMBIN2_Level or @ref EMB_Port_EMBIN3_Level */

    uint32_t    u32PortEmbInFilterDiv;      /*!< EMB port filter division
                                                 This parameter can be a value of @ref EMB_Port_EMBIN1_Filter_Clock_Division
                                                 @ref EMB_Port_EMBIN2_Filter_Clock_Division or @ref EMB_Port_EMBIN3_Filter_Clock_Division */
} stc_emb_ctrl_port_t;

/**
 * @brief EMB group0 Timer4 initialization configuration
 */
typedef struct
{
    uint32_t    u32Cmp1Enable;              /*!< Enable or disable EMB detect CMP1 result function
                                                 This parameter can be a value of @ref EMB_CMP1_Selection */

    uint32_t    u32Cmp2Enable;              /*!< Enable or disable EMB detect CMP2 result function
                                                 This parameter can be a value of @ref EMB_CMP2_Selection */

    uint32_t    u32Cmp3Enable;              /*!< Enable or disable EMB detect CMP3 result function
                                                 This parameter can be a value of @ref EMB_CMP3_Selection */

    uint32_t    u32OscEnable;               /*!< EMB detect OSC failure function
                                                 This parameter can be a value of @ref EMB_OSC_Stop_Selection */

    stc_emb_ctrl_timer4_t   stcTimer4;      /*!< EMB detect Timer4 function
                                                 This parameter details refer @ref stc_emb_ctrl_timer4_t structure */

    stc_emb_ctrl_port_t     stcEmbIn1;      /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_ctrl_port_t structure */

    stc_emb_ctrl_port_t     stcEmbIn2;      /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_ctrl_port_t structure */

    stc_emb_ctrl_port_t     stcEmbIn3;      /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_ctrl_port_t structure */
} stc_emb_group0_timer4_init_t;

/**
 * @brief EMB group1 TimerB initialization configuration
 */
typedef struct
{
    uint32_t    u32Cmp1Enable;              /*!< Enable or disable EMB detect CMP1 result function
                                                 This parameter can be a value of @ref EMB_CMP1_Selection */

    uint32_t    u32Cmp2Enable;              /*!< Enable or disable EMB detect CMP2 result function
                                                 This parameter can be a value of @ref EMB_CMP2_Selection */

    uint32_t    u32Cmp3Enable;              /*!< Enable or disable EMB detect CMP3 result function
                                                 This parameter can be a value of @ref EMB_CMP3_Selection */

    uint32_t    u32OscEnable;               /*!< EMB detect OSC failure function
                                                 This parameter can be a value of @ref EMB_OSC_Stop_Selection */

    stc_emb_ctrl_port_t     stcEmbIn1;      /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_ctrl_port_t structure */

    stc_emb_ctrl_port_t     stcEmbIn2;      /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_ctrl_port_t structure */

    stc_emb_ctrl_port_t     stcEmbIn3;      /*!< EMB detect port EMBIN1 function
                                                 This parameter details refer @ref stc_emb_ctrl_port_t structure */
} stc_emb_group1_timerb_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Global_Macros EMB Global Macros
 * @{
 */

/**
 * @defgroup EMB_Group EMB Group
 * @{
 */
#define EMB_GROUP0_TMR4                         ((uint32_t)0UL)
#define EMB_GROUP1_TMRB                         ((uint32_t)1UL)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP1_Selection EMB CMP1 Selection
 * @{
 */
#define EMB_CMP1_ENABLE                         (EMB_CTL0_CMPEN_0)
#define EMB_CMP1_DISABLE                        ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP2_Selection EMB CMP2 Selection
 * @{
 */
#define EMB_CMP2_ENABLE                         (EMB_CTL0_CMPEN_1)
#define EMB_CMP2_DISABLE                        ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_CMP3_Selection EMB CMP3 Selection
 * @{
 */
#define EMB_CMP3_ENABLE                         (EMB_CTL0_CMPEN_2)
#define EMB_CMP3_DISABLE                        ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_OSC_Stop_Selection EMB OSC Stop Selection
 * @{
 */
#define EMB_OSC_ENABLE                          (EMB_CTL0_OSCSTPEN)
#define EMB_OSC_DISABLE                         ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer4_PWM_W_Selection EMB Timer4 PWM W Selection
 * @{
 */
#define EMB_TMR4_PWMW_ENABLE                    (EMB_CTL0_PWMSEN0)
#define EMB_TMR4_PWMW_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer4_PWM_V_Selection EMB Timer4 PWM V Selection
 * @{
 */
#define EMB_TMR4_PWMV_ENABLE                    (EMB_CTL0_PWMSEN1)
#define EMB_TMR4_PWMV_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Timer4_PWM_U_Selection EMB Timer4 PWM U Selection
 * @{
 */
#define EMB_TMR4_PWMU_ENABLE                    (EMB_CTL0_PWMSEN2)
#define EMB_TMR4_PWMU_DISABLE                   ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_EMBIN1_Selection EMB Port EMB IN1 Selection
 * @{
 */
#define EMB_PORT_EMBIN1_ENABLE                  (EMB_CTL0_PORTINEN0)
#define EMB_PORT_EMBIN1_DISABLE                 ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_EMBIN2_Selection EMB Port EMB IN2 Selection
 * @{
 */
#define EMB_PORT_EMBIN2_ENABLE                  (EMB_CTL0_PORTINEN1)
#define EMB_PORT_EMBIN2_DISABLE                 ((uint32_t)0UL)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_EMBIN3_Selection EMB Port EMB IN3 Selection
 * @{
 */
#define EMB_PORT_EMBIN3_ENABLE                  (EMB_CTL0_PORTINEN2)
#define EMB_PORT_EMBIN3_DISABLE                 ((uint32_t)0UL)
/**
 * @}
 */

/** @defgroup EMB_Port_EMBIN1_Filter_Clock_Division EMB Port EMBIN1 Filter Clock Division
 * @{
 */
#define EMB_PORT_EMBIN1_FILTER_NONE             ((uint32_t)0UL)                         /*!< Disable filter */
#define EMB_PORT_EMBIN1_FILTER_CLK_DIV1         (EMB_CTL0_NFEN0)                        /*!< PCLK           */
#define EMB_PORT_EMBIN1_FILTER_CLK_DIV8         (EMB_CTL0_NFEN0 | EMB_CTL0_NFSEL0_0)    /*!< PCLK/8         */
#define EMB_PORT_EMBIN1_FILTER_CLK_DIV32        (EMB_CTL0_NFEN0 | EMB_CTL0_NFSEL0_1)    /*!< PCLK/32        */
#define EMB_PORT_EMBIN1_FILTER_CLK_DIV128       (EMB_CTL0_NFEN0 | EMB_CTL0_NFSEL0)      /*!< PCLK/128       */
/**
 * @}
 */

/** @defgroup EMB_Port_EMBIN2_Filter_Clock_Division EMB Port EMBIN2 Filter Clock Division
 * @{
 */
#define EMB_PORT_EMBIN2_FILTER_NONE             ((uint32_t)0UL)                         /*!< Disable filter */
#define EMB_PORT_EMBIN2_FILTER_CLK_DIV1         (EMB_CTL0_NFEN1)                        /*!< PCLK           */
#define EMB_PORT_EMBIN2_FILTER_CLK_DIV8         (EMB_CTL0_NFEN1 | EMB_CTL0_NFSEL1_0)    /*!< PCLK/8         */
#define EMB_PORT_EMBIN2_FILTER_CLK_DIV32        (EMB_CTL0_NFEN1 | EMB_CTL0_NFSEL1_1)    /*!< PCLK/32        */
#define EMB_PORT_EMBIN2_FILTER_CLK_DIV128       (EMB_CTL0_NFEN1 | EMB_CTL0_NFSEL1)      /*!< PCLK/128       */
/**
 * @}
 */

/** @defgroup EMB_Port_EMBIN3_Filter_Clock_Division EMB Port EMBIN3 Filter Clock Division
 * @{
 */
#define EMB_PORT_EMBIN3_FILTER_NONE             ((uint32_t)0UL)                         /*!< Disable filter */
#define EMB_PORT_EMBIN3_FILTER_CLK_DIV1         (EMB_CTL0_NFEN2)                        /*!< PCLK           */
#define EMB_PORT_EMBIN3_FILTER_CLK_DIV8         (EMB_CTL0_NFEN2 | EMB_CTL0_NFSEL2_0)    /*!< PCLK/8         */
#define EMB_PORT_EMBIN3_FILTER_CLK_DIV32        (EMB_CTL0_NFEN2 | EMB_CTL0_NFSEL2_1)    /*!< PCLK/32        */
#define EMB_PORT_EMBIN3_FILTER_CLK_DIV128       (EMB_CTL0_NFEN2 | EMB_CTL0_NFSEL2)      /*!< PCLK/128       */
/**
 * @}
 */

/**
 * @defgroup EMB_Port_EMBIN1_Level EMB Port EMBIN1 Level
 * @{
 */
#define EMB_PORT_EMBIN1_LEVEL_HIGH              ((uint32_t)0UL)
#define EMB_PORT_EMBIN1_LEVEL_LOW               (EMB_CTL0_INVSEL0)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_EMBIN2_Level EMB Port EMBIN2 Level
 * @{
 */
#define EMB_PORT_EMBIN2_LEVEL_HIGH              ((uint32_t)0UL)
#define EMB_PORT_EMBIN2_LEVEL_LOW               (EMB_CTL0_INVSEL1)
/**
 * @}
 */

/**
 * @defgroup EMB_Port_EMBIN3_Level EMB Port EMBIN3 Level
 * @{
 */
#define EMB_PORT_EMBIN3_LEVEL_HIGH              ((uint32_t)0UL)
#define EMB_PORT_EMBIN3_LEVEL_LOW               (EMB_CTL0_INVSEL2)
/**
 * @}
 */

/**
 * @defgroup EMB_Group0_Detect_Timer4_PWMU_Level EMB Group0 Detect Timer4 PWMU Level
 * @{
 */
#define EMB_DETECT_TIMER4_PWMU_LEVEL_LOW        ((uint32_t)0UL)
#define EMB_DETECT_TIMER4_PWMU_LEVEL_HIGH       (EMB_PWMLV0_PWMLV_2)
/**
 * @}
 */

/**
 * @defgroup EMB_Group0_Detect_Timer4_PWMV_Level EMB Group0 Detect Timer4 PWMV Level
 * @{
 */
#define EMB_DETECT_TIMER4_PWMV_LEVEL_LOW        ((uint32_t)0UL)
#define EMB_DETECT_TIMER4_PWMV_LEVEL_HIGH       (EMB_PWMLV0_PWMLV_1)
/**
 * @}
 */

/**
 * @defgroup EMB_Group0_Detect_Timer4_PWMW_Level EMB Group0 Detect Timer4 PWMW Level
 * @{
 */
#define EMB_DETECT_TIMER4_PWMW_LEVEL_LOW        ((uint32_t)0UL)
#define EMB_DETECT_TIMER4_PWMW_LEVEL_HIGH       (EMB_PWMLV0_PWMLV_0)
/**
 * @}
 */

/**
 * @defgroup EMB_Group1_Timerb_PWM_Output_State EMB Group1 Timerb PWM Output State
 * @{
 */
#define EMB_SET_TMRB_PWM_OUTPUT_NORMAL          ((uint32_t)0UL)     /*!< TIMB_1_PWMn(n=1~4) output normal */
#define EMB_SET_TMRB_PWM_OUTPUT_HIZ             (TMR4_PSCR_OSUH_0)  /*!< TIMB_1_PWMn(n=1~4) output Hi-z */
#define EMB_SET_TMRB_PWM_OUTPUT_LOW             (TMR4_PSCR_OSUH_1)  /*!< TIMB_1_PWMn(n=1~4) output low level */
#define EMB_SET_TMRB_PWM_OUTPUT_HIGH            (TMR4_PSCR_OSUH)    /*!< TIMB_1_PWMn(n=1~4) output high level */
/**
 * @}
 */

/**
 * @defgroup EMB_Flag EMB Flag
 * @{
 */
#define EMB_FLAG_PWM                            (EMB_STAT0_PWMSF)
#define EMB_FLAG_CMP                            (EMB_STAT0_CMPF)
#define EMB_FLAG_OSC                            (EMB_STAT0_OSF)
#define EMB_FLAG_PORT_EMBIN1                    (EMB_STAT0_PORTINF0)
#define EMB_FLAG_PORT_EMBIN2                    (EMB_STAT0_PORTINF1)
#define EMB_FLAG_PORT_EMBIN3                    (EMB_STAT0_PORTINF2)
#define EMB_FLAG_PWM_STATE                      (EMB_STAT0_PWMST)
#define EMB_FLAG_PORT_EMBIN1_STATE              (EMB_STAT0_PORTINST0)
#define EMB_FLAG_PORT_EMBIN2_STATE              (EMB_STAT0_PORTINST1)
#define EMB_FLAG_PORT_EMBIN3_STATE              (EMB_STAT0_PORTINST2)
/**
 * @}
 */

/**
 * @defgroup EMB_Interrupt EMB Interrupt
 * @{
 */
#define EMB_INT_PWM                             (EMB_INTEN0_PWMINTEN)
#define EMB_INT_CMP                             (EMB_INTEN0_CMPINTEN)
#define EMB_INT_OSC                             (EMB_INTEN0_OSINTEN)
#define EMB_INT_PORT_EMBIN1                     (EMB_INTEN0_PORTININTEN0)
#define EMB_INT_PORT_EMBIN2                     (EMB_INTEN0_PORTININTEN1)
#define EMB_INT_PORT_EMBIN3                     (EMB_INTEN0_PORTININTEN2)
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
en_result_t EMB_Group0Timer4Init(const stc_emb_group0_timer4_init_t *pstcInit);
en_result_t EMB_Group0Timer4StructInit(stc_emb_group0_timer4_init_t *pstcInit);
en_result_t EMB_Group1TimerbInit(const stc_emb_group1_timerb_init_t *pstcInit);
en_result_t EMB_Group1TimerbStructInit(stc_emb_group1_timerb_init_t *pstcInit);
en_result_t EMB_DeInit(uint32_t u32Group);
void EMB_SetDetectTimer4PwmLevel(stc_emb_timer4_pwm_level_t stcPwmLevel);
void EMB_SetTimerbOutputState(uint32_t u32OutputState);
void EMB_IntCmd(uint32_t u32Group,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewSta);
en_flag_status_t EMB_GetStatus(uint32_t u32Group, uint32_t u32Status);
void EMB_ClearStatus(uint32_t u32Group, uint32_t u32Status);
void EMB_SwBrake(uint32_t u32Group, en_functional_state_t enNewSta);
/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_EMB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
