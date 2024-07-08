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
        if(recv_flag) //������һ������
        {
            recv_flag = 0;
            start_timer = 0; //�ض�ʱ��
            sendString(recv_buf);
            clr_recvbuffer(recv_buf); //�������buffer
        }
    }
}

void Timer0_Init(void)		//1����@11.0592MHz
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
    ET0 = 1;
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}

void Timer0_IST(void) interrupt 1 //��ʱ��0���жϱ�־λ���Զ���0
{
   
    TR0 = 0;
    if(start_timer == 1) //�����ʱ������
    {
        recv_timer_cnt++; //1. �ۼӶ�ʱʱ�����������ʵ��ʱ�䣩
        if(recv_timer_cnt > MAX_REV_TIM) //2.�ж϶�ʱʱ���Ƿ񳬹����趨��������ֵ��
                                         //������˵���ȴ�һ��ʱ���û���µ����ݵ���
                                         //���Ǿ��ж�һ�����ݽ�������
        {
            recv_timer_cnt=0;      //3.�����ʱ���������������ݣ����buffer(�ŵ����ݴ���֮��
            recv_cnt = 0; //���ܵ�����֡��
            recv_flag = 1;  //������һ�����ݱ�־λ
        }
    }
    TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;
    TR0 = 1;
    
}

