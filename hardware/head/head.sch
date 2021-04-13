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
L Connector:Conn_01x05_Male J8
U 1 1 604B08C7
P 6200 5350
F 0 "J8" H 6172 5282 50  0000 R CNN
F 1 "Rotary_Encoder" H 6172 5373 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6200 5350 50  0001 C CNN
F 3 "~" H 6200 5350 50  0001 C CNN
	1    6200 5350
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 604B1FDA
P 6000 5150
F 0 "#PWR0103" H 6000 4900 50  0001 C CNN
F 1 "GND" V 6005 5022 50  0000 R CNN
F 2 "" H 6000 5150 50  0001 C CNN
F 3 "" H 6000 5150 50  0001 C CNN
	1    6000 5150
	0    1    1    0   
$EndComp
Text GLabel 6000 5350 0    50   Input ~ 0
ENCODER_BUTTON
Text GLabel 6000 5450 0    50   Input ~ 0
ENCODER_DATA
Text GLabel 6000 5550 0    50   Input ~ 0
ENCODER_CLOCK
$Comp
L Connector:Conn_01x04_Male J6
U 1 1 604B43FD
P 6200 4200
F 0 "J6" H 6172 4082 50  0000 R CNN
F 1 "Display" H 6172 4173 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6200 4200 50  0001 C CNN
F 3 "~" H 6200 4200 50  0001 C CNN
	1    6200 4200
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Male J7
U 1 1 604B63C3
P 6200 4850
F 0 "J7" H 6172 4732 50  0000 R CNN
F 1 "Load_Cell" H 6172 4823 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6200 4850 50  0001 C CNN
F 3 "~" H 6200 4850 50  0001 C CNN
	1    6200 4850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 604B6949
P 6000 4000
F 0 "#PWR0105" H 6000 3750 50  0001 C CNN
F 1 "GND" V 6005 3872 50  0000 R CNN
F 2 "" H 6000 4000 50  0001 C CNN
F 3 "" H 6000 4000 50  0001 C CNN
	1    6000 4000
	0    1    1    0   
$EndComp
Text GLabel 6000 4200 0    50   Input ~ 0
DISPLAY_SCL
Text GLabel 6000 4300 0    50   Input ~ 0
DISPLAY_SDA
$Comp
L power:GND #PWR0107
U 1 1 604B7917
P 6000 4650
F 0 "#PWR0107" H 6000 4400 50  0001 C CNN
F 1 "GND" V 6005 4522 50  0000 R CNN
F 2 "" H 6000 4650 50  0001 C CNN
F 3 "" H 6000 4650 50  0001 C CNN
	1    6000 4650
	0    1    1    0   
$EndComp
Text GLabel 6000 4750 0    50   Input ~ 0
LOAD_CELL+
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 604B8D51
P 3900 5400
F 0 "J5" H 3872 5282 50  0000 R CNN
F 1 "Temp_Ok" H 3872 5373 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3900 5400 50  0001 C CNN
F 3 "~" H 3900 5400 50  0001 C CNN
	1    3900 5400
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 604B98BA
P 3400 5300
F 0 "#PWR0109" H 3400 5050 50  0001 C CNN
F 1 "GND" V 3405 5172 50  0000 R CNN
F 2 "" H 3400 5300 50  0001 C CNN
F 3 "" H 3400 5300 50  0001 C CNN
	1    3400 5300
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 604BA74B
P 3550 5300
F 0 "R1" V 3343 5300 50  0000 C CNN
F 1 "220" V 3434 5300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3480 5300 50  0001 C CNN
F 3 "~" H 3550 5300 50  0001 C CNN
	1    3550 5300
	0    1    1    0   
$EndComp
Text GLabel 3700 5400 0    50   Input ~ 0
TEMP_OK
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 604C5045
P 6200 2800
F 0 "J3" H 6172 2682 50  0000 R CNN
F 1 "Flush_Button" H 6172 2773 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6200 2800 50  0001 C CNN
F 3 "~" H 6200 2800 50  0001 C CNN
	1    6200 2800
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 604C54A0
P 6000 2700
F 0 "#PWR0111" H 6000 2450 50  0001 C CNN
F 1 "GND" V 6005 2572 50  0000 R CNN
F 2 "" H 6000 2700 50  0001 C CNN
F 3 "" H 6000 2700 50  0001 C CNN
	1    6000 2700
	0    1    1    0   
