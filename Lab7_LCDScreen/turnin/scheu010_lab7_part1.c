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

enum States {Start, INIT, ADD, MINUS, RESET, ADDING, MINUSING}state;
unsigned char temp = 0x00;
unsigned char display = 0x00;

void Tick() {
	switch(state) { //transitions
		case Start:
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
				state = ADDING;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;

		case MINUS: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUSING;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;

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
			break;
			
		case ADDING: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADDING;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;
		
		case MINUSING: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUSING;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;
	}
		
	switch(state){ //actions
		case Start:
			display = 0x00;
			LCD_ClearScreen();
			LCD_WriteData( display + '0');
			temp = 0x00;
			break;

		case INIT:
			temp = 0x00;
			LCD_ClearScreen();
			LCD_WriteData( display + '0');
			break;

		case ADD: 
			temp = 0x00;
			if (display < 0x09) {
				display = display + 0x01;
				LCD_ClearScreen();
				LCD_WriteData( display + '0');
			}
			break;

		case MINUS: 
			temp = 0x00;
			if (display > 0x00) {
				display = display - 0x01;
				LCD_ClearScreen();
				LCD_WriteData( display + '0');
			}
			break;

		case RESET:
			display = 0x00;
			temp = 0x00;
			LCD_ClearScreen();
			LCD_WriteData( display + '0');
			break;
			
		case ADDING: 
			if ((display < 0x09) && (temp >= 0x0A)) {
				display = display + 0x01;
				temp = 0x00;
				LCD_ClearScreen();
				LCD_WriteData( display + '0');
			}
			temp = temp + 0x01;
			break;
		
		case MINUSING: 
			if ((display > 0x00) && (temp >= 0x0A)) {
				display = display - 0x01;
				temp = 0x00;
				LCD_ClearScreen();
				LCD_WriteData( display + '0');
			}
			temp = temp + 0x01;
			break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;

	DDRC = 0xFF; PORTC = 0x00; //LCD data lines
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines

	//initializes LCD display
	LCD_init();

	//starting at position 1 on LCD screen, writes Hello World
	LCD_DisplayString(1, display);
	
	
	state = Start;
	TimerSet(100);
	TimerOn();
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}


