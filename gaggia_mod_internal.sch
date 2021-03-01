EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Device:R R1
U 1 1 603D9A99
P 3700 3250
F 0 "R1" V 3493 3250 50  0000 C CNN
F 1 "10000" V 3584 3250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3630 3250 50  0001 C CNN
F 3 "~" H 3700 3250 50  0001 C CNN
	1    3700 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 603DA608
P 3700 3700
F 0 "R2" V 3493 3700 50  0000 C CNN
F 1 "10000" V 3584 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 3630 3700 50  0001 C CNN
F 3 "~" H 3700 3700 50  0001 C CNN
	1    3700 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 3250 4050 3250
Wire Wire Line
	3550 3250 3450 3250
Wire Wire Line
	3450 3700 3550 3700
$Comp
L Connector:Conn_01x02_Female J2
U 1 1 603DD8F9
P 4300 3050
F 0 "J2" V 4238 2862 50  0000 R CNN
F 1 "GroupheadThermistor" V 4147 2862 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4300 3050 50  0001 C CNN
F 3 "~" H 4300 3050 50  0001 C CNN
	1    4300 3050
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x02_Female J3
U 1 1 603DF456
P 4300 3500
F 0 "J3" V 4238 3312 50  0000 R CNN
F 1 "PumpThermistor" V 4147 3312 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4300 3500 50  0001 C CNN
F 3 "~" H 4300 3500 50  0001 C CNN
	1    4300 3500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 3250 4050 3400
Connection ~ 4050 3250
Wire Wire Line
	4050 3250 4300 3250
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 603E01E4
P 4700 4700
F 0 "J4" H 4780 4692 50  0000 L CNN
F 1 "PumpConnect" H 4780 4601 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2-5.08_1x02_P5.08mm_Horizontal" H 4700 4700 50  0001 C CNN
F 3 "~" H 4700 4700 50  0001 C CNN
	1    4700 4700
	1    0    0    -1  
$EndComp
$Comp
L Omron:G3MC202PDC24 K1
U 1 1 603E237A
P 2900 4550
F 0 "K1" H 3500 4915 50  0000 C CNN
F 1 "G3MC202PDC24" H 3500 4824 50  0000 C CNN
F 2 "SnapEDA Library:RELAY_G3MB202PDC12" H 2900 5050 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g3mc.pdf" H 2900 5150 50  0001 L CNN
F 4 "+80°C" H 2900 5250 50  0001 L CNN "ambient temperature range high"
F 5 "-30°C" H 2900 5350 50  0001 L CNN "ambient temperature range low"
F 6 "Relay" H 2900 5450 50  0001 L CNN "category"
F 7 "Electromechanical" H 2900 5550 50  0001 L CNN "device class L1"
F 8 "Relays" H 2900 5650 50  0001 L CNN "device class L2"
F 9 "Solid State Relays" H 2900 5750 50  0001 L CNN "device class L3"
F 10 "RELAY SSR SPST-NO SIP 24VDC" H 2900 5850 50  0001 L CNN "digikey description"
F 11 "Z2987-ND" H 2900 5950 50  0001 L CNN "digikey part number"
F 12 "20.5mm" H 2900 6050 50  0001 L CNN "height"
F 13 "yes" H 2900 6150 50  0001 L CNN "lead free"
F 14 "eac7530ef8727681" H 2900 6250 50  0001 L CNN "library id"
F 15 "Omron" H 2900 6350 50  0001 L CNN "manufacturer"
F 16 "Solid State Relays - PCB Mount 24VDC/100-240VAC 2A Zero cross snubber" H 2900 6450 50  0001 L CNN "mouser description"
F 17 "653-G3MC-202P-DC24" H 2900 6550 50  0001 L CNN "mouser part number"
F 18 "1" H 2900 6650 50  0001 L CNN "number of contacts"
F 19 "2A" H 2900 6750 50  0001 L CNN "output current"
F 20 "1.6V" H 2900 6850 50  0001 L CNN "output voltage"
F 21 "PTH_RELAY" H 2900 6950 50  0001 L CNN "package"
F 22 "yes" H 2900 7050 50  0001 L CNN "rohs"
F 23 "0.8mm" H 2900 7150 50  0001 L CNN "standoff height"
F 24 "+80°C" H 2900 7250 50  0001 L CNN "temperature range high"
F 25 "-30°C" H 2900 7350 50  0001 L CNN "temperature range low"
F 26 "SPST-NO" H 2900 7450 50  0001 L CNN "throw configuration"
F 27 "100-240V" H 2900 7550 50  0001 L CNN "voltage rating AC"
	1    2900 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4450 4500 4450
Wire Wire Line
	4500 4450 4500 4700
Wire Wire Line
	4000 5050 4500 5050
Wire Wire Line
	4500 5050 4500 4800
$Comp
L Device:R R3
U 1 1 603C2CFA
P 2800 4500
F 0 "R3" V 2593 4500 50  0000 C CNN
F 1 "220" V 2684 4500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 2730 4500 50  0001 C CNN
F 3 "~" H 2800 4500 50  0001 C CNN
	1    2800 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 4350 2900 4350
