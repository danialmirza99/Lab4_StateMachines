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

enum States { init, waitA0, pressA0, waitA1, pressA1 } LA_State;

voidTickFct(){
	switch(state){
		case init:
		state = waitA0;
		break;

		case waitA0:
		if(A0){
			state = pressA0;
		}
		else if (!A0){
			state = waitA0;
		}
		break;

		case PressA0:
                if(A0){
                        state = pressA0;
                }
                else if (!A0){
                        state = waitA1;
                }
                break;

		case waitA1:
                if(A1){
                        state = pressA1;
                }
                else if (!A1){
                        state = waitA1;
                }
                break;

		case PressA1:
                if(A1){
                        state = pressA1;
                }
                else if (!A1){
                        state = waitA0;
                }
                break;
	}

	switch(state){
		case waitA0:
		B = 0;
		cntA0 = 0;
		break;

		case pressA0:
		cntA0++;
		break;

		case waitA1:
		break;

		case pressA1:
		B = cntA0 > 100;
		break;
	}

}

int main(void) {
	B = 0x00;
	while (1){
		TickFct();
	}
	return 1;
}
