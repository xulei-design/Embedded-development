#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "OneWire.h"
#include "DS18B20.h"
#include "uart.h"

unsigned char romcode[8];  //romcode��ʵ�Σ����ص�romcode���β�
void LCDShowRomCode(unsigned char *romcode,unsigned char num);
unsigned char code rom1[] = {0x28,0xFF,0x50,0xB9, 0xC0,0x17,0x05,0x31}; //��һ��DS18B20rom��
unsigned char code rom2[] = {0x28,0xFe,0x50,0xB9, 0xC0,0x17,0x05,0x30};
unsigned char i;
void main()
{
    LCDInit(); //LCD1602��ʼ��
    UartInit();
    delayxms(10);
    ReadRomCode(romcode); //���ݵ��ǵ�ַ
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
    LCDSetPosition(7,0); //��һ����ʾ
    LCDWriteData('#');
    LCDWriteData(num+'0');
    
    LCDSetPosition(0,1); //�ڶ�����ʾ
    for(i=0; i < 8; i++)  //  8λCRCУ��λ00 B8C530(48λ��������) 28(8λ������)��������˳��2830C5B800
    {
        temp = romcode[i]>>4; //ȡ����λ��ʾ
        if(temp < 10)
            LCDWriteData(temp+'0');
        else
            LCDWriteData(temp+'7');  //���ݴ���10
        temp = romcode[i] & 0x0f; //ȡ����λ��ʾ
        if(temp < 10)
            LCDWriteData(temp+'0');
        else
            LCDWriteData(temp+'7');  //���ݴ���10
       
    }
    
}
