#pragma once
#include <stdint.h>
#include <string.h>
#include "mxc.h"

// This is our board's I2C register
#define I2C_INTERFACE MXC_I2C1 

/* Send data over I2C
 * @param address
 *  The host memory address to write our buffer to
 * @param recipient_register
 *  The I2C register target for our message
 * @param data
 *  Pointer to our message's data buffer
 * @param length
 *  Length of the memory buffer, function is aborted if the length exceeds 80
 *
 * @requires length to be less than or equal to 80 
 * */
int WriteData(uint8_t recipient, uint8_t *data, size_t length);

/* 
 * NOTE: Maybe we call this function via a callback/event/interrupt instead of a while loop?? idk
 * */
int ReadData();

