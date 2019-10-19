/*	Author: vtsai006
 *  Partner(s) Name: 
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

enum States { Start, Init, Inc, Dec, Reset, Wait} State;
unsigned char cnt = 0x00;
void Tick()
{
	switch(State){ // Transitions
		case Start:
			State = Init;
			break;

		case Init:
			if((~PINA & 0x03) == 0x01)
			{
			State = Inc;
			break;
			}
			else if((~PINA & 0x03) == 0x02)
			{
			State = Dec;
			break;
			}
			else if((~PINA & 0x03) == 0x03)
			{
			State = Reset;
			break;
			}
			else
			{
			State = Init;
			break;
			}
			
		case Inc:
			State = Wait;
			break;
			
		case Dec:
			State = Wait;
			break;
			
		case Reset:
			if((~PINA & 0x03) == 0x00)
			{
			State = Init;
			break;
			}
			else
			{
			State = Reset;
			break;
			}
			
		case Wait:
			if(((~PINA & 0x03) == 0x01)||((~PINA & 0x03) == 0x02))
			{
			State = Wait;
			break;
			}			
			else if((~PINA & 0x03) == 0x03)
			{
			State = Reset;
			break;
			}
			else
			{
			State = Init;
			break;
			}

		default:
			break;
	}

	switch(State){ // State actions
		case Start:
			cnt = 0x00;
			PORTC = 0x00;
			break;

		case Init:
			break;
			
		case Inc:
			if(cnt < 0x09)
			{
			++cnt;
			PORTC = cnt;
			break;
			}
			else
			{
			cnt = 0x09;
			PORTC = cnt;
			break;
			}
						
		case Dec:
			if(cnt <= 0x00)
			{
			cnt = 0x00;
			PORTC = 0x00;
			break;
			}
			else
			{
			--cnt;
			PORTC = cnt;
			break;
			}
			
		case Reset:
			cnt = 0x00;
			PORTC = 0x00;
			break;
			
		case Wait:
			break;
		default:
			break;

	}


}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	State = Start;
//	unsigned char cnt = 0x00;
	while(1)
	{

		Tick();
	}

}

