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

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; 
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char temp = 0x00;
	unsigned char outputb = 0x00;
	unsigned char outputc = 0x00;
	
	while(1) {
		
		temp = PINA;
		outputb = 0x00;
		outputc = 0x00;
		
		outputb = (0x0F & temp);
		outputc = (0xF0 & temp);
		
		
		PORTB = outputb;
		PORTC = outputc;
		
		
		
	}
	
	return 0;
}
