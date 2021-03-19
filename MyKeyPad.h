/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 03/13/2021
* Project: Lab 7 Part 1
* File: MyLCD.h
* Description:
*
**************************************************************************************/

#ifndef MYKEYPAD_H_
#define MYKEYPAD_H_

char Keypad_Read(void);
int state(void);
char getButton(void);
const char* getPin();
void Keypad_Print(char c);

#endif /* MYKEYPAD_H_ */
