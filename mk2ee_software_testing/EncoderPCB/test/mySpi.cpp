#include "mySpi.h"

// void printSPI5Config() {
//     printf("Clocks activation:\n");
//     printf("RCC->APB2ENR= %x: %x\n", &RCC->APB2ENR, RCC->APB2ENR);
//     printf("GPIOs activation:\n");
//     printf("RCC->AHB1ENR= %x: %x\n", &RCC->AHB1ENR, RCC->AHB1ENR);
//     printf("Moder:\n");
//     printf("GPIOA->MODER= %x: %x\n", &GPIOA->MODER, GPIOA->MODER);
//     printf("GPIOB->MODER= %x: %x\n", &GPIOB->MODER, GPIOB->MODER);
//     printf("Alternative Functions:\n");
//     printf("GPIOA->AFR[1]= %x: %x\n", &GPIOA->AFR[1], GPIOA->AFR[1]);
//     printf("GPIOB->AFR[0]= %x: %x\n", &GPIOB->AFR[0], GPIOB->AFR[0]);
//     printf("SPI configuration:\n");
//     printf("SPI5->CR1= %x: %x\n\n", &SPI5->CR1, SPI5->CR1);
// }

void mySPI5() {
    // SPI5 Clock is enabled
    RCC->APB2ENR = setBit((RCC->APB2ENR), RCC_APB2ENR_SPI5EN_Pos);
    // GPIO activation
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOAEN_Pos;
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOBEN_Pos;

    // Clock frequency
    // Maximum frequencies:
    // AS5047=10MHz
    // STM32F411RE_APB2=100MHz
    // SN74HC595_3.3V=5MHz
    // SPI5->CR1 = SPI5->CR1 | SPI_CR1_BR_0; // Frequency at 100MHz/128=781.25KHz
    SPI5->CR1 = SPI5->CR1 | SPI_CR1_BR_1;
    SPI5->CR1 = SPI5->CR1 | SPI_CR1_BR_2;

    // Polarity and Phase
    SPI5->CR1 = clearBit((SPI5->CR1), SPI_CR1_CPOL_Pos); // CPOL = 0
    SPI5->CR1 = setBit((SPI5->CR1), SPI_CR1_CPHA_Pos); // CPHA = 1

    // Data Frame (8 or 16) bits
    SPI5->CR1 = setBit( (SPI5->CR1) , SPI_CR1_DFF_Pos); // Frame of 16 bits
    
    // SSL is controled by hardware or software
    SPI5->CR1 = setBit( (SPI5->CR1) , SPI_CR1_SSM_Pos); // The value is replaced by SSI
    SPI5->CR1 = setBit((SPI5->CR1), SPI_CR1_SSI_Pos); // SSL is forced by GPIO value

    // PB7 is selected as nCS by software
    // DISABLE;
    // (GPIOB -> ODR) = setBit((GPIOB -> ODR), GPIO_ODR_OD7_Pos);
    // ENABLE;

    // Microcontroler is set up as master or slave?
    SPI5->CR1 = setBit((SPI5->CR1), SPI_CR1_MSTR_Pos); // Microcontroller is selected as Master
    
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER12_1; // PA12 - MISO
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER0_1; // PB0 - SCK

    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED12_0; // PA12 - 100 MHz
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED12_1;
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED0_0; // PB0 - 100 MHz
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED0_1;

    // SPI5
    GPIOA->AFR[1] = GPIOA->AFR[1] | GPIO_AFRH_AFRH4_1; // PA12 - MISO
    GPIOA->AFR[1] = GPIOA->AFR[1] | GPIO_AFRH_AFRH4_2;
    GPIOB->AFR[0] = GPIOB->AFR[0] | GPIO_AFRL_AFRL0_1; // PB0 - SCK
    GPIOB->AFR[0] = GPIOB->AFR[0] | GPIO_AFRL_AFRL0_2;

    // At this point we enable SPI
    SPI5->CR1 = setBit((SPI5->CR1), SPI_CR1_SPE_Pos); // SPI2 peripheric is enabled
    
    
}

int SPI5_Recieve() {

    //wait_ns(700);
    int data;
    while((SPI5->SR) & SPI_SR_BSY) {

    }

    SPI5->DR = 0;

    //wait_us(10);
    while(!((SPI5->SR) & SPI_SR_RXNE)) {

    }

    data = SPI5->DR;
    
    //wait_ns(700);
    return data;
}

void mySPI4() {
    // SPI5 Clock is enabled
    RCC->APB2ENR = setBit((RCC->APB2ENR), RCC_APB2ENR_SPI4EN_Pos);
    // GPIO activation
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOAEN_Pos;
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOBEN_Pos;

    // Clock frequency
    // Maximum frequencies:
    // AS5047=10MHz
    // STM32F411RE_APB2=100MHz
    // SN74HC595_3.3V=5MHz
    // SPI5->CR1 = SPI5->CR1 | SPI_CR1_BR_0; // Frequency at 100MHz/128=781.25KHz
    SPI4->CR1 = SPI4->CR1 | SPI_CR1_BR_1;
    SPI4->CR1 = SPI4->CR1 | SPI_CR1_BR_2;

    // Polarity and Phase
    SPI4->CR1 = clearBit((SPI4->CR1), SPI_CR1_CPOL_Pos); // CPOL = 0
    SPI4->CR1 = clearBit((SPI4->CR1), SPI_CR1_CPHA_Pos); // CPHA = 0

    // Data Frame (8 or 16) bits
    SPI4->CR1 = clearBit( (SPI4->CR1) , SPI_CR1_DFF_Pos); // Frame of 8 bits
    
    // SSL is controled by hardware or software
    SPI4->CR1 = setBit( (SPI4->CR1) , SPI_CR1_SSM_Pos); // The value is replaced by SSI
    SPI4->CR1 = setBit((SPI4->CR1), SPI_CR1_SSI_Pos); // SSL is forced by GPIO value

    // PB7 is selected as nCS by software
    // DISABLE;
    // (GPIOB -> ODR) = setBit((GPIOB -> ODR), GPIO_ODR_OD7_Pos);
    // ENABLE;

    // Microcontroler is set up as master or slave?
    SPI4->CR1 = setBit((SPI4->CR1), SPI_CR1_MSTR_Pos); // Microcontroller is selected as Master
    
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER1_1; // PA1 - MOSI
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER13_1; // PB13 - SCK

    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED1_0; // PA1 - 100 MHz
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED1_1;
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED13_0; // PB13 - 100 MHz
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED13_1;

    // SPI4
    GPIOA->AFR[0] = GPIOA->AFR[0] | GPIO_AFRL_AFRL1_0; // PA1 - MOSI
    GPIOA->AFR[0] = GPIOA->AFR[0] | GPIO_AFRL_AFRL1_2;
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFRH0_1; // PB13 - SCK
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFRH0_2;

    // At this point we enable SPI
    SPI4->CR1 = setBit((SPI4->CR1), SPI_CR1_SPE_Pos); // SPI4 peripheric is enabled  
    
}

void SPI4_Transmit(uint32_t data) {

    while(!((SPI4->SR) & SPI_SR_TXE)) {

    }
    SPI5->DR = data;
}

void CSn_Enable() {
    GPIOB->BSRR = setBit((GPIOB->BSRR), GPIO_BSRR_BR12_Pos);
}
void CSn_Disable() {
    GPIOB->BSRR = clearBit((GPIOB->BSRR), GPIO_BSRR_BR12_Pos);
}