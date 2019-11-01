/*	Author: vtsai006
 *  Partner(s) Name: Steve C
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

enum States{Start, Init, Inc, Dec, Wait, Toggle} state;
double freq[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

unsigned char power = 0x00;
double currFreq = 261.63;
unsigned char frqPos = 0x00;

void Tick()
{
    switch(state) // transitions
	{
		case Start:
		{
			state = Init;
			break;
		}
		case Init:
		{
			if((~PINA & 0x07) == 0x01)
			{
				state = Toggle;
				break;
			}
			else if((~PINA & 0x07) == 0x02)
			{
				state = Inc;
				break;
			}
			else if((~PINA & 0x07) == 0x04)
			{
				state = Dec;
				break;
			}
			else
			{
				state = Init;
				break;
			}
		}
		case Toggle: 
		{
			state = Wait;
			break;
		}
		case Inc:
		{
			state = Wait;
			break;
		}
		case Dec:
		{
			state = Wait;
			break;
		}
		case Wait:
		{
			if((~PINA & 0x07) == 0x00)
			{
				state = Init;
				break;
			}
			else
			{
				state = Wait;
				break;
			}
		}
		default:
			break;
	}
	switch(state) // state actions
	{
		case Start:
			power = 0;
			break;
		case Init:
			break;

		case Toggle:
		{		
			if(power == 0)
			{
				PWM_on();

				power = 0x01;
				break;
			}	
			else if (power == 0x01)
			{
			    PWM_off();

				power = 0x00;
				break;
			}
		}
		case Inc:
		{

			if((frqPos + 1) > 0x07)
			{
				frqPos = 0x07;
				break;
			}
			else
			{
				++frqPos;
				break;
			}
		}
		case Dec:
		{

			if((frqPos - 1) < 0x00)
			{
				frqPos = 0x00;
				break;
			}
			else
			{
				--frqPos;
				break;
			}
		}
		case Wait:
		{
			
			currFreq = freq[frqPos];
			set_PWM(currFreq);
			
			break;
		}
		
		default:
		break;
		
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	//PWM_on();
	power = 0;
    state = Start;
    /* Insert your solution below */
    while (1) {
		Tick();
   }
}
Duplicate file upload
You already have a version of this file in Drive. Adding a new version will use more storage.
GOT IT
