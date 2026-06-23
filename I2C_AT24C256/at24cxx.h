#ifndef AT24CXX_H
#define AT24CXX_H

#include <stdint.h>

#define EEPROM1_ADDR  0xA0
#define EEPROM2_ADDR  0xA2

typedef void (*eeprom_callback_t)(void);

void EEPROM_RegisterWriteDoneCallback(eeprom_callback_t cb);

void EEPROM_WriteByte(uint8_t devAddr,uint16_t memAddr, uint8_t data);

uint8_t EEPROM_ReadByte(uint8_t devAddr, uint16_t memAddr);

void EEPROM_WriteString(uint8_t devAddr, uint16_t memAddr,char *str);

void EEPROM_ReadString(uint8_t devAddr,uint16_t memAddr,char *buffer, uint16_t len);

#endif