$EndComp
Text GLabel 6000 2800 0    50   Input ~ 0
FLUSH_BUTTON
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 604D0F1E
P 6200 3150
F 0 "J2" H 6172 3032 50  0000 R CNN
F 1 "Stats_Button" H 6172 3123 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6200 3150 50  0001 C CNN
F 3 "~" H 6200 3150 50  0001 C CNN
	1    6200 3150
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 604D135D
P 6000 3050
F 0 "#PWR0112" H 6000 2800 50  0001 C CNN
F 1 "GND" V 6005 2922 50  0000 R CNN
F 2 "" H 6000 3050 50  0001 C CNN
F 3 "" H 6000 3050 50  0001 C CNN
	1    6000 3050
	0    1    1    0   
$EndComp
Text GLabel 6000 3150 0    50   Input ~ 0
STATS_BUTTON
$Comp
L Connector:DB9_Male J1
U 1 1 604D2002
P 6150 1750
F 0 "J1" H 6330 1796 50  0000 L CNN
F 1 "DB9_Male" H 6330 1705 50  0000 L CNN
F 2 "Connector_Dsub:DSUB-9_Male_Horizontal_P2.77x2.84mm_EdgePinOffset4.94mm_Housed_MountingHolesOffset7.48mm" H 6150 1750 50  0001 C CNN
F 3 " ~" H 6150 1750 50  0001 C CNN
	1    6150 1750
	1    0    0    -1  
$EndComp
$Comp
L teensy:Teensy4.0 U1
U 1 1 604FC8EB
P 3000 3350
F 0 "U1" H 3000 4965 50  0000 C CNN
F 1 "Teensy4.0" H 3000 4874 50  0000 C CNN
F 2 "teensy:Teensy40_SMT" H 2600 3550 50  0001 C CNN
F 3 "" H 2600 3550 50  0001 C CNN
	1    3000 3350
	1    0    0    -1  
$EndComp
Text GLabel 1900 4500 0    50   Input ~ 0
DISPLAY_SCL
Text GLabel 1900 4400 0    50   Input ~ 0
DISPLAY_SDA
Text GLabel 1900 2300 0    50   Input ~ 0
ENCODER_BUTTON
Text GLabel 1900 2400 0    50   Input ~ 0
ENCODER_DATA
Text GLabel 1900 2500 0    50   Input ~ 0
ENCODER_CLOCK
Text GLabel 1900 2600 0    50   Input ~ 0
FLUSH_BUTTON
Text GLabel 1900 2700 0    50   Input ~ 0
BREW_BUTTON
Text GLabel 1900 2800 0    50   Input ~ 0
STATS_BUTTON
Text GLabel 1900 3000 0    50   Input ~ 0
TEMP_OK
$Comp
L power:GND #PWR01
U 1 1 60520795
P 1900 2000
F 0 "#PWR01" H 1900 1750 50  0001 C CNN
F 1 "GND" V 1905 1872 50  0000 R CNN
F 2 "" H 1900 2000 50  0001 C CNN
F 3 "" H 1900 2000 50  0001 C CNN
	1    1900 2000
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 60521EE0
P 4100 4500
F 0 "#PWR05" H 4100 4350 50  0001 C CNN
F 1 "+3.3V" H 4115 4673 50  0000 C CNN
F 2 "" H 4100 4500 50  0001 C CNN
F 3 "" H 4100 4500 50  0001 C CNN
	1    4100 4500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 60522C1C
P 1900 3600
F 0 "#PWR02" H 1900 3350 50  0001 C CNN
F 1 "GND" V 1905 3472 50  0000 R CNN
F 2 "" H 1900 3600 50  0001 C CNN
F 3 "" H 1900 3600 50  0001 C CNN
	1    1900 3600
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 60523242
P 4100 4400
F 0 "#PWR04" H 4100 4150 50  0001 C CNN
F 1 "GND" V 4105 4272 50  0000 R CNN
F 2 "" H 4100 4400 50  0001 C CNN
F 3 "" H 4100 4400 50  0001 C CNN
	1    4100 4400
	0    -1   -1   0   
