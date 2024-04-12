#include "stm32f303xc.h"
#include "digital_io.h"

// Define a function pointer to store the button press handler
void (*button_press_handler)(void) = 0x00;

// Define a variable to store the LED state
static uint8_t led_state = 0;

// EXTI0 interrupt handler
void EXTI0_IRQHandler(void)
{
    if (button_press_handler != 0x00) {
        button_press_handler();
    }
    EXTI->PR |= EXTI_PR_PR0;
}

// Function to set the button press handler
void set_button_press_handler(void (*handler)(void))
{
    button_press_handler = handler;
}

// Function to get the LED state
uint8_t get_led_state(void)
{
    return led_state;
}

// Function to set the LED state
void set_led_state(uint8_t state)
{
    led_state = state;
}



// Function to implement LED chasing effect
void chase_led(void)
{
    static uint8_t led_value = 0x01;  // Holds the current pattern to display on LEDs

    // Set the LED state to the current value
    set_led_state(led_value);

    // Calculate the next LED pattern with circular shift
    led_value = (led_value << 1) | (led_value >> 7);

    // Write the current state of the LEDs to the actual hardware
    // Retrieve the LED state managed through get/set functions
    uint8_t led_register = get_led_state();

    // Get a pointer to the Output Data Register of GPIOE, assuming only PE8-PE15 are used for LEDs
    uint8_t *led_register_ptr = ((uint8_t*)&(GPIOE->ODR)) + 1;
    *led_register_ptr = led_register;  // Update the output register with the current LED state
}
