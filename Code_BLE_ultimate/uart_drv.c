#include "stm32f10x.h"
#include "uart_drv.h"

void UART1_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART1->BRR = 0x1D4C; //9600

    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    USART1->CR1 |= USART_CR1_UE;
}
void UART2_DRV_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    //115200 baud
    USART2->BRR = 0x138; //0x138

    USART2->CR1 = USART_CR1_TE |
                  USART_CR1_RE;

    USART2->CR1 |= USART_CR1_UE;
}

void UART1_SendChar(char c)
{
    while(!(USART1->SR & USART_SR_TXE));

    USART1->DR = c;
}
void UART2_SendChar(char c)
{
    while(!(USART2->SR & USART_SR_TXE));

    USART2->DR = c;
}

void UART1_SendString(char *s)
{
    while(*s)
    {
        UART1_SendChar(*s++);
    }
}
void UART2_SendString(char *s)
{
    while(*s)
        UART2_SendChar(*s++);
}

//receive
int UART1_Available(void)
{
    return (USART1->SR & USART_SR_RXNE);
}

int UART2_Available(void)
{
    return (USART2->SR & USART_SR_RXNE);
}

char UART1_ReadChar(void)
{
    while(!(USART1->SR & USART_SR_RXNE));

    return USART1->DR;
}

char UART2_ReadChar(void)
{
    while(!(USART2->SR & USART_SR_RXNE));

    return USART2->DR;
}
