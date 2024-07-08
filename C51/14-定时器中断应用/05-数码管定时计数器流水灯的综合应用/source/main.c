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


void Timer0Init(void)		//1����@12.000MHz
{
	
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
}


void  timer0_ISR(void) interrupt 1
{
	TR0 = 0;
	Display();
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;
	TR0 = 1;
}

void Timer1Init(void)		//50����@12.000MHz
{
	
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;
	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
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

	TL1 = 0xB0;		//���ö�ʱ��ֵ
	TH1 = 0x3C;
	TR1 = 1;
}