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

unsigned char tmp = 0x03; 

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

enum States {Start, LightB0, LightB1, LightB2, Pressed, Pause, Pressed2}state;
unsigned char score = 0x05;
unsigned char bool = 0x00;

void Tick()
{
switch(state){ //transitions
	case Start:
		state = LightB0;
		break;
	case LightB0:
		if((~PINA & 0x01) == 0x01)
		{
			state = Pressed;   break;
		}
		else
		{
			state = LightB1;  break;
		}
	case LightB1:
		if((~PINA & 0x01) == 0x01)
		{
			state = Pressed;   break;
		}
		else
		{	
			state = LightB2;  break;
		}
	case LightB2:
		if((~PINA & 0x01) == 0x01)
		{
			state = Pressed;   break;
		}
		else
		{
			state = LightB0;  break;
		}
	case Pressed2:
		state = Pause; break;
		
	case Pressed:
		if((~PINA & 0x01) == 0x00)
		{
			state = Pressed2;   break;
		}
		else
		{
			state = Pressed;  break;
		}

	case Pause:
		if((~PINA & 0x01) == 0x01)
		{
			if(tmp == 0x00)
			{	
				state = LightB0;  break;
			}
			else if(tmp == 0x01)
			{	
				state = LightB0;  break;
			}
			else if(tmp == 0x02)
			{	
				state = LightB0;  break;
			}
		}
		else
		{
			state = Pause;  break;
		}
}
	
	switch(state){ //actions
		case Start:
			PORTB = 0x00;
			break;
		case LightB0:
			PORTB = 0x01;
			tmp = 0x00;
			break;
		case LightB1:
			PORTB = 0x02;
			tmp = 0x01;
			break;
		case LightB2:
			PORTB = 0x04;
			tmp = 0x02;
			break;
		case Pressed2:
				if(tmp == 0x00)
				{	
					if (score > 0 ) {
						score = score - 1;
					}
					LCD_ClearScreen();
					LCD_WriteData(score + '0');
					//PORTB = 0x01;  break;
				}
				else if(tmp == 0x01)
				{	
					if (score < 9 ) {
						score = score + 1;
					}
					LCD_ClearScreen();
					LCD_WriteData(score + '0');
					if (score >= 9) {
						LCD_ClearScreen();
						LCD_DisplayString(1, "Victory");
					}
					//PORTB = 0x02;  break;
				}
				else if(tmp == 0x02)
				{	
					if (score > 0 ) {
						score = score - 1;
					}
					LCD_ClearScreen();
					LCD_WriteData(score + '0');
					//PORTB = 0x04;  break;
				}
  			break;
		case Pause:
			if((~PINA & 0x01) == 0x01)
			{
				break;
			}
			else
			{
				if(tmp == 0x00)
				{	
					PORTB = 0x01;  break;
				}
				else if(tmp == 0x01)
				{	
					PORTB = 0x02;  break;
				}
				else if(tmp == 0x02)
				{	
					PORTB = 0x04;  break;
				}
			}
			case Pressed:
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
	DDRD = 0xFF; PORTD = 0x00; //LCD control lines

	state = Start;
	TimerSet(100);
	TimerOn();
	
	LCD_init();
	LCD_WriteData(score + '0');
	
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}

}

