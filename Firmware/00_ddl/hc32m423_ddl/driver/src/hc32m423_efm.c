/**
 *******************************************************************************
 * @file  hc32m423_efm.c
 * @brief This file provides firmware functions to manage the Embedded Flash
 *        Management unit (EFM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-06       Heqb          First version
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
#include "hc32m423_efm.h"
#include "hc32m423_utility.h"

/**
 * @addtogroup HC32M423_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EFM EFM
 * @brief Embedded Flash Management Driver Library
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Local_Macros EFM Local Macros
 * @{
 */

/**
 * @defgroup EFM_Configuration_Bit_Mask EFM Configuration Bit Mask
 * @{
 */
#define EFM_CHCHE_MASK             (EFM_FRMC_CRST | EFM_FRMC_ICHE | EFM_FRMC_DCHE)
#define EFM_CLR_FLAG_MASK          (EFM_CLR_FLAG_PEWERRCLR | EFM_CLR_FLAG_PEPRTERRCLR | \
                                    EFM_CLR_FLAG_OPTENDCLR | EFM_CLR_FLAG_COLERRCLR   | \
                                    EFM_CLR_FLAG_PGMISMTCHCLR)

/**
 * @}
 */
/**
 * @dexfgroup EFM_Check_Parameters_Validity EFM Check Parameters Validity
 * @{
 */
/*  Parameter validity check for pointer. */
#define IS_VALID_POINTER(x)                     (NULL != (x))

/*  Parameter validity check for flash latency. */
#define IS_VALID_EFM_WAIT_CYCLE(x)                                            \
(   ((x) == EFM_WAIT_CYCLE_0)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_1)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_2)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_3)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_4)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_5)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_6)              ||                                 \
    ((x) == EFM_WAIT_CYCLE_7))

/*  Parameter validity check for operate mode. */
#define IS_VALID_EFM_OPERATE_MD(x)                                            \
(   ((x) == EFM_MODE_PROGRAMSINGLE)        ||                                 \
    ((x) == EFM_MODE_PROGRAMREADBACK)      ||                                 \
    ((x) == EFM_MODE_PROGRAMSEQUENCE)      ||                                 \
    ((x) == EFM_MODE_ERASESECTOR)          ||                                 \
    ((x) == EFM_MODE_ERASECHIP)            ||                                 \
    ((x) == EFM_MODE_READONLY)             ||                                 \
    ((x) == EFM_MODE_READONLY1)            ||                                 \
    ((x) == EFM_MODE_READONLY2))

/*  Parameter validity check for flash interrupt select. */
#define IS_VALID_EFM_INT_SEL(x)                                               \
(   ((x) == EFM_INT_EOP)                   ||                                 \
    ((x) == EFM_INT_PEERR)                 ||                                 \
    ((x) == EFM_INT_RDCOLERR)              ||                                 \
    ((x) == EFM_INT_PEERR_OPTEND)          ||                                 \
    ((x) == EFM_INT_PEERR_RDCOLERR)        ||                                 \
    ((x) == EFM_INT_OPTEND_RDCOLERR)       ||                                 \
    ((x) == EFM_INT_ALL))

/*  Parameter validity check for flash flag. */
#define IS_VALID_EFM_FLAG(x)                                                  \
(   ((x) == EFM_FLAG_PEWERR)               ||                                 \
    ((x) == EFM_FLAG_PEPRTERR)             ||                                 \
    ((x) == EFM_FLAG_PGMISMTCHERR)         ||                                 \
    ((x) == EFM_FLAG_OPTEND)               ||                                 \
    ((x) == EFM_FLAG_COLERR)               ||                                 \
    ((x) == EFM_FLAG_RDY))

