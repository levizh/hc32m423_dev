/**
 *******************************************************************************
 * @file  hc32m423_tmr0.c
 * @brief This file provides firmware functions to manage the TMR0
 *        (TMR0).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-01-01       Heqb          First version
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
#include "hc32m423_tmr0.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMR0 TMR0
 * @brief TMR0 Driver Library
 * @{
 */

#if (DDL_TMR0_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR0_Local_Macros TMR0 Local Macros
 * @{
 */
#define TMR0_BCONR_INIT_MSK             (TMR0_BCONR_CAPMDA | TMR0_BCONR_CKDIVA | \
                                         TMR0_BCONR_HICPA  | TMR0_BCONR_HSTAA  | \
                                         TMR0_BCONR_HSTPA  | TMR0_BCONR_HCLEA  | \
                                         TMR0_BCONR_SYNCLKA)

#define TMR0_CHB_POS                    (16U)
#define TMR0_OFFSET(ch)                 ((ch) * TMR0_CHB_POS)
/**
 * @defgroup TMR0_Check_Parameters_Validity TMR0 Check Parameters Validity
 * @{
 */
#define IS_VALID_UNIT(x)                                                       \
(   ((x) == M4_TMR01)                              ||                          \
    ((x) == M4_TMR02))

#define IS_VALID_CHANNEL(x)                                                    \
(   ((x) == TMR0_CH_A)                             ||                          \
    ((x) == TMR0_CH_B))

#define IS_VALID_CLK_DIVISION(x)                                               \
(   ((x) == TMR0_CLK_DIV1)                         ||                          \
    ((x) == TMR0_CLK_DIV2)                         ||                          \
    ((x) == TMR0_CLK_DIV4)                         ||                          \
    ((x) == TMR0_CLK_DIV8)                         ||                          \
    ((x) == TMR0_CLK_DIV16)                        ||                          \
    ((x) == TMR0_CLK_DIV32)                        ||                          \
    ((x) == TMR0_CLK_DIV64)                        ||                          \
    ((x) == TMR0_CLK_DIV128)                       ||                          \
    ((x) == TMR0_CLK_DIV256)                       ||                          \
    ((x) == TMR0_CLK_DIV512)                       ||                          \
    ((x) == TMR0_CLK_DIV1024))

#define IS_VALID_CLK_SRC(x)                                                    \
(   ((x) == TMR0_CLK_SRC_HCLK)                     ||                          \
    ((x) == TMR0_CLK_SRC_INTHWTRIG))

#define IS_VALID_HWTRG_FUNC(x)                                                 \
(   ((x) | TMR0_HETRG_FUNC_MASK) == TMR0_HETRG_FUNC_MASK)

#define IS_VALID_TMR0_FUNC(x)                                                  \
(   ((x) == TMR0_FUNC_CMP)                         ||                          \
    ((x) == TMR0_FUNC_CAPTURE))

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
 * @defgroup TMR0_Local_Functions TMR0 Local Functions
 * @{
 */

/**
 * @defgroup TMR0_Global_Functions TMR0 Global Functions
 * @{
 */

/**
 * @brief  Tmr0 peripheral initialization stucture clear
 * @param  [in] pstcInitStruct    Tmr0 function structure
 *   @arg  See the structure definition for @ref stc_tmr0_init_t
 * @retval Ok: Success
 * @retval ErrorInvalidParameter: Parameter error
 */
en_result_t TMR0_StructInit(stc_tmr0_init_t* pstcInitStruct)
{
    en_result_t enRet = ErrorInvalidParameter;
    
    if (pstcInitStruct != NULL)
    {
        pstcInitStruct->u32ClockDivision = TMR0_CLK_DIV1;
        pstcInitStruct->u32ClockSource = TMR0_CLK_SRC_HCLK;
        pstcInitStruct->u32Tmr0Func = TMR0_FUNC_CMP;
        pstcInitStruct->u16CmpValue = 0xFFFFU;
        pstcInitStruct->u32HwTrigFunc = TMR0_HWTRG_FUNC_NONE;
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Tmr0 peripheral function initialize
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] pstcTmr0Init     TMR0 function base parameter structure
 *   @arg  See the structure definition for @ref stc_tim0_init_t
 * @retval Ok: Success
 *         ErrorInvalidParameter: Parameter error
 * @note   In capture mode, don't need configure member u32HwTrigFunc and u16CmpValue
 */
en_result_t TMR0_Init(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
                              const stc_tmr0_init_t* pstcTmr0Init)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Temp;
    uint32_t u32CMPRAddr;
    uint32_t u32CNTRAddr;
    if (pstcTmr0Init != NULL)
    {
        DDL_ASSERT(IS_VALID_UNIT(TMR0x));
        DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
        DDL_ASSERT(IS_VALID_CLK_DIVISION(pstcTmr0Init->u32ClockDivision));
        DDL_ASSERT(IS_VALID_CLK_SRC(pstcTmr0Init->u32ClockSource));
        DDL_ASSERT(IS_VALID_TMR0_FUNC(pstcTmr0Init->u32Tmr0Func));
        DDL_ASSERT(IS_VALID_HWTRG_FUNC(pstcTmr0Init->u32HwTrigFunc));

        u32Temp = (uint32_t)u8Channel * 4UL;
        u32CNTRAddr = (uint32_t)(&TMR0x->CNTAR) + u32Temp;
        u32CMPRAddr = (uint32_t)(&TMR0x->CMPAR) + u32Temp;
        RW_MEM32(u32CNTRAddr) = pstcTmr0Init->u16CntValue;
        RW_MEM32(u32CMPRAddr) = pstcTmr0Init->u16CmpValue;

        u32Temp = pstcTmr0Init->u32ClockDivision \
                  | pstcTmr0Init->u32ClockSource \
                  | pstcTmr0Init->u32HwTrigFunc  \
                  | pstcTmr0Init->u32Tmr0Func;

        u8Channel = TMR0_OFFSET(u8Channel);
        /* Config mode, clock source */
        MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_INIT_MSK << u8Channel), (u32Temp << u8Channel));
        enRet = Ok;
    }
    return enRet;
}

