#include "at24cxx.h"
#include "i2c_drv.h"
#include "systick_drv.h"

static eeprom_callback_t write_done_callback = 0;//dia chi chua ham callback

void EEPROM_RegisterWriteDoneCallback(eeprom_callback_t cb)
{
    write_done_callback = cb;
}

void EEPROM_WriteByte(uint8_t devAddr,
                      uint16_t memAddr,
                      uint8_t data)
{
    I2C_Start();

    I2C_SendAddress(devAddr);

    I2C_WriteByte((memAddr >> 8) & 0xFF);

    I2C_WriteByte(memAddr & 0xFF);

    I2C_WriteByte(data);

    I2C_Stop();

    delay_ms(10);

    if(write_done_callback)
    {
        write_done_callback();
    }
}

uint8_t EEPROM_ReadByte(uint8_t devAddr,
                        uint16_t memAddr)
{
    uint8_t data;

    I2C_Start();

    I2C_SendAddress(devAddr);

    I2C_WriteByte((memAddr >> 8) & 0xFF);

    I2C_WriteByte(memAddr & 0xFF);

    I2C_Start();

    I2C_SendAddress(devAddr | 0x01);

    data = I2C_ReadByte_NACK();

    I2C_Stop();

    return data;
}

void EEPROM_WriteString(uint8_t devAddr,
                        uint16_t memAddr,
                        char *str)
{
    while(*str)
    {
        EEPROM_WriteByte(devAddr,
                         memAddr++,
                         *str++);
    }
}

void EEPROM_ReadString(uint8_t devAddr,
                       uint16_t memAddr,
                       char *buffer,
                       uint16_t len)
{
    uint16_t i;

    for(i = 0; i < len; i++)
    {
        buffer[i] = EEPROM_ReadByte(devAddr,
                                    memAddr + i);
    }

    buffer[len] = '\0';
}
