#ifndef __UART_H__
#define __UART_H__

#include <reg51.h>
#include <stdio.h>

#define MAX_REV_NUM 20
#define MAX_REV_TIM 3


void UartInit();
void sendByte(unsigned char dat);
void sendString(unsigned char *dat);
void clr_recvbuffer(unsigned char *buf);
char putchar(char c);

extern unsigned char recv_cnt;
extern unsigned char recv_buf[];
extern unsigned char recv_flag;
extern unsigned int beep_data;
extern unsigned int beep_cnt;
extern unsigned int led_cnt;
extern unsigned int led_data;

#endif