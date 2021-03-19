/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 03/13/2021
* Project: Lab 7 Part 1
* File: MyLCD.h
* Description:
*
**************************************************************************************/

#ifndef MYLCD_H_
#define MYLCD_H_
void LCD_init (void);
void PulseEnablePin (void);
void pushNibble (uint8_t nibble);
void pushByte (uint8_t byte);
void commandWrite (uint8_t command);
void dataWrite (uint8_t data);
void writeLCD(char *myString);
#endif /* MYLCD_H_ */
