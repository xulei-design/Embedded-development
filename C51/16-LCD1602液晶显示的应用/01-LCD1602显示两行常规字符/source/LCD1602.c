#include "LCD1602.h"


void LCDReadBF()  //æΪ���
{
    unsigned char state;
    unsigned char i;
    LCD1602_DB = 0xFF; //IO����1��������
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    
    do
    {
        LCD1602_EN = 1;
        state = LCD1602_DB; 
        LCD1602_EN = 0;
        i++;
        if(i>50)  //æ�ź�һֱΪ1���Զ��˳�
        {
            break;
        }
    }
    while(state & 0x80); //���λΪ1��æ���ȴ������λΪ0���˳�ѭ��
}

void LCDWriteCmd(unsigned char cmd)
{
    LCDReadBF(); //�ȴ�æ��⣬��æʱ����
    LCD1602_RS = 0; //д����
    LCD1602_RW = 0;
    LCD1602_DB = cmd;
    LCD1602_EN = 1;  //��æʱ��LCD1602_EN�Ѿ�Ϊ0
    //����Ҫ��ʱ�ˣ���Ϊ����һ��ָ���ʱ�����tpw
    LCD1602_EN = 0;
    
}
void LCDWriteData(unsigned char dat)
{
    LCDReadBF(); //�ȴ�æ��⣬��æʱ����
    LCD1602_RS = 1; //д����
    LCD1602_RW = 0;
    LCD1602_DB = dat;
    LCD1602_EN = 1;  //��æʱ��LCD1602_EN�Ѿ�Ϊ0
    //����Ҫ��ʱ�ˣ���Ϊ����һ��ָ���ʱ�����tpw
    LCD1602_EN = 0;
    
}

void LCDInit() //LCD��ʼ��
{
    LCDWriteCmd(LCD_MODE_PIN8); //��ʾ��ģʽ��������5*8�ĵ���
    LCDWriteCmd(LCD_DIS_ON);  //��ʾ��,����,��겻��˸
    LCDWriteCmd(LCD_CURSOR_RIGHT);  //�������,��ʾ���ƶ�
    LCDWriteCmd(LCD_SCREEN_CLR);  //����
}

void LCDShowStr(unsigned char x,unsigned char y,unsigned char *str)
{
    if(0==y)  //DDRAM��ַ����
    {
        LCDWriteCmd(0x80 | x);  //��ʾ�ڵ�һ��ĳ��λ��
    }
    else
    {
        LCDWriteCmd(0x80 | (0x40+x)); //��ʾ�ڵڶ���ĳ��λ��
    }
    while(*str != '\0')
    {
        LCDWriteData(*str++);
    }
}