/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 03/13/2021
* Project: Lab 7 Part 1
* File: MySetup.c
* Description:
*
**************************************************************************************/

#include "msp.h"
#include <stdio.h>
#include <string.h>
#include "MySetup.h"

/****| setupIO | ***********************************************
* Brief: Function to configure the input and output bits used
* for the onboard LEDs and switches
* Param:
* none
* return:
* N/A
*************************************************************/
void setupIO(void){
    // Configure Red LED, special function bits to 0, direction to output, resistor off
    P1->SEL0 &= ~BIT0;
    P1->SEL1 &= ~BIT0;
    P1->DIR |= BIT0;
    P1->REN &= ~BIT0;

    // Configure RGB Red LED, special function bits to 0, direction to output, resistor off
    P2->SEL0 &= ~BIT0;
    P2->SEL1 &= ~BIT0;
    P2->DIR |= BIT0;
    P2->REN &= ~BIT0;

    // Configure RGB Green LED, special function bits to 0, direction to output, resistor off
    P2->SEL0 &= ~BIT1;
    P2->SEL1 &= ~BIT1;
    P2->DIR |= BIT1;
    P2->REN &= ~BIT1;

    // Configure RGB Blue LED, special function bits to 0, direction to output, resistor off
    P2->SEL0 &= ~BIT2;
    P2->SEL1 &= ~BIT2;
    P2->DIR |= BIT2;
    P2->REN &= ~BIT2;

    // Configure Switch 1, special function bits to 0, direction to input, resistor enabled as a pull up
    P1->SEL0 &= ~BIT1;
    P1->SEL1 &= ~BIT1;
    P1->DIR &= ~BIT1;
    P1->REN |= BIT1;
    P1->OUT |= BIT1;

    // Configure Switch 2, special function bits to 0, direction to input, resistor enabled as a pull up
    P1->SEL0 &= ~BIT4;
    P1->SEL1 &= ~BIT4;
    P1->DIR &= ~BIT4;
    P1->REN |= BIT4;
    P1->OUT |= BIT4;

    // turn off Red LED
    P1->OUT &= ~BIT0;

    // turn off RGB LED
    P2->OUT &= ~BIT0;
    P2->OUT &= ~BIT1;
    P2->OUT &= ~BIT2;
}

