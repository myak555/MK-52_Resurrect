EESchema Schematic File Version 4
LIBS:MK52_Electronics-cache
EELAYER 29 0
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
L Transistor_FET:BS250 Q1
U 1 1 5FE6E4D4
P 3400 1300
F 0 "Q1" H 3606 1254 50  0000 L CNN
F 1 "BS250" H 3606 1345 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 3600 1225 50  0001 L CIN
F 3 "http://www.vishay.com/docs/70209/70209.pdf" H 3400 1300 50  0001 L CNN
	1    3400 1300
	-1   0    0    1   
$EndComp
$Comp
L power:+6V #PWR02
U 1 1 5FE6EF69
P 3300 800
F 0 "#PWR02" H 3300 650 50  0001 C CNN
F 1 "+6V" H 3315 973 50  0000 C CNN
F 2 "" H 3300 800 50  0001 C CNN
F 3 "" H 3300 800 50  0001 C CNN
	1    3300 800 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5FE6F3D2
P 4200 1100
F 0 "R2" H 4270 1146 50  0000 L CNN
F 1 "10K" H 4270 1055 50  0000 L CNN
F 2 "" V 4130 1100 50  0001 C CNN
F 3 "~" H 4200 1100 50  0001 C CNN
	1    4200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1300 4200 1250
Wire Wire Line
	4200 900  4200 950 
Text Notes 1950 3650 0    50   ~ 0
1 - RAW Power\n2 - Power Hold\n3 - KBD reset\n4 - KBD select\n5 - KBD sense\n6 - Power sense\n7 - 3.3V\n8 - GND
$Comp
L Connector:Conn_01x08_Female J1
U 1 1 5FE71275
P 2700 3400
F 0 "J1" H 2592 3885 50  0000 C CNN
F 1 "Processor" H 2600 2900 50  0000 C CNN
F 2 "" H 2700 3400 50  0001 C CNN
F 3 "~" H 2700 3400 50  0001 C CNN
	1    2700 3400
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7000 Q2
U 1 1 5FE73BEA
P 4100 1850
F 0 "Q2" H 4306 1896 50  0000 L CNN
F 1 "2N7000" H 4306 1805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4300 1775 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 4100 1850 50  0001 L CNN
	1    4100 1850
	1    0    0    -1  
$EndComp
Connection ~ 4200 1300
$Comp
L Device:R R1
U 1 1 5FE77DA3
P 3500 2050
F 0 "R1" H 3570 2096 50  0000 L CNN
F 1 "4.7M" H 3570 2005 50  0000 L CNN
F 2 "" V 3430 2050 50  0001 C CNN
F 3 "~" H 3500 2050 50  0001 C CNN
	1    3500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 1300 4200 1650
$Comp
L power:GND #PWR06
U 1 1 5FE831A3
P 5800 4500
F 0 "#PWR06" H 5800 4250 50  0001 C CNN
F 1 "GND" H 5805 4327 50  0000 C CNN
F 2 "" H 5800 4500 50  0001 C CNN
F 3 "" H 5800 4500 50  0001 C CNN
	1    5800 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5FE84282
P 3100 4500
F 0 "#PWR01" H 3100 4250 50  0001 C CNN
F 1 "GND" H 3105 4327 50  0000 C CNN
F 2 "" H 3100 4500 50  0001 C CNN
F 3 "" H 3100 4500 50  0001 C CNN
	1    3100 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5FE84B64
P 4200 2300
F 0 "#PWR04" H 4200 2050 50  0001 C CNN
F 1 "GND" H 4205 2127 50  0000 C CNN
F 2 "" H 4200 2300 50  0001 C CNN
F 3 "" H 4200 2300 50  0001 C CNN
	1    4200 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5FE8927B
P 3500 2300
F 0 "#PWR03" H 3500 2050 50  0001 C CNN
F 1 "GND" H 3505 2127 50  0000 C CNN
F 2 "" H 3500 2300 50  0001 C CNN
F 3 "" H 3500 2300 50  0001 C CNN
	1    3500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2050 4200 2300
$Comp
L Transistor_FET:2N7000 Q3
U 1 1 5FE8A545
P 5150 1850
F 0 "Q3" H 5356 1896 50  0000 L CNN
F 1 "2N7000" H 5356 1805 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5350 1775 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7000.pdf" H 5150 1850 50  0001 L CNN
	1    5150 1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5050 1300 5050 1650
Wire Wire Line
	4200 1300 5050 1300
$Comp
L power:GND #PWR05
U 1 1 5FE8BF6B
P 5050 2300
F 0 "#PWR05" H 5050 2050 50  0001 C CNN
F 1 "GND" H 5055 2127 50  0000 C CNN
F 2 "" H 5050 2300 50  0001 C CNN
F 3 "" H 5050 2300 50  0001 C CNN
	1    5050 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2050 5050 2300
