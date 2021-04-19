/*	Author: dmirz001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { init, On_0, Wait_0, On_1, Wait_1 } state;

void TickFct(){
	switch(state){
		case init:
		state = On_0;
		break;

		case On_0:
		if((PINA & 0x01) == 0x01){
			state = Wait_0;
		}
		else if ((PINA & 0x01) != 0x01){
			state = On_0;
		}
		break;

		case Wait_0:
                state = On_1;
                break;

		case On_1:
                if((PINA & 0x01) == 0x01){
                        state = On_1;
                }
                else if ((PINA & 0x01) != 0x01){
                        state = Wait_1;
                }
                break;

		case Wait_1:
                state = On_0;
                break;

		default:
		state = On_0;
		break;
	}

	switch(state){
		case init:
		break;

		case On_0:
		PORTB = 0x01;
		break;

		case Wait_0:
		break;

		case On_1:
		PORTB = 0x02;
		break;

		case Wait_1:
		break;

		default:
		PORTB = 0x01;
		break;
	}

}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	while (1){
		TickFct();
	}
	return 1;
}
