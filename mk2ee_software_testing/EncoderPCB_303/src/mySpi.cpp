#include "mySpi.hpp"

void printSPIConfig() {
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

void mySPI1() {
    // SPI1 Clock is enabled
    RCC->APB2ENR = setBit((RCC->APB2ENR), RCC_APB2ENR_SPI1EN_Pos);
    // GPIO activation
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOAEN_Pos;
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOBEN_Pos;
    RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOCEN_Pos;

    // Clock frequency
    // Maximum frequencies:
    // AS5047=10MHz
    // STM32F303RE_APB2=72MHz
    // SN74HC595_3.3V=5MHz
    // SPI1->CR1 = SPI1->CR1 | SPI_CR1_BR_0; // Frequency at 72MHz/32=562.5KHz
    SPI1->CR1 = SPI1->CR1 | SPI_CR1_BR_1;
    SPI1->CR1 = SPI1->CR1 | SPI_CR1_BR_2;

    // Polarity and Phase
    SPI1->CR1 = clearBit((SPI1->CR1), SPI_CR1_CPOL_Pos); // CPOL = 0
    SPI1->CR1 = setBit((SPI1->CR1), SPI_CR1_CPHA_Pos); // CPHA = 1

    // Data Frame (8 or 16) bits
    SPI1->CR2 = SPI1->CR2 | SPI_CR2_DS_0; // Frame of 16 bits
    SPI1->CR2 = SPI1->CR2 | SPI_CR2_DS_1;
    SPI1->CR2 = SPI1->CR2 | SPI_CR2_DS_2;
    SPI1->CR2 = SPI1->CR2 | SPI_CR2_DS_3;
    
    // SSL is controled by hardware or software
    SPI1->CR1 = setBit( (SPI1->CR1) , SPI_CR1_SSM_Pos); // The value is replaced by SSI
    SPI1->CR1 = setBit((SPI1->CR1), SPI_CR1_SSI_Pos); // SSL is forced by GPIO value

    // PB7 is selected as nCS by software
    // DISABLE;
    // (GPIOB -> ODR) = setBit((GPIOB -> ODR), GPIO_ODR_OD7_Pos);
    // ENABLE;

    // Microcontroler is set up as master or slave?
    SPI1->CR1 = setBit((SPI1->CR1), SPI_CR1_MSTR_Pos); // Microcontroller is selected as Master
    
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER6_1; // PA6 - MISO
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER5_1; // PA5 - SCK

    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDER_OSPEEDR6_0; // PA6 - 100 MHz
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDER_OSPEEDR6_1;
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDER_OSPEEDR0_0; // PB5 - 100 MHz
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDER_OSPEEDR0_1;

    // SPI1
    GPIOA->AFR[0] = setBit(GPIOA->AFR[0], GPIO_AFRL_AFRL6_Pos); // PA6 - MISO
    GPIOA->AFR[0] = setBit(GPIOA->AFR[0], (GPIO_AFRL_AFRL6_Pos+2UL));
    GPIOA->AFR[0] = setBit(GPIOA->AFR[0], GPIO_AFRL_AFRL5_Pos); // PA5 - SCK
    GPIOA->AFR[0] = setBit(GPIOA->AFR[0], (GPIO_AFRL_AFRL5_Pos+2UL));

    // At this point we enable SPI
    SPI1->CR1 = setBit((SPI1->CR1), SPI_CR1_SPE_Pos); // SPI1 peripheric is enabled
}

int SPI_Recieve() {

    //wait_ns(700);
    int data;
    while((SPI1->SR) & SPI_SR_BSY) {

    }

    SPI1->DR = 0;

    //wait_us(10);
    while(!((SPI1->SR) & SPI_SR_RXNE)) {

    }

    data = SPI1->DR;
    
    //wait_ns(700);
    return data;
}