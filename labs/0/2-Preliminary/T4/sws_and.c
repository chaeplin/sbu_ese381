/*
*       title:          sws_and.c
*       description:    performs AND bitwise between PD7-PD4 and PD3-PD0. Output
*                       to PB3-PB0 as active low. PB7-PB4 are kept constant high.
*       target:         ATMEGA128
*/

#include <iom128.h>

int main(void){
  //setup input and output pins
    DDRD =      0x00;
    PORTD =     0xFF;   //switches will use internal PUN
    DDRB =      0xFF;
    
  //define variables
    char tempA,tempB;

  //while loop for AND process
    while(1){
      tempA = PIND;           //tempA = 0bABCDEFGH
      tempB = tempA>>4;       //tempB = 0b0000ABCD
      
      //PORTB = ~( PIND & (PIND>>4) )   //Volatile solution
      
      PORTB = ~( tempA & tempB );       //AND values and invert for active low
    }
}