# Assignment2--Group11

**1. Details About Project**
-
   
**Group Members**
Kyan Gan
Tom Henry
Darcy Schofield

**Roles and Responsibilities**

*Kyan Gan:*
-Responsible for Completing exercise 3
-Assisted in the documentation of ReadMe

*Tom Henry:*
-Responsible for Completing exercise 2
-Assisted in the documentation of ReadMe

*Darcy Schofield:*
-Responsible for Completing exercise 1
-Responsible for writing minutes
-Assisted in the documentation of ReadMe


**2. Code Description**
- 

**Exercise 1 - Digital I/O**

**W05-C-Interrupt:**
To know how exercise 1 works, you need to know how the provided code works for W05-C-Interrupt. Firstly, the code enters the EXTI0_IRQHandler function, where the interrupt service routine (ISR) for the EXTI. This is linked to a button press. The interrupt is triggerred when the button is pressed. Inside the ISR, it first checks if on_button_press is not NULL, ensuring there's a valid function to call, then calls that function to handle the button press. The interrupt is cleared by setting the appropriate bit in the EXTI pending register (EXTI->PR), ensuring it doesn't trigger repeatedly without another actual button press. The enable_clocks function enables the clocks for GPIO ports A, C, and E using the RCC AHB peripheral clock enable register. The initialise_board function configures the GPIOE pins 8-15 to operate as output. The chase_led function manipulates the LEDs connected to GPIOE's upper 8 pins (8-15). It shifts the current LED state left, creating a "running light" effect. If the register value becomes 0 after shifting (all LEDs off), it resets to start the pattern over from the first LED. The main function then calls all the appropriate functions.

**1A:**
exercise1A requires that a module is made for the provided code. The code is functions similarly to the previous code except for the fact that it now calls a header file, digital_io.h. This file links the digitcal_io.c file to the main function. The digital_io.c file now contains the code for the EXTI0_IRQHandler, chase_led and the button_pressed_handler functions. Code runs as before, except now it calls the digital_io functions from a different file. 

**1B:**
exercise1B requires the passing of a function pointer to the software module on initialisation that is called (as a callback) when there is a button press. First, there is a function pointer defined, [void (*button_press_handler)(void) = 0x00;]. This function pointer is meant to point to any function that matches the signature void func(void). The header file (digital_io.h) declares a function set_button_press_handler() which is defined in digital_io.c. This function is used to assign a valid function to button_press_handler. The argument handler is itself a function pointer of the same type as button_press_handler. This function simply assigns the passed function pointer handler to the global function pointer button_press_handler. The ISR check in the EXTI0_IRQHandler function if button_press_handler points to a valid function. If the pointer is valid, the function it points to is called using button_press_handler(). This calls the function whose address is stored in the pointer, executing the callback. In the main file, the callback function can be seen, button_press_callback. This function just calls the chase_led function, however it can do whatever the coder desires.

**1C:**
exercise1C requires that the chase_led function uses get/set functions, and that the only way to acess the LED state is via the get/set functions. The set_led_state(uint8_t state) function updates the state of the LEDs, which is stored in a static variable within the file (making it accessible only through these functions). This function sets the internal state of the LEDs to the passed state value. This function is used whenever the state of the LEDs needs to be changed/when the button is pressed. The get_led_state() function retrieves the current state of the LEDs from the same static variable (led_state). This function provides access to the current state of the LEDs, allowing other parts of the program to read but not directly modify the state.

**1D:**
exercise1D requires that the speed at which the leds change to be restricted by a timer. The code functions similarly to before, where the leds turn on and chase around the board, except now it utilises timers instead of a button press to update the led state. First, there is a timer configuration where the following functions are executed: timer_initialisation, __disable_irq, max_count_value, set_prescaler, reset_timer, reset_UIF and __enable_irq. Next the interrupts are set up: enable_interrupt sets up the interrupt handling for Timer 2. It configures the importance level of the Timer 2 interrupt overflow. Then, it activates the Timer 2 interrupt in the microcontroller's Nested Vector Interrupt Controller (NVIC) and ensures that Timer 2 is configured to generate an update interrupt (UIE) when it overflows.

**Exercise 2 - Serial Interface**

**2A:**

**2B:**

**2C:**

**2D:**


**Exercise 3 - Timer Interface**

**3A:**
This module contains 2 main modules, one is the "timers.c" file which includes all necessary initialisation of the board and the timers.
The other is the error handling function which triggers a callback function of the user's choice.

**3B:**
This module contains 2 main modules, one is the "timers.c" file which includes all necessary initialisation of the board and the timers. A struct is defined which through the get/set functions provided sets the necessary information to the timer registers.
The other is the error handling function which triggers a callback function of the user's choice.

**3C:**
This module contains 2 main modules, one is the "timers.c" file which includes all necessary initialisation of the board and the timers. There is a function defined here called oneshot which encapsulates the functionality of this part.
The other is the error handling function which triggers a callback function of the user's choice.

**Exercise 4 - Integrations**




**3. User Instructions**
-
**Exercise 1 - Digital I/O**
The user instructions are as follows:
1. Run the code
2. Press the USER button (blue button)
3. An led should turn on
4. Continue pressing the led to see the led state hange and shift around the microcontroller

**Exercise 2 - Serial Interface**

The user instructions is the samse for each section of exercise 2.
1. Run the code and open a serial input terminal connected to USART1. 
2. Type the string or phrase to be transmitted to the microcontroller into the serial input terminal.
3. Once the string or phrase has been completed, type '+' into the serial input terminal to signify the end of the string. In this program '+' is the terminating character.
4. Once the terminating character is transmitted, a the callback function is called. In this program the callback function, 'Stirng , causes the LEDs to represent the binary ascii value of the transmitted characters.

A serial port besides USART1 can be used by defining a different serial port struct and enteirng the address of that struct into SerialInitialise.
Similarly, baud rates of 9600, 19200, 38400, 57600, 115200 at 8 MHz can be used by changing the baud rate input into SerialInitialise in the main function. This program uses 115200 at 8 MHz.




**Exercise 3 - Timer Interface**
Run the code, open a serial terminal program with the following settings:
- baud rate: 115200
- data size: 8
- Parity: None
- Stop bits: 1
Type in "timer xxxx+" where "xxxx" is the number of milliseconds the period of the timer will be. Once this has been typed, the LEDs on the board should start lighting up one at a time at the requested interval.
In order to change the period of the timer, type the same thing in while changing the value for "xxxx".
To stop the timer from running, type in "disable timer+"
Type in "oneshot xxxx+" where "xxxx" is the number of milliseconds of the delay before the oneshot event occurs. Once this has been typed, wait for the requested delay to elapse and then all of the LEDs will turn on at once.
In order to get a clear image of how each function operates independently, can type in "disable led+" to turn off all the LEDs



**4. Testing Procedure**
- 

**Exercise 1:**
The testing procedure is very simple for exercise 1. The led represents the state, shows that the code functions appropriately, therefore the led is the testcase for all of exercise 1. As the button is pressed, the led moves around the microcontroller, showing the functionality of the code.
