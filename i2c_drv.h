#ifndef I2C_DRV_H
#define I2C_DRV_H

#include <stdint.h>

void I2C_DRV_Init(void);

void I2C_Start(void);

void I2C_Stop(void);

void I2C_SendAddress(uint8_t addr, uint8_t rw);

void I2C_WriteByte(uint8_t data);

uint8_t I2C_ReadByte_NACK(void);

uint8_t I2C_ReadByte_ACK(void);

#endif

