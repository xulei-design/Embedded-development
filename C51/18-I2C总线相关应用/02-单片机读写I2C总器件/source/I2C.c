/******************
文件名：I2C.c
功能： 单片机IO口模拟I2C基本时序，I2C底层函数
版本：
修订时间：
****************/

#include "I2C.h"
bit I2CRecvAck();

/**************************
函数名：I2CStart
功能：I2C启动信号
参数：无
返回值：无
***************************/ 
void I2CStart() //启动总线函数
{
    I2C_SCL = 1;  //总线空闲时 SCL SDA都为高电平
    I2C_SDA = 1;
    I2CDelay(); //SCL保持4.7个us之后，拉低SDA，产生起始信号
    I2C_SDA = 0;
    I2CDelay(); //SCL再维持4.7个us之后，拉低SCL，一个时钟周期结束
    I2C_SCL = 0;
}


/********************
函数名：I2CWriteByte
功能：写一数据字节到总线上，并接受应答位
参数：待数据写入
返回值：读取应答位 0:应答， 1:非应答
*********************/
bit I2CWriteByte(unsigned char dat) //写一个字节的函数
{
    unsigned char temp;
    bit ack;
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
    ack = I2CRecvAck();
    return ack;
}
/********************************
函数名: I2CRecvAck
功能： 主机读取从机应答位
参数：无
返回值：读取应答位 0:应答  1：非应答
*********************************/
bit I2CRecvAck() //读应答信号
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

/********************************
函数名: I2CReadByte
功能: I2C读取总线上字节数据
参数: 无
返回值: 读取数据
***********************************/
unsigned char I2CReadByte()
{
    unsigned char dat = 0;
    unsigned char temp;
    I2C_SDA = 1;
    for(temp = 0x80;temp != 0;temp >>= 1)
    {
        I2CDelay();
        I2C_SCL = 1;
        if(I2C_SDA == 1)
        {
            dat |= temp;
        }
        else
        {
            dat &= ~temp;
        }
        I2CDelay();
        I2C_SCL = 0;
    }
    return dat;
}
/*****************************
函数名：SendAck
功能：注意发送应答/非应答
参数：ack = 0: 应答 ,1：非应答
返回值：无
******************************/
void SendAck(unsigned int ack)
{
    I2C_SDA = ack;
    I2CDelay();
    I2C_SCL = 1;
    I2CDelay();
    I2C_SCL = 0;   
}

/********************
函数名:I2CStop
功能：I2C停止信号
参数：无
返回值：无
*******************/
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