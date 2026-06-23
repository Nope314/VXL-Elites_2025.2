#include "uart.h"

void UART1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA9 TX AF Push Pull
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    // PA10 RX floating input
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    USART1->BRR = 0x341; // 9600 baud @72MHz

    USART1->CR1 =
          USART_CR1_TE
        | USART_CR1_RE;

    USART1->CR1 |= USART_CR1_UE;
}

void UART1_SendChar(char c)
{
    while(!(USART1->SR & USART_SR_TXE));

    USART1->DR = c;
}

void UART1_SendString(char *str)
{
    while(*str)
    {
        UART1_SendChar(*str++);
    }
}
