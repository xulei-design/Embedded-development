#include<reg51.h>
#include"display.h"

unsigned int num;
unsigned int timeCnt;
void Timer0Init(void);
void Timer1Init(void);
void DIS_service();
void main()
{
	Timer0Init();
	Timer1Init();
	EA = 1;
	while(1)
	{	
		DIS_service();
	}
}

void DIS_service()
{
	LEDBuf[0] = num/1000;
	LEDBuf[1] = num/100%10;
	LEDBuf[2] = num/10%10;
	LEDBuf[3] = num%10;
}

void Timer0Init(void)		//1����@11.0592MHz
{
	
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0X01;
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1;
}

void Timer0_ISR(void) interrupt 1
{	
	TR0 = 0;
	timeCnt++;
	if(timeCnt >= 1000) //1sʱ�䵽	�ʺϸ�Ƶ����Ƶ���ϴ�
	{
		TR1 = 0;   //���巢�����ر�
		timeCnt = 0;  //���������0��
		num = TH1*256+TL1; //�߰�λ����8λ��ȡ���������� ��Ƶ�ʣ�1s�в�����������
		TH1 = TL1 =0;  //������������е�ֵ����
		TR1 = 1;	
	}
	Display();
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;
	TR0 = 1;
}
void Timer1Init(void)  //�������Ƕ��ⲿ������м���
{
	TMOD &= 0x0f;  //��������λ������λ����
	TMOD |= 0x50;  //���� 0101 0000
	TL1 = 0;   //����������
	TH1 = 0;
	TF1 = 0;
	TR1 = 1;
	ET1 = 1;
}
