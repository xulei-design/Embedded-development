#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

#include <reg51.h>
#include "delay.h"
#include <intrins.h>

sbit DS18B20 = P3^7; //DS18B20½Ó¿Ú
bit OneWireRst();
void WriteOneWire(unsigned char dat);
unsigned char ReadOneWire();




#endif