/*  Parameter validity check for flash clear flag. */
#define IS_VALID_EFM_CLRFLAG(x)                                               \
(   ((x) == EFM_CLR_FLAG_PEWERRCLR)        ||                                 \
    ((x) == EFM_CLR_FLAG_PEPRTERRCLR)      ||                                 \
    ((x) == EFM_CLR_FLAG_PGMISMTCHCLR)     ||                                 \
    ((x) == EFM_CLR_FLAG_OPTENDCLR)        ||                                 \
    ((x) == EFM_CLR_FLAG_COLERRCLR)        ||                                 \
    ((x) == EFM_CLR_FLAG_MASK))

/*  Parameter validity check for bus state while flash program or erase. */
#define IS_VALID_EFM_BUS_STATUS(x)                                            \
(   ((x) == EFM_BUS_BUSY)                  ||                                 \
    ((x) == EFM_BUS_RELEASE))

/*  Parameter validity check for efm data cache reset function. */
#define IS_VALID_EFM_CACHERST_FUNC(x)                                         \
(   ((x) == EFM_CACHERST_ON)               ||                                 \
    ((x) == EFM_CACHERST_OFF))

/*  Parameter validity check for efm instruction cache function. */
#define IS_VALID_EFM_INSCACHE_FUNC(x)                                         \
(   ((x) == EFM_INSCACHE_ON)               ||                                 \
    ((x) == EFM_INSCACHE_OFF))

/*  Parameter validity check for efm data cache function. */
#define IS_VALID_EFM_DATACACHE_FUNC(x)                                        \
(   ((x) == EFM_DATACACHE_ON)              ||                                 \
    ((x) == EFM_DATACACHE_OFF))

/*  Parameter validity check for efm status . */
#define IS_VALID_EFM_STATUS(x)                                                \
(   ((x) == EFM_ON)                        ||                                 \
    ((x) == EFM_OFF))
/*  Parameter validity check for efm address. */
#define IS_VALID_EFM_ADDR(x)                             ((x) <= EFM_END_ADDR)


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
 * @defgroup EFM_Global_Functions EFM Global Functions
 * @{
 */

/**
 * @brief  EFM unlock.
 * @param  None
 * @retval None
 */
void EFM_Unlock(void)
{
    M4_EFM->FAPRT = EFM_KEY1;
    M4_EFM->FAPRT = EFM_KEY2;
}
/**
 * @brief  EFM Lock.
 * @param  None
 * @retval None
 */
void EFM_Lock(void)
{
    M4_EFM->FAPRT = 0x00001111U;
}

/**
 * @brief  Enable or disable EFM.
 * @param  [in] u32efmstatus       Specifies the flash status.
 *  This parameter can be one of the following values:
 *   @arg  EFM_ON                  EFM Enable
 *   @arg  EFM_OFF                 EFM Disable
 * @retval None
 */
void EFM_Cmd(uint32_t u32efmstatus)
{
    DDL_ASSERT(IS_VALID_EFM_STATUS(u32efmstatus));
    M4_EFM->FSTP = u32efmstatus;
}

/**
 * @brief  Init efm config structure with default value.
 * @param  [in] pstcEfmCfg         The pointer of efm config structure.
 *   @arg u32WaitCycle             Specifies the efm latency.
 *   @arg u32InsCache              Specifies the instruction cache on or off.
 *   @arg u32DataCache             Specifies the data cache on or off.
 *   @arg u32BusStatus             Specifies the bus status busy or release while program & erase.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_StrucInit(stc_efm_cfg_t *pstcEfmCfg)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcEfmCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcEfmCfg->u32WaitCycle = EFM_WAIT_CYCLE_0;
        pstcEfmCfg->u32CacheRst  = EFM_CACHERST_OFF;
        pstcEfmCfg->u32InsCache  = EFM_INSCACHE_OFF;
        pstcEfmCfg->u32DataCache = EFM_DATACACHE_OFF;
        pstcEfmCfg->u32BusStatus = EFM_BUS_BUSY;
    }

    return enRet;
}

/**
 * @brief  Efm Config.
 * @param  [in] pstcEfmCfg         The pointer of efm config structure.
 *   @arg u32WaitCycle             Specifies the efm latency.
 *   @arg u32CacheRst              Specifies the data cache reset on or off.
 *   @arg u32InsCache              Specifies the instruction cache on or off.
 *   @arg u32DataChche             Specifies the data cache on or off.
 *   @arg u32BusStatus             Specifies the bus status busy or release while program & erase.
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg)
{
    en_result_t enRet = Ok;
    /* Check if pointer is NULL */
    if (NULL == pstcEfmCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Param valid check */
        DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(pstcEfmCfg->u32WaitCycle));
        DDL_ASSERT(IS_VALID_EFM_BUS_STATUS(pstcEfmCfg->u32BusStatus));
        DDL_ASSERT(IS_VALID_EFM_CACHERST_FUNC(pstcEfmCfg->u32CacheRst));
        DDL_ASSERT(IS_VALID_EFM_INSCACHE_FUNC(pstcEfmCfg->u32InsCache));
        DDL_ASSERT(IS_VALID_EFM_DATACACHE_FUNC(pstcEfmCfg->u32DataCache));

        /* Config efm. */
        MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT | EFM_FRMC_ICHE | EFM_FRMC_DCHE | EFM_FRMC_CRST,
                     pstcEfmCfg->u32WaitCycle | pstcEfmCfg->u32DataCache |
                     pstcEfmCfg->u32InsCache | pstcEfmCfg->u32CacheRst);
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_BUSHLDCTL, pstcEfmCfg->u32BusStatus);
    }

    return enRet;
}

