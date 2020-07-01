/**
 *******************************************************************************
 * @file  adc/adc_01_sa_base/source/main.c
 * @brief Main program ADC base for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-02-03       Wuze            First version
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
 * @addtogroup ADC_Base
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* ADC channels definition for this example. */
#define ADC_SA_NORMAL_CHANNEL       (ADC_CH0 | ADC_CH1)
#define ADC_SA_VOL_CHANNEL          (ADC_CH9)
#define ADC_SA_CHANNEL              (ADC_SA_NORMAL_CHANNEL | ADC_SA_VOL_CHANNEL)
#define ADC_SA_CHANNEL_COUNT        (3u)

#define ADC_AVG_CHANNEL             (ADC_SA_NORMAL_CHANNEL)

/* ADC channel sampling time.        ADC_CH0  ADC_CH1    ADC_CH9
   This depends on the application. */
#define ADC_SA_CHANNEL_SAMPLE_TIME  { 0x20,     0x30,      0x20 }

/* ADC resolution definition. */
#define ADC_RESOLUTION              (ADC_RES_12BIT)

/* ADC accuracy. */
#define ADC_ACCURACY                (1UL << 12U)

/* ADC reference voltage. The voltage of pin VREFH. */
#define ADC_VREF                    (3.3018f)

/* Timeout value definitions. */
#define TIMEOUT_MS                  (10U)

/* Variable voltage channel ADC value definition. */
#define vol_value                   (m_au16AdcSaVal[3U])

/* Debug printing definition. */
#if (DDL_PRINT_ENABLE == DDL_ON)
#define DBG         printf
#else
#define DBG(...)
#endif

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);

static void AdcConfig(void);
static void AdcClockConfig(void);
static void AdcInitConfig(void);
static void AdcChannelConfig(void);

static void AdcSetChannelPinAnalogMode(uint16_t u16Channel);
static void AdcSetPinAnalogMode(uint8_t u8PinNum);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
static uint16_t m_au16AdcSaVal[ADC_SA_CHANNEL_COUNT];

#if (DDL_PRINT_ENABLE == DDL_ON)
static float m_f32Vol;
#endif // #if (DDL_PRINT_ENABLE == DDL_ON)

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @brief  Main function of adc_01_sa_base project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    /* Configure the system clock to HRC32MHz. */
    SystemClockConfig();

#if (DDL_PRINT_ENABLE == DDL_ON)
    /* Initializes UART for debug printing. Baudrate is 115200. */
    DDL_UartInit();
#endif // #if (DDL_PRINT_ENABLE == DDL_ON)

    /* Configures ADC. */
    AdcConfig();

    /***************** Configuration end, application start **************/

    while (1U)
    {
        ADC_PollingSA(m_au16AdcSaVal, ADC_SA_CHANNEL_COUNT, TIMEOUT_MS);
#if (DDL_PRINT_ENABLE == DDL_ON)
        m_f32Vol = ((float)vol_value * ADC_VREF) / ((float)ADC_ACCURACY);
        DBG("\nThe voltage is %.3f.", m_f32Vol);
        DDL_Delay1ms(1000U);
#endif // #if (DDL_PRINT_ENABLE == DDL_ON)
    }
}

/**
 * @brief  Configures a new system clock -- HRC32MHz.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    /* Set EFM read latency when system clock greater than 24MHz. */
    //EFM_SetLatency(EFM_LATENCY_1);
}

/**
 * @brief  ADC configuration, including clock configuration, initial configuration
 *         and channel configuration.
 * @param  None
 * @retval None
 */
static void AdcConfig(void)
{
    AdcClockConfig();
    AdcInitConfig();
    AdcChannelConfig();
}

/**
 * @brief  Configures ADC clock.
 *         The clock of ADC: HRC32MHz / 2 = 16MHz.
 * @param  None
 * @retval None
 */
static void AdcClockConfig(void)
{
    //CLK_SetADClkDiv(CLK_HCLK_DIV2);
}

/**
 * @brief  Initializes ADC.
 * @param  None
 * @retval None
 */
static void AdcInitConfig(void)
{
    stc_adc_init_t stcInit;

    /* Set a default value. */
    ADC_StructInit(&stcInit);

    /* User configurations. */
    //stcInit.u16Resolution = ADC_RESOLUTION;
    
    /* 1. Enable ADC peripheral. */
    //CLK_FcgPeriphClockCmd(CLK_FCG_ADC, Enable);

    /* 2. Initializes ADC. */
    ADC_Init(&stcInit);
}

/**
 * @brief  Configures ADC channel(s).
 * @param  None
 * @retval None
 */
static void AdcChannelConfig(void)
{
    uint8_t au8SplTime[] = ADC_SA_CHANNEL_SAMPLE_TIME;

    /* 1. Set the ADC pin to analog input mode. */
    AdcSetChannelPinAnalogMode(ADC_SA_CHANNEL);

    /* 2. Enable ADC channels. */
    ADC_ChannelCmd(ADC_SEQ_A, ADC_SA_CHANNEL, au8SplTime, Enable);

    /* 3. Configures average channel if needed. */
    ADC_AvgSetCnt(ADC_AVG_CNT_8);
    ADC_AvgChannelCmd(ADC_AVG_CHANNEL, Enable);
}

/**
 * @brief  Set the pin(s) corresponding to the specified channel(s) to analog mode.
 * @param  [in]  u16Channel         The specified channel(s).
 * @retval None
 */
static void AdcSetChannelPinAnalogMode(uint16_t u16Channel)
{
    uint8_t u8PinNum;

    u8PinNum    = 0U;
    u16Channel &= ADC_CH_ALL;

    while (u16Channel != 0U)
    {
        if (u16Channel & 0x1U)
        {
            AdcSetPinAnalogMode(u8PinNum);
        }

        u16Channel >>= 1U;
        u8PinNum++;
    }
}

/**
 * @brief  Set specified ADC pin to analog mode.
 * @param  [in]  u8PinNum           The ADC pin number.
 *                                  This parameter can be a value of @ref ADC_Pin_Number
 * @retval None
 */
static void AdcSetPinAnalogMode(uint8_t u8PinNum)
{
    uint8_t u8Port = GPIO_PORT_4;
    uint8_t u8Pin  = GPIO_PIN_0;
    uint8_t u8Flag = 1U;

    switch (u8PinNum)
    {
    case ADC_ANI0:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_0;
        break;

    case ADC_ANI1:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_1;
        break;

    case ADC_ANI2:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_2;
        break;

    case ADC_ANI3:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_3;
        break;

    case ADC_ANI4:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_4;
        break;

    case ADC_ANI5:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_5;
        break;

    case ADC_ANI6:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_6;
        break;

    case ADC_ANI7:
        u8Port = GPIO_PORT_4;
        u8Pin  = GPIO_PIN_7;
        break;

    case ADC_ANI8:
        u8Port = GPIO_PORT_1;
        u8Pin  = GPIO_PIN_1;
        break;

    case ADC_ANI9:
        u8Port = GPIO_PORT_1;
        u8Pin  = GPIO_PIN_0;
        break;

    default:
        u8Flag = 0U;
        break;
    }

    if (u8Flag != 0U)
    {
        GPIO_SetFunc(u8Port, u8Pin, GPIO_FUNC_1_ADST);
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
