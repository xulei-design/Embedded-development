#include <reg51.h>
#include <intrins.h>
#include "delay.h"

void UartInit(void);
unsigned char temp = 0x01;
void main()
{
    UartInit();	
    while(1)
    {
        SBUF = temp; //������ʽ1��10λ�첽����ͨ�� 0 1000 1000 1
        while(!TI)  // ֹͣ�ȴ�
        TI = 0;
        P1 = temp;
        temp = _crol_(temp,1);
        delayxms(1000);
    }  
}

void UartInit(void)	//4800bps@11.0592MHz   �����ʵ�����
{
	SCON = 0x50;		
 //8λ����,�ɱ䲨���� SM0����λ�� SM1 (���ù�����ʽ��SM2�����ͨ��ʹ�ܣ� REN�������н���λ��
 // TB8 RB8����Ϲ���3ʹ�ã� TI(�����жϱ�־λ) RI(�����жϱ�־λ��
 // SM0 SM1 SM2 REN TB8 RB8 TI RI
 //  0   1   0   1   0   0   0  0 ��0x50��
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1��������ʽ2��Ϊ8λ�Զ���װ��ʽ  M0 M1 C/T GATE M0 M1 C/T GATE
	TL1 = 0xFA;		//�趨��ʱ��ֵ                                   0  0   0   0   0  1  0   0
	TH1 = 0xFA;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}
