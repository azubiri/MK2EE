EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MC74HC595ADG:MC74HC595ADG U3
U 1 1 5F510292
P 5600 3450
F 0 "U3" H 5600 4320 50  0000 C CNN
F 1 "MC74HC595ADG" H 5600 4229 50  0000 C CNN
F 2 "MK2Library:MC74HC595ADG" H 5600 3450 50  0001 L BNN
F 3 "MC74HC595ADG" H 5600 3450 50  0001 L BNN
F 4 "MC74HC595ADG" H 5600 3450 50  0001 C CNN "Name"
F 5 "On Semiconductor" H 5600 3450 50  0001 L BNN "Manufacturer"
	1    5600 3450
	1    0    0    -1  
$EndComp
$Comp
L S5B-PH-K-S_LF__SN_:S5B-PH-K-S(LF)(SN) J4
U 1 1 5F511536
P 8650 3700
F 0 "J4" H 8980 3791 50  0000 L CNN
F 1 "Digital Signals Output" H 8980 3700 50  0000 L CNN
F 2 "MK2Library:S5B-PH-K-S_LF__SN_" H 8650 3700 50  0001 L BNN
F 3 "JST Sales" H 8650 3700 50  0001 L BNN
F 4 "S5B-PH-SM4-TB" H 8980 3609 50  0000 L CNN "Name"
F 5 "JST" H 8650 3700 50  0001 C CNN "Manufacturer"
	1    8650 3700
	1    0    0    -1  
$EndComp
$Comp
L S5B-PH-K-S_LF__SN_:S5B-PH-K-S(LF)(SN) J3
U 1 1 5F511B5E
P 8650 2850
F 0 "J3" H 8980 2941 50  0000 L CNN
F 1 "Digital Signals Input" H 8980 2850 50  0000 L CNN
F 2 "MK2Library:S5B-PH-K-S_LF__SN_" H 8650 2850 50  0001 L BNN
F 3 "JST Sales" H 8650 2850 50  0001 L BNN
F 4 "S5B-PH-SM4-TB" H 8980 2759 50  0000 L CNN "Name"
F 5 "JST" H 8650 2850 50  0001 C CNN "Manufacturer"
	1    8650 2850
	1    0    0    -1  
$EndComp
Text GLabel 6750 2950 2    50   Output ~ 0
DIR
Text GLabel 6750 3050 2    50   Output ~ 0
USM0
Text GLabel 6750 3150 2    50   Output ~ 0
USM1
Text GLabel 6750 3250 2    50   Output ~ 0
STEP
Text GLabel 6750 3350 2    50   Output ~ 0
SRn
Text GLabel 6750 3450 2    50   Output ~ 0
RESETn
NoConn ~ 6500 3550
NoConn ~ 6500 3650
Wire Wire Line
	6500 2950 6750 2950
Wire Wire Line
	6500 3050 6750 3050
Wire Wire Line
	6500 3150 6750 3150
Wire Wire Line
	6500 3250 6750 3250
Wire Wire Line
	6500 3350 6750 3350
Wire Wire Line
	6500 3450 6750 3450
Text GLabel 8200 2850 0    50   Output ~ 0
SerialDataIn
Text GLabel 8200 2750 0    50   Output ~ 0
VCC
Text GLabel 8200 2650 0    50   Output ~ 0
SH-CLK
Text GLabel 8200 2950 0    50   Output ~ 0
GND
Text GLabel 8200 3050 0    50   Output ~ 0
PO-CLK
Text GLabel 8200 3700 0    50   Input ~ 0
SerialDataOut
Text GLabel 8200 3600 0    50   Input ~ 0
VCC
Text GLabel 8200 3500 0    50   Input ~ 0
SH-CLK
Text GLabel 8200 3800 0    50   Input ~ 0
GND
Text GLabel 8200 3900 0    50   Input ~ 0
PO-CLK
Wire Wire Line
	8200 2650 8450 2650
Wire Wire Line
	8200 2750 8450 2750
Wire Wire Line
	8200 2850 8450 2850
Wire Wire Line
	8200 2950 8450 2950
Wire Wire Line
	8200 3050 8450 3050
Wire Wire Line
	8200 3500 8450 3500
Wire Wire Line
	8200 3600 8450 3600
Wire Wire Line
	8200 3700 8450 3700
Wire Wire Line
	8200 3800 8450 3800
Wire Wire Line
	8200 3900 8450 3900
Text GLabel 4450 2950 0    50   Input ~ 0
VCC
Text GLabel 4450 4150 0    50   Input ~ 0
GND
Text GLabel 4450 3350 0    50   Input ~ 0
SH-CLK
Text GLabel 4450 3450 0    50   Input ~ 0
PO-CLK
Wire Wire Line
	4450 2950 4600 2950
Wire Wire Line
	4450 3350 4700 3350
Wire Wire Line
	4450 3450 4700 3450
Wire Wire Line
	4450 4150 4700 4150
Wire Wire Line
	4600 2950 4600 3150
Wire Wire Line
	4600 3150 4700 3150
Connection ~ 4600 2950
Wire Wire Line
	4600 2950 4700 2950
NoConn ~ 4700 3650
Text GLabel 4450 3850 0    50   Output ~ 0
SerialDataOut
Text GLabel 4450 3950 0    50   Input ~ 0
SerialDataIn
Wire Wire Line
	4450 3850 4700 3850
Wire Wire Line
	4450 3950 4700 3950
$EndSCHEMATC