/**
 * @brief  Get Tmr0 status (STFLR)
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval Set: Flag is set
 *         Reset: Flag is reset
 */
en_flag_status_t TMR0_GetStatus(const M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    en_flag_status_t enRet = Reset;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u8Channel = TMR0_OFFSET(u8Channel);
    if (READ_REG32_BIT(TMR0x->STFLR, (TMR0_STFLR_CMFA << u8Channel)) != 0U)
    {
        enRet = Set;
    }
    return enRet;
}

/**
 * @brief  Clear Tmr0 status (STFLR)
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval None
 */
void TMR0_ClearStatus(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{

    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u8Channel = TMR0_OFFSET(u8Channel);
    /*Clear the Flag*/
    CLEAR_REG32_BIT(TMR0x->STFLR, (TMR0_STFLR_CMFA << u8Channel));
}

/**
 * @brief  Command the tmr0 function
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState       Disable or Enable the function
 * @retval None
 */
void TMR0_Cmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
              en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Channel = TMR0_OFFSET(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CSTA <<u8Channel), ((uint32_t)enNewState << TMR0_BCONR_CSTA_POS) << u8Channel);
}

/**
 * @brief  Tmr0 interrupt function command
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] enNewState       Disable or Enable the function
 * @retval None
 */
void TMR0_IntCmd(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, \
                        en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Channel = TMR0_OFFSET(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_INTENA << u8Channel), ((uint32_t)enNewState << TMR0_BCONR_INTENA_POS) << u8Channel);
}

/**
 * @brief  Get Tmr0 counter register
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval The counter register data
 */
uint16_t TMR0_GetCntVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint16_t u16CntVal;
    uint32_t u32CNTRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CNTRAddr = (uint32_t)&TMR0x->CNTAR + (uint32_t)u8Channel * 4UL;
    u16CntVal = (uint16_t)RW_MEM32(u32CNTRAddr);
    return u16CntVal;
}

/**
 * @brief  Write Tmr0 counter register
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u16Value         The data to write to the counter register
 * @retval None
 * @note   Setting the count requires stop tmr0
 */
void TMR0_SetCntVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value)
{
    uint32_t u32CNTRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CNTRAddr = (uint32_t)&TMR0x->CNTAR + (uint32_t)u8Channel * 4UL;
    RW_MEM32(u32CNTRAddr) = (uint32_t)u16Value;
}

/**
 * @brief  Get Tmr0 base compare count register
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @retval The compare register data
 */
uint16_t TMR0_GetCmpReg(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel)
{
    uint16_t u16CmpVal;
    uint32_t u32CMPRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CMPRAddr = (uint32_t)&TMR0x->CMPAR + (uint32_t)u8Channel * 4UL;
    u16CmpVal = (uint16_t)RW_MEM32(u32CMPRAddr);
    return u16CmpVal;
}

/**
 * @brief  Write Tmr0 compare count register
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] u8Channel        TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u16Value         The data to write to the compare register
 * @retval None
 */
void TMR0_SetCmpVal(M4_TMR0_TypeDef* TMR0x, uint8_t u8Channel, uint16_t u16Value)
{
    uint32_t u32CMPRAddr;
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));

    u32CMPRAddr = (uint32_t)&TMR0x->CMPAR + (uint32_t)u8Channel * 4UL;
    RW_MEM32(u32CMPRAddr) = (uint32_t)u16Value;
}

/**
 * @brief  Set clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:               TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32ClkSrc          Specifies the clock source
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_SRC_PCLK1:     Synchronous clock source: PCLK1.
 *   @arg  TMR0_CLK_SRC_INTHWTRIG: Synchronous clock source: Hardware Trigger Event.
 * @retval None.
 */
void TMR0_SetClkSrc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkSrc)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_CLK_SRC(u32ClkSrc));

    u8Channel = TMR0_OFFSET(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_SYNCLKA << u8Channel), (u32ClkSrc << u8Channel));
}