$EndComp
NoConn ~ 1900 3400
NoConn ~ 1900 3500
NoConn ~ 1900 2200
NoConn ~ 1900 2100
NoConn ~ 1900 3700
NoConn ~ 1900 3800
NoConn ~ 1900 3900
NoConn ~ 1900 4600
NoConn ~ 1900 4700
NoConn ~ 4100 4600
NoConn ~ 4100 4700
$Comp
L power:+3.3V #PWR0101
U 1 1 60527563
P 6000 5250
F 0 "#PWR0101" H 6000 5100 50  0001 C CNN
F 1 "+3.3V" V 6015 5378 50  0000 L CNN
F 2 "" H 6000 5250 50  0001 C CNN
F 3 "" H 6000 5250 50  0001 C CNN
	1    6000 5250
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 60528F10
P 6000 4950
F 0 "#PWR0102" H 6000 4800 50  0001 C CNN
F 1 "+3.3V" V 6015 5078 50  0000 L CNN
F 2 "" H 6000 4950 50  0001 C CNN
F 3 "" H 6000 4950 50  0001 C CNN
	1    6000 4950
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR0104
U 1 1 605298C9
P 6000 4100
F 0 "#PWR0104" H 6000 3950 50  0001 C CNN
F 1 "+3.3V" V 6015 4228 50  0000 L CNN
F 2 "" H 6000 4100 50  0001 C CNN
F 3 "" H 6000 4100 50  0001 C CNN
	1    6000 4100
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 6053C7F2
P 3800 1200
F 0 "H2" H 3900 1249 50  0000 L CNN
F 1 "MountingHole_Pad" H 3900 1158 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm_Pad" H 3800 1200 50  0001 C CNN
F 3 "~" H 3800 1200 50  0001 C CNN
	1    3800 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6053E6FD
P 3800 1300
F 0 "#PWR08" H 3800 1050 50  0001 C CNN
F 1 "GND" V 3805 1172 50  0000 R CNN
F 2 "" H 3800 1300 50  0001 C CNN
F 3 "" H 3800 1300 50  0001 C CNN
	1    3800 1300
	1    0    0    -1  
$EndComp
Text GLabel 5850 2150 0    50   Input ~ 0
HEATER_SSR+
Text GLabel 5850 1750 0    50   Input ~ 0
PUMP_SSR+
$Comp
L power:GND #PWR019
U 1 1 606BE46B
P 5850 1550
F 0 "#PWR019" H 5850 1300 50  0001 C CNN
F 1 "GND" V 5855 1422 50  0000 R CNN
F 2 "" H 5850 1550 50  0001 C CNN
F 3 "" H 5850 1550 50  0001 C CNN
	1    5850 1550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 606BE6FE
P 5850 1950
F 0 "#PWR020" H 5850 1700 50  0001 C CNN
F 1 "GND" V 5855 1822 50  0000 R CNN
F 2 "" H 5850 1950 50  0001 C CNN
F 3 "" H 5850 1950 50  0001 C CNN
	1    5850 1950
	0    1    1    0   
$EndComp
Text GLabel 5850 1350 0    50   Input ~ 0
BOILER_TOP_TEMP+
Text GLabel 5850 2050 0    50   Input ~ 0
BOILER_TOP_TEMP-
Text GLabel 5850 1650 0    50   Input ~ 0
BOILER_BOTTOM_TEMP-
Text GLabel 5850 1850 0    50   Input ~ 0
BOILER_BOTTOM_TEMP+
NoConn ~ 5850 1450
Text GLabel 1900 3200 0    50   Input ~ 0
HEATER_SSR+
Text GLabel 1900 3100 0    50   Input ~ 0
PUMP_SSR+
$Comp
L Amplifier_Instrumentation:INA128 U4
U 1 1 606C15BD
P 9800 3550
F 0 "U4" H 10244 3596 50  0000 L CNN
F 1 "INA126" H 10244 3505 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9900 3550 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/ina126.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1617679302882" H 9900 3550 50  0001 C CNN
	1    9800 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 606C21F7
P 8800 3550
F 0 "C8" H 8915 3596 50  0000 L CNN
F 1 "10nF" H 8915 3505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 3400 50  0001 C CNN
F 3 "~" H 8800 3550 50  0001 C CNN
	1    8800 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 606C2CD8
P 8200 4000
F 0 "R9" H 8270 4046 50  0000 L CNN
F 1 "1M" H 8270 3955 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8130 4000 50  0001 C CNN
F 3 "~" H 8200 4000 50  0001 C CNN
	1    8200 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 606C3597
P 8350 3350
F 0 "R7" H 8420 3396 50  0000 L CNN
F 1 "10k" H 8420 3305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 3350 50  0001 C CNN
F 3 "~" H 8350 3350 50  0001 C CNN
	1    8350 3350
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C7
U 1 1 606C463B
P 8800 3200
F 0 "C7" H 8915 3246 50  0000 L CNN
F 1 "1nF" H 8915 3155 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 3050 50  0001 C CNN
F 3 "~" H 8800 3200 50  0001 C CNN
	1    8800 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 606C4816
