#ifndef __UART_H__
#define __UART_H__

#include <reg51.h>
#include <stdio.h>
void UartInit(void);
void sendByte(unsigned char dat);
void sendString(unsigned char *dat);
char putchar(char c);

#endif