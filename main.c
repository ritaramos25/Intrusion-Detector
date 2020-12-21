/*******************************************************************************
 *
 * Module: main.c
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

#include "LIB/display.h"
#include "LIB/keypad.h"
#include "driverlib/rom_map.h"
#include "LIB/sensor_temp.h"
#include "LIB/clock.h"
#include "LIB/system.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int main()
{
    SysCtlClockSet(SYSCTL_SYSDIV_8|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    char button;
    char init[20]="change time";
    char time[20];
    long int temperature; //temperatura
    int state=0;

    //Inicializacao do hardware
    initLCD();
    initKEYPAD();

    //Adquire o estado do sistema
    state = wake_up();

    //Se um botao for premido o state fica a high e o programa começa a funcionar
    if (state==1)
    {
        clearLCD();
        printLCD(init);
        setCursorPositionLCD(1,0);
        SysCtlDelay(10000000);
        clearLCD();

        define_time(); //as horas e os dias sao definidos

       /* while (1)
        {
            while (1)
            {
                printLCD(time);
                setCursorPositionLCD(1,0);
                SysCtlDelay(10000);

                temperature=read_temp();

                button=readKEYPAD();

                if (button != ' ')
                {
                    break;
                }
            }

            print_temp(temperature, button);
        }*/
    }

    return 0;
}
