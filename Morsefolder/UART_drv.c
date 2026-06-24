#include "common.h"
#include "uart_drv.h"

void UART1_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_USART1EN;
    RCC->APB2ENR |= RCC_IOPAEN;

    // PA9 TX
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    // PA10 RX
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);
	//baudrate : 9600
    USART1->BRR = 0x1D4C;

    USART1->CR1 |= USART_TE;
    USART1->CR1 |= USART_RE;
    USART1->CR1 |= USART_UE;
}

void UART1_SendChar(char c)
{
    while(!(USART1->SR & USART_TXE)); //check xem ready chua

    USART1->DR = c;
}

void UART1_SendString(char *s) //con tro toi string
{
    while(*s) //ky tu khac /0
    {
        UART1_SendChar(*s++);
    }
}
