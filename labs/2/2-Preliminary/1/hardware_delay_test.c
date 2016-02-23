/*
NAME:	hardware_delay_test
AUTHOR:	B. Jarnagin
REV:	- >020160223
DESCRIPTION:	Creates a 1 ms wide pulse on OC0 pin
				Interrupt controlled
TARGET:	ATMEGA128 @ 16 MHz
USES:	TC0, pin OC0
*/

#include <iom128.h>         //Atmega128 definitions
#include <intrinsics.h>     //Intrinsic functions
#include <avr_macros.h>     //Useful macros

// COUNTER IN NORMAL MODE WITH CLK/64
const byte COUNTER_MODE = (1 << CS01) | (1 << CS00);

// COUNTER WILL RUN FOR 1 ms = 64*(16E-6 sec)*(255-5)
const byte DELAY_POSITION = 5;

void main(){
	// SETUP PIN OC0 FOR OUTPUT
	DDRB = (1 << OC0);
	
	// SETUP INTERRUPT FOR OVERFLOW
	TIMSK = (1 << TOIE0);
	
	// LOAD VALUE FOR COUNTER
	TCNT0 = DELAY_POSITION;
	
	// BEGIN PULSE
	SETBIT(PORTB, OC0);
	
	// SETUP COUNTER PRESCALER/MODE
	TCCR0 = COUNTER_MODE;
	
	__enable_interrupt();
	
	// ENTER CAPTURE LOOP, DONE WITH SETUP
	while(1);
}

#PRAGMA vector=TOV0_vect
__interrupt void TOV0_ISR(void){
	// DISABLE COUNTER
	TCCR0 = 0;
	
	// END PULSE
	// CLEARBIT(PORTB, OC0);
}