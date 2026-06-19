#include "app.h"

#include "gpio_drv.h"
#include "i2c_drv.h"
#include "uart_drv.h"
#include "systick_drv.h"

#include "esp32.h"

//file day du de chung 1 chuong trinh o trong file main trong folder I2C_AT24C256
char buf1[10];
char buf2[10];
/*
static void APP_esp32_WriteDone_Callback(void)
{
    UART1_SendString("...\r\n");
}
*/
void APP_Init(void)
{
    GPIO_DRV_Init();

    I2C_DRV_Init();

    SysTick_DRV_Init();

    //UART1_DRV_Init();
/*
    esp32_RegisterWriteDoneCallback(
        APP_esp32_WriteDone_Callback
    );
	*/
}

void APP_Run(void)
{
    uint8_t txBuf1[] = "1 LOVE";
    uint8_t txBuf2[] = "1 EDABK";

    //UART1_SendString("ESP32 TEST\r\n");

    //string 1
    esp32_WriteBuffer(ESP32_ADDR,
                      0x01,
                      txBuf1,
                      sizeof(txBuf1) - 1);

    //read again
    esp32_ReadBuffer(ESP32_ADDR,
                     0x01,
                     (uint8_t *)buf1,
                     6);
   // buf1[6] = '\0';

    //UART1_SendString("ESP321: ");
    //UART1_SendString(buf1);
    //UART1_SendString("\r\n");

    //string 2
    esp32_WriteBuffer(ESP32_ADDR,
                      0x01,
                      txBuf2,
                      sizeof(txBuf2) - 1);

    //read again 
    esp32_ReadBuffer(ESP32_ADDR,
                     0x01,
                     (uint8_t *)buf2,
                     6);
    //buf2[6] = '\0';

    //UART1_SendString("ESP322: ");
    //UART1_SendString(buf2);
    //UART1_SendString("\r\n");

    while (1)
    {

    }
}

