#include<reg51.h>
#include"display.h"	

unsigned char DIS_u();
void DIS_Service();
void Timer0Init(void);
void EX0_Init();
void EX1_Init();
unsigned int numCnt = 0;//����
unsigned char temp0;
unsigned char temp1;
unsigned char temp2;
unsigned char temp3;
void main()
{
	Timer0Init();
	EX0_Init();
	EX1_Init();
	EA = 1;	 //�ж��ܿ���
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
void Timer0Init(void)		//1����@11.0592MHz
{

	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;

}

void EX0_Init()
{
	IT0 = 1;  //������ʽ���½���
	EX0 = 1;  //���ⲿ�ж�
	
}

void EX1_Init()
{
	IT1 = 1;  //������ʽ���½���
	EX1 = 1;  //���ⲿ�ж�
	
}
void timer0_ISR(void) interrupt 1	//��ʱ��T0�жϷ�����
{
	TR0 = 0;
	Display();
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;
	TR0 = 1;
}

void EX0_ISR(void) interrupt 0	   //�ⲿ�жϵ�0�ķ�����
{
	EX0 = 0;
	numCnt++;
	if(numCnt>9999)
		numCnt = 0;
	EX0 = 1;	
}
void EX1_ISR(void) interrupt 2	   //�ⲿ�жϵ�1�ķ�����
{
	EX1 = 0;
	numCnt--;
	if(numCnt > 10000)
		numCnt = 9999;
	EX1 = 1;		
	
}