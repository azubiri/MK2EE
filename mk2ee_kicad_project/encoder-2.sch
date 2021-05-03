EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 5
Title "Encoder2 - PCB4"
Date "2021-02-09"
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
	9650 2550 9900 2550
Wire Wire Line
	9650 2250 9900 2250
Wire Wire Line
	9650 2350 9900 2350
Wire Wire Line
	9650 2450 9900 2450
Wire Wire Line
	9650 2850 9900 2850
Wire Wire Line
	9650 2650 9900 2650
Wire Wire Line
	9650 2750 9900 2750
Wire Wire Line
	9650 2150 9900 2150
Text GLabel 9650 2150 0    50   Output ~ 0
CLKEn4
Text GLabel 9650 2450 0    50   Output ~ 0
MISO4
Text GLabel 9650 2850 0    50   Output ~ 0
SH-CLKEn4
Text GLabel 9650 2250 0    50   Output ~ 0
SerialDataInEn4
Text GLabel 9650 2650 0    50   Output ~ 0
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
Text GLabel 9650 2050 0    50   Output ~ 0
PO-CLKDr4
Text GLabel 9650 2550 0    50   Output ~ 0
SH-CLKDr4
Text GLabel 9650 3050 0    50   Output ~ 0
VCCF3v3
Text GLabel 9650 2750 0    50   Output ~ 0
SerialDataDr4
Text GLabel 9650 3150 0    50   Output ~ 0
VMC
Wire Wire Line
	9650 3050 9850 3050
Wire Wire Line
	9650 3150 9900 3150
Wire Wire Line
	9650 5150 9900 5150
Wire Wire Line
	9650 3850 9900 3850
Wire Wire Line
	9650 3750 9900 3750
Wire Wire Line
	9650 5050 9900 5050
Wire Wire Line
	9650 5250 9900 5250
Text GLabel 9650 3750 0    50   Input ~ 0
CLKEn4
Text GLabel 9650 3850 0    50   Input ~ 0
MISO4
Text GLabel 9650 5150 0    50   Input ~ 0
SH-CLKEn4
Text GLabel 9650 5050 0    50   Input ~ 0
SerialDataOutEn4
Text GLabel 9650 5250 0    50   Input ~ 0
PO-CLKEn4
Text GLabel 9550 3950 0    50   Input ~ 0
SerialDataDr4
Text GLabel 9550 4950 0    50   Input ~ 0
SH-CLKDr4
Text GLabel 9550 4750 0    50   Input ~ 0
PO-CLKDr4
Text GLabel 9550 4250 0    50   Input ~ 0
VMC
Wire Wire Line
	9550 4950 9900 4950
Wire Wire Line
	9550 4750 9900 4750
Wire Wire Line
	9550 3950 9900 3950
Wire Wire Line
	9550 4250 9900 4250
Wire Wire Line
	9900 4150 9150 4150
Wire Wire Line
	9150 4150 9150 4300
$Comp
L power:GND #PWR?
U 1 1 5F53EADC
P 9150 4300
AR Path="/5F4C6CE4/5F53EADC" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F53EADC" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F53EADC" Ref="#PWR0134"  Part="1" 
F 0 "#PWR0134" H 9150 4050 50  0001 C CNN
F 1 "GND" H 9155 4127 50  0000 C CNN
F 2 "" H 9150 4300 50  0001 C CNN
F 3 "" H 9150 4300 50  0001 C CNN
	1    9150 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F5DDE3D
P 9650 2950
AR Path="/5F4C6CE4/5F5DDE3D" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F5DDE3D" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F5DDE3D" Ref="#PWR0136"  Part="1" 
F 0 "#PWR0136" H 9650 2700 50  0001 C CNN
F 1 "GND" H 9655 2777 50  0000 C CNN
F 2 "" H 9650 2950 50  0001 C CNN
F 3 "" H 9650 2950 50  0001 C CNN
	1    9650 2950
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
Wire Wire Line
	3450 2000 3450 2400
