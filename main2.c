/*	Author: scheu010
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template 
 *	or example code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"

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

unsigned char dartposition;
unsigned char ammoleft;
unsigned char score;
unsigned char targetposition;

enum dartstates {dartinit, dartwait, dartshoot, dartend} dartstate;

void dart() {
	switch(dartstate) { //transitions
		case dartinit:
			dartstate = dartwait;
			break;
		case dartwait:
			if ((~PINA & 0x01) == 0x01) {
				dartstate = dartshoot;
			} else if ((~PINA & 0x01) == 0x00){
				dartstate = dartwait;
			}
			break;
		case dartshoot:
			if (dartposition < 0x13) {
				dartstate = dartstate;
			} else if (dartposition >= 0x13) {
				if (ammoleft <= 0) {
					dartstate = dartend;
				}
				dartstate = dartwait;
			}
			break;
		case dartend:
			if ((~PINA & 0x01) == 0x01) {
				dartstate = dartinit;
			} else if ((~PINA & 0x01) == 0x00){
				dartstate = dartend;
			}
			break;
	}
	switch(dartstate) { //actions
		case dartinit:
			dartposition = 0x01;
			ammoleft = 0x09;
			break;
		case dartwait:
			dartposition = 0x01;
			break;
		case dartshoot:
			if (dartposition < 0x13) {
				dartposition = dartposition + 1;
			} else if (dartposition >= 0x13) {
				if (ammoleft > 0) {
					ammoleft = ammoleft - 1;
				}
			}
			break;
		case dartend:
			score = score;
			break;
	}
}

enum targetstates {targetinit, targetposition1, targetposition2, 
targetposition3, targetposition4, targetend} targetstate;

void target() {
	switch(targetstate) { //transitions
		case targetinit:
			targetstate = targetposition1;
			break;
		case targetposition1:
			targetstate = targetposition2;
			break;
		case targetposition2:
			targetstate = targetposition3;
			break;
		case targetposition3:
			targetstate = targetposition4;
			break;
		case targetposition4:
			targetstate = targetposition5;
			break;
		case targetposition5:
			targetstate = targetposition6;
			break;
		case targetposition6:
			targetstate = targetposition1;
			break;
		case targetend:
			break;
	}
	switch(targetstate) { //actions
		case targetinit:
			targetposition = 0x00;
			LCD_DisplayString(19, " ");
			LCD_DisplayString(39, " ");
			LCD_DisplayString(59, " ");
			LCD_DisplayString(79, " ");
			break;
		case targetposition1:
			targetposition = 0x01;
			LCD_DisplayString(19, "@");
			LCD_DisplayString(39, " ");
			LCD_DisplayString(59, " ");
			LCD_DisplayString(79, " ");
			break;
		case targetposition2:
			targetposition = 0x02;
			LCD_DisplayString(19, " ");
			LCD_DisplayString(39, "@");
			LCD_DisplayString(59, " ");
			LCD_DisplayString(79, " ");
			break;
		case targetposition3:
			targetposition = 0x03;
			LCD_DisplayString(19, " ");
			LCD_DisplayString(39, " ");
			LCD_DisplayString(59, "@");
			LCD_DisplayString(79, " ");
			break;
		case targetposition4:
			targetposition = 0x04;
			LCD_DisplayString(19, " ");
			LCD_DisplayString(39, " ");
			LCD_DisplayString(59, " ");
			LCD_DisplayString(79, "@");
			break;
		case targetposition5:
			targetposition = 0x03;
			LCD_DisplayString(19, " ");
			LCD_DisplayString(39, " ");
			LCD_DisplayString(59, "@");
			LCD_DisplayString(79, " ");
			break;
		case targetposition6:
			targetposition = 0x02;
			LCD_DisplayString(19, " ");
			LCD_DisplayString(39, "@");
			LCD_DisplayString(59, " ");
			LCD_DisplayString(79, " ");
			break;
		case targetend:
			LCD_DisplayString(19, "@");
			LCD_DisplayString(39, "@");
			LCD_DisplayString(59, "@");
			LCD_DisplayString(79, "@");
			break;
	}
}

enum outputstates {outputinit} outputstate;

void output() {
	switch(outputstate) { //transitions
		case outputinit:

			break;
	}
	switch(outputstate) { //actions
		case outputinit:

			break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	
	DDRC = 0xFF; PORTC = 0x00; //LCD data lines
	DDRD = 0xC0; PORTD = 0x3F; //LCD control lines + input

	dartstate = dartinit;
	targetstate = targetinit;
	outputstate = outputinit;
	TimerSet(1000);
	TimerOn();
	
	LCD_init();
	LCD_ClearScreen();
	LCD_Cursor(0);
	LCD_WriteData(9 + '0');
	LCD_DisplayString(1, "23456789012345678901234567890 2nd row half");
	
	while(1) {
		dart();
		target();
		output();
		while (!TimerFlag);
		TimerFlag = 0;
	}

}
