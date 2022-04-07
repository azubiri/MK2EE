#include "mk2eeSPI1.hpp"

Mk2eeSPI1::Mk2eeSPI1() {
    print_config_spi();
    ///////////////////////////////
    // GPIO registers configuration
    ///////////////////////////////
    gpio_moder_af(GPIOA, 6); // PA6 - MISO
    gpio_moder_af(GPIOA, 5); // PA5 - SCK

    gpio_pin_speed(GPIOA, 6, 3); // PA6 - 100 MHz
    gpio_pin_speed(GPIOA, 5, 3); // PA5 - 100 MHz

    // SPI1 AF
    gpio_set_af(GPIOA, 6, 5); // PA6 is set as MISO function for SPI1
    gpio_set_af(GPIOA, 5, 5); // PA5 is set as SCK function for SPI1

    // Enable GPIOA
    init_clock_gpio('A');
    ///////////////////////////////

    ///////////////////////////////
    // SPI1 registers configuration
    ///////////////////////////////
    init_clock_spi();
    
    // Clock frequency
    frequency_spi(1000u); // set 1 MHz but the actual frequency is set is 562.5KHz

    polarity_phase_spi(1);
    
    csn_sw_hw_spi(true);

    master_slave_spi(true);

    format_spi(false);

    // At this point we enable SPI
    enable_spi();
    ///////////////////////////////
    print_config_spi();
}

Mk2eeSPI1::~Mk2eeSPI1() {
    desable_spi();
}

void Mk2eeSPI1::print_config_spi() {
    printf("Clocks activation:\n");
    printf("RCC->APB2ENR= %x: %x\n", &RCC->APB2ENR, RCC->APB2ENR);
    printf("GPIOs activation:\n");
    printf("RCC->AHBENR= %x: %x\n", &RCC->AHBENR, RCC->AHBENR);
    printf("Moder:\n");
    printf("GPIOA->MODER= %x: %x\n", &GPIOA->MODER, GPIOA->MODER);
    printf("Alternative Functions:\n");
    printf("GPIOA->AFR[0]= %x: %x\n", &GPIOA->AFR[0], GPIOA->AFR[0]);
    printf("SPI configuration:\n");
    printf("SPI1->CR1= %x: %x\n\n", &SPI1->CR1, SPI1->CR1);
    printf("SPI1->CR2= %x: %x\n\n", &SPI1->CR2, SPI1->CR2);
}

void Mk2eeSPI1::init_clock_spi() {
    // SPI1 Clock is enabled
    RCC->APB2ENR = setBit((RCC->APB2ENR), RCC_APB2ENR_SPI1EN_Pos);
}

void Mk2eeSPI1::format_spi(bool eight_bits) {
    format(SPI1, eight_bits);
}

void Mk2eeSPI1::frequency_spi(int freq) {
    frequency(SPI1, freq);
}

void Mk2eeSPI1::polarity_phase_spi(int mode) {
    polarity_phase(SPI1, mode);
}

void Mk2eeSPI1::csn_sw_hw_spi(bool sw_hw) {
    csn_sw_hw(SPI1, sw_hw);
}

void Mk2eeSPI1::master_slave_spi(bool master) {
    master_slave(SPI1, master);
}

void Mk2eeSPI1::enable_spi() {
    enable(SPI1);
}

void Mk2eeSPI1::desable_spi() {
    desable(SPI1);
}

int Mk2eeSPI1::receive_spi() {
    return receive(SPI1);
}

void Mk2eeSPI1::transmit_spi() {
    transmit(SPI1);
}