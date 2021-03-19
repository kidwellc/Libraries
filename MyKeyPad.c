/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 03/13/2021
* Project: Lab 7 Part 1
* File: MyKeyPad.c
* Description:
*
**************************************************************************************/
#include "msp.h"
#include <stdio.h>
#include <string.h>
#include "MyKeyPad.h"
#include "MyTimer.h"

/****| Keypad_Read | ***********************************************
* Brief: Scan the keypad connected to port 4 and return
* the key that's being pressed.
* Param:
* none
* return:
* Button pressed,
* Return NULL if nothing pressed0 if both buttons pressed
*************************************************************/
char Keypad_Read(void) {
    int temp;

    // Configure all port 4 bits as inputs with pullups
    P4->SEL0 &= 0x80; // clear bits 0-6 in SEL0
    P4->SEL1 &= 0x80; // clear bits 0-6 in SEL1
    P4->DIR &= 0x80; // clear bits 0-6 in DIR
    P4->REN |= 0x7F; // set bits 0-6 in REN
    P4->OUT |= 0x7F; // set bits 0-6 in OUT

    // set col 1 to output low
    P4->DIR |= BIT4; // Set col to output
    P4->OUT &= ~BIT4; // set col to logic low

    temp = state();

    // set col 1 back to input
    P4->DIR &= ~BIT4; // Set col to input
    P4->OUT |= BIT4; // set col ot logic high

    if (temp==1) return '1';
    if (temp==2) return '4';
    if (temp==3) return '7';
    if (temp==4) return '*';

    // set col 2 to output low
    P4->DIR |= BIT5; // Set col to output
    P4->OUT &= ~BIT5; // set col to logic low

    temp = state();

    // set col 2 back to input
    P4->DIR &= ~BIT5; // Set col to input
    P4->OUT |= BIT5; // set col ot logic high

    if (temp==1) return '2';
    if (temp==2) return '5';
    if (temp==3) return '8';
    if (temp==4) return '0';

    // set col 3 to output low
    P4->DIR |= BIT6; // Set col to output
    P4->OUT &= ~BIT6; // set col to logic low

    temp = state();

    // set col 3 back to input
    P4->DIR &= ~BIT6; // Set col to input
    P4->OUT |= BIT6; // set col ot logic high

    if (temp==1) return '3';
    if (temp==2) return '6';
    if (temp==3) return '9';
    if (temp==4) return '#';

    return NULL;
}


/****| state | ***********************************************
* Brief: Check the row inputs to check for two consecutive
* matching readings that are separated by 15ms
* Do Not return a value if more than one button pressed
* Param:
* none
* return:
* row number of button pressed
* F if no button pressed
*************************************************************/
int state(void){
    int temp,temp2;
    temp=P4->IN & (BIT3 | BIT2 | BIT1 | BIT0); // get initial switch condition and save it
    while(1){
        SysTickDelay(15); // delay a bit
        temp2 = P4->IN & (BIT3 | BIT2 | BIT1 | BIT0); // get another switch condition
        if (temp==temp2){ // if the new switch condition matches the saved one
            if (temp == 0x07) return 4;
            if (temp == 0x0B) return 3;
            if (temp == 0x0D) return 2;
            if (temp == 0x0E) return 1;
            if (temp == 0x0F) return 0xF;
        }
        temp = temp2; // otherwise, update saved condition with new one
    }
}

/****| getButton | ***********************************************
* Brief: function to wait for and return a button press
* Param:
* none
* return:
* character value of the button that was pressed.
*************************************************************/
char getButton(void) {
    char buttonVal;

    while(1) {
        buttonVal = Keypad_Read();
        if (buttonVal != NULL) break;
    }
    Keypad_Print(buttonVal);
    while(Keypad_Read() != NULL);
    return buttonVal;
}


/****| getPin | ***********************************************
* Brief: function to return a 4 character pin number.
* asterisk is ignored, # is used as enter
* Param:
* character to be printed
* return:
* Nothing
*************************************************************/
const char* getPin() {
    char *pin[5] = {'X','X','X','X'};
    char c;

    while(1) {
        c=getButton();
        if(c=='*'); //ignore asterisks
        else if(c=='#') {
            if(pin[0]=='X') printf("Too Few Characters!\n");
            else {
                printf("Pin Entered: [%c][%c][%c][%c]\n", pin[0], pin[1], pin[2], pin[3]);
                return pin;
            }
        }
        else {
            pin[0]=pin[1];
            pin[1]=pin[2];
            pin[2]=pin[3];
            pin[3]=c;
            pin[4]=0x00;
        }
    }
}

/****| Keypad_Print | ***********************************************
* Brief: function to print the key that was pressed to the console
* Param:
* character to be printed
* return:
* Nothing
*************************************************************/
void Keypad_Print(char c) {
    printf("Key [%c]\n", c);

}
