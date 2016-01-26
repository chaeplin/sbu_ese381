/*
 *  sws_level.c -  Simple program to input byte from Switches(PORTD)
 *   count the number of 1s and output the count as a level to LEDS(PORTB).
 */
#include <iom128.h>

int main(void)
{
  unsigned char switches, leds, i;   //unsigned byte variables.

  DDRD = 0x00;    //PORTD - all bits configured as inputs.
  PORTD = 0xFF;   //PORTD - internal pull-ups enabled.
  DDRB = 0xFF;    //PORTB - all bits configured as outputs.

  while(1) {
    switches = PIND;    //Input byte from SWITCHES.
    leds = 0x00;  //Initialize leds to 0
    
    for (i = 1; i < 9; i++, switches >>= 1)
    {
      if (switches & 0x01)
      {
        leds <<= 1;
        leds |= 0x01;
      }
    }
    leds = ~leds;
    PORTB = leds;   //Output byte to LEDS.
  }
}
