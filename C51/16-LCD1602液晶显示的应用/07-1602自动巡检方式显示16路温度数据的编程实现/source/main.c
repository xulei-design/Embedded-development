#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "Key.h"
#include "LCDShowMenu.h"

void KeyService();
void LCDShowService();
void Timer0_Init(void);
int TEMPbuf[] = {125,126,127,128,223,224,225,226,334,335,336,337,421,422,423,424};
unsigned char menu = 0;
bit mode = 0; //用于切换模式，属于用户巡检模式，还是自动巡检模式
unsigned int timer0cnt = 0;
unsigned char menuflag;

void main()
{
    LCDInit();
    delayxms(10);
    StartMenu();
    delayxms(2000);
    Timer0_Init();
    LCDWriteCmd(LCD_SCREEN_CLR);
    while(1)
    { 
        if(mode == 0)
        {
            TR0 = 1;
            if(menuflag == 1)
            {
                menuflag = 0;
                menu++;
                if(menu == 4)
                    menu = 0;
            }
        }
        KeyService();
        LCDShowService();
    }
}

void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	//AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
    TMOD |= 0x01;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
    ET0 = 1;
    EA = 1;
	//TR0 = 1;				//定时器0开始计时
    
}

void Timer0_ISR() interrupt 1
{
    TR0 = 0;
    timer0cnt++;
    if(timer0cnt >= 5000)
    {
        timer0cnt = 0;
        menuflag = 1;
    }
    TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
    TR0 = 1;
}

void KeyService()
{
    switch(Key_Scan())
    {
        case 1: mode = ~mode;  break;
        case 2: if(mode == 1)
            {
                TR0 = 0;
                menu++; 
                if(menu == 4) 
                    menu = 0;
            }break;
        case 3: 
            mode = 1;
            TR0 = 0;
            menu = 0; 
         break;
        case 4: mode = 1; TR0 = 0; menu = 4; LCDWriteCmd(LCD_SCREEN_CLR); break;
        default: break;
    }
}

void LCDShowService()
{
    switch(menu)
    {
        case 0:  SubmenuOne(); break;
        case 1:  SubmenuTwo(); break;
        case 2:  SubmenuThree(); break;
        case 3:  SubmenuFour(); break;
        case 4:  AlarmSetMenu(); break;
        default: break;
        
    }
}
