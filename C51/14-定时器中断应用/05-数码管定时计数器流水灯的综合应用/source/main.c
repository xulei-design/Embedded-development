#include<reg51.h>
#include"display.h"
#include<intrins.h>




unsigned char secCnt;
unsigned char temp = 0xfe;
unsigned char sec = 60;
unsigned char timerCnt;
void Timer0Init(void);
void Timer1Init(void);
void main()
{
	Timer0Init();
	Timer1Init();
	EA = 1;
	while(1)
	{
		LEDBuf[2]=sec/10;
		LEDBuf[3]=sec%10;
	}

}


void Timer0Init(void)		//1毫秒@12.000MHz
{
	
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
}


void  timer0_ISR(void) interrupt 1
{
	TR0 = 0;
	Display();
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;
	TR0 = 1;
}

void Timer1Init(void)		//50毫秒@12.000MHz
{
	
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x10;
	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1 = 1;
}

void  timer1_ISR(void) interrupt 3
{
	TR1 = 0;
	secCnt++;
	timerCnt++;
	if(timerCnt>=10)
	{
		timerCnt=0;
		P1 = temp;
		temp = _cror_(temp,1);
	}
	if(secCnt>=20)
	{
		secCnt=0;
		sec--;
		if(sec>60)
			sec =60;
	}

	TL1 = 0xB0;		//设置定时初值
	TH1 = 0x3C;
	TR1 = 1;
}