/*******************************************************************************
 *
 * Module: clock.h
 *
 * Embedded Systems Project 2020/2021
 * Intrusion Detector for Domestic Applications
 * 15/12/2020
 *
 * Rita Ramos 81616
 * Joao Beirao 82056
 *
 * Prof Rui Rocha
 *
 ***************************************************************************/

#ifndef LIB_CLOCK_H_
#define LIB_CLOCK_H_

#include <keypad.h>
#include <display.h>
#include <sensor_temp.h>
#include <stdio.h>
#include <stdlib.h>

void start_count_watch (void);

void count_watch(int hour,int minute,int second);

void fini_stopwatch(void);

void displayTime_temp(int h,int m,int s);

void define_time (void);




#endif /* LIB_CLOCK_H_ */
