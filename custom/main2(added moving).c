/*	Author: scheu010
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template 
 *	or example code, is my own original work.
 */
#define F_CPU 8000000UL
#include <avr/io.h>
#include "io.h"
#include <util/delay.h>

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

unsigned char dartposition = 0x02;
unsigned char ammoleft = 0x06;
unsigned char score = 0x00;
unsigned char targetposition = 0x13;
unsigned char bool = 0x00;
unsigned char playerposition = 0x01;


		unsigned char s1 = 0x01;
		unsigned char s2 = 0x02;
		unsigned char s3 = 0x04;
		unsigned char s4 = 0x08;
		unsigned char s5 = 0x10;
		unsigned char s6 = 0x20;
		unsigned char s7 = 0x40;

enum dartstates {dartinit, dartwait, dartshoot, dartshoot2, dartshoot3, dartshoot4, dartend} dartstate;
enum targetstates {targetinit, targetposition1, targetposition2, 
targetposition3, targetposition4, targetposition5, targetposition6, targetend} targetstate;
enum playerstates {playerinit, playerwait} playerstate;
enum outputstates {outputinit} outputstate;

void dart() {
	switch(dartstate) { //transitions
		case dartinit:
			dartstate = dartwait;
			break;
		case dartwait:
			if ((~PINA & 0x04) == 0x04) {
				if (playerposition == 01) {
					dartstate = dartshoot;
					if (targetstate == targetposition1) {
						bool = 0x01;
					}
				} else if (playerposition == 21) {
					dartstate = dartshoot2;
					if (targetstate == targetposition2 || targetposition6) {
						bool = 0x01;
					}
				} else if (playerposition == 41) {
					dartstate = dartshoot3;
					if (targetstate == targetposition3 || targetposition5) {
						bool = 0x01;
					}
				} else if (playerposition == 61) {
					if (targetstate == targetposition4) {
						bool = 0x01;
					} 
					dartstate = dartshoot4;
				}
			} else if ((~PINA & 0x04) == 0x00){
				dartstate = dartwait;
			}
			break;
		case dartshoot:
			if (dartposition < 0x13) {
				dartstate = dartstate;
				dartposition = dartposition + 1;
			} else if (dartposition >= 0x13) {
				
				if (bool == 0x01) {
					bool = 0x00;
					score = score + 1;
				}
				
				//score if statements
				if (score == 6) {
					PORTB = ~(s2|s3|s4|s5|s6|s7);
				}
				if (score == 5) {
					PORTB = ~(s2|s3|s4|s5|s6);
				}
				if (score == 4) {
					PORTB = ~(s1|s3|s4|s5);
				}
				if (score == 3) {
					PORTB = ~(s1|s2|s4|s5|s6);
				}
				if (score == 2) {
					PORTB = ~(s1|s2|s4|s6|s7);
				}
				if (score == 1) {
					PORTB = ~(s1|s5);
				}
				if (score == 0) {
					PORTB = ~(s1|s2|s3|s5|s6|s7);
				}
				//score if statements
				
				
				if (ammoleft > 0) {
					ammoleft = ammoleft - 1;
				}
				if (ammoleft <= 0) {
					PORTD = 0x00;
					dartstate = dartend;
				} else {
					dartstate = dartwait;
				}
			}
			break;
		case dartshoot2:
			if (dartposition < 39) {
				dartstate = dartstate;
				dartposition = dartposition + 1;
			} else if (dartposition >= 39) {
				
				if (bool == 0x01) {
					bool = 0x00;
					score = score + 1;
				}
				
				//score if statements
				if (score == 6) {
					PORTB = ~(s2|s3|s4|s5|s6|s7);
				}
				if (score == 5) {
					PORTB = ~(s2|s3|s4|s5|s6);
				}
				if (score == 4) {
					PORTB = ~(s1|s3|s4|s5);
				}
				if (score == 3) {
					PORTB = ~(s1|s2|s4|s5|s6);
				}
				if (score == 2) {
					PORTB = ~(s1|s2|s4|s6|s7);
				}
				if (score == 1) {
					PORTB = ~(s1|s5);
				}
				if (score == 0) {
					PORTB = ~(s1|s2|s3|s5|s6|s7);
				}
				//score if statements
				
				
				if (ammoleft > 0) {
					ammoleft = ammoleft - 1;
				}
				if (ammoleft <= 0) {
					PORTD = 0x00;
					dartstate = dartend;
				} else {
					dartstate = dartwait;
				}
			}
			break;
		case dartshoot3:
			if (dartposition < 59) {
				dartstate = dartstate;
				dartposition = dartposition + 1;
			} else if (dartposition >= 59) {
				
				if (bool == 0x01) {
					bool = 0x00;
					score = score + 1;
				}
				
				//score if statements
				if (score == 6) {
					PORTB = ~(s2|s3|s4|s5|s6|s7);
				}
				if (score == 5) {
					PORTB = ~(s2|s3|s4|s5|s6);
				}
				if (score == 4) {
					PORTB = ~(s1|s3|s4|s5);
				}
				if (score == 3) {
					PORTB = ~(s1|s2|s4|s5|s6);
				}
				if (score == 2) {
					PORTB = ~(s1|s2|s4|s6|s7);
				}
				if (score == 1) {
					PORTB = ~(s1|s5);
				}
				if (score == 0) {
					PORTB = ~(s1|s2|s3|s5|s6|s7);
				}
				//score if statements
				
				
				if (ammoleft > 0) {
					ammoleft = ammoleft - 1;
				}
				if (ammoleft <= 0) {
					PORTD = 0x00;
					dartstate = dartend;
				} else {
					dartstate = dartwait;
				}
			}
			break;
		case dartshoot4:
			if (dartposition < 79) {
				dartstate = dartstate;
				dartposition = dartposition + 1;
			} else if (dartposition >= 79) {
				
				if (bool == 0x01) {
					bool = 0x00;
					score = score + 1;
				}
				
				//score if statements
				if (score == 6) {
					PORTB = ~(s2|s3|s4|s5|s6|s7);
				}
				if (score == 5) {
					PORTB = ~(s2|s3|s4|s5|s6);
				}
				if (score == 4) {
					PORTB = ~(s1|s3|s4|s5);
				}
				if (score == 3) {
					PORTB = ~(s1|s2|s4|s5|s6);
				}
				if (score == 2) {
					PORTB = ~(s1|s2|s4|s6|s7);
				}
				if (score == 1) {
					PORTB = ~(s1|s5);
				}
				if (score == 0) {
					PORTB = ~(s1|s2|s3|s5|s6|s7);
				}
				//score if statements
				
				
				if (ammoleft > 0) {
					ammoleft = ammoleft - 1;
				}
				if (ammoleft <= 0) {
					PORTD = 0x00;
					dartstate = dartend;
				} else {
					dartstate = dartwait;
				}
			}
			break;
		case dartend:
			break;
	}
	switch(dartstate) { //actions
		case dartinit:
			dartposition = 0x02;
			ammoleft = 0x06;
			PORTB = (s1|s2|s3|s4|s5|s6|s7);
			break;
		case dartwait:
			dartposition = playerposition + 1;
			LCD_DisplayString(dartposition, ">");
			_delay_ms(100);
			
			if (ammoleft == 6) {
				PORTD = 0x3F;
			}
			if (ammoleft == 5) {
				PORTD = 0x1F;
			}
			if (ammoleft == 4) {
				PORTD = 0x0F;
			}
			if (ammoleft == 3) {
				PORTD = 0x07;
			}
			if (ammoleft == 2) {
				PORTD = 0x03;
			}
			if (ammoleft == 1) {
				PORTD = 0x01;
			}
			if (ammoleft == 0) {
				PORTD = 0x00;
			} 
			
			break;
		case dartshoot:
			LCD_DisplayString(dartposition, ">");
			_delay_ms(100);
			break;
		case dartshoot2:
			LCD_DisplayString(dartposition, ">");
			_delay_ms(100);
			break;
		case dartshoot3:
			LCD_DisplayString(dartposition, ">");
			_delay_ms(100);
			break;
		case dartshoot4:
			LCD_DisplayString(dartposition, ">");
			_delay_ms(100);
			break;
		case dartend:
			LCD_DisplayString(1, "GAME OVER, RAN OUT  OF AMMO! SCORE = ");
			_delay_ms(300);
			LCD_Cursor(38);
			LCD_WriteData(score + '0');
			_delay_ms(300);
			score = score;
			break;
	}
}


