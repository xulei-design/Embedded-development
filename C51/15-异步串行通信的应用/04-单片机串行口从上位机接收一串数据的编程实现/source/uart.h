#ifndef __UART_H__
#define __UART_H__

#include <reg51.h>
#include <stdio.h>

#define MAX_REV_NUM 13
#define REV_CNT 10


void UartInit();
void sendByte(unsigned char dat);
void sendString(unsigned char *dat);
char putchar(char c);
extern unsigned char recv_flag;
extern unsigned char recv_buf[];
extern unsigned char recv_length;

#endif