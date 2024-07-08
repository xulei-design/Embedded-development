#include<reg51.h>
#include"display.h"

unsigned int num;
unsigned int timeCnt;
void Timer0Init(void);
void Timer1Init(void);
void DIS_service();
void main()
{
	Timer0Init();
	Timer1Init();
	EA = 1;
	while(1)
	{	
		DIS_service();
	}
}

void DIS_service()
{
	LEDBuf[0] = num/1000;
	LEDBuf[1] = num/100%10;
	LEDBuf[2] = num/10%10;
	LEDBuf[3] = num%10;
}

void Timer0Init(void)		//1毫秒@11.0592MHz
{
	
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0X01;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
}

void Timer0_ISR(void) interrupt 1
{	
	TR0 = 0;
	timeCnt++;
	if(timeCnt >= 1000) //1s时间到	适合高频，低频误差较大
	{
		TR1 = 0;   //脉冲发生器关闭
		timeCnt = 0;  //脉冲计数清0；
		num = TH1*256+TL1; //高八位左移8位，取出计数脉冲 ，频率：1s中产生多少脉冲
		TH1 = TL1 =0;  //将脉冲计数器中的值清零
		TR1 = 1;	
	}
	Display();
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;
	TR0 = 1;
}
void Timer1Init(void)  //计数，是对外部脉冲进行计数
{
	TMOD &= 0x0f;  //保留高四位，低四位清零
	TMOD |= 0x50;  //或上 0101 0000
	TL1 = 0;   //计数脉冲数
	TH1 = 0;
	TF1 = 0;
	TR1 = 1;
	ET1 = 1;
}
