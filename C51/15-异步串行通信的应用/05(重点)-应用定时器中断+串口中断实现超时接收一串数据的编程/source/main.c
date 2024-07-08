#include <reg51.h>
#include "uart.h"



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
        if(recv_flag) //接收完一包数据
        {
            recv_flag = 0;
            start_timer = 0; //关定时器
            sendString(recv_buf);
            clr_recvbuffer(recv_buf); //清除缓冲buffer
        }
    }
}

void Timer0_Init(void)		//1毫秒@11.0592MHz
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
    if(start_timer == 1) //软件定时计数器
    {
        recv_timer_cnt++; //1. 累加定时时间计数器（真实的时间）
        if(recv_timer_cnt > MAX_REV_TIM) //2.判断定时时间是否超过了设定的最大的阈值，
                                         //超过则说明等待一段时间后没有新的数据到，
                                         //我们就判断一包数据接收完了
        {
            recv_timer_cnt=0;      //3.清除定时计数器，处理数据，清除buffer(放到数据处理之后）
            recv_cnt = 0; //接受的数据帧数
            recv_flag = 1;  //接受完一包数据标志位
        }
    }
    TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;
    TR0 = 1;
    
}

