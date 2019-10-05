/*	Author: scheu010
 *  Partner(s) Name: n/a
 *	Lab Section: 023
 *	Assignment: Lab #02  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char temp = 0x00;
	
	while(1) {
		
		temp = PINA;
		if (temp == 0x01) {
			PORTB = 0x01;
		} else {
			PORTB = 0x00;
		}
		
	}
	
	return 0;
}

 
 
