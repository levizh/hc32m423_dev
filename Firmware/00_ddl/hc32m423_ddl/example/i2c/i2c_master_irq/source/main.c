/**
 *******************************************************************************
 * @file  i2c/i2c_master_irq/source/main.c
 * @brief Main program of I2C for the Device Driver Library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2019-07-09       Wangmin         First version
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
 * @addtogroup I2C_Master_Irq
 * @{
 */

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/
/**
 * @brief I2c communication mode enum
 */
typedef enum stc_i2c_com_mode
{
    Mode_Send = 0U,
    Mode_Rev = 1U,
}stc_i2c_com_mode_t;


/**
 * @brief I2c communication structure
 */
typedef struct
{
    stc_i2c_com_mode_t enMode;    /*!< I2C communication mode*/
    uint32_t u32Length;           /*!< I2C communication data length*/
    uint8_t* pBuf;                /*!< I2C communication data buffer pointer*/
    uint32_t u32DataIndex;        /*!< I2C communication data transfer index*/
    __IO uint8_t u8FinishFlag;    /*!< I2C communication status*/
}stc_i2c_communication_t;


/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Define slave device address for example */
#define DEVICE_ADDRESS                  0x06U

/* Define port and pin for SDA and SCL */
#define I2C_SCL_PORT                    (GPIO_PORT_B)
#define I2C_SCL_PIN                     (GPIO_PIN_6)
#define I2C_SDA_PORT                    (GPIO_PORT_B)
#define I2C_SDA_PIN                     (GPIO_PIN_5)

#define TIMEOUT                         ((uint32_t)0x10000)

#define I2C_RET_OK                      0U
#define I2C_RET_ERROR                   1U

#define GENERATE_START                  0x00U
#define GENERATE_RESTART                0x01U

#define ADDRESS_W                       0x00U
#define ADDRESS_R                       0x01U

/* Define Write and read data length for the example */
#define TEST_DATA_LEN                   128U
/* Define i2c baudrate */
#define I2C_BAUDRATE                    400000UL

/* Define for RGB LED */
#define LED_R_PORT                      (GPIO_PORT_12)
#define LED_G_PORT                      (GPIO_PORT_7)
#define LED_B_PORT                      (GPIO_PORT_3)
#define LED_R_PIN                       (GPIO_PIN_0)
#define LED_G_PIN                       (GPIO_PIN_0)
#define LED_B_PIN                       (GPIO_PIN_1)
//#define LED_G_TOGGLE()                  (GPIO_TogglePins(LED_G_PORT, LED_G_PIN))
//#define LED_R_TOGGLE()                  (GPIO_TogglePins(LED_R_PORT, LED_R_PIN)) //todo
#define LED_G_TOGGLE()
#define LED_R_TOGGLE()
/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void SystemClockConfig(void);
static void LedConfig(void);
static void WaitSw2_ShortPress(void);
static uint8_t Master_Initialize(void);
static void BufWrite(uint8_t* pbuf, uint8_t u8Data);
static uint8_t BufRead(uint8_t* pbuf);
static uint8_t Master_StartOrRestart(uint8_t u8Start);
static uint8_t Master_SendAdr(uint8_t u8Adr);
static void MasterSendData(uint32_t u32Len, uint8_t* pbuf);
static void MasterRevData(uint32_t u32Len, uint8_t* pbuf);
static uint8_t GetComStatus(void);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/
uint8_t u8TxBuf[TEST_DATA_LEN];
uint8_t u8RxBuf[TEST_DATA_LEN];
stc_i2c_communication_t stcI2cCom;

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief  Main function of i2c_at24c02 project
 * @param  None
 * @retval int32_t return value, if needed
 */
int32_t main(void)
{
    uint32_t i;

    /* Configure system clock. */
    SystemClockConfig();

    /* RGB LED configuration */
    LedConfig();

    /* Test buffer initialize */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        u8TxBuf[i] = (uint8_t)i+1U;
    }
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        u8RxBuf[i] = 0U;
    }

    /* Initialize I2C port*/
    GPIO_SetFunc(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_FUNC_7_I2C);
    GPIO_SetFunc(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_FUNC_7_I2C);

    /* Enable I2C Peripheral*/
    //CLK_FcgPeriphClockCmd(CLK_FCG_I2C, Enable);//todo

    /* Initialize I2C peripheral and enable function*/
    Master_Initialize();

    /* Short press key SW2 */
    WaitSw2_ShortPress();

    /* I2C master data write */
    MasterSendData(TEST_DATA_LEN, u8TxBuf);

    i = 0UL;
    /* Wait communicaiton finished*/
    while(0U == GetComStatus())
    {
        if(TIMEOUT == i++)
        {
            /* Communication time out*/
            while(1)
            {
                LED_R_TOGGLE();
                DDL_Delay1ms(500U);
            }
        }
    }

    /* 5mS delay for device*/
    DDL_Delay1ms(1U);

    /* I2C master data Read */
    MasterRevData(TEST_DATA_LEN, u8RxBuf);

    i = 0UL;
    /* Wait communicaiton finished*/
    while(0U == GetComStatus())
    {
        if(TIMEOUT == i++)
        {
            /* Communication time out*/
            while(1)
            {
                LED_R_TOGGLE();
                DDL_Delay1ms(500U);
            }
        }
    }

    /* Compare the data */
    for(i=0U; i<TEST_DATA_LEN; i++)
    {
        if(u8TxBuf[i] != u8RxBuf[i])
        {
            /* Data write error*/
            while(1)
            {
                LED_R_TOGGLE();
                DDL_Delay1ms(500U);
            }
        }
    }

    /* Communication finished */
    while(1)
    {
        LED_G_TOGGLE();
        DDL_Delay1ms(500U);
    }
}

