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

void Timer0_Init(void)		//1����@11.0592MHz
{
	//AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
    TMOD |= 0x01;
	TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
    ET0 = 1;
    EA = 1;
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
    
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
    TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
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
