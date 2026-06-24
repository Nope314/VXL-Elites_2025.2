#include "common.h"
#include "gpio_drv.h"

void GPIO_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_IOPAEN;
    RCC->APB2ENR |= RCC_IOPBEN;

    // PB13 output
    GPIOB->CRH &= ~(0xF << 20);
    GPIOB->CRH |=  (0x2 << 20);

    // PA0 input
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0x8 << 0);
}
