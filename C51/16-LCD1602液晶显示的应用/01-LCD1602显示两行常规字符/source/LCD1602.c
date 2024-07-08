#include "LCD1602.h"


void LCDReadBF()  //忙为检测
{
    unsigned char state;
    unsigned char i;
    LCD1602_DB = 0xFF; //IO口置1，做输入
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    
    do
    {
        LCD1602_EN = 1;
        state = LCD1602_DB; 
        LCD1602_EN = 0;
        i++;
        if(i>50)  //忙信号一直为1，自动退出
        {
            break;
        }
    }
    while(state & 0x80); //最高位为1，忙，等待。最高位为0，退出循环
}

void LCDWriteCmd(unsigned char cmd)
{
    LCDReadBF(); //等待忙检测，不忙时操作
    LCD1602_RS = 0; //写命令
    LCD1602_RW = 0;
    LCD1602_DB = cmd;
    LCD1602_EN = 1;  //不忙时，LCD1602_EN已经为0
    //不需要延时了，因为处理一个指令的时间大于tpw
    LCD1602_EN = 0;
    
}
void LCDWriteData(unsigned char dat)
{
    LCDReadBF(); //等待忙检测，不忙时操作
    LCD1602_RS = 1; //写数据
    LCD1602_RW = 0;
    LCD1602_DB = dat;
    LCD1602_EN = 1;  //不忙时，LCD1602_EN已经为0
    //不需要延时了，因为处理一个指令的时间大于tpw
    LCD1602_EN = 0;
    
}

void LCDInit() //LCD初始化
{
    LCDWriteCmd(LCD_MODE_PIN8); //显示的模式设置两行5*8的点阵
    LCDWriteCmd(LCD_DIS_ON);  //显示开,光标关,光标不闪烁
    LCDWriteCmd(LCD_CURSOR_RIGHT);  //光标右移,显示不移动
    LCDWriteCmd(LCD_SCREEN_CLR);  //清屏
}

void LCDShowStr(unsigned char x,unsigned char y,unsigned char *str)
{
    if(0==y)  //DDRAM地址设置
    {
        LCDWriteCmd(0x80 | x);  //显示在第一行某个位置
    }
    else
    {
        LCDWriteCmd(0x80 | (0x40+x)); //显示在第二行某个位置
    }
    while(*str != '\0')
    {
        LCDWriteData(*str++);
    }
}