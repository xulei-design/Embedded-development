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
bit mode = 0; //�����л�ģʽ�������û�Ѳ��ģʽ�������Զ�Ѳ��ģʽ
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
	//TR0 = 1;				//��ʱ��0��ʼ��ʱ
    
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
    TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
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
