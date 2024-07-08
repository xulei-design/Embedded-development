#include "LCDShowMenu.h"

extern int TEMPbuf[];

void StartMenu()
{
    LCDShowStr(0,0,"The DAS of TEMP");
    LCDShowStr(6,1,"V1.0");
}

void SubmenuOne()
{
    LCDShowStr(0,0,"CH0:");  //第一行 显示DS18B20 #1
    ShowTempData(TEMPbuf,0);
    LCDShowStr(0,1,"CH1:");  //第二行 显示DS18B20 #2
    ShowTempData(TEMPbuf,1);
    
}
void SubmenuTwo()
{
    LCDShowStr(0,0,"CH2:"); //第二个界面第一行 显示DS18B20 #3
    ShowTempData(TEMPbuf,2);
    LCDShowStr(0,1,"CH3:"); //第二个界面第二行 显示DS18B20 #4
    ShowTempData(TEMPbuf,3);
}



void AlarmSetMenu()
{
    LCDShowStr(0,0,"   ALARM MENU");
}
void ShowTempData(int *buf,unsigned char index)
{
    int temp;
    float tmp;
    temp = buf[index]; //*(buf+index)
    if(temp < 0) //当温度值为负数
    {
        if(index%2) //奇数
            LCDWriteCmd(0xC5); //写地址 C0表示初始地址第二行
        else
            LCDWriteCmd(0x85); //写地址 80表示初始地址第一行
        LCDWriteData('-'); //显示负
        temp = ~temp; //补码存放，取反加一求原码
        temp = temp+1;
        tmp = temp;
        temp = tmp*0.0625*100; //小数点后保留两位
    }
    else //温度为正数
    {
         if(index%2) //奇数
            LCDWriteCmd(0xC5); //写地址 C0表示初始地址第二行
        else
            LCDWriteCmd(0x85);
        LCDWriteData(' '); 
        tmp = temp; //正数
        temp = tmp*0.0625*100; //小数点后保留两位
    }
    if(temp >= 10000) //如果温度大于等于100°，5位数
    {
         if(index%2) //奇数
            LCDWriteCmd(0xC7); 
        else
            LCDWriteCmd(0x87);
        LCDWriteData('0'+temp/10000); //显示百位
        LCDWriteData('0'+temp%10000/1000); //显示十位
        LCDWriteData('0'+temp%1000/100); //显示个位
        LCDWriteData('.'); //显示'.'
        LCDWriteData('0'+temp%100/10); //显示小数点
        LCDWriteData('0'+temp%10); //显示小数
    }
    else
    {
        if(temp >= 1000)  //温度大于等于10°
        {
             if(index%2) //奇数
                LCDWriteCmd(0xC7); 
            else
                LCDWriteCmd(0x87);
            LCDWriteData('0'+temp%10000/1000); //显示十位
            LCDWriteData('0'+temp%1000/100); //显示个位
            LCDWriteData('.'); //显示'.'
            LCDWriteData('0'+temp%100/10); //显示小数点
            LCDWriteData('0'+temp%10); //显示小数
            LCDWriteData(' ');
        }
        else
        {
             if(index%2) //奇数
                LCDWriteCmd(0xC7); 
            else
                LCDWriteCmd(0x87);
            LCDWriteData('0'+temp%1000/100); //显示个位
            LCDWriteData('.'); //显示'.'
            LCDWriteData('0'+temp%100/10); //显示小数点
            LCDWriteData('0'+temp%10); //显示小数
            LCDWriteData(' ');
            LCDWriteData(' ');
        }
    }
}
