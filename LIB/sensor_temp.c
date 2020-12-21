/*******************************************************************************
 *
 * Module: sensor_temp.c
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

#include "sensor_temp.h"

volatile bool g_bTMP100Done;


/*float bintofloat(uint16_t x) {
    float f = 0.0f;
    memcpy(&f, &x, sizeof(f) < sizeof(x) ? sizeof(f) : sizeof(x));
    return f;
}
*/

int check_temp(long int temperature)
{
      long int temp;


      temp=(temperature/256);

      if (temp >= 24)
      {
          return 1;

      }
      else
          return 0;

}

void print_temp(long int temperature, char button)
{
    long int temp_int1;
    long int temp;
    long int temp_int2;
    float temp_frac;

    char str_temp[15];
    char error[20];

    clearLCD();

    if (button == 'A')
    {
        if ((temperature % 256) == 0) //se a temperaturo é divisivel por 256 é inteiro
        {
            temp=(temperature/256);
            sprintf(str_temp, "temp = %d\0", temp);

            printLCD(str_temp);
            setCursorPositionLCD(1,0);
            SysCtlDelay(10000000);
            clearLCD();

        }
        else //se a temperatura tem casas decimais
        {
            temp_int1=(temperature/256);
            temp_frac=temperature-temp_int1;
            temp_int2= trunc (temp_frac * 10);
            sprintf(str_temp, "temp = %d.%d\0", temp_int1, temp_int2);

            printLCD(str_temp);
            setCursorPositionLCD(1,0);
            SysCtlDelay(10000000);
            clearLCD();

       }
    }
    else
    {
        sprintf(error, "botao invalido %s", &button);
        printLCD(error);
        setCursorPositionLCD(1,0);
        SysCtlDelay(10000000);
        clearLCD();
    }

}

long int read_temp(void)
{
    InitI2C1();

    //temp=I2CReceive(TEMP_ADDR, 0x00);

    long int raw = (long int) I2CReceive(TEMP_ADDR, 0x00);

    return raw;

    //I2CMSimpleExample();

    /*g_bTMP100Done = false;
    TMP100Init(&sTMP100, &sI2CInst, 0x4a, TMP100Callback, 0);
    while(!g_bTMP100Done)
    {
    }

    g_bTMP100Done = false;
    TMP100ReadModifyWrite(&sTMP100, TMP100_O_CONFIG, ~TMP100_CONFIG_RES_M,
    TMP100_CONFIG_RES_12BIT, TMP100Callback, 0);

    while(!g_bTMP100Done)
    {
    }


    while(1)
    {
//
// Request another reading from the TMP100.
//
        g_bTMP100Done = false;
        TMP100DataRead(&sTMP100, TMP100Callback, 0);
        while(!g_bTMP100Done)
        {
        }
//
// Get the new temperature reading.
//
       TMP100DataTemperatureGetFloat(&sTMP100, &fTemperature);

//
// Do something with the new temperature reading.
//
    }*/
}


void TMP100Callback(void *pvCallbackData, uint_fast8_t ui8Status)
{
// See if an error occurred.

    if(ui8Status != I2CM_STATUS_SUCCESS)
    {
        // An error occurred, so handle it here if required.
    }
        // Indicate that the TMP100 transaction has completed.

    g_bTMP100Done = true;
}

