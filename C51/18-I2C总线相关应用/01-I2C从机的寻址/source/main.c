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
    I2CStart(); //����������ʼ�ź�
    I2CWriteByte(addr << 1); // 0101 0000 0xA0 дһ���ֽڣ���һ���ֽ�һ��������Ѱַ�ֽ�
    ack = I2CReccvAck(); //ÿдһ���ֽڣ��ӻ�����һ��ackӦ��λ
    I2CStop(); //��������ֹͣ�źţ�����һ�����ݴ���
    
    return ack;
}
    