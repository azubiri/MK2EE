EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title "Encoder2 - PCB4"
Date "2020-09-03"
Rev "1"
Comp "ETSETB/UPC"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	9650 2050 9900 2050
Wire Wire Line
	9650 2150 9900 2150
Wire Wire Line
	9650 2250 9900 2250
Wire Wire Line
	9650 2350 9900 2350
Wire Wire Line
	9650 2450 9900 2450
Wire Wire Line
	9650 2550 9900 2550
Wire Wire Line
	9650 2650 9900 2650
Wire Wire Line
	9650 2750 9900 2750
Wire Wire Line
	9650 2850 9900 2850
Wire Wire Line
	9650 2950 9900 2950
Text GLabel 9650 2750 0    50   Output ~ 0
CLKEn4
Text GLabel 9650 2650 0    50   Output ~ 0
MISO4
Text GLabel 9650 2350 0    50   Output ~ 0
SH-CLKEn4
Text GLabel 9650 2550 0    50   Output ~ 0
SerialDataInEn4
Text GLabel 9650 2450 0    50   Output ~ 0
PO-CLKEn4
$Comp
L AS5047D-ATSM:AS5047D-ATSM IC?
U 1 1 5F509105
P 5850 2100
AR Path="/5F4C6CE4/5F509105" Ref="IC?"  Part="1" 
AR Path="/5F4C6BF4/5F509105" Ref="IC?"  Part="1" 
AR Path="/5F505E68/5F509105" Ref="U10"  Part="1" 
F 0 "U10" H 6450 2365 50  0000 C CNN
F 1 "AS5047D-ATSM" H 6450 2274 50  0000 C CNN
F 2 "MK2Library:AS5047D-ATSM" H 6900 2200 50  0001 L CNN
F 3 "http://ams.com/eng/content/download/595083/1609657/320155" H 6900 2100 50  0001 L CNN
F 4 "AS5047D-ATSM" H 5850 2100 50  0001 C CNN "Name"
F 5 "ams" H 6900 1600 50  0001 L CNN "Manufacturer"
F 6 "ams AS5047D-ATSM Hall Effect Sensor 14-Pin TSSOP, 3  3.6 V, 4.5  5.5 V" H 6900 2000 50  0001 L CNN "Description"
F 7 "1.2" H 6900 1900 50  0001 L CNN "Height"
F 8 "985-AS5047D-ATSM" H 6900 1800 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/ams/AS5047D-ATSM?qs=qEcPHXRbv51jEdbehV7Mjw%3D%3D" H 6900 1700 50  0001 L CNN "Mouser Price/Stock"
F 10 "AS5047D-ATSM" H 6900 1500 50  0001 L CNN "Manufacturer_Part_Number"
	1    5850 2100
	1    0    0    -1  
$EndComp
NoConn ~ 7050 2100
NoConn ~ 7050 2500
NoConn ~ 7050 2600
NoConn ~ 7050 2700
NoConn ~ 5850 2600
NoConn ~ 5850 2700
Text GLabel 5500 2100 0    50   Input ~ 0
CSn4
Text GLabel 5500 2200 0    50   Input ~ 0
CLKEn4
Text GLabel 5500 2300 0    50   Input ~ 0
MISO4
Text GLabel 5500 2400 0    50   Input ~ 0
VCCF3v3
Text GLabel 7700 2400 2    50   Input ~ 0
VCCF3v3
Wire Wire Line
	5500 2100 5850 2100
Wire Wire Line
	5500 2200 5850 2200
Wire Wire Line
	5500 2300 5850 2300
Wire Wire Line
	5500 2400 5850 2400
Wire Wire Line
	7050 2400 7350 2400
Wire Wire Line
	7050 2300 7350 2300
Wire Wire Line
	7350 2300 7350 2400
Connection ~ 7350 2400
Wire Wire Line
	7350 2400 7700 2400
$Comp
L power:GND #PWR?
U 1 1 5F50911F
P 7050 2200
AR Path="/5F4C6CE4/5F50911F" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F50911F" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F50911F" Ref="#PWR0131"  Part="1" 
F 0 "#PWR0131" H 7050 1950 50  0001 C CNN
F 1 "GND" V 7055 2072 50  0000 R CNN
F 2 "" H 7050 2200 50  0001 C CNN
F 3 "" H 7050 2200 50  0001 C CNN
	1    7050 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F509125
P 5850 2500
AR Path="/5F4C6CE4/5F509125" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F509125" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F509125" Ref="#PWR0132"  Part="1" 
F 0 "#PWR0132" H 5850 2250 50  0001 C CNN
F 1 "GND" V 5855 2372 50  0000 R CNN
F 2 "" H 5850 2500 50  0001 C CNN
F 3 "" H 5850 2500 50  0001 C CNN
	1    5850 2500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F509145
P 7350 2700
AR Path="/5F4C6CE4/5F509145" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F509145" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F509145" Ref="#PWR0133"  Part="1" 
F 0 "#PWR0133" H 7350 2450 50  0001 C CNN
F 1 "GND" H 7355 2527 50  0000 C CNN
F 2 "" H 7350 2700 50  0001 C CNN
F 3 "" H 7350 2700 50  0001 C CNN
	1    7350 2700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x12_Male J9
