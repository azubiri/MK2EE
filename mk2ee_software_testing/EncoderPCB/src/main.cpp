#include <mbed.h>
#include <chrono>

#define PULSE_DURATION 25 // Pulse duration SRCLK or RCLK high or low (in nanoseconds) 

#define modifyBitPos(n, p, b) ((n & ~(1 << p)) | (b << p)) // Set or clear a bit given a position
#define setBit(n, p) (n | (1 << p))
#define clearBit(n, p) (n & ~(1 << p))
#define LED1Red     1
#define LED1Green   2
#define LED1Blue    3
#define LED2Blue    4
#define LED2Green   5
#define LED2Red     6
#define SH_PO_CSn   7

typedef enum {
    AS_FLAG_PARITY = 0x8000,
    AS_FLAG_READ = 0x4000,
} As5047Flag;

typedef enum {
    AS_CMD_NOP = 0x0000,
    AS_CMD_ERROR = 0x0001 | AS_FLAG_READ,       // Reads error register of sensor and clear error flags
    AS_CMD_DIAGNOSTICS = 0x3FFD |  AS_FLAG_READ, // Reads automatic gain control and diagnostics info
    AS_CMD_MAGNITUDE = 0x3FFE | AS_FLAG_READ,
    
    AS_CMD_ANGLE = 0x3FFF| AS_FLAG_PARITY | AS_FLAG_READ,
} As5047Command;

// Masks for bits in the result of the AS_CMD_DIAGNOSTICS command
typedef enum {
    AS_DIAG_CORDIC_OVERFLOW = 0x0200,
    AS_DIAG_HIGH_MAGNETIC = 0x0400,
    AS_DIAG_LOW_MAGNETIC = 0x0800,
} As5047Diagnostics;



//SPI encoder(PA_7, PA_6, PA_5); // SPI5

SPI shPo(PC_12, PC_11, PC_10); // SPI4
DigitalOut csn_shpo(PB_12, 0);
// Shift Register transmitter and receiver
uint16_t data_tx;
uint16_t data_rx;

static UnbufferedSerial pc(USBTX, USBRX, 9600); // tx, rx

int velocity = 10000; // 10 ms

static inline int modifyBit(int n, int p, int b) {
    int mask = 1 << p;
    return ((n & ~mask) | (b << p));
}

void portsInit() {
    // SPI5 Clock is enabled
    RCC->APB2ENR = setBit((RCC->APB2ENR), RCC_APB2ENR_SPI5EN_Pos);
    // GPIO activation
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOAEN_Pos;
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOBEN_Pos;
    

    /***************************************************************
    // Mode Registers Settings: Alternate Functions
    ***************************************************************/
    /*
    // SPI1
    DISABLE;
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODE7_1; // PA7 - MOSI
    ENABLE;
    DISABLE;
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODE5_1; // PA5 - SCK
    ENABLE;
    
    // SPI4
    DISABLE;
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODE1_1; // PA1 - MOSI
    ENABLE;
    DISABLE;
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODE13_1; // PB13 - SCK
    ENABLE;
    */
    // SPI5
    GPIOA->MODER = GPIOA->MODER | GPIO_MODER_MODER12_1; // PA12 - MISO
    GPIOB->MODER = GPIOB->MODER | GPIO_MODER_MODER0_1; // PB0 - SCK
    
    /***************************************************************
    // Alternate Functions Settings: SPIs
    ***************************************************************/
    /*
    // SPI1
    DISABLE;
    GPIOA->AFR[0] = GPIOA->AFR[0] | GPIO_AFRL_AFRL7_0 | GPIO_AFRL_AFRL7_2; // PA7 - MOSI
    ENABLE;
    DISABLE;
    GPIOA->AFR[0] = GPIOA->AFR[0] | GPIO_AFRL_AFRL5_0 | GPIO_AFRL_AFRL5_2; // PA5 - SCK
    ENABLE;
    */
    /*
    // SPI4
    DISABLE;
    GPIOA->AFR[0] = GPIOA->AFR[0] | GPIO_AFRL_AFRL1_0 | GPIO_AFRL_AFRL1_2; // PA1 - MOSI
    ENABLE;
    DISABLE;
    GPIOB->AFR[1] = GPIOB->AFR[1] | GPIO_AFRH_AFRH5_1 | GPIO_AFRH_AFRH5_2; // PB13 - SCK
    ENABLE;
    */
    // SPI5
    GPIOA->AFR[1] = GPIOA->AFR[1] | GPIO_AFRH_AFRH4_1; // PA12 - MISO
    GPIOA->AFR[1] = GPIOA->AFR[1] | GPIO_AFRH_AFRH4_2;
    GPIOB->AFR[0] = GPIOB->AFR[0] | GPIO_AFRL_AFRL0_1; // PB0 - SCK
    GPIOB->AFR[0] = GPIOB->AFR[0] | GPIO_AFRL_AFRL0_2;
    
    /***************************************************************
    // Speed Configuration
    ***************************************************************/
   // SPI5
   /*
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED12_0; // PA12 - 100 MHz
    GPIOA->OSPEEDR = GPIOA->OSPEEDR | GPIO_OSPEEDR_OSPEED12_1;
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED0_0; // PB0 - 100 MHz
    GPIOB->OSPEEDR = GPIOB->OSPEEDR | GPIO_OSPEEDR_OSPEED0_1;
    */
}

