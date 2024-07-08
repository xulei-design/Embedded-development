#include<reg51.h>


sbit LED = P1^0;
unsigned char timer0_Cnt;
void Timer0Init(void);
void main()
{
	Timer0Init();
	while(1);
}

void Timer0Init(void)		//50����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ GATE C/T M0 M1
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xB0;		//���ö�ʱ��ֵ (65535-50000)%256
	TH0 = 0x3C;		//���ö�ʱ��ֵ (65535-50000)/256
	TF0 = 0;		//���TF0��־
	ET0 = 1;
	EA = 1;  //���ж�
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
}

void timer0_ISR() interrupt 1
{
	TL0 = 0xB0;		//���ö�ʱ��ֵ (65535-50000)%256
	TH0 = 0x3C;
	timer0_Cnt++;
	if(timer0_Cnt>=10)
	{
		LED = ~LED;	
}	}