/**
 * @brief  Set the efm read wait cycles.
 * @param  [in] u32WaitCycle            Specifies the efm read wait cycles.
 *  This parameter can be one of the following values:
 *   @arg  EFM_WAIT_CYCLE_0             Don't insert read wait cycle
 *   @arg  EFM_WAIT_CYCLE_1             Insert 1 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_2             Insert 2 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_3             Insert 3 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_4             Insert 4 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_5             Insert 5 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_6             Insert 6 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_7             Insert 7 read wait cycles
 * @retval None
 */
void EFM_SetWaitCycle(uint32_t u32WaitCycle)
{
    /* Param valid check */
    DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(u32WaitCycle));
    /* Set the code latency value. */
    MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT, u32WaitCycle);
}

/**
 * @brief  Enable or disable the flash data cache reset.
 * @param  [in] enNewState                The new state of the flash data cache reset.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_DataCacheRstCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_CRST);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_CRST);
    }
}

/**
 * @brief  Enable or disable the flash instruction cache.
 * @param  [in] enNewState                The new state of the flash instruction cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_InsCacheCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_ICHE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_ICHE);
    }
}

/**
 * @brief  Enable or disable the flash data cache.
 * @param  [in] enNewState                The new state of the flash data cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_DataCacheCmd(en_functional_state_t enNewState)
{
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_DCHE);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_FRMC_DCHE);
    }
}

/**
 * @brief  Set the FLASH erase program mode .
 * @param  [in] u32PgmMode                  Specifies the FLASH flag to check.
 *  This parameter can be one of the following values:
 *   @arg  EFM_MODE_PROGRAMSINGLE           Program single at a specified address
 *   @arg  EFM_MODE_PROGRAMREADBACK         Program and read back at a specified address
 *   @arg  EFM_MODE_PROGRAMSEQUENCE         Program sequence at sequence address
 *   @arg  EFM_MODE_ERASESECTOR             Sector erase
 *   @arg  EFM_MODE_ERASECHIP               Chip erase
 *   @arg  EFM_MODE_READONLY                Read only
 *   @arg  EFM_MODE_READONLY1               Read only
 *   @arg  EFM_MODE_READONLY2               Read only
 * @retval None
 */
void EFM_SetOperateMode(uint32_t u32PgmMode)
{
    DDL_ASSERT(IS_VALID_EFM_OPERATE_MD(u32PgmMode));

    /* Enable operate mode modified. */
    SET_REG32_BIT(M4_EFM->FWMC, EFM_FWMC_PEMODE);
    /* Set the program or erase mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, u32PgmMode);
    /* Disable operate mode modified. */
    CLEAR_REG32_BIT(M4_EFM->FWMC, EFM_FWMC_PEMODE);
}

