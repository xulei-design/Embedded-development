#include"Key.h"



unsigned char Key_Scan()
{
	unsigned char temp1,temp2;
	unsigned char KeyNum = 22;
	KEYPORT = 0xf0; //����ȫ������͵�ƽ��������Ϊ���룬���д��0��������д��1�����������
	temp1 = KEYPORT; //����I/O�ڣ�
	if(temp1!=0xf0)	 //�ж��Ƿ��м����¡�
	{
		Delayxms(10); //����
		if(temp1!=0xf0) //�ٴ��жϰ����Ƿ��¡�
		{
			temp1 = KEYPORT & 0xf0; //ȡ����λȷ���к�
			KEYPORT = 0x0f; //4�������룬������Ϊ��������д��0��������д��1����������С�	
			temp2 = KEYPORT&0x0f;//���벢ȡ����λȷ���к�
		}
	}
	switch(temp1 + temp2)
	{
		case 0xee: KeyNum = 1; break;
		case 0xed: KeyNum = 2; break;
		case 0xeb: KeyNum = 3; break;
		case 0xe7: KeyNum = 4; break;
		case 0xde: KeyNum = 5; break;
		case 0xdd: KeyNum = 6; break;
		case 0xdb: KeyNum = 7; break;
		case 0xd7: KeyNum = 8; break;
		case 0xbe: KeyNum = 9; break;
		case 0xbd: KeyNum = 10; break;
		case 0xbb: KeyNum = 11; break;
		case 0xb7: KeyNum = 12; break;
		case 0x7e: KeyNum = 13; break;
		case 0x7d: KeyNum = 14; break;
		case 0x7b: KeyNum = 15; break;
		case 0x77: KeyNum = 16; break;
	}

	return KeyNum;
}

