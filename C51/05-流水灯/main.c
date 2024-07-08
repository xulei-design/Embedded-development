#include<reg51.h>



void delayxms(unsigned int xms);


void main()
{
P1 = 0xff;
	while(1)
	{
		P1 = 0xfe;	   //1111 1110
		delayxms(500);
		P1 = 0xfd;	   //1111 1101
		delayxms(500);
		P1 = 0xfb;	   //1111 1011
		delayxms(500); 
		P1 = 0xf7;	   //1111 0111
		delayxms(500); 

		P1 = 0xef;	   //1110 1111
		delayxms(500);
		P1 = 0xdf;	   //1101 1111
		delayxms(500);
		P1 = 0xbf;	   //1011 1111
		delayxms(500);
		P1 = 0x7f;	   //0111 1111
		delayxms(500);



	}		

}

void delayxms(unsigned int xms)
{
unsigned int i,j;
	for(i = xms;i>0;i--)
	{
		for(j = 124;j>0;j--)
		{}
	}
}