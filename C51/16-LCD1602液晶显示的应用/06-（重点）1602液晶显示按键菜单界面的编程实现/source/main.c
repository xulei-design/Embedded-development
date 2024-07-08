#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "Key.h"
#include "LCDShowMenu.h"

void KeyService();
void LCDShowService();

unsigned char menu = 0;
void main()
{
    LCDInit();
    delayxms(10);
    StartMenu();
    delayxms(2000);
    LCDWriteCmd(LCD_SCREEN_CLR);
    while(1)
    { 
        KeyService();
        LCDShowService();
    }
}
void KeyService()
{
    switch(Key_Scan())
    {
        case 1: menu++; if(menu == 4) menu = 0; break;
        case 2: menu--; if(menu > 4) menu = 0;break;
        case 3: menu = 0; break;
        case 4: menu = 4; LCDWriteCmd(LCD_SCREEN_CLR); break;
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
