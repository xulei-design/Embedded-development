#include<reg51.h>
#include<intrins.h>//�ҵ���_nop_�Ŀ⺯���ĵ���


void Delay5000ms();//����������

void main()
{
	while(1)
	{
		P1 = 0xfe;
		Delay5000ms();//��ʱ ��һ��
		P1 = 0xff;
		Delay5000ms();//��ʱ ��һ��

	
	}
}

void Delay5000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	/*��һ��������û����������һ��C51��һ���⺯������Ҫ�ҵ�����⺯����
	��help�ĵ��С���β��ң�1.���help��2.�����һ����3.�����˺������ҵ����ڿ�   */
	i = 38;
	j = 0;
	k = 118;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
