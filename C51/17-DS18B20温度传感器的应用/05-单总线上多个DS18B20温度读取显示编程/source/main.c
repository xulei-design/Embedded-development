#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "OneWire.h"
#include "DS18B20.h"
#include "LCDShowMenu.h"

void LCDShowService();
void Timer0_Init(void);
int TEMPbuf[] = {125,126,127,128};
unsigned char menu = 0;
unsigned char menuflag;

void main()
{
    LCDInit();
    delayxms(10);
    StartMenu();
    delayxms(2000);
    Timer0_Init();
    Start18B20();
    LCDWriteCmd(LCD_SCREEN_CLR);
    while(1)
    { 
        
        
        if(menuflag == 1)
        {
            menuflag = 0;
            menu++;
            if(menu == 2)
                menu = 0;
            Get18B20Temp(TEMPbuf,1);
            Get18B20Temp(TEMPbuf+1,2);
            Get18B20Temp(TEMPbuf+2,3);
            Get18B20Temp(TEMPbuf+3,4);
        }
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
	TR0 = 1;				//定时器0开始计时
    
}

void Timer0_ISR() interrupt 1
{
    static unsigned int timer0cnt = 0;
    TR0 = 0;
    timer0cnt++;
    if(timer0cnt >= 3000)
    {
        timer0cnt = 0;
        menuflag = 1;
    }
    TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
    TR0 = 1;
}
void LCDShowService()
{
    switch(menu)
    {
        case 0:  SubmenuOne(); break;
        case 1:  SubmenuTwo(); break;
        default: break;
        
    }
}
