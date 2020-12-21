/*******************************************************************************
 *
 * Module: display.h
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
 * References for this module:
 * LCD Library for Stellaris/Tiva launchpads
 *
 ***************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef LIB_DISPLAY_H_
#define LIB_DISPLAY_H_


void pulseLCD(void);
void sendByte(char, int);
void setCursorPositionLCD(char, char);
void clearLCD(void);
void initLCD(void);
void printLCD(char*);
void setBlockCursorLCD(void);
void setLineCursorLCD(void);
void cursorOnLCD(void);
void cursorOffLCD(void);
void displayOffLCD(void);
void displayOnLCD(void);
void homeLCD(void);

#define FALSE 0
#define TRUE 1
/*
 *
 * Pin Connections:
 * PE4 -> RS
 * PE5 -> EN
 * PD0 -> D4
 * PD1 -> D5
 * PD2 -> D6
 * PD3 -> D7
 *
 *
 */

#define RS GPIO_PIN_3
#define EN GPIO_PIN_2
#define D4 GPIO_PIN_4
#define D5 GPIO_PIN_5
#define D6 GPIO_PIN_6
#define D7 GPIO_PIN_7
#define ALLDATAPINS  D7 | D6 | D5 | D4
#define ALLCONTROLPINS RS | EN

#define DATA_PORT_BASE GPIO_PORTC_BASE
#define CMD_PORT_BASE GPIO_PORTA_BASE
#define DATA_PERIPH SYSCTL_PERIPH_GPIOC
#define CMD_PERIPH SYSCTL_PERIPH_GPIOA

#endif /* LIB_DISPLAY_H_ */