/**
 * @brief  Set the division of the clock source.
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:               TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32ClkDiv          Specifies the clock source division
 * This parameter can be a value of the following:
 *   @arg  TMR0_CLK_DIV1:          Clock source.
 *   @arg  TMR0_CLK_DIV2:          Clock source / 2.
 *   @arg  TMR0_CLK_DIV4:          Clock source / 4.
 *   @arg  TMR0_CLK_DIV8:          Clock source / 8.
 *   @arg  TMR0_CLK_DIV16:         Clock source / 16.
 *   @arg  TMR0_CLK_DIV32:         Clock source / 32.
 *   @arg  TMR0_CLK_DIV64:         Clock source / 64.
 *   @arg  TMR0_CLK_DIV128:        Clock source / 128.
 *   @arg  TMR0_CLK_DIV256:        Clock source / 256.
 *   @arg  TMR0_CLK_DIV512:        Clock source / 512.
 *   @arg  TMR0_CLK_DIV1024:       Clock source / 1024.
 * @retval None.
 */
void TMR0_SetClkDiv(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32ClkDiv)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_CLK_DIVISION(u32ClkDiv));

    u8Channel = TMR0_OFFSET(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CKDIVA << u8Channel), (u32ClkDiv << u8Channel));
}

/**
 * @brief  Set Tmr0 HardWare Trigger Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:               TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_ChannelA or TMR0_ChannelB
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32HWFunc          Select TMR0 hardware trigger function
 * This parameter can be a value of @ref TMR0_HardwareTrigger_Func_define
 * @param  [in] enNewState         Disable or Enable the function
 * @retval None
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_HWTrigCmd(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, \
                           uint32_t u32HWFunc, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_HWTRG_FUNC(u32HWFunc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8Channel = TMR0_OFFSET(u8Channel);
    if(enNewState == Enable)
    {
        SET_REG32_BIT(TMR0x->BCONR, (u32HWFunc << u8Channel));
    }
    else
    {
        CLEAR_REG32_BIT(TMR0x->BCONR, (u32HWFunc << u8Channel));
    }
}

/**
 * @brief  Set Tmr0 Function
 * @param  [in] TMR0x              Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:               TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:               TMR0 unit 2 instance register base
 * @param  [in] u8Channel          TMR0_CH_A or TMR0_CH_B
 *   @arg  TMR0_CH_A.
 *   @arg  TMR0_CH_B.
 * @param  [in] u32Func            Select TMR0 function
 *   @arg  TMR0_FUNC_CMP:          Select the Compare function for TMR0
 *   @arg  TMR0_FUNC_CAP:          Select the Capture function for TMR0
 * @retval None
 * @note   In asynchronous clock, continuous operation of the BCONR register requires waiting for 3 asynchronous clocks.
 */
void TMR0_SetFunc(M4_TMR0_TypeDef *TMR0x, uint8_t u8Channel, uint32_t u32Func)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    DDL_ASSERT(IS_VALID_CHANNEL(u8Channel));
    DDL_ASSERT(IS_VALID_TMR0_FUNC(u32Func));

    u8Channel = TMR0_OFFSET(u8Channel);
    MODIFY_REG32(TMR0x->BCONR, (TMR0_BCONR_CAPMDA << u8Channel), (u32Func << u8Channel));
}

/**
 * @brief  De-Initialize TMR0 function
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *  @arg M4_TMR01               TMR0 unit 1 instance register base
 *  @arg M4_TMR02               TMR0 unit 2 instance register base
 *
 * @retval None
 */
void TMR0_DeInit(M4_TMR0_TypeDef* TMR0x)
{
    WRITE_REG32(TMR0x->CMPAR, 0x0000FFFFUL);
    WRITE_REG32(TMR0x->CMPBR, 0x0000FFFFUL);
    WRITE_REG32(TMR0x->CNTAR, 0UL);
    WRITE_REG32(TMR0x->CNTBR, 0UL);
    WRITE_REG32(TMR0x->STFLR, 0UL);
    WRITE_REG32(TMR0x->BCONR, 0UL);
}

/**
 * @brief  Set external trigger source for Tmr0
 * @param  [in] TMR0x            Pointer to TMR0 instance register base.
 * This parameter can be a value of the following:
 *   @arg  M4_TMR01:             TMR0 unit 1 instance register base
 *   @arg  M4_TMR02:             TMR0 unit 2 instance register base
 * @param  [in] enEvent          External event source, @ref en_event_src_t
 * @retval None
 */
void TMR0_SetTriggerSrc(M4_TMR0_TypeDef* TMR0x, en_event_src_t enEvent)
{
    DDL_ASSERT(IS_VALID_UNIT(TMR0x));
    if(TMR0x == M4_TMR01)
    {
        M4_AOS->TMR00_HTSSR = enEvent;
    }
    else
    {
        M4_AOS->TMR01_HTSSR = enEvent;
    }
}

/**
 * @}
 */

#endif /* DDL_TMR0_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
