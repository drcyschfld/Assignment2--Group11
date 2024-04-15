#include <stdint.h>
#include "stm32f303xc.h"
#include "initialise.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int enable_clocks(){

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN; //enable GPIOA, GPIOC, GPIOE

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //store a 1 into the TIM2 enable flag to enable the timer

}



void initialise_board() {

	// get a pointer to the second half word of the MODER register (for outputs pe8-15)
	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
}


void reset_timer_2() {

	TIM2->EGR |= TIM_EGR_UG;

}

void reset_UIF_2(){

	TIM2->SR &= ~TIM_SR_UIF;

}

void max_count_value_timer_2(timer_info *s) {

	uint16_t max_count = s->max_count;
	TIM2->ARR = max_count;

}

void start_timer_2() {

	TIM2->CR1 |= TIM_CR1_CEN;

}

void set_prescaler_timer_2(timer_info *s){

	uint16_t psc_value = s->psc_value;
	TIM2->PSC = psc_value;

}

void general_initialisation() {

	enable_clocks();
	initialise_board();

}

void timer_2_initialisation(timer_info *s){

	__disable_irq();

	max_count_value_timer_2(s);
	start_timer_2();
	set_prescaler_timer_2(s);
	reset_timer_2();
	reset_UIF_2();

	__enable_irq();

}

void enable_interrupt_timer_2(){

	__disable_irq();

	__NVIC_SetPriority(TIM2_IRQn,2);
	__NVIC_EnableIRQ(TIM2_IRQn);

	TIM2->DIER |= TIM_DIER_UIE;

	__enable_irq();
}








void reset_timer_3() {

	TIM3->EGR |= TIM_EGR_UG;

}

void reset_UIF_3(){

	TIM3->SR &= ~TIM_SR_UIF;

}

void max_count_value_timer_3(timer_info *s) {

	uint16_t max_count = s->max_count;
	TIM3->ARR = max_count;

}

void start_timer_3() {

	TIM3->CR1 |= TIM_CR1_CEN;

}

void set_prescaler_timer_3(timer_info *s){

	uint16_t psc_value = s->psc_value;
	TIM3->PSC = psc_value;

}


void timer_3_initialisation(timer_info *s){

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

	__disable_irq();

	__NVIC_SetPriority(TIM3_IRQn,2);
	__NVIC_EnableIRQ(TIM3_IRQn);

	TIM3->DIER |= TIM_DIER_UIE;

	__enable_irq();
}

void disable_timer_3(){

	RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN;

}