$Comp
L power:GND #PWR?
U 1 1 5F9DF237
P 3450 3700
AR Path="/5F4C6CE4/5F9DF237" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F9DF237" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F9DF237" Ref="#PWR0149"  Part="1" 
F 0 "#PWR0149" H 3450 3450 50  0001 C CNN
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
Wire Wire Line
	3050 2900 2900 2900
Wire Wire Line
	2900 2900 2900 2000
Connection ~ 2900 2000
Wire Wire Line
	2900 2000 3450 2000
$Comp
L power:GND #PWR?
U 1 1 5F9DF24E
P 2600 2300
AR Path="/5F4C6CE4/5F9DF24E" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/5F9DF24E" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/5F9DF24E" Ref="#PWR0150"  Part="1" 
F 0 "#PWR0150" H 2600 2050 50  0001 C CNN
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
Text GLabel 9650 2350 0    50   Output ~ 0
PWM4
Text GLabel 9550 4850 0    50   Input ~ 0
PWM4
Wire Wire Line
	9550 4850 9900 4850
Text Notes 5900 1650 0    100  ~ 0
Magnetic Encoder
Text Notes 2100 1750 0    100  ~ 0
Shift Registers with Parallel Output
Text Notes 9400 1750 0    100  ~ 0
Connectors
$Comp
L 74xx:74HC595 U?
U 1 1 6023EEEB
P 3450 3000
AR Path="/5F4C6CE4/6023EEEB" Ref="U?"  Part="1" 
AR Path="/5F505E68/6023EEEB" Ref="U11"  Part="1" 
F 0 "U11" H 3450 3781 50  0000 C CNN
F 1 "74HC595" H 3450 3690 50  0000 C CNN
F 2 "MK2Library:SN74HC595PWR" H 3450 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 3450 3000 50  0001 C CNN
F 4 "SN74HC595PWR" H 3450 3000 50  0001 C CNN "Name"
F 5 "Texas Instruments" H 3450 3000 50  0001 C CNN "Manufacturer"
	1    3450 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 60249757
P 10100 4050
AR Path="/5F475AB3/60249757" Ref="J?"  Part="1" 
AR Path="/5F4C6CE4/60249757" Ref="J?"  Part="1" 
AR Path="/5F505E68/60249757" Ref="J12"  Part="1" 
F 0 "J12" H 10072 3887 50  0000 R CNN
F 1 "Conn_01x06_Male" H 10072 3978 50  0000 R CNN
F 2 "MK2Library:Molex_MicroClasp_55932-0610_1x06_P2.00mm_Vertical" H 10100 4050 50  0001 C CNN
F 3 "~" H 10100 4050 50  0001 C CNN
F 4 "55932-0610 " H 10072 4069 50  0000 R CNN "Name"
F 5 "Molex" H 10100 4050 50  0001 C CNN "Manufacturer"
	1    10100 4050
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 6022FE7E
P 10100 5050
AR Path="/5F475AB3/6022FE7E" Ref="J?"  Part="1" 
AR Path="/5F4C6CE4/6022FE7E" Ref="J?"  Part="1" 
AR Path="/5F505E68/6022FE7E" Ref="J13"  Part="1" 
F 0 "J13" H 10072 4887 50  0000 R CNN
F 1 "Conn_01x06_Male" H 10072 4978 50  0000 R CNN
F 2 "MK2Library:Molex_MicroClasp_55932-0610_1x06_P2.00mm_Vertical" H 10100 5050 50  0001 C CNN
F 3 "~" H 10100 5050 50  0001 C CNN
F 4 "55932-0610" H 10072 5069 50  0000 R CNN "Name"
F 5 "Molex" H 10100 5050 50  0001 C CNN "Manufacturer"
	1    10100 5050
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x12_Male J11
U 1 1 6024674F
P 10100 2650
AR Path="/5F505E68/6024674F" Ref="J11"  Part="1" 
AR Path="/5F4C637B/6024674F" Ref="J?"  Part="1" 
AR Path="/5F455032/6024674F" Ref="J?"  Part="1" 
F 0 "J11" H 10208 3421 50  0000 C CNN
F 1 "Conn_02x6_Male" H 10208 3330 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x06_P2.54mm_Horizontal" H 10100 2650 50  0001 C CNN
F 3 "~" H 10100 2650 50  0001 C CNN
F 4 "T821112A1R100CEU" H 10208 3239 50  0000 C CNN "Name"
F 5 "AMPHENOL ICC" H 10100 2650 50  0001 C CNN "Manufacturer"
	1    10100 2650
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG?
U 1 1 60304507
P 9850 3050
AR Path="/5F455032/60304507" Ref="#FLG?"  Part="1" 
AR Path="/5F4C637B/60304507" Ref="#FLG?"  Part="1" 
AR Path="/5F505E68/60304507" Ref="#FLG0108"  Part="1" 
F 0 "#FLG0108" H 9850 3125 50  0001 C CNN
F 1 "PWR_FLAG" H 9850 3223 50  0000 C CNN
F 2 "" H 9850 3050 50  0001 C CNN
F 3 "~" H 9850 3050 50  0001 C CNN
	1    9850 3050
	1    0    0    -1  