/**
 * @brief  Enable or Disable EFM interrupt.
 * @param  [in] u32EfmInt               Specifies the FLASH flag to check.
 *  This parameter can be one of the following values:
 *   @arg  EFM_INT_EOP                  End of EFM Operation Interrupt source
 *   @arg  EFM_INT_PEERR                Program/erase error Interrupt source
 *   @arg  EFM_INT_RDCOLERR             Read collide error Interrupt source
 *   @arg  EFM_INT_PEERR_OPTEND         Program/erase error and End of EFM operation
 *   @arg  EFM_INT_PEERR_RDCOLERR       Program/erase error and Read collide error
 *   @arg  EFM_INT_OPTEND_RDCOLERR      End of EFM operation and Read collide error
 *   @arg  EFM_INT_ALL                  All Interrupt source
 * @param  [in] enNewState              The new state of specified interrupt.
 *  This parameter can be: Enable or Disable.
 * @retval None
 */
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_EFM_INT_SEL(u32EfmInt));

    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FITE, u32EfmInt);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FITE, u32EfmInt);
    }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @param  [in] u32flag                  Specifies the FLASH flag to check.
 *  This parameter can be one of the following values:
 *   @arg  EFM_FLAG_PEWERR               Flash wirte protect error flag.
 *   @arg  EFM_FLAG_PEPRTERR             Flash program protect area error flag.
 *   @arg  EFM_FLAG_PGMISMTCHERR         Flash program miss match flag.
 *   @arg  EFM_FLAG_OPTEND               Flash end of program flag.
 *   @arg  EFM_FLAG_COLERR               Flash read write error flag.
 *   @arg  EFM_FLAG_RDY                  Flash ready flag.
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Interrupt flag is set
 *           - Reset: Interrupt flag is reset
 */
en_flag_status_t EFM_GetFlagStatus(uint32_t u32flag)
{
    DDL_ASSERT(IS_VALID_EFM_FLAG(u32flag));
    return ((0UL == (M4_EFM->FSR & u32flag)) ? Reset :Set);
}

/**
 * @brief  Clear the flash flag.
 * @param  [in] u32Flag                  Specifies the FLASH flag to clear.
 *  This parameter can be one of the following values:
 *   @arg  EFM_FLAG_CLR_PEWERRCLR        Flash wirte protect error flag.
 *   @arg  EFM_FLAG_CLR_PEPRTERRCLR      Flash program protect area error flag.
 *   @arg  EFM_FLAG_CLR_PGMISMTCHCLR     Flash program miss match flag.
 *   @arg  EFM_FLAG_CLR_OPTENDCLR        Flash end of program flag.
 *   @arg  EFM_FLAG_CLR_COLERRCLR        Flash read write error flag.
 * @retval None
 */
void EFM_ClearFlag(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_CLRFLAG(u32Flag));
    SET_REG32_BIT(M4_EFM->FSCLR, u32Flag);
}

/**
 * @brief  Set flash protect area.
 * @param  [in] u32StartAddr                  Start address of protect area.
 * @param  [in] u32EndAddr                    End address of protect area.
 * @retval None
 */
void EFM_SetWinProtectAddr(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32StartAddr));
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32EndAddr));
    /* Set protect area start address */
    MODIFY_REG32(M4_EFM->FPMTSW, EFM_FPMTSW_FPMTSW, u32StartAddr);
    /* Set protect area end address */
    MODIFY_REG32(M4_EFM->FPMTEW, EFM_FPMTEW_FPMTEW, u32EndAddr);
}

/**
 * @brief  Set bus state while flash program or erase.
 * @param  [in] u32Status                 Specifies the new bus status while flash program or erase.
 *  This parameter can be one of the following values:
 *   @arg  EFM_BUS_BUSY                   Bus busy while flash program or erase.
 *   @arg  EFM_BUS_RELEASE                Bus releas while flash program or erase.
 * @retval None
 */
