/*	Author: scheu010
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

enum States {BEGIN, INIT, ADD, MINUS, WAIT, RESET}state;
void Tick();

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x07;
	state = BEGIN;
	while(1) {
		Tick();
	}
}

void Tick(){
	switch(state){ 
		case BEGIN: {
			PORTC = 0x07;
			state = INIT;
			break;
		}
		
		case INIT:
		if (PINA  == 0x01) {
			state = ADD; break;
		} else if(PINA== 0x02) {
			state = MINUS; break;
		} else if(PINA == 0x03) {
			state = RESET; break;
		} else if (PINA == 0x00) {
			state = INIT; break;
		}
		break;
		
		case ADD:
		state = WAIT;
		break;
		
		case MINUS:
		state = WAIT;
		break;
		
		case WAIT:
		if((PINA== 0x01) || (PINA == 0x02)) {
			state = WAIT; break;
		}
		else if((PINA & 0x03) == 0x03) {
			state = RESET; break;
		} else {
			state = INIT; break;
		}
		
		case RESET:
		if((PINA == 0x01) && (PINA == 0x02)) {
			state = RESET; break;
		} else if (PINA == 0x00) {
			state = INIT; break;
		}
		
		default:
		break;
	}
	switch(state) { 
		case BEGIN: {
			PORTC = 0x07;
		}
		break;
		
		case INIT:
		break;
		
		case ADD: {
			if(PORTC >= 0x09) {
				PORTC = 0x09; break;
			} else {
				PORTC = PORTC + 0x01; break;
			}
		}
		break;
		
		case MINUS: {
			if(PORTC <= 0x00) {
				PORTC = 0x00; break;
			} else {
				PORTC = PORTC - 0x01; break;
			}
		}
		break;
		
		case WAIT:
		break;
		
		case RESET: {
			PORTC = 0x00; break;
		}
	}
}
