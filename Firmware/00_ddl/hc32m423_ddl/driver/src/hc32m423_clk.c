/**
 *******************************************************************************
 * @file  hc32m423_clk.c
 * @brief This file provides firmware functions to manage the Clock(CLK).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-06-24       Chengy          First version
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
#include "hc32m423_clk.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CLK CLK
 * @brief Clock Driver Library
 * @{
 */

#if (DDL_CLK_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CLK_Local_Macros CLK Local Macros
 * @{
 */

#define CLK_TIMEOUT             (0x1000U)
#define CLK_XTAL_TIMEOUT        (0x20000U)
#define CLK_PLL_TIMEOUT         (0x80000U)

#define CLK_PLL_DIV_MIN         (2U)
#define CLK_PLL_DIV_MAX         (4U)

#define CLK_PLLN_MIN            (10U)
#define CLK_PLLN_MAX            (60U)

#define CLK_PLLM_MIN            (1U)
#define CLK_PLLM_MAX            (8U)


#define CLK_PLL_VCO_IN_MIN                  (4U*1000U*1000U)
#define CLK_PLL_VCO_IN_MAX                  (125U*100U*1000U)

#define CLK_PLL_VCO_OUT_MIN                 (120U*1000U*1000U)
#define CLK_PLL_VCO_OUT_MAX                 (240U*1000U*1000U)

/**
 * @defgroup RTC_Check_Parameters_Validity RTC Check Parameters Validity
 * @{
 */
/* Paramer valid check for XTAL state */
#define IS_VALID_CLK_XTAL_STATE(STA)                                           \
(       ((STA) == CLK_XTAL_OFF)                     ||                         \
        ((STA) == CLK_XTAL_ON))

/* Paramer valid check for XTAL mode */
#define IS_VALID_CLK_XTAL_MODE(MODE)                                           \
(       ((MODE) == CLK_XTALMODE_OSC)                ||                         \
        ((MODE) == CLK_XTALMODE_EXCLK))

/* Paramer valid check for XTAL super driver state */
#define IS_VALID_CLK_XTAL_SUPDRV_STATE(STA)                                    \
(       ((STA) == CLK_XTAL_SUPDRV_ON)               ||                         \
        ((STA) == CLK_XTAL_SUPDRV_OFF))

/* Paramer valid check for XTAL driver ability mode */
#define IS_VALID_CLK_XTALDRV_MODE(MODE)                                        \
(       ((MODE) == CLK_XTALDRV_HIGH)                ||                         \
        ((MODE) == CLK_XTALDRV_MID)                 ||                         \
        ((MODE) == CLK_XTALDRV_LOW)                 ||                         \
        ((MODE) == CLK_XTALDRV_ULOW))

/* Paramer valid check for XTAL stable time selection */
#define IS_VALID_CLK_XTALSTB_SEL(SEL)                                          \
(       ((SEL) == CLK_XTALSTB_8)                    ||                         \
        ((SEL) == CLK_XTALSTB_9 )                   ||                         \
        ((SEL) == CLK_XTALSTB_10)                   ||                         \
        ((SEL) == CLK_XTALSTB_11)                   ||                         \
        ((SEL) == CLK_XTALSTB_13)                   ||                         \
        ((SEL) == CLK_XTALSTB_15)                   ||                         \
        ((SEL) == CLK_XTALSTB_16)                   ||                         \
        ((SEL) == CLK_XTALSTB_17))

/* Paramer valid check for XTALSTD state */
#define IS_VALID_CLK_XTALSTD_STATE(STA)                                        \
(       ((STA) == CLK_XTALSTD_OFF)                  ||                         \
        ((STA) == CLK_XTALSTD_ON))

/* Paramer valid check for XTALSTD mode */
#define IS_VALID_CLK_XTALSTD_MODE(MD)                                          \
(       ((MD) == CLK_XTALSTD_MODE_RST)            ||                           \
        ((MD) == CLK_XTALSTD_MODE_INT))

/* Paramer valid check for XTALSTD interrupt state */
#define IS_VALID_CLK_XTALSTD_INT_STATE(STA)                                    \
(       ((STA) == CLK_XTALSTD_INT_OFF)              ||                         \
        ((STA) == CLK_XTALSTD_INT_ON))

/* Paramer valid check for XTALSTD reset state */
#define IS_VALID_CLK_XTALSTD_RST_STATE(STA)                                    \
(       ((STA) == CLK_XTALSTD_RST_OFF)              ||                         \
        ((STA) == CLK_XTALSTD_RST_ON))

/* Paramer valid check for HRC state */
#define IS_VALID_CLK_HRC_STATE(STA)                                            \
(       ((STA) == CLK_HRC_OFF)                      ||                         \
        ((STA) == CLK_HRC_ON))

/* Paramer valid check for HRC state */
#define IS_VALID_CLK_HRC_FREQ_SEL(SEL)                                         \
 (      ((SEL) == CLK_HRCFREQ_32)                   ||                         \
        ((SEL) == CLK_HRCFREQ_16)                   ||                         \
        ((SEL) == CLK_HRCFREQ_8)                    ||                         \
        ((SEL) == CLK_HRCFREQ_4)                    ||                         \
        ((SEL) == CLK_HRCFREQ_2)                    ||                         \
        ((SEL) == CLK_HRCFREQ_1))

/* Paramer valid check for LRC state */
#define IS_VALID_CLK_LRC_STATE(STA)                                            \
(       ((STA) == CLK_LRC_OFF)                      ||                         \
        ((STA) == CLK_LRC_ON))

/* Paramer valid check for system clock source */
#define IS_VALID_CLK_SYSCLK_SRC(SRC)                                           \
(       ((SRC) == CLK_SYSCLKSOURCE_HRC)             ||                         \
        ((SRC) == CLK_SYSCLKSOURCE_MRC)             ||                         \
        ((SRC) == CLK_SYSCLKSOURCE_LRC)             ||                         \
        ((SRC) == CLK_SYSCLKSOURCE_XTAL)            ||                         \
        ((SRC) == CLK_SYSCLKSOURCE_PLL))

/* Paramer valid check for HCLK clock divider */
#define IS_VALID_HCLK_DIV(DIV)                                                 \
(       ((DIV) == CLK_HCLK_DIV1)                    ||                         \
        ((DIV) == CLK_HCLK_DIV2)                    ||                         \
        ((DIV) == CLK_HCLK_DIV4)                    ||                         \
        ((DIV) == CLK_HCLK_DIV8)                    ||                         \
        ((DIV) == CLK_HCLK_DIV16)                   ||                         \
        ((DIV) == CLK_HCLK_DIV32)                   ||                         \
        ((DIV) == CLK_HCLK_DIV64))

/* Paramer valid check for PCLK1 clock divider */
#define IS_VALID_PCLK1_DIV(DIV)                                                \
(       ((DIV) == CLK_PCLK1_DIV1)                   ||                         \
        ((DIV) == CLK_PCLK1_DIV2)                   ||                         \
        ((DIV) == CLK_PCLK1_DIV4)                   ||                         \
        ((DIV) == CLK_PCLK1_DIV8)                   ||                         \
        ((DIV) == CLK_PCLK1_DIV16)                  ||                         \
        ((DIV) == CLK_PCLK1_DIV32)                  ||                         \
        ((DIV) == CLK_PCLK1_DIV64))

/* Paramer valid check for PCLK4 clock divider */
#define IS_VALID_PCLK4_DIV(DIV)                                                \
(       ((DIV) == CLK_PCLK4_DIV1)                   ||                         \
        ((DIV) == CLK_PCLK4_DIV2)                   ||                         \
        ((DIV) == CLK_PCLK4_DIV4)                   ||                         \
        ((DIV) == CLK_PCLK4_DIV8)                   ||                         \
        ((DIV) == CLK_PCLK4_DIV16)                  ||                         \
        ((DIV) == CLK_PCLK4_DIV32)                  ||                         \
        ((DIV) == CLK_PCLK4_DIV64))

/* Paramer valid check for ADC clock divider */
#define IS_VALID_ADCCLK_DIV(DIV)                                               \
(       ((DIV) == CLK_ADCCLK_PCLK4_DIV1)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV2)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV3)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV4)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV5)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV6)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV7)            ||                         \
        ((DIV) == CLK_ADCCLK_PCLK4_DIV8))

