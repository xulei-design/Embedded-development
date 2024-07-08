#include "DS18B20.h"

unsigned char code rom1[] = {0x28,0xFF,0x50,0xB9, 0xC0,0x17,0x05,0x31}; //��һ��DS18B20rom��
unsigned char code rom2[] = {0x28,0xFE,0x50,0xB9, 0xC0,0x17,0x05,0x30};
unsigned char code rom3[] = {0x28,0xFD,0x50,0xB9, 0xC0,0x17,0x05,0x29};
unsigned char code rom4[] = {0x28,0xFC,0x50,0xB9, 0xC0,0x17,0x05,0x28};

bit Start18B20()
{
    bit ack;
    //1.��ʼ�����ж��Ƿ��е���������
    ack = OneWireRst();
    if(ack == 0)
    {
        //2.ROMָ��
        WriteOneWire(SKIP_ROM);
        //3.����ָ�� �����¶�ת��
        WriteOneWire(CONVERT_T);
    }
    return ~ack;
}

bit Read18B20(int * temp) //���ݶ�ȡ�ɹ�����ack=1
{
    bit ack;
    unsigned char MSB,LSB;
    //1.��ʼ�����ж��Ƿ��е���������
    ack = OneWireRst();
    if(ack == 0)
    {
        //2.ROMָ��
        WriteOneWire(SKIP_ROM); //����������������ͨ��
        //3.����ָ�� �����¶�ת��
        WriteOneWire(READ_REGISTER);
        //4.��ת����� ���ݹ���ָ����ȷ��
        LSB = ReadOneWire();
        MSB = ReadOneWire();
        *temp = ((int)MSB<<8) + LSB;
    }
    return ~ack;
}

void ReadRomCode(unsigned char *romcode)
{
    unsigned char i;
    bit ack;
    ack = OneWireRst();
    if(ack == 0)
    {
        WriteOneWire(READ_ROM); //��ȡromָ��
        for(i=0;i<8;i++)  //��ȡ8���ֽڵ�64λROM��
        {
            //romcode[i] = ReadOneWire();
            *(romcode+i) = ReadOneWire();
        }
        
    }
}

void MatchRomCode(unsigned char n) //���ݲ�����ƥ�䲻ͬ��DS18B20 ROM��
{
    unsigned char i;
    WriteOneWire(MATH_ROM); //��������������ͨ��,����ROM��
    switch(n)
    {
        case 1: 
            for(i=0;i<8;i++)
                WriteOneWire(rom1[i]);
        break;
        case 2: 
            for(i=0;i<8;i++)
                WriteOneWire(rom2[i]);
        break;
        case 3:
            for(i=0;i<8;i++)
                WriteOneWire(rom3[i]);
        break;
        case 4:  
            for(i=0;i<8;i++)
                WriteOneWire(rom4[i]);
        break;
        default: break;
    }
}

void Get18B20Temp(int *temp,unsigned char n)
{
    bit ack;
    unsigned char MSB,LSB;
    //1.��ʼ�����ж��Ƿ��е���������
    ack = OneWireRst();
    while(ack);  
    //2.ROMָ��
    MatchRomCode(n); //����������������ͨ��,ƥ��ROMָ��,
    //3.����ָ�� �����¶�ת��
    WriteOneWire(CONVERT_T);
    //������ƥ��ROM���¶�ת��
    
    
    //1.��ʼ��
    ack = OneWireRst();
    while(ack);
    //2.ROMָ�� ƥ��ɹ�ִ����һ��
    MatchRomCode(n);
    //3.����ָ�� ��ȡת�����
    WriteOneWire(READ_REGISTER);
    //4.��ȡת����� ���ݹ���ָ����ȷ��
    LSB = ReadOneWire();
    MSB = ReadOneWire();
    *temp = ((int)MSB<<8) + LSB;
    //��ȡ��������¶�ת������
    
}
    