P 8800 3900
F 0 "C9" H 8915 3946 50  0000 L CNN
F 1 "1nF" H 8915 3855 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 3750 50  0001 C CNN
F 3 "~" H 8800 3900 50  0001 C CNN
	1    8800 3900
	1    0    0    -1  
$EndComp
Text GLabel 8100 3750 0    50   Input ~ 0
BOILER_BOTTOM_TEMP-
Text GLabel 8100 3350 0    50   Input ~ 0
BOILER_BOTTOM_TEMP+
$Comp
L Device:R R8
U 1 1 606C70FD
P 8350 3750
F 0 "R8" H 8420 3796 50  0000 L CNN
F 1 "10k" H 8420 3705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 3750 50  0001 C CNN
F 3 "~" H 8350 3750 50  0001 C CNN
	1    8350 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 606C79BF
P 8200 4150
F 0 "#PWR022" H 8200 3900 50  0001 C CNN
F 1 "GND" V 8205 4022 50  0000 R CNN
F 2 "" H 8200 4150 50  0001 C CNN
F 3 "" H 8200 4150 50  0001 C CNN
	1    8200 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3750 8200 3750
Wire Wire Line
	8200 3750 8200 3850
Connection ~ 8200 3750
Wire Wire Line
	8200 3350 8100 3350
$Comp
L power:GND #PWR027
U 1 1 606CA82F
P 8800 4050
F 0 "#PWR027" H 8800 3800 50  0001 C CNN
F 1 "GND" V 8805 3922 50  0000 R CNN
F 2 "" H 8800 4050 50  0001 C CNN
F 3 "" H 8800 4050 50  0001 C CNN
	1    8800 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 606CAB11
P 8800 3050
F 0 "#PWR026" H 8800 2800 50  0001 C CNN
F 1 "GND" V 8805 2922 50  0000 R CNN
F 2 "" H 8800 3050 50  0001 C CNN
F 3 "" H 8800 3050 50  0001 C CNN
	1    8800 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	8800 3750 9500 3750
Wire Wire Line
	8500 3350 8800 3350
Wire Wire Line
	8800 3350 8800 3400
Connection ~ 8800 3350
Wire Wire Line
	8800 3700 8800 3750
Connection ~ 8800 3750
Wire Wire Line
	8500 3750 8800 3750
Wire Wire Line
	8800 3350 9500 3350
$Comp
L Device:R R14
U 1 1 606CFF0A
P 9300 3550
F 0 "R14" H 9370 3596 50  0000 L CNN
F 1 "400" H 9370 3505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 9230 3550 50  0001 C CNN
F 3 "~" H 9300 3550 50  0001 C CNN
	1    9300 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3400 9500 3400
Wire Wire Line
	9500 3400 9500 3450
Wire Wire Line
	9300 3700 9500 3700
Wire Wire Line
	9500 3700 9500 3650
$Comp
L power:GND #PWR033
U 1 1 606D15EB
P 9800 3850
F 0 "#PWR033" H 9800 3600 50  0001 C CNN
F 1 "GND" V 9805 3722 50  0000 R CNN
F 2 "" H 9800 3850 50  0001 C CNN
F 3 "" H 9800 3850 50  0001 C CNN
	1    9800 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR032
U 1 1 606D187E
P 9800 3250
F 0 "#PWR032" H 9800 3100 50  0001 C CNN
F 1 "+3.3V" V 9815 3378 50  0000 L CNN
F 2 "" H 9800 3250 50  0001 C CNN
F 3 "" H 9800 3250 50  0001 C CNN
	1    9800 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 606D25C0
P 9950 3250
F 0 "C14" H 10065 3296 50  0000 L CNN
F 1 "0.1uF" H 10065 3205 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 9988 3100 50  0001 C CNN
F 3 "~" H 9950 3250 50  0001 C CNN
	1    9950 3250
	0    -1   -1   0   
$EndComp
Connection ~ 9800 3250
$Comp
L power:GND #PWR037
U 1 1 606D390B
P 10100 3250
F 0 "#PWR037" H 10100 3000 50  0001 C CNN
F 1 "GND" V 10105 3122 50  0000 R CNN
F 2 "" H 10100 3250 50  0001 C CNN
F 3 "" H 10100 3250 50  0001 C CNN
	1    10100 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9900 3850 9800 3850
