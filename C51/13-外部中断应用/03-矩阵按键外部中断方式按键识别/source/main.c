#include<reg51.h>	  //Ӳ��P2����λ���Ž���һ����ͨP3.2
#include"display.h"
#include"Delay.h"
#include"Key.h"


unsigned char KeyNum=22;
unsigned char KeyPressFlag;
void EX0_Init(void);
void Dis_Service();
unsigned int pramater = 0;
void main()
{
	EX0_Init();
	P2 = 0x0f;
	while(1)
	{
		if(KeyPressFlag == 1)
		{
			KeyPressFlag = 0;
			KeyNum = Key_Scan();
		}
		Dis_Service();
		Display();	
	}
}

void Dis_Service()
{
	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = 23;
	LEDBuf[3] = KeyNum;
}

void EX0_Init(void) //�ⲿ�ж�0��ʼ�� 
{
	IT0 = 1; //�½��ش��� 
	EX0 = 1;
	EA = 1;//�жϵ��ܿ���
}

void EX0_ISR(void) interrupt 0 //�ⲿ�ж�1���жϷ�����
{
	KeyPressFlag = 1;	
}
