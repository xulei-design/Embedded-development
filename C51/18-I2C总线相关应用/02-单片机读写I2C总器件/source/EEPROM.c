#include "EEPROM.h"

/**************
���ܣ���ȡ������ַΪIC_Addr�������ڲ��ֽڵ�ַaddr�е�����
*******************/
unsigned char E2ReadByte(unsigned char IC_Addr,unsigned char addr)
{
    unsigned char dat;
    I2CStart();
    I2CWriteByte(IC_Addr<<1); //����Ѱַ��ִ��д����,�ӻ�Ӧ���ں����ڲ�ʵ��
    I2CWriteByte(addr); //д�ڲ����ֽڵ�ַ����������Ҫ���ĸ��ط���ʼ������
    I2CStart();
    I2CWriteByte((IC_Addr<<1) | 0x01); //��������Ϊ���������ӵ�ַaddr������
    dat = I2CReadByte();  //�������϶�ȡ����
    SendAck(1); //����ֻ��һ���ֽڣ���not ack����1�������ȡ����ֽڣ�����0
    I2CStop();
    
    return dat;
}