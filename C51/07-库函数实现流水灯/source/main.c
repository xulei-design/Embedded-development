#include<reg51.h>
#include"delay.h"
#include<intrins.h>



void main()
{
unsigned char temp = 0xfe;
	while(1)
	{
		P1 = temp;
		delayxms(500);
		temp = _crol_(temp,1);			
	}
}