/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 03/13/2021
* Project: Lab 7 Part 1
* File: MyLCD.c
* Description:
*
**************************************************************************************/
#include "msp.h"
#include "MyLCD.h"
#include "MyTimer.h"

/****| LCD_init | ***********************************************
* Brief: This function goes through the entire initialization 
* sequence as shown in Figure 4.
* Param:
* none
* return:
* N/A
*************************************************************/
void LCD_init (void) {
    // set P3.6&7 and P2.4-7 as outputs.

    // Configure RS pin
    P3->SEL0 &= ~BIT6;
    P3->SEL1 &= ~BIT6;
    P3->DIR |= BIT6;
    P3->REN &= ~BIT6;
    P3->OUT &= ~BIT6;

    // Configure E pin
    P3->SEL0 &= ~BIT7;
    P3->SEL1 &= ~BIT7;
    P3->DIR |= BIT7;
    P3->REN &= ~BIT7;
    P3->OUT &= ~BIT7;

    // Configure data pins
    P2->SEL0 &= 0x0F; // clear bits 4-7 in SEL0
    P2->SEL1 &= 0x0F; // clear bits 4-7 in SEL1
    P2->DIR |= 0xF0; // set bits 4-7 in DIR
    P2->REN &= 0x0F; // clear bits 4-7 in REN

    commandWrite(3); // Reset the display
    msDelay(100);
    commandWrite(3);
    microDelay(200);
    commandWrite(3);
    msDelay(10);

    commandWrite(2); // set 4 bit mode
    microDelay(100);
    commandWrite(0x28); // 2 lines 5x7 format
    microDelay(100);
    commandWrite(0x0F); // display on, cursor on, blinking
    microDelay(100);
    commandWrite(0x01); // clear display
    microDelay(100);
    commandWrite(0x06); // increment cursor
    msDelay(10);
}

/****| PulseEnablePin | ***********************************************
* Brief: This function will sequence the Enable (E) pin as shown 
* in Figure 6.
* Param:
* none
* return:
* N/A
*************************************************************/
void PulseEnablePin (void) {
    P3->OUT &= ~BIT7; 	// clear E pin
    microDelay(10);		// delay 10 micro seconds
    P3->OUT |= BIT7; 	// Set E pin
    microDelay(10);		// delay 10 micro seconds
    P3->OUT &= ~BIT7; 	// clear E pin
    microDelay(10);		// delay 10 micro seconds
}

/****| pushNibble | ***********************************************
* Brief: This function pushes 1 nibble onto the data pins and 
* pulses the Enable pin.
* Param:
* Nibble to send to the display
* return:
* N/A
*************************************************************/
void pushNibble (uint8_t nibble) {
    P2->OUT &= 0x0F;          // clear bits 4-7 in OUTput port
    P2->OUT |= (nibble << 4); // shift and send nibble to OUTput port
    PulseEnablePin ();
}

/****| pushByte | ***********************************************
* Brief: This function first pushes the most significant 4 bits 
* of the byte onto the data pins by calling the pushNibble () function. 
* Next, it pushes the least significant 4 bits onto the data pins by 
* calling the pushNibble ( ) function again.
* Param:
* Byte to send to the display
* return:
* N/A
*************************************************************/
void pushByte (uint8_t byte) {
    pushNibble ((byte >> 4) & 0x0F);	// send the upper nibble
    pushNibble (byte & 0x0F);			// send the lower nibble
}

/****| commandWrite | ***********************************************
* Brief: This function will write one byte of COMMAND by calling 
* the pushByte ( ) function with the COMMAND parameter. This function 
* will move the cursor to the next line by sending a byte command 
* of 0xC0 followed by a delay of 100μs.
* Param:
* Command to send to the display
* return:
* N/A
*************************************************************/
void commandWrite (uint8_t command) {
    P3->OUT &= ~BIT6;   // set RS to indicate command byte being sent
    pushByte (command); // output the byte
    microDelay(100);    // delay 100 micro seconds
}

/****| dataWrite | ***********************************************
* Brief: This function will write one byte of DATA by calling the 
* pushByte ( ) function with the DATA parameter
* Param:
* Data to send to the display
* return:
* N/A
*************************************************************/
void dataWrite (uint8_t data) {
    P3->OUT |= BIT6; // set RS to indicate data byte being sent
    pushByte (data); // output the byte
    microDelay(100); // delay 100 micro seconds
}

/****| writeLCD | ***********************************************
* Brief: This function will write a string of DATA by calling the
* dataWrite( ) function for each byte of the string. Output stops
* when the end of the string is reached.
* Param:
* pointer to string to send to the display
* return:
* N/A
*************************************************************/
void writeLCD(char *myString)
{
    int i = 0;
    while(1) {
        dataWrite(myString[i++]);		// output a character, point to the next
        if(myString[i]=='\0') break;	// exit if we've reached the end of the string
    }
}

