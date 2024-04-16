#ifndef DIGITAL_IO_H
#define DIGITAL_IO_H

#include <stdint.h>

// EXTI0 interrupt handler
void EXTI0_IRQHandler(void);

// Function to set the button press handler
void set_button_press_handler(void (*handler)(void));

// Function to implement LED chasing effect
void chase_led(void);

// Function to get the LED state
uint8_t get_led_state(void);

// Function to set the LED state
void set_led_state(uint8_t state);

#endif /* DIGITAL_IO_H */
