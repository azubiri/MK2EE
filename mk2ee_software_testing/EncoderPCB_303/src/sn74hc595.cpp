#include "sn74hc595.hpp"

void Sn74hc595::latchSignal() {

    csn_shpo = 1;
    wait_ns(PULSE_DURATION_NS);
    csn_shpo = 0;

}

Sn74hc595::Sn74hc595() : shPo(PC_12, PC_11, PC_10), csn_shpo(PB_12, 0){
    shPo.format(8, 0);
    shPo.frequency(1000000);
}

Sn74hc595::~Sn74hc595() {
    
}

void Sn74hc595::shiftOut(uint16_t data_tx) {

    shPo.write(data_tx);
    latchSignal();
    
}