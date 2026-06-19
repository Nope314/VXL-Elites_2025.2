#include "stm32f10x.h"
#include "gpio_drv.h"

void GPIO_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
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
}

