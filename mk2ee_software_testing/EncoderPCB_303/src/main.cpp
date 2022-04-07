/**
 * @file main.cpp
 * @author Alberto Zubiri Carrizosa (azubiri@pm.me)
 * @brief Testing software for an EncoderPCB with a Nucleo-F303RE board from STMicroelectronics.
 * 
 * The main goal of this board is to provide rotation position readings from the magnetic encoder AS5047 to the microcontroller STMF303RE.
 * 
 * There is a communication between a microcontroller and a magnetic encoder, two RBG LEDs are included in order to indicate the state of the board.
 * To reduce the number of cables a shift register with parallel output is added to connect from the all LEDs imputs and one encoder input to the microcontroller.
 * There are three connectors, J8 (input digital signals), J9 (output digital signals but it's not used here), and J10 (power supply).
 * 
 * Components which we are testing inside EncoderPCB:
 * - 1 x SN74HC595: Shift Register with Parallel Output
 * - 1 x AS5047: Magnetic Encoder
 * - 2 x ASMB-KTF0-0A306: RGB LED
 * 
 * More information about components in:
 * - as5047.hpp
 * - sn74hc595.hpp
 * 
 * 2 SPI communications are configured for this software testing:
 * - From F303RE to SN74HC595: MOSI, SCK and NSS
 * - From AS5047 to F303RE: MISO, SCK, (NSS is an output of SN74HC595)
 * In both communications F303RE acts as a master and the other devices as slaves.
 * 
 * This software tests a proper communication between:
 * - STMicrocontroller F303RE and SN74HC595
 * - SN74HC595 and AS5047 encoder
 * - SN74HC595 and 2 RGB LEDs
 * - AS5047 encoder and STMicrocontroller F303RE
 * 
 * Data transfer format:
 * Bit0: Not used
 * Bit1: Red colour from RGB LED1
 * Bit2: Green colour from RGB LED1
 * Bit3: Blue colour from RGB LED1
 * Bit4: Blue colour from RGB LED2
 * Bit5: Green colour from RGB LED2
 * Bit6: Red colour from RGB LED2
 * Bit7: CSn signal for the Encoder AS5047
 * TODO: Explicar conectores
 * TODO: Explicar cómo funciona
 * 
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <mbed.h>
#include "mk2ee_definitions.hpp"
#include "mk2eeSPI1.hpp"
#include "mk2eeSPI.hpp"
#include "as5047.hpp"
#include "sn74hc595.hpp"

static UnbufferedSerial pc(USBTX, USBRX, 9600); // tx, rx

/**
 * @brief Default values for each output of the SN74HC595 component. RGB LEDs from EncoderPCB board will light with purple colour to indicate
 * the board is in default mode. LEDs are turn on with a low level. CSn output is turn on to avoid an encoder reading.
 */
void default_shiftRegister() {

    Sn74hc595 encoder_sh_po;
    uint16_t data_tx = 0;

    data_tx = clearBit(data_tx, LED1Red); // ON
    data_tx = setBit(data_tx, LED1Green); // OFF
    data_tx = clearBit(data_tx, LED1Blue); // ON
    data_tx = clearBit(data_tx, LED2Red); // ON
    data_tx = setBit(data_tx, LED2Green); // OFF
    data_tx = clearBit(data_tx, LED2Blue); // ON
    data_tx = setBit(data_tx, SH_PO_CSn); // OFF
    
    encoder_sh_po.shiftOut(data_tx);

}

void read_angle_encoder() {
    // Clock frequency
    // Maximum frequencies:
    // AS5047=10MHz
    // STM32F303RE_APB2=72MHz
    // SN74HC595_3.3V=5MHz
    int receive_encoder;
    Sn74hc595 encoder_sh_po;
    As5047 encoder;
    Mk2eeSPI1 spi1;
    //////////////////////////////////////////////////////////////
    // Enable an SPI Communication
    //////////////////////////////////////////////////////////////
    // Set values for each output of sh-po
    uint16_t data_tx = 0;
    //Timer t;
    //t.start();
    // CSn is set as 0 to select IC encoder
    prf_0; // Timing: rising edge
    data_tx = setBit(data_tx, LED1Red);
    data_tx = setBit(data_tx, LED1Blue);
    data_tx = setBit(data_tx, LED2Red);
    data_tx = setBit(data_tx, LED2Blue);
    data_tx = clearBit(data_tx, SH_PO_CSn);
    prf_1; // Timing: falling edge
    //t.stop();
    //printf("The time taken was %llu microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(t.elapsed_time()).count());

    // Update sh-po outputs
    encoder_sh_po.shiftOut(data_tx);

    // Wait at least 350ns for a SPI communication
    wait_ns(700); // TODO: Asegurar con osc. que realmente espera 700ns

    //////////////////////////////////////////////////////////////
    // SPI Communication
    //////////////////////////////////////////////////////////////
    // Angle reading in bits through MISO connection
    // angle = encoder.write(AS_CMD_ANGLE);
    // angle = myWrite(AS_CMD_ANGLE);
    receive_encoder = spi1.receive_spi();
    //printf("Received bytes: %x\n\n", angle);
    //////////////////////////////////////////////////////////////
    // Desable an SPI Communication
    //////////////////////////////////////////////////////////////
    // CSn is set as 1 to deselect IC encoder
    data_tx = setBit(data_tx, SH_PO_CSn);

    // Update sh-po outputs
    encoder_sh_po.shiftOut(data_tx);

    // Wait at least 350ns for a SPI communication
    wait_ns(700);
    
    if(encoder.parity_check(receive_encoder)) {
        // Convert range from 0 to 2^14-1 to 0 - 360 degrees
        float anglef = encoder.get_angle(receive_encoder);
        printf("Angle: %.2f degrees\r\n", anglef );
    }
    else {
        printf("Parity check failed.\r\n");
    }
    
}

void leds() {

    char colour;
    bool isColour = true;
    uint16_t data_tx;
    Sn74hc595 encoder_sh_po;
    
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
        
        pc.read(&colour, 1);

        data_tx = 0;

        switch (colour) {
        
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
    encoder_sh_po.shiftOut(data_tx);

    }

}



int main() {

    char option;

    // Default values at output registers
    default_shiftRegister();
    while(1) {
        
        printf("\nMain Menu:\n");
        printf("Default outputs: d\n");
        printf("Reading encoder: r\n");
        printf("SPI Initialization: p\n");
        printf("LEDs menu: l\n\n");

        pc.read(&option, 1);
        
        switch (option) {
            
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
                
                break;

            default:
                printf("This option doesn't exist\n");
                break;
        
        }

    }
    
}