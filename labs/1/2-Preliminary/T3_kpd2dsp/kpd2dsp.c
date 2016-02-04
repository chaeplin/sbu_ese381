

//***************************************************************************
//
// File Name            : kpd2dsp.c
// Title                : Keypad to display
// Date                 : 02/07/10
// Version              : 1.0
// Target MCU           : ATmega128 @  MHz
// Target Hardware      ; 
// Author               : Ken Short
// DESCRIPTION
// Displays the value of a key pressed on a 4 x 4 keypad on a DOG LCD module   
// display. This file is part of a multifile mixed language program
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version 
// 
//
//**************************************************************************

// In compiler options, select the small version of printf to reduce object
// code size.

#include <iom128.h>
#include <intrinsics.h>
#include <avr_macros.h>
#include <stdio.h>

// Declarations for functions in files lcd_ext.c and lcd_dog_iar_driver.asm
#include "lcd.h"    

char keycode;         // Holds keycode

int main( void )
{ 
  // Configure PortD for INT0 interrupt.
  DDRD = 0xFE;                    // INT0 input
  PORTD = 0x01;               // INT0 pullup enabled
  
  // Configure PortC for keypad, initial configuration
  DDRC = 0xF0;        // High nibble outputs, low nibble inputs 
  PORTC = 0x0F;
  
  // Configure PortB for DOG LCD module's SPI interface
  DDRB = 0xFF;             // Set PortB to outputs
  SETBIT (PORTB, 0);       // unassert slave select
    
  MCUCR = 0x30;     // Sleep enabled for power down mode.
  EIMSK = 0x01;     // Enable interrupt INT0. 
                    // Low level by default (EICRA not written)
  init_lcd_dog();               // Call to asm subroutine init_dsp()

  clear_dsp();        // Call to C function clear_dsp()
  update_lcd_dog();   // Call to C function update_lcd_dog()
  
  __enable_interrupt();           //Enable global interrupts.
  
  while (1) {
    clear_dsp();
    printf("Key pressed = %d", keycode); 
    update_lcd_dog();    
  }  
}




