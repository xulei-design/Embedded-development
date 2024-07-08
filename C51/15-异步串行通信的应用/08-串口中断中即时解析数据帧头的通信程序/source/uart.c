#include "uart.h"



unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt;
unsigned char recv_flag=0;
unsigned char machine_step = 0;



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
        switch(machine_step)
        {
            case 0:recv_buf[0] = SBUF;
                if(recv_buf[0] == 0xAA)
                {
                    machine_step = 1;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 1:recv_buf[1] = SBUF;
                if(recv_buf[1] == 0x55)
                {
                    machine_step = 2;
                    recv_cnt = 2;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 2: recv_buf[recv_cnt] = SBUF;
                recv_cnt++;
                if(recv_cnt > 4)
                {
                    machine_step = 3;
                }
                else
                {
                    machine_step = 2;
                }
            break;
            case 3:recv_buf[recv_cnt] = SBUF; 
                if(recv_buf[recv_cnt] == 0x0D) //判断正确接收
                {
                    switch(recv_buf[2]) //取点亮/蜂鸣器响数据
                        case 11: //控制LED灯
                            led_data = recv_buf[3]; //led_data是一个字，16位
                            led_data = led_data << 8;
                            led_data = led_data + recv_buf[4];
                            led_cnt = 0; //目的是使LED点亮上述接收的数据的时间
                            break;
                        case 12: //控制蜂鸣器
                            beep_data = recv_buf[3]; //led_data是一个字，16位
                            beep_data = led_data << 8;
                            beep_data = led_data + recv_buf[4];
                            beep_cnt = beep_data; 
                            break;
                        machine_step = 0;
                        recv_cnt = 0;
                        recv_flag = 1; //接受完一串数据，标志位置1
                }
                
            break; 
            defalut :break;
        }
    }
    if(TI)
    {
        TI = 0;
    }
}


