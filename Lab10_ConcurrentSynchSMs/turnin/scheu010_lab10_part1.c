/*	Author: scheu010
 *  Partner(s) Name: vivian
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

volatile unsigned char TimerFlag = 0; //timerISR() sets this to 1. C programmer should clear to 0

//internal variables for mapping AVR's ISR to our cleaner timerISR model
unsigned long _avr_timer_M = 1; //start count from here, down to 0. default 1ms
unsigned long _avr_timer_cntcurr = 0; //current internal count of 1ms ticks


void TimerOn() {
	//avr timer/counter controller register TCCR1
	TCCR1B = 0x0B; //bit3=0: CTC mode (clear timer on compare)

	//avr output compare register OCR1A
	OCR1A = 125; //timer interrupt will be generated when TCNT1==OCR1A

	//avr timer interrupt mask register
	TIMSK1 = 0x02; //bit1: OCIE1A -- enables match interrupt

	//initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	//timerISR will be called every _avr_timer_cntcurr millisecs

	//enable glibal interrupts
	SREG |= 0x80; 
}

void TimerOff() {
	TCCR1B = 0x00; 
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}


//set timerISR() to tick every M ms
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

unsigned char tt = 0x00;
unsigned char bb = 0x00;

enum TStates {TStart, LED0, LED1, LED2}Tstate;

void TTick() {
	switch(Tstate) { //transitions
		case TStart:
			Tstate = LED0;
			break;

		case LED0:
			Tstate = LED1;
			break;

		case LED1: 
			Tstate = LED2;
			break;

		case LED2: 
			Tstate = LED0;
			break;

		
	}
		
	switch(Tstate){ //actions
		case TStart:
			break;

		case LED0:
			tt = 0x01;
			break;

		case LED1: 
			tt = 0x02;
			break;

		case LED2: 
			tt = 0x04;
			break;
		
	}
}

enum BStates {BStart, ON, OFF}Bstate;

void BTick() {
	switch(Bstate) { //transitions
		case BStart:
			Bstate = ON;
			break;

		case ON:
			Bstate = OFF;
			break;

		case OFF: 
			Bstate = ON;
			break;
	}
		
	switch(Bstate){ //actions
		case BStart:
			break;

		case ON:
			bb = 0x08;
			break;

		case OFF: 
			bb = 0x00;
			break;
	}
}

enum CStates {CStart, Combine}Cstate;

void CTick() {
	switch(Cstate) { //transitions
		case CStart:
			Cstate = Combine;
			break;

		case Combine:
			Cstate = Combine;
			break;
	}
		
	switch(Cstate){ //actions
		case CStart:
			break;

		case Combine:
			PORTB = (tt | bb);
			break;
	}
}


int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;

	Tstate = TStart;
	Bstate = BStart;
	Cstate = CStart;
	TimerSet(1000);
	TimerOn();
	while(1) {
		TTick();
		BTick();
		CTick();
		
		while (!TimerFlag);
		TimerFlag = 0;
	}
}


