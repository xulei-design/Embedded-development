/******************
�ļ�����I2C.c
���ܣ� ��Ƭ��IO��ģ��I2C����ʱ��I2C�ײ㺯��
�汾��
�޶�ʱ�䣺
****************/

#include "I2C.h"
bit I2CRecvAck();

/**************************
��������I2CStart
���ܣ�I2C�����ź�
��������
����ֵ����
***************************/ 
void I2CStart() //�������ߺ���
{
    I2C_SCL = 1;  //���߿���ʱ SCL SDA��Ϊ�ߵ�ƽ
    I2C_SDA = 1;
    I2CDelay(); //SCL����4.7��us֮������SDA��������ʼ�ź�
    I2C_SDA = 0;
    I2CDelay(); //SCL��ά��4.7��us֮������SCL��һ��ʱ�����ڽ���
    I2C_SCL = 0;
}


/********************
��������I2CWriteByte
���ܣ�дһ�����ֽڵ������ϣ�������Ӧ��λ
������������д��
����ֵ����ȡӦ��λ 0:Ӧ�� 1:��Ӧ��
*********************/
bit I2CWriteByte(unsigned char dat) //дһ���ֽڵĺ���
{
    unsigned char temp;
    bit ack;
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
    ack = I2CRecvAck();
    return ack;
}
/********************************
������: I2CRecvAck
���ܣ� ������ȡ�ӻ�Ӧ��λ
��������
����ֵ����ȡӦ��λ 0:Ӧ��  1����Ӧ��
*********************************/
bit I2CRecvAck() //��Ӧ���ź�
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

/********************************
������: I2CReadByte
����: I2C��ȡ�������ֽ�����
����: ��
����ֵ: ��ȡ����
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
��������SendAck
���ܣ�ע�ⷢ��Ӧ��/��Ӧ��
������ack = 0: Ӧ�� ,1����Ӧ��
����ֵ����
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
������:I2CStop
���ܣ�I2Cֹͣ�ź�
��������
����ֵ����
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