#include<reg51.h>
#include"Key.h"
#include"display.h"
void Key_Service();
void Dis_Service();

unsigned int NumCut;
void main()
{	
	while(1)
	{
		Dis_Service(); //��ʼ����

		Key_Service();//����������

		Display(); //��ʾ������
	}
}

void Key_Service() //���̹��ܺ���
{
	switch(Key_Scan())
		{
			case 0:break;
			case 1:
				NumCut++;
				if(NumCut>9999)
					NumCut = 0;
			break;
			case 2:
				NumCut++;
				if(NumCut>9999)
					NumCut = 9999;
			break;
			case 3:
				NumCut=0;
			break;
			case 4:
				NumCut=88;
			break;
			default: break;
		}
}
void Dis_Service()
{
	LEDBuf[0] = NumCut/1000; 
	LEDBuf[1] =	NumCut/100%10;
	LEDBuf[2] =	NumCut/10%10;
	LEDBuf[3] =	NumCut%10;	
}