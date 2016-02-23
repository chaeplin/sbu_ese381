/*
NAME:	hardware_pwm_test
AUTHOR:	B. Jarnagin
REV:	- >020160223
DESCRIPTION:	Creates a 500 Hz 22% rectangle wave on OC0 pin
TARGET:	ATMEGA128 @ 16 MHz
USES:	TC0, pin OC0
*/

#include <iom128.h>         //Atmega128 definitions
#include <intrinsics.h>     //Intrinsic functions
#include <avr_macros.h>     //Useful macros

//16 MHz =
// COUNTER IN CLEAR ON COMPARE MODE WITH CLK/64 
const byte COUNTER_MODE = (1 << CTC0) | (1 << CS01) | (1 << CS00) (1 << WGM01);

void main(){
	// SETUP PIN OC0 FOR OUTPUT
	DDRB = (1 << OC0);
	
	// CLEAR COUNTER VALUE
	TCNT0 = 0;
	
	// 62 COUNTS PER 1/2 PERIOD
	// FREQ OUT 22 kHz = (16 MHz)/(2*64*(1+62))
	OCR0 = 62;
	
	// SETUP COUNTER PRESCALER/MODE
	TCCR0 = COUNTER_MODE;

	// ENTER CAPTURE LOOP, DONE WITH SETUP
	while(1);
}