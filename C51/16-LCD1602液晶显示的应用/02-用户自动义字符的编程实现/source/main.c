#include <reg51.h>
#include"delay.h"
#include "LCD1602.h"

void main()
{
    
    unsigned char str1[] = "13:14";
    unsigned char code str2[] = {0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00};
    LCDInit();
    while(1)
    {
        LCDSetChar(9,0,2,str2);
        LCDShowStr(0,1,str1);
        
    }
}