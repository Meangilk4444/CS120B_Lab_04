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
enum States{START, HASHTAG, RELEASED_HASHTAG, X, RELEASED_X, Y, RELEASED_Y, X_TWO, RELEASED_X_TWO,  RELEASED_HASHTAG_TWO, X_THREE, RELEASED_X_THREE, Y_TWO, RELEASED_Y_TWO, X_FOUR, RELEASED_X_FOUR} state;
unsigned char hash = 0x00;
unsigned char why = 0x00;
unsigned char x = 0x00;
unsigned char lock = 0x00;
void Tick()
{
	lock = PINA & 0xFF;
	x = PINA & 0x0F;
	why = PINA & 0x0F;
	hash = PINA & 0x0F;

	switch(state) {
		
		case START:
			state = HASHTAG;
			PORTB = 0x00;
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
				state = X;
			}
			else
			{
				state = RELEASED_HASHTAG;
			}
			
			break;						

		case X:
			if(x  == 0x01)
			{
				state = RELEASED_X;
			}
			else if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else
			{
				state = X;
			}	

			break;

		case RELEASED_X:
			if(x == 0x00)
			{
				state = Y;
			}
			else if(x == 0x01)
			{
				state = RELEASED_X;
			}
			else
			{
				state = HASHTAG;
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

			if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else if(hash == 0x00)
			{
				state = X_TWO;
			}
			else
			{
				state = RELEASED_Y;
			}

			break;

		case X_TWO:

			if(x == 0x01)
			{
				state = RELEASED_X_TWO;
				PORTB = 0x01;
			}
			else if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else
			{
				state = X_TWO;
			}

			break;


		case RELEASED_X_TWO:
			PORTB = 0x01;		
			state = RELEASED_HASHTAG_TWO;
			break;
 	
	
		case RELEASED_HASHTAG_TWO:
			
			if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else if(hash == 0x04)
			{
				state = RELEASED_HASHTAG_TWO;
			}
			else if(hash == 0x00)
			{
				state = X_THREE;
			}
			else
			{
				state = RELEASED_HASHTAG_TWO;
			}
			break;

		case X_THREE:
			
			if(x == 0x01)
			{
				state = Y_TWO;
			}
			else if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else
			{
				state = X_THREE;
			}
			break;
		
		case RELEASED_X_THREE:

			if(x == 0x00)
			{
				state = Y_TWO;
			}
			else if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else
			{
				state = RELEASED_X_THREE;
			}

			break;

		case Y_TWO:
			
			if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else if(why == 0x02)
			{
				state = RELEASED_Y_TWO;
			}
			else
			{
				state = Y_TWO;
			}
			break;

		case RELEASED_Y_TWO:

			if(why == 0x00)
			{
				state = X_FOUR;
			}
			else if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else
			{
				state = RELEASED_Y_TWO;
			}

			break;

		case X_FOUR:

			if(x == 0x01)
			{
				state = RELEASED_X_FOUR;
			}
			else if(lock == 0x80)
			{
				state = HASHTAG;
			}
			else
			{
				state = X_FOUR;
			}

			break;

		case RELEASED_X_FOUR:
			state = HASHTAG;
			break;

		default:
			state = START;
			break;
	}

	switch(state){

		case HASHTAG:
			PORTB = 0x00;
			break;

		case RELEASED_X_TWO:
			PORTB = 0x01;
			break;

		case RELEASED_X_FOUR:
			PORTB = 0x00;
			break;
	}
}
				
		
int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF;
//DDRC = 0xFF; PORTC = 0x00;
DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    state = START;
 
    while (1) {
		Tick();
    }
    return 1;
}
