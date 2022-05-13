// DELUPPGIFT 4 

#include <avr/io.h>
#include "led.h"
#include <stdbool.h>

extern volatile uint8_t centis;
extern volatile uint8_t ADCValue;

void LED_init(void) 
{
		// SET PIN D6/"Digital 6" AS OUTPUT
		DDRD |= _BV(PIND6);
		// SET PIN B3/"Digital 11"/Red LED AS INPUT
		DDRB &= ~(_BV(PINB3));
}

uint8_t simple_ramp(void) 
{		
		static int8_t direction = 1;
		static uint8_t pwm_value = 0;
		
		pwm_value += direction;
		// Switch to incremention/decremention of
		// variable alue every time it hits the
		// upper or lower limit
		if(pwm_value >= 255 || pwm_value <= 0)
				direction *= -1;

		return pwm_value;
}

void toggle_LED(void)
{
		// Toggle LED on/off every second. If OCR0A has a value, set it
		// to 0, otherwise invert it.
		if(centis >= 100) {
				centis = 0;
				if(OCR0A)
						OCR0A = 0x0;
				else
						OCR0A = 255; 
		}
}

void execute_state(void)
{
	switch(current_state) {
	case 1: // Ramp/fade LED
			if(centis) {
				centis = 0;
				OCR0A = simple_ramp();
			}
			break;
	case 2: // Set LED strength according to trimpot value
			OCR0A = 255 - ADCValue;
			break;
	case 3:	// Toggle LED on or off every second
			toggle_LED();
			break;
	default: // Turn LED off
			OCR0A = 255;
			current_state = 0;
		}
}