Connection ~ 9800 3850
Text GLabel 1900 4000 0    50   Input ~ 0
BOILER_BOTTOM_TEMP
Text GLabel 1900 4100 0    50   Input ~ 0
BOILER_TOP_TEMP
Text GLabel 10200 3550 2    50   Input ~ 0
BOILER_BOTTOM_TEMP
$Comp
L Amplifier_Instrumentation:INA128 U5
U 1 1 606DED96
P 9800 5300
F 0 "U5" H 10244 5346 50  0000 L CNN
F 1 "INA126" H 10244 5255 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9900 5300 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/ina126.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1617679302882" H 9900 5300 50  0001 C CNN
	1    9800 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 606DED9C
P 8800 5300
F 0 "C11" H 8915 5346 50  0000 L CNN
F 1 "10nF" H 8915 5255 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 5150 50  0001 C CNN
F 3 "~" H 8800 5300 50  0001 C CNN
	1    8800 5300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 606DEDA2
P 8200 5750
F 0 "R12" H 8270 5796 50  0000 L CNN
F 1 "1M" H 8270 5705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8130 5750 50  0001 C CNN
F 3 "~" H 8200 5750 50  0001 C CNN
	1    8200 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 606DEDA8
P 8350 5100
F 0 "R10" V 8557 5100 50  0000 C CNN
F 1 "10k" V 8466 5100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 5100 50  0001 C CNN
F 3 "~" H 8350 5100 50  0001 C CNN
	1    8350 5100
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C10
U 1 1 606DEDAE
P 8800 4950
F 0 "C10" H 8915 4996 50  0000 L CNN
F 1 "1nF" H 8915 4905 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 4800 50  0001 C CNN
F 3 "~" H 8800 4950 50  0001 C CNN
	1    8800 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 606DEDB4
P 8800 5650
F 0 "C12" H 8915 5696 50  0000 L CNN
F 1 "1nF" H 8915 5605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 5500 50  0001 C CNN
F 3 "~" H 8800 5650 50  0001 C CNN
	1    8800 5650
	1    0    0    -1  
$EndComp
Text GLabel 8100 5500 0    50   Input ~ 0
BOILER_TOP_TEMP-
Text GLabel 8100 5100 0    50   Input ~ 0
BOILER_TOP_TEMP+
$Comp
L Device:R R11
U 1 1 606DEDBC
P 8350 5500
F 0 "R11" V 8557 5500 50  0000 C CNN
F 1 "10k" V 8466 5500 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 5500 50  0001 C CNN
F 3 "~" H 8350 5500 50  0001 C CNN
	1    8350 5500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR021
U 1 1 606DEDC2
P 8200 5900
F 0 "#PWR021" H 8200 5650 50  0001 C CNN
F 1 "GND" V 8205 5772 50  0000 R CNN
F 2 "" H 8200 5900 50  0001 C CNN
F 3 "" H 8200 5900 50  0001 C CNN
	1    8200 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 5500 8200 5500
Wire Wire Line
	8200 5500 8200 5600
Connection ~ 8200 5500
Wire Wire Line
	8200 5100 8100 5100
$Comp
L power:GND #PWR025
U 1 1 606DEDCC
P 8800 5800
F 0 "#PWR025" H 8800 5550 50  0001 C CNN
F 1 "GND" V 8805 5672 50  0000 R CNN
F 2 "" H 8800 5800 50  0001 C CNN
F 3 "" H 8800 5800 50  0001 C CNN
	1    8800 5800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 606DEDD2
P 8800 4800
F 0 "#PWR024" H 8800 4550 50  0001 C CNN
F 1 "GND" V 8805 4672 50  0000 R CNN
F 2 "" H 8800 4800 50  0001 C CNN
F 3 "" H 8800 4800 50  0001 C CNN
	1    8800 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	8800 5500 9500 5500
Wire Wire Line
	8500 5100 8800 5100
Wire Wire Line
	8800 5100 8800 5150
Connection ~ 8800 5100
Wire Wire Line
	8800 5450 8800 5500
Connection ~ 8800 5500
Wire Wire Line
	8500 5500 8800 5500
Wire Wire Line
	8800 5100 9500 5100
$Comp
L Device:R R15
U 1 1 606DEDE0
P 9300 5300
F 0 "R15" H 9370 5346 50  0000 L CNN
F 1 "400" H 9370 5255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 9230 5300 50  0001 C CNN
F 3 "~" H 9300 5300 50  0001 C CNN
	1    9300 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 5150 9500 5150
Wire Wire Line
	9500 5150 9500 5200
Wire Wire Line
	9300 5450 9500 5450
Wire Wire Line
	9500 5450 9500 5400
