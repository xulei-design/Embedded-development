#include "uart.h"


unsigned char start_timer = 0; //启动软件定时计数器
unsigned char recv_buf[MAX_REV_NUM]; //接收数据缓冲区
unsigned char recv_cnt; //接收字符帧个数的计数变量
unsigned char recv_timer_cnt;  //定时计数器中的计数
unsigned char recv_flag=0;
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
    ES = 1;         //串行中断打开
    
}

void sendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);  //发送等待，发送完成，将发送中断位清0
		TI = 0;
}

void sendString(unsigned char *dat) //只需传递首地址
{
   while(*dat != '\0')
   {
        sendByte(*(dat++)); //*dat代表的是首地址 *dat = &dat
   }       
}

char putchar(char c) //c语言中是打印到屏幕，现在让它打印到串口，定向到串口
//printf重定向
{
    sendByte(c);
    return c;
}

void clr_recvbuffer(unsigned char *buf)
{
    unsigned char i;
    for(i=0;i<MAX_REV_NUM;i++)
    {
        buf[i] = 0;
    }
}


void uart_ISR(void) interrupt 4 
//串行口中断服务函数
//计算机发送一帧数据通过com3口传递到com2口，然后通过com2传递给单片机，
//当单片机接收完这一帧数据时，接收中断RI会置1，进入到中断函数中对数据进行处理，
{
    static unsigned char recv_cnt = 0;
    if(RI)
    {
        RI = 0;
        start_timer = 1; //1.每接收第一帧数据时，启动软件定时计数器去记数
        if(recv_cnt < MAX_REV_NUM)
        {
            recv_buf[recv_cnt] = SBUF; //2.接收数据到数据缓冲区，注意缓冲区的范围
            recv_cnt++;
        }
        else  //超过设定的最大接收数据范围//超过设定的最大接收数据范围
        {
           recv_cnt = MAX_REV_NUM;
        }
        recv_timer_cnt = 0; //3.每接收一帧数据清零，记得把定时的计数清零，相当于喂狗（看门狗）
                            //但是在定时中断里面会不断累加
        
    }
    if(TI)
    {
        TI = 0;
    }
}