/* Parameter valid check for CLK MCO clock source. */
#define IS_VALID_CLK_MCOSOURCE(SOURCE)                                         \
(       ((SOURCE) == CLK_MCOSOURCCE_HRC)            ||                         \
        ((SOURCE) == CLK_MCOSOURCCE_MRC)            ||                         \
        ((SOURCE) == CLK_MCOSOURCCE_LRC)            ||                         \
        ((SOURCE) == CLK_MCOSOURCCE_XTAL)           ||                         \
        ((SOURCE) == CLK_MCOSOURCCE_PLLP)           ||                         \
        ((SOURCE) == CLK_MCOSOURCCE_HCLK)           ||                         \
        ((SOURCE) == CLK_MCOSOURCCE_SWDT))

/* Parameter valid check for CLK MCO clock Prescaler. */
#define IS_VALID_CLK_MCODIV(DIV)                                               \
(       ((DIV) == CLK_MCODIV_1)                     ||                         \
        ((DIV) == CLK_MCODIV_2)                     ||                         \
        ((DIV) == CLK_MCODIV_4)                     ||                         \
        ((DIV) == CLK_MCODIV_8)                     ||                         \
        ((DIV) == CLK_MCODIV_16)                    ||                         \
        ((DIV) == CLK_MCODIV_32)                    ||                         \
        ((DIV) == CLK_MCODIV_64)                    ||                         \
        ((DIV) == CLK_MCODIV_128))

