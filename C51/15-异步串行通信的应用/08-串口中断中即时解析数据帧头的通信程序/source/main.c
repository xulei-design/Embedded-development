#include <reg51.h>
#include "uart.h"

sbit LED = P1^0;
sbit BEEP = P3^7;
void Timer0_Init(void);
void main()
{
    UartInit();
    Timer0_Init();
    EA = 1;
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a command:\r\n");
    while(1)
    {
        if(recv_flag == 1)
        {
            recv_flag = 0;
            sendString(recv_buf);
            clr_recvbuffer(recv_buf);
        }
    }
}
void Timer0_Init(void)		//1毫秒定时器的初始化
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
    ET0 = 1;
	TR0 = 1;				//定时器0开始计时
}

void Timer0_IST(void) interrupt 1 //定时器0的中断标志位会自动清0
{
   
    TR0 = 0;
    if(led_cnt < led_data)  //当变量小于所接收数据的点亮时间，LED灯点亮
    {
        led_cnt++;
        LED = 0;
    }
    else
    {
        LED = 1; //使得LED灯熄灭
    }
    if(beep_cnt != 0)
    {
        beep_cnt--;
        BEEP = ~BEEP; //给蜂鸣器方波信号蜂鸣器才能鸣响
    }
    TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;
    TR0 = 1;
    
}

