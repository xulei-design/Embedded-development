#include<reg51.h>
#include"display.h"

	
sbit LED = P1^0;
unsigned int systemTimer = 0;
unsigned char systemFlag = 1;
unsigned int Num=9875;
void Timer0Init(void);
void Dis_Service();
void main()
{
		
	Timer0Init();
	do
	{
		if(systemTimer%50==0) //开机指示
		LED = ~LED;	
	}while(systemTimer<5000); // 5S 5000ms/1ms
	systemFlag = 0;
	LED = 1;
	while(1)		 //while(1) 与定时器并行
	{
		Dis_Service();
	}
}


void Timer0Init(void)		//1毫秒@12.000MHz
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;   //设置定时器模式
    TL0 = 0x0C;		//设置定时初值
	TH0 = 0xFE;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	EA = 1;
	ET0 = 1;
	TR0 = 1;		//定时器0开始计时
}



void Dis_Service()
{
	LEDBuf[0] = Num/1000;
	LEDBuf[1] = Num/100%10;
	LEDBuf[2] = Num/10%10;
	LEDBuf[3] = Num%10;
}


void timer0_ISR(void) interrupt 1
{

	TR0 = 0;
	if(systemFlag == 1)
	{
		systemTimer++;	
	}
	
	Display();
    TL0 = 0x0C;		//设置定时初值
	TH0 = 0xFE;		//设置定时初值
	TR0 = 1;
}