/**
 * @brief  Master send data kick start via interrupt .
 * @param  [in] u32Len  Data length
 * @param  [in] pbuf    Data buffer pointer
 * @retval None
 */
static void MasterSendData(uint32_t u32Len, uint8_t* pbuf)
{
    stcI2cCom.u32DataIndex = 0U;
    stcI2cCom.u8FinishFlag = 0U;
    stcI2cCom.enMode = Mode_Send;
    stcI2cCom.u32Length = u32Len;
    stcI2cCom.pBuf = pbuf;

    /* General start condition */
    Master_StartOrRestart(GENERATE_START);
}

/**
 * @brief  Master Rev data kick start via interrupt .
 * @param  [in] u32Len  Data length
 * @param  [in] pbuf    Data buffer pointer
 * @retval None
 */
static void MasterRevData(uint32_t u32Len, uint8_t* pbuf)
{
    stcI2cCom.u32DataIndex = 0U;
    stcI2cCom.u8FinishFlag = 0U;
    stcI2cCom.enMode = Mode_Rev;
    stcI2cCom.u32Length = u32Len;
    stcI2cCom.pBuf = pbuf;

    /* General start condition */
    Master_StartOrRestart(GENERATE_START);
}

/**
 * @brief  Master communication status read.
 * @param  None
 * @retval uint8_t  If return 1 indicate communication finished.
 */
static uint8_t GetComStatus(void)
{
    return stcI2cCom.u8FinishFlag;
}


/**
 * @brief  Wait SW2 key short press.
 * @param  None
 * @retval None
 */
static void WaitSw2_ShortPress(void)
{
    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPortPin(GPIO_PORT_2, GPIO_PIN_1))
    {
        ;
    }
    DDL_Delay1ms(5U);

    /* Wait key down */
    while(Pin_Reset != GPIO_ReadInputPortPin(GPIO_PORT_2, GPIO_PIN_1))
    {
        ;
    }
    DDL_Delay1ms(5U);

    /* Wait key up */
    while(Pin_Set != GPIO_ReadInputPortPin(GPIO_PORT_2, GPIO_PIN_1))
    {
        ;
    }
    DDL_Delay1ms(5U);
}

/**
 * @brief  Configure system clock.
 * @param  None
 * @retval None
 */
static void SystemClockConfig(void)
{
    stc_clk_xtal_init_t stcXTALInit;

    /* Configure XTAL */
    stcXTALInit.u8XtalState = CLK_XTAL_ON;
    stcXTALInit.u8XtalMode = CLK_XTALMODE_OSC;
    stcXTALInit.u8XtalDrv = CLK_XTALDRV_HIGH;
    stcXTALInit.u8XtalSupDrv = CLK_XTAL_SUPDRV_OFF;
    stcXTALInit.u8XtalStb = CLK_XTALSTB_8;

    /* Initialize XTAL clock */
    CLK_XTALInit(&stcXTALInit);

    /* Switch system clock from HRC(default) to XTAL */
    CLK_SetSysclkSrc(CLK_SYSCLKSOURCE_XTAL);
}

/**
 * @brief   Initialize the I2C peripheral for master
 * @param   None
 * @retval  Process result
 *          - I2C_RET_ERROR  Initialize failed
 *          - I2C_RET_OK     Initialize success
 */
