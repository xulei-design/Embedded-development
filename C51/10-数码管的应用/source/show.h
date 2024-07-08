#ifndef __SHOW_H__
#define __SHOW_H__

#include"Delay.h" //因为display.c文件中用到了delay函数
#include<reg51.h> //包含51头文件，用于识别P1,P2
#define GPIO_DIG     P1 //段码 I/O口的宏定义
#define GPIO_PLACE   P2 //位选 I/O口的宏定义
#define     N	     4	//常量的宏定义

unsigned char code leddata[];  //变量的声明
extern unsigned char LEDBuf[]; //全局变量，主函数中需要调用，要定义成外部变量，方便调用


void Show();	 //函数的声明

#endif