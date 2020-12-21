/*
 * I2C_masterdrive.h
 *
 *  Created on: 02/12/2020
 *      Author: Rita
 */

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
#include "sensorlib/tmp100.h"
#include "sensorlib/hw_tmp100.h"
#include "sensorlib/i2cm_drv.h"


#ifndef LIB_I2C_MASTERDRIVE_H_
#define LIB_I2C_MASTERDRIVE_H_

#define INT_I2C1 53

void I2CMSimpleIntHandler(void);
void I2CMSimpleCallback(void *pvData, uint_fast8_t ui8Status);
void I2CMSimpleExample(void);



#endif /* LIB_I2C_MASTERDRIVE_H_ */
