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


double song[30] = {523.25, 261.63, 392.00, 329.63, 493.88, 
				   440.00, 440.00, 440.00, 440.00, 293.66,
				   523.25, 261.63, 392.00, 329.63, 493.88, 
				   440.00, 440.00, 493.88, 523.25, 293.66,
				   523.25, 000.00, 000.00, 000.00, 493.88, 
				   440.00, 440.00, 493.88, 523.25, 293.66};
				 
unsigned char songpos = 0x00;


void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){TCCR3B &= 0x08;}
		else { TCCR3B |= 0x03;}
		
		if(frequency < 0.954){OCR3A = 0xFFFF;}
		else if (frequency > 31250){OCR3A = 0x0000;}
		else{OCR3A = (short)(8000000 / (128*frequency))-1;}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1<<COM3A0);
	TCCR3B = (1<<WGM32) | (1<<CS31) | (1<<CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


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

enum States {Start, INIT, Sing, Inc, Wait}state;
unsigned char temp = 0x00;

void Tick() {
	switch(state) { //transitions
		case Start:
			state = INIT;
			break;

		case INIT:
			if ((~PINA & 0x01) == 0x01) {
				state = Sing;
			} else {
				state = INIT;
			}
			break;

		case Sing: 
			PORTB = 0x02;
			set_PWM(song[songpos]);
			if (songpos < 0x1E) {
				state = Inc;
			} else if (songpos >= 0x1E) {
				state = Wait;
			}
			break;
			
		case Inc: 
			PORTB = 0x04;
			songpos = songpos + 1;
			if (songpos < 0x1E) {
				state = Sing;
			} else if (songpos >= 0x1E) {
				state = Wait;
			}
			break;
		
		case Wait: 
			if ((~PINA & 0x01) == 0x01) {
				state = Wait;
			} else {
				state = INIT;
			}
			break;
	}
		
	switch(state){ //actions
		case Start:
			PORTB = 0xFF;
			songpos = 0x00;
			break;

		case INIT:
			PORTB = 0x01;
			set_PWM(0);
			//songpos = 0x00;
			break;

		case Sing: 
			
			break;
			
		case Inc: 
			
			break;

		case Wait:
			PORTB = 0x0F;
			songpos = 0x00;
			break;
		
	}
}

int main(void) {
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	PWM_on();

	state = Start;
	TimerSet(100);
	TimerOn();
	
	songpos = 0x00;
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
	PWM_off();
	return 1;
}
