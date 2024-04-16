#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>
#include "stm32f303xc.h"

typedef struct {
    uint16_t max_count;
    uint16_t psc_value;
} timer_info;

int enable_clocks();
void initialise_board();
void set_max_count(timer_info *s, uint16_t max_count_value);
void set_psc_value(timer_info *s, uint16_t psc_int);
timer_info delay_set(uint16_t delay_in_milliseconds);


void reset_timer_2();
void reset_UIF_2();
void max_count_value_timer_2(timer_info *s);
void start_timer_2();
void set_prescaler_timer_2(timer_info *s);
void general_initialisation();
void timer_2_initialisation(timer_info *s);
void enable_interrupt_timer_2();
void disable_timer_2_interrupt();
void timer_2_set(uint16_t delay_in_milliseconds);
void (*regular_timer(uint16_t delay_in_milliseconds, void (*func_ptr)()))();


void reset_timer_3();
void reset_UIF_3();
void max_count_value_timer_3(timer_info *s);
void start_timer_3();
void set_prescaler_timer_3(timer_info *s);
void timer_3_initialisation(timer_info *s);
void enable_interrupt_timer_3();
void disable_timer_3_interrupt();
void timer_3_set(uint16_t delay_in_milliseconds);
void (*one_shot(uint16_t delay_in_milliseconds, void (*func_ptr)()))();


void reset_timer_4();
void reset_UIF_4();
void max_count_value_timer_4(timer_info *s);
void start_timer_4();
void set_prescaler_timer_4(timer_info *s);
void timer_4_initialisation(timer_info *s);
void enable_interrupt_timer_4();
void disable_timer_4_interrupt();
void timer_4_set(uint16_t delay_in_milliseconds);
void timer_4_begin(uint16_t delay_in_milliseconds);


void LED_all();
void LED_off();

#endif /* TIMERS_H */
