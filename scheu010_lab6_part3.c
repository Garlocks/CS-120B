/*	Author: Steve C
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

enum States {Start, INIT, ADD, MINUS, RESET}state;

void Tick() {
	switch(state) { //transitions
		case Start:
			PORTB = 0x07;
			state = INIT;
			break;

		case INIT:
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state = RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;

		case ADD: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}

		case MINUS: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}

		case RESET:
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
	}
		
	switch(state){ //actions
		case Start:
			PORTB = 0x07;
			break;

		case INIT:
			break;

		case ADD: 
			if (PORTB < 0x09) {
				PORTB = PORTB + 0x01;
			}
			break;

		case MINUS: 
			if (PORTB > 0x00) {
				PORTB = PORTB - 0x01;
			}
			break;

		case RESET:
			PORTB = 0x00;
			break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;

	state = Start;
	TimerSet(300);
	TimerOn();
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
