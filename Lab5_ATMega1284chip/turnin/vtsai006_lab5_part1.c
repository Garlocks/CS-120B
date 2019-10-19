/*	Author: vtsai006
 * 	Partner(s) Name: Steve C
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
   DDRA = 0x00; PORTA = 0xFF;
   DDRC = 0xFF; PORTC = 0x00; 
				
   unsigned char fuelLevel = 0x00;
   unsigned char lightSensor = 0x00;
	
    while(1)
    {
		fuelLevel = ~PINA;

                if((fuelLevel & 0x00) == 0x00)
                {
                        lightSensor = 0x40;
                }
                if((fuelLevel & 0x01) == 0x01)
                {
                        lightSensor = 0x60;
                }
                if((fuelLevel & 0x02) == 0x02)
                {
                        lightSensor = 0x60;
                }
                if((fuelLevel & 0x03) == 0x03)
                {
                        lightSensor = 0x70;
                }
                if((fuelLevel & 0x04) == 0x04)
                {
                        lightSensor = 0x70;
                }	
		if((fuelLevel & 0x05) == 0x05)
		{
			lightSensor = 0x38;
		}	
		if((fuelLevel & 0x06) == 0x06)
		{
			lightSensor = 0x38;
		}	
		if((fuelLevel & 0x07) == 0x07)
		{
			lightSensor = 0x3C;
		}	
		if((fuelLevel & 0x08) == 0x08)
		{
			lightSensor = 0x3C;
		}
		if((fuelLevel & 0x09) == 0x09)
		{
			lightSensor = 0x3C;
		}	
		if((fuelLevel & 0x0A) == 0x0A)
		{
			lightSensor = 0x3E;
		}	
		if((fuelLevel & 0x0B) == 0x0B)
		{
			lightSensor = 0x3E;
		}	
		if((fuelLevel & 0x0C) == 0x0C)
		{
			lightSensor = 0x3E;
		}	
		if((fuelLevel & 0x0D) == 0x0D)
		{
			lightSensor = 0x3F;
		}			
		if((fuelLevel & 0x0E) == 0x0E)
		{
			lightSensor = 0x3F;
		}	
		if((fuelLevel & 0x0F) == 0x0F)
		{
			lightSensor = 0x3F;
		}
		PORTC = lightSensor ;
		lightSensor = 0x00;
		fuelLevel = 0x00;	
    }

return 0;
}

