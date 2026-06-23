#include "stm32f10x.h"
#include "stdint.h"

#define EEPROM1_ADDR  0xA0
#define EEPROM2_ADDR  0xA2
//I2C1_SCL  PB6
//I2C1_SDA  PB7


void GPIO_clock_enable()
{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN ;
		RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN ;
		RCC -> APB1ENR |= RCC_APB1ENR_I2C1EN ;
}

void GPIO_Pin_Init(){
		// PB6 SCL
		GPIOB->CRL &= ~(0xFU << 24);
		GPIOB->CRL |=  (0xFU << 24); // Alternate Function Open Drain
		// PB7 SDA
		GPIOB->CRL &= ~(0xFU <<28);
		GPIOB->CRL |= (0xFU << 28);  //Alternate Function Open Drain
}

void I2C_Init(){
    // Reset I2C
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST; //reset

    // Peripheral clock frequency (MHz)
    I2C1->CR2 = 36;  // 36MHz

    // Clock control (100kHz)
    I2C1->CCR = 180; // CCR= FPCLK1 / (2 * FSCL) voi Fpclk1 = 36MHz , Fsc1 = 100kHz

    // Maximum rise time
    I2C1->TRISE = 37; 
	// trong standard mode : t_rise max =1000ns, T_pclk1=1/36Mhz
	// TRISE = (t_rise/T_pclk1) +1

    // Enable I2C
    I2C1->CR1 |= I2C_CR1_PE;
		
		//enable ACK
		I2C1->CR1 |= I2C_CR1_ACK;
}

void I2C_Start()
{
    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB)); // doi gui start xog
}

void I2C_SendAddress(uint8_t address)
{
    I2C1->DR = address;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2; //doc SR2 thi tu dong clear flag cho byte trc do
}

void I2C_Write(uint8_t data)
{
    while (!(I2C1->SR1 & I2C_SR1_TXE));
    I2C1->DR = data;
	 
	  while (!(I2C1->SR1 & I2C_SR1_BTF));//dam bao byte da gui xong
}

void I2C_Stop()
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

volatile uint32_t tick =0 ;

void SysTick_Init()
{
    SysTick->LOAD = 72000 - 1; // 1ms 
    SysTick->VAL = 0;
    SysTick->CTRL = 7; //(0b111 enable ,interupt, dung clock CPU)	
}

void SysTick_Handler()
{
    tick++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = tick;
    while ((tick - start) < ms);
}

void EEPROM_WriteByte(uint8_t devAddr, uint16_t memAddr, uint8_t data)
{
    I2C_Start();

    I2C_SendAddress(devAddr);

    // Memory Address High
    I2C_Write((memAddr >> 8) & 0xFF);

    // Memory Address Low
    I2C_Write(memAddr & 0xFF);

    // Data
    I2C_Write(data);

    I2C_Stop();

    // wait write cycle
    delay_ms(10);
}

uint8_t EEPROM_ReadByte(uint8_t devAddr, uint16_t memAddr)
{
    uint8_t data;

    // Send memory address
    I2C_Start();

    I2C_SendAddress(devAddr);

    I2C_Write((memAddr >> 8) & 0xFF);

    I2C_Write(memAddr & 0xFF);

    // Repeated START
    I2C_Start();

    // Read mode
    I2C_SendAddress(devAddr | 0x01);

    // Disable ACK for single byte
    I2C1->CR1 &= ~I2C_CR1_ACK;

    while(!(I2C1->SR1 & I2C_SR1_RXNE));

    data = I2C1->DR;

    I2C_Stop();

    // Re-enable ACK
    I2C1->CR1 |= I2C_CR1_ACK;

    return data;
}

void EEPROM_WriteString(uint8_t devAddr, uint16_t memAddr, char *str)
{
    while(*str)
    {
        EEPROM_WriteByte(devAddr, memAddr++, *str++);
    }
}

void EEPROM_ReadString(uint8_t devAddr, uint16_t memAddr, char *buffer, uint16_t len)
{
    uint16_t i;

    for(i = 0; i < len; i++)
    {
        buffer[i] = EEPROM_ReadByte(devAddr, memAddr + i);
    }

    buffer[len] = '\0';
}


void UART1_DRV_Init(void)
{
    RCC ->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

    // PA9 TX
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    // PA10 RX
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);
	//baudrate : 9600
    USART1->BRR = 0x1D4C;

   USART1->CR1 |= (1 <<3); //TX
	USART1->CR1 |= (1 <<2);//RX
	
	USART1->CR1 |= (1 <<13); //USART Enable
}

void UART1_SendChar(char c)
{
    while(!(USART1->SR & USART_SR_TXE)); //check xem ready chua

    USART1->DR = c;
}

void UART1_SendString(char *s) //con tro toi string
{
    while(*s) //ky tu khac /0
    {
        UART1_SendChar(*s++);
    }
}

char buf1[10];
char buf2[10];

int main()
{
    GPIO_clock_enable();

    GPIO_Pin_Init();

    I2C_Init();

    SysTick_Init();

    UART1_DRV_Init();

    UART1_SendString("EEPROM TEST\r\n");

    // EEPROM1
    EEPROM_WriteString(EEPROM1_ADDR, 0x0000, "HELLO");

		UART1_SendString("DONE\r\n");
    EEPROM_ReadString(EEPROM1_ADDR, 0x0000, buf1, 5);

    UART1_SendString("EEPROM1: ");
    UART1_SendString(buf1);
    UART1_SendString("\r\n");

    // EEPROM2
    EEPROM_WriteString(EEPROM2_ADDR, 0x0000, "WORLD");

    EEPROM_ReadString(EEPROM2_ADDR, 0x0000, buf2, 5);

    UART1_SendString("EEPROM2: ");
    UART1_SendString(buf2);
    UART1_SendString("\r\n");

    while(1)
    {

    }
}
		