void printSPIConfig() {
    printf("Clocks activation:\n");
    printf("RCC->APB2ENR= %x: %x\n", &RCC->APB2ENR, RCC->APB2ENR);
    printf("GPIOs activation:\n");
    printf("RCC->AHB1ENR= %x: %x\n", &RCC->AHB1ENR, RCC->AHB1ENR);
    printf("Moder:\n");
    printf("GPIOA->MODER= %x: %x\n", &GPIOA->MODER, GPIOA->MODER);
    printf("GPIOB->MODER= %x: %x\n", &GPIOB->MODER, GPIOB->MODER);
    printf("Alternative Functions:\n");
    printf("GPIOA->AFR[1]= %x: %x\n", &GPIOA->AFR[1], GPIOA->AFR[1]);
    printf("GPIOB->AFR[0]= %x: %x\n", &GPIOB->AFR[0], GPIOB->AFR[0]);
    printf("SPI configuration:\n");
    printf("SPI5->CR1= %x: %x\n\n", &SPI5->CR1, SPI5->CR1);
}

void mySPI() {
    // SPI5 Clock is enabled
    RCC->APB2ENR = setBit((RCC->APB2ENR), RCC_APB2ENR_SPI5EN_Pos);
    // GPIO activation
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOAEN_Pos;
    RCC->AHB1ENR = RCC->AHB1ENR | RCC_AHB1ENR_GPIOBEN_Pos;

    // Clock frequency
    // Maximum frequencies:
    // AS5047=10MHz
    // STM32F411RE_APB2=50MHz
    // SN74HC595_3.3V=5MHz
    // SPI5->CR1 = SPI5->CR1 | SPI_CR1_BR_0; // Frequency at 100MHz/32=1.56MHz
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

int SPI_Recieve() {

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

int myWrite(int data) {
    // Write data to be sent
    printf("SPI5->SR= %x: %x\n", &SPI5->SR, SPI5->SR);
    SPI5->DR = data;

    wait_us(100);
    while(!(SPI5->SR & SPI_SR_TXE));
    printf("SPI5->SR= %x: %x\n", &SPI5->SR, SPI5->SR);
    // Read received data
    int ret = SPI5->DR;
    wait_us(100);
    while(!(SPI5->SR & SPI_SR_RXNE));
    printf("SPI5->SR= %x: %x\n\n", &SPI5->SR, SPI5->SR);
    return ret;
}


// Shift Register Code ////////////
void latchSignal() {
    csn_shpo = 1;
    wait_ns(PULSE_DURATION);
    csn_shpo = 0;
}

void shiftOut(uint16_t data_tx, uint16_t *data_rx ) {
    *data_rx = shPo.write(data_tx);
    latchSignal();
}
//////////////////////////////////

// Encoder Code //////////////////
int mask(int sensor_result)
{
    return sensor_result & 0x3FFF; // return lowest 14-bits
}

float degrees(int sensor_result)
{
    float conversor, angle;
    conversor = 360.0 / 16384.0;
    angle = mask(sensor_result);
    return angle * conversor;
}

bool parity_check(int sensor_result)
{
    // Use the LSb of result to keep track of parity (0 = even, 1 = odd)
    int result = sensor_result;
    
    for(int i = 1; i <= 15; ++i) {
        sensor_result >>= 1;
        // pc.printf("Sensor result: 0x%04X\n", sensor_result);
        result ^= sensor_result;
        // pc.printf("Result: 0x%04X\n", result);
    }
    // Parity should be even
    return (result & 0x0001) == 0;
}
//////////////////////////////////


void default_shiftRegister() {
    
    data_tx = clearBit(data_tx, LED1Red);
    data_tx = setBit(data_tx, LED1Green);
    data_tx = clearBit(data_tx, LED1Blue);
    data_tx = clearBit(data_tx, LED2Red);
    data_tx = setBit(data_tx, LED2Green);
    data_tx = clearBit(data_tx, LED2Blue);
    data_tx = setBit(data_tx, SH_PO_CSn);
    
    shiftOut(data_tx, &data_rx);

}

void read_angle_encoder() {

    int angle;
    
    //////////////////////////////////////////////////////////////
    // Enable an SPI Communication
    //////////////////////////////////////////////////////////////
    // Set values for each output of sh-po
    data_tx = 0;
    //Timer t;
    //t.start();
    // CSn is set as 0 to select IC encoder
    (GPIOC -> ODR) = setBit((GPIOC -> ODR), GPIO_ODR_OD3_Pos);
    data_tx = setBit(data_tx, LED1Red);
    data_tx = setBit(data_tx, LED1Blue);
    data_tx = setBit(data_tx, LED2Red);
    data_tx = setBit(data_tx, LED2Blue);
    data_tx = clearBit(data_tx, SH_PO_CSn);
    (GPIOC -> ODR) = clearBit((GPIOC -> ODR), GPIO_ODR_OD3_Pos);
    //t.stop();
    //printf("The time taken was %llu microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(t.elapsed_time()).count());

    // Update sh-po outputs
    shiftOut(data_tx, &data_rx);

    // Wait at least 350ns for a SPI communication
    wait_ns(700);

    //////////////////////////////////////////////////////////////
    // SPI Communication
    //////////////////////////////////////////////////////////////
    // Angle reading in bits through MISO connection
    // angle = encoder.write(AS_CMD_ANGLE);
    // angle = myWrite(AS_CMD_ANGLE);
    angle = SPI_Recieve();
    //printf("Received bytes: %x\n\n", angle);
    //////////////////////////////////////////////////////////////
    // Desable an SPI Communication
    //////////////////////////////////////////////////////////////
    // CSn is set as 1 to deselect IC encoder
    data_tx = setBit(data_tx, SH_PO_CSn);

    // Update sh-po outputs
    shiftOut(data_tx, &data_rx);

    // Wait at least 350ns for a SPI communication
    wait_ns(700);
    
    if( parity_check(angle))
    {
        // Convert range from 0 to 2^14-1 to 0 - 360 degrees
        float deg = degrees(angle);
        printf("Angle: %.2f degrees\r\n", deg );
    }
    else
    {
        printf("Parity check failed.\r\n");
    }
    
}



void leds() {
    char *colour = new char[1];
    bool isColour = true;

    printf("LEDs Menu:\n");
    while(isColour) {

        printf("Options:\n");
        printf("Red colour: r\n");
        printf("Blue colour: b\n");
        printf("Yellow colour: y\n");
        printf("Green colour: g\n");
        printf("Purple colour: p\n");
        printf("Sky blue colour: s\n");
        printf("Shutdown LEDS: o\n");
        printf("Exit: e\n");
        printf("White colour: other\n");
        pc.read(colour, sizeof(colour));

        data_tx = 0;

        switch (*colour) {
        
        case 'o':
            printf("LEDs are shutdown\n\n");

            data_tx = setBit(data_tx, LED1Red);
            data_tx = setBit(data_tx, LED1Green);
            data_tx = setBit(data_tx, LED1Blue);
            data_tx = setBit(data_tx, LED2Red);
            data_tx = setBit(data_tx, LED2Blue);
            data_tx = setBit(data_tx, LED2Green);

            break;
        
        case 'r':
            printf("LEDs: Red colour\n\n");
            
            data_tx = setBit(data_tx, LED1Green);
            data_tx = setBit(data_tx, LED1Blue);
            data_tx = setBit(data_tx, LED2Blue);
            data_tx = setBit(data_tx, LED2Green);

            break;
        
        case 'g':
            printf("LEDs: Green colour\n\n");
            
            data_tx = setBit(data_tx, LED1Red);
            data_tx = setBit(data_tx, LED1Blue);
            data_tx = setBit(data_tx, LED2Red);
            data_tx = setBit(data_tx, LED2Blue);

            break;

        case 'b':
            printf("LEDs: Blue colour\n\n");
            
            data_tx = setBit(data_tx, LED1Red);
            data_tx = setBit(data_tx, LED1Green);
            data_tx = setBit(data_tx, LED2Red);
            data_tx = setBit(data_tx, LED2Green);

            break;

        case 'p':
            printf("LEDs: Purple colour\n\n");
            
            data_tx = setBit(data_tx, LED1Green);
            data_tx = setBit(data_tx, LED2Green);

            break;

        case 's':
            printf("LEDs: Sky blue colour\n\n");
            
            data_tx = setBit(data_tx, LED1Red);
            data_tx = setBit(data_tx, LED2Red);

            break;

        case 'y':
            printf("LEDs: Yellow colour\n\n");
            
            data_tx = setBit(data_tx, LED1Blue);
            data_tx = setBit(data_tx, LED2Blue);

            break;

        case 'e':
            printf("Exit from LEDs colour selection\n\n");
            isColour = false;
            break;

        default:
            printf("LEDs: White colour\n\n");
            break;
        }
    
    // Update sh-po outputs
    shiftOut(data_tx, &data_rx);

    }
    delete[] colour;
}

int main() {

    printf("\n\n\n\n");

    char *c = new char[1];

    // SPI Shift Register configuration
    shPo.format(8, 0);
    shPo.frequency(1000000);

    // SPI Encoder configuration
    //encoder.format(16, 1);
    //encoder.frequency(1000000);
    

    // Default values at output registers
    default_shiftRegister();

    while(1) {
        
        printf("\nMain Menu:\n");
        printf("Default outputs: d\n");
        printf("Reading encoder: r\n");
        printf("SPI Initialization: p\n");
        printf("LEDs menu: l\n\n");

        pc.read(c, sizeof(c));
        
        switch (*c)
        {
            
            case 'd':
                default_shiftRegister();
                break;

            case 'r':
                printf("Reading angle\n");
                read_angle_encoder();
                break;

            case 'l':
                printf("LEDs option\n");
                leds();
                break;

            case 'p':
                printf("-------------------------\n");
                printf("----SPI Configuration----\n");
                printf("-------------------------\n");
                printSPIConfig();
                //portsInit();
                mySPI();
                mySPI4();
                printSPIConfig();
                break;

            default:
                printf("This option doesn't exist\n");
                break;
        }
    }
}