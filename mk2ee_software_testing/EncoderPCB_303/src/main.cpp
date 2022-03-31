#include "mk2ee.hpp"

// Shift Register transmitter and receiver
uint16_t data_tx;
uint16_t data_rx;

static UnbufferedSerial pc(USBTX, USBRX, 9600); // tx, rx

void default_shiftRegister() {
    
    data_tx = 0;
    data_tx = clearBit(data_tx, LED1Red); //To-Do: añadir on/off
    data_tx = setBit(data_tx, LED1Green); //off
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
    //(GPIOC -> ODR) = setBit((GPIOC -> ODR), GPIO_ODR_OD3_Pos); // To-Do: cambiar por bsrr
    data_tx = setBit(data_tx, LED1Red);
    data_tx = setBit(data_tx, LED1Blue);
    data_tx = setBit(data_tx, LED2Red);
    data_tx = setBit(data_tx, LED2Blue);
    data_tx = clearBit(data_tx, SH_PO_CSn);
    //(GPIOC -> ODR) = clearBit((GPIOC -> ODR), GPIO_ODR_OD3_Pos); // To-Do: cambiar por bsrr
    //t.stop();
    //printf("The time taken was %llu microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(t.elapsed_time()).count());

    // Update sh-po outputs
    shiftOut(data_tx, &data_rx);

    // Wait at least 350ns for a SPI communication
    wait_ns(700); // To-Do: Asegurar con osc. que realmente espera 700ns

    //////////////////////////////////////////////////////////////
    // SPI Communication
    //////////////////////////////////////////////////////////////
    // Angle reading in bits through MISO connection
    // angle = encoder.write(AS_CMD_ANGLE);
    // angle = myWrite(AS_CMD_ANGLE);
    angle = SPI_Recieve(); //To-Do: funcion ambigua
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
        float deg = degrees(angle); // To-Do: Cambiar el nombre angle
        printf("Angle: %.2f degrees\r\n", deg );
    }
    else
    {
        printf("Parity check failed.\r\n");
    }
    
}

void leds() {
    char *colour = new char[1]; // To-Do: usar memria statica
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

    char c1;
    // AS5047 spi confuguration
    setUpSpi();

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

        pc.read(&c1, 1);
        
        switch (c1)
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
                mySPI1();
                printSPIConfig();
                break;

            default:
                printf("This option doesn't exist\n");
                break;
        }
    }
}