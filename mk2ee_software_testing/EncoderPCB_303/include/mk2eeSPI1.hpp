#ifndef MK2EESPI1_HPP
#define MK2EESPI1_HPP

#include "mk2eeSPI.hpp"

#define MAX_FREQ_F303RE_MHZ 72000

class Mk2eeSPI1 : public Mk2eeSPI {

private:
    void print_config_spi() override;
    void init_clock_spi() override;
    void csn_sw_hw_spi(bool sw_hw) override;
    void master_slave_spi(bool master) override;
    void enable_spi() override;
    void desable_spi() override;

public:
    Mk2eeSPI1();
    ~Mk2eeSPI1();
    void format_spi(bool eight_bits) override;
    void frequency_spi(int freq) override;
    void polarity_phase_spi(int mode) override;
    int receive_spi() override;
    void transmit_spi() override;
};

#endif