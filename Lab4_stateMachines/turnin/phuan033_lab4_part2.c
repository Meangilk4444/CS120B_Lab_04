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
enum States{START, INIT, INCREASE, DECREASE, RESET} state;
unsigned char button0;
unsigned char button1;
void Tick()
{
	button0 = PINA & 0x01;
	button1 = PINA & 0x02;

	switch(state){
		case START:
			
			state = INIT;
			break;
		
		case INIT:
			
			PORTC = 0x07;

			if(button0 && !button1)
			{
				state = INCREASE;
				
			}
			else if(!button0 && button1)
			{
				state = DECREASE;
				
			}
			else if(button0 && button1)
			{
				state = RESET;
				
			}
			else
			{
				state = INIT;
				
			}

			break;

		case INCREASE:
			
			if(PORTC < 9)
			{
				PORTC = PORTC + 1;
			
			}
			
                        if(button0 && !button1)
                        {                                                                                                                               state = INCREASE;
			}
			else if(!button0 && button1)
			{
				state = DECREASE;
			}
			else if(button0 && button1)
			{
				state = RESET;
			}
			else
			{
				break;
			}	
			
			break;

		case DECREASE://	PORTB = 0x00;
			if(PORTC > 0)
			{	
				PORTC = PORTC - 1;
			}	

                        if(button0 && !button1)
                        {                                                                                                                               state = INCREASE;
                        }
                        else if(!button0 && button1)
                        {
                                state = DECREASE;
                        }
                        else if(button0 && button1)
                        {
                                state = RESET;
                        }
                        else
                        {
                                break;
                        }
			
			break;

		case RESET:
			
			PORTC = 0x00;


                        if(button0 && !button1)
                        {                                                                                                                               state = INCREASE;
                        }
                        else if(!button0 && button1)
                        {
                                state = DECREASE;
                        }
                        else if(button0 && button1)
                        {
                                state = RESET;
                        }
                        else
                        {
                                break;
                        }
			
			break;

		default:
			state = START;
			break;
	}

}
int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    state = START;
    PORTC = 0x00;
    while (1) {
		Tick();
    }
    return 1;
}
