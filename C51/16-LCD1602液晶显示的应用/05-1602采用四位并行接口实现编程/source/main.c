#include <reg51.h>
#include "LCD1602.h"
#include"delay.h"
#include <stdio.h>


void main()
{
    unsigned char code str[] ="Hello LCD 1602";
     unsigned char code str1[] ="123456789ASFAG";
    LCDInit();
    delayxms(10);
    LCDShowStr(0,0,str);
    LCDShowStr(0,1,str1);
    while(1)
    {
       
    }
}


