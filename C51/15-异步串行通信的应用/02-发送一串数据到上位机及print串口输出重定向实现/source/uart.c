#include "uart.h"

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
   // ES = 1;         //串行中断打开
    // EA = 1;
}

void sendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);  //查询方式，当TI=0时，一直等待，直到TI = 1，执行下一条语句。
		TI = 0;
}

void sendString(unsigned char *dat) 
{
   while(*dat != '\0')
   {
        sendByte(*(dat++)); //*dat代表的是首地址 *dat = &dat
   }       
}

char putchar(char c) //c语言中是打印到屏幕，现在让它打印到串口，定向到串口
{
    sendByte(c);
    return c;
}