void EFM_SetBusStatus(uint32_t u32Status)
{
    DDL_ASSERT(IS_VALID_EFM_BUS_STATUS(u32Status));

    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_BUSHLDCTL, u32Status);
}

/**
 * @brief  Flash single program mode(word).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 */
en_result_t EFM_ProgramWord(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32tmp = 0U;
    uint32_t u32Timeout = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));

    if(u32Addr % 2U == 0U)
    {
        enRet = Ok;
        /* Clear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get chche status */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK); 
        /* Set single program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSINGLE);
        /* program data. */
        *(uint32_t*)u32Addr = (uint32_t)u32Data;

        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);

        if(u32Data != *(uint32_t*)u32Addr)
        {
            enRet = Error;
        }


        /* Recover CACHE function */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);

    }

    return enRet;
}

/**
 * @brief  Flash single program mode(half word).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u16Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 */
en_result_t EFM_ProgramHalfWord(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32tmp = 0U;
    uint32_t u32Timeout = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    if(u32Addr % 2U == 0U)
    {
        enRet = Ok;
        /* Clear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get chche status */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Set single program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSINGLE);
        /* program data. */
        *(( uint16_t*)u32Addr) = u16Data;

        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
        if(u16Data != *(( uint16_t*)u32Addr))
        {
            enRet = Error;
        }

        /* Recover CACHE function */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);

        }

    return enRet;
}

/**
 * @brief  Flash single program word with read back.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 */
en_result_t EFM_ProgramWordRB(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32tmp = 0U;
    uint32_t u32Timeout = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    if(u32Addr % 2U == 0U)
    {
        enRet = Ok;
        /* Clear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get chche status */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Set single program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMREADBACK);
        /* program data. */
        *(uint32_t*)u32Addr = u32Data;

        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
        if(Set == EFM_GetFlagStatus(EFM_FLAG_PGMISMTCHERR))
        {
            /* clear flag PGMISMTCH */
            EFM_ClearFlag(EFM_CLR_FLAG_PGMISMTCHCLR);
            enRet = Error;
        }

        /* Recover CACHE function */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }

    return enRet;
}

/**
 * @brief  Flash single program half word with read back.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u16Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 */
en_result_t EFM_ProgramHalfWordRB(uint32_t u32Addr, uint16_t u16Data)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32tmp = 0U;
    uint32_t u32Timeout = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    if(u32Addr % 2U == 0U)
    {
        enRet = Ok;
        /* Clear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_PEWERRCLR    | EFM_CLR_FLAG_PEPRTERRCLR | \
                      EFM_CLR_FLAG_PGMISMTCHCLR | EFM_CLR_FLAG_OPTENDCLR   | \
                      EFM_CLR_FLAG_COLERRCLR);
        /* Get chche status */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Set single program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMREADBACK);
        /* program data. */
        *((uint16_t*) u32Addr) = u16Data;

        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
        {
            u32Timeout ++;
            if(u32Timeout > EFM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }

        if(Set == EFM_GetFlagStatus(EFM_FLAG_PGMISMTCHERR))
        {
            /* Clear flag PGMISMTCH */
            EFM_ClearFlag(EFM_CLR_FLAG_PGMISMTCHCLR);
            enRet = Error;
        }

        EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
        /* Recover CACHE function */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }

    return enRet;
}

