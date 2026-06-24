#include "common.h"
#include "EXTI_drv.h"
#include "Systick_drv.h"
extern void Button_Callback(uint32_t duration);

volatile uint32_t press_time = 0;
volatile uint32_t release_time = 0;
volatile uint32_t last_interrupt_time = 0;

#define DEBOUNCE_TIME 30

void EXTI0_DRV_Init(void)
{
    RCC->APB2ENR |= RCC_AFIOEN;

    AFIO->EXTICR[0] &= ~(0xF << 0);

    EXTI->RTSR |= (1 << 0);
    EXTI->FTSR |= (1 << 0);

    EXTI->IMR |= (1 << 0);

    NVIC_ISER0 |= (1 << 6);
}

void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & (1 << 0))
    {
        EXTI->PR |= (1 << 0); //remove flag

        if((millis - last_interrupt_time) < DEBOUNCE_TIME)
        {
            return; //exit
        }

        last_interrupt_time = millis; //de lan interupt sau debounce dc

        if(GPIOA->IDR & (1 << 0)) //check xem co nhan ko ?
        {
            press_time = millis;
        }
        else
        {
            release_time = millis;

            uint32_t duration;
            duration = release_time - press_time;

            Button_Callback(duration);
        }
    }
}
