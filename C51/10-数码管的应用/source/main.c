#include<reg51.h>
#include"delay.h"
#include"display.h"

unsigned char wnd;
unsigned char parm1 = 56;
unsigned char parm2 = 96;
unsigned char parm3 = 46;
unsigned char parm4 = 93;


												
void main()
{
	unsigned int i;
	for(i=0;i<5000;i++)
	{
		Display();
	}
	while(1)
	{
		switch(wnd)
		{
			case 0: 
				LEDBuf[0]=0;
				LEDBuf[1]=23;
				LEDBuf[2]=parm1/10;
				LEDBuf[3]=parm1%10;
				for(i=0;i<5000;i++)
				{
					Display();
				}
				wnd++;
				break;
			case 1:
				LEDBuf[0]=1;
				LEDBuf[1]=23;
				LEDBuf[2]=parm2/10;
				LEDBuf[3]=parm2%10;
				wnd++;
				for(i=0;i<5000;i++)
				{
					Display();
				}
				break;
			case 2:
				LEDBuf[0]=2;
				LEDBuf[1]=23;
				LEDBuf[2]=parm3/10;
				LEDBuf[3]=parm3%10;
				wnd++;
				for(i=0;i<5000;i++)
				{
					Display();
				}
				break;
			case 3:
				LEDBuf[0]=3;
				LEDBuf[1]=23;
				LEDBuf[2]=parm4/10;
				LEDBuf[3]=parm4%10;
				for(i=0;i<5000;i++)
				{
					Display();
				}
				wnd = 0;
				break;
				}	
	}
	
}	