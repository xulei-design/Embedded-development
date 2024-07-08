#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "OneWire.h"


void main()
{
    unsigned char ack;
    LCDInit();
    delayxms(10);
    ack = OneWireRst();
    LCDWriteCmd(LCD_SCREEN_CLR);
    while(1)
    {
        LCDSetPosition(0,0);
        LCDWriteData(ack + '0');
    }
}

