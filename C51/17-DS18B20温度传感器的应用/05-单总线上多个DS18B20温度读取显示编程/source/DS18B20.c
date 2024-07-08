#include "DS18B20.h"

unsigned char code rom1[] = {0x28,0xFF,0x50,0xB9, 0xC0,0x17,0x05,0x31}; //第一个DS18B20rom码
unsigned char code rom2[] = {0x28,0xFE,0x50,0xB9, 0xC0,0x17,0x05,0x30};
unsigned char code rom3[] = {0x28,0xFD,0x50,0xB9, 0xC0,0x17,0x05,0x29};
unsigned char code rom4[] = {0x28,0xFC,0x50,0xB9, 0xC0,0x17,0x05,0x28};

bit Start18B20()
{
    bit ack;
    //1.初始化，判断是否有单总线器件
    ack = OneWireRst();
    if(ack == 0)
    {
        //2.ROM指令
        WriteOneWire(SKIP_ROM);
        //3.功能指令 启动温度转换
        WriteOneWire(CONVERT_T);
    }
    return ~ack;
}

bit Read18B20(int * temp) //数据读取成功返回ack=1
{
    bit ack;
    unsigned char MSB,LSB;
    //1.初始化，判断是否有单总线器件
    ack = OneWireRst();
    if(ack == 0)
    {
        //2.ROM指令
        WriteOneWire(SKIP_ROM); //建立单总线器件的通信
        //3.功能指令 启动温度转换
        WriteOneWire(READ_REGISTER);
        //4.读转换结果 根据功能指令来确定
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
        WriteOneWire(READ_ROM); //读取rom指令
        for(i=0;i<8;i++)  //读取8个字节的64位ROM码
        {
            //romcode[i] = ReadOneWire();
            *(romcode+i) = ReadOneWire();
        }
        
    }
}

void MatchRomCode(unsigned char n) //根据参数，匹配不同的DS18B20 ROM码
{
    unsigned char i;
    WriteOneWire(MATH_ROM); //建立单总线器件通信,发送ROM码
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
    //1.初始化，判断是否有单总线器件
    ack = OneWireRst();
    while(ack);  
    //2.ROM指令
    MatchRomCode(n); //建立单总线器件的通信,匹配ROM指令,
    //3.功能指令 启动温度转换
    WriteOneWire(CONVERT_T);
    //上面是匹配ROM的温度转换
    
    
    //1.初始化
    ack = OneWireRst();
    while(ack);
    //2.ROM指令 匹配成功执行下一步
    MatchRomCode(n);
    //3.功能指令 读取转换结果
    WriteOneWire(READ_REGISTER);
    //4.读取转换结果 根据功能指令来确定
    LSB = ReadOneWire();
    MSB = ReadOneWire();
    *temp = ((int)MSB<<8) + LSB;
    //读取启动后的温度转换数据
    
}
    