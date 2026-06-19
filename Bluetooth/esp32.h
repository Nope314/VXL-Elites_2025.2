#ifndef ESP32_H
#define ESP32_H

#include <stdint.h>

#define ESP32_ADDR 0x55

//typedef void (*esp32_callback_t)(void);

//void esp32_RegisterWriteDoneCallback(esp32_callback_t cb);

void esp32_WriteByte(uint8_t devAddr,
                     uint8_t cmd,
                     uint8_t data);

uint8_t esp32_ReadByte(uint8_t devAddr,
                       uint8_t cmd);

void esp32_WriteBuffer(uint8_t devAddr,
                       uint8_t cmd,
                       uint8_t *buffer,
                       uint16_t len);

void esp32_ReadBuffer(uint8_t devAddr,
                      uint8_t cmd,
                      uint8_t *buffer,
                      uint16_t len);

#endif
