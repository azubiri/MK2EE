#include "mbed.h"

static BufferedSerial pc(USBTX, USBRX, 9600);
PwmOut servo(PB_7);
char *buff = new char[1];
int leftpos = 2150;
int rightpos = 1000;
int middlepos = 1500;

void stepbystep() {
  printf("Step by Step\n");
  for(int pulsewidth = rightpos; pulsewidth <= leftpos; pulsewidth += 10) {
    printf("Pulsewidth: %d\n", pulsewidth);
    servo.pulsewidth_us(pulsewidth);
    ThisThread::sleep_for(200);
  }
  for(int pulsewidth = leftpos; pulsewidth >= rightpos; pulsewidth -= 10) {
    printf("Pulsewidth: %d\n", pulsewidth);
    servo.pulsewidth_us(pulsewidth);
    ThisThread::sleep_for(200);
  }
}

void rightposition() {
  printf("Closed grip\n");
  servo.pulsewidth_us(rightpos);
}

void leftposition() {
  printf("Opened grip\n");
  servo.pulsewidth_us(leftpos);
}

void middleposition() {
  printf("Middle\n");
  servo.pulsewidth_us(middlepos);
}

int main() {
    servo.period_ms(20);
    
    char msg[] = "Echoes back to the screen anything you type\n";
    pc.write(msg, sizeof(msg));
    while (1) {
        pc.read(buff, sizeof(1));
        //pc.write(buff, sizeof(1));

        if(*buff == 'w') {
          stepbystep();
        }
        else if(*buff == 'a') {
          rightposition();
        }
        else if(*buff == 'd') {
          leftposition();
        }
        else if(*buff == 's') {
          middleposition();
        }
    }

}