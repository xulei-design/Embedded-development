#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "OneWire.h"
#include "DS18B20.h"
#include "uart.h"

unsigned char romcode[8];  //romcode是实参，返回的romcode是形参
void LCDShowRomCode(unsigned char *romcode,unsigned char num);
unsigned char code rom1[] = {0x28,0xFF,0x50,0xB9, 0xC0,0x17,0x05,0x31}; //第一个DS18B20rom码
unsigned char code rom2[] = {0x28,0xFe,0x50,0xB9, 0xC0,0x17,0x05,0x30};
unsigned char i;
void main()
{
    LCDInit(); //LCD1602初始化
    UartInit();
    delayxms(10);
    ReadRomCode(romcode); //传递的是地址
    LCDShowRomCode(romcode,1);
    for(i=0; i < 8; i++) 
    {
        sendByte(romcode[i]);
    }
    while(1);
           
}

void LCDShowRomCode(unsigned char *romcode,unsigned char num)
{
    unsigned char i;
    unsigned char temp;
    LCDSetPosition(7,0); //第一行显示
    LCDWriteData('#');
    LCDWriteData(num+'0');
    
    LCDSetPosition(0,1); //第二行显示
    for(i=0; i < 8; i++)  //  8位CRC校验位00 B8C530(48位串行数据) 28(8位家族码)，读到的顺序2830C5B800
    {
        temp = romcode[i]>>4; //取高四位显示
        if(temp < 10)
            LCDWriteData(temp+'0');
        else
            LCDWriteData(temp+'7');  //数据大于10
        temp = romcode[i] & 0x0f; //取低四位显示
        if(temp < 10)
            LCDWriteData(temp+'0');
        else
            LCDWriteData(temp+'7');  //数据大于10
       
    }
    
}
