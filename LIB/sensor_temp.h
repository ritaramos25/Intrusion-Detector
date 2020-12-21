/*******************************************************************************
 *
 * Module: sensor_temp.h
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

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "sensorlib/tmp100.h"
#include "sensorlib/hw_tmp100.h"
#include "driverlib/i2c.h"
#include "sensorlib/i2cm_drv.h"
#include "driverlib/sysctl.h"
#include "I2C.h"
#include "I2C_masterdrive.h"
#include "math.h"
#include "stdio.h"
#include "display.h"



#ifndef LIB_SENSOR_TEMP_H_
#define LIB_SENSOR_TEMP_H_


#define TEMP_ADDR 0x4A

int check_temp(long int temperature);

void print_temp(long int temperature, char button);

long int read_temp (void);

void TMP100Callback(void *pvCallbackData, uint_fast8_t ui8Status);

#endif /* LIB_SENSOR_TEMP_H_ */
