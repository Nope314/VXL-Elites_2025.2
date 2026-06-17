#include <stm32f10x.h>

//================ GPIO =================
void GPIO_Init_Config(void)
{
    // Clock GPIOA + GPIOC + AFIO
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // PA1 OUTPUT PUSH PULL 50MHz (TX)
    GPIOA->CRL &= ~(0xF << 4);
		GPIOA->CRL |=  (0x3 << 4);
	
	 // TX idle = HIGH
    GPIOA->BSRR = (1<<1);

    // PA0 INPUT PULL DOWN(RX)
	
    GPIOA->CRL &= ~(0xF << 0);
    GPIOA->CRL |=  (0x8 << 0);

    GPIOA->ODR &= ~(1 << 0);
		
		//init PA2 de debug
		GPIOA->CRL &= ~(0xF << 8);
		GPIOA->CRL |=  (0x3 << 8);
}

	void TIM4_DRV_Init(void)
	{
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

		// enable clock for TIM4
			// enable update interrupt
			// enable TIM4 interrupt in NVIC
			
			TIM4->PSC = 71;           //cycle of interrupt
			TIM4->ARR = 103;            // frequency -> baudrate= 9600

			TIM4->DIER |= (1 << 0);     // Update interrupt enable

			NVIC_EnableIRQ(TIM4_IRQn);  // enable interrupt in NVIC
		
				TIM4->CNT=0;
				TIM4->CR1 |= (1 <<0);// start timer
	}

volatile uint8_t tx_busy =0;
volatile uint8_t tx_data;
volatile uint8_t tx_bit_idx;	//index of 10bit
	
void SoftUART_SendByte(uint8_t data)
{
		while(tx_busy);
		
		tx_data =data;
    tx_busy = 1;
    tx_bit_idx = 0;

    TIM4->CNT = 0;
    TIM4->CR1 |= TIM_CR1_CEN;     // timer on
}
	uint8_t bit;
	void TIM4_IRQHandler(void)
	{
			if (TIM4->SR &  TIM_SR_UIF) {      //check flag, UIF = update interrupt flag
				 TIM4->SR &= ~TIM_SR_UIF;      // clear flag , neu ko clear thi se treo o buoc tren luon
		
					if(tx_busy)
					{
						if(tx_bit_idx ==0)
						{
							GPIOA->BRR |= (1<<1); //start bit
			}
			else if(tx_bit_idx >= 1 && tx_bit_idx <=8)
			{
				bit = (tx_data >> (tx_bit_idx -1)) & 0x01;
				
				if(bit){
						GPIOA->BSRR |= (1<<1); //bit can truyen la 1'
				   // GPIOA->BSRR |= (1<<2);
				} else {
					GPIOA->BRR |= (1<<1);
			//		GPIOA->BRR |= (1<<2);
				}
	}
			else if(tx_bit_idx ==9){
				GPIOA->BSRR  |= (1<<1); //stop bit
			}
			else{
				tx_busy =0 ; //finish
				TIM4->CR1 &= ~TIM_CR1_CEN;        // timer off
			}
			tx_bit_idx++;
		}
	}
}
	
void delay_ms(uint32_t time_ms){
	for(volatile uint32_t i=0;i<time_ms;i++);
}

//================ EXTI =================
void EXTI0_DRV_Init(void)
{
    // PA0 -> EXTI0
    AFIO->EXTICR[0] &= ~(0xF << 0);

    // Falling edge trigger
    EXTI->FTSR |= (1 << 0);

    // Unmask EXTI0
    EXTI->IMR |= (1 << 0);

    // Enable NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);	
}
void TIM3_DRV_Init(void)
	{
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

		// enable clock for TIM4
			// enable update interrupt
			// enable TIM4 interrupt in NVIC
			
			TIM3->PSC = 71;           //cycle of interrupt
			TIM3->ARR = 103;            // frequency -> baudrate= 9600

			TIM3->DIER |= (1 << 0);     // Update interrupt enable

			NVIC_EnableIRQ(TIM3_IRQn);  // enable interrupt in NVIC
		
				TIM3->CNT=0;
				TIM3->CR1 |= (1 <<0);// start timer
	}

volatile uint8_t rx_busy =0;
volatile uint8_t rx_data=0;
volatile uint8_t rx_bit_idx=0;	//index of 10bit
volatile uint8_t rx_done=0;
	
//================ ISR =================
 void EXTI0_IRQHandler(void)
{
    if(EXTI->PR & (1 << 0))
    {
        // Clear pending bit
        EXTI->PR |= (1 << 0);

       if(rx_busy ==0 )
			 {
				rx_busy =1;
				rx_data =0;
				rx_bit_idx=0;
				 
				 TIM3-> CNT=0;
				 
				 //1.5 bit time
				 TIM3-> ARR =155;
						 
				 TIM3-> CR1 |= TIM_CR1_CEN; //timer on
			 }
		 }
}

	void TIM3_IRQHandler(void)
{
    if(TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;

        if(rx_busy)
        {
            if(rx_bit_idx < 8)
            {
                uint8_t bit;

                bit = (GPIOA->IDR >> 0) & 0x01;

                rx_data |= (bit << rx_bit_idx);

                rx_bit_idx++;

                TIM3->ARR = 103;
            }
            else
            {
                rx_busy = 0;
                rx_done = 1;

                TIM3->CR1 &= ~TIM_CR1_CEN;
            }
        }
    }
}

void UART1_DRV_Init(void)
{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
		GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

		// PA10 RX
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);
	
	 USART1->BRR = 0x1D4C;
	
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

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

void UART1_SendHex(uint8_t x)
{
    char hex[] = "0123456789ABCDEF";

    UART1_SendChar(hex[(x >> 4) & 0x0F]);
    UART1_SendChar(hex[x & 0x0F]);
}

void APP_Init ()
{
	GPIO_Init_Config();
	TIM4_DRV_Init();
	EXTI0_DRV_Init();
	TIM3_DRV_Init();
	UART1_DRV_Init();
	
}
uint8_t received_char;
/*
int main()
{
	APP_Init();
	while(1){
	UART1_SendString("Start");
	SoftUART_SendByte('A');
		
	//test TX(PA1)
	
   GPIOA->ODR ^= (1<<2);//neu dc thi led P2 toggle
	  
	  delay_ms(960000); //tgian gui giua cac lan
	}
}
	
	
	//test RX(PA0)
	 if(rx_done)
    {
        rx_done = 0;

        received_char = rx_data;
			
				GPIOA->ODR ^= (1<<2);//neu dc thi led P2 toggle 
				
				delay_ms(960000);
    }
}
}
*/
//test du lieu co dung la A khong
int main(){
	while(1)
{
	 APP_Init();

    SoftUART_SendByte('A');
		
		while(tx_busy)
	
    while(rx_done == 0);

    rx_done = 0;

    UART1_SendString("RX = 0x");
		UART1_SendHex(rx_data);
		UART1_SendString("\r\n");
		UART1_SendChar (rx_data);
		UART1_SendString("\r\n");

    delay_ms(960000);
}
}
