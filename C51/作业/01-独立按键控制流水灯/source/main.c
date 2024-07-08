#include<reg51.h>
#include"Key.h"
#include"Delay.h"
#include<intrins.h>





void Key_Service();
bit Startflag = 0;
bit UpDownflag = 0;
unsigned int temp = 0xfe;

void main()
{
	while(1)
	{
		Key_Service();	
	}
}

void Key_Service()
{
	switch(Key_Scan())
		{
			case 1: Startflag = 1; break; //Æô¶¯
			case 2: Startflag = 0; break; //Í£Ö¹
			case 3: UpDownflag = 1; break; //Down
			case 4: UpDownflag = 0; break; //UP
			default : break;
		}
	if(Startflag)
	{
		P1 = temp;
		if(UpDownflag)
		{
			temp = _crol_(temp,1);
		}
		else
		{
			temp = _cror_(temp,1);
		}
		Delayxms(500);	
	}
}