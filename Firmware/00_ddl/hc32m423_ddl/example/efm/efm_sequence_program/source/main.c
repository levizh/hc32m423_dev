/**
 *******************************************************************************
 * @file  efm/efm_sequence_program/source/main.c
 * @brief Main program of EFM for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-05-20       Heqb          First version
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
#include "hc32_ddl.h"

/**
 * @addtogroup HC32M423_DDL_Examples
 * @{
 */

/**
 * @addtogroup EFM_Sequence_Program
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

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
 * @brief  Main function of EFM project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    stc_efm_cfg_t stcEfmCfg;
    uint8_t u8TestBuf[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};

    /* Unlock EFM. */
    EFM_Unlock();
    /* EFM default config. */
    EFM_StrucInit(&stcEfmCfg);
    stcEfmCfg.u32BusStatus = EFM_BUS_RELEASE;
    EFM_Init(&stcEfmCfg);
    /* Enable flash. */
    EFM_Cmd(EFM_ON);
    /* Wait flash ready. */
    while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
    {
        ;
    }
    /* Erase sector 15 140. */
    EFM_SectorErase(EFM_SECTOR15_ADRR);
    EFM_SectorErase(EFM_SECTOR140_ADRR);

    /* Sequence program. */
    EFM_SequenceProgram(EFM_SECTOR15_ADRR, sizeof(u8TestBuf) - 2U, u8TestBuf);

    /* Sequence program. */
    EFM_SequenceProgram(EFM_SECTOR140_ADRR, sizeof(u8TestBuf), u8TestBuf);

    /* Chip Erase */
    EFM_ChipErase();

    /* Lock EFM. */
    EFM_Lock();

    while(1)
    {
        ;
    }
}

/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
