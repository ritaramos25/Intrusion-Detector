/*******************************************************************************
 *
 * Module: system.h
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
 *
 ***************************************************************************/

#ifndef LIB_SYSTEM_H_
#define LIB_SYSTEM_H_

#include "display.h"
#include "keypad.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int wake_up(void);

void guarda_error(int h, int m, int s);

void print_error(char *str_error);




#endif /* LIB_SYSTEM_H_ */
