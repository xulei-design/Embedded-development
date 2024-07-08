#include<reg51.h>
#include"display.h"
#include"Delay.h"

void EX0_Init(void);
void EX1_Init(void);
void Dis_Service();
unsigned int pramater = 0;
void main()
{
	EX0_Init();
	EX1_Init();
	EA = 1;//中断的总开关
	while(1)
	{
		Dis_Service();
		Display();	
	}
}

void Dis_Service()
{
	LEDBuf[0] = pramater/1000;
	LEDBuf[1] = pramater/100%10;
	LEDBuf[2] = pramater/10%10;
	LEDBuf[3] = pramater%10;
}

void EX0_Init(void) //外部中断0初始化 
{
	IT0 = 1; //下降沿触发 
	EX0 = 1;
}
void EX1_Init(void) 
{
	IT1 = 1;
	EX1 = 1;
}


void EX0_ISR(void) interrupt 0 //外部中断1的中断服务函数
{
	pramater++;
	if(pramater > 9999)
		pramater = 0;
}

void EX1_ISR(void) interrupt 2 //外部中断1的中断服务函数
{
	pramater--;
	if(pramater < 0)
		pramater = 9999;
} 
