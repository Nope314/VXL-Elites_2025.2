#include "stm32f10x.h"
#include "m45pe80.h"
#include "uart.h"

uint8_t tx_data[] = "HELLO FLASH";

uint8_t rx_data[32];

int main(void)
{
		
    uint8_t i;

    UART1_Init();

    M45PE80_Init();

    UART1_SendString("Start NOR Flash Test\r\n");

    // erase
    UART1_SendString("Erase Sector...\r\n");

    M45PE80_SectorErase(0x000000);

    UART1_SendString("Erase Done\r\n");

    // write
    UART1_SendString("Write Data...\r\n");

    M45PE80_PageProgram(0x000000, tx_data, sizeof(tx_data));

    UART1_SendString("Write Done\r\n");

    // read
    UART1_SendString("Read Data...\r\n");

    M45PE80_ReadData(0x000000, rx_data, sizeof(tx_data));

    UART1_SendString("Data =");

    for(i = 0; i < sizeof(tx_data); i++)
    {
        UART1_SendChar(rx_data[i]);
    }

    UART1_SendString("\r\n");

    while(1)
    {

    }
}

