// Precondition, port clock is active
void setAF(GPIO_TypeDef *port,int line,int af)
{
    int index,start;

    af = af&0xF; // Guarantee AF between 0 and 15

    // Informatin for AF Register
    index = line/8; // Register used 0 or 1
    start = 4*(line - index*8); // Position in this register

    // Set GPIO line to AF function
    port->MODER &= (~(1<<(line*2)));
    port->MODER |= (1<<(line*2+1));

    // Set speed
    //port->OSPEEDR |= (3<<(line*2)); // Set high speed

    // Set alternate function number
    port->AFR[index] &= (~(0xF<<start)); // Erase AF information
    port->AFR[index] |= (af<<start); // Set AF number
}

void configureSPI(void)
{
    // SPI1 configuration
    RCC->APB2ENR |= (1<<12); // Activate SPI1 clock
    RCC->APB1ENR |= (1<<14); // Activate SPI2 clock
    RCC->APB1ENR |= (1<<15); // Activate SPI3 clock

    RCC->AHB1ENR |= (1); // Activate GPIO A
    RCC->AHB1ENR |= (1<<1); // Activate GPIO B
    RCC->AHB1ENR |= (1<<2); // Activate GPIO C

    // Configure SPI1
    // Set BR value
    SPI1->CR1 = ((SPI1_BR)&7)<<3;
    // Set CPOL value
    SPI1->CR1 |= (SPI1_CPOL)<<1;
    // Set CPHA value
    SPI1->CR1 |= (SPI1_CPHA);
    // Set DFF value
    SPI1->CR1 |= (SPI1_DFF)<<11;
    // Set SSM and SS
    SPI1->CR1 |= (1<<9)|(1<<8);
    // Activate SPI1 in master mode
    SPI1->CR1 |= (1<<2)|(1<<6);

    // Pins used are PA5, PA6, PA7 at AF05
    setAF(GPIOA,5,5);
    setAF(GPIOA,6,5);
    setAF(GPIOA,7,5);

    // Configure SPI2
    // Set BR value
    SPI2->CR1 = ((SPI2_BR)&7)<<3;
    // Set CPOL value
    SPI2->CR1 |= (SPI2_CPOL)<<1;
    // Set CPHA value
    SPI2->CR1 |= (SPI2_CPHA);
    // Set DFF value
    SPI2->CR1 |= (SPI2_DFF)<<11;
    // Set SSM and SS
    SPI2->CR1 |= (1<<9)|(1<<8);
    // Activate SPI2 in master mode
    SPI2->CR1 |= (1<<2)|(1<<6);

    // Pins used are PB13, PB14, PB15 at AF05
    setAF(GPIOB,13,5);
    setAF(GPIOB,14,5);
    setAF(GPIOB,15,5);

    // Configure SPI3
    // Set BR value
    SPI3->CR1 = ((SPI3_BR)&7)<<3;
    // Set CPOL value
    SPI3->CR1 |= (SPI3_CPOL)<<1;
    // Set CPHA value
    SPI3->CR1 |= (SPI3_CPHA);
    // Set DFF value
    SPI3->CR1 |= (SPI3_DFF)<<11;
    // Set SSM and SS
    SPI3->CR1 |= (1<<9)|(1<<8);
    // Activate SPI3 in master mode
    SPI3->CR1 |= (1<<2)|(1<<6);

    RCC->AHB1ENR |= (1<<2);
    GPIOC->OSPEEDR |= (3<<20)|(3<<22)|(3<<24);

    // Pins used are PC10, PC11, PC12 at AF06
    setAF(GPIOC,10,6);
    setAF(GPIOC,11,6);
    setAF(GPIOC,12,6);

    //GPIOC->OSPEEDR |= (3<<20)|(3<<22)|(3<<24);

    // Initialize CS lines
    dacCS = 1;
    ftdiCS = 1;
}

