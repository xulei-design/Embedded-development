#include "OneWire.h"





bit OneWireRst()
{
    bit ack;
    EA = 0;
    DS18B20 = 0; //拉低总线，发复位脉冲
    Delay600us(); //480us-960us，取600us
    DS18B20 = 1; //释放总线
    Delay60us(); //15-60us,取60us
    ack = DS18B20; //读取I/O口，读取18B20
    while(!DS18B20); //等待18B20释放总线，等待存在脉冲结束，才能进入下一步
    EA = 1;
    return ack;
    
}
void WriteOneWire(unsigned char dat)
{
    unsigned char tmp;
    EA = 0;
    for(tmp = 0x01; tmp!=0; tmp<<=1)
    {
        DS18B20 = 0; //拉低总线
        _nop_();  //执行一个nop指令1us
        _nop_(); //延时2us判断写0/1
        if((dat &tmp) == 0)  //dat&tmp相当于取最低位，此时写0，写数据是一个字节的写
        {
            DS18B20 = 0;
            Delay60us();
            DS18B20 = 1;
        }
        else   //写1
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
            dat &= ~tmp; //某位与0与，任何结果这位都是0，保存这位结果
        else
            dat |= tmp; //某位与1或，任何结果这位都是1，保存这位结果
        Delay60us();
    }
    EA = 1;
    return dat;
    
}

