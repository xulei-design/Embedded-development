#include <reg51.h>
#include "I2C.h"
#include "LCD1602.h"
#include "delay.h"

void main()
{
    bit ack;
    bit E2PROMAddr(unsigned char addr);
    LCDInit();
    delayxms(10);
    ack = E2PROMAddr(0x50);
    
    while(1)
    {    
        LCDSetPosition(0,0);
        LCDWriteData(((unsigned char)ack) + '0');
    }
    
}

bit E2PROMAddr(unsigned char addr)
{
    bit ack;
    I2CStart(); //主机发出起始信号
    I2CWriteByte(addr << 1); // 0101 0000 0xA0 写一个字节，第一个字节一定是器件寻址字节
    ack = I2CReccvAck(); //每写一个字节，从机返回一个ack应答位
    I2CStop(); //主机发出停止信号，结束一次数据传输
    
    return ack;
}
    