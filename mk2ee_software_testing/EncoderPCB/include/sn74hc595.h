#include <mbed.h>
#include "mySpi.h"

// Pulse duration SRCLK or RCLK high or low (in nanoseconds) 
#define PULSE_DURATION 25

SPI &setSPI();
DigitalOut &setCsnShPo();
void latchSignal();
void shiftOut(uint32_t data_tx, uint32_t *data_rx);