#include "uart.h"

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
   // ES = 1;         //�����жϴ�
    // EA = 1;
}

void sendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);  //��ѯ��ʽ����TI=0ʱ��һֱ�ȴ���ֱ��TI = 1��ִ����һ����䡣
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


