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
enum States{START, HASHTAG, RELEASED_HASHTAG, Y, RELEASED_Y} state;
unsigned char hash = 0x00;
unsigned char why = 0x00;
unsigned char lock = 0x00;
void Tick()
{
	lock = PINA & 0xFF;
	hash = PINA & 0x0F;
	why = PINA & 0x0F;

	switch(state) {
		
		case START:
			state = HASHTAG;
			break;

		case HASHTAG:
			if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else if(hash == 0x04)
			{
				state = RELEASED_HASHTAG;
			}
			else
			{
				state = HASHTAG;
			}
			
			break;

		case RELEASED_HASHTAG:
			
			if(lock == 0x80) //go to beginning
			{
				state = HASHTAG;
			}
			else if(hash == 0x04) //still hasnt been released
			{
				state = RELEASED_HASHTAG;
			}
			else if(hash == 0x00)
			{
				state = Y;
			}
			else
			{
				state = Y;
			}
			
			break;						

		case Y:
			if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else if(why == 0x02)
			{
				state = RELEASED_Y;
			}
			else
			{
				state = Y;
			}

			break;

		case RELEASED_Y:

			if(why == 0x02)
			{
				state = RELEASED_Y;
			}
			if(lock == 0x80)
			{
				state = HASHTAG;
			}
			break;	

		default:
			state = START;
			break;
	}

	switch(state){

		case HASHTAG:
			PORTB = 0x00;
			PORTC = 0x00;
			break;

		case RELEASED_HASHTAG:
			PORTC = 0x01;
			break;

		case Y:
			PORTC = 0x02;
		//	PORTB = 0x01;
			break;

		case RELEASED_Y:
			PORTC = 0x03;
			PORTB = 0x01;
			break;
	}
}
				
		
int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF;
DDRC = 0xFF; PORTC = 0x00;
DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    state = START;
 
    while (1) {
		Tick();
    }
    return 1;
}
