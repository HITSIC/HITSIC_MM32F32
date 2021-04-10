#include "board.h"

void BOARD_Init(void)
{
    HSE_SYSCLK_Init(RCC_PLLMul_15);                             //PLL:15倍频
    UART_DEBUG_Init(DEBUG_UART, DEBUG_UART_BAUD);
}

void GPIO_DEBUG_Init(GPIO_TypeDef *GPIO_TX, u16 TX_PIN, GPIO_TypeDef *GPIO_RX, u16 RX_PIN)
{
    //开启GPIOA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIO_TX, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_FLOATING;
    GPIO_InitStructure.GPIO_Pin = RX_PIN;
    GPIO_Init(GPIO_RX, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
}

void UART_DEBUG_Init(UART_TypeDef *debug_uartn, u32 baud)
{
    GPIO_DEBUG_Init(DEBUG_UART_TX_GPIO, DEBUG_UART_TX_PIN, DEBUG_UART_RX_GPIO, DEBUG_UART_RX_PIN);
    //开启UART1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_UART1, ENABLE);
    
    UART_InitTypeDef UART_InitStructure;
    UART_InitStructure.UART_BaudRate = baud;
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;
    UART_InitStructure.UART_StopBits = UART_StopBits_1;
    UART_InitStructure.UART_Parity = UART_Parity_No;
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;
    UART_InitStructure.UART_Mode = (UART_Mode_Rx | UART_Mode_Tx);
    UART_Init(debug_uartn, &UART_InitStructure);
    
    UART_Cmd(debug_uartn, ENABLE);
}


//重定向printf
int fputc(int ch, FILE *f)
{
    UART_SendData(DEBUG_UART, (unsigned char) ch);
    while (!(DEBUG_UART->CSR & UART_FLAG_TXEMPTY));
    return (ch);
}

//配置系统时钟
void HSE_SYSCLK_Init(RCC_PLLMul_TypeDef pll_mul)
{
    RCC_DeInit();                                                       //rcc重置
    RCC_HSEConfig(RCC_HSE_ON);                                          //打开外部晶振(HSE:8Mhz无源晶振)
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);               //等待HSE准备完毕     
    RCC_HCLKConfig(RCC_SYSCLK_Div1);                                    //HCLK = SYSCLK
    RCC_PCLK1Config(RCC_HCLK_Div2);                                     //PCLK1 = HCLK / 2
    RCC_PCLK2Config(RCC_HCLK_Div1);                                     //PCLK2 = HCLK
    RCC_PLLConfig(RCC_HSE_Div1, pll_mul);                               //8Mhz * 15倍频 = 120Mhz
    RCC_PLLCmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);                //等待PLL
    RCC_SYSCLKConfig(RCC_PLL);                                          //设置系统时钟源
    while (RCC_GetSYSCLKSource() != 0x08);                              //判断PLL是不是系统时钟
}
