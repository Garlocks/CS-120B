#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
# Test file for Lab3_BitManipulation

enum States {START, INIT, HASHTAG, WAIT, UNLOCK, LOCK, PAUSE}state;
void Tick();

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x02;
	DDRC = 0xFF; PORTC = 0x00;
	state = START;
	while(1) {
		Tick();
	}
}


void Tick() {
	switch(state) { 
		case START: {
			PORTB = 0x00;
			state = INIT;
			break;
		}

		case INIT:
		if(PINA == 0x04) {
			state = HASHTAG; break;
		} else if (PINA == 0x80) {
			state = LOCK; break;
		} else {
			state = INIT; break;
		}

		case HASHTAG: {
			state = WAIT; break;
		}

		case WAIT: {
			if(PINA == 0x02) {
				state = UNLOCK; break;
			} else if((PINA & 0x80) == 0x80) {
				state = LOCK; break;
			} else if((PINA & 0x01) == 0x01) {
				state = INIT; break;
			} else {
				state = WAIT; break;
			}
		}


		case UNLOCK: {
			PORTB = 0x01;
			state = PAUSE; break;
		}

		case PAUSE:
		if((PINA & 0x87) == 0x80) {
			state = INIT; break;
		} else {
			state = PAUSE; break;
		}

		case LOCK:
		PORTB = 0x00;
		if(PINA == 0x00) {
			state = INIT; break;
		} else {
			state = LOCK; break;
		}

		default:
		break;
	}
	switch(state) { 
		case START:
		PORTB = 0x00;
		PORTC = 0x00;
		break;

		case INIT:
		PORTC = 0x01;
		break;

		case HASHTAG:
		PORTC = 0x02;
		break;

		case WAIT:
		PORTC = 0x03;
		break;

		case UNLOCK:
		PORTC = 0x04;
		PORTB = 0x01;
		break;

		case PAUSE:
		PORTC = 0x05;
		break;

		case LOCK:
		PORTC = 0x06;
		PORTB = 0x00;
		break;
	}

}
