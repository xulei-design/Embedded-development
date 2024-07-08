#include <reg51.h>
#include "LCD1602.h"
#include"delay.h"
#include <stdio.h>

unsigned char IntegerToStr(long dat,unsigned char *str);
void main()
{
    // long dat = -56678;  //长整型的最大范围4294967295
    int dat = -1235;
    unsigned char str[6]; //最大的ASCII码“4294967295\0”
    
    float num = 1.25;
    float num2 = 1.3564;
    int temp; 
    unsigned char lcdbuf[10];
    
    LCDInit();
    delayxms(10); 
    IntegerToStr(dat,str); //数字转字符串，就是将数字转换为ASCII码值
    LCDShowStr(0,0,str);
    
    temp = num*100;
    LCDSetPosition(0,1); //显示位置
    LCDWriteData(temp/100+'0'); //显示数据
    LCDWriteData('.');
    LCDWriteData(temp/10%10+'0');
    LCDWriteData(temp%10+'0');
    
    sprintf(lcdbuf,"%0.4f",num2);
    LCDShowStr(6,1,lcdbuf);
    
    while(1)
    {
       
    }
}


unsigned char IntegerToStr(int dat,unsigned char *str) 
//带有返回值的函数，返回值为字符串的长度,将数字转换为字符串的函数
{
    unsigned char i;
    unsigned char len;
    unsigned char buf[6];
    if(dat < 0)
    {
        dat = -dat; //如果是负数，取绝对值。
        *str++ = '-';
        len++;
    }
    do  //分离数据
    {
        buf[i++] = dat%10 + '0'; //dat%10 + 0x30  buf[0] = '8' buf[1] = '7' buf[2] = '6'
        dat /= 10;
    }
    while(dat > 0);
    len += i;
    while(i-- > 0) //反数据
    {
        *str++ = buf[i];
    }
    *str = '\0';  //字符串加一个结束符
    return len;
}

