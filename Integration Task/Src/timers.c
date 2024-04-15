#include <stdint.h>
#include "stm32f303xc.h"
#include "timers.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int enable_clocks(){
/*
 * function info:
 * this function enables all necessary GPIO clocks
 */

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN; //enable GPIOA, GPIOC, GPIOE



}

void initialise_board() {
/*
 * function info:
 * this function sets the LED ports to output
 */
	// get a pointer to the second half word of the MODER register (for outputs pe8-15)
	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
}

void set_max_count(timer_info *s, uint16_t max_count_value){
/*
 * function info:
 * this function takes in a variable of type timer_info and a value and sets the variable.max_count to the value
 */

	s->max_count = max_count_value;

}

void set_psc_value(timer_info *s, uint16_t psc_int){
/*
 * function info:
 * this function takes in a variable of type timer_info and a value and sets the variable.psc_value to the value
 */

	s->psc_value = psc_int;

}

timer_info delay_set(uint16_t delay_in_milliseconds){
/*
 * function info:
 * this function takes in the requested delay in milliseconds and sends it to the set_max_count function.
 * once the function has completed it returns a variable called timer_x_info of type timer_info that has information for max_count and the psc_value
 * max count values:
 * 0x2710 = count of 10000 (10 seconds),
 * 0x1388 = count of 5000 (5 seconds),
 * 0x3E8 = count of 1000 (1 second)
 */

	timer_info timer_x_info;
	//uint16_t max_count_value = 0x3E8;
	uint16_t psc_value = 0x1F3F;
	set_max_count(&timer_x_info, delay_in_milliseconds);
	set_psc_value(&timer_x_info, psc_value);

	return timer_x_info;
}




void reset_timer_2() {
/*
 * function info:
 * this function forces the counter to overflow
 */
	TIM2->EGR |= TIM_EGR_UG;

}

void reset_UIF_2(){
/*
 * function info:
 * this function resets the UIF bit in timer 2 SR register
 */

	TIM2->SR &= ~TIM_SR_UIF;

}

void max_count_value_timer_2(timer_info *s) {
/*
 * function info:
 * this function takes in a struct that gives information about the timers properties and sets timer 2 max count to the
 * specified count
 */

	uint16_t max_count = s->max_count;
	TIM2->ARR = max_count;

}

void start_timer_2() {
/*
 * function info:
 * this function sets timer 2 enable bit to 1 to start the counter
 */

	TIM2->CR1 |= TIM_CR1_CEN;

}

void set_prescaler_timer_2(timer_info *s){
/*
 * function info:
 * this function takes in a struct that gives information about the timers properties and sets timer 2 psc to the
 * specified value
 */

	uint16_t psc_value = s->psc_value;
	TIM2->PSC = psc_value;

}

void general_initialisation() {
/*
 * function info:
 * this function encapsulates the general setup of the STM32 board to allow for things to be done
 */
	enable_clocks();
	initialise_board();

}

void timer_2_initialisation(timer_info *s){
/*
 * function info:
 * this function initialises timer 2 to have a delay specified by the struct that is passed into it
 */
	__disable_irq();

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //store a 1 into the TIM2 enable flag to enable the timer

	max_count_value_timer_2(s);
	start_timer_2();
	set_prescaler_timer_2(s);
	reset_timer_2();
	reset_UIF_2();

	__enable_irq();

}

void enable_interrupt_timer_2(){
/*
 * function info:
 * this function enables interrupts for timer 2
 */
	__disable_irq();


	__NVIC_SetPriority(TIM2_IRQn,2);
	__NVIC_EnableIRQ(TIM2_IRQn);

	TIM2->DIER |= TIM_DIER_UIE;

	__enable_irq();
}

void disable_timer_2_interrupt(){
/*
 * function info:
 * this function disables interrupts for timer 2
 */

	TIM2->DIER &= ~TIM_DIER_UIE;

}

void timer_2_set(uint16_t delay_in_milliseconds){

/*
 * function info:
 * this function takes in a delay in milliseconds and passes it to the delay_set function.
 * The return of the delay_set function is saved in the variable timer_x_info which is then
 * passed to the timer_initialisation function to start the delay
 */

	timer_info timer_x_info = delay_set(delay_in_milliseconds);

	timer_2_initialisation(&timer_x_info);
}

void (*regular_timer(uint16_t delay_in_milliseconds, void (*func_ptr)()))() {
/*
 * function info:
 * this function makes it so that any function can be passed in as a function pointer and when an interrupt occurs
 * the desired function is called
 */
    timer_2_set(delay_in_milliseconds);
    enable_interrupt_timer_2();

    return func_ptr;

}




void reset_timer_3() {
/*
 * function info:
 * this function forces the counter to overflow
 */

	TIM3->EGR |= TIM_EGR_UG;

}

void reset_UIF_3(){
/*
 * function info:
 * this function resets the UIF bit in timer 2 SR register
 */

	TIM3->SR &= ~TIM_SR_UIF;

}

void max_count_value_timer_3(timer_info *s) {
/*
 * function info:
 * this function takes in a struct that gives information about the timers properties and sets timer 3 max count to the
 * specified count
 */
	uint16_t max_count = s->max_count;
	TIM3->ARR = max_count;

}

