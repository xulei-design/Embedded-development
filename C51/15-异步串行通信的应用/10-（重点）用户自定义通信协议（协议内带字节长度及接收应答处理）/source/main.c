#include <reg51.h>
#include "uart.h"

sbit LED = P1^0;
sbit BEEP = P3^7;
unsigned int beep_data;
unsigned int beep_cnt;
unsigned int led_cnt;
unsigned int led_data;

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
            switch(recv_buf[0]) //取点亮/蜂鸣器响数据
            {
                case 1: //控制LED灯
                    led_data = recv_buf[1]; //led_data是一个字，16位
                    led_data = led_data << 8;
                    led_data = led_data + recv_buf[2];
                    led_cnt = 0; //目的是使LED点亮上述接收的数据的时间
                    break;
                case 2: //控制蜂鸣器
                    beep_data = recv_buf[1]; //led_data是一个字，16位
                    beep_data = led_data << 8;
                    beep_data = led_data + recv_buf[2];
                    beep_cnt = beep_data; 
                    break;
                default :
                    clr_recvbuffer(recv_buf);
                break;
             } 
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

