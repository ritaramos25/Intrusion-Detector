/*******************************************************************************
 *
 * Module: system.c
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

#include <system.h>


//Função para "acordar" o sistema, se um botao for premido ele inicia
//Se um botao for premido retorna 1, se não retorna 0

int wake_up(void)
{
    char button;
    char message[20]="Press to start";

    while (1)
    {
        printLCD(message);
        setCursorPositionLCD(1,0);
        SysCtlDelay(10000);

        button=readKEYPAD();

        if (button != ' ')
        {
            return 1;
        }
    }
}

void guarda_error(int h, int m, int s)
{
    char str_error[20];

    sprintf(str_error, "%d:%d:%d\0", h, m, s);

    print_error(str_error);

}


void print_error(char *str_error)
{
    printLCD(str_error);
    setCursorPositionLCD(1,0);
    SysCtlDelay(10000000);
    clearLCD();
}


