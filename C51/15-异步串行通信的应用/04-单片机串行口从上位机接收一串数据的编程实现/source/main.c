#include <reg51.h>
#include "uart.h"


void main()
{
    unsigned char i;
    UartInit();
	printf("Wait for Serial Communication Test Start.\r\n");
	printf("Please Send a command:\r\n");
    while(1)
    {
        if(recv_flag == 1)
        {
            recv_flag = 0; 
            if(i = 0; i < recv_length; i++)
            {
                sendByte(recv_buf[i]);
            }
        }
    }
}
