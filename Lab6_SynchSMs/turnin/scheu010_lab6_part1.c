/*	Author: Steve
 *  Partner(s) Name: vtsai006
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1; 
unsigned long _avr_timer_cntcurr = 0; 

void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff()
{
	TCCR1B = 0x00;
}

void TimerISR()
{
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States {Start, LightB0, LightB1, LightB2}state;

void Tick()
{
	switch(state){ //transitions
		case Start:
			state = LightB0;
			break;
		case LightB0:
			state = LightB1;
			break;
		case LightB1:
			state = LightB2;
			break;
		case LightB2:
			state = LightB0;
			break;
	}
	switch(state){ //actions
		case Start:
			PORTB = 0x00;
			break;
		case LightB0:
			PORTB = 0x01;
			break;
		case LightB1:
			PORTB = 0x02;
			break;
		case LightB2:
			PORTB = 0x04;
			break;
	}
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;

	state = Start;
	TimerSet(1000);
	TimerOn();
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