U 1 1 5F50E8F5
P 10100 2650
F 0 "J9" H 10072 2487 50  0000 R CNN
F 1 "Conn_01x12_Male" H 10072 2578 50  0000 R CNN
F 2 "Connector_Molex:Molex_CLIK-Mate_502443-1270_1x12-1MP_P2.00mm_Vertical" H 10100 2650 50  0001 C CNN
F 3 "~" H 10100 2650 50  0001 C CNN
F 4 "CLIK-Mate 502443-1207" H 10072 2669 50  0000 R CNN "Name"
F 5 "Molex" H 10100 2650 50  0001 C CNN "Manufacturer"
	1    10100 2650
	-1   0    0    1   
$EndComp
Text GLabel 9650 2150 0    50   Output ~ 0
PO-CLKDr4
Text GLabel 9650 2050 0    50   Output ~ 0
SH-CLKDr4
Text GLabel 9650 2950 0    50   Output ~ 0
VCCF3v3
Text GLabel 9650 2250 0    50   Output ~ 0
SerialDataInDr4
Text GLabel 9650 3150 0    50   Output ~ 0
VMC
Wire Wire Line
	9650 3050 9900 3050
Wire Wire Line
	9650 3150 9900 3150
Wire Wire Line
	9650 3700 9900 3700
Wire Wire Line
	9650 3800 9900 3800
Wire Wire Line
	9650 3900 9900 3900
Wire Wire Line
	9650 4000 9900 4000
Wire Wire Line
	9650 4100 9900 4100
Text GLabel 9650 3900 0    50   Input ~ 0
CLKEn4
Text GLabel 9650 3800 0    50   Input ~ 0
MISO4
Text GLabel 9650 3700 0    50   Input ~ 0
SH-CLKEn4
Text GLabel 9650 4000 0    50   Input ~ 0
SerialDataOutEn4
Text GLabel 9650 4100 0    50   Input ~ 0
PO-CLKEn4
Text GLabel 9550 4900 0    50   Input ~ 0
SerialDataOutDr4
Text GLabel 9550 4700 0    50   Input ~ 0
SH-CLKDr4
Text GLabel 9550 4800 0    50   Input ~ 0
PO-CLKDr4
Text GLabel 9550 5000 0    50   Input ~ 0
VMC
Wire Wire Line
	9550 4700 9900 4700
Wire Wire Line
	9550 4800 9900 4800
Wire Wire Line
	9550 4900 9900 4900
Wire Wire Line
	9550 5000 9900 5000
Wire Wire Line
	9900 5100 9150 5100
Wire Wire Line
	9150 5100 9150 5250
$Comp
L power:GND #PWR?
U 1 1 5F53EADC
P 9150 5250
AR Path="/5F4C6CE4/5F53EADC" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F53EADC" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F53EADC" Ref="#PWR0134"  Part="1" 
F 0 "#PWR0134" H 9150 5000 50  0001 C CNN
F 1 "GND" H 9155 5077 50  0000 C CNN
F 2 "" H 9150 5250 50  0001 C CNN
F 3 "" H 9150 5250 50  0001 C CNN
	1    9150 5250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J10
U 1 1 5F5D61FE
P 10100 3900
F 0 "J10" H 10072 3787 50  0000 R CNN
F 1 "Conn_01x05_Male" H 10072 3878 50  0000 R CNN
F 2 "Connector_Molex:Molex_CLIK-Mate_502386-0570_1x05-1MP_P1.25mm_Horizontal" H 10100 3900 50  0001 C CNN
F 3 "~" H 10100 3900 50  0001 C CNN
F 4 "CLIK-Mate_502386-0570" H 10072 3969 50  0000 R CNN "Name"
F 5 "Molex" H 10100 3900 50  0001 C CNN "Manufacturer"
	1    10100 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5DDE3D
P 9650 3050
AR Path="/5F4C6CE4/5F5DDE3D" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F5DDE3D" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F5DDE3D" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 9650 2800 50  0001 C CNN
F 1 "GND" H 9655 2877 50  0000 C CNN
F 2 "" H 9650 3050 50  0001 C CNN
F 3 "" H 9650 3050 50  0001 C CNN
	1    9650 3050
	0    1    1    0   
$EndComp
Text GLabel 4100 2600 2    50   Output ~ 0
CSn4
NoConn ~ 3850 3300
Wire Wire Line
	3850 2600 4100 2600
Wire Wire Line
	3850 2700 4100 2700
Wire Wire Line
	3850 2800 4100 2800
Wire Wire Line
	3850 2900 4100 2900
Wire Wire Line
	3850 3000 4100 3000
Wire Wire Line
	3850 3100 4100 3100
Text GLabel 2400 2000 0    50   Input ~ 0
VCCF3v3
Text GLabel 2800 2800 0    50   Input ~ 0
SH-CLKEn4
Text GLabel 2800 3100 0    50   Input ~ 0
PO-CLKEn4
Wire Wire Line
	2800 2800 3050 2800
