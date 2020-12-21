/*******************************************************************************
 *
 * Module: clock.c
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

#include "display.h"
#include "keypad.h"
#include "clock.h"

void start_count_watch (void)
{
    printLCD("Count time");
    setCursorPositionLCD(1,0);
    SysCtlDelay(10000000);
    clearLCD();
}


void count_watch(int hour,int minute,int second)
{
  //start_count_watch();

  int h = hour, m = minute, s = second;
  long int temperature;
  char button;
  char temp_max[20]="aaaaa";
  int error=0;
  char str_error[20];

  while(1)
  {
      while(h < 24)
      {
        while(m < 60)
        {
          while(s < 60)
          {
              /*printLCD(init);
              setCursorPositionLCD(1,0);*/

              button=readKEYPAD();
              temperature = read_temp();

              error=check_temp(temperature);

              displayTime_temp(h, m, s);

              if(error==1)
              {
                  sprintf(str_error, "Temp max %d:%d:%d\0", h, m, s);
              }

              if (button== 'C')
              {
                  print_error(str_error);
              }

              s++;
          }
          m++;
          s = 0;
        }
        h++;
        m = 0;
        s = 0;
      }

      break;
    }

    fini_stopwatch(); //Se chegar ao final do dia volta o relogio volta a zeros
}


void fini_stopwatch(void)
{
    int h=0, m=0, s=0;

    clearLCD();
    count_watch(h,m,s);

}



void displayTime_temp(int h,int m,int s)
{
    char time[20];
    long int temperature;
    long int temp_int1;
    long int temp;
    long int temp_int2;
    float temp_frac;

    temperature = read_temp();

    if ((temperature % 256) == 0) //se a temperaturo é divisivel por 256 é inteiro
            {
                temp=(temperature/256);
                sprintf(time, "t= %d %d:%d:%d\0", temp, h, m, s);

                printLCD(time);
                setCursorPositionLCD(1,0);
                SysCtlDelay(10000000);
                clearLCD();

            }
            else //se a temperatura tem casas decimais
            {
                temp_int1=(temperature/256);
                temp_frac=temperature-temp_int1;
                temp_int2= trunc (temp_frac * 10);
                sprintf(time, "t= %d.%d %d:%d:%d\0", temp_int1, temp_int2, h, m, s);

                printLCD(time);
                setCursorPositionLCD(1,0);
                SysCtlDelay(10000000);
                clearLCD();
            }

}

void define_time(void)
{
    char str_time[20]="HH:MM:SS  DD:MM:YYYY";
    char error[20]="Invalid time";
    char button_pressed[20];
    int i = 0;
    int j=1;
    char button;
    long int h1;
    long int h2;
    long int h;
    long int m1;
    long int m2;
    long int m;
    long int s2;
    long int s1;
    long int s;

    printLCD(str_time);
    setCursorPositionLCD(1,0);
    SysCtlDelay(10000000);
    clearLCD();


    for(i=0; i<20; i++) //ADQUIRE AS HORAS E O DIA
    {
        if(i != 2 & i != 5 & i !=8 & i!=9 & i!=12 & i!=15) //Se a posicao da string são os 2pontos ou espaços passa a frente
        {
            j=1;
            str_time[i]=' '; //Imprime um espaço no local da string onde adquire o valor do utilizador

            while (j)
            {
                printLCD(str_time);
                setCursorPositionLCD(1,0);
                SysCtlDelay(1000000);

                button=readKEYPAD();

                //Se um botao for premido
                if(button != ' ')
                {
                    SysCtlDelay(1000000);
                    clearLCD();
                    button_pressed[i] = button;

                     //SE OS DADOS FOREM INVALIDOS POR EX MES 13, HORA 25 , ETC
                    if(( button_pressed[0] > '2') | (str_time[0]== '2' &&  button_pressed[1] > '3') | (button_pressed[3] > '5') |
(button_pressed[6] > '5') | (button_pressed[10] > '3') | (str_time[10] == '3' && (button_pressed[11] > '1')) | (button_pressed[13] > '1') |
(str_time[13] == '1' && (button_pressed[14] > '2')) | (str_time[16]== '2' && (button_pressed[17] > '0')) |
(str_time[16]== '2' && (str_time[17] == '0') && (button_pressed[18] > '2')) | (str_time[16]== '2' && (str_time[17] == '0') && (str_time[18] == '2') && (button_pressed[19] > '0')))
                    {
                        printLCD(error);
                        setCursorPositionLCD(1,0);
                        SysCtlDelay(10000000);
                        clearLCD();
                    }
                    else
                    {
                        str_time[i]=button;
                        j=0;
                    }
                }
            }
        }
    }

     h1=(str_time[0]-48); //guarda as horas na variavel int h
     h2=(str_time[1]-48);

     h=h1*10+h2;

     m1=(str_time[3]-48); //guarda os minutos na variavel int m
     m2=(str_time[4]-48);
     m=m1*10+m2;

     s1=(str_time[6]-48); //guarda os segundos na variavel int s
     s2=(str_time[7]-48);
     s=s1*10+s2;

     count_watch(h, m, s); //Comeca a contar o tempo
}
