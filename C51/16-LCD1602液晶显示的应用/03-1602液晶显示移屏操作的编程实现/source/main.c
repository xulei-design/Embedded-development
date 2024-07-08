#include <reg51.h>
#include "LCD1602.h"
#include"delay.h"
#include <string.h>


void main()
{
    unsigned char i;
    unsigned char str[] = "hell0 LCD1602";
    unsigned char str1[] = "welcome to study LCD1602";
    LCDInit();
    delayxms(10);
    //LCDWriteCmd(LCD_DIS_MODE_LEFT); //初始设置的是字符的输入模式 整屏左移
    LCDWriteCmd(0x80);
        for(i=0;i<strlen(str);i++)
        {
            LCDWriteData(str[i]);
            //delayxms(200);
        }

        LCDWriteCmd(0xC0);
        for(i=0;i<strlen(str1);i++)
        {
            LCDWriteData(str1[i]); //显示
            //delayxms(2000);
        }
    
    while(1)
    {
        LCDWriteCmd(0x18);
        delayxms(1000);
        
    }
}