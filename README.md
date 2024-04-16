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

**1A:**
exercise1A requires that a module is made for the provided code. The module is called digital_io.c/h. The way is work is

**1B:**
exercise1B requires the passing of a function pointer to the software module on initialisation that
is called (as a callback) when there is a button press.

**1C:**
exercise1C requires that the chase_led function uses get/set functions, and that the only way to acess the LED state is via the get/set functions.

**1D:**
exercise1D requires 

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


**Exercise 2 - Serial Interface**
The user instructions is the samse for each section of exercise 2.
1. Run the code and open a serial input terminal connected to USART1.
2. Type the string or phrase to be transmitted to the microcontroller into the serial input terminal.
3. Once the string or phrase has been completed, type a '+' into the serial input terminal to signify that the end of the string. In this program '+' is the terminating character.
4. The callback function is then called. In this program the callback function, 'Stirng , causes the LEDs to represent the binary ascii value of the transmitted characters.





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
