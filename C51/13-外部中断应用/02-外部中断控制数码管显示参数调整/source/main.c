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
	EA = 1;//�жϵ��ܿ���
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

void EX0_Init(void) //�ⲿ�ж�0��ʼ�� 
{
	IT0 = 1; //�½��ش��� 
	EX0 = 1;
}
void EX1_Init(void) 
{
	IT1 = 1;
	EX1 = 1;
}


void EX0_ISR(void) interrupt 0 //�ⲿ�ж�1���жϷ�����
{
	pramater++;
	if(pramater > 9999)
		pramater = 0;
}

void EX1_ISR(void) interrupt 2 //�ⲿ�ж�1���жϷ�����
{
	pramater--;
	if(pramater < 0)
		pramater = 9999;
} 