/* Parameter valid check for CLK stable flag. */
#define IS_VALID_CLK_STB_FLAG(flag)                                            \
(       ((flag) == CLK_FLAG_HRCSTB)                 ||                         \
        ((flag) == CLK_FLAG_PLLSTB)                 ||                         \
        ((flag) == CLK_FLAG_XTALSTB))

/* Parameter valid check for PLL clock source. */
#define IS_VALID_PLL_SRC(flag)                                                 \
(       ((flag) == CLK_PLL_SRC_HRC)                 ||                         \
        ((flag) == CLK_PLL_SRC_XTAL))

/*! Parameter validity check for pllp */
#define IS_PLL_DIV_VALID(pllp)                                                 \
(   (CLK_PLL_DIV_MIN        <=  (pllp))     &&                                 \
    (CLK_PLL_DIV_MAX        >=  (pllp)))

/*! Parameter validity check for plln */
#define IS_PLLN_VALID(plln)                                                    \
(   (CLK_PLLN_MIN           <=  (plln))     &&                                 \
    (CLK_PLLN_MAX           >=  (plln)))

/*! Parameter validity check for pllm*/
#define IS_PLLM_VALID(pllm)                                                    \
(   (CLK_PLLM_MIN           <=  (pllm))     &&                                 \
    (CLK_PLLM_MAX           >=  (pllm)))

/*! Parameter validity check for pllsource/pllm \a vco_in. */
#define IS_PLL_VCO_IN_VALID(vco_in)                                            \
(   (CLK_PLL_VCO_IN_MIN     <=  (vco_in))   &&                                 \
    (CLK_PLL_VCO_IN_MAX     >=  (vco_in)))

