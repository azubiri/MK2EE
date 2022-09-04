# Software Testing
Every single folder is a independent project to test the hardware.

## AS5047D_SPI_Two
### Summary
It tests a reading of two magnetic encoders via a SPI communication. It doesn't test a EncoderPCB.
### Hardware required
- 2 x AS5047D (magnetic encoder)
- 2 x Capacitor (100nF)
- 2 x Magnets with a radial magnetization
- 1 x Nucleo Board

## DRV8818 (deprecated)
### Summary
It tests a DriverPCB which it is communicated with a Nucleo Board via SPI.
It uses arithmetic operators, that's why this code is deprecated.
### Hardware required
- 1 x DriverPCB
- 1 x Nucleo Board

## DRV8818_AS5047D_SPI (deprecated)
### Summary
It tests a DriverPCB and an EncoderPCB that they are communicated with a Nucleo Board via two different SPI peripherals.
It uses arithmetic operators, that's why this code is deprecated.
### Hardware required
- 1 x DriverPCB
- 1 x EncoderPCB
- 1 x Magnet with radial magnetization
- 1 x Nucleo Board

## EncoderPCB (deprecated)
### Summary
It tests an EncoderPCB setting up SPI registers directly from a Nucleo Board F411RE.
### Hardawre required
- 1 x EncoderPCB
- 1 x Magnet with radial magnetization
- 1 x Nucleo Board F411RE

## EncoderPCB_303
### Summary
It tests an EncoderPCB setting up SPI registers directly from a Nucleo Board F303RE.
Every module is coded for each digital electronic component.

Recomendations:
- I recommend to continue this code in order to finish the project.
- You can use the SPI settings that they are inside "EncoderPCB" folder in order to use a F303RE board.
- You add a module to programm the driver. Use the interface made here.

###Hardware required
- 1 x EncoderPCB
- 1 x Magnet with radial magnetization
- 1 x Nucleo Board F411RE

## Servo_PWM (deprecated)
### Summary
It tests the servo motor which is connected with a Nucleo Board, and it's controlled via PWM.
### Hardware Required
- 1 x Servo MG996
- 1 x Nucleo board (F411RE or F303RE)
