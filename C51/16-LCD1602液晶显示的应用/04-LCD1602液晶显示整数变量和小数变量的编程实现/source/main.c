#include <reg51.h>
#include "LCD1602.h"
#include"delay.h"
#include <stdio.h>

unsigned char IntegerToStr(long dat,unsigned char *str);
void main()
{
    // long dat = -56678;  //�����͵����Χ4294967295
    int dat = -1235;
    unsigned char str[6]; //����ASCII�롰4294967295\0��
    
    float num = 1.25;
    float num2 = 1.3564;
    int temp; 
    unsigned char lcdbuf[10];
    
    LCDInit();
    delayxms(10); 
    IntegerToStr(dat,str); //����ת�ַ��������ǽ�����ת��ΪASCII��ֵ
    LCDShowStr(0,0,str);
    
    temp = num*100;
    LCDSetPosition(0,1); //��ʾλ��
    LCDWriteData(temp/100+'0'); //��ʾ����
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
//���з���ֵ�ĺ���������ֵΪ�ַ����ĳ���,������ת��Ϊ�ַ����ĺ���
{
    unsigned char i;
    unsigned char len;
    unsigned char buf[6];
    if(dat < 0)
    {
        dat = -dat; //����Ǹ�����ȡ����ֵ��
        *str++ = '-';
        len++;
    }
    do  //��������
    {
        buf[i++] = dat%10 + '0'; //dat%10 + 0x30  buf[0] = '8' buf[1] = '7' buf[2] = '6'
        dat /= 10;
    }
    while(dat > 0);
    len += i;
    while(i-- > 0) //������
    {
        *str++ = buf[i];
    }
    *str = '\0';  //�ַ�����һ��������
    return len;
}

