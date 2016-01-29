/*
*       title:          sws_alu.c
*       description:    performs AND, OR, XOR or ~ bitwise between PD5-PD3 and
*                       PD2-PD0 based on selection by PD7-PD6. Output to
*                       PB2-PB0 as active low. PB7-PB3 are kept constant high.
*       target:         ATMEGA128
*/

#include <iom128.h>

int main(void){
    //setup input and output pins
      DDRD =      0x00;
      PORTD =     0xFF;
      DDRB =      0xFF;
    
    //define variables
      char op, tempA, tempB;
      
      while(1){
        tempA = PIND;           //tempA = 0bABCDEFGH
        tempB = tempA>>3;       //tempB = 0b000ABCDE
        op = tempB>>3;          //op =    0b000000AB
        
        switch(op){
          case 0:       //AND
            tempA &= tempB;
            break;
            
          case 1:       //OR
            tempA |= tempB;
            break;
          
          case 2:       //XOR
            tempA ^= tempB;
            break;
          
          case 3:       //COMP
            tempA = ~tempA;
            break;
        }
        
        PORTB = ~( tempA & 0x03 );
      }
}