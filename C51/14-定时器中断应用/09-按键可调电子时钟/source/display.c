#include"display.h"	  //����ܵ���ʾ����


unsigned char code leddata[]={ 
//����������ܵĶ����
				0x3f, //0
				0x06, //1
				0x5b, //2
				0x4f, //3
				0x66, //4
				0x6d, //5
				0x7d, //6
				0x07, //7
				0x7f, //8
				0x6f, //9
				0xff, //a
				0x7c, //b
				0x39, //c
				0x5e, //d
				0x79, //e
				0x71, //f
				0x76, //h
				0x38, //l
				0x37, //n
				0x3e, //u
				0x73, //p
				0x5c, //0
				0x00,  //Ϩ��
				0x40  //--
				 
};

unsigned char LEDBuf[] = {0,0,0,0}; //������ʾ������
unsigned char code PLACE_CODE[] = {0xf7,0xfb,0xfd, 0xfe}; //λѡ�źţ��ǳ��������õ�ROM��

void Display()
{
	static unsigned char i=0 ;
		switch(i)
		{
			case 0:
				GPIO_DIG = 0x00;
				GPIO_PLACE = PLACE_CODE[0];
				GPIO_DIG = leddata[LEDBuf[0]];			
				i++;
				break; 
			case 1:
				GPIO_DIG = 0x00;
				GPIO_DIG = leddata[LEDBuf[1]];
				GPIO_PLACE = PLACE_CODE[1];
			
				i++;
				break; 
			case 2:
				GPIO_DIG = 0x00;
				GPIO_DIG = leddata[LEDBuf[2]];
				GPIO_PLACE = PLACE_CODE[2];
				
				i++;
				break;
			case 3:
				GPIO_DIG = 0x00;
				GPIO_DIG = leddata[LEDBuf[3]];
				GPIO_PLACE = PLACE_CODE[3];
				i=0;
				break;
			default:break;
		}

}