// DELUPPGIFT 4

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "led.h"
#include "timer.h"
#include "switch.h"

uint8_t check_switch(void)
{       
        uint8_t current_state = 0;
        static uint8_t previous_state = 0;
              
        // Read current state of pin D2, act on any change to its' 
        // state and set DBOG flag.
        current_state = (PIND & _BV(PIND2));

        if(current_state == previous_state) 
                return 0;
        
        previous_state = current_state;
        
        return (!current_state);
             
}