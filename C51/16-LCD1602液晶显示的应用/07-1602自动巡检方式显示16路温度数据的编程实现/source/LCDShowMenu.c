#include "LCDShowMenu.h"

extern int TEMPbuf[];

void StartMenu()
{
    LCDShowStr(0,0,"The DAS of TEMP");
    LCDShowStr(6,1,"V1.0");
}

void SubmenuOne()
{
    LCDShowStr(0,0,"CH0:");
    ShowTempData(4,0,TEMPbuf,0);
    LCDShowStr(0,1,"CH1:");
    ShowTempData(4,1,TEMPbuf,1);
    LCDShowStr(8,0,"CH2:"); 
    ShowTempData(12,0,TEMPbuf,2);
    LCDShowStr(8,1,"CH3:");
    ShowTempData(12,1,TEMPbuf,3);
}
void SubmenuTwo()
{
    LCDShowStr(0,0,"CH4:");
    ShowTempData(4,0,TEMPbuf,4);
    LCDShowStr(0,1,"CH5:");
    ShowTempData(4,1,TEMPbuf,5);
    LCDShowStr(8,0,"CH6:");
    ShowTempData(12,0,TEMPbuf,6);
    LCDShowStr(8,1,"CH7:");
    ShowTempData(12,1,TEMPbuf,7);
}

void SubmenuThree()
{
    LCDShowStr(0,0,"CH8:");
    ShowTempData(4,0,TEMPbuf,8);
    LCDShowStr(0,1,"CH9:");
    ShowTempData(4,1,TEMPbuf,9);
    LCDShowStr(8,0,"CHa:");
    ShowTempData(12,0,TEMPbuf,10);
    LCDShowStr(8,1,"CHb:");
    ShowTempData(12,1,TEMPbuf,11);
}
void SubmenuFour()
{
    LCDShowStr(0,0,"CHc:");
    ShowTempData(4,0,TEMPbuf,12);
    LCDShowStr(0,1,"CHd:");
    ShowTempData(4,1,TEMPbuf,13);
    LCDShowStr(8,0,"CHe:");
    ShowTempData(12,0,TEMPbuf,14);
    LCDShowStr(8,1,"CHf:");
    ShowTempData(12,1,TEMPbuf,15);
}

void AlarmSetMenu()
{
    LCDShowStr(0,0,"   ALARM MENU");
}
void ShowTempData(unsigned char x,unsigned char y, int *buf,unsigned char index)
{
    LCDSetPosition(x,y);
    LCDWriteData(*(buf+index)/100+'0');
    LCDWriteData(*(buf+index)/10%10+'0');
    LCDWriteData('.');
    LCDWriteData(*(buf+index)%10+'0');
}