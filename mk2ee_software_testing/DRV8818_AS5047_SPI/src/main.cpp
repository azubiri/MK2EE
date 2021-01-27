#include <mbed.h>
#include <cmath>

#define PULSE_DURATION 25 // Pulse duration SRCLK or RCLK high or low (in nanoseconds) 

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

SPI encoder(PA_7, PA_6, PA_5);

SPI shPo(PC_12, PC_11, PC_10);
DigitalOut csn_shpo(A3, 1);
// Shift Register transmitter and receiver
uint16_t data_tx;
uint16_t data_rx;

static Serial pc(USBTX, USBRX, 115200); // tx, rx

// Parallel outputs
// Driver parameters
uint8_t stepper_dir, stepper_usm1, stepper_usm0, 
    stepper_sleepn, stepper_step, stepper_resetn, 
    stepper_srn, stepper_enablen;
// Encoder parameter
uint8_t csn_encoder;

int velocity = 10000; // 10 ms

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
//////////////////////////////////

// Driver Code
void default_shiftRegister() {
    // Parallel output parameters
    stepper_dir = 0;
    stepper_usm1 = 0;
    stepper_usm0 = 0;
    stepper_sleepn = 1;
    stepper_step = 0;
    stepper_resetn = 1;
    stepper_srn = 0;
    stepper_enablen = 0;
    csn_encoder = 1;
    // Latch clock
    csn_shpo = 0;

    data_tx = stepper_dir * pow(2, 0) + stepper_usm1 * pow(2, 1) + stepper_usm0 * pow(2, 2) + 
        stepper_sleepn * pow(2, 3) + stepper_step * pow(2, 4) + stepper_resetn * pow(2, 5) + 
        stepper_srn * pow(2, 6) + stepper_enablen * pow(2, 7) + csn_encoder * pow(2, 9);
    shiftOut(data_tx, &data_rx);
}

void stepper_motion(int direction, int degrees) {
    stepper_dir = direction;
    int num_steps = degrees / 1.8;
    for(int i = 0; i < num_steps; i++) {
        stepper_step = 1;
        data_tx = stepper_dir * pow(2, 0) + stepper_usm1 * pow(2, 1) + stepper_usm0 * pow(2, 2) + 
            stepper_sleepn * pow(2, 3) + stepper_step * pow(2, 4) + stepper_resetn * pow(2, 5) + 
            stepper_srn * pow(2, 6) + stepper_enablen * pow(2, 7) + csn_encoder * pow(2, 9);
        shiftOut(data_tx, &data_rx);

        wait_us(velocity/2);

        stepper_step = 0;
        data_tx = stepper_dir * pow(2, 0) + stepper_usm1 * pow(2, 1) + stepper_usm0 * pow(2, 2) + 
            stepper_sleepn * pow(2, 3) + stepper_step * pow(2, 4) + stepper_resetn * pow(2, 5) + 
            stepper_srn * pow(2, 6) + stepper_enablen * pow(2, 7) + csn_encoder * pow(2, 9);
        shiftOut(data_tx, &data_rx);

        wait_us(velocity/2);
    }
}

void increase_velocity() {
    velocity = velocity - 10;
    printf("Velocity: %d\n", velocity);
}

void decrease_velocity() {
    velocity = velocity + 10;
    printf("Velocity: %d\n", velocity);
}

void stepper_mode(int usm1, int usm0) {
    if(usm1 == 0 && usm0 == 0) {
        stepper_usm1 = usm1;
        stepper_usm0 = usm0;
        printf("Full Step mode is selected\n");
    }
    else if (usm1 == 0 && usm0 == 1) {
        stepper_usm1 = usm1;
        stepper_usm0 = usm0;
        printf("Half Step mode is selected\n");
    }
    else if (usm1 == 1 && usm0 == 0) {
        stepper_usm1 = usm1;
        stepper_usm0 = usm0;
        printf("1/4 Step mode is selected\n");
    }
    else if (usm1 == 1 && usm0 == 1){
        stepper_usm1 = usm1;
        stepper_usm0 = usm0;
        printf("1/8 Step mode is selected\n");
    }
    else {
        stepper_usm1 = 0;
        stepper_usm0 = 0;
        printf("This option is not correct, full step mode is selected\n");
    }
}

void read_angle_encoder() {
    int angle;
    angle = encoder.write(AS_CMD_ANGLE);

    stepper_dir = 0;
    stepper_usm1 = 0;
    stepper_usm0 = 0;
    stepper_sleepn = 1;
    stepper_step = 0;
    stepper_resetn = 1;
    stepper_srn = 0;
    stepper_enablen = 0;
    csn_encoder = 1;

    data_tx = stepper_dir * pow(2, 0) + stepper_usm1 * pow(2, 1) + stepper_usm0 * pow(2, 2) + 
        stepper_sleepn * pow(2, 3) + stepper_step * pow(2, 4) + stepper_resetn * pow(2, 5) + 
        stepper_srn * pow(2, 6) + stepper_enablen * pow(2, 7) + csn_encoder * pow(2, 9);
    shiftOut(data_tx, &data_rx);
    wait_us(1); // Wait at least 350ns after chip select
    
    if( parity_check(angle))
    {
        // Convert range from 0 to 2^14-1 to 0 - 360 degrees
        float deg = degrees(angle);
        printf("Angle: %f degrees\r\n", deg );
    }
    else
    {
        printf("Parity check failed.\r\n");
    }
}

int main() {

    printf("\n\n\n\n");

    char c;

    // SPI Shift Register configuration
    shPo.format(16, 0);
    shPo.frequency(1000000);

    // SPI Encoder configuration
    encoder.format(16, 1);
    encoder.frequency(1000000);

    // Default values at output registers
    default_shiftRegister();

    while(1) {
        
        c = pc.getc();

        switch (c)
        {
            case 'l':
                stepper_motion(1, 90);
                break;
            
            case 'j':
                stepper_motion(0, 90);
                break;

            case 'd':
                stepper_motion(1, 9);
                break;

            case 'a':
                stepper_motion(0, 9);
                break;

            case 'w':
                increase_velocity();
                break;

            case 's':
                decrease_velocity();
                break;

            case 'r':
                default_shiftRegister();
                read_angle_encoder();
                break;
            
            case '1':
                stepper_mode(0, 0);
                break;

            case '2':
                stepper_mode(0, 1);
                break;

            case '3':
                stepper_mode(1, 0);
                break;

            case '4':
                stepper_mode(1, 1);
                break;

            default:
                printf("This option doesn't exist\n");
                break;
        }
    }
}