$Comp
L 4xxx:4051 U2
U 1 1 5FE93AD4
P 7400 1600
F 0 "U2" V 8081 1600 50  0000 C CNN
F 1 "4051" V 7990 1600 50  0000 C CNN
F 2 "" H 7400 1600 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 7400 1600 50  0001 C CNN
	1    7400 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5800 1100 6800 1100
Wire Wire Line
	6400 1600 6500 1600
Wire Wire Line
	8300 1500 8350 1500
Wire Wire Line
	8350 1500 8350 1600
Wire Wire Line
	8350 1600 8300 1600
$Comp
L power:GND #PWR09
U 1 1 5FE99EF1
P 8350 2400
F 0 "#PWR09" H 8350 2150 50  0001 C CNN
F 1 "GND" H 8355 2227 50  0000 C CNN
F 2 "" H 8350 2400 50  0001 C CNN
F 3 "" H 8350 2400 50  0001 C CNN
	1    8350 2400
	1    0    0    -1  
$EndComp
Connection ~ 8350 1600
$Comp
L Connector:Conn_01x08_Female J2
U 1 1 5FE9C0B3
P 7200 2500
F 0 "J2" V 7200 1950 50  0000 C CNN
F 1 "KBD Columns" V 7300 2450 50  0000 C CNN
F 2 "" H 7200 2500 50  0001 C CNN
F 3 "~" H 7200 2500 50  0001 C CNN
	1    7200 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 2100 6800 2300
Wire Wire Line
	6900 2100 6900 2300
Wire Wire Line
	7000 2100 7000 2300
Wire Wire Line
	7100 2100 7100 2300
Wire Wire Line
	7200 2100 7200 2300
Wire Wire Line
	7300 2100 7300 2300
Wire Wire Line
	7400 2100 7400 2300
Wire Wire Line
	7500 2100 7500 2300
$Comp
L 4xxx:4051 U3
U 1 1 5FEA5062
P 9550 1600
F 0 "U3" V 10231 1600 50  0000 C CNN
F 1 "4051" V 10140 1600 50  0000 C CNN
F 2 "" H 9550 1600 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 9550 1600 50  0001 C CNN
	1    9550 1600
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 5FEA6426
P 9150 2500
F 0 "J3" V 9150 2150 50  0000 L CNN
F 1 "KBD Rows" V 9050 2250 50  0000 L CNN
F 2 "" H 9150 2500 50  0001 C CNN
F 3 "~" H 9150 2500 50  0001 C CNN
	1    9150 2500
	0    1    -1   0   
$EndComp
Wire Wire Line
	8950 2100 8950 2300
Wire Wire Line
	9050 2100 9050 2300
Wire Wire Line
	9150 2100 9150 2300
Wire Wire Line
	9250 2100 9250 2300
NoConn ~ 9350 2100
NoConn ~ 9450 2100
NoConn ~ 9550 2100
NoConn ~ 9650 2100
Wire Wire Line
	7700 2100 7700 2200
Wire Wire Line
	7700 2200 8350 2200
Wire Wire Line
	8350 1600 8350 2200
Wire Wire Line
	8350 2200 8350 2400
Connection ~ 8350 2200
$Comp
L power:GND #PWR012
U 1 1 5FEB48B8
P 10500 2350
F 0 "#PWR012" H 10500 2100 50  0001 C CNN
F 1 "GND" H 10505 2177 50  0000 C CNN
F 2 "" H 10500 2350 50  0001 C CNN
F 3 "" H 10500 2350 50  0001 C CNN
	1    10500 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 2100 9850 2200
Wire Wire Line
	9850 2200 10150 2200
Wire Wire Line
	10500 2200 10500 2350
Wire Wire Line
	10450 1500 10500 1500
Wire Wire Line
	10500 1500 10500 1600
Connection ~ 10500 2200
Wire Wire Line
	10450 1600 10500 1600
Connection ~ 10500 1600
Wire Wire Line
	10500 1600 10500 2200
$Comp
L Device:R R5
U 1 1 5FEB8590
P 8750 1050
F 0 "R5" V 8957 1050 50  0000 C CNN
F 1 "5K*" V 8866 1050 50  0000 C CNN
F 2 "" V 8680 1050 50  0001 C CNN
F 3 "~" H 8750 1050 50  0001 C CNN
	1    8750 1050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8900 1050 8950 1050
Wire Wire Line
	8950 1050 8950 1100
Wire Wire Line
	8500 800  8500 1050
Wire Wire Line
	8500 1600 8650 1600
Wire Wire Line
	8500 1050 8600 1050
Connection ~ 8500 1050
Wire Wire Line
	8500 1050 8500 1600
