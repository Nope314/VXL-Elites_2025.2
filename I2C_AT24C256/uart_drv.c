#include "stm32f10x.h"
#include "uart_drv.h"

void UART1_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    USART1->BRR = 0x1D4C;

    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    USART1->CR1 |= USART_CR1_UE;
}

void UART1_SendChar(char c)
{
    while(!(USART1->SR & USART_SR_TXE));

    USART1->DR = c;
}

void UART1_SendString(char *s)
{
    while(*s)
    {
        UART1_SendChar(*s++);
    }
}
