#include<reg51.h>
#include"delay.h"
#include"display.h"
#include"Key.h"

unsigned char wnd;
unsigned char parm1 = 56;
unsigned char parm2 = 96;
unsigned char parm3 = 4;
unsigned char parm4 = 93;

void dis_Service();
void Key_Service();
												
void main()
{
	unsigned int i;
	for(i=0;i<5000;i++)
	{
		Display();
	}
	while(1)
	{
		Key_Service();
		dis_Service();		
		Display();	
	}
	
}

void dis_Service()
{	
switch(wnd)
{
	case 0: 
		LEDBuf[0]=20;
		LEDBuf[1]=1;
		LEDBuf[2]=parm1/10;
		LEDBuf[3]=parm1%10;
		break;
	case 1:
		LEDBuf[0]=20;
		LEDBuf[1]=2;
		LEDBuf[2]=parm2/10;
		LEDBuf[3]=parm2%10;
		break;
	case 2:
		LEDBuf[0]=20;
		LEDBuf[1]=3;
		LEDBuf[2]=parm3/10;
		LEDBuf[3]=parm3%10;
		break;
	case 3:
		LEDBuf[0]=20;
		LEDBuf[1]=4;
		LEDBuf[2]=parm4/10;
		LEDBuf[3]=parm4%10;
		break;
		}
}
void Key_Service()
{
	switch(Key_Scan())
	{
		case 1: 
			wnd++;if(wnd>3) wnd = 0;
		break;
		case 2:
			switch(wnd)
			{
				case 0: parm1++; if(parm1>99) parm1 = 0; break;
				case 1: parm2++; if(parm2>99) parm2 = 0; break;
				case 2: parm3++; if(parm3>99) parm3 = 0; break;
				case 3: parm4++; if(parm4>99) parm4 = 0; break;
				default:break;
			}
		break;
		case 3: 
			switch(wnd)
			{
				case 0: parm1--; if(parm1>100) parm1 = 99; break;
				case 1: parm2--; if(parm2>100) parm2 = 99; break;
				case 2: parm3--; if(parm3>100) parm3 = 99; break;
				case 3: parm4--; if(parm4>100) parm4 = 99; break;
				default:break;
			}
		break;
		case 4:
			switch(wnd)
			{
				case 0: parm1=0; break;
				case 1: parm2=0; break;
				case 2: parm3=0; break;
				case 3: parm4=0; break;
				default:break;
			}
		break;
		default : break;
	}	
}	