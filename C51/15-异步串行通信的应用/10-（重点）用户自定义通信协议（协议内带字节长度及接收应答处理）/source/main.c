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
            switch(recv_buf[0]) //ȡ����/������������
            {
                case 1: //����LED��
                    led_data = recv_buf[1]; //led_data��һ���֣�16λ
                    led_data = led_data << 8;
                    led_data = led_data + recv_buf[2];
                    led_cnt = 0; //Ŀ����ʹLED�����������յ����ݵ�ʱ��
                    break;
                case 2: //���Ʒ�����
                    beep_data = recv_buf[1]; //led_data��һ���֣�16λ
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
void Timer0_Init(void)		//1���붨ʱ���ĳ�ʼ��
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
    if(led_cnt < led_data)  //������С�����������ݵĵ���ʱ�䣬LED�Ƶ���
    {
        led_cnt++;
        LED = 0;
    }
    else
    {
        LED = 1; //ʹ��LED��Ϩ��
    }
    if(beep_cnt != 0)
    {
        beep_cnt--;
        BEEP = ~BEEP; //�������������źŷ�������������
    }
    TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;
    TR0 = 1;
    
}

