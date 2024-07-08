/*
功能:带有参数的延时函数实现小灯的闪烁
编程人：许磊
版本：v1.0
时间：2022/5/22
*/

//头文件的声明
#include<reg51.h>

sbit LED = P1^7;
void DelayXms(unsigned int xms);//函数声明

void main()
{
	while(1)
	{
		LED = 0;
		DelayXms(1000);//调用函数时，函数要么在前面声明过，要么包含在库中。
		LED = 1;
		DelayXms(1000);	
	}
}

/*
函数名：DelayXms
功能：延时函数
参数：unsigned int
返回值：无
*/

void DelayXms(unsigned int xms)	  //不是特别精确
{
	unsigned int i,j; //0-65535   0000h-
	for(i = xms;i>0;i--)
	{
		for(j=124;j>0;j--)
		{
		
		}
	}
}