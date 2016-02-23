/*
NAME:	hardware_pulse_test
AUTHOR:	B. Jarnagin
REV:	- >020160223
DESCRIPTION:	Creates a 400 us wide pulse on OC0 pin followed by a ~1000 us delay repeat
				Interrupt controlled
TARGET:	ATMEGA128 @ 16 MHz
USES:	TC0, pin OC0
*/

#include <iom128.h>         //Atmega128 definitions
#include <intrinsics.h>     //Intrinsic functions
#include <avr_macros.h>     //Useful macros

// COUNTER IN NORMAL MODE WITH CLK/64 
const byte COUNTER_MODE = (1 << CS01) | (1 << CS00);

// COUNTER WILL RUN FOR 400 us = 64*(16E-6 sec)*(255-100)
const byte DELAY_POSITION = 155;

void main(){
	// SETUP PIN OC0 FOR OUTPUT
	DDRB = (1 << OC0);
	
	// SETUP INTERRUPT FOR OVERFLOW
	TIMSK = (1 << TOIE0);
	
	// LOAD VALUE FOR COUNTER
	TCNT0 = DELAY_POSITION;
	
	// SETUP COUNTER PRESCALER/MODE
	TCCR0 = COUNTER_MODE;
	__enable_interrupt();
	
	// ENTER CAPTURE LOOP, DONE WITH SETUP
	while(1);
}

#PRAGMA vector=TOV0_vect
__interrupt void TOV0_ISR(void){
	//DISABLE COUNTER
	TCCR0 = 0;
	
	// TURN OFF PIN
	// CLEARBIT(PORTB, OC0);
	
	// LOAD VALUE FOR COUNTER
	TCNT0 = DELAY_POSITION;
	
	// DELAY FOR 1000 us = (16E-6) * 16000
	__delay_cycles(16000);
	
	// TURN ON PIN
	SETBIT(PORTB, OC0);
	
	// SETUP COUNTER PRESCALER/MODE
	TCCR0 = COUNTER_MODE;
}