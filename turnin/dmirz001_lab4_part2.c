/*	Author: dmirz001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { init, wait, inc_wait, inc, dec_wait, dec, reset } state;

void TickFct(){
	switch(state){
		case init:
		if(((PINA & 0x01) == 0x01) || ((PINA & 0x02) == 0x02))
		state = wait;
		break;
      
		case wait:
		if((PINA & 0x01) == 0x01){
			state = inc_wait;
		}
		else if ((PINA & 0x02) == 0x02){
			state = dec_wait;
		}
		else if ((PINA & 0x03) == 0x03){
			state = reset;
		}
		else{
			state = wait;
		}
		break;

		case inc_wait:
                state = inc;
                break;

		case dec_wait:
                state = dec;
                break;

		case inc:
                if((PINA & 0x01) == 0x00){
                        state = wait;
                }
                else if((PINA & 0x03) == 0x03){
                     state = reset;
                }
                break;

		case dec:
                if((PINA & 0x02) == 0x00){
                        state = wait;
                }
                else if((PINA & 0x03) == 0x03){
                        state = reset;
                }
                break;
      

      
		case reset:
		if ((PINA & 0x03) == 0x00){
			state = wait;
		}
                break;

		default:
		state = init;
	}

	switch(state){
		case init:
		PORTC = 0x07;
		break;


		case wait:
		break;

		case inc_wait:
		if (PORTC < 0x09){
			B++;
		}
		else{
			PORTC = 0x09;
		}
		break;

		case dec_wait:
		if (PORTC > 0x00){
			PORTC--;
		}
		else{
			PORTC = 0x00;
		}
		break;

		case inc:
		break;

		case dec:
		break;

		case reset:
		PORTC = 0x00;
		break;
		
		default:
		PORTC = 0x07;
		break;
	}

}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTB = 0x00;
	while (1){
		TickFct();
	}
	return 1;
}
