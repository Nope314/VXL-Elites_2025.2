#include "esp32.h"
#include "i2c_drv.h"
#include "systick_drv.h"
/*
static esp32_callback_t write_done_callback = 0;//dia chi chua ham callback

void esp32_RegisterWriteDoneCallback(esp32_callback_t cb)
{
    write_done_callback = cb;
}
*/
void esp32_WriteByte(uint8_t devAddr,
                     uint8_t cmd,
                     uint8_t data)
{
    I2C_Start();

    I2C_SendAddress(devAddr,0);

    I2C_WriteByte(cmd);

    I2C_WriteByte(data);

    I2C_Stop();
/*
    if(write_done_callback)
			write_done_callback();
*/
	}
	

uint8_t esp32_ReadByte(uint8_t devAddr,
                       uint8_t cmd)
{
    uint8_t data;

    I2C_Start();

    I2C_SendAddress(devAddr,0);

    I2C_WriteByte(cmd);

    I2C_Start();//restart

    I2C_SendAddress(devAddr,1);

    data = I2C_ReadByte_NACK();

    I2C_Stop();

    return data;
}
void esp32_WriteBuffer(uint8_t devAddr,
                       uint8_t cmd,
                       uint8_t *buffer,
                       uint16_t len)
{
    uint16_t i;

    I2C_Start();

    I2C_SendAddress(devAddr,0);

    I2C_WriteByte(cmd);
	
	if(len == 0)
{
    I2C_Stop();
    return;
}

    for(i=0;i<len;i++)
    {
        I2C_WriteByte(buffer[i]);
    }

    I2C_Stop();
/*
    if(write_done_callback)
        write_done_callback();
*/
		}
void esp32_ReadBuffer(uint8_t devAddr,
                      uint8_t cmd,
                      uint8_t *buffer,
                      uint16_t len)
{
    uint16_t i;

    I2C_Start();

    I2C_SendAddress(devAddr,0);

    I2C_WriteByte(cmd);

    I2C_Start();

    I2C_SendAddress(devAddr,1);

		if(len == 0)
{
    I2C_Stop();
    return;
}

    for(i=0;i<(len-1);i++)
    {
        buffer[i] = I2C_ReadByte_ACK();
    }

    buffer[len-1] = I2C_ReadByte_NACK();

    I2C_Stop();
}
