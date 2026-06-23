#include "stm32f10x.h"
#include "i2c_drv.h"

void I2C_DRV_Init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    I2C1->CR2 = 36;

    I2C1->CCR = 180;

    I2C1->TRISE = 37;

    I2C1->CR1 |= I2C_CR1_PE;

    I2C1->CR1 |= I2C_CR1_ACK;
}

void I2C_Start(void)
{
    I2C1->CR1 |= I2C_CR1_START;

    while(!(I2C1->SR1 & I2C_SR1_SB));
}

void I2C_Stop(void)
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C_SendAddress(uint8_t addr)
{
    I2C1->DR = addr;

    while(!(I2C1->SR1 & I2C_SR1_ADDR));

    (void)I2C1->SR2;
}

void I2C_WriteByte(uint8_t data)
{
    while(!(I2C1->SR1 & I2C_SR1_TXE));

    I2C1->DR = data;

    while(!(I2C1->SR1 & I2C_SR1_BTF));
}

uint8_t I2C_ReadByte_NACK(void)
{
    uint8_t data;

    I2C1->CR1 &= ~I2C_CR1_ACK;

    while(!(I2C1->SR1 & I2C_SR1_RXNE));

    data = I2C1->DR;

    I2C1->CR1 |= I2C_CR1_ACK;

    return data;
}
