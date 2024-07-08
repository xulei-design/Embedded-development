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
		if(systemTimer%50==0) //����ָʾ
		LED = ~LED;	
	}while(systemTimer<5000); // 5S 5000ms/1ms
	systemFlag = 0;
	LED = 1;
	while(1)		 //while(1) �붨ʱ������
	{
		Dis_Service();
	}
}


void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		
	TMOD |= 0x01;   //���ö�ʱ��ģʽ
    TL0 = 0x0C;		//���ö�ʱ��ֵ
	TH0 = 0xFE;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	EA = 1;
	ET0 = 1;
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
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
    TL0 = 0x0C;		//���ö�ʱ��ֵ
	TH0 = 0xFE;		//���ö�ʱ��ֵ
	TR0 = 1;
}
