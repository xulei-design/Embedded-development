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
			case 0: TR0 = 1; DIS_ISR(); break; //正常时钟状态
			case 1: DIS_Sec(); break; //调秒
			case 2: DIS_Min(); break; //调分
			case 3: DIS_Hour();break; //调时
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

void Timer0Init(void)		//50毫秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;
	TL0 = 0xB0;		//设置定时初值
	TH0 = 0x3C;		//设置定时初值
	TF0 = 0;		//清除TF0标志			
	ET0 = 1;

}
void Timer1Init(void)		//1毫秒@12.000MHz
{
    TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x01;
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	ET1 = 1;

}

void EX0_Iint()	 //外部中断0
{
	IT0 = 1;
	EX0 = 1;
}
void EX1_Iint()  //外部中断1
{
	IT1 = 1;
	EX1 = 1;
}
void EX0_ISR(void) interrupt 0	 // 外部中断0调节状态
{
	TR0 = 0; //一旦切换状态想进行调节时间时，就将计数时钟关掉
	state++;
	if(state>3)
		state = 0;		
}

void timer0_ISR(void) interrupt 1
{
	TR0 = 0;
	timerCnt++;
	if(timerCnt>=20) //1s钟到
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
	TL0 = 0xB0;		//设置定时初值
	TH0 = 0x3C;
	TR0 = 1;
}
void EX1_ISR(void) interrupt 2	 // 外部中断1调节状态
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
void timer1_ISR(void) interrupt 3  //定时器1显示刷新
{
	TR1 = 0;
	Display();
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;
	TR1 = 1;	
}
   
