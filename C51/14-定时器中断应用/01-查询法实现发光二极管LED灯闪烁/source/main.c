#include<reg51.h>


void timer0_Iint();
sbit LED = P1^0;
void main()
{
	timer0_Iint();
	while(1)
	{
		if(TF0 == 1)
		{
			TF0 = 0;
			TH0 = (65536 - 50000)/256; //���¸���ֵ
			TL0 = (65536 - 50000)%256;
			LED = ~LED;
		}	
	}

}

void timer0_Iint() //��ʱ��0�ĳ�ʼ��
{
	//1.����TMOD ȷ��������ʽ ��ʱ  ������ʽ1 GATE = 0
	TMOD = 0x01;
	//2.��ֵ�ļ��� ��ʱ��ֵ50ms  12M
	TH0 = (65536 - 50000)/256;
	TL0 = (65536 - 50000)%256;
	//3.�򿪶�ʱ��
	TR0 = 1;
}
