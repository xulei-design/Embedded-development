#include "uart.h"


unsigned char recv_buf[MAX_REV_NUM]; //接收缓冲
unsigned char recv_flag = 0; //接收完一串数据的数据标志位，全局变量
unsigned char recv_length;
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
    EA = 1;
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

void uart_ISR(void) interrupt 4 //串行口中断服务函数
//计算机发送一帧数据通过com3口传递到com2口，然后通过com2传递给单片机，
//当单片机接收完这一帧数据时，接收中断RI会置1，进入到中断函数中对数据进行处理，
{
    static unsigned char recv_cnt = 0;
    unsigned char temp;
    if(RI)
    {
        RI = 0;
        temp = SBUF;
        if(temp != 0x0D)  //以回车符为结束符，回车符的ASCII码值为0x0d
        {
            recv_buf[recv_cnt] = temp; //数据只能一帧一帧的传递
            recv_cnt++;
            if(recv_cnt > MAX_REV_NUM)
            {
               recv_cnt =  MAX_REV_NUM;
            }
        }
        else
        {
           recv_flag = 1;
           recv_length =  recv_cnt; //接收的字符长度
           recv_cnt = 0;
        }
       
    }
    if(TI)
    {
        TI = 0;
    }
}


