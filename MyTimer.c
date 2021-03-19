/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 03/13/2021
* Project: EGR226 timer library
* File: MyTimer.c
* Description: A library to contain timer and delay related functions
*
**************************************************************************************/
#include "msp.h"
#include "MyTimer.h"

uint16_t periodGlobal;						// global variable to store period cycle count

/****| TimerAInit | ***********************************************
* Brief: a function to initialize Timer A. Default period and duty cycle= 40 Hz & 50%
* Param:
* none
* return:
* N/A
*************************************************************/
void TimerAInit(void) {
    TIMER_A2->CCR[0] = 9375;                // PWM Period (# cycles of clock)
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7; // CCR1 reset/set mode 7
    TIMER_A2->CCR[1] = 4687;                     // CCR1 PWM On cycles
    TIMER_A2->CTL = 0x02D0;                     // SMCLK, /8, up mode, and start

    // Configure Port 5 pin 6, special function bits to 0, direction to output, resistor off
    P5->SEL0 |= BIT6;
    P5->SEL1 &= ~BIT6;
    P5->DIR |= BIT6;
}

/****| TimerASetPeriod | ***********************************************
* Brief: A function to set the period of Timer A2
* Param:
* Number of clock cycles for one period (stores value in globa variable
* return:
* N/A
*************************************************************/
void TimerASetPeriod(uint16_t period) {
    periodGlobal=period;
    TIMER_A2->CCR[0] = period - 1;                // PWM Period (# cycles of clock)

}
	
/****| TimerASetDutyCycle | ***********************************************
* Brief: A function to set the duty cycle of timer A2
* Param:
* Number of cycles the timer output should remain on
* return:
* N/A
*************************************************************/
void TimerASetDutyCycle(uint16_t dutyCycle) {
    TIMER_A2->CCR[1] = dutyCycle;                     // CCR1 PWM duty cycle on cycle count
}
	
/****| TimerASetMotorSpeed | ***********************************************
* Brief: A function to set the speed of a motor connected to P5.6
* Param:
* Motor speed as a fractional value (0.00-1.00 not presently error checked!)
* return:
* N/A
*************************************************************/
void TimerASetMotorSpeed(float motorSpeed) {
    TimerASetDutyCycle(motorSpeed*periodGlobal);	// calculate the number of on cycles 
}													// and send it to the timer
	
/****| TimerAStopMotor | ***********************************************
* Brief: A function to stop Timer A2 thereby halting a motor connected to P5.6
* Param:
* none
* return:
* N/A
*************************************************************/
void TimerAStopMotor(void) {
    TIMER_A2->CCR[0] = 0;                // Setting PWM Period to zero stops motor
}
	
/****| microDelay | ***********************************************
* Brief: Use the SysTick Timer peripheral to generate a delay in microseconds
* for this function. It must be able to generate delays between 10 and 100 μs.
* NOTE: If the master clock is running at the default 3 MHz, the overhead of
* making this C function call can make short delays a bit longer than expected.
* Measure the duration of some expected delays (especially short ones) using
* the Digital Probe attachment to the oscilloscope. You can compensate for
* this function call overhead by passing a smaller parameter if necessary.
* Param:
* Microseconds to delay
* return:
* N/A
*************************************************************/
void microDelay (unsigned microsec) {
    SysTick -> LOAD = ((microsec * 3) - 1); //delay for 1 microsecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}


/****| msDelay | ***********************************************
* Brief: This function uses the SysTick timer peripheral to generate
* a delay in milliseconds. This function must be able to generate a
* delay of at least 60ms.
* NOTE: Since you use the SysTick timer for both the microsecond and
* millisecond delay functions, each delay function will require a
* different scale factor to produce the proper delay.
* Param:
* Milliseconds to delay
* return:
* N/A
*************************************************************/
void msDelay (unsigned ms) {
    SysTick -> LOAD = ((ms * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

/****| SysTickInit | *********************************************
* Brief: Function to initialize SysTick for use as a millisecond timer
* Param:
* none
* return:
* N/A
*************************************************************/
void SysTickInit (void) {
    //initialization of systic timer
    SysTick->CTRL = 0; // disable SysTick During step
    SysTick->LOAD = 0x00FFFFFF; // max reload value
    SysTick->VAL = 0; // any write to current clears it
    SysTick->CTRL = 0x00000005; // enable systic, 3MHz, No Interrupts
}

/****| SysTickDelay | *********************************************
* Brief: Function that uses SysTick to generate a delay
* of a given number of milliseconds
* Param:
* uint16_t delay = number of milliseconds to delay
* return:
* N/A
*************************************************************/
void SysTickDelay (uint16_t delay) {
    // Systick delay function
    SysTick -> LOAD = ((delay * 3000) - 1); //delay for 1 msecond per delay value
    SysTick -> VAL = 0; // any write to CVR clears it
    while ((SysTick -> CTRL & 0x00010000) == 0); // wait for flag to be SET
}

