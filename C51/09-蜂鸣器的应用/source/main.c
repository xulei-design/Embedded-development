#include<reg51.h>
#include"delay.h"

void Delay956us();
sbit sound = P3^7;


void main()
{
unsigned int i;
	while(1)
	{
		for(i;i<200;i++)
		{
			sound = ~sound;
			Delay956us();
		}
		for(i;i<500;i++)
		{
			sound = ~sound;
			Delay1280us();
		}
	}
}