#ifndef INITIALISE_H
#define INITIALISE_H

#include <stdint.h>
#include "stm32f303xc.h"

typedef struct {
    uint16_t max_count;
    uint16_t psc_value;
} timer_info;

int enable_clocks();
void initialise_board();
void reset_timer_2();
void reset_UIF_2();
void max_count_value_timer_2(timer_info *s);
void start_timer_2();
void set_prescaler_timer_2(timer_info *s);
void general_initialisation();
void timer_2_initialisation(timer_info *s);
void enable_interrupt_timer_2();
void reset_timer_3();
void reset_UIF_3();
void max_count_value_timer_3(timer_info *s);
void start_timer_3();
void set_prescaler_timer_3(timer_info *s);
void timer_3_initialisation(timer_info *s);
void enable_interrupt_timer_3();
void disable_timer_3();

#endif /* INITIALISE_H */
