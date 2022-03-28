#include "sn74hc595.h"

// Shift Register Code ////////////
// SPI &setSPIShPo() {
//     static SPI shPo(PC_12, PC_11, PC_10);
//     return shPo;
// }

// DigitalOut &setCsnShPo() {
//     static DigitalOut csn_shpo(PB_12, 0);
//     return csn_shpo;
// }

void latchSignal() {
    CSn_Enable();
    wait_ns(PULSE_DURATION);
    CSn_Disable();
}

void shiftOut(uint32_t data_tx, uint32_t *data_rx) {
    // *data_rx = shPo.write(data_tx);
    SPI4_Transmit(data_tx);
    latchSignal();
}
//////////////////////////////////