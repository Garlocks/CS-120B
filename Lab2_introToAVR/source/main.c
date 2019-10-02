/*	Author: scheu010
 *  Partner(s) Name: n/a
 *	Lab Section: 023
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
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
					// Initialize output on PORTB to 0x00
	unsigned char temp_input = 0x00;

    /* Insert your solution below */
    while (1) {
		temp_input = PINA;
		PORTB = temp_input;	// Writes port B's 8 pins with the values
							// on port A's 8 pins

    }
    return 1;
}
 
 
