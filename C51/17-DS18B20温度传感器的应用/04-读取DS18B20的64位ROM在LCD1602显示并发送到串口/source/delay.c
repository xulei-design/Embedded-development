#include "delay.h"
#include <intrins.h>
void delayxms(unsigned int xms)
{
unsigned int i,j;
	for(i = xms;i>0;i--)
	{
		for(j = 124;j>0;j--)
		{}
	}
}

void Delay600us()		//@12.000MHz—” ±600us
{
	unsigned char i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}
void Delay60us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 27;
	while (--i);
}
