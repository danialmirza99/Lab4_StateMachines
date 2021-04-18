/*	Author: dmirz001
 *  Partner(s) Name: 
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

enum States { init, waitA0, pressA0, waitA1, pressA1 } state;

void TickFct(){
	switch(state){
		case init:
		state = waitA0;
		break;

		case waitA0:
		if((PINA & 0x01) == 0x01){
			state = pressA0;
		}
		else if ((PINA & 0x01) != 0x01){
			state = waitA0;
		}
		break;

		case PressA0:
                if((PINA & 0x01) == 0x01){
                        state = pressA0;
                }
                else if ((PINA & 0x01) != 0x01){
                        state = waitA1;
                }
                break;

		case waitA1:
                if((PINA & 0x02) == 0x02){
                        state = pressA1;
                }
                else if ((PINA & 0x02) != 0x02){
                        state = waitA1;
                }
                break;

		case PressA1:
                if((PINA & 0x02) == 0x02){
                        state = pressA1;
                }
                else if ((PINA & 0x02) != 0x02){
                        state = waitA0;
                }
                break;
	}

	switch(state){
		case WaitA0:
		PORTB = 0x00;
		cntA0 = 0;
		break;

		case PressA0:
		cntA0++;
		break;

		case WaitA1:
		break;

		case PressA1:
		PORTB = cntA0 > 100;
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
