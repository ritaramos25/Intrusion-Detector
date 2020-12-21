#include <I2C_masterdrive.h>

//
// The I2C master driver instance data.
//
tI2CMInstance g_sI2CMSimpleInst;
//
// A boolean that is set when an I2C transaction is completed.
//
volatile bool g_bI2CMSimpleDone = true;




//
// The interrupt handler for the I2C module.
//
void I2CMSimpleIntHandler(void)
{
//
// Call the I2C master driver interrupt handler.
//
    I2CMIntHandler(&g_sI2CMSimpleInst);
}



//
// The function that is provided by this example as a callback when I2C
// transactions have completed.
//
void I2CMSimpleCallback(void *pvData, uint_fast8_t ui8Status)
{
//
// See if an error occurred.
//
    if(ui8Status != I2CM_STATUS_SUCCESS)
    {
//
// An error occurred, so handle it here if required.
//
    }
//
// Indicate that the I2C transaction has completed.
//
    g_bI2CMSimpleDone = true;
}



//
// The simple I2C master driver example.
//
void I2CMSimpleExample(void)
{
    uint8_t pui8Data[7];

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
//
// Initialize the I2C master driver. It is assumed that the I2C module has
// already been enabled and the I2C pins have been configured.
//
    I2CMInit(&g_sI2CMSimpleInst, I2C1_BASE, INT_I2C1, 0xff, 0xff, 80000000);
//
// Write two bytes of data to the I2C device at address 0x22.
//
    g_bI2CMSimpleDone = false;

    I2CMWrite(&g_sI2CMSimpleInst, 0x4a, pui8Data, 2, I2CMSimpleCallback, 0);

    while(!g_bI2CMSimpleDone)
    {
    }
//
// Read four bytes of data from the I2C device at address 0x31.
//
    g_bI2CMSimpleDone = false;

    I2CMRead(&g_sI2CMSimpleInst, 0x4a, pui8Data, 1, pui8Data, 2, I2CMSimpleCallback, 0);

    while(!g_bI2CMSimpleDone)
    {
    }
}
