#include "mk2eeSPI.hpp"

void Mk2eeSPI::init_clock_gpio(char gpio) {

    switch (gpio) {
    // GPIOA Clock is enabled
    case 'A':
        RCC->AHBENR = setBit(RCC->AHBENR, RCC_AHBENR_GPIOAEN_Pos);
        break;
    // GPIO Clock is enabled
    case 'B':
        RCC->AHBENR = setBit(RCC->AHBENR, RCC_AHBENR_GPIOBEN_Pos);
        break;
    // GPIO Clock is enabled
    case 'C':
        RCC->AHBENR = setBit(RCC->AHBENR, RCC_AHBENR_GPIOCEN_Pos);
        break;
    // This GPIO is not in the list
    default:
        break;
    }

}

void Mk2eeSPI::gpio_moder_af(GPIO_TypeDef *gpio, int pin_number) {
    gpio->MODER = clearBit(gpio->MODER, (2*pin_number));
    gpio->MODER = setBit(gpio->MODER, (2*pin_number) + 1);
}

void Mk2eeSPI::gpio_pin_speed(GPIO_TypeDef *gpio, int pin_number, int pin_speed) {

    switch (pin_speed) {
    // Low speed
    case 0:
        gpio->OSPEEDR = clearBit(gpio->OSPEEDR, (2*pin_number));
        gpio->OSPEEDR = clearBit(gpio->OSPEEDR, (2*pin_number) + 1);
        break;
    // Medium speed
    case 1:
        gpio->OSPEEDR = setBit(gpio->OSPEEDR, (2*pin_number));
        gpio->OSPEEDR = clearBit(gpio->OSPEEDR, (2*pin_number) + 1);
        break;
    // High speed
    default:
        gpio->OSPEEDR = setBit(gpio->OSPEEDR, (2*pin_number));
        gpio->OSPEEDR = setBit(gpio->OSPEEDR, (2*pin_number) + 1);
        break;
    }

}

void Mk2eeSPI::gpio_set_af(GPIO_TypeDef *gpio, int pin_number, int af) {
    
    // If the pin line is lower than the 8th, index will be 0
    // If the pin line is higher than the 8th, index will be 1
    uint8_t index = pin_number / 8;
    uint8_t start = 4*pin_number - 8*index;
    // If the pin line is lower than the 8th, the AF low register is set
    // If the pin line is higher than the 8th, the AF high register is set 
    gpio->AFR[index] = gpio->AFR[index] & ~(0xF << start); // Bits of the pin from AF register are erased
    gpio->AFR[index] = gpio->AFR[index] | (af << start); // Bits of the pin from AF register are set

}

void Mk2eeSPI::polarity_phase(SPI_TypeDef *spi_peripheral, int mode) {
    // Polarity and Phase
    switch (mode) {
    case 0:
        spi_peripheral->CR1 = clearBit((spi_peripheral->CR1), SPI_CR1_CPOL_Pos); // CPOL = 0
        spi_peripheral->CR1 = clearBit((spi_peripheral->CR1), SPI_CR1_CPHA_Pos); // CPHA = 0
        break;

    case 1:
        spi_peripheral->CR1 = clearBit((spi_peripheral->CR1), SPI_CR1_CPOL_Pos); // CPOL = 0
        spi_peripheral->CR1 = setBit((spi_peripheral->CR1), SPI_CR1_CPHA_Pos); // CPHA = 1
        break;

    case 2:
        spi_peripheral->CR1 = setBit((spi_peripheral->CR1), SPI_CR1_CPOL_Pos); // CPOL = 1
        spi_peripheral->CR1 = clearBit((spi_peripheral->CR1), SPI_CR1_CPHA_Pos); // CPHA = 0
        break;

    case 3:
        spi_peripheral->CR1 = setBit((spi_peripheral->CR1), SPI_CR1_CPOL_Pos); // CPOL = 1
        spi_peripheral->CR1 = setBit((spi_peripheral->CR1), SPI_CR1_CPHA_Pos); // CPHA = 1
        break;

    default:
        break;
    }
    
}

