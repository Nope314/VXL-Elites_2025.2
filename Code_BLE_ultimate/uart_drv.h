#ifndef UART_DRV_H
#define UART_DRV_H

void UART1_DRV_Init(void);
void UART2_DRV_Init(void);

void UART1_SendChar(char c);
void UART2_SendChar(char c);

void UART1_SendString(char *s);
void UART2_SendString(char *s);

char UART1_ReadChar(void);
char UART2_ReadChar(void);

int UART1_Available(void);
int UART2_Available(void);

#endif

