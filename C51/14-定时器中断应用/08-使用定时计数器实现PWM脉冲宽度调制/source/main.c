#include<reg51.h>



sbit PWM = P1^0;
unsigned char PWM_DUTY;
unsigned char PWM_Cnt;
void Timer0Init(void);
void EX0_Iint();
void main()
{
	Timer0Init();
	EX0_Iint();
	EA = 1;
	while(1)
	{

	}

}

void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;
	TL0 = 0x9C;		//���ö�ʱ��ֵ
	TH0 = 0xFF;			//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
	
}

void timer0_Service(void) interrupt 1
{
	TR0 = 0;
	if(PWM_Cnt>=100)
	{
		PWM_Cnt=0;		
	}
	if(PWM_Cnt<=PWM_DUTY)
	{
		PWM = 1;
	}
	else
		PWM = 0;
    TL0 = 0x9C;		//���ö�ʱ��ֵ
	TH0 = 0xFF;		
	TR0 = 1;

}

void EX0_Iint()
{
	IT0 = 1;
	IE0 = 0;
	EX0 = 1;
}
void EX0_Service(void) interrupt 0
{
	static unsigned char  PWM_KEY;
	PWM_KEY++;
	if(PWM_KEY>4)
		PWM_KEY = 0;
	switch(PWM_KEY)
	{
		case 0: PWM_DUTY = 0;  break;
		case 1: PWM_DUTY = 25; break;
		case 2: PWM_DUTY = 50; break;
		case 3: PWM_DUTY = 75; break;
		case 4: PWM_DUTY = 100; break;
		default:break;
	}
}
