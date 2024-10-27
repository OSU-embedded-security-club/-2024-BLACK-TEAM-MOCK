#include "i2c_controller.h"

int WriteData(uint8_t recipient, uint8_t *data, size_t length)
{
        // actual data size should not exceed 81 because we stick the recipient on the front
        if (length >= 81)
        {
                return -1;
        }
        
        // initialize to all zeroes
        uint8_t message[81] = {0};
        // quick memcpy so contents of the message can't be changed by another source
        // not sure if this is necessary tbh...
        memcpy(message, data, length);

        //NOTE: We should hopefully be able to not use a null bytes since every message will be exactly 81 bytes in length

        mxc_i2c_req_t request = {
                // I2C buffer memory address
                .i2c = I2C_INTERFACE,
                // The component id of the recipient
                .addr = recipient,
                // Number of bytes to write to the I2C buffer
                .tx_len = 81,
                .tx_buf = message,
                .rx_len = 0,
                .rx_buf = 0,
                .restart = 0,
                .callback = NULL
        };
        int message_success = MXC_I2C_MasterTransaction(&request);
        // Maybe a error would indicate a malformed packet???, hopefully that never happens..
        if (message_success != E_SUCCESS)
        {
                printf("[Error] %d\n", message_success);
                return -2;
        }

        return 0;
}
