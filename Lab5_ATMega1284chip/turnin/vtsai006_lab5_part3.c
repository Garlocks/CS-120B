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

enum States { Start, Init, S1, S2, S3, Inc, Wait, Wait2, Wait3} State;
unsigned char cnt = 0x01;
void Tick()
{
	switch(State){ // Transitions
		case Start:
			State = Init;
			break;

		case Init:
			if((~PINA & 0x01) == 0x01)
			{
			State = S1;
			break;
			}
			else
			{
			State = Init;
			break;
			}
			
		case S1:
                        if((~PINA & 0x01) == 0x00)
                        {
                        State = Wait;
                        break;
                        }
                        else
                        {
                        State = S1;
                        break;
                        }
			
		case S2:
                        if((~PINA & 0x01) == 0x00)
                        {
                        State = Wait2;
                        break;
                        }
                        else
                        {
                        State = S2;
                        break;
                        }

		case S3:
			if((~PINA & 0x01) == 0x00)
			{
			State = Inc;
			break;
			}
			else
			{
			State = S3;
			break;
			}
		case Inc:
			
			State = Wait3;
			break;
		case Wait:
			if((~PINA & 0x01) == 0x01)
			{
			State = S2;
			break;
			}			
			else
			{
			State = Wait;
			break;
			}
               case Wait2:
                        if((~PINA & 0x01) == 0x01)
                        {
                        State = S3;
                        break;
                        }
                        else
                        {
                        State = Wait2;
                        break;
                        }
               case Wait3:
                        if((~PINA & 0x03) == 0x01)
                        {
                        	if(cnt<0x04)
				{
					State = S3;
					break;
				}
				else
				{		
				State = Init;
				break;
				}
                        }
                        else
                        {
                        State = Wait3;
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

		case S1:
			PORTC = 0x2A;
			break;
                case S2:
                        PORTC = 0x15;
                        break;
                case S3:
			if(cnt<0x04)
			{
				PORTC = cnt;break;
			}
			else 
			{
			PORTC = 0x01; break;
			}
		case Inc:
			if(cnt<0x04)
			{
			cnt++;                        
			PORTC = cnt + 0x01;
			break;
			}
			else
			{
			cnt = 0x00;
			break;
			}
			//cnt = 0x00;
                        			
		case Wait:
			break;
                case Wait2:
                        break;
                case Wait3:
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

