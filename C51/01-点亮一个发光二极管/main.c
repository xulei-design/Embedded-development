//单片机的头文件，实际上是建立软件与硬件的联系。
#include<reg51.h>

sbit LED = P1^0;

void main()
{
	while(1)
	{
		LED = 0;
		//P1 = 0XFE; //P1.7-P1.0 1111 1110	
	}


}