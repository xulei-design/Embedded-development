#include<reg51.h>	  //硬件P2低四位与门接在一起，联通P3.2
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

void EX0_Init(void) //外部中断0初始化 
{
	IT0 = 1; //下降沿触发 
	EX0 = 1;
	EA = 1;//中断的总开关
}

void EX0_ISR(void) interrupt 0 //外部中断1的中断服务函数
{
	KeyPressFlag = 1;	
}
