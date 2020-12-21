/*******************************************************************************
 *
 * Module: keypad.c
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

#include "keypad.h"
#include "stdio.h"

unsigned const char keypad[padRows][padCols] = {{ '1', '2', '3', 'F'},
                                                { '4', '5', '6', 'E'},
                                                { '7', '8', '9', 'D'},
                                                { 'A', '0', 'B', 'C'}};


void initKEYPAD (void)
{
        SysCtlPeripheralEnable(DATA_PERIPH_KEY);

        GPIOPinTypeGPIOInput(DATA_PORT_BASE_KEY,  DATAPINS_INPUT);
        GPIOPinTypeGPIOOutput(DATA_PORT_BASE_KEY, DATAPINS_OUTPUT);

        GPIOPinWrite(DATA_PORT_BASE_KEY, DATAPINS_OUTPUT, 0);

        SysCtlDelay(100000);


}

char readKEYPAD(void)
{
    int i=0; //variavel contagem linhas
    int j=0; //variavel contagem colunas
    char data= ' ';

    volatile uint8_t DATA_WRITE; //valor do GPIO_PIN actual (com valor 1) das linhas
    volatile uint8_t DATA_READ;  //valor do porto actual das colunas

    volatile uint32_t value_read;
    //volatile uint32_t value_write_B0;
    //volatile uint32_t value_write_B1;
    //volatile uint32_t value_read_B7;

    GPIOPinWrite(DATA_PORT_BASE_KEY, DATAPINS_OUTPUT, 0);
    GPIOPinWrite(DATA_PORT_BASE_KEY, DATAPINS_INPUT, 0);


    for(i=0; i<4; i++)
    {
        DATA_WRITE= (1U << i);

        GPIOPinWrite(DATA_PORT_BASE_KEY, DATA_WRITE, DATA_WRITE);

           for(j=0; j<4; j++)
           {
                DATA_READ= (1U << j+4);


                value_read=(GPIOPinRead(DATA_PORT_BASE_KEY, DATA_READ));


            if ((GPIOPinRead(DATA_PORT_BASE_KEY, DATA_READ) && DATA_READ) == 1)
            {
              return keypad[i][j];
            }
            else //nenhum botao foi premido
            {
               data=' ';
            }
        }

           GPIOPinWrite(DATA_PORT_BASE_KEY, DATA_WRITE, 0);
    }

    return data;

 }



