#ifndef __DISPLAY_H__
#define __DISPLAY_H__


#include<reg51.h> //����51ͷ�ļ�������ʶ��P1,P2
#define GPIO_DIG     P1 //���� I/O�ڵĺ궨��
#define GPIO_PLACE   P2 //λѡ I/O�ڵĺ궨��
#define     N	     4	//�����ĺ궨��

unsigned char code leddata[];  //����������
extern unsigned char LEDBuf[]; //ȫ�ֱ���������������Ҫ���ã�Ҫ������ⲿ�������������


void Display();	 //����������

#endif