#include<reg51.h>

void main()
{
//while(1)���棺�����������ʼ������Ĵ���
	unsigned int i;
	while(1)
	{
		i =20000;
		P1 = 0x7e; //1111 1110 
		//��һ��  ��ʱ
		while(i--);
		i = 20000;		
		P1 = 0xff; //1111 1111
		//��һ��  ��ʱ
		while(i--);
		
		
	}
}