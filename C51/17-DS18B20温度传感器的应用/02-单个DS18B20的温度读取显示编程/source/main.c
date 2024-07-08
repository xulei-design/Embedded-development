#include <reg51.h>
#include "LCD1602.h"
#include "delay.h"
#include "OneWire.h"
#include "DS18B20.h"

unsigned char flag;
void Timer0_Init();
void main()
{
    unsigned char ack;
    int temp; //��������¶�����
    float tmp;
    Timer0_Init();
    LCDInit();
    Start18B20();  //�����¶�ת��
    delayxms(10);
    while(1)
    {
        if(flag == 1)
        {
            flag = 0;
            Start18B20();
            ack = Read18B20(&temp);  //��ȡ��ǰ�¶�
            if(ack == 1) //���ݶ�ȡ�ɹ�
            {
                if(temp<0) //���¶�ֵΪ����
                {
                    LCDWriteCmd(0x80); //д��ַ80��ʾ��ʼ��ַ
                    LCDWriteData('-'); //��ʾ��
                    temp = ~temp; //�����ţ�ȡ����һ��ԭ��
                    temp = temp+1;
                    tmp = temp;
                    temp = tmp*0.0625*100; //С���������λ
                }
                else
                {
                    LCDWriteCmd(0x80); //д��ַ80��ʾ��ʼ��ַ
                    LCDWriteData(' '); 
                    tmp = temp; //����
                    temp = tmp*0.0625*100; //С���������λ
                }
                if(temp >= 10000) //����¶ȴ��ڵ���100�㣬5λ��
                {
                    LCDWriteCmd(0x82); //д��ַ82��ʾ��ʼ��ַ
                    LCDWriteData('0'+temp/10000); //��ʾ��λ
                    LCDWriteData('0'+temp%10000/1000); //��ʾʮλ
                    LCDWriteData('0'+temp%1000/100); //��ʾ��λ
                    LCDWriteData('.'); //��ʾ'.'
                    LCDWriteData('0'+temp%100/10); //��ʾС����
                    LCDWriteData('0'+temp%10); //��ʾС��
                }
                else
                {
                    if(temp >= 1000)  //�¶ȴ��ڵ���10��
                    {
                        LCDWriteCmd(0x82); //д��ַ82��ʾ��ʼ��ַ
                        LCDWriteData('0'+temp%10000/1000); //��ʾʮλ
                        LCDWriteData('0'+temp%1000/100); //��ʾ��λ
                        LCDWriteData('.'); //��ʾ'.'
                        LCDWriteData('0'+temp%100/10); //��ʾС����
                        LCDWriteData('0'+temp%10); //��ʾС��
                        LCDWriteData(' ');
                    }
                    else
                    {
                        LCDWriteCmd(0x82); //д��ַ82��ʾ��ʼ��ַ
                        LCDWriteData('0'+temp%1000/100); //��ʾ��λ
                        LCDWriteData('.'); //��ʾ'.'
                        LCDWriteData('0'+temp%100/10); //��ʾС����
                        LCDWriteData('0'+temp%10); //��ʾС��
                        LCDWriteData(' ');
                        LCDWriteData(' ');
                    }
                }
            }
            Start18B20();
        }
    }
}

void Timer0_Init(void)		//10΢��@12.000MHz
{
	//AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//���ö�ʱ��ģʽ
	TL0 = 0xF6;				//���ö�ʱ��ʼֵ
	TH0 = 0xFF;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
    ET0 = 1;
    EA = 1;
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}

void Timer0_ISR(void) interrupt 1
{
    static unsigned char timer0Cnt = 0;
    TR0 = 0;
    timer0Cnt++;
    if(timer0Cnt >=100 )
    {
        timer0Cnt = 0;
        flag = 1;
    }
    TL0 = 0xF6;				//���ö�ʱ��ʼֵ
	TH0 = 0xFF;		
    TR0 = 1;
}

