/**
 *******************************************************************************
 * @file  exint_nmi/source/main.c
 * @brief Main program EXINT_NMI for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-05       Zhangxl         First version
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
 * @addtogroup EXINT_NMI_SWI
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* KEY1 EXINT5 */
#define KEY1_INT_CH     (EXINT_CH05)
#define KEY1_INT_PORT   (GPIO_PORT_0)
#define KEY1_INT_PIN    (GPIO_PIN_2)
#define KEY1_INT_SRC    (INT_PORT_EIRQ5)
#define KEY1_INT_IRQn   (ExInt5_IRQn)
/* KEY2 EXINT4 */
#define KEY2_INT_CH     (EXINT_CH04)
#define KEY2_INT_PORT   (GPIO_PORT_0)
#define KEY2_INT_PIN    (GPIO_PIN_1)
#define KEY2_INT_SRC    (INT_PORT_EIRQ4)
#define KEY2_INT_IRQn   (ExInt4_IRQn)
/* KEY3 NMI Pin */
#define KEY3_INT_PORT   (GPIO_PORT_E)
#define KEY3_INT_PIN    (GPIO_PIN_2)
/* KEY4 EXINT7 */
#define KEY4_INT_CH     (EXINT_CH07)
#define KEY4_INT_PORT   (GPIO_PORT_D)
#define KEY4_INT_PIN    (GPIO_PIN_7)
#define KEY4_INT_SRC    (INT_PORT_EIRQ7)
#define KEY4_INT_IRQn   (Int000_IRQn)
/* Software interrupt Ch.14 */
#define SWI_CH          (INTC_SWIER_SWIE14)
#define SWI_IRQn        (SwInt14_IRQn)

#define LED_R_PORT      (GPIO_PORT_A)
#define LED_G_PORT      (GPIO_PORT_A)
#define LED_B_PORT      (GPIO_PORT_1)

#define LED_R_PIN       (GPIO_PIN_4)
#define LED_G_PIN       (GPIO_PIN_5)
#define LED_B_PIN       (GPIO_PIN_0)

#define LED_R_ON()      (GPIO_ResetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_ON()      (GPIO_ResetPins(LED_G_PORT, LED_G_PIN))
#define LED_B_ON()      (GPIO_ResetPins(LED_B_PORT, LED_B_PIN))

#define LED_R_OFF()     (GPIO_SetPins(LED_R_PORT, LED_R_PIN))
#define LED_G_OFF()     (GPIO_SetPins(LED_G_PORT, LED_G_PIN))
#define LED_B_OFF()     (GPIO_SetPins(LED_B_PORT, LED_B_PIN))

#define LED_R_TOGGLE()  (GPIO_TogglePins(LED_R_PORT, LED_R_PIN))
#define LED_G_TOGGLE()  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))
#define LED_B_TOGGLE()  (GPIO_TogglePins(LED_B_PORT, LED_B_PIN))
#define LED_RGB_TOGGLE()                                                        \
                        {LED_R_TOGGLE();LED_G_TOGGLE();LED_B_TOGGLE();}

#define LED_RGB_ON()    {LED_R_ON();LED_G_ON();LED_B_ON();}
#define LED_RGB_OFF()   {LED_R_OFF();LED_G_OFF();LED_B_OFF();}

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
static void LED_Init(void);
static void KEY4_IrqCallback(void);
static void NMI_IrqCallback(void);
static void KEY1_Init(void);
static void KEY2_Init(void);
static void KEY3_Init(void);
static void KEY4_Init(void);
static void SWI_Init(void);


/**
 * @brief  KEY1 (External interrupt Ch.5) ISR
 * @param  None
 * @retval None
 */
void EXINT05_SWINT13_IrqHandler(void)
{
   if (Set == EXINT_GetExIntSrc(EXINT_CH05))
   {
        EXINT_ClrExIntSrc(EXINT_CH05);
        LED_R_TOGGLE();
   }
}

/**
 * @brief  KEY2 (External interrupt Ch.4) ISR
 * @param  None
 * @retval None
 */
void EXINT04_SWINT12_IrqHandler(void)
{
   if (Set == EXINT_GetExIntSrc(EXINT_CH04))
   {
        EXINT_ClrExIntSrc(EXINT_CH04);
        LED_G_TOGGLE();
   }
}

