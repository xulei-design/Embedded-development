#include<reg51.h>


sbit LED = P1^0;
unsigned char timer0_Cnt;
void Timer0Init(void);
void main()
{
	Timer0Init();
	while(1);
}

void Timer0Init(void)		//50毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式 GATE C/T M0 M1
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初值 (65535-50000)%256
	TH0 = 0x3C;		//设置定时初值 (65535-50000)/256
	TF0 = 0;		//清除TF0标志
	ET0 = 1;
	EA = 1;  //打开中断
	TR0 = 1;		//定时器0开始计时
}

void timer0_ISR() interrupt 1
{
	TL0 = 0xB0;		//设置定时初值 (65535-50000)%256
	TH0 = 0x3C;
	timer0_Cnt++;
	if(timer0_Cnt>=10)
	{
		LED = ~LED;	
}	}

