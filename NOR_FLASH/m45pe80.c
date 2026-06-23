#include "m45pe80.h"

static uint8_t SPI1_TransmitReceive(uint8_t data)
 { 
 while(!(SPI1->SR & SPI_SR_TXE)); //wait txe empty
 SPI1->DR = data;
	 while(!(SPI1->SR & SPI_SR_RXNE)); //wait rxne empty (sr: status)
 return SPI1->DR; 
 }

void SPI1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // PA5 SCK AF_PP 50MHz
    GPIOA->CRL &= ~(0xF << 20);
    GPIOA->CRL |=  (0xB << 20);

    // PA7 MOSI AF_PP 50MHz
    GPIOA->CRL &= ~(0xFU << 28);
    GPIOA->CRL |=  (0xBU << 28);

    // PA6 MISO input floating
    GPIOA->CRL &= ~(0xF << 24);
    GPIOA->CRL |=  (0x4 << 24);

    // PA4 CS output push-pull
    GPIOA->CRL &= ~(0xF << 16);
    GPIOA->CRL |=  (0x3 << 16);

    FLASH_CS_HIGH();

    SPI1->CR1 =
          SPI_CR1_MSTR
        | SPI_CR1_SSM
        | SPI_CR1_SSI;
         
		SPI1->CR1|=SPI_CR1_BR_1; // fPCLK/8

    SPI1->CR1 |= SPI_CR1_SPE; //SPI enable
}

void M45PE80_Init(void)
{
    SPI1_Init();
}

void M45PE80_WriteEnable(void)
{
    FLASH_CS_LOW();

    SPI1_TransmitReceive(CMD_WREN);

    FLASH_CS_HIGH();
}

uint8_t M45PE80_ReadStatus(void)
{
    uint8_t status;

    FLASH_CS_LOW();

    SPI1_TransmitReceive(CMD_RDSR);

    status = SPI1_TransmitReceive(0xFF);

    FLASH_CS_HIGH();

    return status;
}

void M45PE80_WaitBusy(void)
{
    while(M45PE80_ReadStatus() & 0x01);
}

void M45PE80_ReadData(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i;

    FLASH_CS_LOW();

    SPI1_TransmitReceive(CMD_READ);

    SPI1_TransmitReceive((addr >> 16) & 0xFF); //byte cao
    SPI1_TransmitReceive((addr >> 8) & 0xFF);	//byte giua
    SPI1_TransmitReceive(addr & 0xFF);//byte thap 

    for(i = 0; i < len; i++)
    {
        buf[i] = SPI1_TransmitReceive(0xFF); //TX gui 0xFF de tao clock ,luc do flash tra du lieu that qua MISO
    }

    FLASH_CS_HIGH();
}

void M45PE80_PageProgram(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i;

    M45PE80_WriteEnable();

    FLASH_CS_LOW();

    SPI1_TransmitReceive(CMD_PP);

    SPI1_TransmitReceive((addr >> 16) & 0xFF);
    SPI1_TransmitReceive((addr >> 8) & 0xFF);
    SPI1_TransmitReceive(addr & 0xFF);

    for(i = 0; i < len; i++)
    {
        SPI1_TransmitReceive(buf[i]);
    }

    FLASH_CS_HIGH();

    M45PE80_WaitBusy();
}

void M45PE80_SectorErase(uint32_t addr)
{
    M45PE80_WriteEnable();

    FLASH_CS_LOW();

    SPI1_TransmitReceive(CMD_SE);

    SPI1_TransmitReceive((addr >> 16) & 0xFF);
    SPI1_TransmitReceive((addr >> 8) & 0xFF);
    SPI1_TransmitReceive(addr & 0xFF);

    FLASH_CS_HIGH();

    M45PE80_WaitBusy();
}
