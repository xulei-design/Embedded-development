#ifndef __UART_H__
#define __UART_H__

#include <reg51.h>
#include <stdio.h>

void UartInit();
void sendByte(unsigned char dat);
char putchar(char c);
extern unsigned char rev_flag; //��main.c����Ҫʹ��
extern unsigned char rev_data; //ȫ�ֱ���������

#endif