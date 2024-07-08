#include<reg51.h>

void main()
{
//while(1)外面：定义变量，初始化特殊寄存器
	unsigned int i;
	while(1)
	{
		i =20000;
		P1 = 0x7e; //1111 1110 
		//亮一会  延时
		while(i--);
		i = 20000;		
		P1 = 0xff; //1111 1111
		//灭一会  延时
		while(i--);
		
		
	}
}