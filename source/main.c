/*	Author: dmirz001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States { init, unlock1, unlock1_wait, unlock2, unlock2_wait, lock_wait } state;

void TickFct(){
	switch(state){
		case init:
		if((PINA & 0x04) == 0x04){
			state = unlock1;
		}
		else{
		   state = init;
		}
		break;
      
		case unlock1:
		if((PINA & 0x04) == 0x04){
			state = unlock1;
		}
		else if((PINA & 0x04) == 0x00){
			state = unlock1_wait;
		}
		else{
		   state = init;
		}
		break;

      case unlock1_wait:
      if((PINA & 0x02) == 0x02){
			state = unlock2;
		}
		else if((PINA & 0x04) == 0x00){
			state = unlock1_wait;
		}
		else{
		   state = init;
		}
      break;

		case unlock2:
		if((PINA & 0x02) == 0x02){
			state = unlock2;
		}
		else if((PINA & 0x02) == 0x00){
			state = unlock2_wait;
		}
		break;

      case unlock2_wait:
		if((PINA & 0x80) == 0x80){
			state = lock_wait;
		}
		else if((PINA & 0x02) == 0x00){
			state = unlock2_wait;
		}
      break;
      
      case lock_wait:
      if((PINA & 0x80) == 0x80){
			state = lock_wait;
		}
		else if((PINA & 0x80) == 0x00){
			state = init;
		}
		break;
			
		default:
		state = init;
	}

	switch(state){
		case init:
		PORTC = 0x00;
		break;


		case unlock1:
		PORTC = 0x00;
		break;

		case unlock1_wait:
		PORTC = 0x00;
		break;

		case unlock2:
		PORTC = 0x01;
		break;

		case unlock2_wait:
		PORTC = 0x01;
		break;
		
		case lock_wait:
		PORTC = 0x01;
		break;
		
		default:
		PORTC = 0x00;
		break;
	}

}


int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	while (1){
		TickFct();
	}
	return 1;
}
