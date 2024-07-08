/*
功能：蜂鸣器的发声
*/
#include"delay.h"
#include<intrins.h>

void delayxms(unsigned int xms)
{
unsigned int i,j;
	for(i = xms;i>0;i--)
	{
		for(j = 124;j>0;j--)
		{}
	  }
}
void Delay956us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 179;
	do
	{
		while (--j);
	} while (--i);
}
void Delay1280us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 3;
	j = 71;
	do
	{
		while (--j);
	} while (--i);
}
