/**
 *******************************************************************************
 * @file  hc32m423_pwc.c
 * @brief This file provides firmware functions to manage the Power Contorl(PWC).
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32m423_pwc.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_PWC PWC
 * @brief Power Control Driver Library
 * @{
 */

#if (DDL_PWC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup PWC_Local_Macros PWC Local Macros
 * @{
 */
#define PWC_LVD_CR0_MASK            (PWR_LVDCR0_L1IEGS | PWR_LVDCR0_L1LVL  | \
                                     PWR_LVDCR0_L1NFS  | PWR_LVDCR0_L1NMIS | \
                                     PWR_LVDCR0_L1IRS  | PWR_LVDCR0_L1IRE  | \
                                     PWR_LVDCR0_L1CMPOE)

#define PWC_LVD2_CONFIG_SHIFT       ((uint32_t)16UL)

/**
 * @defgroup PWC_Check_Parameters_Validity PWC Check Parameters Validity
 * @{
 */



/*  Parameter validity check for stop mode high POR sel. */
#define IS_VALID_PWC_STOP_HPOR_SEL(sel)                                        \
(       ((sel) == PWC_HPOR_ON)                  ||                             \
        ((sel) == PWC_HPOR_OFF))

/*  Parameter validity check for system clock sel while awake stop mode. */
#define IS_VALID_PWC_STOP_SYSCLK_SEL(sel)                                      \
(       ((sel) == PWC_SYSCLK_FIX)               ||                             \
        ((sel) == PWC_SYSCLK_HRCDIVX))

/*  Parameter validity check for power monitor. */
#define IS_VALID_PWC_PWRMON_EN(x)                                              \
(       ((x) == PWC_PWRMON_ON)                  ||                             \
        ((x) == PWC_PWRMON_OFF))

/*  Parameter validity check for power monitor sel. */
#define IS_VALID_PWC_PWRMON_SEL(sel)                                           \
(       ((sel) == PWC_PWRMON_VINREF)            ||                             \
        ((sel) == PWC_PWRMON_VOTS))

/*  Parameter validity check for LVD Level. */
#define IS_VALID_PWC_LVD_LEVEL(level)                                          \
(       ((level) == PWC_LVD_LEVEL0)             ||                             \
        ((level) == PWC_LVD_LEVEL1)             ||                             \
        ((level) == PWC_LVD_LEVEL2)             ||                             \
        ((level) == PWC_LVD_LEVEL3)             ||                             \
        ((level) == PWC_LVD_LEVEL4)             ||                             \
        ((level) == PWC_LVD_LEVEL5)             ||                             \
        ((level) == PWC_LVD_LEVEL6)             ||                             \
        ((level) == PWC_LVD_LEVEL7)             ||                             \
        ((level) == PWC_LVD_LEVEL8)             ||                             \
        ((level) == PWC_LVD_LEVEL9)             ||                             \
        ((level) == PWC_LVD_LEVEL10)            ||                             \
        ((level) == PWC_LVD_LEVEL11)            ||                             \
        ((level) == PWC_LVD_INP))

/*  Parameter validity check for LVD Level. */
#define IS_VALID_PWC_LVD_DFS_SEL(sel)                                          \
(       ((sel) == PWC_LVD_DFS_2)                ||                             \
        ((sel) == PWC_LVD_DFS_4)                ||                             \
        ((sel) == PWC_LVD_DFS_8)                ||                             \
        ((sel) == PWC_LVD_DFS_16))

/*  Parameter validity check for LVD flag. */
#define IS_VALID_PWC_LVD_FLAG(flag)                                            \
(       ((flag) == PWC_LVD_FLAG_DET)            ||                             \
        ((flag) == PWC_LVD_FLAG_LVI))

