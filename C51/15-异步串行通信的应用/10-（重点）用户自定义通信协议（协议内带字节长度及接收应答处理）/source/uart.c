#include "uart.h"



unsigned char recv_buf[MAX_REV_NUM];
unsigned char recv_cnt;
unsigned char recv_flag=0;
unsigned char machine_step = 0;



void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
    ES = 1;         //�����жϴ�
    
}

void sendByte(unsigned char dat)
{
	SBUF = dat;
	while(!TI);  //���͵ȴ���������ɣ��������ж�λ��0
		TI = 0;
}

void sendString(unsigned char *dat) //ֻ�贫���׵�ַ
{
   while(*dat != '\0')
   {
        sendByte(*(dat++)); //*dat��������׵�ַ *dat = &dat
   }       
}

char putchar(char c) //c�������Ǵ�ӡ����Ļ������������ӡ�����ڣ����򵽴���
//printf�ض���
{
    sendByte(c);
    return c;
}

void clr_recvbuffer(unsigned char *buf)  //����������ݣ����ݻ�����
{
    unsigned char i;
    for(i=0;i<MAX_REV_NUM;i++)
    {
        buf[i] = 0;
    }
}


void uart_ISR(void) interrupt 4 
//���п��жϷ�����
//���������һ֡����ͨ��com3�ڴ��ݵ�com2�ڣ�Ȼ��ͨ��com2���ݸ���Ƭ����
//����Ƭ����������һ֡����ʱ�������ж�RI����1�����뵽�жϺ����ж����ݽ��д���
{
 
    static unsigned char recv_data; //���ܵ��м����
    static unsigned char sum_check;
    static unsigned char xor_check;
    static unsigned char recv_cnt = 0;
    if(RI)
    {
        RI = 0;
        recv_data = SBUF;
        switch(machine_step)
        {
            case 0:
                if(recv_data == 0x55)
                {
                    machine_step = 1;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 1:
                if(recv_data == 0xAA)
                {
                    machine_step = 2;
                    recv_cnt = 0;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 2:  //У�������У�飬֡ͷ֡β����У�飬��ʼ��У�飬���У�飬��������
                sum_check += recv_data;
                xor_check ^= recv_data;
                recv_buf[recv_cnt] = recv_data; //��������
                recv_cnt++;
                if(recv_cnt > 2)    //���ݹ̶�����        
                {
                    machine_step = 3;
                }
                else
                {
                    machine_step = 2;
                }
            break;
            case 3:  //У��
                if(sum_check == recv_data) //��У��ͨ��
                {   
                    machine_step = 4;
                }
                else
                {
                    machine_step = 0;
                }
            break;
            case 4:
                if(xor_check == recv_data) //���У��ͨ��
                {   
                    recv_flag = 1;  //��ȷ����һ������
                }
                else
                {
                    machine_step = 0;
                }
                machine_step = 0;
                recv_cnt = 0;
                sum_check = 0;
                xor_check = 0;
            break;
            default :break;    
        }
    }
    if(TI)
    {
        TI = 0;
    }
}
