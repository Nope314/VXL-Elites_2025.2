#ifndef __M45PE80_H
#define __M45PE80_H

#include "stm32f10x.h"
#include <stdint.h>

#define FLASH_CS_LOW()     GPIOA->BRR = (1 << 4); //chon card
#define FLASH_CS_HIGH()    GPIOA->BSRR = (1 << 4); //bo card

// Command
#define CMD_WREN           0x06
#define CMD_WRDI           0x04
#define CMD_RDSR           0x05
#define CMD_READ           0x03
#define CMD_PP             0x02
#define CMD_SE             0xD8
#define CMD_PE             0xDB

void SPI1_Init(void);

void M45PE80_Init(void);

uint8_t M45PE80_ReadStatus(void);

void M45PE80_WriteEnable(void);

void M45PE80_WaitBusy(void);

void M45PE80_ReadData(uint32_t addr, uint8_t *buf, uint16_t len);

void M45PE80_PageProgram(uint32_t addr, uint8_t *buf, uint16_t len);

void M45PE80_SectorErase(uint32_t addr);

#endif
