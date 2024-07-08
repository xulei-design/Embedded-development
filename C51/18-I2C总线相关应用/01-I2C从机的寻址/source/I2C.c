#include "I2C.h"


void I2CStart() //启动总线函数
{
    I2C_SCL = 1;  //总线空闲时 SCL SDA都为高电平
    I2C_SDA = 1;
    I2CDelay(); //SCL保持4.7个us之后，拉低SDA，产生起始信号
    I2C_SDA = 0;
    I2CDelay(); //SCL再维持4.7个us之后，拉低SCL，一个时钟周期结束
    I2C_SCL = 0;
}
     
void I2CWriteByte(unsigned char dat) //写一个字节的函数
{
    unsigned char temp;
    for(temp = 0x80; temp != 0; temp >>= 1) //从最高位开始写
    {
        if((temp & dat) == 0) //当前位为0
            I2C_SDA = 0;
        else                  //当前位为 1
            I2C_SDA = 1;    
        I2CDelay(); //延时至少4us 使得SCL保持低
        I2C_SCL = 1; //拉高 器件读数据位
        I2CDelay(); //延时至少4us 使得SCL保持高
        I2C_SCL = 0; //拉低
    }
}
bit I2CReccvAck() //读应答信号
{
    bit ack;
    I2C_SDA = 1; //主机主动释放SDA，为读ACK做准备
    I2CDelay();  //SCL保持4.7us低
    I2C_SCL = 1;
    ack = I2C_SDA;
    I2CDelay();
    I2C_SCL = 0; //拉低SCL
    return (ack);
    
}

void I2CStop()
{
    I2C_SCL = 0;  
    I2C_SDA = 0;
    I2CDelay();
    I2C_SCL = 1;
    I2CDelay();
    I2C_SDA = 1;
    I2CDelay();
}  