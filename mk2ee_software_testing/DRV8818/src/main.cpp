#include <mbed.h>
#include <cmath>

#define PULSE_DURATION 25 // Pulse duration SRCLK or RCLK high or low (in nanoseconds) 

SPI shPo(PB_5, PB_4, PB_3);
DigitalOut csn_shpo(PA_15, 0);

static UnbufferedSerial pc(USBTX, USBRX, 9600); // tx, rx

void latchSignal() {
    csn_shpo = 1;
    wait_ns(PULSE_DURATION);
    csn_shpo = 0;
}

void shiftOut(uint16_t data_tx, uint16_t *data_rx ) {
    *data_rx = shPo.write(data_tx);
    latchSignal();
}


void printBinary(int decNumber) {
    int a[8], i;
    for(i=0; decNumber>0; i++)
    {
        a[i]=decNumber%2;
        decNumber = decNumber/2;
    }
    for(i=i-1 ;i>=0 ;i--)
    {
        printf("%i", a[i]);
    }
    printf("\n");
}

void stepper_motion(uint8_t stepper_dir, uint8_t stepper_usm1, uint8_t stepper_usm0, uint8_t shaft_motor_degrees, int velocity) {
    // Stepper resolution parameter depends on the type and the model of the stepper motor. See the datasheet
    // In our case we use a hybrid bipolar stepper motor, and commonly its resolution is 1.8 degrees/step
    float stepper_resolution = 1.8;
    uint8_t number_steps = shaft_motor_degrees / stepper_resolution;

    uint8_t stepper_sleepn, stepper_step, stepper_resetn, 
        stepper_srn, stepper_enablen;

        uint16_t data_tx;
        uint16_t data_rx;

        // stepper_dir, stepper_usm1 and stepper_usm0 are defined by the parameters above
        stepper_sleepn = 1;
        stepper_step = 0;
        stepper_resetn = 1;
        stepper_srn = 0;
        stepper_enablen = 0;

    for(int i = 0; i < number_steps; i++) {
        stepper_step = 1;
        data_tx = stepper_dir * pow(2, 0) + stepper_usm1 * pow(2, 1) + stepper_usm0 * pow(2, 2) + 
            stepper_srn * pow(2, 3) + stepper_resetn * pow(2, 4) + stepper_step * pow(2, 5) + 
            stepper_enablen * pow(2, 6) + stepper_sleepn * pow(2, 7);
        shiftOut(data_tx, &data_rx);

        wait_us(velocity/2);

        stepper_step = 0;
        data_tx = stepper_dir * pow(2, 0) + stepper_usm1 * pow(2, 1) + stepper_usm0 * pow(2, 2) + 
            stepper_srn * pow(2, 3) + stepper_resetn * pow(2, 4) + stepper_step * pow(2, 5) + 
            stepper_enablen * pow(2, 6) + stepper_sleepn * pow(2, 7);
        shiftOut(data_tx, &data_rx);

        wait_us(velocity/2);
    }
    printBinary(data_tx);
}

int main() {

    printf("\n\n\n\n");

    char *c = new char[1];

    // SPI communication settings
    shPo.format(8, 0);
    shPo.frequency(1000000);

    csn_shpo = 0;

    // Velocity parameter set the frequency between steps of the motor.
    int velocity = 10000;
    // How many degrees the shaft of the motor has rotated.
    uint8_t shaft_motor_degrees;
    // Direction parameter for the motor rotation.
    uint8_t stepper_dir = 0;
    // By default, the motor is set-up in full stepp.
    uint8_t stepper_usm1 = 0;
    uint8_t stepper_usm0 = 0;


    // stepper_dir, stepper_usm1 and stepper_usm0 are defined by the parameters above
    

    while(1) {
        
        pc.read(c, sizeof(c));

        if(*c == 'l') {
            stepper_dir = 0;
            shaft_motor_degrees = 90;

            stepper_motion(stepper_dir, stepper_usm1, stepper_usm0, shaft_motor_degrees, velocity);
            
            printf("Right\n");
        }
        else if(*c == 'j') {
            stepper_dir = 1;
            shaft_motor_degrees = 90;

            stepper_motion(stepper_dir, stepper_usm1, stepper_usm0, shaft_motor_degrees, velocity);
            printf("Left\n");
        }
        else if(*c == 'd') {
            stepper_dir = 0;
            shaft_motor_degrees = 9;

            stepper_motion(stepper_dir, stepper_usm1, stepper_usm0, shaft_motor_degrees, velocity);
        }
        else if(*c == 'a') {
            stepper_dir = 1;
            shaft_motor_degrees = 9;

            stepper_motion(stepper_dir, stepper_usm1, stepper_usm0, shaft_motor_degrees, velocity);        }
        else if(*c == 'w') {
            velocity = velocity - 10;
            printf("Velocity: %d\n", velocity);
        }
        else if(*c == 's') {
            velocity = velocity + 10;
            printf("Velocity: %d\n", velocity);
        }
        else if(*c == '1') {
            stepper_usm1 = 0;
            stepper_usm0 = 0;
            printf("Full Step mode is selected\n");
        }
        else if(*c == '2') {
            stepper_usm1 = 0;
            stepper_usm0 = 1;
            printf("Half Step mode is selected\n");
        }
        else if(*c == '3') {
            stepper_usm1 = 1;
            stepper_usm0 = 0;
            printf("1/4 Step mode is selected\n");
        }
        else if(*c == '4') {
            stepper_usm1 = 1;
            stepper_usm0 = 1;
            printf("1/8 Step mode is selected\n");
        }
    }
}