/**
 * @brief  Flash sequence program.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Len                    The len of specified program data.
 * @param  [in] u8pBuf                    The pointer of specified program data.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - Error: program error
 *           - ErrorInvalidParameter: Invalid parameter
 *           - ErrorTimeout: program error timeout
 * @note  The address should be half word align.
 *        The length has to be a multiple of 2
 */
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, uint8_t *u8pBuf)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;
    uint32_t u32pSrc = (uint32_t )u8pBuf;
    uint32_t u32pDest = (uint32_t )u32Addr;
    uint32_t u32LoopWords = u32Len >> 2U;
    uint32_t u32RemainBytes = u32Len % 4U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_POINTER(u8pBuf));
    if((u32Addr % 2U == 0U) && (u32RemainBytes % 2U == 0U))
    {
        enRet = Ok;
        /* Clear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE status */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Set sequence program mode. */
        EFM_SetOperateMode(EFM_MODE_PROGRAMSEQUENCE);

        /* program data. */
        while(u32LoopWords--)
        {
            *((uint32_t *)u32pDest) = *((uint32_t *)u32pSrc);
            u32pDest += 4U;
            u32pSrc += 4U;
            /* wait operate end. */
            while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND))
            {
                u32Timeout++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* Clear end flag. */
            EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
        }
        if(u32RemainBytes)
        {
            *((uint16_t *)u32pDest) = *((uint16_t *)u32pSrc);
            u32pDest += 2U;
            u32pSrc += 2U;
            /* wait operate end. */
            while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND))
            {
                u32Timeout++;
                if(u32Timeout >= EFM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            /* Clear end flag. */
            EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);

        }

        /* Set read only mode. */
        EFM_SetOperateMode(EFM_MODE_READONLY);

        u32Timeout = 0U;
        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
        {
            u32Timeout ++;
            if(u32Timeout > EFM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* Clear the end of operate flag */
        EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
        /* Recover CACHE */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }
    return enRet;
}

/**
 * @brief  Flash sector erase.
 * @param  [in] u32Addr                   The uncertain(random) address in the specified sector.
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - ErrorTimeout: program error timeout
 */
en_result_t EFM_SectorErase(uint32_t u32Addr)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0U;
    uint32_t u32tmp = 0U;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    if (u32Addr % 2U == 0U)
    {
        enRet = Ok;
        /* Clear the error flag. */
        EFM_ClearFlag(EFM_CLR_FLAG_MASK);
        /* Get CACHE status */
        u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Disable CACHE */
        CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
        /* Set sector erase mode. */
        EFM_SetOperateMode(EFM_MODE_ERASESECTOR);

        *(uint32_t*)u32Addr = (uint32_t)0x0UL;

        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* Clear the end of operate flag */
        EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
        /* Recover CACHE */
        MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);
    }
    return enRet;
}

/**
 * @brief  Flash chip erase.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: program success
 *           - ErrorTimeout: program error timeout
 */
en_result_t EFM_ChipErase(void)
{
    en_result_t enRet = Ok;
    uint32_t u32tmp = 0U;
    uint32_t u32Timeout = 0U;

    /* Clear the error flag. */
    EFM_ClearFlag(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CHCHE_MASK);
    /* Set sector erase mode. */
    EFM_SetOperateMode(EFM_MODE_ERASECHIP);

    *(uint32_t*)0x0UL = (uint32_t)0UL;

    while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Clear the end of operate flag */
    EFM_ClearFlag(EFM_CLR_FLAG_OPTENDCLR);
    /* Recover CACHE */
    MODIFY_REG32(M4_EFM->FRMC, EFM_CHCHE_MASK, u32tmp);

    return enRet;
}

/**
 * @brief  Read unique ID.
 * @param  None
 * @retval An stc_efm_unique_id_t structure value:
 *           - uniqueID0: unique ID 0
 *           - uniqueID1: unique ID 1
 *           - uniqueID2: unique ID 2
 */
stc_efm_unique_id_t EFM_ReadUID(void)
{
    stc_efm_unique_id_t stcUID;

    stcUID.u32UniqueID0 = M4_EFM->UQID0;
    stcUID.u32UniqueID1 = M4_EFM->UQID1;
    stcUID.u32UniqueID2 = M4_EFM->UQID2;
    stcUID.u32UniqueID3 = M4_EFM->UQID3;
    return stcUID;
}

/**
 * @}
 */

#endif  /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
