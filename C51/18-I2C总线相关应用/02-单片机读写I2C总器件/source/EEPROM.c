#include "EEPROM.h"

/**************
功能：读取器件地址为IC_Addr的器件内部字节地址addr中的数据
*******************/
unsigned char E2ReadByte(unsigned char IC_Addr,unsigned char addr)
{
    unsigned char dat;
    I2CStart();
    I2CWriteByte(IC_Addr<<1); //器件寻址，执行写操作,从机应答在函数内部实现
    I2CWriteByte(addr); //写内部的字节地址，告诉器件要从哪个地方开始读数据
    I2CStart();
    I2CWriteByte((IC_Addr<<1) | 0x01); //后续操作为读操作，从地址addr读数据
    dat = I2CReadByte();  //从总线上读取数据
    SendAck(1); //主机只读一个字节，发not ack，发1，如果读取多个字节，发送0
    I2CStop();
    
    return dat;
}