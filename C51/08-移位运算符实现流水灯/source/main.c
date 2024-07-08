#include<reg51.h>
#include"delay.h"


void main()
{

	while(1)
	{
	
	unsigned char temp = 0x1;
	unsigned char i = 0;
		for(i;i<8;i++)
		{
			P1 = ~(temp << i);	 //È¡·´
			delayxms(500);
			//temp = temp << 1;
		 }
	}
}