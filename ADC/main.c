//Đọc DMA trên bluepill , dùng DMA lấy mẫu ADC nối với microphone, lấy mẫu tiếng nói đấy và in ra uart ,
//nối một vào 1 file in ra uart và vẽ bằng python in mẫu hình (làm real time là optional)

#include "stm32f10x.h"
#include "stdio.h"

	void GPIO_DRV_Init(void)
	{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
			RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

			GPIOA->CRL &= ~(0xF << 0);
			GPIOA->CRL |=  (0x0 << 0);
			
	}

	static void delay_ms(uint32_t ms)
	{
			volatile uint32_t i,j;

			for(i=0;i<ms;i++)
					for(j=0;j<1000;j++);
	}

	void ADC_DRV_Init(void)
	{
			RCC ->APB2ENR |= RCC_APB2ENR_ADC1EN ;
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

			GPIOA->CRL &= ~(0xF << 0);//mode input analog PA0
		
			ADC1->CR2 |= (1 <<20); //EXTTRIG
			ADC1->CR1 &= ~(1 << 8 ) ; //scan mode
			ADC1->CR2 &= ~(1 << 11) ;// right alignment
			ADC1->CR2 &=~(1 <<1); //continuous conversion mode off
			ADC1->CR2 |= (1 << 0); //ADC on
			delay_ms(20);// yeu cau cua stm32
			ADC1->SMPR2 &= ~(7<<0); //clear sampling trc
			ADC1->SMPR2 |= (7 << 0) ; // 239,5 cycles
			ADC1->SQR3 = 0; // channel 0 
			/* Reset calibration */
			ADC1->CR2 |= (1 << 3);
			while(ADC1->CR2 & (1 << 3));
			/* Start calibration */
			ADC1->CR2 |= (1 << 2);
			while(ADC1->CR2 & (1 << 2));
			ADC1->CR2 |= (1 << 8); //ADC enable DMA
	}

	void ADC_DRV_Start(void)
	{
			ADC1->CR2 |= ADC_CR2_ADON;
			ADC1->CR2 |= (1 << 22); //SWSTART
	}
	//test ADC raw
	uint16_t ADC_Read(void)
	{
			ADC1->CR2 |= (1 <<22);

			while(!(ADC1->SR & ADC_SR_EOC));//wait EOC ( quan trong)

			return ADC1->DR;
	}


	#define ADC_BUFFER_SIZE 256

	volatile uint16_t adc_buffer[2][ADC_BUFFER_SIZE]; //adc_buffer[number][size]

	volatile uint8_t buffer_ready[2] = {0, 0};

	volatile uint8_t current_dma_buffer = 0;

	void DMA_DRV_Init(void)
	{
			RCC->AHBENR |= RCC_AHBENR_DMA1EN;

		DMA1_Channel1->CPAR = (uint32_t)&ADC1->DR; //Peripheral address
		DMA1_Channel1->CMAR = (uint32_t)adc_buffer[0]; //memory address
		DMA1_Channel1->CNDTR = ADC_BUFFER_SIZE; //samples
		DMA1_Channel1->CCR &= ~(1 << 4);//direction :perepherial -> memmory
		DMA1_Channel1->CCR |= (1 << 7);//mem increment
		DMA1_Channel1->CCR &= ~(1 << 6);//peri incre
		
		DMA1_Channel1->CCR &= ~(3 << 8);
		DMA1_Channel1->CCR |= (1 << 8);//P size
		
		DMA1_Channel1->CCR &= ~(3 << 10);
		DMA1_Channel1->CCR |= (1 << 10);// M size
		DMA1_Channel1->CCR |= (1 << 5); //circular mode on
		DMA1_Channel1->CCR |= (1 << 1);//transfer complete interrupt
		
		DMA1_Channel1->CCR |= (1 << 0);//enable DMA
		NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	}

	void DMA_SwitchBuffer(uint32_t addr, uint16_t size) //ping pong buffering
	{
					DMA1_Channel1->CCR &=~(1 << 0);//disenable DMA channel

					DMA1_Channel1->CMAR = addr;//doi memory address

					DMA1_Channel1->CNDTR = size; //reload transfer count

					DMA1_Channel1->CCR |= (1 << 0);//enable lai
	}

	typedef void (*dma_callback_t)(void);

	static void (*dma_tc_callback)(void) = 0;//variable luu adress function 

	void DMA_RegisterCallback(dma_callback_t cb) //luu address cua func DMA_RegisterCallback 
	{
			dma_tc_callback = cb;
	}

	void DMA1_Channel1_IRQHandler(void)
	{
			if(DMA1->ISR & DMA_ISR_TCIF1)
			{
					//clear interupt flag
					DMA1->IFCR |= DMA_IFCR_CTCIF1; //thua chu |
				
			if(dma_tc_callback)
					{
							dma_tc_callback();
					}
		}
	}


	void TIM4_DRV_Init(void)
	{
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

		// enable clock for TIM4
			// configure PSC and ARR for 5 ms period
			// enable update interrupt
			// enable TIM4 interrupt in NVIC
			// start timer
			TIM4->PSC = 71;           //cycle of interrupt
			TIM4->ARR = 124;            // frequency

			TIM4->DIER |= (1 << 0);     // Update interrupt enable

			NVIC_EnableIRQ(TIM4_IRQn);  // enable interrupt in NVIC
		
				TIM4->CNT=0;
				TIM4->CR1 |= (1 <<0);// start timer
	}

	void TIM4_IRQHandler(void)
	{
			if (TIM4->SR &  TIM_SR_UIF) {      //check flag, UIF = update interrupt flag
				 TIM4->SR &= ~TIM_SR_UIF;      // clear flag , neu ko clear thi se treo o buoc tren luon
		//trigger ADC here
					ADC_DRV_Start();
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
		
		USART1->BRR = 0x138; //115200   ; 0x27: 921600
		
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

	volatile uint8_t overflow_detected = 0;

	//static uint32_t current_sector = 100;

	/*------------------------------------------------------------------*/
	/* DMA callback                                                     */
	/*------------------------------------------------------------------*/
	void APP_DMA_TransferComplete_Callback(void)
	{
			buffer_ready[current_dma_buffer] = 1;

			current_dma_buffer ^= 1;

			if(buffer_ready[current_dma_buffer])
			{
				  overflow_detected = 1;
			}

			DMA_SwitchBuffer(
					(uint32_t)adc_buffer[current_dma_buffer],
					ADC_BUFFER_SIZE
			);
	}

	/*------------------------------------------------------------------*/
	/* Init                                                             */
	/*------------------------------------------------------------------*/
	void APP_Init(void)
	{
			UART1_DRV_Init();

			GPIO_DRV_Init();

			ADC_DRV_Init();

			DMA_DRV_Init();
			DMA_RegisterCallback(
					APP_DMA_TransferComplete_Callback
			);

			TIM4_DRV_Init();

			SPI1_DRV_Init();

	}

	int main(void)
	{
			APP_Init();

			ADC_DRV_Start();

			while(1)
			{
				
					if(buffer_ready[0])
					{
							buffer_ready[0]=0;

							for(int i=0;i<ADC_BUFFER_SIZE;i++)
							{
									char msg[16];

									sprintf(
											msg,
											"%u\r\n",
											adc_buffer[0][i]
									);

									UART1_SendString(msg);
							}
					}

					if(overflow_detected)
	{
			UART1_SendString("OVF\r\n");
	    overflow_detected = 0;
	}

					if(buffer_ready[1])
					{
							buffer_ready[1]=0;

							for(int i=0;i<ADC_BUFFER_SIZE;i++)
							{
									char msg[16];

									sprintf(
											msg,
											"%u\r\n",
											adc_buffer[1][i]
									);

									UART1_SendString(msg);
							}
					}
			}
	}