$Comp
L 4xxx:4040 U1
U 1 1 5FEBEDDC
P 6400 3500
F 0 "U1" H 6600 4350 50  0000 C CNN
F 1 "4040" H 6650 4250 50  0000 C CNN
F 2 "" H 6400 3500 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4020bms-24bms-40bms.pdf" H 6400 3500 50  0001 C CNN
	1    6400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1600 6400 2600
Connection ~ 6400 1600
Wire Wire Line
	6900 3000 9950 3000
Wire Wire Line
	9950 3000 9950 2100
Wire Wire Line
	6900 3100 10050 3100
Wire Wire Line
	10050 3100 10050 2100
Wire Wire Line
	6900 3200 7800 3200
Wire Wire Line
	7800 3200 7800 2100
Wire Wire Line
	6900 3300 7900 3300
Wire Wire Line
	7900 3300 7900 2100
Wire Wire Line
	6900 3400 8000 3400
Wire Wire Line
	8000 3400 8000 2100
$Comp
L Device:LED_ALT D1
U 1 1 5FED2B96
P 8350 3500
F 0 "D1" H 8343 3716 50  0000 C CNN
F 1 "Function" H 8343 3625 50  0000 C CNN
F 2 "" H 8350 3500 50  0001 C CNN
F 3 "~" H 8350 3500 50  0001 C CNN
	1    8350 3500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6900 3500 8200 3500
$Comp
L power:GND #PWR011
U 1 1 5FED7B8B
P 8650 4500
F 0 "#PWR011" H 8650 4250 50  0001 C CNN
F 1 "GND" H 8655 4327 50  0000 C CNN
F 2 "" H 8650 4500 50  0001 C CNN
F 3 "" H 8650 4500 50  0001 C CNN
	1    8650 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3500 8650 3500
Wire Wire Line
	8650 3500 8650 3650
$Comp
L power:GND #PWR08
U 1 1 5FEDA29F
P 6400 4500
F 0 "#PWR08" H 6400 4250 50  0001 C CNN
F 1 "GND" H 6405 4327 50  0000 C CNN
F 2 "" H 6400 4500 50  0001 C CNN
F 3 "" H 6400 4500 50  0001 C CNN
	1    6400 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 4400 6400 4500
$Comp
L Device:R R4
U 1 1 5FEDD07D
P 8650 3800
F 0 "R4" H 8720 3846 50  0000 L CNN
F 1 "1.0K*" H 8720 3755 50  0000 L CNN
F 2 "" V 8580 3800 50  0001 C CNN
F 3 "~" H 8650 3800 50  0001 C CNN
	1    8650 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3950 8650 4500
NoConn ~ 6900 3600
NoConn ~ 6900 3700
NoConn ~ 6900 3800
NoConn ~ 6900 3900
NoConn ~ 6900 4000
NoConn ~ 6900 4100
$Comp
L Device:R R3
U 1 1 5FE823E4
P 5800 4000
F 0 "R3" H 5870 4046 50  0000 L CNN
F 1 "10K" H 5870 3955 50  0000 L CNN
F 2 "" V 5730 4000 50  0001 C CNN
F 3 "~" H 5800 4000 50  0001 C CNN
	1    5800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3000 5900 3000
Wire Wire Line
	5800 4150 5800 4300
Wire Wire Line
	2900 3300 5200 3300
Wire Wire Line
	2900 3100 3300 3100
Wire Wire Line
	2900 3200 3250 3200
Wire Wire Line
	2900 3400 5500 3400
Wire Wire Line
	5700 3000 5700 3400
Wire Wire Line
	2900 3800 3100 3800
Wire Wire Line
	3100 3800 3100 4500
$Comp
L Device:R R7
U 1 1 5FF13CCB
P 5500 4000
F 0 "R7" H 5570 4046 50  0000 L CNN
F 1 "10K" H 5570 3955 50  0000 L CNN
F 2 "" V 5430 4000 50  0001 C CNN
F 3 "~" H 5500 4000 50  0001 C CNN
	1    5500 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5FF14173
P 5200 4000
F 0 "R6" H 5270 4046 50  0000 L CNN
F 1 "10K" H 5270 3955 50  0000 L CNN
F 2 "" V 5130 4000 50  0001 C CNN
F 3 "~" H 5200 4000 50  0001 C CNN
	1    5200 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3400 5500 3850
Connection ~ 5500 3400
Wire Wire Line
	5500 3400 5700 3400
Wire Wire Line
	5200 3300 5200 3850
Connection ~ 5200 3300
Wire Wire Line
	5200 3300 5900 3300
Wire Wire Line
	5200 4150 5200 4300
Wire Wire Line
	5200 4300 5500 4300
Connection ~ 5800 4300
Wire Wire Line
	5800 4300 5800 4500
Wire Wire Line
	5500 4150 5500 4300
