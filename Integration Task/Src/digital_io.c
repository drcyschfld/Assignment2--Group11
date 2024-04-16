#include "stm32f303xc.h"
#include "digital_io.h"

// Define a function pointer to store the button press handler
void (*button_press_handler)(void) = 0x00;



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
	uint8_t *LED_output_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
	uint8_t LED_pattern;
	 LED_pattern = *LED_output_register;
	 return LED_pattern;
}

// Function to set the LED state
void set_led_state(uint8_t state)
{
    uint8_t *LED_output_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    uint8_t LED_pattern = state;
    *LED_output_register = LED_pattern;
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



void enable_interrupt_led(void) {
    // Disable the interrupts while messing around with the settings
    // otherwise, can lead to strange behavior
    __disable_irq();

    // Enable the system configuration controller (SYSCFG in RCC)
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Configure PA0 as EXTI0 interrupt source
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0_Msk; // Clear bits
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;  // Set EXTI0 to PA0

    // Configure EXTI0 to trigger on rising edge
    EXTI->RTSR |= EXTI_RTSR_TR0;

    // Enable EXTI0 interrupt
    EXTI->IMR |= EXTI_IMR_MR0;

    // Set EXTI0 interrupt priority and enable it
    NVIC_SetPriority(EXTI0_IRQn, 1);
    NVIC_EnableIRQ(EXTI0_IRQn);

    // Re-enable all interrupts (now that we are finished)
    __enable_irq();
}

void disable_interrupt_led(void) {
    // Disable the interrupts while messing around with the settings
    // otherwise, can lead to strange behavior
    __disable_irq();

    // Enable EXTI0 interrupt
    EXTI->IMR &= ~EXTI_IMR_MR0;

    // Re-enable all interrupts (now that we are finished)
    __enable_irq();
}