/*  Parameter validity check for Ram protect area selection. */
#define IS_VALID_PWC_RAM_PRAT_SEL(sel)                                         \
(       ((sel) == PWC_RAM_PRTA_NONE)            ||                             \
        ((sel) == PWC_RAM_PRTA_128)             ||                             \
        ((sel) == PWC_RAM_PRTA_256)             ||                             \
        ((sel) == PWC_RAM_PRTA_512))



/*  Parameter validity check for PWC LDO Flag. */
#define IS_VALID_PWC_LDO_Flag(x)                                               \
(       ((x) == PWC_FLAG_LDO_PLL)               ||                             \
        ((x) == PWC_FLAG_LDO_HRC))

/*  Parameter validity check for PWC Power Monitor. */
#define IS_VALID_PWC_POWER_MONITOR(x)                                          \
(       ((x) == PWC_POWER_MONITOR_DISABLE)                  ||                 \
        ((x) == PWC_POWER_MONITOR_INTERNAL_REF_VOL)         ||                 \
        ((x) == PWC_POWER_MONITOR_TEMP_SENSOR_VOL))

/*  Parameter validity check for PWC LVD normal unit. */
#define IS_VALID_PWC_LVD_NORMAL_UNIT(x)                                        \
(       ((x) == PWC_LVD1)                       ||                             \
        ((x) == PWC_LVD2))

/*  Parameter validity check for PWC LVD special unit. */
#define IS_VALID_PWC_LVD_SPECIAL_UNIT(x)                                       \
(       ((x) == PWC_LVD0)                       ||                             \
        ((x) == PWC_LVD1)                       ||                             \
        ((x) == PWC_LVD2))

/*  Parameter validity check for PWC LVD External Input. */
#define IS_VALID_PWC_LVD_EX_INPUT(x)                                           \
(       ((x) == PWC_LVD_EX_INPUT_DISABLE)       ||                             \
        ((x) == PWC_LVD_EX_INPUT_ENABLE))

/*  Parameter validity check for PWC LVD Detect Edge. */
#define IS_VALID_PWC_LVD_DETECT_EDGE(x)                                        \
(       ((x) == PWC_LVD_DETECT_EDGE_RISING)     ||                             \
        ((x) == PWC_LVD_DETECT_EDGE_FALLING)    ||                             \
        ((x) == PWC_LVD_DETECT_EDGE_RISING_FALLING))

/*  Parameter validity check for PWC LVD voltage threshold. */
#define IS_VALID_PWC_LVD_VOL_THRESHOLD(x)                                      \
(       ((x) == PWC_LVD_VOL_BELOW4P29_OR_ABOVE4P39)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW4P14_OR_ABOVE4P23)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW4P02_OR_ABOVE4P14)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW3P84_OR_ABOVE3P96)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW3P10_OR_ABOVE3P20)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW3P00_OR_ABOVE3P09)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW2P90_OR_ABOVE2P99)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW2P79_OR_ABOVE2P87)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW2P68_OR_ABOVE2P75)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW2P34_OR_ABOVE2P41)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW2P14_OR_ABOVE2P21)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW1P94_OR_ABOVE2P01)         ||                 \
        ((x) == PWC_LVD_VOL_BELOW1P84_OR_ABOVE1P90)         ||                 \
        ((x) == PWC_LVD_VOL_EX_INPUT)) 

/*  Parameter validity check for PWC LVD Filter. */
#define IS_VALID_PWC_LVD_FILTER(x)                                             \
(       ((x) == PWC_LVD_FILTER_DISABLE)         ||                             \
        ((x) == PWC_LVD_FILTER_CLK_LRC_0P25)    ||                             \
        ((x) == PWC_LVD_FILTER_CLK_LRC_0P5)     ||                             \
        ((x) == PWC_LVD_FILTER_CLK_LRC_DIV1)    ||                             \
        ((x) == PWC_LVD_FILTER_CLK_LRC_DIV2))

