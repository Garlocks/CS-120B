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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char temp = 0x00;
	unsigned char output = 0x00;
	
	while(1) {
		
		temp = PINA;
		output = 0x00;
		if (temp == 0x01 || temp == 0x02) {
			output = 0x60; //low fuel
		}
		if (temp == 0x03 || temp == 0x04) {
			output = 0x70; //low fuel
		}
		if (temp == 0x05 || temp == 0x06) {
			output = 0x38;
		}
		if (temp == 0x07 || temp == 0x08 || temp == 0x09) {
			output = 0x3C;
		}
		if (temp == 0x0A || temp == 0x0B || temp == 0x0C) {
			output = 0x3E;
		}
		if (temp == 0x0D || temp == 0x0E || temp == 0x0F) {
			output = 0x3F;
		}
		
		PORTC = output;
		
		
		
	}
	
	return 0;
}
