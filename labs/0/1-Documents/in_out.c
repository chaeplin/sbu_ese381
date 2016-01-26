
/*
 *  inout.c -  A simple program to continuously input a byte from
 *              Switches(PORTD) and output the byte to LEDS(PORTB).
 */

#include <iom128.h> //File with register addresses for ATmega128

int main(void)
{
  char temp;        //byte read. unsigned char by default.

  DDRB = 0xFF;    //PORTB - all bits configured as outputs.
  DDRD = 0x00;    //PORTD - all bits configured as inputs.
  PORTD =0xFF;    //PORTD enable pullups

  while(1) {
    temp = PIND;    //Input byte from SWITCHES.
    temp = ~temp;   //Complement to drive LEDS
    PORTB = temp;   //Output byte to LEDS.
  }
}