/*  Parameter validity check for PWC LVD Trigger Event. */
#define IS_VALID_PWC_LVD_TRIG_EVENT(x)                                         \
(       ((x) == PWC_LVD_TRIG_DISABLE)           ||                             \
        ((x) == PWC_LVD_TRIG_RESET)             ||                             \
        ((x) == PWC_LVD_TRIG_NMI_INTERRUPT)     ||                             \
        ((x) == PWC_LVD_TRIG_MI_INTERRUPT))

/*  Parameter validity check for PWC LVD Comparer Output. */
#define IS_VALID_PWC_LVD_CMP_OUTPUT(x)                                         \
(       ((x) == PWC_LVD_COMPARER_OUTPUT_DISABLE)            ||                 \
        ((x) == PWC_LVD_COMPARER_OUTPUT_ENABLE))

/*  Parameter validity check for Ram Parity flag. */
#define IS_VALID_PWC_RAM_PARITY_FLAG(x)                                        \
(       ((x) == PWC_FLAG_CACHE_PARITY_ERR)      ||                             \
        ((x) == PWC_FLAG_HRAM_PARITY_ERR)       ||                             \
        ((x) == PWC_FLAG_RAM_PARITY_ERR))

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
 * @defgroup PWC_Global_Functions PWC Global Functions
 * @{
 */

/**
 * @brief  Enter stop mode.
 * @param  None
 * @retval None
 */
void PWC_EnterStopMode(void)
{
    PWC_POWER_REG_WRITE_ENABLE();

    SET_REG8_BIT(M4_PWC->STPMCR, PWC_STPMCR_STOP);

    PWC_POWER_REG_WRITE_DISABLE();

     __WFI();
}

/**
 * @brief  Enter sleep mode.
 * @param  None
 * @retval None
 */
void PWC_EnterSleepMode(void)
{
    PWC_POWER_REG_WRITE_ENABLE();

    bM4_PWC->STPMCR_b.STOP = 0U;

    PWC_POWER_REG_WRITE_DISABLE();

     __WFI();
}

/**
 * @brief  Switch high speed to low speed, set the LDO driver ability.
 * @param  None
 * @retval None
 */
void PWC_HighSpeedToLowSpeed(void)
{
    PWC_POWER_REG_WRITE_ENABLE();

    MODIFY_REG32(M4_PWC->PWRC, PWC_PWRC_PWDRV , PWC_DRV_LOW);

    DDL_Delay1ms(1U);

    PWC_POWER_REG_WRITE_DISABLE();
}

/**
 * @brief  Switch low speed to high speed, set the LDO driver ability.
 * @param  None
 * @retval None
 */
void PWC_LowSpeedToHighSpeed(void)
{
    PWC_POWER_REG_WRITE_ENABLE();

    MODIFY_REG32(M4_PWC->PWRC, PWC_PWRC_PWDRV , PWC_DRV_HIGH);

    DDL_Delay1ms(1U);

    PWC_POWER_REG_WRITE_DISABLE();
}

/**
 * @brief  Init the stop config structure with default value.
 * @param  [in] pstcStopCfg            The pointer of stop config structure.
 *   @arg u8HPorSel  Specifies the high POR on or off while stop mode.
 *   @arg u8HrcSel   Specifies the system clock while awake from stop mode.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_StopStructInit(stc_pwc_stop_mode_t* pstcStopCfg)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcStopCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcStopCfg->u8HPorSel = PWC_HPOR_ON;
        pstcStopCfg->u8HrcSel = PWC_SYSCLK_FIX;
    }

    return enRet;
}

/**
 * @brief  Config the stop mode.
 * @param  [in] pstcStopCfg      The pointer of stop config.
 *   @arg u8HPorSel  Specifies the high POR on or off while stop mode.
 *   @arg u8HrcSel   Specifies the system clock while awake from stop mode.
 * @retval None
 */
en_result_t PWC_StopMdConfig(const stc_pwc_stop_mode_t* pstcStopCfg)
{
    en_result_t enRet = Ok;

    if(pstcStopCfg == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter valid check */
        DDL_ASSERT(IS_VALID_PWC_STOP_HPOR_SEL(pstcStopCfg->u8HPorSel));
        DDL_ASSERT(IS_VALID_PWC_STOP_SYSCLK_SEL(pstcStopCfg->u8HrcSel));

        PWC_POWER_REG_WRITE_ENABLE();

        /* Config the stop mode */
        MODIFY_REG8(M4_PWC->STPMCR, PWC_STPMCR_HAPORDIS , pstcStopCfg->u8HPorSel);
        MODIFY_REG8(M4_PWC->STPMCR, PWC_STPMCR_CKSHRC , pstcStopCfg->u8HrcSel);

        PWC_POWER_REG_WRITE_DISABLE();
    }

    return enRet;
}








/**
 * @brief  Get PWC LDO flag status.
 * @param  [in] u16Flag                 PWC LDO flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg PWC_FLAG_LDO_PLL:     PLL LDO ready flag
 *           @arg PWC_FLAG_LDO_HRC:     HRC LDO ready flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_GetLdoFlag(uint16_t u16Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LDO_Flag(u16Flag));
    if (Reset != (READ_REG32_BIT(M4_PWR->PWRC, u16Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Set PWC power monitor.
 * @param  [in] u8CfgVal                PWC Monitor configure value
 *         This parameter can be one of the following values:
 *           @arg PWC_POWER_MONITOR_DISABLE:          Disable power monitor
 *           @arg PWC_POWER_MONITOR_INTERNAL_REF_VOL: Monitor internal reference voltage of power supply
 *           @arg PWC_POWER_MONITOR_TEMP_SENSOR_VOL:  Monitor temperature sensor voltage
 * @retval None
 */
void PWC_SetPowerMonitor(uint8_t u8CfgVal)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_POWER_MONITOR(u8CfgVal));

    PWC_POWER_REG_WRITE_ENABLE();
    MODIFY_REG8(M4_PWR->PWRMONR, (PWR_PWRMONR_PWMONSEL | PWR_PWRMONR_PWMONE), u8CfgVal;
    PWC_POWER_REG_WRITE_DISABLE();
}

