EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 5
Title "MK2EE"
Date "2020-09-03"
Rev "1"
Comp "ETSETB/UPC"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3800 1700 700  500 
U 5F455032
F0 "supply" 50
F1 "supply.sch" 50
$EndSheet
$Sheet
S 2900 2600 2500 550 
U 5F475AB3
F0 "driver-1" 50
F1 "driver-1.sch" 50
$EndSheet
$Sheet
S 5800 2600 2600 550 
U 5F4C6CE4
F0 "encoder-1" 50
F1 "encoder-1.sch" 50
$EndSheet
Wire Notes Line
	2800 2400 5500 2400
Text Notes 3850 3400 0    100  ~ 0
DriverPCB
Wire Notes Line
	8500 2400 5700 2400
Text Notes 6700 3450 0    100  ~ 0
EncoderPCB
Wire Notes Line
	5400 2300 2800 2300
Text Notes 3450 1550 0    100  ~ 0
MCU+SupplyPCB
Wire Notes Line
	2800 1350 5400 1350
Wire Notes Line
	2800 1350 2800 2300
Wire Notes Line
	5400 1350 5400 2300
Wire Notes Line
	2800 2400 2800 3450
Wire Notes Line
	2800 3450 5500 3450
Wire Notes Line
	5500 2400 5500 3450
$Sheet
S 5850 3700 2550 600 
U 5F505E68
F0 "encoder-2" 50
F1 "encoder-2.sch" 50
$EndSheet
Wire Notes Line
	5700 4500 8500 4500
Wire Notes Line
	5700 2400 5700 4500
Wire Notes Line
	8500 2400 8500 4500
$EndSCHEMATC
