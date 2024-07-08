#include <reg51.h>
#include <intrins.h>
#include "delay.h"

void UartInit(void);
unsigned char temp = 0x01;
void main()
{
    UartInit();	
    while(1)
    {
        SBUF = temp; //工作方式1，10位异步串口通信 0 1000 1000 1
        while(!TI)  // 停止等待
        TI = 0;
        P1 = temp;
        temp = _crol_(temp,1);
        delayxms(1000);
    }  
}

void UartInit(void)	//4800bps@11.0592MHz   波特率的设置
{
	SCON = 0x50;		
 //8位数据,可变波特率 SM0（高位） SM1 (设置工作方式）SM2（多机通信使能） REN（允许串行接收位）
 // TB8 RB8（配合工作3使用） TI(发送中断标志位) RI(接收中断标志位）
 // SM0 SM1 SM2 REN TB8 RB8 TI RI
 //  0   1   0   1   0   0   0  0 （0x50）
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1（工作方式2）为8位自动重装方式  M0 M1 C/T GATE M0 M1 C/T GATE
	TL1 = 0xFA;		//设定定时初值                                   0  0   0   0   0  1  0   0
	TH1 = 0xFA;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}
