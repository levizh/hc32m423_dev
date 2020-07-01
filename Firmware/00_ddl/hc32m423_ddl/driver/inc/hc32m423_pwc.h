/**
 *******************************************************************************
 * @file  hc32m423_pwc.h
 * @brief This file contains all the functions prototypes of the PWC driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-07-09       Chengy          First version
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
#ifndef __HC32M423_PWC_H__
#define __HC32M423_PWC_H__

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
 * @addtogroup DDL_PWC
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Types PWC Global Types
 * @{
 */

/**
 * @brief PWC stop mode config
 */
typedef struct
{
    uint8_t             u8HPorSel;      /*!< Specifies the high POR(power on reset) on or off while stop mode.      */
    uint8_t             u8HrcSel;       /*!< Specifies the system clock while awake from stop mode.                 */
} stc_pwc_stop_mode_t;

/**
 * @brief PWC LVD initialization structure definition
 */
typedef struct
{
    uint32_t u32ExInputEn;              /*!< Specifies the validity of the PWC LVD external input (Only for LVD2).
                                             This parameter can be a value of @ref PWC_LVD_External_Input */
    uint32_t u32DetectEdge;             /*!< Specifies the PWC LVD detect VCC across the edge of LVD.
                                             This parameter can be a value of @ref PWC_LVD_Detect_Edge */
    uint32_t u32VoltageThreshold;       /*!< Specifies the PWC LVD detect voltage threshole.
                                             This parameter can be a value of @ref PWC_LVD_Voltage_Threshold */
    uint32_t u32Filter;                 /*!< Specifies the PWC LVD filter.
                                             This parameter can be a value of @ref PWC_LVD_Filter */
    uint32_t u32TrigEvent;              /*!< Specifies the PWC LVD trigger event.
                                             This parameter can be a value of @ref PWC_LVD_Trigger_Event */
    uint32_t u32ComparerOutputEn;       /*!< Specifies the validity of the PWC LVD comparer output.
                                             This parameter can be a value of @ref PWC_LVD_Comparer_Output */
} stc_pwc_lvd_init_t;


/**
 * @brief PWC LVD Unit
 */
