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
		if (temp == 0x01 || temp == 0x02 || temp == 0x31 || temp == 0x32) {
			output = 0x60; //low fuel
		}
		if (temp == 0x03 || temp == 0x04 || temp == 0x33 || temp == 0x34) {
			output = 0x70; //low fuel
		}
		if (temp == 0x05 || temp == 0x06 || temp == 0x35 || temp == 0x36) {
			output = 0x38;
		}
		if (temp == 0x07 || temp == 0x08 || temp == 0x09 || temp == 0x37 || temp == 0x38 || temp == 0x39) {
			output = 0x3C;
		}
		if (temp == 0x0A || temp == 0x0B || temp == 0x0C || temp == 0x3A || temp == 0x3B || temp == 0x3C) {
			output = 0x3E;
		}
		if (temp == 0x0D || temp == 0x0E || temp == 0x0F || temp == 0x3D || temp == 0x3E || temp == 0x3F) {
			output = 0x3F;
		}
		if ((temp & 0x30) == 0x30) {
			output =  (output + 0x80);
		}
		
		PORTC = output;
		
		
		
	}
	
	return 0;
}
