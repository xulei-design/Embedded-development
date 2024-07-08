#include<reg51.h>
#include"display.h"


unsigned char timerCnt;
unsigned char sec = 10;
unsigned char min = 59;
unsigned char hour;
unsigned char state=0;
void Timer0Init(void);
void Timer1Init(void);
void EX0_Iint();
void EX1_Iint();
void DIS_ISR();
void DIS_Sec();
void DIS_Min();
void DIS_Hour();
void main()
{
	Timer0Init();
	Timer1Init();
	EX0_Iint();
	EX1_Iint();
	EA = 1;
	while(1)
	{
		switch(state)
		{
			case 0: TR0 = 1; DIS_ISR(); break; //����ʱ��״̬
			case 1: DIS_Sec(); break; //����
			case 2: DIS_Min(); break; //����
			case 3: DIS_Hour();break; //��ʱ
			default : break;
		}
	}
}

void DIS_ISR()
{
	LEDBuf[0] = hour/10;
	LEDBuf[1] = hour%10;
	LEDBuf[2] = min/10;
	LEDBuf[3] = min%10;
}
void DIS_Min()
{
	LEDBuf[0] = min/10;
	LEDBuf[1] = min%10;
	LEDBuf[2] = 23;
	LEDBuf[3] = 23;
}
void DIS_Sec()
{
	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = sec/10;
	LEDBuf[3] = sec%10;
}

void DIS_Hour()
{
	LEDBuf[0] = hour/10;
	LEDBuf[1] = hour%10;
	LEDBuf[2] = 22;
    LEDBuf[3] = 22;
}

void Timer0Init(void)		//50����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;
	TL0 = 0xB0;		//���ö�ʱ��ֵ
	TH0 = 0x3C;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־			
	ET0 = 1;

}
void Timer1Init(void)		//1����@12.000MHz
{
    TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1 = 1;

}

void EX0_Iint()	 //�ⲿ�ж�0
{
	IT0 = 1;
	EX0 = 1;
}
void EX1_Iint()  //�ⲿ�ж�1
{
	IT1 = 1;
	EX1 = 1;
}
void EX0_ISR(void) interrupt 0	 // �ⲿ�ж�0����״̬
{
	TR0 = 0; //һ���л�״̬����е���ʱ��ʱ���ͽ�����ʱ�ӹص�
	state++;
	if(state>3)
		state = 0;		
}

void timer0_ISR(void) interrupt 1
{
	TR0 = 0;
	timerCnt++;
	if(timerCnt>=20) //1s�ӵ�
	{
		timerCnt=0;
		sec++;
		if(sec>=60)
		{
			sec = 0;
			min++;
			if(min>=60)
			{
				min=0;
				hour++;
				if(hour >= 24)
				{
					hour = 0;
				}
			}
		}
	}
	TL0 = 0xB0;		//���ö�ʱ��ֵ
	TH0 = 0x3C;
	TR0 = 1;
}
void EX1_ISR(void) interrupt 2	 // �ⲿ�ж�1����״̬
{
	switch(state)
	{
		case 0: break;
		case 1: 
			sec++; 
			if(sec>=60) 
				sec=0;
		break;
		case 2:
			
			min++; 
			if(min>=60) 
				min=0;
		break;
		case 3:
			hour++;
			if(hour>=24)
				hour = 0;
		break;
		default : break;
	}	
}
void timer1_ISR(void) interrupt 3  //��ʱ��1��ʾˢ��
{
	TR1 = 0;
	Display();
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;
	TR1 = 1;	
}
   
