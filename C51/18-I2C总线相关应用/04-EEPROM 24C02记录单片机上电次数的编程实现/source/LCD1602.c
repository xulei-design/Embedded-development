#include "LCD1602.h"

#ifndef LCD_1602_4PINS
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
#else
void LCDReadBF()  //æΪ���
{
    unsigned char state;
    unsigned char i;
    LCD1602_DB |= 0xF0; //����λIO����1������λ���ֲ��䣬������
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    
    do
    {
        LCD1602_EN = 1;
        state = LCD1602_DB & 0xF0; //�ȶ�����λ
        LCD1602_EN = 0;
        
        LCD1602_EN = 1;
        state |= (LCD1602_DB&0xF0)>>4 ; //������λ
        LCD1602_EN = 0;
        i++;
        if(i>50)  //æ�ź�һֱΪ1���Զ��˳�
        {
            break;
        }
    }
    while(state & 0x80); //���λΪ1��æ���ȴ������λΪ0���˳�ѭ��
}
#endif

#ifndef LCD_1602_4PINS
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
#else
void LCDWriteCmd(unsigned char cmd)
{
    LCD1602_RS = 0; //д����
    LCD1602_RW = 0;
    LCD1602_DB = cmd; //д����λ
    LCD1602_EN = 1;  //��æʱ��LCD1602_EN�Ѿ�Ϊ0
    delayxms(1);//����Ҫ��ʱ�ˣ���Ϊ����һ��ָ���ʱ�����tpw
    LCD1602_EN = 0;
    
    LCD1602_DB = cmd << 4; //д����λ
    LCD1602_EN = 1;  
    delayxms(1);
    LCD1602_EN = 0;
    
}
#endif
#ifndef LCD_1602_4PINS
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
#else
void LCDWriteData(unsigned char dat)
{
    LCDReadBF(); //�ȴ�æ��⣬��æʱ����
    LCDReadBF(); //�ȴ�æ��⣬��æʱ����
    LCD1602_RS = 1; //д����
    LCD1602_RW = 0;
    LCD1602_DB = dat;
    LCD1602_EN = 1;  //��æʱ��LCD1602_EN�Ѿ�Ϊ0
    delayxms(1);//����Ҫ��ʱ�ˣ���Ϊ����һ��ָ���ʱ�����tpw
    LCD1602_EN = 0;
    
    LCD1602_DB = dat << 4;
    LCD1602_EN = 1;  //��æʱ��LCD1602_EN�Ѿ�Ϊ0
    delayxms(1);//����Ҫ��ʱ�ˣ���Ϊ����һ��ָ���ʱ�����tpw
    LCD1602_EN = 0;
}
#endif
#ifndef LCD_1602_4PINS
void LCDInit() //LCD4λ���нӿڵĳ�ʼ��
{
    LCDWriteCmd(LCD_MODE_PIN8); //��ʾ��ģʽ��������5*8�ĵ���
    LCDWriteCmd(LCD_DIS_ON);  //��ʾ��,����,��겻��˸
    LCDWriteCmd(LCD_CURSOR_RIGHT);  //�������,��ʾ���ƶ�
    LCDWriteCmd(LCD_SCREEN_CLR);  //����
}
#else
void LCDInit() //LCD��ʼ��
{
    LCDWriteCmd(0x33);
    LCDWriteCmd(0x32);
    LCDWriteCmd(LCD_MODE_PIN4); //��ʾ��ģʽ��������5*8�ĵ���
    LCDWriteCmd(LCD_DIS_ON);  //��ʾ��,����,��겻��˸
    LCDWriteCmd(LCD_CURSOR_RIGHT);  //�������,��ʾ���ƶ�
    LCDWriteCmd(LCD_SCREEN_CLR);  //����
}
#endif

void LCDSetPosition(unsigned char x,unsigned char y) //ȷ����ʾλ�õĺ���
{
    if(0==y)  //DDRAM��ַ����
    {
        LCDWriteCmd(0x80 | x);  //��ʾ�ڵ�һ��ĳ��λ��
    }
    else
    {
        LCDWriteCmd(0x80 | (0x40+x)); //��ʾ�ڵڶ���ĳ��λ��
    }
}
void LCDShowStr(unsigned char x,unsigned char y,unsigned char *str)
{
    LCDSetPosition(x,y);
    while(*str != '\0')
    {
        LCDWriteData(*str++);
    }
}

//��һ�ַ���
/***void LCDWriteCGRAM()
{
    unsigned char i;
    LCDWriteCmd(0x40); //1,�����Զ�����ַ�
    for(i = 0;i < 8;i++)
    {
        LCDWriteData(str[i]);
    }
    //��ʾ����ַ�
    LCDWriteCmd(0x80 | 0x05);
    LCDWriteData(0x00); //д���ַ����ڵ�ַ
    
}
***/

/***
���ƣ�LCDSetChar
������x-�У�y-�У�pos-CGRAMλ�� *str-�Զ����ַ�����
��������
���ܣ��Զ����ַ���ʾ
***/
void LCDSetChar(unsigned char x,unsigned char y,unsigned char pos,unsigned char *str)
{
    //��Χ�޶�x:0~16,y:0~1,pos:0~7 str:��ʾ�ַ���ָ��
    unsigned char i;
    //�ȹ����Զ����ַ� ȷ��λ�� CGRAM
    for(i = 0;i<8;i++)
    {
        LCDWriteCmd(0x40+pos*8+i);  //д���ݵ�ַ
        LCDWriteData(*(str+i));
    }
    //��ʾ
    LCDSetPosition(x,y); //������ʾλ�ã�DDRAM
    LCDWriteData(0x00+pos); //��ʾ����
    
}


/***
���ƣ�IntegerToStr
������dat ��������  *str�ַ�����
�������ַ�������ַ�����
���ܣ�������ת�ַ���
***/
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

