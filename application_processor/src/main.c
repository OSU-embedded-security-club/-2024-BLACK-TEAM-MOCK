#include <stdint.h>
#include <stdio.h>

#include <led.h>
#include <mxc_delay.h>
#include "mxc.h"

// I2C interface
#define I2C_INTERFACE MXC_I2C1 //i have no fucking clue what im doing its 2am
#define I2C_SPEED 10000 //idk random value 
// I2C address
#define I2C_ADDR 0x50 //hardcode this later for testing

/* Send data over I2C
 * 
 * */
int writeData(uint8_t address, uint8_t recipient_register, uint8_t *data, int length){
        if (length >= 80)
        {
                return -1;
        }
        mxc_i2c_req_t request = {
                // I2C buffer memory address
                .i2c = I2C_INTERFACE,
                // The component id of the recipient
                .addr = address,
                // Number of bytes to write to the I2C buffer
                .tx_len = length+1,
                .tx_buf = data,
                .rx_len = 0,
                .rx_buf = 0,
                .restart = 0,
                .callback = NULL
        };
        int MXC_I2C_MasterTransaction(&request);
}

void readData(uint8_t slave, uint8_t *buffer, int length){
        MXC_I2C_Read(I2C_INT, slave_addr, buffer, length, 0);
}


int main(void)
{      
        // Why do we do this, What does this do
        MXC_ICC_Enable(MXC_ICC0); //it does a thing possibly
        // Why are we doing this?!??!
        MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);

        //Initialize I2C
        int i2c_success = MXC_I2C_Init(I2C_INTERFACE, I2C_SPEED, 0);
        if (!i2c_success)
        {
                printf("I2C failed to initialize.\n[Error] %d\n", i2c_success);
        }

        MXC_I2C_SetFrequency(I2C_INST, I2C_SPEED);

        uint8_t dataToSend = 0x55;
        uint8_t recievedData = 0x00;

        writeData(I2C_ADDR, &dataToSend, 1);
        readData(I2C_ADDR, &recievedData,1);
        printf("Retard alert\n 0x%x",recievedData);

        LED_Init();
        
        while (1)
        {
                LED_On(0);
                LED_On(1);
                MXC_Delay(MXC_DELAY_MSEC(500));
                LED_Off(0);
                LED_Off(1);
                MXC_Delay(MXC_DELAY_MSEC(500));

                printf("Hello World\n");

        }

        return 0;
}
