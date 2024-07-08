#include "uart.h"


unsigned char recv_buf[MAX_REV_NUM]; //���ջ���
unsigned char recv_flag = 0; //������һ�����ݵ����ݱ�־λ��ȫ�ֱ���
unsigned char recv_length;
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
    EA = 1;
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

void uart_ISR(void) interrupt 4 //���п��жϷ�����
//���������һ֡����ͨ��com3�ڴ��ݵ�com2�ڣ�Ȼ��ͨ��com2���ݸ���Ƭ����
//����Ƭ����������һ֡����ʱ�������ж�RI����1�����뵽�жϺ����ж����ݽ��д���
{
    static unsigned char recv_cnt = 0;
    unsigned char temp;
    if(RI)
    {
        RI = 0;
        temp = SBUF;
        if(temp != 0x0D)  //�Իس���Ϊ���������س�����ASCII��ֵΪ0x0d
        {
            recv_buf[recv_cnt] = temp; //����ֻ��һ֡һ֡�Ĵ���
            recv_cnt++;
            if(recv_cnt > MAX_REV_NUM)
            {
               recv_cnt =  MAX_REV_NUM;
            }
        }
        else
        {
           recv_flag = 1;
           recv_length =  recv_cnt; //���յ��ַ�����
           recv_cnt = 0;
        }
       
    }
    if(TI)
    {
        TI = 0;
    }
}