static uint8_t Master_Initialize(void)
{
    stc_i2c_init_t stcI2cInit;
    float32_t fErr;

    I2C_DeInit();

    I2C_StructInit(&stcI2cInit);
    stcI2cInit.u32Baudrate = I2C_BAUDRATE;
    stcI2cInit.u32I2cClkDiv = I2C_CLK_DIV1;
    stcI2cInit.u32SclTime = 5U;
    I2C_Init(&stcI2cInit, &fErr);

    /* Set slave address*/
#ifdef I2C_10BITS_ADDRESS
    I2C_SlaveAdrConfig(I2C_ADR_0, I2C_ADR_CONFIG_10BIT, DEVICE_ADDRESS);
#else
    I2C_SlaveAdrConfig(I2C_ADR_0, I2C_ADR_CONFIG_7BIT, DEVICE_ADDRESS);
#endif

    /* configure NVIC. */
    NVIC_ClearPendingIRQ(I2cRXI_IRQn);
    NVIC_SetPriority(I2cRXI_IRQn, DDL_IRQ_PRIORITY_03);
    NVIC_EnableIRQ(I2cRXI_IRQn);

    NVIC_ClearPendingIRQ(I2cTXI_IRQn);
    NVIC_SetPriority(I2cTXI_IRQn, DDL_IRQ_PRIORITY_03);
    NVIC_EnableIRQ(I2cTXI_IRQn);

    NVIC_ClearPendingIRQ(I2cTEI_IRQn);
    NVIC_SetPriority(I2cTEI_IRQn, DDL_IRQ_PRIORITY_03);
    NVIC_EnableIRQ(I2cTEI_IRQn);

    NVIC_ClearPendingIRQ(I2cEEI_IRQn);
    NVIC_SetPriority(I2cEEI_IRQn, DDL_IRQ_PRIORITY_03);
    NVIC_EnableIRQ(I2cEEI_IRQn);

    /* I2C function command */
    I2C_Cmd(Enable);

    /* Config startf and slave address match interrupt function*/
    I2C_IntCmd(I2C_CR2_STARTIE | I2C_CR2_SLADDR0IE, Enable);

    return I2C_RET_OK;
}

/**
 * @brief   Send start or restart condition
 * @param   [in]  u8Start  Indicate the start mode, start or restart
 * @retval  Process result
 *          - I2C_RET_ERROR  Send start or restart failed
 *          - I2C_RET_OK     Send start or restart success
 */
static uint8_t Master_StartOrRestart(uint8_t u8Start)
{
    /* generate start or restart signal */
    if(GENERATE_START == u8Start)
    {
        I2C_GenerateStart();
    }
    else
    {
        /* Clear start status flag */
        I2C_ClearStatus(I2C_CLR_STARTFCLR);
        /* Send restart condition */
        I2C_GenerateReStart();
    }

    return I2C_RET_OK;
}

/**
 * @brief   Send slave address
 * @param   [in]  u8Adr  The slave address
 * @retval  Process result
 *          - I2C_RET_ERROR  Send failed
 *          - I2C_RET_OK     Send success
 */
static uint8_t Master_SendAdr(uint8_t u8Adr)
{
    uint32_t u32TimeOut = TIMEOUT;
    uint8_t u8Ret = I2C_RET_OK;

    /* Wait tx buffer empty */
    while(Reset == I2C_GetStatus(I2C_SR_TEMPTYF))
    {
        if(0U == (u32TimeOut--))
        {
            u8Ret = I2C_RET_ERROR;
        }
    }

    if(I2C_RET_ERROR != u8Ret)
    {
        /* Send I2C address */
        I2C_SendData(u8Adr);
    }

    return u8Ret;
}

/**
 * @brief  Configure RGB LED.
 * @param  None
 * @retval None
 */
static void LedConfig(void)
{
#if 0
  //todo
    stc_gpio_init_t stcGpioInit = {0U};

    stcGpioInit.u16PinMode = PIN_MODE_OUT;
    stcGpioInit.u16PinState = PIN_STATE_SET;
    GPIO_Init(LED_G_PORT, LED_G_PIN, &stcGpioInit);
    GPIO_Init(LED_R_PORT, LED_R_PIN, &stcGpioInit);
#endif
}

