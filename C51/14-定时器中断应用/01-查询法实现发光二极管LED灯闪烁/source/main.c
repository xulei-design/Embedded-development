#include<reg51.h>


void timer0_Iint();
sbit LED = P1^0;
void main()
{
	timer0_Iint();
	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;
			TH0 = (65536 - 50000)/256; //重新赋初值
			TL0 = (65536 - 50000)%256;
			LED = ~LED;
		}	
	}

}

void timer0_Iint() //定时器0的初始化
{
	//1.设置TMOD 确定工作方式 定时  工作方式1 GATE = 0
	TMOD = 0x01;
	//2.初值的计算 定时初值50ms  12M
	TH0 = (65536 - 50000)/256;
	TL0 = (65536 - 50000)%256;
	//3.打开定时器
	TR0 = 1;
}