typedef enum
{
    PWC_LVD0 = 0x04U,                   /*!< PWC LVD unit 0 (LVD0) */
    PWC_LVD1 = 0x00U,                   /*!< PWC LVD unit 1 (LVD1) */
    PWC_LVD2 = 0x01U,                   /*!< PWC LVD unit 2 (LVD2) */
} en_pwc_lvd_unit_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Global_Macros PWC Global Macros
 * @{
 */

/**
 * @defgroup PWC_HPOR_Config PWC High POR(power on reset) Config
 * @{
 */
#define PWC_HPOR_ON                 (0x00U)                   /*!< High POR is valid while in stop mode   */
#define PWC_HPOR_OFF                (PWC_STPMCR_HAPORDIS)     /*!< High POR is invalid while in stop mode */
/**
 * @}
 */

/**
 * @defgroup PWC_CKSHRC_Config PWC Clock Config
 * @{
 */
#define PWC_SYSCLK_FIX              (0x00U)               /*!< System clock is fixed after stop mode awake              */
#define PWC_SYSCLK_HRCDIVX          (PWC_STPMCR_CKSHRC)   /*!< System clock is n divided of HRC after stop mode awake */
/**
 * @}
 */

/**
 * @defgroup PWC_DRV_Selection PWC Driver ability selection
 * @{
 */
#define PWC_DRV_LOW                 (0x00U)       /*!< system clock = 32kHz */
#define PWC_DRV_HIGH                (0x07U)       /*!< system clock < 48Mhz */
/**
 * @}
 */


/**
 * @defgroup PWC_LDO_Flag PWC LDO Flag
 * @{
 */
#define PWC_FLAG_LDO_PLL                        (PWR_PWRC_PLLPWRDY)   /*!< PLL LDO ready flag */
#define PWC_FLAG_LDO_HRC                        (PWR_PWRC_HRCPWRDY)   /*!< HRC LDO ready flag */
/**
 * @}
 */

/**
 * @defgroup PWC_Power_Monitor PWC Power Monitor
 * @{
 */
#define PWC_POWER_MONITOR_DISABLE               ((uint8_t)0x00U)                                        /*!< Disable power monitor */
#define PWC_POWER_MONITOR_INTERNAL_REF_VOL      (PWR_PWRMONR_PWMONE)                                    /*!< Monitor internal reference voltage of power supply */
#define PWC_POWER_MONITOR_TEMP_SENSOR_VOL       ((uint8_t)(PWR_PWRMONR_PWMONE | PWR_PWRMONR_PWMONSEL))  /*!< Monitor temperature sensor voltage */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_External_Input PWC LVD External Input
 * @{
 */
#define PWC_LVD_EX_INPUT_DISABLE                ((uint32_t)0x00000000UL)
#define PWC_LVD_EX_INPUT_ENABLE                 (PWR_LVDCR0_EXVCCINEN)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Detect_Edge PWC LVD Detect Edge
 * @{
 */
#define PWC_LVD_DETECT_EDGE_RISING              ((uint32_t)0x00000000UL)     /*!< Detect VCC rising passing through LVD */
#define PWC_LVD_DETECT_EDGE_FALLING             (PWR_LVDCR0_L1IEGS_0)       /*!< Detect VCC falling passing through LVD */
#define PWC_LVD_DETECT_EDGE_RISING_FALLING      (PWR_LVDCR0_L1IEGS_1)       /*!< Detect VCC rising or falling passing through LVD */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Voltage_Threshold PWC LVD Voltage Threshold
 * @note The parameter PWC_LVD_VOL_EX_INPUT only LVD2 is valid
 * @{
 */
#define PWC_LVD_VOL_BELOW4P29_OR_ABOVE4P39      ((uint32_t)0x00000000UL)                                                         /*!< LVD voltage threshold less than 4.29 or higher than 4.39 */
#define PWC_LVD_VOL_BELOW4P14_OR_ABOVE4P23      (PWR_LVDCR0_L1LVL_0)                                                            /*!< LVD voltage threshold less than 4.14 or higher than 4.23 */
#define PWC_LVD_VOL_BELOW4P02_OR_ABOVE4P14      (PWR_LVDCR0_L1LVL_1)                                                            /*!< LVD voltage threshold less than 4.02 or higher than 4.14 */
#define PWC_LVD_VOL_BELOW3P84_OR_ABOVE3P96      ((uint32_t)(PWR_LVDCR0_L1LVL_1 | PWR_LVDCR0_L1LVL_0))                            /*!< LVD voltage threshold less than 3.84 or higher than 3.96 */
#define PWC_LVD_VOL_BELOW3P10_OR_ABOVE3P20      (PWR_LVDCR0_L1LVL_2)                                                            /*!< LVD voltage threshold less than 3.10 or higher than 3.20 */
#define PWC_LVD_VOL_BELOW3P00_OR_ABOVE3P09      ((uint32_t)(PWR_LVDCR0_L1LVL_2 | PWR_LVDCR0_L1LVL_0))                            /*!< LVD voltage threshold less than 3.00 or higher than 3.09 */
#define PWC_LVD_VOL_BELOW2P90_OR_ABOVE2P99      ((uint32_t)(PWR_LVDCR0_L1LVL_2 | PWR_LVDCR0_L1LVL_1))                            /*!< LVD voltage threshold less than 2.90 or higher than 2.99 */
#define PWC_LVD_VOL_BELOW2P79_OR_ABOVE2P87      ((uint32_t)(PWR_LVDCR0_L1LVL_2 | PWR_LVDCR0_L1LVL_1 | PWR_LVDCR0_L1LVL_0))       /*!< LVD voltage threshold less than 2.79 or higher than 2.87 */
#define PWC_LVD_VOL_BELOW2P68_OR_ABOVE2P75      (PWR_LVDCR0_L1LVL_3)                                                            /*!< LVD voltage threshold less than 2.68 or higher than 2.75 */
#define PWC_LVD_VOL_BELOW2P34_OR_ABOVE2P41      ((uint32_t)(PWR_LVDCR0_L1LVL_3 | PWR_LVDCR0_L1LVL_0))                            /*!< LVD voltage threshold less than 2.34 or higher than 2.41 */
#define PWC_LVD_VOL_BELOW2P14_OR_ABOVE2P21      ((uint32_t)(PWR_LVDCR0_L1LVL_3 | PWR_LVDCR0_L1LVL_1))                            /*!< LVD voltage threshold less than 2.14 or higher than 2.21 */
#define PWC_LVD_VOL_BELOW1P94_OR_ABOVE2P01      ((uint32_t)(PWR_LVDCR0_L1LVL_3 | PWR_LVDCR0_L1LVL_1 | PWR_LVDCR0_L1LVL_0))       /*!< LVD voltage threshold less than 1.94 or higher than 2.01 */
#define PWC_LVD_VOL_BELOW1P84_OR_ABOVE1P90      ((uint32_t)(PWR_LVDCR0_L1LVL_3 | PWR_LVDCR0_L1LVL_2))                            /*!< LVD voltage threshold less than 1.84 or higher than 1.90 */
#define PWC_LVD_VOL_EX_INPUT                    ((uint32_t)(PWR_LVDCR0_L1LVL_3 | PWR_LVDCR0_L1LVL_2 | PWR_LVDCR0_L1LVL_1))       /*!< LVD use external input reference voltage */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Filter PWC LVD Filter
 * @{
 */
#define PWC_LVD_FILTER_DISABLE                  (PWR_LVDCR0_L1NFDIS)        /*!< Disable filter */
#define PWC_LVD_FILTER_CLK_LRC_0P25             ((uint32_t)0x00000000UL)     /*!< 0.25 LRC cycle */
#define PWC_LVD_FILTER_CLK_LRC_0P5              (PWR_LVDCR0_L1NFS_0)        /*!< 0.5 LRC cycle  */
#define PWC_LVD_FILTER_CLK_LRC_DIV1             (PWR_LVDCR0_L1NFS_1)        /*!< LRC division 1 */
#define PWC_LVD_FILTER_CLK_LRC_DIV2             (PWR_LVDCR0_L1NFS)          /*!< LRC division 2 */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Trigger_Event PWC LVD Trigger Event
 * @{
 */
#define PWC_LVD_TRIG_DISABLE                    ((uint32_t)0x00000000UL)                             /*!< Disable trigger event */
#define PWC_LVD_TRIG_RESET                      ((uint32_t)(PWR_LVDCR0_L1IRE | PWR_LVDCR0_L1IRS))    /*!< An LVD reset occurs when passing through LVD On the way down */
#define PWC_LVD_TRIG_NMI_INTERRUPT              ((uint32_t)(PWR_LVDCR0_L1IRE | PWR_LVDCR0_L1NMIS))   /*!< An LVD NMI interrupt occurs when passing through LVD */
#define PWC_LVD_TRIG_MI_INTERRUPT               ((uint32_t)PWR_LVDCR0_L1IRE)                         /*!< An LVD maskable interrupt occurs when passing through LVD */
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Comparer_Output PWC LVD Comparer Output
 * @{
 */
#define PWC_LVD_COMPARER_OUTPUT_DISABLE         ((uint32_t)0x00000000UL)
#define PWC_LVD_COMPARER_OUTPUT_ENABLE          (PWR_LVDCR0_L1CMPOE)
/**
 * @}
 */

/**
 * @defgroup PWC_LVD_Compare_Result PWC LVD Compare Result
 * @{
 */
#define PWC_LVD_COMPARE_VCC_LESS_LVD            ((uint8_t)0x00U)            /*!< VCC < VLVD */
#define PWC_LVD_COMPARE_VCC_GREATER_LVD         (PWR_LVDCSR1_L1MON)         /*!< VCC = VLVD or LVD is invalid */
/**
 * @}
 */

/**
 * @defgroup PWC_Ram_Parity_Flag PWC Ram Parity Flag
 * @{
 */
#define PWC_FLAG_CACHE_PARITY_ERR               (PWR_RAMCR_CRPEF)       /*!< Cache Ram parity error flag */
#define PWC_FLAG_HRAM_PARITY_ERR                (PWR_RAMCR_HRPEF)       /*!< High RAM parity error flag  */
#define PWC_FLAG_RAM_PARITY_ERR                 (PWR_RAMCR_SRPEF)       /*!< RAM parity error flag       */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup PWC_Write_Protect_Configuration PWC Write Protect Configuration
 * @{
 */
#define PWC_CLK_REG_WRITE_DISABLE()             (WRITE_REG16(M4_PWR->FPRC, 0xA500U))
#define PWC_CLK_REG_WRITE_ENABLE()              (WRITE_REG16(M4_PWR->FPRC, 0xA501U))

#define PWC_POWER_REG_WRITE_DISABLE()           (WRITE_REG16(M4_PWR->FPRC, 0xA500U))
#define PWC_POWER_REG_WRITE_ENABLE()            (WRITE_REG16(M4_PWR->FPRC, 0xA502U))

#define PWC_LVD_REG_WRITE_DISABLE()             (WRITE_REG16(M4_PWR->FPRC, 0xA500U))
#define PWC_LVD_REG_WRITE_ENABLE()              (WRITE_REG16(M4_PWR->FPRC, 0xA508U))
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
 * @addtogroup PWC_Global_Functions
 * @{
 */
void PWC_EnterStopMode(void);
void PWC_EnterSleepMode(void);

void PWC_HighSpeedToLowSpeed(void);
void PWC_LowSpeedToHighSpeed(void);

en_result_t PWC_StopStructInit(stc_pwc_stop_mode_t* pstcStopCfg);
en_result_t PWC_StopMdConfig(const stc_pwc_stop_mode_t* pstcStopCfg);


en_flag_status_t PWC_GetLdoFlag(uint16_t u16Flag);
void PWC_SetPowerMonitor(uint8_t u8CfgVal);

en_result_t PWC_LVD_DeInit(uint8_t u8Unit);
en_result_t PWC_LVD_Init(uint8_t u8Unit, const stc_pwc_lvd_init_t* pstcLvdInit);
en_result_t PWC_LVD_StructInit(stc_pwc_lvd_init_t* pstcLvdInit);
void PWC_LVD_Cmd(uint8_t u8Unit, en_functional_state_t enNewState);
void PWC_LVD_CmpOutputCmd(uint8_t u8Unit, en_functional_state_t enNewState);
void PWC_LVD_TrigEventCmd(uint8_t u8Unit, en_functional_state_t enNewState);
en_result_t PWC_LVD_SetVolThreshold(uint8_t u8Unit, uint32_t u32VolThreshold);
uint8_t PWC_LVD_GetCmpResult(uint8_t u8Unit);
en_flag_status_t PWC_LVD_GetDetectFlag(uint8_t u8Unit);
void PWC_LVD_CleaDetectFlag(uint8_t u8Unit);

void PWC_RamParityErrResetCmd(en_functional_state_t enNewState);
en_flag_status_t PWC_GetRamParityFlag(uint8_t u8Flag);
void PWC_ClearRamParityFlag(uint8_t u8Flag);

void PWC_DebugCmd(en_functional_state_t enNewState);
/**
 * @}
 */

#endif /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_PWC_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
