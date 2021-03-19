/**************************************************************************************
* Author: Christina Kidwell
* Course: EGR 226 - 905
* Date: 032/13/2021
* Project: Lab 7 Part 1
* File: MyTimer.h
* Description:
*
**************************************************************************************/

#ifndef MYTIMER_H_
#define MYTIMER_H_
void TimerAInit(void);
void TimerASetPeriod(uint16_t period);
void TimerASetDutyCycle(uint16_t dutyCycle);
void TimerASetMotorSpeed(float motorSpeed);
void TimerAStopMotor(void);
void microDelay (unsigned microsec);
void msDelay (unsigned ms);
void SysTickInit (void);
void SysTickDelay (uint16_t delay);
#endif /* MYTIMER_H_ */
