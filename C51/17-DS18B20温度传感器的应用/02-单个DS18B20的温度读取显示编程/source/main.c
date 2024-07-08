#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "OneWire.h"
#include "DS18B20.h"

unsigned char flag;
void Timer0_Init();
void main()
{
    unsigned char ack;
    int temp; //保存接受温度数据
    float tmp;
    Timer0_Init();
    LCDInit();
    Start18B20();  //启动温度转换
    delayxms(10);
    while(1)
    {
        if(flag == 1)
        {
            flag = 0;
            Start18B20();
            ack = Read18B20(&temp);  //读取当前温度
            if(ack == 1) //数据读取成功
            {
                if(temp<0) //当温度值为负数
                {
                    LCDWriteCmd(0x80); //写地址80表示初始地址
                    LCDWriteData('-'); //显示负
                    temp = ~temp; //补码存放，取反加一求原码
                    temp = temp+1;
                    tmp = temp;
                    temp = tmp*0.0625*100; //小数点后保留两位
                }
                else
                {
                    LCDWriteCmd(0x80); //写地址80表示初始地址
                    LCDWriteData(' '); 
                    tmp = temp; //正数
                    temp = tmp*0.0625*100; //小数点后保留两位
                }
                if(temp >= 10000) //如果温度大于等于100°，5位数
                {
                    LCDWriteCmd(0x82); //写地址82表示初始地址
                    LCDWriteData('0'+temp/10000); //显示百位
                    LCDWriteData('0'+temp%10000/1000); //显示十位
                    LCDWriteData('0'+temp%1000/100); //显示个位
                    LCDWriteData('.'); //显示'.'
                    LCDWriteData('0'+temp%100/10); //显示小数点
                    LCDWriteData('0'+temp%10); //显示小数
                }
                else
                {
                    if(temp >= 1000)  //温度大于等于10°
                    {
                        LCDWriteCmd(0x82); //写地址82表示初始地址
                        LCDWriteData('0'+temp%10000/1000); //显示十位
                        LCDWriteData('0'+temp%1000/100); //显示个位
                        LCDWriteData('.'); //显示'.'
                        LCDWriteData('0'+temp%100/10); //显示小数点
                        LCDWriteData('0'+temp%10); //显示小数
                        LCDWriteData(' ');
                    }
                    else
                    {
                        LCDWriteCmd(0x82); //写地址82表示初始地址
                        LCDWriteData('0'+temp%1000/100); //显示个位
                        LCDWriteData('.'); //显示'.'
                        LCDWriteData('0'+temp%100/10); //显示小数点
                        LCDWriteData('0'+temp%10); //显示小数
                        LCDWriteData(' ');
                        LCDWriteData(' ');
                    }
                }
            }
            Start18B20();
        }
    }
}

void Timer0_Init(void)		//10微秒@12.000MHz
{
	//AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0xF6;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
    ET0 = 1;
    EA = 1;
	TR0 = 1;				//定时器0开始计时
}

void Timer0_ISR(void) interrupt 1
{
    static unsigned char timer0Cnt = 0;
    TR0 = 0;
    timer0Cnt++;
    if(timer0Cnt >=100 )
    {
        timer0Cnt = 0;
        flag = 1;
    }
    TL0 = 0xF6;				//设置定时初始值
	TH0 = 0xFF;		
    TR0 = 1;
}

