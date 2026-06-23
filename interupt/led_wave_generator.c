#include "stm32f10x.h"

void GPIO_Init_Config(void);
void EXTI0_Init(void);

int main(void)
{
    GPIO_Init_Config();
    EXTI0_Init();

    while(1)
    {
		
    }
}

//================ GPIO =================
void GPIO_Init_Config(void)
{
    // Clock GPIOA + GPIOC + AFIO
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // PB13 OUTPUT PUSH PULL
    GPIOB->CRH &= ~(0xF << 20);
    GPIOB->CRH |=  (0x2 << 20);

    // PA0 INPUT PULL DOWN
	/*
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0x8 << 0);

    GPIOA->ODR &= ~(1 << 0);
	*/
}

//================ EXTI =================
void EXTI0_Init(void)
{
    // PA0 -> EXTI0
    AFIO->EXTICR[0] &= ~(0xF << 0);

    // Rising edge trigger
    EXTI->RTSR |= (1 << 0);

    // Unmask EXTI0
    EXTI->IMR |= (1 << 0);

    // Enable NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);	
}

//================ ISR =================
 void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & (1 << 0))
    {
        // Clear pending bit
        EXTI->PR |= (1 << 0);

        // Toggle LED
        GPIOB->ODR ^= (1 << 13);
			
    }
}

//tang len 1k xem chay duoc ko , phai tang dem cai den , tang max dc bao nhieu thi interupt loi
//5M xem chay dc ko , 10M loi , 
//tang xung len , thi bi giat ko chay , tsao lai nhu the , tsao den 1,2MHz thi bi giat , neu config bang code thi gioi han max la 1,2Mhz co thay doi dc ko (toi dang nghi la do phancung