Wire Wire Line
	3000 4350 3000 4550
Wire Wire Line
	3000 4950 2800 4950
$Comp
L power:GND #PWR0101
U 1 1 6041A9D6
P 4400 3250
F 0 "#PWR0101" H 4400 3000 50  0001 C CNN
F 1 "GND" H 4405 3077 50  0000 C CNN
F 2 "" H 4400 3250 50  0001 C CNN
F 3 "" H 4400 3250 50  0001 C CNN
	1    4400 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 6041B8C9
P 4400 3700
F 0 "#PWR0102" H 4400 3450 50  0001 C CNN
F 1 "GND" H 4405 3527 50  0000 C CNN
F 2 "" H 4400 3700 50  0001 C CNN
F 3 "" H 4400 3700 50  0001 C CNN
	1    4400 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 3250 3450 3700
$Comp
L Connector:DB9_Male J1
U 1 1 6040A814
P 1950 3600
F 0 "J1" H 1868 2908 50  0000 C CNN
F 1 "DB9_Male" H 1868 2999 50  0000 C CNN
F 2 "Connector_Dsub:DSUB-9_Male_Horizontal_P2.77x2.84mm_EdgePinOffset4.94mm_Housed_MountingHolesOffset7.48mm" H 1950 3600 50  0001 C CNN
F 3 " ~" H 1950 3600 50  0001 C CNN
	1    1950 3600
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 60425392
P 2350 3200
F 0 "#PWR0103" H 2350 2950 50  0001 C CNN
F 1 "GND" H 2355 3027 50  0000 C CNN
F 2 "" H 2350 3200 50  0001 C CNN
F 3 "" H 2350 3200 50  0001 C CNN
	1    2350 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 6042602E
P 2800 4950
F 0 "#PWR0104" H 2800 4700 50  0001 C CNN
F 1 "GND" H 2805 4777 50  0000 C CNN
F 2 "" H 2800 4950 50  0001 C CNN
F 3 "" H 2800 4950 50  0001 C CNN
	1    2800 4950
	1    0    0    -1  
$EndComp
Connection ~ 2800 4950
$Comp
L Device:LED D1
U 1 1 603C21CF
P 2800 4800
F 0 "D1" V 2839 4682 50  0000 R CNN
F 1 "LED" V 2748 4682 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm_Horizontal_O1.27mm_Z2.0mm" H 2800 4800 50  0001 C CNN
F 3 "~" H 2800 4800 50  0001 C CNN
	1    2800 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2250 3200 2350 3200
Wire Wire Line
	2250 3600 3300 3600
Wire Wire Line
	3300 3600 3300 3400
Wire Wire Line
	3300 3400 4050 3400
Wire Wire Line
	2250 4000 2900 4000
Wire Wire Line
	2900 4000 2900 4350
Connection ~ 2900 4350
Wire Wire Line
	2900 4350 3000 4350
Wire Wire Line
	2250 3400 3150 3400
Wire Wire Line
	3150 3400 3150 3250
Wire Wire Line
	3150 3250 3450 3250
Connection ~ 3450 3250
NoConn ~ 2250 3300
NoConn ~ 2250 3500
NoConn ~ 2250 3700
NoConn ~ 2250 3900
Wire Wire Line
	3850 3700 4050 3700
Wire Wire Line
	4050 3800 4050 3700
Wire Wire Line
	2250 3800 4050 3800
Connection ~ 4050 3700
Wire Wire Line
	4050 3700 4300 3700
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 604388E9
P 3000 2850
F 0 "H2" H 3100 2899 50  0000 L CNN
F 1 "MountingHole_Pad" H 3100 2808 50  0000 L CNN
F 2 "MountingHole:MountingHole_4.3mm_M4_Pad" H 3000 2850 50  0001 C CNN
F 3 "~" H 3000 2850 50  0001 C CNN
	1    3000 2850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 604393E9
P 2700 2850
F 0 "H1" H 2800 2899 50  0000 L CNN
F 1 "MountingHole_Pad" H 2800 2808 50  0000 L CNN
F 2 "MountingHole:MountingHole_4.3mm_M4_Pad" H 2700 2850 50  0001 C CNN
F 3 "~" H 2700 2850 50  0001 C CNN
	1    2700 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 60439EEC
P 3000 2950
F 0 "#PWR0105" H 3000 2700 50  0001 C CNN
F 1 "GND" H 3005 2777 50  0000 C CNN
F 2 "" H 3000 2950 50  0001 C CNN
F 3 "" H 3000 2950 50  0001 C CNN
	1    3000 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6043A240
P 2700 2950
F 0 "#PWR0106" H 2700 2700 50  0001 C CNN
F 1 "GND" H 2705 2777 50  0000 C CNN
F 2 "" H 2700 2950 50  0001 C CNN
F 3 "" H 2700 2950 50  0001 C CNN
	1    2700 2950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
