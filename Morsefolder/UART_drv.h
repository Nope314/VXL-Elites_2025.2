#ifndef UART_DRV_H
#define UART_DRV_H

void UART1_DRV_Init(void);

void UART1_SendChar(char c);
void UART1_SendString(char *s);

#endif
