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

void clr_recvbuffer(unsigned char *buf)  //清除数组数据，数据缓冲区
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
 
    static unsigned char recv_data; //接受的中间变量
    static unsigned char sum_check;
    static unsigned char xor_check;
    static unsigned char recv_cnt = 0;
    if(RI)
    {
        RI = 0;
        recv_data = SBUF;
        switch(machine_step)
        {
            case 0:
                if(recv_data == 0x55)
                {
                    machine_step = 1;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 1:
                if(recv_data == 0xAA)
                {
                    machine_step = 2;
                    recv_cnt = 0;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 2:  //校验从数据校验，帧头帧尾不会校验，开始和校验，异或校验，接收数据
                sum_check += recv_data;
                xor_check ^= recv_data;
                recv_buf[recv_cnt] = recv_data; //保存数据
                recv_cnt++;
                if(recv_cnt > 2)    //数据固定个数        
                {
                    machine_step = 3;
                }
                else
                {
                    machine_step = 2;
                }
            break;
            case 3:  //校验
                if(sum_check == recv_data) //和校验通过
                {   
                    machine_step = 4;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 4:
                if(xor_check == recv_data) //异或校验通过
                {   
                    recv_flag = 1;  //正确接收一包数据
                }
                else
                {
                    machine_step = 0;
                }
                machine_step = 0;
                recv_cnt = 0;
                sum_check = 0;
                xor_check = 0;
            break;
            default :break;    
        }
    }
    if(TI)
    {
        TI = 0;
    }
}
