#ifndef __LCDSHOWMENU_H__
#define __LCDSHOWMENU_H__
#include "LCD1602.h"





void StartMenu();
void SubmenuOne();
void SubmenuTwo();
void SubmenuThree();
void SubmenuFour();
void AlarmSetMenu();
void ShowTempData(unsigned char x,unsigned char y, int *buf,unsigned char index);





#endif