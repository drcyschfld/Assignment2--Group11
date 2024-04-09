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


void reset_timer() {

	TIM2->EGR |= TIM_EGR_UG;

}

void reset_UIF(){

	TIM2->SR &= ~TIM_SR_UIF;

}

void max_count_value(timer_info *s) {

	uint16_t max_count = s->max_count;
	TIM2->ARR = max_count;

}

void start_timer() {

	TIM2->CR1 |= TIM_CR1_CEN;

}

void set_prescaler(timer_info *s){

	uint16_t psc_value = s->psc_value;
	TIM2->PSC = psc_value;

}

void general_initialisation() {

	enable_clocks();
	initialise_board();

}

void timer_initialisation(timer_info *s){

	__disable_irq();

	max_count_value(s);
	start_timer();
	set_prescaler(s);
	reset_timer();
	reset_UIF();

	__enable_irq();

}

void enable_interrupt(){

	__disable_irq();

	__NVIC_SetPriority(TIM2_IRQn,2);
	__NVIC_EnableIRQ(TIM2_IRQn);

	TIM2->DIER |= TIM_DIER_UIE;

	__enable_irq();
}


