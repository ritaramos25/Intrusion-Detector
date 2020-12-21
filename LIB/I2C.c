/*******************************************************************************
 *
 * Module: I2C.c
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

#include "I2C.h"


//initialize I2C module 1
//Slightly modified version of TI's example code
void InitI2C1(void)
{
    //enable I2C module 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);

    //enable GPIO peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for I2C1 functions on port A6 and A7.
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

    // Enable and initialize the I2C1 master module.  Use the system clock for
    // the I2C1 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);

    //clear I2C FIFOs
    //HWREG(I2C2_BASE + I2C_2_FIFOCTL) = 80008000;
}

//read specified register on slave device
uint16_t I2CReceive(uint8_t slave_addr, uint8_t reg)
{
    uint16_t temp;
    uint8_t temp1, temp2;
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C1_BASE, reg);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C1_BASE));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C1_BASE));

    temp1=I2CMasterDataGet(I2C1_BASE);

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    while(I2CMasterBusy(I2C1_BASE));

    temp2=I2CMasterDataGet(I2C1_BASE);

    temp=(temp1<<8)|temp2;

    //return temperature
    return temp;
}



//sends an I2C command to the specified slave
/*void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    uint8_t i;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    //stores list of variable number of arguments
    va_list vargs;

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C1_BASE));

        //"close" variable argument list
        va_end(vargs);
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C1_BASE));

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        for(i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C1_BASE));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C1_BASE, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C1_BASE));

        //"close" variable args list
        va_end(vargs);
    }
}*/



//
// I2C1 Write function
//
/*void I2C1_write(uint8_t slave_addr, uint8_t slave_reg)
{
  // Set address to be used by the master module when writing to the slave
  I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
  while (I2CMasterBusy(I2C1_BASE));
  // Place command to be sent to the data register
  I2CMasterDataPut(I2C1_BASE, slave_reg);
  // Send data to slave register
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND);
  while (I2CMasterBusy(I2C1_BASE));
}

//
// I2C1 Read function
//
void I2C1_read(uint8_t slave_addr, uint16_t *RxData, uint8_t N)
{
  uint8_t i; //Set local variable for loop function
  // Set address to be read
  I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);
  if (N==1)
  {
    // Read 8-bit data
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
    while (I2CMasterBusy(I2C1_BASE));
    // Place data into Rx array
    RxData[0]=I2CMasterDataGet(I2C1_BASE);
    while (I2CMasterBusy(I2C1_BASE));
  }
  else
  {
    // Start reading bursts of data
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while (I2CMasterBusy(I2C1_BASE));
    // Place data into RxData array
    RxData[0]=I2CMasterDataGet(I2C1_BASE);
    while (I2CMasterBusy(I2C1_BASE));

    // Continue reading data until N-1
    for (i=1;i<(N-1);i++)
    {
      I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
      while (I2CMasterBusy(I2C1_BASE));
      RxData[i]=I2CMasterDataGet(I2C1_BASE);
      while (I2CMasterBusy(I2C1_BASE));
    }

  // Read final data
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

  while (I2CMasterBusy(I2C1_BASE));
  // Place last piece of data into RxData array
  RxData[N-1]=I2CMasterDataGet(I2C1_BASE);
  while (I2CMasterBusy(I2C1_BASE));
  }
}
*/

