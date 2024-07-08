#include<reg51.h>
#include"display.h"
#include"Key.h"

void main()
{
	while(1)
	{	LEDBuf[0]=22;
		LEDBuf[1]=22;
		LEDBuf[1]=22;
		switch(Key_Scan())
		{
			case 1: LEDBuf[3]=1; break;
			case 2: LEDBuf[3]=2; break;
			case 3: LEDBuf[3]=3; break;
			case 4: LEDBuf[3]=4; break;
			case 5: LEDBuf[3]=5; break;
			case 6: LEDBuf[3]=6; break;
			case 7: LEDBuf[3]=7; break;
			case 8: LEDBuf[3]=8; break;
			case 9: LEDBuf[3]=9; break;
			case 10: LEDBuf[2]=1; LEDBuf[3]=0; break;
			case 11: LEDBuf[2]=1; LEDBuf[3]=1; break;
			case 12: LEDBuf[2]=1; LEDBuf[3]=2; break;
			case 13: LEDBuf[2]=1; LEDBuf[3]=3; break;
			case 14: LEDBuf[2]=1; LEDBuf[3]=4; break;
			case 15: LEDBuf[2]=1; LEDBuf[3]=5; break;
			case 16: LEDBuf[2]=1; LEDBuf[3]=6; break;
			default: break;
		}
		Display();
	}
}