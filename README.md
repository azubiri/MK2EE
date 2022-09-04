# MK2EE
## Introduction
The main goal of this project is a fabrication of robotic arm. This project is based on a previous project that is called [MK2Plus](https://www.instructables.com/Robot-Arm-MK2-Plus-Stepper-Motor-Used/). This previous project is a purpose which the joints of the robot are moved by stepper motors instead of servo motors like another project [EEZYbotARM MK2](http://www.eezyrobots.it/eba_mk2.html).

These additions which are implemented in this project are the following:
* Rotatory information of the joints that are provided by magnetic encoders.
* All electronic is integrated in the robot.
* Stressfuls for cables are avoided.

In this repository you will find the several files to replicate and improve this purposed robotic arm. It is structured by the mechanical part, electronic part and software that have been used to test the electronic part. In addition, there is anohter folder where you will find some software tools.

This project was a part of Master's Thesis. You can see more details about it in the documentation folder.

## Software requirements
### Mechanical part
* Autodesk Fusion 360 (recommended)
* FreeCAD (optional)
### Electronic part
* KiCad
### Software testing
* Visual Studio Code with PlatformIO extension (recommended)
* Mbed OS (optional)
### Software utilities
* Jupyter Notebook

## ToDo list
### Mechanical Part
- [ ] Paste one of the gear that is coupled with a stepper motor.
- [ ] Make a new gripper using a microservo and energised with 5V.

### Electronical Part
- [ ] Solder 2 EncoderPCB
- [ ] Solder 2 DriverPCB
- [ ] Solder 1 EncoderPCB2
- [ ] Solder 1 SupplyPCB

(see some important information in the README file inside mk2ee_kicad_project)

### Firmware Part
- [x] Test EncoderPCB with a Nucleo Board F303RE
- [x] Test DriverPCB with a Nucleo Board F303RE
- [x] Test EncoderPCB with a Nucleo Board F411RE
- [x] Test DriverPCB with a Nucleo Board F411RE
- [ ] Test EncoderPCB2 with a Nucleo Board F411RE
- [ ] Final testing SupplyPCB + EncoderPCB2 + 3xEncoderPCB + 3xDriverPCB

(see more details in the README file inside mk2ee_software_testing folder)
