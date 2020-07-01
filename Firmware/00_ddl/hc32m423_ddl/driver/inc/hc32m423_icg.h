/**
 *******************************************************************************
 * @file    hc32m423_icg.h
 * @brief   This file contains all the Macro Definitions of the ICG driver
 *          library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-03       Yangjp          First version
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
#ifndef __HC32M423_ICG_H__
#define __HC32M423_ICG_H__

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
 * @addtogroup DDL_ICG
 * @{
 */

#if (DDL_ICG_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup ICG_Global_Macros ICG Global Macros
 * @{
 */

/**
 * @defgroup ICG_SWDT_Running_State ICG SWDT Running State
 * @{
 */
#define ICG_SWDT_AFTER_RESET_AUTOSTART          ((uint32_t)0x00000000UL)        /*!< SWDT Auto Start after reset */
#define ICG_SWDT_AFTER_RESET_STOP               ((uint32_t)ICG_ICG0_SWDTAUTST)  /*!< SWDT stop after reset */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Trigger_Event_Type ICG SWDT Trigger Event Type
 * @{
 */
#define ICG_SWDT_TRIG_EVENT_INT                 ((uint32_t)0x00000000UL)      /*!< SWDT trigger interrupt */
#define ICG_SWDT_TRIG_EVENT_RESET               ((uint32_t)ICG_ICG0_SWDTITS)  /*!< SWDT trigger reset */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Counter_Cycle ICG SWDT Counter Cycle
 * @{
 */
#define ICG_SWDT_COUNTER_CYCLE_256              ((uint32_t)0x00000000UL)         /*!< 256 clock cycle */
#define ICG_SWDT_COUNTER_CYCLE_4096             ((uint32_t)ICG_ICG0_SWDTPERI_0)  /*!< 4096 clock cycle */
#define ICG_SWDT_COUNTER_CYCLE_16384            ((uint32_t)ICG_ICG0_SWDTPERI_1)  /*!< 16384 clock cycle */
#define ICG_SWDT_COUNTER_CYCLE_65536            ((uint32_t)ICG_ICG0_SWDTPERI)    /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Clock_Division ICG SWDT Clock Division
 * @{
 */
#define ICG_SWDT_CLOCK_DIV1                     ((uint32_t)0x00000000UL)                                                    /*!< SWDTCLK */
#define ICG_SWDT_CLOCK_DIV16                    ((uint32_t)ICG_ICG0_SWDTCKS_2)                                              /*!< SWDTCLK/16 */
#define ICG_SWDT_CLOCK_DIV32                    ((uint32_t)(ICG_ICG0_SWDTCKS_0 | ICG_ICG0_SWDTCKS_2))                       /*!< SWDTCLK/32 */
#define ICG_SWDT_CLOCK_DIV64                    ((uint32_t)(ICG_ICG0_SWDTCKS_1 | ICG_ICG0_SWDTCKS_2))                       /*!< SWDTCLK/64 */
#define ICG_SWDT_CLOCK_DIV128                   ((uint32_t)(ICG_ICG0_SWDTCKS_0 | ICG_ICG0_SWDTCKS_1 | ICG_ICG0_SWDTCKS_2))  /*!< SWDTCLK/128 */
#define ICG_SWDT_CLOCK_DIV256                   ((uint32_t)ICG_ICG0_SWDTCKS_3)                                              /*!< SWDTCLK/256 */
#define ICG_SWDT_CLOCK_DIV2048                  ((uint32_t)(ICG_ICG0_SWDTCKS_0 | ICG_ICG0_SWDTCKS_1 | ICG_ICG0_SWDTCKS_3))  /*!< SWDTCLK/2048 */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_Refresh_Percent_Range ICG SWDT Refresh Percent Range
 * @{
 */
#define ICG_SWDT_RANGE_100PCT                   ((uint32_t)0x00000000UL)                                                        /*!< 100% */
#define ICG_SWDT_RANGE_0TO25PCT                 ((uint32_t)ICG_ICG0_SWDTWDPT_0)                                                 /*!< 0%~25% */
#define ICG_SWDT_RANGE_25TO50PCT                ((uint32_t)ICG_ICG0_SWDTWDPT_1)                                                 /*!< 25%~50% */
#define ICG_SWDT_RANGE_0TO50PCT                 ((uint32_t)(ICG_ICG0_SWDTWDPT_0 | ICG_ICG0_SWDTWDPT_1))                         /*!< 0%~50% */
#define ICG_SWDT_RANGE_50TO75PCT                ((uint32_t)ICG_ICG0_SWDTWDPT_2)                                                 /*!< 50%~75% */
#define ICG_SWDT_RANGE_0TO25PCT_50TO75PCT       ((uint32_t)(ICG_ICG0_SWDTWDPT_0 | ICG_ICG0_SWDTWDPT_2))                         /*!< 0%~25% & 50%~75% */
#define ICG_SWDT_RANGE_25TO75PCT                ((uint32_t)(ICG_ICG0_SWDTWDPT_1 | ICG_ICG0_SWDTWDPT_2))                         /*!< 25%~75% */
#define ICG_SWDT_RANGE_0TO75PCT                 ((uint32_t)(ICG_ICG0_SWDTWDPT_0 | ICG_ICG0_SWDTWDPT_1 | ICG_ICG0_SWDTWDPT_2))   /*!< 0%~75% */
#define ICG_SWDT_RANGE_75TO100PCT               ((uint32_t)ICG_ICG0_SWDTWDPT_3)                                                 /*!< 75%~100% */
#define ICG_SWDT_RANGE_0TO25PCT_75TO100PCT      ((uint32_t)(ICG_ICG0_SWDTWDPT_0 | ICG_ICG0_SWDTWDPT_3))                         /*!< 0%~25% & 75%~100% */
#define ICG_SWDT_RANGE_25TO50PCT_75TO100PCT     ((uint32_t)(ICG_ICG0_SWDTWDPT_1 | ICG_ICG0_SWDTWDPT_3))                         /*!< 25%~50% & 75%~100% */
#define ICG_SWDT_RANGE_0TO50PCT_75TO100PCT      ((uint32_t)(ICG_ICG0_SWDTWDPT_0 | ICG_ICG0_SWDTWDPT_1 | ICG_ICG0_SWDTWDPT_3))   /*!< 0%~50% & 75%~100% */
#define ICG_SWDT_RANGE_50TO100PCT               ((uint32_t)(ICG_ICG0_SWDTWDPT_2 | ICG_ICG0_SWDTWDPT_3))                         /*!< 50%~100% */
#define ICG_SWDT_RANGE_0TO25PCT_50TO100PCT      ((uint32_t)(ICG_ICG0_SWDTWDPT_0 | ICG_ICG0_SWDTWDPT_2 | ICG_ICG0_SWDTWDPT_3))   /*!< 0%~25% & 50%~100% */
#define ICG_SWDT_RANGE_25TO100PCT               ((uint32_t)(ICG_ICG0_SWDTWDPT_1 | ICG_ICG0_SWDTWDPT_2 | ICG_ICG0_SWDTWDPT_3))   /*!< 25%~100% */
#define ICG_SWDT_RANGE_0TO100PCT                ((uint32_t)ICG_ICG0_SWDTWDPT)                                                   /*!< 0%~100% */
/**
 * @}
 */

/**
 * @defgroup ICG_SWDT_LPW_Mode_Count ICG SWDT Low Power Mode Count
 * @brief SWDT count control in the sleep/stop mode
 * @{
 */
#define ICG_SWDT_LPW_MODE_COUNT_CONTINUE        ((uint32_t)0x00000000UL)         /*!< SWDT count continue in the sleep/stop mode */
#define ICG_SWDT_LPW_MODE_COUNT_STOP            ((uint32_t)ICG_ICG0_SWDTSLPOFF)  /*!< SWDT count stop in the sleep/stop mode */
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Frequency_Select ICG HRC Frequency Select
 * @{
 */

#define ICG_HRC_FREQ_1P5MHZ                     ((uint32_t)(ICG_ICG0_HRCREQS_0 | ICG_ICG0_HRCREQS_2 | ICG_ICG0_HRCREQS_3))  /*!< HRC frequency 1.5MHZ */
#define ICG_HRC_FREQ_2MHZ                       ((uint32_t)(ICG_ICG0_HRCREQS_0 | ICG_ICG0_HRCREQS_2))                       /*!< HRC frequency 2MHZ */
#define ICG_HRC_FREQ_3MHZ                       ((uint32_t)(ICG_ICG0_HRCREQS_2 | ICG_ICG0_HRCREQS_3))                       /*!< HRC frequency 3MHZ */
#define ICG_HRC_FREQ_4MHZ                       ((uint32_t)ICG_ICG0_HRCREQS_2)                                              /*!< HRC frequency 4MHZ */
#define ICG_HRC_FREQ_6MHZ                       ((uint32_t)(ICG_ICG0_HRCREQS_0 | ICG_ICG0_HRCREQS_1 | ICG_ICG0_HRCREQS_3))  /*!< HRC frequency 6MHZ */
#define ICG_HRC_FREQ_8MHZ                       ((uint32_t)(ICG_ICG0_HRCREQS_0 | ICG_ICG0_HRCREQS_1))                       /*!< HRC frequency 8MHZ */
#define ICG_HRC_FREQ_12MHZ                      ((uint32_t)(ICG_ICG0_HRCREQS_1 | ICG_ICG0_HRCREQS_3))                       /*!< HRC frequency 12MHZ */
#define ICG_HRC_FREQ_16MHZ                      ((uint32_t)ICG_ICG0_HRCREQS_1)                                              /*!< HRC frequency 16MHZ */
#define ICG_HRC_FREQ_24MHZ                      ((uint32_t)(ICG_ICG0_HRCREQS_0 | ICG_ICG0_HRCREQS_3))                       /*!< HRC frequency 24MHZ */
#define ICG_HRC_FREQ_32MHZ                      ((uint32_t)ICG_ICG0_HRCREQS_0)                                              /*!< HRC frequency 32MHZ */
#define ICG_HRC_FREQ_48MHZ                      ((uint32_t)ICG_ICG0_HRCREQS_3)                                              /*!< HRC frequency 48MHZ */
#define ICG_HRC_FREQ_64MHZ                      ((uint32_t)0x00000000UL)                                                    /*!< HRC frequency 64MHZ */
/**
 * @}
 */

/**
 * @defgroup ICG_HRC_Switch ICG HRC Switch
 * @brief Enable or disable HRC function
 * @{
 */
#define ICG_HRC_ENABLE                          ((uint32_t)0x00000000UL)      /*!< Enable HRC */
#define ICG_HRC_DISABLE                         ((uint32_t)ICG_ICG0_HRCSTOP)  /*!< Disable HRC */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Filter_Clock_Division ICG NMI Pin Filter Clock Division
 * @{
 */
#define ICG_NMI_PIN_FILTER_CLOCK_DIV1           ((uint32_t)0x00000000UL)        /*!< HCLK */
#define ICG_NMI_PIN_FILTER_CLOCK_DIV8           ((uint32_t)ICG_ICG0_NMIFCLK_0)  /*!< HCLK/8 */
#define ICG_NMI_PIN_FILTER_CLOCK_DIV32          ((uint32_t)ICG_ICG0_NMIFCLK_1)  /*!< HCLK/32 */
#define ICG_NMI_PIN_FILTER_CLOCK_DIV64          ((uint32_t)ICG_ICG0_NMIFCLK)    /*!< HCLK/64 */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Digital_Filter_Switch ICG NMI Digital Filter Switch
 * @brief Enable or disable NMI digital filter
 * @{
 */
#define ICG_NMI_PIN_DIGITAL_FILTER_DISABLE      ((uint32_t)0x00000000UL)     /*!< Disable NMI digital filter */
#define ICG_NMI_PIN_DIGITAL_FILTER_ENABLE       ((uint32_t)ICG_ICG0_NMIFEN)  /*!< Enable NMI digital filter */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_Trigger_Edge ICG NMI Pin Trigger Edge
 * @{
 */
#define ICG_NMI_PIN_TRIG_EDGE_FALLING           ((uint32_t)0x00000000UL)     /*!< Falling edge trigger */
#define ICG_NMI_PIN_TRIG_EDGE_RISING            ((uint32_t)ICG_ICG0_NMITRG)  /*!< Rising edge trigger */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_INT_Switch ICG NMI Pin Interrupt Switch
 * @brief Enable or disable NMI pin interrupt
 * @{
 */
#define ICG_NMI_PIN_INT_DISABLE                 ((uint32_t)0x00000000UL)    /*!< Disable NMI pin interrupt */
#define ICG_NMI_PIN_INT_ENABLE                  ((uint32_t)ICG_ICG0_NMIEN)  /*!< Enable NMI pin interrupt */
/**
 * @}
 */

/**
 * @defgroup ICG_NMI_Pin_ICG_Configure ICG NMI Pin ICG Configure
 * @brief Enable or disable NMI pin ICG configure
 * @{
 */
#define ICG_NMI_PIN_ICG_CONFIG_DISABLE          ((uint32_t)ICG_ICG0_NMIICGNE)   /*!< Disable NMI pin ICG configure */
#define ICG_NMI_PIN_ICG_CONFIG_ENABLE           ((uint32_t)0x00000000UL)        /*!< Enable NMI pin ICG configure */
/**
 * @}
 */

/**
 * @defgroup ICG_Lockup_Reset_Switch ICG Lockup Reset Switch
 * @brief Enable or disable core Lockup reset
 * @{
 */
#define ICG_LOCKUP_RESET_DISABLE                ((uint32_t)ICG_ICG1_LKUPDIS)    /*!< Disable core Lockup reset */
#define ICG_LOCKUP_RESET_ENABLE                 ((uint32_t)0x00000000UL)        /*!< Enable core Lockup reset */
/**
 * @}
 */

/**
 * @defgroup ICG_LVD_Voltage_Threshold ICG LVD Voltage Threshold
 * @{
 */
#define ICG_LVD_BELOW4P29_OR_ABOVE4P39          ((uint32_t)0x00000000UL)                                /*!< LVD voltage threshold less than 4.29 or higher than 4.39 */
#define ICG_LVD_BELOW3P84_OR_ABOVE3P96          ((uint32_t)ICG_ICG1_LVD0LVL_0)                          /*!< LVD voltage threshold less than 3.84 or higher than 3.96 */
#define ICG_LVD_BELOW2P82_OR_ABOVE2P90          ((uint32_t)ICG_ICG1_LVD0LVL_1)                          /*!< LVD voltage threshold less than 2.82 or higher than 2.90 */
#define ICG_LVD_BELOW2P51_OR_ABOVE2P59          ((uint32_t)(ICG_ICG1_LVD0LVL_0 | ICG_ICG1_LVD0LVL_1))   /*!< LVD voltage threshold less than 2.51 or higher than 2.59 */
#define ICG_LVD_BELOW2P34_OR_ABOVE2P41          ((uint32_t)ICG_ICG1_LVD0LVL_2)                          /*!< LVD voltage threshold less than 2.34 or higher than 2.41 */
#define ICG_LVD_BELOW2P14_OR_ABOVE2P21          ((uint32_t)(ICG_ICG1_LVD0LVL_0 | ICG_ICG1_LVD0LVL_2))   /*!< LVD voltage threshold less than 2.14 or higher than 2.21 */
#define ICG_LVD_BELOW1P94_OR_ABOVE2P01          ((uint32_t)(ICG_ICG1_LVD0LVL_1 | ICG_ICG1_LVD0LVL_2))   /*!< LVD voltage threshold less than 1.94 or higher than 2.01 */
#define ICG_LVD_BELOW1P84_OR_ABOVE1P90          ((uint32_t)ICG_ICG1_LVD0LVL)                            /*!< LVD voltage threshold less than 1.84 or higher than 1.90 */
/**
 * @}
 */

/**
 * @defgroup ICG_LVD_Voltage_Detection_Switch ICG LVD Voltage Detection Switch
 * @brief Enable or disable LVD0 circuitry detection
 * @{
 */
#define ICG_LVD_VOLTAGE_DETECTION_DISABLE       ((uint32_t)ICG_ICG1_LVDDIS)  /*!< Disable LVD0 circuitry detection */
#define ICG_LVD_VOLTAGE_DETECTION_ENABLE        ((uint32_t)0x00000000UL)     /*!< Enable LVD0 circuitry detection */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Running_State ICG WDT Running State
 * @{
 */
#define ICG_WDT_AFTER_RESET_AUTOSTART           ((uint32_t)0x00000000UL)       /*!< WDT Auto Start after reset */
#define ICG_WDT_AFTER_RESET_STOP                ((uint32_t)ICG_ICG7_WDTAUTST)  /*!< WDT stop after reset */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Trigger_Event_Type ICG WDT Trigger Event Type
 * @{
 */
#define ICG_WDT_TRIG_EVENT_INT                  ((uint32_t)0x00000000UL)     /*!< WDT trigger interrupt */
#define ICG_WDT_TRIG_EVENT_RESET                ((uint32_t)ICG_ICG7_WDTITS)  /*!< WDT trigger reset */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Counter_Cycle ICG WDT Counter Cycle
 * @{
 */
#define ICG_WDT_COUNTER_CYCLE_256               ((uint32_t)0x00000000UL)        /*!< 256 clock cycle */
#define ICG_WDT_COUNTER_CYCLE_4096              ((uint32_t)ICG_ICG7_WDTPERI_0)  /*!< 4096 clock cycle */
#define ICG_WDT_COUNTER_CYCLE_16384             ((uint32_t)ICG_ICG7_WDTPERI_1)  /*!< 16384 clock cycle */
#define ICG_WDT_COUNTER_CYCLE_65536             ((uint32_t)ICG_ICG7_WDTPERI)    /*!< 65536 clock cycle */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Clock_Division ICG WDT Clock Division
 * @{
 */
#define ICG_WDT_CLOCK_DIV4                      ((uint32_t)ICG_ICG7_WDTCKS_1)                                            /*!< PCLK1/4 */
#define ICG_WDT_CLOCK_DIV64                     ((uint32_t)(ICG_ICG7_WDTCKS_1 | ICG_ICG7_WDTCKS_2))                      /*!< PCLK1/64 */
#define ICG_WDT_CLOCK_DIV128                    ((uint32_t)(ICG_ICG7_WDTCKS_0 | ICG_ICG7_WDTCKS_1 | ICG_ICG7_WDTCKS_2))  /*!< PCLK1/128 */
#define ICG_WDT_CLOCK_DIV256                    ((uint32_t)ICG_ICG7_WDTCKS_3)                                            /*!< PCLK1/256 */
#define ICG_WDT_CLOCK_DIV512                    ((uint32_t)(ICG_ICG7_WDTCKS_0 | ICG_ICG7_WDTCKS_3))                      /*!< PCLK1/512 */
#define ICG_WDT_CLOCK_DIV1024                   ((uint32_t)(ICG_ICG7_WDTCKS_1 | ICG_ICG7_WDTCKS_3))                      /*!< PCLK1/1024 */
#define ICG_WDT_CLOCK_DIV2048                   ((uint32_t)(ICG_ICG7_WDTCKS_0 | ICG_ICG7_WDTCKS_1 | ICG_ICG7_WDTCKS_3))  /*!< PCLK1/2048 */
#define ICG_WDT_CLOCK_DIV8192                   ((uint32_t)(ICG_ICG7_WDTCKS_0 | ICG_ICG7_WDTCKS_2 | ICG_ICG7_WDTCKS_3))  /*!< PCLK1/8192 */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_Refresh_Percent_Range ICG WDT Refresh Percent Range
 * @{
 */
#define ICG_WDT_RANGE_100PCT                    ((uint32_t)0x00000000UL)                                                    /*!< 100% */
#define ICG_WDT_RANGE_0TO25PCT                  ((uint32_t)ICG_ICG7_WDTWDPT_0)                                              /*!< 0%~25% */
#define ICG_WDT_RANGE_25TO50PCT                 ((uint32_t)ICG_ICG7_WDTWDPT_1)                                              /*!< 25%~50% */
#define ICG_WDT_RANGE_0TO50PCT                  ((uint32_t)(ICG_ICG7_WDTWDPT_0 | ICG_ICG7_WDTWDPT_1))                       /*!< 0%~50% */
#define ICG_WDT_RANGE_50TO75PCT                 ((uint32_t)ICG_ICG7_WDTWDPT_2)                                              /*!< 50%~75% */
#define ICG_WDT_RANGE_0TO25PCT_50TO75PCT        ((uint32_t)(ICG_ICG7_WDTWDPT_0 | ICG_ICG7_WDTWDPT_2))                       /*!< 0%~25% & 50%~75% */
#define ICG_WDT_RANGE_25TO75PCT                 ((uint32_t)(ICG_ICG7_WDTWDPT_1 | ICG_ICG7_WDTWDPT_2))                       /*!< 25%~75% */
#define ICG_WDT_RANGE_0TO75PCT                  ((uint32_t)(ICG_ICG7_WDTWDPT_0 | ICG_ICG7_WDTWDPT_1 | ICG_ICG7_WDTWDPT_2))  /*!< 0%~75% */
#define ICG_WDT_RANGE_75TO100PCT                ((uint32_t)ICG_ICG7_WDTWDPT_3)                                              /*!< 75%~100% */
#define ICG_WDT_RANGE_0TO25PCT_75TO100PCT       ((uint32_t)(ICG_ICG7_WDTWDPT_0 | ICG_ICG7_WDTWDPT_3))                       /*!< 0%~25% & 75%~100% */
#define ICG_WDT_RANGE_25TO50PCT_75TO100PCT      ((uint32_t)(ICG_ICG7_WDTWDPT_1 | ICG_ICG7_WDTWDPT_3))                       /*!< 25%~50% & 75%~100% */
#define ICG_WDT_RANGE_0TO50PCT_75TO100PCT       ((uint32_t)(ICG_ICG7_WDTWDPT_0 | ICG_ICG7_WDTWDPT_1 | ICG_ICG7_WDTWDPT_3))  /*!< 0%~50% & 75%~100% */
#define ICG_WDT_RANGE_50TO100PCT                ((uint32_t)(ICG_ICG7_WDTWDPT_2 | ICG_ICG7_WDTWDPT_3))                       /*!< 50%~100% */
#define ICG_WDT_RANGE_0TO25PCT_50TO100PCT       ((uint32_t)(ICG_ICG7_WDTWDPT_0 | ICG_ICG7_WDTWDPT_2 | ICG_ICG7_WDTWDPT_3))  /*!< 0%~25% & 50%~100% */
#define ICG_WDT_RANGE_25TO100PCT                ((uint32_t)(ICG_ICG7_WDTWDPT_1 | ICG_ICG7_WDTWDPT_2 | ICG_ICG7_WDTWDPT_3))  /*!< 25%~100% */
#define ICG_WDT_RANGE_0TO100PCT                 ((uint32_t)ICG_ICG7_WDTWDPT)                                                /*!< 0%~100% */
/**
 * @}
 */

/**
 * @defgroup ICG_WDT_LPW_Mode_Count ICG WDT Low Power Mode Count
 * @brief WDT count control in the sleep mode
 * @{
 */
#define ICG_WDT_LPW_MODE_COUNT_CONTINUE         ((uint32_t)0x00000000UL)        /*!< WDT count continue in the sleep mode */
#define ICG_WDT_LPW_MODE_COUNT_STOP             ((uint32_t)ICG_ICG7_WDTSLPOFF)  /*!< WDT count stop in the sleep mode */
/**
 * @}
 */

/**
 * @defgroup ICG_Subfunction_Configure ICG Subfunction Configure
 * @brief On/Off ICG subfunction
 * @{
 */
#ifndef ICG_FUNCTION_ON
    #define ICG_FUNCTION_ON                     (1U)
#endif

#ifndef ICG_FUNCTION_OFF
    #define ICG_FUNCTION_OFF                    (0U)
#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_SWDT_Hardware_Start_Configuration SWDT Hardware Start Configuration
 * @{
 *******************************************************************************
 */
/* Enable or disable SWDT hardware start */
#define ICG0_SWDT_HARDWARE_START                (ICG_FUNCTION_OFF)

/* SWDT register config */
#define ICG0_SWDT_AUTST                         (ICG_SWDT_AFTER_RESET_AUTOSTART)
#define ICG0_SWDT_ITS                           (ICG_SWDT_TRIG_EVENT_INT)
#define ICG0_SWDT_PERI                          (ICG_SWDT_COUNTER_CYCLE_256)
#define ICG0_SWDT_CKS                           (ICG_SWDT_CLOCK_DIV64)
#define ICG0_SWDT_WDPT                          (ICG_SWDT_RANGE_100PCT)
#define ICG0_SWDT_SLTPOFF                       (ICG_SWDT_LPW_MODE_COUNT_CONTINUE)

/* SWDT register config value */
#if ICG0_SWDT_HARDWARE_START == ICG_FUNCTION_ON
    #define ICG0_SWDT_REG_CONFIG                (((uint32_t)ICG0_SWDT_AUTST | ICG0_SWDT_ITS | \
                                                            ICG0_SWDT_PERI  | ICG0_SWDT_CKS | \
                                                            ICG0_SWDT_WDPT  | ICG0_SWDT_SLTPOFF))
#else
    #define ICG0_SWDT_REG_CONFIG                ((uint32_t)0x0000FFFFUL)
#endif

/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_HRC_Hardware_Start_Configuration HRC Hardware Start Configuration
 * @{
 *******************************************************************************
 */
/* Enable or disable HRC hardware start */
#define ICG0_HRC_HARDWARE_START                 (ICG_FUNCTION_OFF)

/* HRC register config */
#define ICG0_HRC_FRQSEL                         (ICG_HRC_FREQ_8MHZ)
#define ICG0_HRC_STOP                           (ICG_HRC_ENABLE)

/* HRC register config value */
#if ICG0_HRC_HARDWARE_START == ICG_FUNCTION_ON
    #define ICG0_HRC_REG_CONFIG                 ((uint32_t)(ICG0_HRC_FRQSEL | ICG0_HRC_STOP))
#else
    #define ICG0_HRC_REG_CONFIG                 ((uint32_t)0x00FF0000UL)
#endif

/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_NMI_Hardware_Start_Configuration NMI Hardware Start Configuration
 * @{
 *******************************************************************************
 */
/* Enable or disable NMI hardware start */
#define ICG0_NMI_HARDWARE_START                 (ICG_FUNCTION_OFF)

/* NMI register config */
#define ICG0_NMI_FCLK                           (ICG_NMI_PIN_FILTER_CLOCK_DIV64)
#define ICG0_NMI_FEN                            (ICG_NMI_PIN_DIGITAL_FILTER_ENABLE)
#define ICG0_NMI_TRG                            (ICG_NMI_PIN_TRIG_EDGE_FALLING)
#define ICG0_NMI_EN                             (ICG_NMI_PIN_INT_ENABLE)
#define ICG0_NMI_ICGEN                          (ICG_NMI_PIN_ICG_CONFIG_ENABLE)

/* NMI register config value */
#if ICG0_NMI_HARDWARE_START == ICG_FUNCTION_ON
    #define ICG0_NMI_REG_CONFIG                 ((uint32_t)(ICG0_NMI_FCLK | ICG0_NMI_FEN | \
                                                            ICG0_NMI_TRG  | ICG0_NMI_EN  | \
                                                            ICG0_NMI_ICGEN))
#else
    #define ICG0_NMI_REG_CONFIG                 ((uint32_t)0xFF000000UL)
#endif

/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_LVD_Hardware_Start_Configuration LVD Hardware Start Configuration
 * @{
 *******************************************************************************
 */
/* Enable or disable LVD hardware start */
#define ICG1_LVD_HARDWARE_START                 (ICG_FUNCTION_OFF)

/* Lockup register config */
#define ICG1_LKUP_DIS                           (ICG_LOCKUP_RESET_ENABLE)
/* LVD register config */
#define ICG1_LVD0_LVL                           (ICG_LVD_BELOW2P82_OR_ABOVE2P90)
#define ICG1_LVD0_DIS                           (ICG_LVD_VOLTAGE_DETECTION_ENABLE)

/* LVD register config value */
#if ICG1_LVD_HARDWARE_START == ICG_FUNCTION_ON
    #define ICG1_LVD_REG_CONFIG                 ((uint32_t)(ICG1_LKUP_DIS | ICG1_LVD0_LVL | ICG1_LVD0_DIS))
#else
    #define ICG1_LVD_REG_CONFIG                 ((uint32_t)0xFFFFFFFFUL)
#endif

/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_WDT_Hardware_Start_Configuration WDT Hardware Start Configuration
 * @{
 *******************************************************************************
 */
/* Enable or disable WDT hardware start */
#define ICG7_WDT_HARDWARE_START                 (ICG_FUNCTION_OFF)

/* WDT register config */
#define ICG7_WDT_AUTST                          (ICG_WDT_AFTER_RESET_AUTOSTART)
#define ICG7_WDT_ITS                            (ICG_WDT_TRIG_EVENT_INT)
#define ICG7_WDT_PERI                           (ICG_WDT_COUNTER_CYCLE_4096)
#define ICG7_WDT_CKS                            (ICG_WDT_CLOCK_DIV256)
#define ICG7_WDT_WDPT                           (ICG_WDT_RANGE_100PCT)
#define ICG7_WDT_SLTPOFF                        (ICG_WDT_LPW_MODE_COUNT_CONTINUE)

/* WDT register config value */
#if ICG7_WDT_HARDWARE_START == ICG_FUNCTION_ON
    #define ICG7_WDT_REG_CONFIG                 (((uint32_t)ICG7_WDT_AUTST | ICG7_WDT_ITS | \
                                                            ICG7_WDT_PERI  | ICG7_WDT_CKS | \
                                                            ICG7_WDT_WDPT  | ICG7_WDT_SLTPOFF))
#else
    #define ICG7_WDT_REG_CONFIG                 ((uint32_t)0xFFFFFFFFUL)
#endif

/**
 * @}
 */

/**
 *******************************************************************************
 * @defgroup ICG_Registers_Configuration ICG Registers Configuration
 * @{
 *******************************************************************************
 */
/* ICG0 register value */
#define ICG0_REGISTER_CONSTANT                  ((uint32_t)(ICG0_SWDT_REG_CONFIG | \
                                                            ICG0_HRC_REG_CONFIG  | \
                                                            ICG0_NMI_REG_CONFIG))
/* ICG1 register value */
#define ICG1_REGISTER_CONSTANT                  ((uint32_t)ICG1_LVD_REG_CONFIG)
/* ICG2~6 register reserved value */
#define ICG2_REGISTER_CONSTANT                  ((uint32_t)0xFFFFFFFFUL)
#define ICG3_REGISTER_CONSTANT                  ((uint32_t)0xFFFFFFFFUL)
#define ICG4_REGISTER_CONSTANT                  ((uint32_t)0xFFFFFFFFUL)
#define ICG5_REGISTER_CONSTANT                  ((uint32_t)0xFFFFFFFFUL)
#define ICG6_REGISTER_CONSTANT                  ((uint32_t)0xFFFFFFFFUL)
/* ICG7 register value */
#define ICG7_REGISTER_CONSTANT                  ((uint32_t)ICG7_WDT_REG_CONFIG)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

#endif /* DDL_ICG_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32M423_ICG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
