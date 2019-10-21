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


enum States {BEGIN, INIT, OFF, WAIT1, ON, WAIT2}state;
void Tick();
int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
	state = BEGIN;
	while(1) {
		Tick();
	}
}

void Tick() {
	switch(state) { 
		case BEGIN:
		PORTB = 0x01;
		state = INIT;
		break;
		
		case INIT:
		PORTB = 0x01;
		if(PINA == 0x01) {
			state = OFF; break;
		} else {
			state = INIT; break;
		}break;
		
		case OFF:
		PORTB = 0x02;
		if(PINA == 0x00) {
			state = WAIT1; break;
		} else {
			state = OFF; break;
		}break;
		
		case WAIT1:
		if(PINA == 0x01) {
			state = ON; break;
		} else {
			state = WAIT1; break;
		}break;
		
		case ON:
		PORTB = 0x01;
		if(PINA == 0x00) {
			state = WAIT2; break;
		} else {
			state = ON; break;
		}break;
		
		case WAIT2:
		if(PINA == 0x01) {
			state = OFF; break;
		} else {
			state = WAIT2; break;
		}break;
		
		default:
		break;
	}
	
	switch(state) { 
		case BEGIN:
		break;
		
		case INIT:
		PORTB = 0x01;
		break;
		
		case OFF:
		PORTB = 0x02;
		break;
		
		case WAIT1:
		break;
		
		case ON:
		PORTB = 0x01;
		break;
		
		case WAIT2:
		break;
		
		default:
		break;
	}
}
