// DELUPPGIFT 4

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdbool.h>

#include "led.h"
#include "timer.h"
#include "switch.h"
#include "adc.h"

volatile bool time_to_check_key;

volatile uint8_t ADCValue;
volatile uint8_t centis = 0;

uint8_t current_state = 1;

ISR(ADC_vect)
{		// Store value from ADC Conversion 
		ADCValue = ADCH;
}

ISR(TIMER2_COMPA_vect)
{
		time_to_check_key = true;
		centis++;
		ADCSRA |= _BV(ADSC); // Initialize a ADC conversion	
}

void main (void) 
{
		LED_init();
		ADC_init();
		timer0_init();
		timer2_init();
		sei();

		while (1) {
			//  Poll switch every 10ms and set new state if button 
			//	has been pressed and released
				if(time_to_check_key) {
						time_to_check_key = false;
						if(check_switch()) 
								current_state++;
				}
				execute_state();
		}
}

