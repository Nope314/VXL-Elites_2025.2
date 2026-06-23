#include "app.h"

#include "gpio_drv.h"
#include "i2c_drv.h"
#include "uart_drv.h"
#include "systick_drv.h"

#include "at24cxx.h"

//file day du de chung 1 chuong trinh o trong file main trong folder I2C_AT24C256
char buf1[10];
char buf2[10];

static void APP_EEPROM_WriteDone_Callback(void)
{
    UART1_SendString("...\r\n");
}

void APP_Init(void)
{
    GPIO_DRV_Init();

    I2C_DRV_Init();

    SysTick_DRV_Init();

    UART1_DRV_Init();

    EEPROM_RegisterWriteDoneCallback(
        APP_EEPROM_WriteDone_Callback
    );
}

void APP_Run(void)
{
    UART1_SendString("EEPROM TEST\r\n");

    EEPROM_WriteString(EEPROM1_ADDR,
                       0x0000,
                       "1 LOVE");

    EEPROM_ReadString(EEPROM1_ADDR,
                      0x0000,
                      buf1,
                      6);

    UART1_SendString("EEPROM1: ");
    UART1_SendString(buf1);
    UART1_SendString("\r\n");

    EEPROM_WriteString(EEPROM2_ADDR,
                       0x0000,
                       "1 EDABK");

    EEPROM_ReadString(EEPROM2_ADDR,
                      0x0000,
                      buf2,
                      7);

    UART1_SendString("EEPROM2: ");
    UART1_SendString(buf2);
    UART1_SendString("\r\n");

    while(1)
    {

    }
}