// Max. Frequency: 72 MHz
void Mk2eeSPI::frequency(SPI_TypeDef *spi_peripheral, int freq) {
    // Frequency at 72MHz/256=281.25KHz
    if ( freq < (MAX_FREQ_F303RE_KHZ / 128) ) {
        printf("Menos\n");
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_0;
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_1;
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_2;
    }
    // Frequency at 72MHz/128=562.5KHz
    else if ( (freq >= (MAX_FREQ_F303RE_KHZ / 128)) && (freq < (MAX_FREQ_F303RE_KHZ / 64)) ) {
        printf("Mas\n");
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_0);
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_1;
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_2;
    }
    // Frequency at 72MHz/64=1.125MHz
    else if ( (freq >= (MAX_FREQ_F303RE_KHZ / 64)) && (freq < (MAX_FREQ_F303RE_KHZ / 32)) ) {
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_0;
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_1);
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_2;
    }
    // Frequency at 72MHz/32=2.25MHz
    else if ( (freq >= (MAX_FREQ_F303RE_KHZ / 32)) && (freq < (MAX_FREQ_F303RE_KHZ / 16)) ) {
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_0);
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_1);
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_2;
    }
    // Frequency at 72MHz/16=4.5MHz
    else if ( (freq >= (MAX_FREQ_F303RE_KHZ / 16)) && (freq < (MAX_FREQ_F303RE_KHZ / 8)) ) {
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_0;
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_1;
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_2);
    }
    // Frequency at 72MHz/8=9MHz
    else if ( (freq >= (MAX_FREQ_F303RE_KHZ / 8)) && (freq < (MAX_FREQ_F303RE_KHZ / 4)) ) {
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_0);
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_1;
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_2);
    }
    // Frequency at 72MHz/4=18MHz
    else if ( (freq >= (MAX_FREQ_F303RE_KHZ / 4)) && (freq < (MAX_FREQ_F303RE_KHZ / 2)) ) {
        spi_peripheral->CR1 = spi_peripheral->CR1 | SPI_CR1_BR_0;
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_1);
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_2);
    }
    // Frequency at 72MHz/2=36MHz
    else if ( freq >= (MAX_FREQ_F303RE_KHZ / 2) ) {
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_0);
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_1);
        spi_peripheral->CR1 = spi_peripheral->CR1 & ~(SPI_CR1_BR_2);
    }
}

// SSL is controled by software or hardware
void Mk2eeSPI::csn_sw_hw(SPI_TypeDef *spi_peripheral, bool sw_option) {
    
    if (sw_option) {
        SPI1->CR1 = setBit( (spi_peripheral->CR1), SPI_CR1_SSM_Pos);
        SPI1->CR1 = setBit( (spi_peripheral->CR1), SPI_CR1_SSI_Pos);
    }
    else {
        SPI1->CR1 = clearBit( (spi_peripheral->CR1), SPI_CR1_SSM_Pos);
        SPI1->CR1 = clearBit( (spi_peripheral->CR1), SPI_CR1_SSI_Pos);
    }

}

// Data Frame (8 or 16) bits
void Mk2eeSPI::format(SPI_TypeDef *spi_peripheral, bool eight_bits) {
    
    // 8 bits format
    if (eight_bits) {
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_0; 
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_1;
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_2;
        spi_peripheral->CR2 = spi_peripheral->CR2 & ~(SPI_CR2_DS_3);
    }
    else {
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_0; 
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_1;
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_2;
        spi_peripheral->CR2 = spi_peripheral->CR2 | SPI_CR2_DS_3;
    }
    
}

// Microcontroler is set up as master or slave
void Mk2eeSPI::master_slave(SPI_TypeDef *spi_peripheral, bool master) {
    // Microcontroller is selected as Master
    if(master) {
        spi_peripheral->CR1 = setBit((spi_peripheral->CR1), SPI_CR1_MSTR_Pos);
    }
    // Microcontroller is selected as Slave
    else {
        spi_peripheral->CR1 = clearBit((spi_peripheral->CR1), SPI_CR1_MSTR_Pos);
    }
}

void Mk2eeSPI::enable(SPI_TypeDef *spi_peripheral) {
    spi_peripheral->CR1 = setBit((spi_peripheral->CR1), SPI_CR1_SPE_Pos);
}

void Mk2eeSPI::desable(SPI_TypeDef *spi_peripheral) {
    spi_peripheral->CR1 = clearBit((spi_peripheral->CR1), SPI_CR1_SPE_Pos);
}

int Mk2eeSPI::receive(SPI_TypeDef *spi_peripheral) {

    int data;

    while((spi_peripheral->SR) & SPI_SR_BSY);

    spi_peripheral->DR = 0;

    while(!((spi_peripheral->SR) & SPI_SR_RXNE));

    data = spi_peripheral->DR;
    
    return data;
}

void Mk2eeSPI::transmit(SPI_TypeDef *spi_peripheral) {
    // TODO: Define transmit function
}