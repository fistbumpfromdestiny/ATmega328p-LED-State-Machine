// DELUPPGIFT 4
#include <avr/io.h>
#include "adc.h"

void ADC_init(void)
{
        ADCSRA |= _BV(ADEN);    // Enable ADC
        ADCSRA |= _BV(ADIE);    // Enable ADC Interrupt
        ADCSRA |= (_BV(ADPS1) | _BV(ADPS0)); // Set prescaler to 8
        
        ADMUX  = 0x0;           // Enable ADC0 as input
        ADMUX |= _BV(ADLAR);    // Left adjusted
        ADMUX |= _BV(REFS0);    // Voltage reference; AVcc with external 
                                // capacitor at AREF pin
}

