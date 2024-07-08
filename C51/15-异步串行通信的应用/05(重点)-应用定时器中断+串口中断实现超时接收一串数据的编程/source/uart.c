#include "uart.h"


unsigned char start_timer = 0; //���������ʱ������
unsigned char recv_buf[MAX_REV_NUM]; //�������ݻ�����
unsigned char recv_cnt; //�����ַ�֡�����ļ�������
unsigned char recv_timer_cnt;  //��ʱ�������еļ���
unsigned char recv_flag=0;
void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
    ES = 1;         //�����жϴ�
    
}

void sendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);  //���͵ȴ���������ɣ��������ж�λ��0
		TI = 0;
}

void sendString(unsigned char *dat) //ֻ�贫���׵�ַ
{
   while(*dat != '\0')
   {
        sendByte(*(dat++)); //*dat��������׵�ַ *dat = &dat
   }       
}

char putchar(char c) //c�������Ǵ�ӡ����Ļ������������ӡ�����ڣ����򵽴���
//printf�ض���
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
//���п��жϷ�����
//���������һ֡����ͨ��com3�ڴ��ݵ�com2�ڣ�Ȼ��ͨ��com2���ݸ���Ƭ����
//����Ƭ����������һ֡����ʱ�������ж�RI����1�����뵽�жϺ����ж����ݽ��д���
{
    static unsigned char recv_cnt = 0;
    if(RI)
    {
        RI = 0;
        start_timer = 1; //1.ÿ���յ�һ֡����ʱ�����������ʱ������ȥ����
        if(recv_cnt < MAX_REV_NUM)
        {
            recv_buf[recv_cnt] = SBUF; //2.�������ݵ����ݻ�������ע�⻺�����ķ�Χ
            recv_cnt++;
        }
        else  //�����趨�����������ݷ�Χ//�����趨�����������ݷ�Χ
        {
           recv_cnt = MAX_REV_NUM;
        }
        recv_timer_cnt = 0; //3.ÿ����һ֡�������㣬�ǵðѶ�ʱ�ļ������㣬�൱��ι�������Ź���
                            //�����ڶ�ʱ�ж�����᲻���ۼ�
        
    }
    if(TI)
    {
        TI = 0;
    }
}


