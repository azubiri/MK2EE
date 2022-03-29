#include "sn74hc595.hpp"

SPI shPo(PC_12, PC_11, PC_10); // SPI4
DigitalOut csn_shpo(PB_12, 0);

// SPI Shift Register configuration
void setUpSpi() {
    shPo.format(8, 0);
    shPo.frequency(1000000);
}

void latchSignal() {
    csn_shpo = 1;
    wait_ns(PULSE_DURATION);
    csn_shpo = 0;
}

void shiftOut(uint16_t data_tx, uint16_t *data_rx ) {
    *data_rx = shPo.write(data_tx);
    latchSignal();
}