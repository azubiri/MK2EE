#ifndef SN74HC595_HPP
#define SN74HC595_HPP

#include <mbed.h>

// todo: ns
#define PULSE_DURATION_NS 25

class Sn74hc595 {

    private:
        
        SPI shPo; // SPI4
        DigitalOut csn_shpo;

        void latchSignal();

    public:

        Sn74hc595();

        ~Sn74hc595();

        void shiftOut(uint16_t data_tx);

};

#endif