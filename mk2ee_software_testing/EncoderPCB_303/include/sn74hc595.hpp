#ifndef SN74HC595_H
#define SN74HC595_H

#include "mk2ee.hpp"
#define PULSE_DURATION 25

void setUpSpi();
void latchSignal();
void shiftOut(uint16_t data_tx, uint16_t *data_rx );

#endif