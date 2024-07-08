#include<reg51.h>
#include"display.h"	

unsigned char DIS_u();
void DIS_Service();
void Timer0Init(void);
void EX0_Init();
void EX1_Init();
unsigned int numCnt = 0;//参数
unsigned char temp0;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
void main()
{
	Timer0Init();
	EX0_Init();
	EX1_Init();
	EA = 1;	 //中断总开关
	while(1)
	{
		DIS_Service();
	}

}

void DIS_Service()
{
	temp0 = numCnt/1000;
	temp1 = numCnt/100%10;
	temp2 =	numCnt/10%10;
	temp3 = numCnt%10;
	if(numCnt < 1000)
		LEDBuf[0]=22;
	else
		LEDBuf[0]=temp0;
	if(numCnt < 100)
		LEDBuf[1]=22;
	else
		LEDBuf[1]=temp1;
	if(numCnt < 10)
		LEDBuf[2]=22;
	else
		LEDBuf[2]=temp2;
		LEDBuf[3]=temp3;

}
void Timer0Init(void)		//1毫秒@11.0592MHz
{

	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;

}

void EX0_Init()
{
	IT0 = 1;  //触发方式，下降沿
	EX0 = 1;  //打开外部中断
	
}

void EX1_Init()
{
	IT1 = 1;  //触发方式，下降沿
	EX1 = 1;  //打开外部中断
	
}
void timer0_ISR(void) interrupt 1	//定时器T0中断服务函数
{
	TR0 = 0;
	Display();
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;
	TR0 = 1;
}

void EX0_ISR(void) interrupt 0	   //外部中断的0的服务函数
{
	EX0 = 0;
	numCnt++;
	if(numCnt>9999)
		numCnt = 0;
	EX0 = 1;	
}
void EX1_ISR(void) interrupt 2	   //外部中断的1的服务函数
{
	EX1 = 0;
	numCnt--;
	if(numCnt > 10000)
		numCnt = 9999;
	EX1 = 1;		
	
}