/**
 * @brief  De-Initialize PWC LVD function.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_LVD_DeInit(uint8_t u8Unit)
{
    en_result_t enRet = Ok;

    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));

    PWC_LVD_REG_WRITE_ENABLE();
    if (PWC_LVD1 == u8Unit)
    {
        CLEAR_REG32_BIT(M4_PWR->LVDCR0, 0x0000FFFFUL);
        bM4_PWR->LVDCSR1_b.L1DETF = 0U;
    }
    else
    {
        CLEAR_REG32_BIT(M4_PWR->LVDCR0, 0xFFFF0000UL);
        bM4_PWR->LVDCSR1_b.L2DETF = 0U;
    }
    PWC_LVD_REG_WRITE_DISABLE();
}

/**
 * @brief  Initialize PWC LVD function.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @param  [in] pstcLvdInit             Pointer to a @ref stc_pwc_lvd_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_LVD_Init(uint8_t u8Unit, const stc_pwc_lvd_init_t* pstcLvdInit)
{
    en_result_t enRet = Ok;
    uint32_t u32ShiftBit = 0UL;

    if (pstcLvdInit == NULL)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Parameter valid check */
        DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
        DDL_ASSERT(IS_VALID_PWC_LVD_EX_INPUT(pstcLvdInit->u32ExInputEn));
        DDL_ASSERT(IS_VALID_PWC_LVD_DETECT_EDGE(pstcLvdInit->u32DetectEdge));
        DDL_ASSERT(IS_VALID_PWC_LVD_VOL_THRESHOLD(pstcLvdInit->u32VoltageThreshold));
        DDL_ASSERT(IS_VALID_PWC_LVD_FILTER(pstcLvdInit->u32Filter));
        DDL_ASSERT(IS_VALID_PWC_LVD_TRIG_EVENT(pstcLvdInit->u32TrigEvent));
        DDL_ASSERT(IS_VALID_PWC_LVD_CMP_OUTPUT(pstcLvdInit->u32ComparerOutputEn));

        if ((PWC_LVD1 == u8Unit) && (PWC_LVD_VOL_EX_INPUT == pstcLvdInit->u32VoltageThreshold))
        {
            enRet = ErrorInvalidParameter;
        }
        else
        {
            PWC_LVD_REG_WRITE_ENABLE();
            if (PWC_LVD2 == u8Unit)
            {
                u32ShiftBit = PWC_LVD2_CONFIG_SHIFT;
                MODIFY_REG32(M4_PWR->LVDCR0, PWR_LVDCR0_EXVCCINEN, pstcLvdInit->u32ExInputEn);
            }
            /* The filter configuration can only be modified if the LxNFDIS bit is "1" */
            SET_REG32_BIT(M4_PWR->LVDCR0, (PWR_LVDCR0_L1NFDIS << u32ShiftBit));
            MODIFY_REG32(M4_PWR->LVDCR0, (PWC_LVD_CR0_MASK << u32ShiftBit),
                         ((pstcLvdInit->u32DetectEdge | pstcLvdInit->u32VoltageThreshold |
                          pstcLvdInit->u32Filter | pstcLvdInit->u32TrigEvent |
                          pstcLvdInit->u32ComparerOutputEn) << u32ShiftBit);
            PWC_LVD_REG_WRITE_DISABLE();
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_pwc_lvd_init_t to default values.
 * @param  [out] pstcLvdInit            Pointer to a @ref stc_pwc_lvd_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_LVD_StructInit(stc_pwc_lvd_init_t* pstcLvdInit)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcLvdInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcLvdInit->u32ExInputEn = PWC_LVD_EX_INPUT_DISABLE;
        pstcLvdInit->u32DetectEdge = PWC_LVD_DETECT_EDGE_RISING;
        pstcLvdInit->u32VoltageThreshold = PWC_LVD_VOL_BELOW4P29_OR_ABOVE4P39;
        pstcLvdInit->u32Filter = PWC_LVD_FILTER_DISABLE;
        pstcLvdInit->u32TrigEvent = PWC_LVD_TRIG_DISABLE;
        pstcLvdInit->u32ComparerOutputEn = PWC_LVD_COMPARER_OUTPUT_DISABLE;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the Low Voltage Detector(LVD).
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_LVD_Cmd(uint8_t u8Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_LVD_REG_WRITE_ENABLE();
    if (PWC_LVD1 == u8Unit)
    {
        bM4_PWR->LVDCR0_b.L1EN = enNewState;
    }
    else
    {
        bM4_PWR->LVDCR0_b.L2EN = enNewState;
    }
    PWC_LVD_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or disable the LVD compare result output.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD0: PWC LVD unit 0
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD CmpOutput.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_LVD_CmpOutputCmd(uint8_t u8Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_LVD_REG_WRITE_ENABLE();
    switch (u8Unit)
    {
    case PWC_LVD0:
        bM4_PWR->LVDCSR1_b.L0CMPOE = enNewState;
        break;
    case PWC_LVD1:
        bM4_PWR->LVDCR0_b.L1CMPOE = enNewState;
        break;
    case PWC_LVD2:
        bM4_PWR->LVDCR0_b.L2CMPOE = enNewState;
        break;
    default:
        break;
    }
    PWC_LVD_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or disable the LVD trigger event.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @param  [in] enNewState      The new state of the LVD trigger event.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_LVD_TrigEventCmd(uint8_t u8Unit, en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_LVD_REG_WRITE_ENABLE();
    if (PWC_LVD1 == u8Unit)
    {
        bM4_PWR->LVDCR0_b.L1IRE = enNewState;
    }
    else
    {
        bM4_PWR->LVDCR0_b.L2IRE = enNewState;
    }
    PWC_LVD_REG_WRITE_DISABLE();
}

/**
 * @brief  Set LVD compare result.
 * @note   The parameter PWC_LVD_VOL_EX_INPUT only PWC_LVD2 is valid.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @param  [in] u32VolThreshold         Compare voltage threshold
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD_VOL_BELOW4P29_OR_ABOVE4P39:   LVD voltage threshold less than 4.29 or higher than 4.39
 *           @arg PWC_LVD_VOL_BELOW4P14_OR_ABOVE4P23:   LVD voltage threshold less than 4.14 or higher than 4.23
 *           @arg PWC_LVD_VOL_BELOW4P02_OR_ABOVE4P14:   LVD voltage threshold less than 4.02 or higher than 4.14
 *           @arg PWC_LVD_VOL_BELOW3P84_OR_ABOVE3P96:   LVD voltage threshold less than 3.84 or higher than 3.96
 *           @arg PWC_LVD_VOL_BELOW3P10_OR_ABOVE3P20:   LVD voltage threshold less than 3.10 or higher than 3.20
 *           @arg PWC_LVD_VOL_BELOW3P00_OR_ABOVE3P09:   LVD voltage threshold less than 3.00 or higher than 3.09
 *           @arg PWC_LVD_VOL_BELOW2P90_OR_ABOVE2P99:   LVD voltage threshold less than 2.90 or higher than 2.99
 *           @arg PWC_LVD_VOL_BELOW2P79_OR_ABOVE2P87:   LVD voltage threshold less than 2.79 or higher than 2.87
 *           @arg PWC_LVD_VOL_BELOW2P68_OR_ABOVE2P75:   LVD voltage threshold less than 2.68 or higher than 2.75
 *           @arg PWC_LVD_VOL_BELOW2P34_OR_ABOVE2P41:   LVD voltage threshold less than 2.34 or higher than 2.41
 *           @arg PWC_LVD_VOL_BELOW2P14_OR_ABOVE2P21:   LVD voltage threshold less than 2.14 or higher than 2.21
 *           @arg PWC_LVD_VOL_BELOW1P94_OR_ABOVE2P01:   LVD voltage threshold less than 1.94 or higher than 2.01
 *           @arg PWC_LVD_VOL_BELOW1P84_OR_ABOVE1P90:   LVD voltage threshold less than 1.84 or higher than 1.90
 *           @arg PWC_LVD_VOL_EX_INPUT:                 LVD use external input reference voltage
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t PWC_LVD_SetVolThreshold(uint8_t u8Unit, uint32_t u32VolThreshold)
{
    en_result_t enRet = Ok;

    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));
    DDL_ASSERT(IS_VALID_PWC_LVD_VOL_THRESHOLD(u32VolThreshold));

    if ((PWC_LVD1 == u8Unit) && (PWC_LVD_VOL_EX_INPUT == u32VolThreshold))
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        PWC_LVD_REG_WRITE_ENABLE();
        if (PWC_LVD1 == u8Unit)
        {
            MODIFY_REG32(M4_PWR->LVDCR0, PWR_LVDCR0_L1LVL, u32VolThreshold);
        }
        else
        {
            MODIFY_REG32(M4_PWR->LVDCR0, PWR_LVDCR0_L2LVL, (u32VolThreshold<<PWC_LVD2_CONFIG_SHIFT));
        }
        PWC_LVD_REG_WRITE_DISABLE();
    }

    return enRet;
}

/**
 * @brief  Get LVD compare result.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD0: PWC LVD unit 0
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @retval An uint8_t value:
 *           - PWC_LVD_COMPARE_VCC_LESS_LVD:    VCC < VLVD
 *           - PWC_LVD_COMPARE_VCC_GREATER_LVD: VCC = VLVD or LVD is invalid
 */
uint8_t PWC_LVD_GetCmpResult(uint8_t u8Unit)
{
    uint8_t u8Result = PWC_LVD_COMPARE_VCC_LESS_LVD;

    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_SPECIAL_UNIT(u8Unit));

    if (Reset != (READ_REG8_BIT(M4_PWR->LVDCSR1, (PWR_LVDCSR1_L1MON << u8Unit))))
    {
        u8Result = PWC_LVD_COMPARE_VCC_GREATER_LVD;
    }

    return u8Result;

}

/**
 * @brief  Get LVD detect flag.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_LVD_GetDetectFlag(uint8_t u8Unit)
{
    en_flag_status_t enFlagSta = Reset;

    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));

    if (Reset != (READ_REG8_BIT(M4_PWR->LVDCSR1, (PWR_LVDCSR1_L1DETF << u8Unit))))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear LVD detect flag.
 * @param  [in] u8Unit                  PWC LVD unit number
 *         This parameter can be one of the following values:
 *           @arg PWC_LVD1: PWC LVD unit 1
 *           @arg PWC_LVD2: PWC LVD unit 2
 * @retval None
 */
void PWC_LVD_CleaDetectFlag(uint8_t u8Unit)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_LVD_NORMAL_UNIT(u8Unit));

    PWC_LVD_REG_WRITE_ENABLE();
    CLEAR_REG8_BIT(M4_PWR->LVDCSR1, (PWR_LVDCSR1_L1DETF << u8Unit));
    PWC_LVD_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or disable the Ram Parity error trigger reset.
 * @param  [in] enNewState      The new state of the Ram Parity error trigger reset.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_RamParityErrResetCmd(en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_POWER_REG_WRITE_ENABLE();
    bM4_PWR->RAMCR_b.RPERDIS = !enNewState;
    PWC_POWER_REG_WRITE_DISABLE();
}

/**
 * @brief  Get the ram parity check flag.
 * @param  [in] u16Flag                 PWC Ram Parity flag type
 *         This parameter can be one of the following values:
 *           @arg PWC_FLAG_CACHE_PARITY_ERR:    Cache Ram parity error flag
 *           @arg PWC_FLAG_HRAM_PARITY_ERR:     High RAM parity error flag
 *           @arg PWC_FLAG_RAM_PARITY_ERR:      RAM parity error flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t PWC_GetRamParityFlag(uint8_t u8Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_RAM_PARITY_FLAG(u8Flag));

    if (Reset != (READ_REG8_BIT(M4_PWR->RAMCR, u8Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear the ram parity check flag.
 * @param  [in] u16Flag                 PWC Ram Parity flag type
 *         This parameter can be one or any combination of the following values:
 *           @arg PWC_FLAG_CACHE_PARITY_ERR:    Cache Ram parity error flag
 *           @arg PWC_FLAG_HRAM_PARITY_ERR:     High RAM parity error flag
 *           @arg PWC_FLAG_RAM_PARITY_ERR:      RAM parity error flag
 * @retval None
 */
void PWC_ClearRamParityFlag(uint8_t u8Flag)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_VALID_PWC_RAM_PARITY_FLAG(u8Flag));

    PWC_POWER_REG_WRITE_ENABLE();
    CLEAR_REG8_BIT(M4_PWR->RAMCR, u8Flag);
    PWC_POWER_REG_WRITE_DISABLE();
}

/**
 * @brief  Enable or disable the Debug.
 * @param  [in] enNewState      The new state of the Debug.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void PWC_DebugCmd(en_functional_state_t enNewState)
{
    /* Parameter valid check */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    PWC_POWER_REG_WRITE_ENABLE();
    bM4_PWR->DBGC_b.DBGEN = enNewState;
    PWC_POWER_REG_WRITE_DISABLE();
}

/**
 * @}
 */

#endif  /* DDL_PWC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