void target() {
	switch(targetstate) { //transitions
		case targetinit:
			targetstate = targetposition1;
			break;
		case targetposition1:
			if (dartstate == dartend) {
				targetstate = targetend;
			}
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
			_delay_ms(100);
			
			//LCD_DisplayString(39, " ");
			//LCD_DisplayString(59, " ");
			//LCD_DisplayString(79, " ");
			break;
		case targetposition2:
			targetposition = 0x02;
			//LCD_DisplayString(19, " ");
			LCD_DisplayString(39, "@");
			_delay_ms(100);
			//LCD_DisplayString(59, " ");
			//LCD_DisplayString(79, " ");
			break;
		case targetposition3:
			targetposition = 0x03;
			//LCD_DisplayString(19, " ");
			//LCD_DisplayString(39, " ");
			LCD_DisplayString(59, "@");
			_delay_ms(100);
			//LCD_DisplayString(79, " ");
			break;
		case targetposition4:
			targetposition = 0x04;
			//LCD_DisplayString(19, " ");
			//LCD_DisplayString(39, " ");
			//LCD_DisplayString(59, " ");
			LCD_DisplayString(79, "@");
			_delay_ms(100);
			break;
		case targetposition5:
			targetposition = 0x03;
			//LCD_DisplayString(19, " ");
			//LCD_DisplayString(39, " ");
			LCD_DisplayString(59, "@");
			_delay_ms(100);
			//CD_DisplayString(79, " ");
			break;
		case targetposition6:
			targetposition = 0x02;
			//LCD_DisplayString(19, " ");
			LCD_DisplayString(39, "@");
			_delay_ms(100);
			//LCD_DisplayString(59, " ");
			//LCD_DisplayString(79, " ");
			break;
		case targetend:
			LCD_DisplayString(19, "@");
			LCD_DisplayString(39, "@");
			LCD_DisplayString(59, "@");
			LCD_DisplayString(79, "@");
			break;
	}
}

