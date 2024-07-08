#include"Key.h"



unsigned char Key_Scan()
{
	unsigned char temp1,temp2;
	unsigned char KeyNum = 22;
	KEYPORT = 0xf0; //四行全部输出低电平，四列做为输入，输出写“0”，输入写“1”，检测四列
	temp1 = KEYPORT; //读入I/O口，
	if(temp1!=0xf0)	 //判断是否有键按下。
	{
		Delayxms(10); //消抖
		if(temp1!=0xf0) //再次判断按键是否按下。
		{
			temp1 = KEYPORT & 0xf0; //取高四位确定列号
			KEYPORT = 0x0f; //4行做输入，四列作为输出，输出写“0”，输入写“1”，检测四行。	
			temp2 = KEYPORT&0x0f;//读入并取低四位确定行号
		}
	}
	switch(temp1 + temp2)
	{
		case 0xee: KeyNum = 1; break;
		case 0xed: KeyNum = 2; break;
		case 0xeb: KeyNum = 3; break;
		case 0xe7: KeyNum = 4; break;
		case 0xde: KeyNum = 5; break;
		case 0xdd: KeyNum = 6; break;
		case 0xdb: KeyNum = 7; break;
		case 0xd7: KeyNum = 8; break;
		case 0xbe: KeyNum = 9; break;
		case 0xbd: KeyNum = 10; break;
		case 0xbb: KeyNum = 11; break;
		case 0xb7: KeyNum = 12; break;
		case 0x7e: KeyNum = 13; break;
		case 0x7d: KeyNum = 14; break;
		case 0x7b: KeyNum = 15; break;
		case 0x77: KeyNum = 16; break;
	}

	return KeyNum;
}