/**
 * @brief  KEY4 (External interrupt Ch.7) callback function
 * @param  None
 * @retval None
 */
static void KEY4_IrqCallback(void)
{
   if (Set == EXINT_GetExIntSrc(KEY4_INT_CH))
   {
        EXINT_ClrExIntSrc(KEY4_INT_CH);
        LED_RGB_TOGGLE();
   }
}

/**
 * @brief  Software interrupt Ch.14 callback function
 * @param  None
 * @retval None
 */
void EXINT06_SWINT14_IrqHandler(void)
{
    INTC_SWICmd(INTC_SWIER_SWIE14, Disable);
    LED_RGB_TOGGLE();
}

/**
 * @brief  NMI IRQ callback function
 * @param  None
 * @retval None
 */
static void NMI_IrqCallback(void)
{
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_NMIFR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_NMIFR);
        LED_B_TOGGLE();
    }
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_SWDTFR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_SWDTFR);
    }
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_PVD1FR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_PVD1FR);
    }
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_PVD2FR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_PVD2FR);
    }
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_XTALSTPFR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_XTALSTPFR);
    }
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_REPFR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_REPFR);
    }
    if (Set == NMI_GetNmiSrc(INTC_NMIFR_WDTFR))
    {
        NMI_ClrNmiSrc(INTC_NMIFR_WDTFR);
    }
}

/**
 * @brief  LED initialize.
 * @param  None
 * @retval None
 */
