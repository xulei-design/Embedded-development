#include <reg51.h>
#include"delay.h"
#include "LCD1602.h"

void main()
{
    unsigned char str[] = "hello LCD 1602";
    unsigned char str1[] = "13:14:520";
    LCDInit();
    while(1)
    {
        LCDShowStr(0,0,str);
        LCDShowStr(0,1,str1);
        
    }
}