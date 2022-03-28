#include <mbed.h>
#include "defConfig.h"

void portsInit();
//void printSPI5Config();
void mySPI5();
int SPI5_Recieve();
void mySPI4();
void SPI4_Transmit(uint32_t data);
void CSn_Enable();
void CSn_Disable();
int myWrite(int data);