$EndComp
Text Label 3300 2000 2    50   ~ 0
pwr12
$Comp
L Device:C C?
U 1 1 603335FB
P 7350 2550
AR Path="/5F4C6CE4/603335FB" Ref="C?"  Part="1" 
AR Path="/5F475AB3/603335FB" Ref="C?"  Part="1" 
AR Path="/5F505E68/603335FB" Ref="C23"  Part="1" 
F 0 "C23" H 7465 2596 50  0000 L CNN
F 1 "100nF" H 7465 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 7388 2400 50  0001 C CNN
F 3 "~" H 7350 2550 50  0001 C CNN
F 4 "C1206C104K5RACTU" H 7350 2550 50  0001 C CNN "Name"
F 5 "Kemet" H 7350 2550 50  0001 C CNN "Manufacturer"
	1    7350 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2000 2600 2000
$Comp
L Device:C C?
U 1 1 6033F2EA
P 2600 2150
AR Path="/5F4C6CE4/6033F2EA" Ref="C?"  Part="1" 
AR Path="/5F475AB3/6033F2EA" Ref="C?"  Part="1" 
AR Path="/5F505E68/6033F2EA" Ref="C22"  Part="1" 
F 0 "C22" H 2715 2196 50  0000 L CNN
F 1 "100nF" H 2715 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 2638 2000 50  0001 C CNN
F 3 "~" H 2600 2150 50  0001 C CNN
F 4 "C1206C104K5RACTU" H 2600 2150 50  0001 C CNN "Name"
F 5 "Kemet" H 2600 2150 50  0001 C CNN "Manufacturer"
	1    2600 2150
	1    0    0    -1  
$EndComp
Connection ~ 2600 2000
Wire Wire Line
	2600 2000 2900 2000
Connection ~ 9850 3050
Wire Wire Line
	9850 3050 9900 3050
Wire Wire Line
	9650 2950 9900 2950
NoConn ~ 9900 4050
$Comp
L Connector:TestPoint TP?
U 1 1 608DDC15
P 6050 3800
AR Path="/5F455032/608DDC15" Ref="TP?"  Part="1" 
AR Path="/5F4C637B/608DDC15" Ref="TP?"  Part="1" 
AR Path="/5F475AB3/608DDC15" Ref="TP?"  Part="1" 
AR Path="/5F505E68/608DDC15" Ref="TP13"  Part="1" 
F 0 "TP13" H 6108 3918 50  0000 L CNN
F 1 "TestPoint" H 6108 3827 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 6250 3800 50  0001 C CNN
F 3 "~" H 6250 3800 50  0001 C CNN
	1    6050 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 608DF432
P 6050 3800
AR Path="/5F4C6CE4/608DF432" Ref="#PWR?"  Part="1" 
AR Path="/5F4C6BF4/608DF432" Ref="#PWR?"  Part="1" 
AR Path="/5F505E68/608DF432" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6050 3550 50  0001 C CNN
F 1 "GND" H 6055 3627 50  0000 C CNN
F 2 "" H 6050 3800 50  0001 C CNN
F 3 "" H 6050 3800 50  0001 C CNN
	1    6050 3800
	1    0    0    -1  
$EndComp
$EndSCHEMATC