Wire Wire Line
	2800 3100 3050 3100
NoConn ~ 2050 3300
Text GLabel 4100 3500 2    50   Output ~ 0
SerialDataOutEn4
Text GLabel 2800 2600 0    50   Input ~ 0
SerialDataInEn4
Wire Wire Line
	4100 3500 3850 3500
Wire Wire Line
	2800 2600 3050 2600
Wire Wire Line
	3850 3200 4100 3200
$Comp
L 74xx:74HC595 U?
U 1 1 5F9DF230
P 3450 3000
AR Path="/5F4C6CE4/5F9DF230" Ref="U?"  Part="1" 
AR Path="/5F505E68/5F9DF230" Ref="U9"  Part="1" 
F 0 "U9" H 3450 3781 50  0000 C CNN
F 1 "74HC595" H 3450 3690 50  0000 C CNN
F 2 "" H 3450 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 3450 3000 50  0001 C CNN
	1    3450 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 2000 3450 2400
$Comp
L power:GND #PWR?
U 1 1 5F9DF237
P 3450 3700
AR Path="/5F4C6CE4/5F9DF237" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F9DF237" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F9DF237" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3450 3450 50  0001 C CNN
F 1 "GND" H 3455 3527 50  0000 C CNN
F 2 "" H 3450 3700 50  0001 C CNN
F 3 "" H 3450 3700 50  0001 C CNN
	1    3450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 3200 2950 3200
Wire Wire Line
	2950 3200 2950 3700
Wire Wire Line
	2950 3700 3450 3700
Connection ~ 3450 3700
Wire Wire Line
	3050 2900 2900 2900
Wire Wire Line
	2900 2900 2900 2000
Connection ~ 2900 2000
Wire Wire Line
	2900 2000 3450 2000
Wire Wire Line
	2400 2000 2600 2000
$Comp
L Device:C C?
U 1 1 5F9DF246
P 2600 2150
AR Path="/5F4C6CE4/5F9DF246" Ref="C?"  Part="1" 
AR Path="/5F505E68/5F9DF246" Ref="C20"  Part="1" 
F 0 "C20" H 2715 2196 50  0000 L CNN
F 1 "100nF" H 2715 2105 50  0000 L CNN
F 2 "" H 2638 2000 50  0001 C CNN
F 3 "~" H 2600 2150 50  0001 C CNN
	1    2600 2150
	1    0    0    -1  
$EndComp
Connection ~ 2600 2000
Wire Wire Line
	2600 2000 2900 2000
$Comp
L power:GND #PWR?
U 1 1 5F9DF24E
P 2600 2300
AR Path="/5F4C6CE4/5F9DF24E" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F9DF24E" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F9DF24E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2600 2050 50  0001 C CNN
F 1 "GND" H 2605 2127 50  0000 C CNN
F 2 "" H 2600 2300 50  0001 C CNN
F 3 "" H 2600 2300 50  0001 C CNN
	1    2600 2300
	1    0    0    -1  
$EndComp
NoConn ~ 4100 2700
NoConn ~ 4100 2800
NoConn ~ 4100 2900
NoConn ~ 4100 3000
NoConn ~ 4100 3100
NoConn ~ 4100 3200
Text GLabel 9650 2850 0    50   Output ~ 0
PWM4
Text GLabel 9550 4600 0    50   Input ~ 0
PWM4
Wire Wire Line
	9550 4600 9900 4600
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 5FA8DBDA
P 10100 4900
AR Path="/5F475AB3/5FA8DBDA" Ref="J?"  Part="1" 
AR Path="/5F505E68/5FA8DBDA" Ref="J11"  Part="1" 
F 0 "J11" H 10072 4737 50  0000 R CNN
F 1 "Conn_01x06_Male" H 10072 4828 50  0000 R CNN
F 2 "Connector_Molex:Molex_CLIK-Mate_502443-0670_1x06-1MP_P2.00mm_Vertical" H 10100 4900 50  0001 C CNN
F 3 "~" H 10100 4900 50  0001 C CNN
F 4 "CLIC-Mate 502443-0670" H 10072 4919 50  0000 R CNN "Name"
F 5 "Molex" H 10100 4900 50  0001 C CNN "Manufacturer"
	1    10100 4900
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5FA9A4D8
P 7350 2550
AR Path="/5F4C6CE4/5FA9A4D8" Ref="C?"  Part="1" 
AR Path="/5F505E68/5FA9A4D8" Ref="C21"  Part="1" 
F 0 "C21" H 7465 2596 50  0000 L CNN
F 1 "100nF" H 7465 2505 50  0000 L CNN
F 2 "" H 7388 2400 50  0001 C CNN
F 3 "~" H 7350 2550 50  0001 C CNN
	1    7350 2550
	1    0    0    -1  
$EndComp
Text Notes 5900 1650 0    100  ~ 0
Magnetic Encoder
Text Notes 2100 1750 0    100  ~ 0
Shift Registers with Parallel Output
Text Notes 9400 1750 0    100  ~ 0
Connectors
$EndSCHEMATC
