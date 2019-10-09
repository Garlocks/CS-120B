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
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tempa = 0x00;
	unsigned char tempb = 0x00;
	unsigned char tempc = 0x00;
	unsigned char num1a = 0x00;
	unsigned char num1b = 0x00;

	
	while(1) {
		
		tempa = PINA;
		tempb = PINB;

		while (tempa != 0x00) {
			if (tempa & 0x01) {
				num1a = num1a + 1;
			}
			tempa = tempa >> 1;
		}
		while (tempb != 0x00) {
			if (tempb & 0x01) {
				num1b = num1b + 1;
			}
			tempb = tempb >> 1;
		}
		
		tempc = tempa + tempb;

		PORTC = tempc;
		
	}
	
	return 0;
}