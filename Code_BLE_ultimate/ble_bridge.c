#include "ble_bridge.h"
#include "uart_drv.h"
#include "stm32f10x.h"

void BLE_Bridge_Task(void)
{
    if(UART1_Available())
    {
        char c = UART1_ReadChar();

        // Debug
        UART2_SendChar(c);

        if(c == '1')
        {
            // LED ON 
            GPIOA->BSRR = GPIO_BRR_BR0;

            UART2_SendString("\r\nLED ON\r\n");
        }

        if(c == '0')
        {
            // LED OFF
            GPIOA->BRR = GPIO_BSRR_BS0;

            UART2_SendString("\r\nLED OFF\r\n");
        }
    }
}