/*! Parameter validity check for pllsource/pllm*plln \a vco_out. */
#define IS_PLL_VCO_OUT_VALID(vco_out)                                          \
(   (CLK_PLL_VCO_OUT_MIN    <=  (vco_out))  &&                                 \
    (CLK_PLL_VCO_OUT_MAX    >=  (vco_out)))

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
 * @defgroup CLK_Global_Functions CLK Global Functions
 * @{
 */
/**
  * @brief  Resets the CLK clock configuration to the default reset state.
  * @note   The default reset state of the clock configuration is given below:
  *            - LRC HRC ON and HRC used as system clock source
  *            - XTAL OFF
  *            - SysClk divider set to 1.
  *            - MCO OFF
  *            - PLL OFF
  *            - All interrupts disabled
  * @param  None
  * @retval None
  */
void CLK_DeInit(void)
{
    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    /* Reset peripheral clock */
    M4_CMU->FCG = 0xFFFFFFFFu;

    /* Reset system clock / HCLK divider */
    M4_CMU->SCFGR = 0x00000000U;
//    M4_CMU->PERICKSEL = 0x00U;

    /* Start the HRC clock */
    M4_CMU->HRCCR = 0x00U;
    while(1U == READ_REG8_BIT(M4_CMU->HRCCR, CMU_HRCCR_HRCSTP));

    /* Reset MCO */
    M4_CMU->MCOCFGR = 0x00U;

    /* Reset the system source */
    M4_CMU->CKSWR = 0x00U;

    /* Reset XTALSTD */
    M4_CMU->XTALSTDCR = 0x00U;

    /* Reset PLL */
    M4_CMU->PLLCR = 0x01U;

    /* Reset LRC MRC XTAL */
    M4_CMU->LRCCR = 0x00U;
    M4_CMU->MRCCR = 0x00U;
    M4_CMU->XTALCR = 0x01U;

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();
}

/**
 * @brief  Init Xtal initial structure with default value.
 * @param  pstcXtal specifies the paramer of XTAL.
 *            @arg    u8XtalState  : The new state of the XTAL.
 *            @arg    u8XtalMode   : The XTAL mode selection osc or exclk.
 *            @arg    u8XtalDrv    : The XTAL drive ability.
 *            @arg    u8XtalSupDrv : The XTAL super drive on or off.
 *            @arg    u8XtalStb    : The XTAL stable time selection.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CLK_XtalStrucInit(stc_clk_xtal_init_t* pstcXtal)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtal)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtal->u8XtalState   = CLK_XTAL_OFF;
        pstcXtal->u8XtalMode    = CLK_XTALMODE_OSC;
        pstcXtal->u8XtalDrv     = CLK_XTALDRV_HIGH;
        pstcXtal->u8XtalSupDrv  = CLK_XTAL_SUPDRV_ON;
        pstcXtal->u8XtalStb     = CLK_XTALSTB_8;
    }

    return enRet;
}

/**
  * @brief  Initialise the XTAL.
  * @param  pstcXtal specifies the paramer of XTAL.
  *            @arg    u8XtalState  : The new state of the XTAL.
  *            @arg    u8XtalMode   : The XTAL mode selection osc or exclk.
  *            @arg    u8XtalDrv    : The XTAL drive ability.
  *            @arg    u8XtalSupDrv : The XTAL super drive on or off.
  *            @arg    u8XtalStb    : The XTAL stable time selection.
  * @retval en_result_t Status
  */
en_result_t CLK_XTALInit(const stc_clk_xtal_init_t* pstcXtal)
{
    uint32_t u32timeout = 0UL;
    en_result_t enRet = Ok;

    if (pstcXtal == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Paramers check */
        DDL_ASSERT(IS_VALID_CLK_XTAL_STATE(pstcXtal->u8XtalState));

        /* Enable register write. */
        CLK_REG_WRITE_ENABLE();

        if(CLK_XTAL_OFF == pstcXtal->u8XtalState)
        {
            /* When the XTAL is used as system clock in these case XTAL will not disabled */
            if(CLK_SYSCLKSOURCE_XTAL == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
            {
                enRet = Error;
            }
            else
            {
                /* Disable XTAL */
                M4_CMU->XTALCR = CLK_XTAL_OFF;
                /* Wait XTAL stop */
                while(CLK_FLAG_XTALSTB == READ_REG8_BIT(M4_CMU->OSCSTBSR, CMU_OSCSTBSR_XTALSTBF))
                {
                    u32timeout++;
                    if(u32timeout > CLK_XTAL_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                    }
                    else
                    {
                        /* code */
                    }
                }
            }
        }
        else
        {
            /* Paramers check */
            DDL_ASSERT(IS_VALID_CLK_XTAL_MODE(pstcXtal->u8XtalMode));
            DDL_ASSERT(IS_VALID_CLK_XTALDRV_MODE(pstcXtal->u8XtalDrv));
            DDL_ASSERT(IS_VALID_CLK_XTAL_SUPDRV_STATE(pstcXtal->u8XtalSupDrv));
            DDL_ASSERT(IS_VALID_CLK_XTALSTB_SEL(pstcXtal->u8XtalStb));

            /* Configure XTAL mode, driver ability, super_driver */
            M4_CMU->XTALCFGR = pstcXtal->u8XtalDrv | pstcXtal->u8XtalMode | pstcXtal->u8XtalSupDrv;
            /* Configure XTAL stable time */
            M4_CMU->XTALSTBCR = pstcXtal->u8XtalStb;
            /* Enable XTAL */
            M4_CMU->XTALCR = CLK_XTAL_ON;
            /* Wait XTAL stable */
            while(CLK_FLAG_XTALSTB != READ_REG8_BIT(M4_CMU->OSCSTBSR, CMU_OSCSTBSR_XTALSTBF))
            {
                u32timeout++;
                if(u32timeout > CLK_XTAL_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                }
                else
                {
                    /* code */
                }
            }
        }

        /* Disbale register write. */
        CLK_REG_WRITE_DISABLE();
    }

    return enRet;
}

/**
 * @brief  Initialise the HRC.
 * @param  HRCState specifies the new state of HRC.
 *           This parameter can be one of the following values:
 *            @arg    CLK_HRC_OFF  : Disable HRC.
 *            @arg    CLK_HRC_ON   : Enable HRC.
 * @param  HRCFreq  specifies the frequency of HRC.
 *           This parameter can be one of the following values:
 *            @arg    CLK_HRCFREQ_32 : HRC frequency is 32MHz while ICG.HRCFREQS[3] = 0.
 *            @arg    CLK_HRCFREQ_16 : HRC frequency is 16MHz while ICG.HRCFREQS[3] = 0.
 *            @arg    CLK_HRCFREQ_8  : HRC frequency is 8MHz while ICG.HRCFREQS[3] = 0.
 *            @arg    CLK_HRCFREQ_4  : HRC frequency is 4MHz while ICG.HRCFREQS[3] = 0.
 *            @arg    CLK_HRCFREQ_2  : HRC frequency is 2MHz while ICG.HRCFREQS[3] = 0.
 *            @arg    CLK_HRCFREQ_1  : HRC frequency is 1MHz while ICG.HRCFREQS[3] = 0.
 *            @arg    CLK_HRCFREQ_48 : HRC frequency is 48MHz while ICG.HRCFREQS[3] = 1.
 *            @arg    CLK_HRCFREQ_24 : HRC frequency is 24MHz while ICG.HRCFREQS[3] = 1.
 *            @arg    CLK_HRCFREQ_12 : HRC frequency is 12MHz while ICG.HRCFREQS[3] = 1.
 *            @arg    CLK_HRCFREQ_6  : HRC frequency is 6MHz while ICG.HRCFREQS[3] = 1.
 *            @arg    CLK_HRCFREQ_3  : HRC frequency is 3MHz while ICG.HRCFREQS[3] = 1.
 *            @arg    CLK_HRCFREQ_1P5: HRC frequency is 1.5MHz while ICG.HRCFREQS[3] = 1.
 * @retval en_result_t Status
 */
en_result_t CLK_HRCInit(uint8_t HRCState, uint8_t HRCFreq)
{
    uint32_t u32timeout = 0UL;
    en_result_t enRet = Ok;

    /* Paramers check */
    DDL_ASSERT(IS_VALID_CLK_HRC_STATE(HRCState));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    if(CLK_HRC_OFF == HRCState)
    {
        /* When the HRC is used as system clock in these case HRC will not disabled */
        if(CLK_SYSCLKSOURCE_HRC == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = Error;
        }
        else
        {
            /* Disable HRC */
            M4_CMU->HRCCR = CLK_HRC_OFF;
            /* Wait HRC stop */
            while(CLK_FLAG_HRCSTB == READ_REG8_BIT(M4_CMU->OSCSTBSR, CMU_OSCSTBSR_HRCSTBF))
            {
                u32timeout++;
                if(u32timeout > CLK_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                }
                else
                {
                    /* code */
                }
            }
        }
    }
    else
    {
        /* Paramers check */
        DDL_ASSERT(IS_VALID_CLK_HRC_FREQ_SEL(HRCFreq));

        /* Enable CMU_HRCCFGR register write */
        CLK_HRCCFGR_WRITE_ENBALE();

        /* Configure HRC frequency */
        M4_CMU->HRCCFGR = HRCFreq;

        /* Disbale CMU_HRCCFGR register write */
        CLK_HRCCFGR_WRITE_DISABLE();

        /* Enable HRC */
        M4_CMU->HRCCR = CLK_HRC_ON;
        /* Wait HRC stable */
        while(CLK_FLAG_HRCSTB != READ_REG8_BIT(M4_CMU->OSCSTBSR, CMU_OSCSTBSR_HRCSTBF))
        {
            u32timeout++;
            if(u32timeout > CLK_TIMEOUT)
            {
                enRet = ErrorTimeout;
            }
            else
            {
                /* code */
            }
        }
    }

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();

    /* Update system clock */
    SystemCoreClockUpdate();

    return enRet;
}

/**
 * @brief  Initialise the LRC.
 * @param  LRCState specifies the new state of LRC.
 *           This parameter can be one of the following values:
 *            @arg    CLK_LRC_OFF  : Disable LRC.
 *            @arg    CLK_LRC_ON   : Enable LRC.
 * @retval en_result_t Status
 */
en_result_t CLK_LRCInit(uint8_t LRCState)
{
    en_result_t enRet = Ok;

    /* Paramers check */
    DDL_ASSERT(IS_VALID_CLK_LRC_STATE(LRCState));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    if(CLK_LRC_OFF == LRCState)
    {
        /* When the LRC is used as system clock in these case LRC will not disabled */
        if(CLK_SYSCLKSOURCE_LRC == READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            enRet = Error;
        }
        else
        {
            /* Disable LRC */
            M4_CMU->LRCCR = CLK_LRC_OFF;
        }
    }
    else
    {
        /* Enable LRC */
        M4_CMU->LRCCR = CLK_LRC_ON;
    }

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();

    return enRet;
}

/**
 * @brief  Init XtalStd initial structure with default value.
 * @param  pstcXtalStd specifies the paramer of XTALSTD.
 *            @arg    u8XtalStdState:   The new state of the XTALSTD.
 *            @arg    u8XtalStdMode:    The XTAL status detection occur interrupt or reset.
 *            @arg    u8XtalStdInt:     The XTAL status detection interrupt on or off.
 *            @arg    u8XtalStdRst:     The XTAL status detection reset on or off.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t CLK_XtalStdStrucInit(stc_clk_xtalstd_init_t* pstcXtalStd)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcXtalStd)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcXtalStd->u8XtalStdState = CLK_XTALSTD_OFF;
        pstcXtalStd->u8XtalStdMode  = CLK_XTALSTD_MODE_INT;
        pstcXtalStd->u8XtalStdInt   = CLK_XTALSTD_RST_OFF;
        pstcXtalStd->u8XtalStdRst   = CLK_XTALSTD_INT_OFF;
    }

    return enRet;
}

/**
 * @brief  Initialise the XTAL status detection.
 * @param  pstcXtalStd specifies the paramer of XTALSTD.
 *            @arg    u8XtalStdState:   The new state of the XTALSTD.
 *            @arg    u8XtalStdMode:    The XTAL status detection occur interrupt or reset.
 *            @arg    u8XtalStdInt:     The XTAL status detection interrupt on or off.
 *            @arg    u8XtalStdRst:     The XTAL status detection reset on or off.
 * @retval None
 */
en_result_t CLK_XTALStdInit(const stc_clk_xtalstd_init_t* pstcXtalStd)
{
    en_result_t enRet = Ok;

    if (pstcXtalStd == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Paramer valid check */
        DDL_ASSERT(IS_VALID_CLK_XTALSTD_STATE(pstcXtalStd->u8XtalStdState));

        /* Enable register write. */
        CLK_REG_WRITE_ENABLE();

        if(CLK_XTALSTD_OFF == pstcXtalStd->u8XtalStdState)
        {
            /* Disbale XTAL status detection */
            CLEAR_REG8_BIT(M4_CMU->XTALSTDCR, CMU_XTALSTDCR_XTALSTDE);
        }
        else
        {
            /* Paramer valid check */
            DDL_ASSERT(IS_VALID_CLK_XTALSTD_MODE(pstcXtalStd->u8XtalStdMode));
            DDL_ASSERT(IS_VALID_CLK_XTALSTD_INT_STATE(pstcXtalStd->u8XtalStdInt));
            DDL_ASSERT(IS_VALID_CLK_XTALSTD_RST_STATE(pstcXtalStd->u8XtalStdRst));

            /* Confiure XTALSTD and enable XTALSTD */
            M4_CMU->XTALSTDCR = pstcXtalStd->u8XtalStdState | pstcXtalStd->u8XtalStdMode | \
                                pstcXtalStd->u8XtalStdInt   | pstcXtalStd->u8XtalStdRst;
        }
    }

    return enRet;
}

/**
 * @brief  Set the system clock source.
 * @param  u8Src specifies the source of system clock.
 *          This parameter can be one of the following values:
 *            @arg    CLK_SYSCLKSOURCE_HRC    : select HRC as system clock source
 *            @arg    CLK_SYSCLKSOURCE_XTAL   : select XTAL as system clock source
 *            @arg    CLK_SYSCLKSOURCE_LRC    : select LRC as system clock source
 *            @arg    CLK_SYSCLKSOURCE_MRC    : select MRC as system clock source
 *            @arg    CLK_SYSCLKSOURCE_PLL    : select PLL as system clock source
 * @retval None
 */
void CLK_SetSysclkSrc(uint8_t u8Src)
{
    DDL_ASSERT(IS_VALID_CLK_SYSCLK_SRC(u8Src));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    /* Set system clock divider */
    M4_CMU->CKSWR = u8Src;

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();

    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Set the system clock divider.
 * @param  pstcClkDivCfg The system clock configures struct.
 * @retval None
 */
void CLK_SetSysclkDiv(const stc_clk_div_cfg_t *pstcClkDivCfg)
{
    DDL_ASSERT(IS_VALID_HCLK_DIV(pstcClkDivCfg->u32HclkDiv));
    DDL_ASSERT(IS_VALID_PCLK1_DIV(pstcClkDivCfg->u32Pclk1Div));
    DDL_ASSERT(IS_VALID_PCLK4_DIV(pstcClkDivCfg->u32Pclk4Div));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    /* Set system clock divider */
    M4_CMU->SCFGR = pstcClkDivCfg->u32HclkDiv | pstcClkDivCfg->u32Pclk1Div | pstcClkDivCfg->u32Pclk4Div;

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();

    /* Update system clock */
    SystemCoreClockUpdate();
}

/**
 * @brief  Set the PCLK4 divider witch used as ADC clock.
 * @param  u8Div specifies the divider of PCLK4. @ref CLK_ADCCLK_Divider.
 * @retval None
 */
void CLK_SetADClkDiv(uint8_t u8Div)
{
    DDL_ASSERT(IS_VALID_ADCCLK_DIV(u8Div));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    /* Set system clock divider */
    M4_CMU->ADCKSEL = u8Div;

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or disable the FCG peripheral clock.
 * @note   After reset,the peripheral clock is disabled and the application
 *         software has to enable this clock before using it.
 * @param  u32FcgPeriph specifies the peripheral in FCG. @ref CLK_FCG_Peripheral_Control.
  *
 * @param  enNewState specifies the new state of the clock output.
 *          This parameter can be one of the following values:
 *            @arg Enable:   Enable clock output.
 *            @arg Disable:  Disable clock output.
 * @retval None
 */
void CLK_FcgPeriphClockCmd(uint32_t u32FcgPeriph, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    if(Enable == enNewState)
    {
        M4_CMU->FCG &= ~u32FcgPeriph;
    }
    else
    {
        M4_CMU->FCG |= u32FcgPeriph;
    }

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();
}

/**
 * @brief  Selects the clock source to output on MCO pin.
 * @note   P15 should be configured in alternate function mode.
 * @param  CLK_MCOSource specifies the clock source to output. @ref CLK_MCO_Clock_Source.
 * @param  CLK_MCODiv specifies the MCOx prescaler. @ref CLK_MCO_Clock_Prescaler.
 * @retval None
 */
void CLK_MCOConfig(uint8_t CLK_MCOSource, uint8_t CLK_MCODiv)
{
    /* Check the parameters. */
    DDL_ASSERT(IS_VALID_CLK_MCOSOURCE(CLK_MCOSource));
    DDL_ASSERT(IS_VALID_CLK_MCODIV(CLK_MCODiv));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    /* Configure the MCO and Enable MCO */
    M4_CMU->MCOCFGR = (CLK_MCODiv | CLK_MCOSource);

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or Disable MCO.
 * @param  enNewState specifies the new state of the clock output.
 *          This parameter can be one of the following values:
 *            @arg Enable:   Enable clock output.
 *            @arg Disable:  Disable clock output.
 * @retval None
 */
void CLK_MCOCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    /* Enable or disable clock output. */
    if(Enable == enNewState)
    {
        MODIFY_REG8(M4_CMU->MCOCFGR, CMU_MCOCFGR_MCO1EN, CMU_MCOCFGR_MCO1EN);
    }
    else
    {
        MODIFY_REG8(M4_CMU->MCOCFGR, CMU_MCOCFGR_MCO1EN, 0U);
    }

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();
}

/**
 * @brief  Clear the XTAL error flag.
 * @param  None
 * @retval None
 * @note   The system clock should not be XTAL before call this function.
 */
void CLK_ClearXtalStdFlag(void)
{
    /* Enable register write. */
    CLK_REG_WRITE_ENABLE();

    if(CMU_XTALSTDSR_XTALSTDF == M4_CMU->XTALSTDSR)
    {
        /* Clear the XTAL STD flag */
        CLEAR_REG8_BIT(M4_CMU->XTALSTDSR, CMU_XTALSTDSR_XTALSTDF);
    }

    /* Disbale register write. */
    CLK_REG_WRITE_DISABLE();
}
/**
 * @brief  Get the clock stable flag.
 * @param  u8Flag  specifies the clock stable flag. @ref CLK_STB_Flag
 * @retval en_flag_status_t
 */
en_flag_status_t CLK_GetStableFlag(uint8_t u8Flag)
{
    en_flag_status_t enFlagStatus = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_CLK_STB_FLAG(u8Flag));

    if (Reset != (READ_REG8_BIT(M4_CMU->OSCSTBSR, u8Flag)))
    {
        enFlagStatus = Set;
    }

    return enFlagStatus;
}

/**
 * @brief  Select pll clock source.
 * @param  [in] u32PllSrc               The pll clock source. @ref CLK_PLL_Clock_Source
 * @retval None
 */
void CLK_SetPllSource(uint32_t u32PllSrc)
{
    DDL_ASSERT(IS_VALID_PLL_SRC(u32PllSrc));

    CLK_REG_WRITE_ENABLE();

    MODIFY_REG32(M4_CMU->PLLCFGR, CMU_PLLCFGR_PLLSRC, u32PllSrc);

    CLK_REG_WRITE_DISABLE();
}

/**
 * @brief  Configures the PLL.
 * @param  [in] pstcPllCfg            The PLL configures struct.
 * @retval None
 */
void CLK_PllConfig(const stc_clk_pll_cfg_t *pstcPllCfg)
{
#ifdef __DEBUG
    uint32_t vcoIn = 0ul;
    uint32_t vcoOut = 0ul;
#endif /* #ifdef __DEBUG */

    if(NULL != pstcPllCfg)
    {
        DDL_ASSERT(IS_PLL_DIV_VALID(pstcPllCfg->PllpDiv));
        DDL_ASSERT(IS_PLLN_VALID(pstcPllCfg->plln));
        DDL_ASSERT(IS_PLLM_VALID(pstcPllCfg->pllmDiv));

#ifdef __DEBUG
        vcoIn = ((CLK_PLL_SRC_XTAL == READ_REG32_BIT(M4_CMU->PLLCFGR, CMU_PLLCFGR_PLLSRC) ?
                XTAL_VALUE : HRC_VALUE) / pstcPllCfg->pllmDiv);
        vcoOut = vcoIn * pstcPllCfg->plln;

        DDL_ASSERT(IS_PLL_VCO_IN_VALID(vcoIn));
        DDL_ASSERT(IS_PLL_VCO_OUT_VALID(vcoOut));
#endif /* #ifdef __DEBUG */

        CLK_REG_WRITE_ENABLE();

        MODIFY_REG32(M4_CMU->PLLCFGR,
                     CMU_PLLCFGR_PLLM|CMU_PLLCFGR_PLLN|CMU_PLLCFGR_PLLP,
                     ((pstcPllCfg->PllpDiv-1U)<<CMU_PLLCFGR_PLLP_POS)
                      |((pstcPllCfg->plln-1U)<<CMU_PLLCFGR_PLLN_POS)
                      |((pstcPllCfg->pllmDiv-1U)<<CMU_PLLCFGR_PLLM_POS));

        CLK_REG_WRITE_DISABLE();
    }
    else
    {
        /* code */
    }
}

/**
 * @brief  Enable or disable the MPLL.
 * @param  [in] enNewState             The new state of the MPLL.
 * @arg    Enable                      Enable MPLL.
 * @arg    Disable                     Disable MPLL.
 * @retval en_result_t
 * @note   MPLL can not be stopped if it is used as system clock source.
 */
en_result_t CLK_PllCmd(en_functional_state_t enNewState)
{
    __IO uint32_t timeout = 0ul;
    en_flag_status_t status;
    en_result_t enRet = Ok;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    CLK_REG_WRITE_ENABLE();

    if(Disable == enNewState)
    {
        if(CLK_SYSCLKSOURCE_PLL == M4_CMU->CKSWR)
        {
            enRet = Error;
        }
        else
        {
            SET_REG8_BIT(M4_CMU->PLLCR, CMU_PLLCR_PLLOFF);
        }
    }
    else
    {
        CLEAR_REG8_BIT(M4_CMU->PLLCR, CMU_PLLCR_PLLOFF);
        do
        {
            status = CLK_GetStableFlag(CLK_FLAG_PLLSTB);
            timeout++;
        }while((timeout < CLK_PLL_TIMEOUT) && (status != Set));
    }

    CLK_REG_WRITE_DISABLE();

    return enRet;
}

static uint32_t u32HrcFreqTable_0[6U] = {64*1000000, 32*1000000, 16*1000000,
                                         8*1000000, 4*1000000, 2*1000000};

static uint32_t GetHrcFreq(void)
{
    uint32_t u32Freq;

    u32Freq = u32HrcFreqTable_0[READ_REG8_BIT(M4_CMU->HRCCFGR, CMU_HRCCFGR_HRCFREQS_0|CMU_HRCCFGR_HRCFREQS_1|CMU_HRCCFGR_HRCFREQS_2)];

    if(CMU_HRCCFGR_HRCFREQS_3 == READ_REG8_BIT(M4_CMU->HRCCFGR, CMU_HRCCFGR_HRCFREQS_3))
    {
    }
    else
    {
        u32Freq = u32Freq*3U/4U;
    }
    return u32Freq;
}

/**
 * @brief  Get clock frequency.
 * @param  [in] pstcClkFreq            The clock source struct.
 * @retval The clock frequency include system clock,hclk,exck,pclk0,pclk4.
 *
 * @note   None
 */
void CLK_GetClockFreq(stc_clk_freq_t *pstcClkFreq)
{
    uint32_t plln = 0u, pllp = 0u, pllm = 0u, pllsource = 0u;
    uint32_t u32HrcFreq;

    u32HrcFreq = GetHrcFreq();
    if(NULL != pstcClkFreq)
    {
        /* Get system clock. */
        switch(READ_REG8_BIT(M4_CMU->CKSWR, CMU_CKSWR_CKSW))
        {
            case CLK_SYSCLKSOURCE_HRC:
                /* HRC used as system clock. */
                pstcClkFreq->sysclkFreq = u32HrcFreq;
                break;
            case CLK_SYSCLKSOURCE_MRC:
                /* MRC used as system clock. */
                pstcClkFreq->sysclkFreq = MRC_VALUE;
                break;
            case CLK_SYSCLKSOURCE_LRC:
                /* LRC used as system clock. */
                pstcClkFreq->sysclkFreq = LRC_VALUE;
                break;
            case CLK_SYSCLKSOURCE_XTAL:
                /* XTAL used as system clock. */
                pstcClkFreq->sysclkFreq = XTAL_VALUE;
                break;
            default:
                /* PLL used as system clock. */
                pllsource = READ_REG32_BIT(M4_CMU->PLLCFGR, CMU_PLLCFGR_PLLSRC);

                pllp = (READ_REG32_BIT(M4_CMU->PLLCFGR, CMU_PLLCFGR_PLLP) >> CMU_PLLCFGR_PLLP_POS);
                plln = (READ_REG32_BIT(M4_CMU->PLLCFGR, CMU_PLLCFGR_PLLN) >> CMU_PLLCFGR_PLLN_POS);
                pllm = (READ_REG32_BIT(M4_CMU->PLLCFGR, CMU_PLLCFGR_PLLM) >> CMU_PLLCFGR_PLLM_POS);

                /* PLLCLK = ((pllsrc / pllm) * plln) / pllp */
                if (CLK_PLL_SRC_XTAL == pllsource)
                {
                    pstcClkFreq->sysclkFreq = (XTAL_VALUE)/(pllm+1u)*(plln+1u)/(pllp+1u);
                }
                else if (CLK_PLL_SRC_HRC == pllsource)
                {
                    pstcClkFreq->sysclkFreq = (u32HrcFreq)/(pllm+1u)*(plln+1u)/(pllp+1u);
                }
                else
                {
                    //else
                }
                break;
        }

        /* Get hclk. */
        pstcClkFreq->hclkFreq = pstcClkFreq->sysclkFreq >> (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_HCLKS)>>CMU_SCFGR_HCLKS_POS);

        /* Get pclk1. */
        pstcClkFreq->pclk1Freq = pstcClkFreq->sysclkFreq >> (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S)>>CMU_SCFGR_PCLK1S_POS);

        /* Get pclk4. */
        pstcClkFreq->pclk4Freq = pstcClkFreq->sysclkFreq >> (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK4S)>>CMU_SCFGR_PCLK4S_POS);
    }
    else
    {
        /* code */
    }
}

/**
 * @}
 */

#endif /* DDL_CLK_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
