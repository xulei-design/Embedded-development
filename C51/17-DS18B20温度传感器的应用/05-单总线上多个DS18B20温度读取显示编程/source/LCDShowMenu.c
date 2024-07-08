#include "LCDShowMenu.h"

extern int TEMPbuf[];

void StartMenu()
{
    LCDShowStr(0,0,"The DAS of TEMP");
    LCDShowStr(6,1,"V1.0");
}

void SubmenuOne()
{
    LCDShowStr(0,0,"CH0:");  //��һ�� ��ʾDS18B20 #1
    ShowTempData(TEMPbuf,0);
    LCDShowStr(0,1,"CH1:");  //�ڶ��� ��ʾDS18B20 #2
    ShowTempData(TEMPbuf,1);
    
}
void SubmenuTwo()
{
    LCDShowStr(0,0,"CH2:"); //�ڶ��������һ�� ��ʾDS18B20 #3
    ShowTempData(TEMPbuf,2);
    LCDShowStr(0,1,"CH3:"); //�ڶ�������ڶ��� ��ʾDS18B20 #4
    ShowTempData(TEMPbuf,3);
}



void AlarmSetMenu()
{
    LCDShowStr(0,0,"   ALARM MENU");
}
void ShowTempData(int *buf,unsigned char index)
{
    int temp;
    float tmp;
    temp = buf[index]; //*(buf+index)
    if(temp < 0) //���¶�ֵΪ����
    {
        if(index%2) //����
            LCDWriteCmd(0xC5); //д��ַ C0��ʾ��ʼ��ַ�ڶ���
        else
            LCDWriteCmd(0x85); //д��ַ 80��ʾ��ʼ��ַ��һ��
        LCDWriteData('-'); //��ʾ��
        temp = ~temp; //�����ţ�ȡ����һ��ԭ��
        temp = temp+1;
        tmp = temp;
        temp = tmp*0.0625*100; //С���������λ
    }
    else //�¶�Ϊ����
    {
         if(index%2) //����
            LCDWriteCmd(0xC5); //д��ַ C0��ʾ��ʼ��ַ�ڶ���
        else
            LCDWriteCmd(0x85);
        LCDWriteData(' '); 
        tmp = temp; //����
        temp = tmp*0.0625*100; //С���������λ
    }
    if(temp >= 10000) //����¶ȴ��ڵ���100�㣬5λ��
    {
         if(index%2) //����
            LCDWriteCmd(0xC7); 
        else
            LCDWriteCmd(0x87);
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
             if(index%2) //����
                LCDWriteCmd(0xC7); 
            else
                LCDWriteCmd(0x87);
            LCDWriteData('0'+temp%10000/1000); //��ʾʮλ
            LCDWriteData('0'+temp%1000/100); //��ʾ��λ
            LCDWriteData('.'); //��ʾ'.'
            LCDWriteData('0'+temp%100/10); //��ʾС����
            LCDWriteData('0'+temp%10); //��ʾС��
            LCDWriteData(' ');
        }
        else
        {
             if(index%2) //����
                LCDWriteCmd(0xC7); 
            else
                LCDWriteCmd(0x87);
            LCDWriteData('0'+temp%1000/100); //��ʾ��λ
            LCDWriteData('.'); //��ʾ'.'
            LCDWriteData('0'+temp%100/10); //��ʾС����
            LCDWriteData('0'+temp%10); //��ʾС��
            LCDWriteData(' ');
            LCDWriteData(' ');
        }
    }
}
