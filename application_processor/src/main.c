// C standard library
#include <stdint.h>
#include <stdio.h>

// MSDK
#include <led.h>
#include <mxc_delay.h>
#include "mxc.h"

// Our project
#include "i2c_controller.h"

#define I2C_SPEED 10000 //idk random value 
// I2C address
#define I2C_ADDR 0x50 //hardcode this later for testing

//void readData(uint8_t slave, uint8_t *buffer, int length){
//        MXC_I2C_Read(I2C_INT, slave_addr, buffer, length, 0);
//}


int main(void)
{      
        LED_Init();

        // LED 3 is blue
        // LED 1 is ?
        // LED 2 is ?
        LED_On(LED3);

        // Why do we do this, What does this do
        MXC_ICC_Enable(MXC_ICC0); //it does a thing possibly
        // Why are we doing this?!??!
        MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);

        //Initialize I2C
        // interface address, master mode?, slave mode?
        int i2c_success = MXC_I2C_Init(I2C_INTERFACE, 1, 0);
        if (i2c_success != E_SUCCESS )
        {
                printf("I2C failed to initialize.\n[Error] %d\n", i2c_success);
        }

        MXC_I2C_SetFrequency(I2C_INTERFACE, I2C_SPEED);
        // timeout in microseconds
        MXC_I2C_SetTimeout(I2C_INTERFACE, 100);

        uint8_t dataToSend = 0x55;
        //uint8_t recievedData = 0x00;

        int write_success = WriteData(I2C_ADDR, &dataToSend, 1);

        printf("write success: %d\n", write_success);

        //readData(I2C_ADDR, &recievedData,1);
        //printf("Retard alert\n 0x%x",recievedData);

        LED_Off(LED3);

        while (1)
        {
                LED_On(LED1);
                LED_Off(LED2);
                MXC_Delay(MXC_DELAY_MSEC(500));
                LED_Off(LED1);
                LED_On(LED2);
                MXC_Delay(MXC_DELAY_MSEC(500));

                //printf("Hello World\n");
        }

        return 0;
}
