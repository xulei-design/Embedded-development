#include "LCD1602.h"

#ifndef LCD_1602_4PINS
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
#else
void LCDReadBF()  //忙为检测
{
    unsigned char state;
    unsigned char i;
    LCD1602_DB |= 0xF0; //高四位IO口置1，低四位保持不变，做输入
    LCD1602_RS = 0;
    LCD1602_RW = 1;
    
    do
    {
        LCD1602_EN = 1;
        state = LCD1602_DB & 0xF0; //先读高四位
        LCD1602_EN = 0;
        
        LCD1602_EN = 1;
        state |= (LCD1602_DB&0xF0)>>4 ; //读低四位
        LCD1602_EN = 0;
        i++;
        if(i>50)  //忙信号一直为1，自动退出
        {
            break;
        }
    }
    while(state & 0x80); //最高位为1，忙，等待。最高位为0，退出循环
}
#endif

#ifndef LCD_1602_4PINS
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
#else
void LCDWriteCmd(unsigned char cmd)
{
    LCD1602_RS = 0; //写命令
    LCD1602_RW = 0;
    LCD1602_DB = cmd; //写高四位
    LCD1602_EN = 1;  //不忙时，LCD1602_EN已经为0
    delayxms(1);//不需要延时了，因为处理一个指令的时间大于tpw
    LCD1602_EN = 0;
    
    LCD1602_DB = cmd << 4; //写低四位
    LCD1602_EN = 1;  
    delayxms(1);
    LCD1602_EN = 0;
    
}
#endif
#ifndef LCD_1602_4PINS
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
#else
void LCDWriteData(unsigned char dat)
{
    LCDReadBF(); //等待忙检测，不忙时操作
    LCDReadBF(); //等待忙检测，不忙时操作
    LCD1602_RS = 1; //写数据
    LCD1602_RW = 0;
    LCD1602_DB = dat;
    LCD1602_EN = 1;  //不忙时，LCD1602_EN已经为0
    delayxms(1);//不需要延时了，因为处理一个指令的时间大于tpw
    LCD1602_EN = 0;
    
    LCD1602_DB = dat << 4;
    LCD1602_EN = 1;  //不忙时，LCD1602_EN已经为0
    delayxms(1);//不需要延时了，因为处理一个指令的时间大于tpw
    LCD1602_EN = 0;
}
#endif
#ifndef LCD_1602_4PINS
void LCDInit() //LCD4位并行接口的初始化
{
    LCDWriteCmd(LCD_MODE_PIN8); //显示的模式设置两行5*8的点阵
    LCDWriteCmd(LCD_DIS_ON);  //显示开,光标关,光标不闪烁
    LCDWriteCmd(LCD_CURSOR_RIGHT);  //光标右移,显示不移动
    LCDWriteCmd(LCD_SCREEN_CLR);  //清屏
}
#else
void LCDInit() //LCD初始化
{
    LCDWriteCmd(0x33);
    LCDWriteCmd(0x32);
    LCDWriteCmd(LCD_MODE_PIN4); //显示的模式设置两行5*8的点阵
    LCDWriteCmd(LCD_DIS_ON);  //显示开,光标关,光标不闪烁
    LCDWriteCmd(LCD_CURSOR_RIGHT);  //光标右移,显示不移动
    LCDWriteCmd(LCD_SCREEN_CLR);  //清屏
}
#endif

void LCDSetPosition(unsigned char x,unsigned char y) //确定显示位置的函数
{
    if(0==y)  //DDRAM地址设置
    {
        LCDWriteCmd(0x80 | x);  //显示在第一行某个位置
    }
    else
    {
        LCDWriteCmd(0x80 | (0x40+x)); //显示在第二行某个位置
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

//第一种方法
/***void LCDWriteCGRAM()
{
    unsigned char i;
    LCDWriteCmd(0x40); //1,构造自定义的字符
    for(i = 0;i < 8;i++)
    {
        LCDWriteData(str[i]);
    }
    //显示这个字符
    LCDWriteCmd(0x80 | 0x05);
    LCDWriteData(0x00); //写大字符所在地址
    
}
***/

/***
名称：LCDSetChar
参数：x-列，y-行，pos-CGRAM位置 *str-自定义字符数据
参数：无
功能：自定义字符显示
***/
void LCDSetChar(unsigned char x,unsigned char y,unsigned char pos,unsigned char *str)
{
    //范围限定x:0~16,y:0~1,pos:0~7 str:显示字符的指针
    unsigned char i;
    //先构造自定义字符 确定位置 CGRAM
    for(i = 0;i<8;i++)
    {
        LCDWriteCmd(0x40+pos*8+i);  //写数据地址
        LCDWriteData(*(str+i));
    }
    //显示
    LCDSetPosition(x,y); //设置显示位置，DDRAM
    LCDWriteData(0x00+pos); //显示代码
    
}


/***
名称：IntegerToStr
参数：dat 整形数据  *str字符数据
参数：字符数组的字符长度
功能：整型数转字符串
***/
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

