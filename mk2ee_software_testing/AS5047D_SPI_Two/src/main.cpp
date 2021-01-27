#include <mbed.h>

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

SPI encoder(PB_15, PB_14, PB_13);
DigitalOut csn_encoder1(A5, 1);
DigitalOut csn_encoder2(A4, 1);

Serial pc(USBTX, USBRX);

int mask(int sensor_result)
{
    return sensor_result & 0x3FFF; // return lowest 14-bits
}

float degrees(int sensor_result)
{
    float conversor, angle;
    conversor = 360.0 / 16384.0;
    // pc.printf("Conv: %f\n", conversor);
    angle = mask(sensor_result);
    // pc.printf("Angle in 14 bits: %f\n", angle);
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

int main() {
    pc.printf("\n\n\n\n");

    encoder.format(16, 1);

    int angle1;
    int angle2;

    while(true) {
        // Give command to start reading the angle
        csn_encoder1 = 0;

        wait_us(1); // Wait at least 350ns after chip select
        angle1 = encoder.write(AS_CMD_ANGLE);

        csn_encoder1 = 1;
        wait_us(1); // Wait at least 350ns after chip select

        csn_encoder2 = 0;

        wait_us(1); // Wait at least 350ns after chip select
        angle2 = encoder.write(AS_CMD_ANGLE);

        csn_encoder2 = 1;
        wait_us(1); // Wait at least 350ns after chip select
        
        if( parity_check(angle1) && parity_check(angle2))
        {
            // Convert range from 0 to 2^14-1 to 0 - 360 degrees
            float deg1 = degrees(angle1);
            float deg2 = degrees(angle2);
            // float degrees_f = deg / 1000;
            // pc.printf("Parity check succesfull.\r");
            pc.printf("Angle 1: %f degrees\r\n", deg1 );
            pc.printf("Angle 2: %f degrees\r\n", deg2 );
        }
        else
        {
            pc.printf("Parity check failed.\r\n");
        }
        // ThisThread::sleep_for(1s);
        wait_ms(500);
    }
}