void player() {
	switch(playerstate) { //transitions
		case playerinit:
			playerstate = playerwait;
			break;
		case playerwait:
			playerstate = playerwait;
			break;
	}
	switch(playerstate) { //actions
		case playerinit:
		playerposition = 0x01;
			LCD_StayString(playerposition, "D");
			break;
		case playerwait:
			if ((~PINA & 0x01) == 0x01) {
				if (playerposition == 01) {
					playerposition = 21;
				} else if (playerposition == 21) {
					playerposition = 41;
				} else if (playerposition == 41) {
					playerposition = 61;
				} else if (playerposition == 61) {
					playerposition = 01;
				}
			}
			if ((~PINA & 0x02) == 0x02) {
				if (playerposition == 01) {
					playerposition = 61;
				} else if (playerposition == 21) {
					playerposition = 01;
				} else if (playerposition == 41) {
					playerposition = 21;
				} else if (playerposition == 61) {
					playerposition = 41;
				}
			}
			_delay_ms(10);
			LCD_StayString(playerposition, "D");
			break;
	}
}

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
	//DDRD = 0xC0; PORTD = 0x3F; //LCD control lines + input
DDRD = 0xFF; PORTD = 0x00;
	
	dartstate = dartinit;
	targetstate = targetinit;
	outputstate = outputinit;
	TimerSet(80);
	TimerOn();
	
	LCD_init();
	LCD_ClearScreen();
	LCD_Cursor(0);
	LCD_WriteData(9 + '0');
	LCD_DisplayString(1, "23456789012345678901234567890 2nd row half");
	
	while(1) {
		player();
		_delay_ms(10);
		dart();
		_delay_ms(10);
		target();
		_delay_ms(10);
		output();
		
		
		while (!TimerFlag);
		TimerFlag = 0;
	}

}