static void LED_Init(void)
{
    stc_gpio_init_t stcGpioInit;

    /* RGB LED initialize */
    GPIO_StructInit(&stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    GPIO_Init(LED_B_PORT, LED_B_PIN, &stcGpioInit);

    /* "Turn off" LED before set to output */
    LED_RGB_OFF();

    /* Output enable */
    GPIO_OE(LED_R_PORT, LED_R_PIN, Enable);
    GPIO_OE(LED_G_PORT, LED_G_PIN, Enable);
    GPIO_OE(LED_B_PORT, LED_B_PIN, Enable);
}

/**
 * @brief  KEY1 initialize.
 * @param  None
 * @retval None
 */
static void KEY1_Init(void)
{
    stc_exint_config_t stcExIntInit;
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    /* KEY1, KEY2, KEY4 initialize */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(KEY1_INT_PORT, KEY1_INT_PIN, &stcGpioInit);

    EXINT_StructInit(&stcExIntInit);

    /* EXINT Channel 5 (KEY1) configure */
    stcExIntInit.u32ExIntCh     = KEY1_INT_CH;
    stcExIntInit.u32ExIntFAE    = EXINT_FILTER_A_ON;
    stcExIntInit.u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV1;
    stcExIntInit.u32ExIntFBE    = EXINT_FILTER_B_ON;
    stcExIntInit.u32ExIntFBTime = NMI_EXINT_FBTIM_2US;
    stcExIntInit.u32ExIntLvl    = EXINT_TRIGGER_FALLING;
    EXINT_Init(&stcExIntInit);

    /* NVIC configure */
    /* IRQ013_Handler, fixed entry for EXINT5(KEY1) */
    NVIC_ClearPendingIRQ(KEY1_INT_IRQn);
    NVIC_SetPriority(KEY1_INT_IRQn, DDL_IRQ_PRIORITY_14);
    NVIC_EnableIRQ(KEY1_INT_IRQn);
}

/**
 * @brief  KEY2 initialize.
 * @param  None
 * @retval None
 */
static void KEY2_Init(void)
{
    stc_exint_config_t stcExIntInit;
    stc_gpio_init_t stcGpioInit;

    GPIO_StructInit(&stcGpioInit);
    /* KEY2 initialize */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(KEY2_INT_PORT, KEY2_INT_PIN, &stcGpioInit);

    EXINT_StructInit(&stcExIntInit);

    /* EXINT Channel 4 (KEY2) configure */
    stcExIntInit.u32ExIntCh     = KEY2_INT_CH;
    stcExIntInit.u32ExIntFAE    = EXINT_FILTER_A_ON;
    stcExIntInit.u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV8;
    stcExIntInit.u32ExIntFBE    = EXINT_FILTER_B_ON;
    stcExIntInit.u32ExIntFBTime = NMI_EXINT_FBTIM_2US;
    stcExIntInit.u32ExIntLvl    = EXINT_TRIGGER_RISING;
    EXINT_Init(&stcExIntInit);

    /* IRQ012_Handler, fixed entry for EXINT4(KEY2) */
    NVIC_ClearPendingIRQ(KEY2_INT_IRQn);
    NVIC_SetPriority(KEY2_INT_IRQn, DDL_IRQ_PRIORITY_15);
    NVIC_EnableIRQ(KEY2_INT_IRQn);
}

/**
 * @brief  KEY3 initialize.
 * @param  None
 * @retval None
 */
static void KEY3_Init(void)
{
    stc_nmi_config_t stcNmiInit;

    /* NMI Pin interrupt configure */
    NMI_StructInit(&stcNmiInit);
    stcNmiInit.u32NmiFAE        = NMI_FILTER_A_ON;
    stcNmiInit.u32NmiFAClk      = NMI_FACLK_HCLK_DIV64;
    stcNmiInit.u32NmiFBE        = NMI_FILTER_B_ON;
    stcNmiInit.u32NmiFBTime     = NMI_EXINT_FBTIM_2US;
    stcNmiInit.u32NmiTigger     = NMI_TRIGGER_FALLING;
    stcNmiInit.u32NmiSrc        = NMI_SRC_NMI_PIN;
    stcNmiInit.pfnNmiCallback   = &NMI_IrqCallback;
    NMI_Init(&stcNmiInit);
}

/**
 * @brief  KEY4 initialize.
 * @param  None
 * @retval None
 */
static void KEY4_Init(void)
{
    uint8_t u8Ret;
    stc_exint_config_t stcExIntInit;
    stc_gpio_init_t stcGpioInit;
    stc_irq_signin_config_t stcIrqSignin;

    GPIO_StructInit(&stcGpioInit);
    /* KEY4 initialize */
    stcGpioInit.u16ExInt = PIN_EXINT_ON;
    GPIO_Init(KEY4_INT_PORT, KEY4_INT_PIN, &stcGpioInit);

    EXINT_StructInit(&stcExIntInit);

    /* EXINT Channel 7 (KEY4) configure */
    stcExIntInit.u32ExIntCh     = KEY4_INT_CH;
    stcExIntInit.u32ExIntFAE    = EXINT_FILTER_A_ON;
    stcExIntInit.u32ExIntFAClk  = EXINT_FACLK_HCLK_DIV32;
    stcExIntInit.u32ExIntFBE    = EXINT_FILTER_B_ON;
    stcExIntInit.u32ExIntFBTime = NMI_EXINT_FBTIM_2US;
    stcExIntInit.u32ExIntLvl    = EXINT_TRIGGER_BOTH;
    EXINT_Init(&stcExIntInit);

    /* Set IRQ handler 0 as the external interrupt Channel 7 (KEY4) entry */
    stcIrqSignin.enIRQn       = KEY4_INT_IRQn;
    stcIrqSignin.enIntSrc     = KEY4_INT_SRC;
    stcIrqSignin.pfnCallback  = &KEY4_IrqCallback;
    u8Ret = INTC_IrqSignIn(&stcIrqSignin);
    if (Ok != u8Ret)
    {
        // check parameter
        while(1)
        {
            ;
        }
    }
    /* IRQ000_Handler for KEY4 */
    NVIC_ClearPendingIRQ(KEY4_INT_IRQn);
    NVIC_SetPriority(KEY4_INT_IRQn, DDL_IRQ_PRIORITY_03);
    NVIC_EnableIRQ(KEY4_INT_IRQn);
}

/**
 * @brief  Software interrupt initialize.
 * @param  None
 * @retval None
 */
static void SWI_Init(void)
{
    /* Software interrupt Ch.14 */
    /* NVIC configure */
    NVIC_ClearPendingIRQ(SWI_IRQn);
    NVIC_SetPriority(SWI_IRQn, DDL_IRQ_PRIORITY_15);
    NVIC_EnableIRQ(SWI_IRQn);
}

/**
 * @brief  Main function of EXINT_NMI project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    LED_Init();

    KEY1_Init();
    KEY2_Init();
    KEY3_Init();
    KEY4_Init();

    SWI_Init();
    /* Software interrupt will occur once enable */
    /* Common entry for EXINT06 and SWINT_14*/
    INTC_SWICmd(SWI_CH, Enable);

    while (1)
    {
        ;// wait KEY1/KEY2/KEY3(NMI)/KEY4 key pressed
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
