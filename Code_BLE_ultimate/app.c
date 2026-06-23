#include "app.h"
#include "uart_drv.h"
#include "ble_bridge.h"

void APP_Init(void)
{
    UART1_DRV_Init();
    UART2_DRV_Init();

    UART2_SendString("\r\n");
    UART2_SendString("System Start\r\n");
}

void APP_Task(void)
{
    BLE_Bridge_Task();
}
