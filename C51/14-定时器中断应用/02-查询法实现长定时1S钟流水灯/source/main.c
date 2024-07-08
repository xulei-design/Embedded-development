#include<reg51.h>
#include<intrins.h>

unsigned char timerCnt;
unsigned char temp = 0x01;
void timer0_Iint();
void main()
{
    timer0_Iint();
	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;
			TH0 = (65536-20000)/256;
			TL0 = (65536-20000)%256;
			timerCnt++;
			if(timerCnt >=50)
				{
					timerCnt = 0;
					P1 = temp;
					temp = _crol_(temp,1);
				}
		}
	}
}

void timer0_Iint()
{
	TMOD = 0x01;
	TH0 = (65536-20000)/256;
	TL0 = (65536-20000)%256;
	TR0 = 1;
}