$Comp
L power:GND #PWR031
U 1 1 606DEDEA
P 9800 5600
F 0 "#PWR031" H 9800 5350 50  0001 C CNN
F 1 "GND" V 9805 5472 50  0000 R CNN
F 2 "" H 9800 5600 50  0001 C CNN
F 3 "" H 9800 5600 50  0001 C CNN
	1    9800 5600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR030
U 1 1 606DEDF0
P 9800 5000
F 0 "#PWR030" H 9800 4850 50  0001 C CNN
F 1 "+3.3V" V 9815 5128 50  0000 L CNN
F 2 "" H 9800 5000 50  0001 C CNN
F 3 "" H 9800 5000 50  0001 C CNN
	1    9800 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 606DEDF6
P 9950 5000
F 0 "C15" V 10202 5000 50  0000 C CNN
F 1 "0.1uF" V 10111 5000 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 9988 4850 50  0001 C CNN
F 3 "~" H 9950 5000 50  0001 C CNN
	1    9950 5000
	0    -1   -1   0   
$EndComp
Connection ~ 9800 5000
$Comp
L power:GND #PWR036
U 1 1 606DEDFD
P 10100 5000
F 0 "#PWR036" H 10100 4750 50  0001 C CNN
F 1 "GND" V 10105 4872 50  0000 R CNN
F 2 "" H 10100 5000 50  0001 C CNN
F 3 "" H 10100 5000 50  0001 C CNN
	1    10100 5000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9900 5600 9800 5600
Connection ~ 9800 5600
Text GLabel 10200 5300 2    50   Input ~ 0
BOILER_TOP_TEMP
$Comp
L Amplifier_Instrumentation:INA128 U3
U 1 1 606E897A
P 9800 1750
F 0 "U3" H 10244 1796 50  0000 L CNN
F 1 "INA126" H 10244 1705 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 9900 1750 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/ina126.pdf?HQS=dis-dk-null-digikeymode-dsf-pf-null-wwe&ts=1617679302882" H 9900 1750 50  0001 C CNN
	1    9800 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 606E8980
P 8800 1750
F 0 "C5" H 8915 1796 50  0000 L CNN
F 1 "10nF" H 8915 1705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 1600 50  0001 C CNN
F 3 "~" H 8800 1750 50  0001 C CNN
	1    8800 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 606E8986
P 8200 2200
F 0 "R6" H 8270 2246 50  0000 L CNN
F 1 "1M" H 8270 2155 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8130 2200 50  0001 C CNN
F 3 "~" H 8200 2200 50  0001 C CNN
	1    8200 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 606E898C
P 8350 1550
F 0 "R4" V 8557 1550 50  0000 C CNN
F 1 "10k" V 8466 1550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 1550 50  0001 C CNN
F 3 "~" H 8350 1550 50  0001 C CNN
	1    8350 1550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C4
U 1 1 606E8992
P 8800 1400
F 0 "C4" H 8915 1446 50  0000 L CNN
F 1 "1nF" H 8915 1355 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 1250 50  0001 C CNN
F 3 "~" H 8800 1400 50  0001 C CNN
	1    8800 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 606E8998
P 8800 2100
F 0 "C6" H 8915 2146 50  0000 L CNN
F 1 "1nF" H 8915 2055 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 8838 1950 50  0001 C CNN
F 3 "~" H 8800 2100 50  0001 C CNN
	1    8800 2100
	1    0    0    -1  
$EndComp
Text GLabel 8100 1950 0    50   Input ~ 0
LOAD_CELL-
Text GLabel 8100 1550 0    50   Input ~ 0
LOAD_CELL+
$Comp
L Device:R R5
U 1 1 606E89A0
P 8350 1950
F 0 "R5" V 8557 1950 50  0000 C CNN
F 1 "10k" V 8466 1950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 8280 1950 50  0001 C CNN
F 3 "~" H 8350 1950 50  0001 C CNN
	1    8350 1950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR023
U 1 1 606E89A6
P 8200 2350
F 0 "#PWR023" H 8200 2100 50  0001 C CNN
F 1 "GND" V 8205 2222 50  0000 R CNN
F 2 "" H 8200 2350 50  0001 C CNN
F 3 "" H 8200 2350 50  0001 C CNN
	1    8200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 1950 8200 1950
Wire Wire Line
	8200 1950 8200 2050
Connection ~ 8200 1950
Wire Wire Line
	8200 1550 8100 1550
