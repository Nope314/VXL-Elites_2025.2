#include "stm32f10x.h"
#include "systick_drv.h"

volatile uint32_t tick = 0;

void SysTick_DRV_Init(void)
{
    SysTick->LOAD = 72000 - 1;

    SysTick->VAL = 0;

    SysTick->CTRL = 7;
}

void SysTick_Handler(void)
{
    tick++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = tick;

    while((tick - start) < ms);
}
