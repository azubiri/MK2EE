#ifndef SN74HC595_H
#define SN74HC595_H

#include <mbed.h>

// todo: ns
#define PULSE_DURATION 25

void setUpSpi4();
void latchSignal();
void shiftOut(uint16_t data_tx);

#endif