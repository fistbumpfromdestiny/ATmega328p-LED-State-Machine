// DELUPPGIFT 4
#include <avr/io.h>
#include <stdbool.h>

#include "timer.h"
#include "led.h"

void timer0_init(void) 
{
		// Set Fast PWM-mode, TOP = 0xFF, Non-inverting
		TCCR0A |= (1<<WGM00) | (1<<WGM01) | (1 << COM0A1);
		/* Set prescaler to 64 -> 16MHz / (256 * 64) 
		 * PWM Frequency = 976,5625Hz */
		TCCR0B = 0x03;		
}

void timer2_init(void) 
{
		// Set CTC-mode
		TCCR2A |= _BV(WGM21);
		// Set Clear OC2A on Compare Match
		TCCR2A |= _BV(COM2A1);
		// Set prescaler to 1024
		TCCR2B = 0x07;
		// 100Hz -> (16MHz/(1024*100))-1 = 155
		OCR2A = 0x9B;
		// Enable Timer Compare Interrupt
		TIMSK2 |= _BV(OCIE2A);
}