Connection ~ 5500 4300
Wire Wire Line
	5500 4300 5800 4300
Wire Wire Line
	5800 3500 5800 3850
Wire Wire Line
	10150 2100 10150 2200
Connection ~ 10150 2200
Wire Wire Line
	10150 2200 10500 2200
Text Notes 1950 4550 0    50   ~ 0
1 - +3.3V\n2 - KBD CLK\n3 - KBD reset\n4 - KBD sense\n5 - GND
$Comp
L Device:R R8
U 1 1 5FF2744E
P 4900 3050
F 0 "R8" H 4970 3096 50  0000 L CNN
F 1 "10K*" H 4970 3005 50  0000 L CNN
F 2 "" V 4830 3050 50  0001 C CNN
F 3 "~" H 4900 3050 50  0001 C CNN
	1    4900 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 1100 5800 3500
Connection ~ 5800 3500
$Comp
L Device:R R9
U 1 1 5FF2AF6F
P 4900 4000
F 0 "R9" H 4970 4046 50  0000 L CNN
F 1 "10K" H 4970 3955 50  0000 L CNN
F 2 "" V 4830 4000 50  0001 C CNN
F 3 "~" H 4900 4000 50  0001 C CNN
	1    4900 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:D D2
U 1 1 5FF1DECD
P 3900 3600
F 0 "D2" H 3700 3500 50  0000 C CNN
F 1 "D" H 4050 3500 50  0000 C CNN
F 2 "" H 3900 3600 50  0001 C CNN
F 3 "~" H 3900 3600 50  0001 C CNN
	1    3900 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3500 5800 3500
Wire Wire Line
	2900 3600 3750 3600
$Comp
L Switch:SW_Push SW1
U 1 1 5FF3F0D4
P 5050 900
F 0 "SW1" H 5050 1185 50  0000 C CNN
F 1 "POWER" H 5050 1094 50  0000 C CNN
F 2 "" H 5050 1100 50  0001 C CNN
F 3 "~" H 5050 1100 50  0001 C CNN
	1    5050 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4150 4900 4300
Wire Wire Line
	4900 4300 5200 4300
Connection ~ 5200 4300
Wire Wire Line
	4900 3200 4900 3600
Wire Wire Line
	4900 2900 4900 2750
Connection ~ 4900 3600
Wire Wire Line
	4900 3600 4900 3850
Wire Wire Line
	4050 3600 4900 3600
Wire Wire Line
	4200 900  4850 900 
Connection ~ 4200 900 
Wire Wire Line
	6400 800  6400 1600
Wire Wire Line
	2900 3700 3200 3700
Wire Wire Line
	6400 2600 3200 2600
Connection ~ 6400 2600
Wire Wire Line
	6400 2600 6400 2700
Wire Wire Line
	3250 1850 3250 3200
Wire Wire Line
	3200 2600 3200 3700
Wire Wire Line
	6400 800  8500 800 
$Comp
L Device:R R11
U 1 1 6003BE54
P 3850 1300
F 0 "R11" V 3950 1300 50  0000 L CNN
F 1 "430R" V 3750 1200 50  0000 L CNN
F 2 "" V 3780 1300 50  0001 C CNN
F 3 "~" H 3850 1300 50  0001 C CNN
	1    3850 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 1300 3700 1300
Wire Wire Line
	4000 1300 4200 1300
Wire Wire Line
	3300 1100 3300 900 
Wire Wire Line
	3300 800  3300 900 
Connection ~ 3300 900 
Wire Wire Line
	3300 900  4200 900 
Wire Wire Line
	3300 1500 3300 3100
Wire Wire Line
	3500 2200 3500 2300
$Comp
L Device:R R10
U 1 1 60058690
P 3750 1850
F 0 "R10" V 3850 1850 50  0000 L CNN
F 1 "430R" V 3650 1750 50  0000 L CNN
F 2 "" V 3680 1850 50  0001 C CNN
F 3 "~" H 3750 1850 50  0001 C CNN
	1    3750 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	3250 1850 3500 1850
Wire Wire Line
	3500 1900 3500 1850
Connection ~ 3500 1850
Wire Wire Line
	3500 1850 3600 1850
$Comp
L Device:R R12
U 1 1 60060935
P 5500 1850
F 0 "R12" V 5600 1850 50  0000 L CNN
F 1 "430R" V 5400 1750 50  0000 L CNN
F 2 "" V 5430 1850 50  0001 C CNN
F 3 "~" H 5500 1850 50  0001 C CNN
	1    5500 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 900  5700 1850
Wire Wire Line
	5700 1850 5650 1850
Wire Wire Line
	5250 900  5700 900 
Wire Wire Line
	5700 1850 5700 2750
Wire Wire Line
	4900 2750 5700 2750
Connection ~ 5700 1850
$EndSCHEMATC