$Comp
L power:GND #PWR029
U 1 1 606E89B0
P 8800 2250
F 0 "#PWR029" H 8800 2000 50  0001 C CNN
F 1 "GND" V 8805 2122 50  0000 R CNN
F 2 "" H 8800 2250 50  0001 C CNN
F 3 "" H 8800 2250 50  0001 C CNN
	1    8800 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR028
U 1 1 606E89B6
P 8800 1250
F 0 "#PWR028" H 8800 1000 50  0001 C CNN
F 1 "GND" V 8805 1122 50  0000 R CNN
F 2 "" H 8800 1250 50  0001 C CNN
F 3 "" H 8800 1250 50  0001 C CNN
	1    8800 1250
	-1   0    0    1   
$EndComp
Wire Wire Line
	8800 1950 9500 1950
Wire Wire Line
	8500 1550 8800 1550
Wire Wire Line
	8800 1550 8800 1600
Connection ~ 8800 1550
Wire Wire Line
	8800 1900 8800 1950
Connection ~ 8800 1950
Wire Wire Line
	8500 1950 8800 1950
Wire Wire Line
	8800 1550 9500 1550
$Comp
L Device:R R13
U 1 1 606E89C4
P 9300 1750
F 0 "R13" H 9370 1796 50  0000 L CNN
F 1 "650" H 9370 1705 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 9230 1750 50  0001 C CNN
F 3 "~" H 9300 1750 50  0001 C CNN
	1    9300 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1600 9500 1600
Wire Wire Line
	9500 1600 9500 1650
Wire Wire Line
	9300 1900 9500 1900
Wire Wire Line
	9500 1900 9500 1850
$Comp
L power:GND #PWR035
U 1 1 606E89CE
P 9800 2050
F 0 "#PWR035" H 9800 1800 50  0001 C CNN
F 1 "GND" V 9805 1922 50  0000 R CNN
F 2 "" H 9800 2050 50  0001 C CNN
F 3 "" H 9800 2050 50  0001 C CNN
	1    9800 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR034
U 1 1 606E89D4
P 9800 1450
F 0 "#PWR034" H 9800 1300 50  0001 C CNN
F 1 "+3.3V" V 9815 1578 50  0000 L CNN
F 2 "" H 9800 1450 50  0001 C CNN
F 3 "" H 9800 1450 50  0001 C CNN
	1    9800 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 606E89DA
P 9950 1450
F 0 "C13" V 10202 1450 50  0000 C CNN
F 1 "0.1uF" V 10111 1450 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D5.1mm_W3.2mm_P5.00mm" H 9988 1300 50  0001 C CNN
F 3 "~" H 9950 1450 50  0001 C CNN
	1    9950 1450
	0    -1   -1   0   
$EndComp
Connection ~ 9800 1450
$Comp
L power:GND #PWR038
U 1 1 606E89E1
P 10100 1450
F 0 "#PWR038" H 10100 1200 50  0001 C CNN
F 1 "GND" V 10105 1322 50  0000 R CNN
F 2 "" H 10100 1450 50  0001 C CNN
F 3 "" H 10100 1450 50  0001 C CNN
	1    10100 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9900 2050 9800 2050
Connection ~ 9800 2050
Text GLabel 10200 1750 2    50   Input ~ 0
SCALE_OUT
Text GLabel 6000 4850 0    50   Input ~ 0
LOAD_CELL-
Text GLabel 1900 4200 0    50   Input ~ 0
SCALE_OUT
$Comp
L power:+5V #PWR016
U 1 1 6072C196
P 5350 6750
F 0 "#PWR016" H 5350 6600 50  0001 C CNN
F 1 "+5V" H 5365 6923 50  0000 C CNN
F 2 "" H 5350 6750 50  0001 C CNN
F 3 "" H 5350 6750 50  0001 C CNN
	1    5350 6750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 6072F3F3
P 5350 6650
F 0 "#PWR017" H 5350 6400 50  0001 C CNN
F 1 "GND" V 5355 6522 50  0000 R CNN
F 2 "" H 5350 6650 50  0001 C CNN
F 3 "" H 5350 6650 50  0001 C CNN
	1    5350 6650
	0    1    1    0   
