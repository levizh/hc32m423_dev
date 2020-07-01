/**
 *******************************************************************************
 * @file  hc32_ddl.h
 * @brief This file contains HC32 Series Device Driver Library file call
 *        management.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-01       Zhangxl         First version
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
#ifndef __HC32_DDL_H__
#define __HC32_DDL_H__

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

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Defined use Device Driver Library */
#if !defined (USE_DDL_DRIVER)
/**
 * @brief Comment the line below if you will not use the Device Driver Library.
 * In this case, the application code will be based on direct access to
 * peripherals registers.
 */
    /* #define USE_DDL_DRIVER */
#endif /* USE_DDL_DRIVER */

/**
 * @brief HC32 Series Device Driver Library version number v1.0.0
 */
#define HC32_DDL_VERSION_MAIN           0x01U  /*!< [31:24] main version */
#define HC32_DDL_VERSION_SUB1           0x00U  /*!< [23:16] sub1 version */
#define HC32_DDL_VERSION_SUB2           0x00U  /*!< [15:8]  sub2 version */
#define HC32_DDL_VERSION_RC             0x00U  /*!< [7:0]   release candidate */
#define HC32_DDL_VERSION                ((HC32_DDL_VERSION_MAIN << 24) | \
                                         (HC32_DDL_VERSION_SUB1 << 16) | \
                                         (HC32_DDL_VERSION_SUB2 << 8 ) | \
                                         (HC32_DDL_VERSION_RC))

/* Use Device Driver Library */
#if defined (USE_DDL_DRIVER)

/**
 * @brief Include peripheral module's header file
 */
#if (DDL_ADC_ENABLE == DDL_ON)
    #include "hc32m423_adc.h"
#endif /* DDL_ADC_ENABLE */

#if (DDL_CLK_ENABLE == DDL_ON)
    #include "hc32m423_clk.h"
#endif /* DDL_CLK_ENABLE */

#if (DDL_CMP_ENABLE == DDL_ON)
    #include "hc32m423_cmp.h"
#endif /* DDL_CMP_ENABLE */

#if (DDL_CRC_ENABLE == DDL_ON)
    #include "hc32m423_crc.h"
#endif /* DDL_CRC_ENABLE */

#if (DDL_CTC_ENABLE == DDL_ON)
    #include "hc32m423_ctc.h"
#endif /* DDL_CTC_ENABLE */

#if (DDL_DCU_ENABLE == DDL_ON)
    #include "hc32m423_dcu.h"
#endif /* DDL_DCU_ENABLE */

#if (DDL_DMA_ENABLE == DDL_ON)
    #include "hc32m423_dma.h"
#endif /* DDL_DMA_ENABLE */

#if (DDL_EFM_ENABLE == DDL_ON)
    #include "hc32m423_efm.h"
#endif /* DDL_EFM_ENABLE */

#if (DDL_EMB_ENABLE == DDL_ON)
    #include "hc32m423_emb.h"
#endif /* DDL_EMB_ENABLE */

#if (DDL_FCM_ENABLE == DDL_ON)
    #include "hc32m423_fcm.h"
#endif /* DDL_FCM_ENABLE */

#if (DDL_GPIO_ENABLE == DDL_ON)
    #include "hc32m423_gpio.h"
#endif /* DDL_GPIO_ENABLE */

#if (DDL_I2C_ENABLE == DDL_ON)
    #include "hc32m423_i2c.h"
#endif /* DDL_I2C_ENABLE */

#if (DDL_ICG_ENABLE == DDL_ON)
    #include "hc32m423_icg.h"
#endif /* DDL_ICG_ENABLE */

#if ((DDL_INTERRUPTS_ENABLE == DDL_ON) || (DDL_EXINT_NMI_SWI_ENABLE == DDL_ON))
    #include "hc32m423_interrupts.h"
#endif /* DDL_INTERRUPTS_ENABLE || DDL_EXINT_NMI_SWI_ENABLE */

#if (DDL_PWC_ENABLE == DDL_ON)
    #include "hc32m423_pwc.h"
#endif /* DDL_PWC_ENABLE */

#if (DDL_RMU_ENABLE == DDL_ON)
    #include "hc32m423_rmu.h"
#endif /* DDL_RMU_ENABLE */

#if (DDL_SPI_ENABLE == DDL_ON)
    #include "hc32m423_spi.h"
#endif /* DDL_SPI_ENABLE */

#if (DDL_SWDT_ENABLE == DDL_ON)
    #include "hc32m423_swdt.h"
#endif /* DDL_SWDT_ENABLE */

#if (DDL_TMR0_ENABLE == DDL_ON)
    #include "hc32m423_tmr0.h"
#endif /* DDL_TMR0_ENABLE */

#if (DDL_TMR2_ENABLE == DDL_ON)
    #include "hc32m423_tmr2.h"
#endif /* DDL_TMR2_ENABLE */

#if (DDL_TMR4_ENABLE == DDL_ON)
    #include "hc32m423_tmr4.h"
#endif /* DDL_TMR4_ENABLE */

#if (DDL_TMRA_ENABLE == DDL_ON)
    #include "hc32m423_tmra.h"
#endif /* DDL_TMRA_ENABLE */

#if (DDL_TMRB_ENABLE == DDL_ON)
    #include "hc32m423_tmrb.h"
#endif /* DDL_TMRB_ENABLE */

#if (DDL_USART_ENABLE == DDL_ON)
    #include "hc32m423_usart.h"
#endif /* DDL_USART_ENABLE */

#if (DDL_UTILITY_ENABLE == DDL_ON)
    #include "hc32m423_utility.h"
#endif /* DDL_UTILITY_ENABLE */

#if (DDL_WDT_ENABLE == DDL_ON)
    #include "hc32m423_wdt.h"
#endif /* DDL_WDT_ENABLE */


/**
 * @brief Include BSP board's header file
 */
#if (BSP_EV_HC32M423_LQFP64 == BSP_EV_HC32M423)
    #include "ev_hc32m423_lqfp64.h"
#endif /* BSP_EV_HC32M423_LQFP64 */

#endif /* USE_DDL_DRIVER */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __HC32_DDL_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
