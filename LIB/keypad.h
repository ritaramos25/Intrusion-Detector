/*******************************************************************************
 *
 * Module: keypad.h
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

#ifndef LIB_KEYPAD_H_
#define LIB_KEYPAD_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


#define FALSE 0
#define TRUE 1

#define  padRows  4
#define  padCols  4


#define B0 GPIO_PIN_0 // Y1  linhas
#define B1 GPIO_PIN_1 // Y2
#define B2 GPIO_PIN_2 // Y3
#define B3 GPIO_PIN_3 // Y4
#define B4 GPIO_PIN_4 // X1 colunas
#define B5 GPIO_PIN_5 // X2
#define B6 GPIO_PIN_6 // X3
#define B7 GPIO_PIN_7 // X4

#define DATA_PORT_BASE_KEY GPIO_PORTB_BASE

#define DATAPINS_INPUT  B4 | B5 | B6 | B7
#define DATAPINS_OUTPUT B0 | B1 | B2 | B3

#define GPIO_PORTB_DATA_R       (*((volatile uint32_t *)0x400053FC))

char readKEYPAD(void);
void initKEYPAD (void);

#define DATA_PERIPH_KEY SYSCTL_PERIPH_GPIOB
#define DATA_PORT_BASE_INPUT GPIO_PORTB_BASE
#define DATA_PORT_BASE_OUTPUT GPIO_PORTB_BASE


#endif /* LIB_KEYPAD_H_ */
