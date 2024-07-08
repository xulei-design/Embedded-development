#include "OneWire.h"





bit OneWireRst()
{
    bit ack;
    EA = 0;
    DS18B20 = 0; //�������ߣ�����λ����
    Delay600us(); //480us-960us��ȡ600us
    DS18B20 = 1; //�ͷ�����
    Delay60us(); //15-60us,ȡ60us
    ack = DS18B20; //��ȡI/O�ڣ���ȡ18B20
    while(!DS18B20); //�ȴ�18B20�ͷ����ߣ��ȴ�����������������ܽ�����һ��
    EA = 1;
    return ack;
    
}
void WriteOneWire(unsigned char dat)
{
    unsigned char tmp;
    EA = 0;
    for(tmp = 0x01; tmp!=0; tmp<<=1)
    {
        DS18B20 = 0; //��������
        _nop_();  //ִ��һ��nopָ��1us
        _nop_(); //��ʱ2us�ж�д0/1
        if((dat &tmp) == 0)  //dat&tmp�൱��ȡ���λ����ʱд0��д������һ���ֽڵ�д
        {
            DS18B20 = 0;
            Delay60us();
            DS18B20 = 1;
        }
        else   //д1
        {
            DS18B20 = 1;
            Delay60us();
            DS18B20 = 1;
        }

    }
    EA = 1;
}

unsigned char ReadOneWire()
{
    
    unsigned char dat;
    unsigned char tmp;
    EA = 0;
    for(tmp = 0x01;tmp !=0;tmp<<=1)
    {
        DS18B20 = 0;
        _nop_();
        _nop_();
        DS18B20 = 1;
        _nop_();
        _nop_();
        if(!DS18B20)   
            dat &= ~tmp; //ĳλ��0�룬�κν����λ����0��������λ���
        else
            dat |= tmp; //ĳλ��1���κν����λ����1��������λ���
        Delay60us();
    }
    EA = 1;
    return dat;
    
}