void start_timer_3() {
/*
 * function info:
 * this function sets timer 3 enable bit to 1 to start the counter
 */

	TIM3->CR1 |= TIM_CR1_CEN;

}

void set_prescaler_timer_3(timer_info *s){
/*
 * function info:
 * this function takes in a struct that gives information about the timers properties and sets timer 3 psc to the
 * specified value
 */
	uint16_t psc_value = s->psc_value;
	TIM3->PSC = psc_value;

}

void timer_3_initialisation(timer_info *s){
/*
 * function info:
 * this function initialises timer 3 to have a delay specified by the struct that is passed into it
 */

	__disable_irq();

	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	max_count_value_timer_3(s);
	start_timer_3();
	set_prescaler_timer_3(s);
	reset_timer_3();
	reset_UIF_3();

	__enable_irq();

}

void enable_interrupt_timer_3(){
/*
 * function info:
 * this function enables interrupts for timer 3
 */

	__disable_irq();

	__NVIC_SetPriority(TIM3_IRQn,2);
	__NVIC_EnableIRQ(TIM3_IRQn);

	TIM3->DIER |= TIM_DIER_UIE;

	__enable_irq();
}

void disable_timer_3_interrupt(){
/*
 * function info:
 * this function disables interrupts for timer 2
 */

	TIM3->DIER &= ~TIM_DIER_UIE;

}

void timer_3_set(uint16_t delay_in_milliseconds){

/*
 * function info:
 * this function takes in a delay in milliseconds and passes it to the delay_set function.
 * The return of the delay_set function is saved in the variable timer_x_info which is then
 * passed to the timer_initialisation function to start the delay
 */

	timer_info timer_x_info = delay_set(delay_in_milliseconds);

	timer_3_initialisation(&timer_x_info);
}

void (*one_shot(uint16_t delay_in_milliseconds, void (*func_ptr)()))() {
/*
 * function info:
 * this function makes it so that any function can be passed in as a function pointer and when an interrupt occurs
 * the desired function is called
 */
    timer_3_set(delay_in_milliseconds);
    enable_interrupt_timer_3();

    return func_ptr;

}




void reset_timer_4() {
/*
 * function info:
 * this function forces the counter to overflow
 */

	TIM4->EGR |= TIM_EGR_UG;

}

void reset_UIF_4(){
/*
 * function info:
 * this function resets the UIF bit in timer 2 SR register
 */

	TIM4->SR &= ~TIM_SR_UIF;

}

void max_count_value_timer_4(timer_info *s) {
/*
 * function info:
 * this function takes in a struct that gives information about the timers properties and sets timer 3 max count to the
 * specified count
 */
	uint16_t max_count = s->max_count;
	TIM4->ARR = max_count;

}

void start_timer_4() {
/*
 * function info:
 * this function sets timer 3 enable bit to 1 to start the counter
 */

	TIM4->CR1 |= TIM_CR1_CEN;

}

void set_prescaler_timer_4(timer_info *s){
/*
 * function info:
 * this function takes in a struct that gives information about the timers properties and sets timer 3 psc to the
 * specified value
 */
	uint16_t psc_value = s->psc_value;
	TIM4->PSC = psc_value;

}

void timer_4_initialisation(timer_info *s){
/*
 * function info:
 * this function initialises timer 3 to have a delay specified by the struct that is passed into it
 */

	__disable_irq();

	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	max_count_value_timer_4(s);
	start_timer_4();
	set_prescaler_timer_4(s);
	reset_timer_4();
	reset_UIF_4();

	__enable_irq();

}

void enable_interrupt_timer_4(){
/*
 * function info:
 * this function enables interrupts for timer 3
 */

	__disable_irq();

	__NVIC_SetPriority(TIM4_IRQn,2);
	__NVIC_EnableIRQ(TIM4_IRQn);

	TIM4->DIER |= TIM_DIER_UIE;

	__enable_irq();
}

void disable_timer_4_interrupt(){
/*
 * function info:
 * this function disables interrupts for timer 2
 */

	TIM4->DIER &= ~TIM_DIER_UIE;

}

void timer_4_set(uint16_t delay_in_milliseconds){

/*
 * function info:
 * this function takes in a delay in milliseconds and passes it to the delay_set function.
 * The return of the delay_set function is saved in the variable timer_x_info which is then
 * passed to the timer_initialisation function to start the delay
 */

	timer_info timer_x_info = delay_set(delay_in_milliseconds);

	timer_4_initialisation(&timer_x_info);
}

void timer_4_begin(uint16_t delay_in_milliseconds){

	timer_4_set(delay_in_milliseconds);
	enable_interrupt_timer_4();

}





void LED_all (){
/*
 * function info:
 * this function turns on all LEDs
 */
	uint8_t *LED_output_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
	uint8_t LED_pattern = 0b11111111;
	*LED_output_register = LED_pattern;

}

void LED_off (){
/*
 * function info:
 * this function turns off all LEDs
 */
	uint8_t *LED_output_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
	uint8_t LED_pattern = 0x00;
	*LED_output_register = LED_pattern;

}