$EndComp
Text GLabel 5350 6550 0    50   Input ~ 0
BREW_BUTTON
Text GLabel 1900 2900 0    50   Input ~ 0
BREW_READY
NoConn ~ 1900 3300
NoConn ~ 1900 4300
Text GLabel 3700 5850 0    50   Input ~ 0
HEATER_SSR+
Text GLabel 3700 6250 0    50   Input ~ 0
PUMP_SSR+
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 607CC259
P 3900 5850
F 0 "J9" H 3872 5732 50  0000 R CNN
F 1 "Heater_Active" H 3872 5823 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3900 5850 50  0001 C CNN
F 3 "~" H 3900 5850 50  0001 C CNN
	1    3900 5850
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x02_Male J10
U 1 1 607CCADB
P 3900 6250
F 0 "J10" H 3872 6132 50  0000 R CNN
F 1 "Pump_Active" H 3872 6223 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3900 6250 50  0001 C CNN
F 3 "~" H 3900 6250 50  0001 C CNN
	1    3900 6250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR039
U 1 1 607CD906
P 3400 5750
F 0 "#PWR039" H 3400 5500 50  0001 C CNN
F 1 "GND" V 3405 5622 50  0000 R CNN
F 2 "" H 3400 5750 50  0001 C CNN
F 3 "" H 3400 5750 50  0001 C CNN
	1    3400 5750
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 607CD90C
P 3550 5750
F 0 "R2" V 3343 5750 50  0000 C CNN
F 1 "220" V 3434 5750 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3480 5750 50  0001 C CNN
F 3 "~" H 3550 5750 50  0001 C CNN
	1    3550 5750
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR040
U 1 1 607D2168
P 3400 6150
F 0 "#PWR040" H 3400 5900 50  0001 C CNN
F 1 "GND" V 3405 6022 50  0000 R CNN
F 2 "" H 3400 6150 50  0001 C CNN
F 3 "" H 3400 6150 50  0001 C CNN
	1    3400 6150
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 607D216E
P 3550 6150
F 0 "R3" V 3343 6150 50  0000 C CNN
F 1 "220" V 3434 6150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P5.08mm_Horizontal" V 3480 6150 50  0001 C CNN
F 3 "~" H 3550 6150 50  0001 C CNN
	1    3550 6150
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 6087E22B
P 2900 650
F 0 "H3" H 3000 699 50  0000 L CNN
F 1 "MountingHole_Pad" H 3000 608 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm_Pad" H 2900 650 50  0001 C CNN
F 3 "~" H 2900 650 50  0001 C CNN
	1    2900 650 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 6087E231
P 2900 750
F 0 "#PWR0106" H 2900 500 50  0001 C CNN
F 1 "GND" V 2905 622 50  0000 R CNN
F 2 "" H 2900 750 50  0001 C CNN
F 3 "" H 2900 750 50  0001 C CNN
	1    2900 750 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 6087F488
P 3800 650
F 0 "H4" H 3900 699 50  0000 L CNN
F 1 "MountingHole_Pad" H 3900 608 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm_Pad" H 3800 650 50  0001 C CNN
F 3 "~" H 3800 650 50  0001 C CNN
	1    3800 650 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 6087F48E
P 3800 750
F 0 "#PWR0108" H 3800 500 50  0001 C CNN
F 1 "GND" V 3805 622 50  0000 R CNN
F 2 "" H 3800 750 50  0001 C CNN
F 3 "" H 3800 750 50  0001 C CNN
	1    3800 750 
	1    0    0    -1  
$EndComp
Text GLabel 5050 7050 0    50   Input ~ 0
BREW_READY
$Comp
L Connector:Conn_01x04_Male J4
U 1 1 6072E9C5
P 5550 6750
F 0 "J4" H 5522 6632 50  0000 R CNN
F 1 "Brew_Button" H 5522 6723 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5550 6750 50  0001 C CNN
F 3 "~" H 5550 6750 50  0001 C CNN
	1    5550 6750
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR018
U 1 1 6072F88E
P 5350 7250
F 0 "#PWR018" H 5350 7000 50  0001 C CNN
F 1 "GND" V 5355 7122 50  0000 R CNN
F 2 "" H 5350 7250 50  0001 C CNN
F 3 "" H 5350 7250 50  0001 C CNN
	1    5350 7250
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF540N Q1
U 1 1 60728D2B
P 5250 7050
F 0 "Q1" H 5454 7096 50  0000 L CNN
F 1 "IRF540N" H 5454 7005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5500 6975 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf540n.pdf" H 5250 7050 50  0001 L CNN
	1    5250 7050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60BA5595
P 4100 4300
F 0 "#PWR?" H 4100 4150 50  0001 C CNN
F 1 "+5V" V 4115 4428 50  0000 L CNN
F 2 "" H 4100 4300 50  0001 C CNN
F 3 "" H 4100 4300 50  0001 C CNN
	1    4100 4300
	0    1    1    0   
$EndComp
$EndSCHEMATC
