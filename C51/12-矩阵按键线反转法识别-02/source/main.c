#include<reg51.h>
#include"display.h"
#include"Key.h"



void main()
{	LEDBuf[0] = 23;
	LEDBuf[1] = 23;
	LEDBuf[2] = 23;
	while(1)
	{
		LEDBuf[3] = Key_Scan();
		Display();
	}
}