#include <stdint.h>
#include "reg_alternative.h"

#define RCC_APB2ENR (*(volatile reg_base*)0x40021018)

void GPIO_clk_enable() {
    RCC_APB2ENR.bit_field.bits.bit2 = 1;
    RCC_APB2ENR.bit_field.bits.bit3 = 1;
}

void GPIO_init() {
    GPIOA->GPIOx_CRL.bit_field.bits.mode0 = 0;
    GPIOA->GPIOx_CRL.bit_field.bits.cnf0 = 2;

    GPIOA->GPIOx_ODR.bit_field.bits.bit0 = 1;
    
    GPIOB->GPIOx_CRH.bit_field.bits.mode13 = 1;
    GPIOB->GPIOx_CRH.bit_field.bits.cnf13 = 0;
}

int main() {
    GPIO_clk_enable();
    GPIO_init();

    while (1){
        if(GPIOA->GPIOx_IDR.bit_field.bits.bit0 == 0) {
            //LED on
            GPIOB->GPIOx_BSRR.bit_field.bits.bit3 = 1;
            GPIOB->GPIOx_BRR.bit_field.bits.bit3 = 0;
        } else {
            //LED off
            GPIOB->GPIOx_BSRR.bit_field.bits.bit3 = 0;
            GPIOB->GPIOx_BRR.bit_field.bits.bit3 = 1;
        }
    }

    return 0;
}
