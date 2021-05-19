#include "mbed.h"
 
PwmOut servo(D3);
 
int main() {
    servo.period_ms(20);          // servo requires a 20ms period
    int pulsewidth = 0;
    while (1) {
        for(int pulsewidth = 700; pulsewidth <= 3000; pulsewidth += 100) {
          printf("Pulsewidth: %d\n", pulsewidth);
          servo.pulsewidth_us(pulsewidth);
          ThisThread::sleep_for(1s);
        }
        for(int pulsewidth = 3000; pulsewidth >= 700; pulsewidth -= 100) {
          printf("Pulsewidth: %d\n", pulsewidth);
          servo.pulsewidth_us(pulsewidth);
          ThisThread::sleep_for(1s);
        }
        pulsewidth = 0;
    }
}