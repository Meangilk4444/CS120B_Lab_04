/*	Author: phuan033
 *  Partner(s) Name: karen Gonzalez
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
enum States{START, ON, OFF_PRESSED, OFF, ON_PRESSED} state;
void Tick()
{
	switch(state){
		case START:
			
			state = ON;
			break;
		
		case ON:
			
			if(PINA == 0x01)
			{
				state = OFF_PRESSED;
				break;
			}
			else
			{
				state = ON;
				break;
			}

			break;

		case OFF_PRESSED:
			
			if(PINA == 0x00)
			{
				state = OFF;
				break;
			}
			else
			{
				state = OFF_PRESSED;
				break;
			}
			
			break;

		case OFF:
		//	PORTB = 0x00;
			if(PINA == 0x01)
			{	
				state = ON_PRESSED;
				break;
			}
			else
			{
				state = OFF; 	
				break;
			}
			
			break;

		case ON_PRESSED:
			
			if(PINA == 0x00)
			{
				state = ON;
				break;
			}
			else
			{
				state = ON_PRESSED; 
				break;
			}
			
			break;

		default:
			state = ON;
			break;
	}

	switch(state){
		case START:
			break;

		case ON:
			PORTB = 0x01;
			break;

		case OFF_PRESSED:
			PORTB = 0x02;
			break;

		case OFF:
			PORTB = 0x02;
			break;

		case ON_PRESSED:
			PORTB = 0x01;
			break;

		default:
			PORTB = 0x01;
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    state = START;
    PORTB = 0x01;
    while (1) {
		Tick();
    }
    return 1;
}
