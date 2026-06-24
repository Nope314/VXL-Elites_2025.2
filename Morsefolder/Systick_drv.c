#include "common.h"
#include "systick_drv.h"

volatile uint32_t millis = 0;

void SysTick_DRV_Init(void)
{
    SysTick->LOAD = 72000 - 1;

    SysTick->VAL = 0; //reset counter

    SysTick->CTRL =SYSTICK_ENABLE | SYSTICK_TICKINT | SYSTICK_CLKSOURCE;
}

void SysTick_Handler(void)
{
    millis++;
}
