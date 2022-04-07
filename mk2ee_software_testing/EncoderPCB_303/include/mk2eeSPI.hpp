#ifndef MK2EESPI_HPP
#define MK2EESPI_HPP

#include <mbed.h>
#include "mk2ee_definitions.hpp"

#define MAX_FREQ_F303RE_KHZ 72000

class Mk2eeSPI {

private:

protected:

    void init_clock_gpio(char gpio);
    void gpio_moder_af(GPIO_TypeDef *gpio, int pin_number);
    void gpio_pin_speed(GPIO_TypeDef *gpio, int pin_number, int pin_speed);
    void gpio_set_af(GPIO_TypeDef *gpio, int pin_number, int af);
    void format(SPI_TypeDef *spi_peripheral, bool eight_bits);
    void frequency(SPI_TypeDef *spi_peripheral, int freq);
    void polarity_phase(SPI_TypeDef *spi_peripheral, int mode);
    void csn_sw_hw(SPI_TypeDef *spi_peripheral, bool sw_hw);
    void master_slave(SPI_TypeDef *spi_peripheral, bool master);
    void enable(SPI_TypeDef *spi_peripheral);
    void desable(SPI_TypeDef *spi_peripheral);
    int receive(SPI_TypeDef *spi_peripheral);
    void transmit(SPI_TypeDef *spi_peripheral);

    virtual void init_clock_spi() = 0;
    virtual void print_config_spi() = 0;
    virtual void format_spi(bool eight_bits) = 0;
    virtual void frequency_spi(int freq);
    virtual void polarity_phase_spi(int mode) = 0;
    virtual void csn_sw_hw_spi(bool sw_hw) = 0;
    virtual void master_slave_spi(bool master) = 0;
    virtual void enable_spi() = 0;
    virtual void desable_spi() = 0;
    virtual int receive_spi() = 0;
    virtual void transmit_spi() = 0;

};

#endif