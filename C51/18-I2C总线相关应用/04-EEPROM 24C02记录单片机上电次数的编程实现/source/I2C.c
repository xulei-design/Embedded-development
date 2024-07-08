#include "I2C.h"


void I2CStart() //�������ߺ���
{
    I2C_SCL = 1;  //���߿���ʱ SCL SDA��Ϊ�ߵ�ƽ
    I2C_SDA = 1;
    I2CDelay(); //SCL����4.7��us֮������SDA��������ʼ�ź�
    I2C_SDA = 0;
    I2CDelay(); //SCL��ά��4.7��us֮������SCL��һ��ʱ�����ڽ���
    I2C_SCL = 0;
}
     
void I2CWriteByte(unsigned char dat) //дһ���ֽڵĺ���
{
    unsigned char temp;
    for(temp = 0x80; temp != 0; temp >>= 1) //�����λ��ʼд
    {
        if((temp & dat) == 0) //��ǰλΪ0
            I2C_SDA = 0;
        else                  //��ǰλΪ 1
            I2C_SDA = 1;    
        I2CDelay(); //��ʱ����4us ʹ��SCL���ֵ�
        I2C_SCL = 1; //���� ����������λ
        I2CDelay(); //��ʱ����4us ʹ��SCL���ָ�
        I2C_SCL = 0; //����
    }
}
bit I2CReccvAck() //��Ӧ���ź�
{
    bit ack;
    I2C_SDA = 1; //���������ͷ�SDA��Ϊ��ACK��׼��
    I2CDelay();  //SCL����4.7us��
    I2C_SCL = 1;
    ack = I2C_SDA;
    I2CDelay();
    I2C_SCL = 0; //����SCL
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