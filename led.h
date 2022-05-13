// DELUPPGIFT 4

#ifndef _LED_H_
#define _LED_H_

extern uint8_t current_state;

void LED_init(void);
void toggle_LED(void);
void execute_state(void);

uint8_t simple_ramp(void);


#endif // _LED_H_

