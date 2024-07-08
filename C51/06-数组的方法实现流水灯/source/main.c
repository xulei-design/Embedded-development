#include<reg51.h>
#include"delay.h"

unsigned char code LEDBUF[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
 //code:常量数组放在rom中，用code关键。


void main()
{
	unsigned char cnt;
	while(1)
	{
		for(cnt = 0;cnt<8;cnt++)
		{
			P1 = LEDBUF[cnt];
			delayxms(1000);
		}
		
	}
}