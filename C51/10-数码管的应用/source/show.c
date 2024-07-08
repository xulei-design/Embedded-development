#include"show.h"	  //数码管的显示程序


unsigned char code leddata[]={ 
//共阴极数码管的段码表
				0x3f, //0
				0x06, //1
				0x5b, //2
				0x4f, //3
				0x66, //4
				0x6d, //5
				0x7d, //6
				0x07, //7
				0x7f, //8
				0x6f, //9
				0xff, //a
				0x7c, //b
				0x39, //c
				0x5e, //d
				0x79, //e
				0x71, //f
				0x76, //h
				0x38, //l
				0x37, //n
				0x3e, //u
				0x73, //p
				0x5c, //0
				0x00,  //熄灭
				0x40  //--
				 
				 			
				/**0xc0,//0
				0xf9,//1
				0xa4,//2
				0xb0,//3
				0x99,//4
				0x92,//5
				0x82,//6
				0xf8,//7
				0x80,//8
				0x90,//9
				0x88,//A
				0x83,//B
				0xc6,//C
				0xa1,//D
				0x86,//E
				0x8e, //F
				0x8c, //P
				0xc1,//U
				0x91,//Y
				0x7c,//L
				0x00,//全亮
				0xff  //熄灭**/
};

unsigned char LEDBuf[] = {23,23,23,23}; //数据显示缓冲区
unsigned char code PLACE_CODE[] = {0xf7,0xfb,0xfd, 0xfe}; //位选信号，是常量，放置到ROM中

void Show()
{
	unsigned char i;
	switch(i)
	{
		case 0:
			GPIO_DIG = leddata[leddata[0]];
			GPIO_PLACE = PLACE_CODE[0];
			Delayxms(1);
			GPIO_DIG = 0x00; 

		case 1:
		case 2:
		case 3:
		default:break;
	}
}
