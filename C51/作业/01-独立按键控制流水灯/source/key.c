#include"Key.h"



unsigned char Key_Scan()
{
	unsigned char KeyNum = 0;
	KEY1 = 1; KEY2 = 1;	KEY3 = 1; KEY4 = 1;
//	if(0 == KEY1)  //1.判断按键是否按下
//	{
//		Delayxms(10);//2.延时消抖，时间一般为5-10ms
//		if(KEY1 == 0) //3.再次判断按键是否按下
//		{
//			KeyNum = 1;	//4.键值的软件编码，赋一个键值，不直接做按键功能，便于模块化					
//		} while(KEY1 == 0);//5.松手等待
//	}
//	if(KEY2 == 0) //初步判断按键是否按下
//	{
//		Delayxms(10);//闭合抖动阶段，消抖
//		if(KEY2 == 0) //再次判断按键是否按下，有效闭合阶段，执行按键的功能。
//		{
//			KeyNum = 2; //赋键值编码
//		} 
//		while(KEY2 == 0);//确保按键还是在有效闭合阶段。		
//	}
//	if(KEY3 == 0) //初步判断按键是否按下
//	{
//		Delayxms(10);//闭合抖动阶段，消抖
//		if(KEY3 == 0) //再次判断按键是否按下，有效闭合阶段，执行按键的功能。
//		{
//			KeyNum = 3; //赋键值编码
//		} 
//		while(KEY3 == 0);//确保按键还是在有效闭合阶段。		
//	}
//	if(KEY4 == 0) //初步判断按键是否按下
//	{
//		Delayxms(10);//闭合抖动阶段，消抖
//		if(KEY4 == 0) //再次判断按键是否按下，有效闭合阶段，执行按键的功能。
//		{
//			KeyNum = 4; //赋键值编码
//		} 
//		while(KEY4 == 0);//确保按键还是在有效闭合阶段。		
//	}
	if(!KEY1||!KEY2||!KEY3||!KEY4)
	{
		Delayxms(10);
		if(!KEY1||!KEY2||!KEY3||!KEY4)
		{
			if(!KEY1)
				KeyNum = 1;
			if(!KEY2)
				KeyNum = 2;
			if(!KEY3)
				KeyNum = 3;
			if(!KEY4)
				KeyNum = 4;
		}
		while(!KEY1||!KEY2||!KEY3||!KEY4);
	}
	return KeyNum;
}
