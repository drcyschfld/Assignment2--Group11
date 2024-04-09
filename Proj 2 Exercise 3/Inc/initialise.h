#ifndef INITIALISE_H
#define INITIALISE_H

#include <stdint.h>
#include "stm32f303xc.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


typedef struct {
    uint16_t max_count;
    uint16_t psc_value;
} timer_info;

int enable_clocks();
void initialise_board();
void reset_timer();
void reset_UIF();
void max_count_value(timer_info *s);
void start_timer();
void set_prescaler(timer_info *s);
void general_initialisation();
void timer_initialisation(timer_info *s);
void enable_interrupt();



#endif /* INITIALISE_H */
