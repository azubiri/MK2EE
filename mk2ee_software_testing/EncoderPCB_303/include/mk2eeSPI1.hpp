#ifndef MK2EESPI1_HPP
#define MK2EESPI1_HPP

#include "mk2eeSPI.hpp"

#define MAX_FREQ_F303RE_MHZ 72000

class Mk2eeSPI1 : public Mk2eeSPI {

private:
    void print_config_spi();
    void init_clock_spi();
    void csn_sw_hw_spi(bool sw_hw);
    void master_slave_spi(bool master);
    void enable_spi();
    void desable_spi();

public:
    Mk2eeSPI1();
    ~Mk2eeSPI1();
    void format_spi(bool eight_bits);
    void frequency_spi(int freq);
    void polarity_phase_spi(int mode);
    int receive_spi();
    void transmit_spi();
};

#endif