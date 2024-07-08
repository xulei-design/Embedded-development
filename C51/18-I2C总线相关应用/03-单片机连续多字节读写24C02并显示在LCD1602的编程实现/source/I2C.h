#ifndef __I2C_H__
#define __I2C_H__


#include <reg51.h>
#include <intrins.h>

#define I2CDelay() {_nop_();_nop_();_nop_();_nop_();}
sbit I2C_SDA = P2^0;
sbit I2C_SCL = P2^1;

void I2CStart();
void I2CWriteByte(unsigned char dat);
bit I2CReccvAck();
void I2CStop();
















#endif