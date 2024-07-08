#include "uart.h"


unsigned char rev_data;
unsigned char rev_flag = 0; //���ձ�־λ
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

void sendString(unsigned char *dat) 
{
   while(*dat != '\0')
   {
        sendByte(*(dat++)); //*dat��������׵�ַ *dat = &dat
   }       
}

char putchar(char c) //c�������Ǵ�ӡ����Ļ������������ӡ�����ڣ����򵽴���
{
    sendByte(c);
    return c;
}

void uart_ISR(void) interrupt 4 //���п��жϷ�����
//���������һ֡����ͨ��com3�ڴ��ݵ�com2�ڣ�Ȼ��ͨ��com2���ݸ���Ƭ����
//����Ƭ����������һ֡����ʱ�������ж�RI����1�����뵽�жϺ����ж����ݽ��д���
{
    if(RI)
    {
        RI = 0;
        rev_data = SBUF;//��������͸���Ƭ�������ݱ�������
        rev_flag = 1; //���ձ�־λ
//        rev_data = rev_data+1; //�����ݴ���
//        SBUF = rev_data; //�ش��������    
    }
    if(TI)
    {
        TI = 0;
    }
}