/**
 * @brief   I2C EEI(communication error or event) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_Err_IrqHandler(void)
{
    /* If starf flag valid */
    if(Set == I2C_GetStatus(I2C_SR_STARTF))
    {
        I2C_ClearStatus(I2C_CLR_STARTFCLR);
        if(Mode_Send == stcI2cCom.enMode)
        {
            Master_SendAdr(((uint8_t)DEVICE_ADDRESS<<1U) | ADDRESS_W);
        }
        else
        {
            Master_SendAdr(((uint8_t)DEVICE_ADDRESS<<1U) | ADDRESS_R);
        }
    }

    /* If address flag valid */
    if(Set == I2C_GetStatus(I2C_SR_SLADDR0F))
    {
        I2C_ClearStatus(I2C_CLR_SLADDR0FCLR);
        /* Enable Tx or Rx function*/
        if(Set == I2C_GetStatus(I2C_SR_TRA))
        {
            /* Config tx buffer empty interrupt function*/
            I2C_IntCmd(I2C_CR2_TEMPTYIE, Enable);
            /* Write the first data to DTR immediately */
            I2C_SendData(BufRead(stcI2cCom.pBuf));
        }
        else
        {
            /* Config rx buffer full interrupt function*/
            I2C_IntCmd(I2C_CR2_RFULLIE, Enable);
        }

        /* Enable NACK interrupt */
        I2C_IntCmd(I2C_CR2_STOPIE | I2C_CR2_NACKIE, Enable);
    }

    /* If NACK interrupt occurred */
    if(Set == I2C_GetStatus(I2C_SR_ACKRF))
    {
        /* clear NACK flag*/
        I2C_ClearStatus(I2C_CLR_NACKFCLR);
        /* Stop tx or rx process*/
        if(Set == I2C_GetStatus(I2C_SR_TRA))
        {
            /* Config tx buffer empty interrupt function disable*/
            I2C_IntCmd(I2C_CR2_TEMPTYIE, Disable);

            /* Read DRR register to release SCL*/
            I2C_ReadData();
        }
        else
        {
            /* Config rx buffer full interrupt function disable */
            I2C_IntCmd(I2C_CR2_RFULLIE, Disable);
        }
    }

    if(Set == I2C_GetStatus(I2C_SR_STOPF))
    {
        /* Communication finished */
        stcI2cCom.u8FinishFlag = 1U;
        /* Disable Stop flag interrupt */
        I2C_IntCmd(I2C_CR2_STOPIE, Disable);
        I2C_ClearStatus(I2C_CLR_STOPFCLR);
    }
}

/**
 * @brief   I2C TXI(transfer buffer empty) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEmpty_IrqHandler(void)
{
    if(Set == I2C_GetStatus(I2C_SR_TEMPTYF))
    {
        if(stcI2cCom.u32DataIndex < TEST_DATA_LEN)
        {
            I2C_SendData(BufRead(stcI2cCom.pBuf));
        }
        else
        {
            I2C_IntCmd(I2C_CR2_TEMPTYIE, Disable);
            I2C_IntCmd(I2C_CR2_TENDIE, Enable);
        }
    }
}

/**
 * @brief   I2C RXI(receive buffer full) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_RxEnd_IrqHandler(void)
{
    if(Set == I2C_GetStatus(I2C_SR_RFULLF))
    {
        BufWrite(stcI2cCom.pBuf, I2C_ReadData());
    }

    if(stcI2cCom.u32DataIndex >= TEST_DATA_LEN)
    {
        /* Generate stop condition */
        I2C_ClearStatus(I2C_CLR_STOPFCLR);
        I2C_GenerateStop();
        /* Enable Stop flag interrupt */
        I2C_IntCmd(I2C_CR2_STOPIE, Enable);
        /* Disable TXI interrupt */
        I2C_IntCmd(I2C_CR2_RFULLIE, Disable);
    }
}

/**
 * @brief   I2C TEI(Transfer end) interrupt callback function
 * @param   None
 * @retval  None
 */
void I2C_TxEnd_IrqHandler(void)
{
    if(Set == I2C_GetStatus(I2C_SR_TENDF))
    {
        /* Generate stop condition */
        I2C_ClearStatus(I2C_CLR_STOPFCLR);
        I2C_GenerateStop();
        /* Enable Stop flag interrupt */
        I2C_IntCmd(I2C_CR2_STOPIE, Enable);
        /* Disable TXI interrupt */
        I2C_IntCmd(I2C_CR2_TEMPTYIE|I2C_CR2_TENDIE, Disable);
    }
}

/**
 * @brief   static function for buffer write.
 * @param   [in]   pbuf   Buffer pointer
 * @param   [in]   u8Data the data to be write.
 * @retval  None
 */
static void BufWrite(uint8_t* pbuf, uint8_t u8Data)
{
    if(stcI2cCom.u32DataIndex >= TEST_DATA_LEN)
    {
        //error
        while(1)
        {
            ;
        }
    }
    *(uint8_t*)(pbuf + stcI2cCom.u32DataIndex) = u8Data;
    stcI2cCom.u32DataIndex++;
}

/**
 * @brief   Static function for buffer read.
 * @param   [in]   pbuf   Buffer pointer
 * @retval  uint8_t  The data read out from buffer.
 */
static uint8_t BufRead(uint8_t* pbuf)
{
    uint8_t temp;
    if(stcI2cCom.u32DataIndex >= TEST_DATA_LEN)
    {
        //error
        while(1)
        {
            ;
        }
    }
    temp = *(uint8_t*)(pbuf + stcI2cCom.u32DataIndex);
    stcI2cCom.u32DataIndex++;

    return temp;
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
