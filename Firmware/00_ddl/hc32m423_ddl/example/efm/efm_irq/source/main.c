/**
 *******************************************************************************
 * @file  efm/efm_irq/source/main.c
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
 * @addtogroup EFM_Irq
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define EFM_IRQn                (EfmErr_IRQn)

#define EFM_WIN_START_ADDR      (EFM_SECTOR10_ADRR)
#define EFM_WIN_END_ADDR        (EFM_SECTOR12_ADRR)

#define LED_R_PORT              (GPIO_PORT_A)
#define LED_G_PORT              (GPIO_PORT_A)

#define LED_R_PIN               (GPIO_PIN_4)
#define LED_G_PIN               (GPIO_PIN_5)

#define LED_R_ON()              (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_ON()              (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))

#define LED_R_OFF()             (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_OFF()             (GPIO_SetPins(LED_G_PORT, LED_G_PIN))

#define LED_RG_ON()             {LED_R_ON();LED_G_ON();}
#define LED_RG_OFF()            {LED_R_OFF();LED_G_OFF();}

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void IRQ_Config(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Led Init
 * @param  None
 * @retval None
 */
static void Led_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* LED initialize */
    GPIO_StructInit(&stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);

    /* "Turn off" LED before set to output */
    LED_RG_OFF();

    /* Output enable */
    GPIO_OE(LED_R_PORT, LED_R_PIN, Enable);
    GPIO_OE(LED_G_PORT, LED_G_PIN, Enable);
}

/**
 * @brief  Main function of EFM project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t u32TestData = 0x5A5A5A5Au;
    uint32_t u32Addr;

    /* Led Init */
    Led_Init();
    LED_G_ON();
    /*Configure IRQ handler && NVIC*/
    IRQ_Config();
    /* Unlock EFM. */
    EFM_Unlock();
    /* Enable EFM. */
    EFM_Cmd(EFM_ON);
    /* Wait flash ready. */
    while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY))
    {
        ;
    }
    /* Set windows protect address. */
    EFM_SetWinProtectAddr(EFM_WIN_START_ADDR, EFM_WIN_END_ADDR);
    /* Enable program & erase err interrupt. */
    EFM_InterruptCmd(EFM_INT_PEERR, Enable);
    /* Erase sector 10. */
    EFM_SectorErase(EFM_SECTOR10_ADRR);
     /* program between windows address. */
    u32Addr = EFM_WIN_START_ADDR;
    EFM_ProgramWord(u32Addr,u32TestData);
    /* SW2 */
    while(Pin_Reset != GPIO_ReadInputPortPin(GPIO_PORT_0, GPIO_PIN_2))
    {
        ;
    }
    /* program out of windows address. */
    u32Addr = EFM_WIN_START_ADDR - 4UL;
    EFM_ProgramWord(u32Addr,u32TestData);

    /* Lock EFM. */
    EFM_Lock();

    while(1)
    {
        ;
    }
}

/**
 * @brief  EFM Program/Erase Error IRQ callback
 * @param  None
 * @retval None
 */
void EFM_PgmEraseErr_IrqHandler(void)
{

    LED_G_OFF();
    LED_R_ON();

    EFM_Unlock();
    /* Clear Flag */
    EFM_ClearFlag(EFM_CLR_FLAG_PEPRTERRCLR);
    EFM_Lock();
}

/**
 * @brief  Configure IRQ handler && NVIC.
 * @param  None
 * @retval None
 */
static void IRQ_Config(void)
{
    stc_irq_regi_config_t stcIrqRegCfg;

    /* Register IRQ handler && configure NVIC. */
    stcIrqRegCfg.enIRQn = EFM_IRQn;
    NVIC_ClearPendingIRQ(stcIrqRegCfg.enIRQn);
    NVIC_SetPriority(stcIrqRegCfg.enIRQn, DDL_IRQ_PRIORITY_02);
    NVIC_EnableIRQ(stcIrqRegCfg.enIRQn);
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
