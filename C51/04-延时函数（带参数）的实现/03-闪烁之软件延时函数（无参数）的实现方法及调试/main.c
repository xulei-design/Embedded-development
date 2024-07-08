#include<reg51.h>
#include<intrins.h>//找到了_nop_的库函数文档。


void Delay5000ms();//函数的声明

void main()
{
	while(1)
	{
		P1 = 0xfe;
		Delay5000ms();//延时 亮一会
		P1 = 0xff;
		Delay5000ms();//延时 灭一会

	
	}
}

void Delay5000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	/*是一个函数，没有声明，是一个C51的一个库函数。需要找到这个库函数，
	从help文档中。如何查找：1.点击help，2.点击第一个，3.搜索此函数，找到所在库   */
	i = 38;
	j = 0;
	k = 118;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
