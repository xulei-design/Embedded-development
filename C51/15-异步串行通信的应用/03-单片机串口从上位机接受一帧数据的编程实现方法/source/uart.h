#ifndef __UART_H__
#define __UART_H__

#include <reg51.h>
#include <stdio.h>

void UartInit();
void sendByte(unsigned char dat);
char putchar(char c);
extern unsigned char rev_flag; //在main.c中需要使用
extern unsigned char rev_data; //全局变量的声明

#endif