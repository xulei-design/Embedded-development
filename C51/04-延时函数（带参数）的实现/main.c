/*
����:���в�������ʱ����ʵ��С�Ƶ���˸
����ˣ�����
�汾��v1.0
ʱ�䣺2022/5/22
*/

//ͷ�ļ�������
#include<reg51.h>

sbit LED = P1^7;
void DelayXms(unsigned int xms);//��������

void main()
{
	while(1)
	{
		LED = 0;
		DelayXms(1000);//���ú���ʱ������Ҫô��ǰ����������Ҫô�����ڿ��С�
		LED = 1;
		DelayXms(1000);	
	}
}

/*
��������DelayXms
���ܣ���ʱ����
������unsigned int
����ֵ����
*/

void DelayXms(unsigned int xms)	  //�����ر�ȷ
{
	unsigned int i,j; //0-65535   0000h-
	for(i = xms;i>0;i--)
	{
		for(j=124;j>0;j--)
		{
		
		}
	}
}