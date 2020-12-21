/*******************************************************************************
 *
 * Module: I2C.h
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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#ifndef LIB_I2C_H_
#define LIB_I2C_H_


//#define GPIO_PA7_I2C1SDA GPIO_PIN_7
//#define GPIO_PA6_I2C1SCL GPIO_PIN_6

void InitI2C1(void);
//void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
uint16_t I2CReceive(uint8_t slave_addr, uint8_t reg);
//void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);

//void I2C1_write(uint8_t slave_addr, uint8_t slave_reg);
//void I2C1_read(uint8_t slave_addr, uint16_t *RxData, uint8_t N);





#endif /* LIB_I2C_H_ */
