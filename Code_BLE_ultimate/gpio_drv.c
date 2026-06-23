#include "stm32f10x.h"
#include "gpio_drv.h"

void GPIO_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // PB6 SCL
    GPIOB->CRL &= ~(0xFU << 24);
    GPIOB->CRL |=  (0xFU << 24);

    // PB7 SDA
    GPIOB->CRL &= ~(0xFU << 28);
    GPIOB->CRL |=  (0xFU << 28);

    // PA9 TX
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    // PA10 RX
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);
	
	// PA2 TX
    GPIOA->CRL &= ~(0xF << 8);
    GPIOA->CRL |=  (0xB << 8);

    // PA3 RX
    GPIOA->CRL &= ~(0xF << 12);
    GPIOA->CRL |=  (0x4 << 12);
		
		// PA0 Output Push Pull 2MHz

GPIOA->CRL &= ~(0xF << 0);
GPIOA->CRL |=  (0x2 << 0);

}

