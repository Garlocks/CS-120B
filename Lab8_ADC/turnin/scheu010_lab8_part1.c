/*	Author: scheu010
 *  Partner(s) Name: vivian
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

void ADC_init() {
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
	//ADEN: setting this bit enables analog to digital conversion
	//ADSC: setting this bit starts the first conversion
	//ADATE: setting this bit enables auto-triggering. since we are
	// 		 in Free Running Mode, a new conversion will trigger
	//		 whenever the previous conversion completes.
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs
	ADC_init();

    /* Insert your solution below */
    unsigned short myshort = ADC; //ADC stores 10 bits so max is 0x03FF
    unsigned char char1 = (char)myshort;
    unsigned char char2 = (char)(myshort>>8);
    
    while (1) {
		myshort = ADC;
		char1 = (char)myshort;
		char2 = (char)(myshort>>8);
		PORTB = char1;
		PORTD = char2;
    }
    return 1;
}
