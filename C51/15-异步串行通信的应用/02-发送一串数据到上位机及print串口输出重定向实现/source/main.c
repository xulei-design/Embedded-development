#include <reg51.h>
#include"delay.h"
#include "uart.h"

void main()
{
	unsigned char dat = 88;
	UartInit();	
    while(1)
    {
		//sendString("hello world!\n");
		printf("Hello world!\r\n"); //printf()���������putchar()����
		delayxms(1000);
		printf("dat=%bd\r\n",&dat);
    }
}
