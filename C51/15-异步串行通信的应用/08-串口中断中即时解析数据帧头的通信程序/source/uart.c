#include "uart.h"



unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt;
unsigned char recv_flag=0;
unsigned char machine_step = 0;



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
                if(recv_buf[recv_cnt] == 0x0D) //�ж���ȷ����
                {
                    switch(recv_buf[2]) //ȡ����/������������
                        case 11: //����LED��
                            led_data = recv_buf[3]; //led_data��һ���֣�16λ
                            led_data = led_data << 8;
                            led_data = led_data + recv_buf[4];
                            led_cnt = 0; //Ŀ����ʹLED�����������յ����ݵ�ʱ��
                            break;
                        case 12: //���Ʒ�����
                            beep_data = recv_buf[3]; //led_data��һ���֣�16λ
                            beep_data = led_data << 8;
                            beep_data = led_data + recv_buf[4];
                            beep_cnt = beep_data; 
                            break;
                        machine_step = 0;
                        recv_cnt = 0;
                        recv_flag = 1; //������һ�����ݣ���־λ��1
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


