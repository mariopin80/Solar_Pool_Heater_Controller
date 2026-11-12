EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Controlador de Piscina MPS01"
Date "2021-05-21"
Rev "1.0"
Comp "Mario Pin"
Comment1 "Desenvolvido no Brasil"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L atmega:ATMEGA328PU U1
U 1 1 60A76D21
P 1100 1300
F 0 "U1" H 2050 -1600 50  0000 R CNN
F 1 "ATMEGA328PU" H 1350 1400 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm_LongPads" H 1100 1300 50  0001 C CNN
F 3 "" H 1100 1300 50  0001 C CNN
	1    1100 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 60A78419
P 1600 1050
F 0 "#PWR0101" H 1600 900 50  0001 C CNN
F 1 "+5V" H 1615 1223 50  0000 C CNN
F 2 "" H 1600 1050 50  0001 C CNN
F 3 "" H 1600 1050 50  0001 C CNN
	1    1600 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1050 1600 1100
Wire Wire Line
	1700 1200 1700 1100
Wire Wire Line
	1700 1100 1600 1100
Connection ~ 1600 1100
Wire Wire Line
	1600 1100 1600 1200
Wire Wire Line
	1450 4200 1450 4300
Wire Wire Line
	1600 4200 1600 4300
Wire Wire Line
	1600 4300 1450 4300
Connection ~ 1450 4300
Wire Wire Line
	1450 4300 1450 4400
$Comp
L Device:Crystal Y1
U 1 1 60A7A001
P 2900 1750
F 0 "Y1" V 2854 1881 50  0000 L CNN
F 1 "16MHz" V 2945 1881 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-4H_Vertical" H 2900 1750 50  0001 C CNN
F 3 "~" H 2900 1750 50  0001 C CNN
	1    2900 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 1900 2900 2000
Wire Wire Line
	2900 2000 3100 2000
Wire Wire Line
	2900 1600 2900 1500
Wire Wire Line
	2900 1500 3100 1500
$Comp
L power:GNDREF #PWR0102
U 1 1 60A7F9E1
P 3500 2050
F 0 "#PWR0102" H 3500 1800 50  0001 C CNN
F 1 "GNDREF" H 3505 1877 50  0001 C CNN
F 2 "" H 3500 2050 50  0001 C CNN
F 3 "" H 3500 2050 50  0001 C CNN
	1    3500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1500 3500 1500
Wire Wire Line
	3500 1500 3500 2000
Wire Wire Line
	3400 2000 3500 2000
Connection ~ 3500 2000
Wire Wire Line
	3500 2000 3500 2050
$Comp
L power:GNDREF #PWR0103
U 1 1 60A802E7
P 1450 4400
F 0 "#PWR0103" H 1450 4150 50  0001 C CNN
F 1 "GNDREF" H 1455 4227 50  0001 C CNN
F 2 "" H 1450 4400 50  0001 C CNN
F 3 "" H 1450 4400 50  0001 C CNN
	1    1450 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60A88DBC
P 2950 3000
F 0 "R1" V 2743 3000 50  0000 C CNN
F 1 "10k" V 2834 3000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2880 3000 50  0001 C CNN
F 3 "~" H 2950 3000 50  0001 C CNN
	1    2950 3000
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 60A89D22
P 3150 2950
F 0 "#PWR0104" H 3150 2800 50  0001 C CNN
F 1 "+5V" H 3165 3123 50  0000 C CNN
F 2 "" H 3150 2950 50  0001 C CNN
F 3 "" H 3150 2950 50  0001 C CNN
	1    3150 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 3000 3150 3000
Wire Wire Line
	3150 3000 3150 2950
Text GLabel 2850 3150 2    50   Input ~ 0
RTS
Wire Wire Line
	2850 3150 2750 3150
Wire Wire Line
	2750 3150 2750 3000
Connection ~ 2750 3000
Wire Wire Line
	2750 3000 2800 3000
Wire Wire Line
	2200 3000 2750 3000
Text GLabel 2300 3200 2    50   Input ~ 0
RX
Text GLabel 2300 3300 2    50   Output ~ 0
TX
Wire Wire Line
	2300 3200 2200 3200
Wire Wire Line
	2300 3300 2200 3300
Text GLabel 2300 3400 2    50   Input ~ 0
PB3
Text GLabel 2300 3500 2    50   Input ~ 0
PB2
Text GLabel 2300 3600 2    50   Input ~ 0
PB1
Wire Wire Line
	2300 3400 2200 3400
Wire Wire Line
	2300 3500 2200 3500
Wire Wire Line
	2300 3600 2200 3600
Text GLabel 2300 3700 2    50   Output ~ 0
RLY_FL
Text GLabel 2300 3800 2    50   Output ~ 0
RLY_AQ
Wire Wire Line
	2300 3700 2200 3700
Wire Wire Line
	2200 3800 2300 3800
Text GLabel 2350 1500 2    50   Output ~ 0
RS
Text GLabel 2350 1600 2    50   Output ~ 0
EN
Text GLabel 2350 1700 2    50   Output ~ 0
D7
Text GLabel 2350 1800 2    50   Output ~ 0
D6
Text GLabel 2350 1900 2    50   Output ~ 0
D5
Text GLabel 2350 2000 2    50   Output ~ 0
D4
Wire Wire Line
	2350 1500 2200 1500
Wire Wire Line
	2350 1600 2200 1600
Wire Wire Line
	2350 1700 2200 1700
Wire Wire Line
	2350 1800 2200 1800
Wire Wire Line
	2350 1900 2200 1900
Wire Wire Line
	2350 2000 2200 2000
Wire Wire Line
	2200 2100 2600 2100
Wire Wire Line
	2600 2100 2600 1500
Wire Wire Line
	2600 1500 2900 1500
Connection ~ 2900 1500
Wire Wire Line
	2200 2200 2750 2200
Wire Wire Line
	2750 2200 2750 2000
Wire Wire Line
	2750 2000 2900 2000
Connection ~ 2900 2000
Text GLabel 2350 2800 2    50   Output ~ 0
SCL
Text GLabel 2350 2900 2    50   BiDi ~ 0
SDA
Text GLabel 2350 2400 2    50   Input ~ 0
CLT_TMP
Text GLabel 2350 2500 2    50   Input ~ 0
PSC_TMP
Wire Wire Line
	2350 2400 2200 2400
Wire Wire Line
	2350 2500 2200 2500
Wire Wire Line
	2350 2800 2200 2800
Wire Wire Line
	2350 2900 2200 2900
$Comp
L Switch:SW_Push SW1
U 1 1 60A9E5DB
P 4850 1200
F 0 "SW1" H 4850 1485 50  0000 C CNN
F 1 "ENT" H 4850 1394 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4850 1400 50  0001 C CNN
F 3 "~" H 4850 1400 50  0001 C CNN
	1    4850 1200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR010
U 1 1 60A9EF53
P 5150 1250
F 0 "#PWR010" H 5150 1000 50  0001 C CNN
F 1 "GNDREF" H 5155 1077 50  0001 C CNN
F 2 "" H 5150 1250 50  0001 C CNN
F 3 "" H 5150 1250 50  0001 C CNN
	1    5150 1250
	1    0    0    -1  
$EndComp
Text GLabel 4550 1200 0    50   Output ~ 0
PB1
Wire Wire Line
	4650 1200 4550 1200
Wire Wire Line
	5050 1200 5150 1200
Wire Wire Line
	5150 1200 5150 1250
$Comp
L Switch:SW_Push SW2
U 1 1 60AA2C76
P 4850 2350
F 0 "SW2" H 4850 2635 50  0000 C CNN
F 1 "NXT" H 4850 2544 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4850 2550 50  0001 C CNN
F 3 "~" H 4850 2550 50  0001 C CNN
	1    4850 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR014
U 1 1 60AA2C7C
P 5150 2400
F 0 "#PWR014" H 5150 2150 50  0001 C CNN
F 1 "GNDREF" H 5155 2227 50  0001 C CNN
F 2 "" H 5150 2400 50  0001 C CNN
F 3 "" H 5150 2400 50  0001 C CNN
	1    5150 2400
	1    0    0    -1  
$EndComp
Text GLabel 4550 2350 0    50   Output ~ 0
PB2
Wire Wire Line
	4650 2350 4550 2350
Wire Wire Line
	5050 2350 5150 2350
Wire Wire Line
	5150 2350 5150 2400
$Comp
L Switch:SW_Push SW3
U 1 1 60AA43C2
P 4850 3600
F 0 "SW3" H 4850 3885 50  0000 C CNN
F 1 "ESC" H 4850 3794 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 4850 3800 50  0001 C CNN
F 3 "~" H 4850 3800 50  0001 C CNN
	1    4850 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR017
U 1 1 60AA43C8
P 5150 3650
F 0 "#PWR017" H 5150 3400 50  0001 C CNN
F 1 "GNDREF" H 5155 3477 50  0001 C CNN
F 2 "" H 5150 3650 50  0001 C CNN
F 3 "" H 5150 3650 50  0001 C CNN
	1    5150 3650
	1    0    0    -1  
$EndComp
Text GLabel 4550 3600 0    50   Output ~ 0
PB3
Wire Wire Line
	4650 3600 4550 3600
Wire Wire Line
	5050 3600 5150 3600
Wire Wire Line
	5150 3600 5150 3650
$Comp
L Relay:FINDER-36.11 K1
U 1 1 60AA5F7F
P 9800 1700
F 0 "K1" H 10230 1746 50  0000 L CNN
F 1 "AQUECEDOR" H 9450 1300 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Finder_36.11" H 11070 1670 50  0001 C CNN
F 3 "https://gfinder.findernet.com/public/attachments/36/EN/S36EN.pdf" H 9800 1700 50  0001 C CNN
	1    9800 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:D D5
U 1 1 60AA6FA2
P 8900 1700
F 0 "D5" V 8854 1780 50  0000 L CNN
F 1 "1N4148" V 8945 1780 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 8900 1700 50  0001 C CNN
F 3 "~" H 8900 1700 50  0001 C CNN
	1    8900 1700
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N3904 Q1
U 1 1 60AA8565
P 8800 2350
F 0 "Q1" H 8990 2396 50  0000 L CNN
F 1 "2N3904" H 8990 2305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9000 2275 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 8800 2350 50  0001 L CNN
	1    8800 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR07
U 1 1 60AA9A28
P 8900 2650
F 0 "#PWR07" H 8900 2400 50  0001 C CNN
F 1 "GNDREF" H 8905 2477 50  0001 C CNN
F 2 "" H 8900 2650 50  0001 C CNN
F 3 "" H 8900 2650 50  0001 C CNN
	1    8900 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 60AAA182
P 8900 1250
F 0 "#PWR06" H 8900 1100 50  0001 C CNN
F 1 "+5V" H 8915 1423 50  0000 C CNN
F 2 "" H 8900 1250 50  0001 C CNN
F 3 "" H 8900 1250 50  0001 C CNN
	1    8900 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 60AAA9B3
P 8600 1500
F 0 "R6" H 8670 1546 50  0000 L CNN
F 1 "330" H 8670 1455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8530 1500 50  0001 C CNN
F 3 "~" H 8600 1500 50  0001 C CNN
	1    8600 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D7
U 1 1 60AAB1A0
P 8600 1850
F 0 "D7" V 8639 1732 50  0000 R CNN
F 1 "LED" V 8548 1732 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8600 1850 50  0001 C CNN
F 3 "~" H 8600 1850 50  0001 C CNN
	1    8600 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8900 1250 8900 1300
Wire Wire Line
	8600 1350 8600 1300
Wire Wire Line
	8600 1300 8900 1300
Connection ~ 8900 1300
Wire Wire Line
	8900 1300 8900 1550
Wire Wire Line
	9600 1300 9600 1400
Wire Wire Line
	8600 1650 8600 1700
Wire Wire Line
	8900 2150 8900 2050
Wire Wire Line
	8600 2000 8600 2050
Wire Wire Line
	8600 2050 8900 2050
Connection ~ 8900 2050
Wire Wire Line
	8900 2050 8900 1850
Wire Wire Line
	9600 2000 9600 2050
Wire Wire Line
	8900 2650 8900 2550
Wire Wire Line
	8900 1300 9600 1300
Wire Wire Line
	8900 2050 9600 2050
$Comp
L Device:R R4
U 1 1 60ABA795
P 8350 2350
F 0 "R4" V 8143 2350 50  0000 C CNN
F 1 "10k" V 8234 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8280 2350 50  0001 C CNN
F 3 "~" H 8350 2350 50  0001 C CNN
	1    8350 2350
	0    1    1    0   
$EndComp
Text GLabel 8100 2350 0    50   Input ~ 0
RLY_AQ
Wire Wire Line
	8100 2350 8200 2350
Wire Wire Line
	8500 2350 8600 2350
$Comp
L Relay:FINDER-36.11 K2
U 1 1 60AC67EF
P 9800 3600
F 0 "K2" H 10230 3646 50  0000 L CNN
F 1 "FILTRO" H 9650 3200 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Finder_36.11" H 11070 3570 50  0001 C CNN
F 3 "https://gfinder.findernet.com/public/attachments/36/EN/S36EN.pdf" H 9800 3600 50  0001 C CNN
	1    9800 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:D D6
U 1 1 60AC67F5
P 8900 3600
F 0 "D6" V 8854 3680 50  0000 L CNN
F 1 "1N4148" V 8945 3680 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 8900 3600 50  0001 C CNN
F 3 "~" H 8900 3600 50  0001 C CNN
	1    8900 3600
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N3904 Q2
U 1 1 60AC67FB
P 8800 4250
F 0 "Q2" H 8990 4296 50  0000 L CNN
F 1 "2N3904" H 8990 4205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9000 4175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 8800 4250 50  0001 L CNN
	1    8800 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR016
U 1 1 60AC6801
P 8900 4550
F 0 "#PWR016" H 8900 4300 50  0001 C CNN
F 1 "GNDREF" H 8905 4377 50  0001 C CNN
F 2 "" H 8900 4550 50  0001 C CNN
F 3 "" H 8900 4550 50  0001 C CNN
	1    8900 4550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 60AC6807
P 8900 3150
F 0 "#PWR015" H 8900 3000 50  0001 C CNN
F 1 "+5V" H 8915 3323 50  0000 C CNN
F 2 "" H 8900 3150 50  0001 C CNN
F 3 "" H 8900 3150 50  0001 C CNN
	1    8900 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 60AC680D
P 8600 3400
F 0 "R7" H 8670 3446 50  0000 L CNN
F 1 "330" H 8670 3355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8530 3400 50  0001 C CNN
F 3 "~" H 8600 3400 50  0001 C CNN
	1    8600 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D8
U 1 1 60AC6813
P 8600 3750
F 0 "D8" V 8639 3632 50  0000 R CNN
F 1 "LED" V 8548 3632 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8600 3750 50  0001 C CNN
F 3 "~" H 8600 3750 50  0001 C CNN
	1    8600 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8900 3150 8900 3200
Wire Wire Line
	8600 3250 8600 3200
Wire Wire Line
	8600 3200 8900 3200
Connection ~ 8900 3200
Wire Wire Line
	8900 3200 8900 3450
Wire Wire Line
	9600 3200 9600 3300
Wire Wire Line
	8600 3550 8600 3600
Wire Wire Line
	8900 4050 8900 3950
Wire Wire Line
	8600 3900 8600 3950
Wire Wire Line
	8600 3950 8900 3950
Connection ~ 8900 3950
Wire Wire Line
	8900 3950 8900 3750
Wire Wire Line
	9600 3900 9600 3950
Wire Wire Line
	8900 4550 8900 4450
Wire Wire Line
	8900 3200 9600 3200
Wire Wire Line
	8900 3950 9600 3950
$Comp
L Device:R R5
U 1 1 60AC6829
P 8350 4250
F 0 "R5" V 8143 4250 50  0000 C CNN
F 1 "10k" V 8234 4250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 8280 4250 50  0001 C CNN
F 3 "~" H 8350 4250 50  0001 C CNN
	1    8350 4250
	0    1    1    0   
$EndComp
Text GLabel 8100 4250 0    50   Input ~ 0
RLY_FL
Wire Wire Line
	8100 4250 8200 4250
Wire Wire Line
	8500 4250 8600 4250
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 60ACFE21
P 10650 1100
F 0 "J5" H 10730 1092 50  0000 L CNN
F 1 "AQC" H 10730 1001 50  0000 L CNN
F 2 "Connector_Phoenix_MSTB:PhoenixContact_MSTBA_2,5_2-G-5,08_1x02_P5.08mm_Horizontal" H 10650 1100 50  0001 C CNN
F 3 "~" H 10650 1100 50  0001 C CNN
	1    10650 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 2000 10000 2050
Wire Wire Line
	10000 2050 10350 2050
Wire Wire Line
	10350 2050 10350 1200
Wire Wire Line
	10350 1200 10450 1200
Wire Wire Line
	10100 1400 10100 1100
Wire Wire Line
	10100 1100 10450 1100
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 60AD7F61
P 10650 3050
F 0 "J6" H 10730 3042 50  0000 L CNN
F 1 "FLT" H 10730 2951 50  0000 L CNN
F 2 "Connector_Phoenix_MSTB:PhoenixContact_MSTBA_2,5_2-G-5,08_1x02_P5.08mm_Horizontal" H 10650 3050 50  0001 C CNN
F 3 "~" H 10650 3050 50  0001 C CNN
	1    10650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 3950 10350 3950
Wire Wire Line
	10350 3950 10350 3150
Wire Wire Line
	10350 3150 10450 3150
Wire Wire Line
	10100 3050 10450 3050
Wire Wire Line
	10000 3950 10000 3900
Wire Wire Line
	10100 3050 10100 3300
$Comp
L Device:R R2
U 1 1 60AEA833
P 6300 1250
F 0 "R2" H 6370 1296 50  0000 L CNN
F 1 "10k" H 6370 1205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6230 1250 50  0001 C CNN
F 3 "~" H 6300 1250 50  0001 C CNN
	1    6300 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J3
U 1 1 60AEB044
P 7100 1500
F 0 "J3" H 7180 1492 50  0000 L CNN
F 1 "CLT" H 7180 1401 50  0000 L CNN
F 2 "Connector_Phoenix_MSTB:PhoenixContact_MSTBA_2,5_2-G-5,08_1x02_P5.08mm_Horizontal" H 7100 1500 50  0001 C CNN
F 3 "~" H 7100 1500 50  0001 C CNN
	1    7100 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 60AEBE97
P 6600 1850
F 0 "D2" V 6554 1930 50  0000 L CNN
F 1 "1N4735" V 6645 1930 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6600 1850 50  0001 C CNN
F 3 "~" H 6600 1850 50  0001 C CNN
	1    6600 1850
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D1
U 1 1 60AED0EA
P 6600 1250
F 0 "D1" V 6554 1330 50  0000 L CNN
F 1 "1N4735" V 6645 1330 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6600 1250 50  0001 C CNN
F 3 "~" H 6600 1250 50  0001 C CNN
	1    6600 1250
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR012
U 1 1 60AF34ED
P 6600 2150
F 0 "#PWR012" H 6600 1900 50  0001 C CNN
F 1 "GNDREF" H 6605 1977 50  0001 C CNN
F 2 "" H 6600 2150 50  0001 C CNN
F 3 "" H 6600 2150 50  0001 C CNN
	1    6600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 1400 6300 1500
Wire Wire Line
	6300 1500 6600 1500
Wire Wire Line
	6600 1400 6600 1500
Connection ~ 6600 1500
Wire Wire Line
	6600 1500 6900 1500
Wire Wire Line
	6600 1700 6600 1500
Wire Wire Line
	6600 2150 6600 2000
$Comp
L power:GNDREF #PWR013
U 1 1 60B01608
P 6850 1650
F 0 "#PWR013" H 6850 1400 50  0001 C CNN
F 1 "GNDREF" H 7050 1550 50  0001 C CNN
F 2 "" H 6850 1650 50  0001 C CNN
F 3 "" H 6850 1650 50  0001 C CNN
	1    6850 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1600 6850 1600
Wire Wire Line
	6850 1600 6850 1650
$Comp
L power:+5V #PWR011
U 1 1 60B04BA4
P 6600 1000
F 0 "#PWR011" H 6600 850 50  0001 C CNN
F 1 "+5V" H 6615 1173 50  0000 C CNN
F 2 "" H 6600 1000 50  0001 C CNN
F 3 "" H 6600 1000 50  0001 C CNN
	1    6600 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1000 6600 1050
Wire Wire Line
	6300 1100 6300 1050
Wire Wire Line
	6300 1050 6600 1050
Connection ~ 6600 1050
Wire Wire Line
	6600 1050 6600 1100
Text GLabel 6150 1500 0    50   Output ~ 0
CLT_TMP
Wire Wire Line
	6150 1500 6300 1500
Connection ~ 6300 1500
$Comp
L Device:R R3
U 1 1 60B11F29
P 6250 3400
F 0 "R3" H 6320 3446 50  0000 L CNN
F 1 "10k" H 6320 3355 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6180 3400 50  0001 C CNN
F 3 "~" H 6250 3400 50  0001 C CNN
	1    6250 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J4
U 1 1 60B11F2F
P 7050 3650
F 0 "J4" H 7130 3642 50  0000 L CNN
F 1 "PSC" H 7130 3551 50  0000 L CNN
F 2 "Connector_Phoenix_MSTB:PhoenixContact_MSTBA_2,5_2-G-5,08_1x02_P5.08mm_Horizontal" H 7050 3650 50  0001 C CNN
F 3 "~" H 7050 3650 50  0001 C CNN
	1    7050 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D4
U 1 1 60B11F35
P 6550 4000
F 0 "D4" V 6504 4080 50  0000 L CNN
F 1 "1N4735" V 6595 4080 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6550 4000 50  0001 C CNN
F 3 "~" H 6550 4000 50  0001 C CNN
	1    6550 4000
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D3
U 1 1 60B11F3B
P 6550 3400
F 0 "D3" V 6504 3480 50  0000 L CNN
F 1 "1N4735" V 6595 3480 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6550 3400 50  0001 C CNN
F 3 "~" H 6550 3400 50  0001 C CNN
	1    6550 3400
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR019
U 1 1 60B11F41
P 6550 4300
F 0 "#PWR019" H 6550 4050 50  0001 C CNN
F 1 "GNDREF" H 6555 4127 50  0001 C CNN
F 2 "" H 6550 4300 50  0001 C CNN
F 3 "" H 6550 4300 50  0001 C CNN
	1    6550 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3550 6250 3650
Wire Wire Line
	6250 3650 6550 3650
Wire Wire Line
	6550 3550 6550 3650
Connection ~ 6550 3650
Wire Wire Line
	6550 3650 6850 3650
Wire Wire Line
	6550 3850 6550 3650
Wire Wire Line
	6550 4300 6550 4150
$Comp
L power:GNDREF #PWR020
U 1 1 60B11F4E
P 6800 3800
F 0 "#PWR020" H 6800 3550 50  0001 C CNN
F 1 "GNDREF" H 7000 3700 50  0001 C CNN
F 2 "" H 6800 3800 50  0001 C CNN
F 3 "" H 6800 3800 50  0001 C CNN
	1    6800 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 3750 6800 3750
Wire Wire Line
	6800 3750 6800 3800
$Comp
L power:+5V #PWR018
U 1 1 60B11F56
P 6550 3150
F 0 "#PWR018" H 6550 3000 50  0001 C CNN
F 1 "+5V" H 6565 3323 50  0000 C CNN
F 2 "" H 6550 3150 50  0001 C CNN
F 3 "" H 6550 3150 50  0001 C CNN
	1    6550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3150 6550 3200
Wire Wire Line
	6250 3250 6250 3200
Wire Wire Line
	6250 3200 6550 3200
Connection ~ 6550 3200
Wire Wire Line
	6550 3200 6550 3250
Text GLabel 6100 3650 0    50   Output ~ 0
PSC_TMP
Wire Wire Line
	6100 3650 6250 3650
Connection ~ 6250 3650
$Comp
L Connector:Conn_01x06_Female J2
U 1 1 60B2656A
P 9800 5650
F 0 "J2" H 9828 5626 50  0000 L CNN
F 1 "FTDI" H 9828 5535 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 9800 5650 50  0001 C CNN
F 3 "~" H 9800 5650 50  0001 C CNN
	1    9800 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR09
U 1 1 60B278B9
P 9500 6050
F 0 "#PWR09" H 9500 5800 50  0001 C CNN
F 1 "GNDREF" H 9505 5877 50  0001 C CNN
F 2 "" H 9500 6050 50  0001 C CNN
F 3 "" H 9500 6050 50  0001 C CNN
	1    9500 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5850 9500 5850
Wire Wire Line
	9500 5850 9500 5950
Wire Wire Line
	9600 5950 9500 5950
Connection ~ 9500 5950
Wire Wire Line
	9500 5950 9500 6050
$Comp
L power:+5V #PWR08
U 1 1 60B2FD30
P 9500 5350
F 0 "#PWR08" H 9500 5200 50  0001 C CNN
F 1 "+5V" H 9515 5523 50  0000 C CNN
F 2 "" H 9500 5350 50  0001 C CNN
F 3 "" H 9500 5350 50  0001 C CNN
	1    9500 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 5750 9500 5750
Wire Wire Line
	9500 5750 9500 5350
Text GLabel 9350 5650 0    50   Output ~ 0
RX
Text GLabel 9350 5550 0    50   Input ~ 0
TX
Text GLabel 8700 5450 0    50   Output ~ 0
RTS
Wire Wire Line
	9100 5450 9600 5450
Wire Wire Line
	8700 5450 8800 5450
$Comp
L Device:R_POT_TRIM RV1
U 1 1 60B81F92
P 6100 5500
F 0 "RV1" V 5893 5500 50  0000 C CNN
F 1 "10k" V 5984 5500 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Runtron_RM-065_Vertical" H 6100 5500 50  0001 C CNN
F 3 "~" H 6100 5500 50  0001 C CNN
	1    6100 5500
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR05
U 1 1 60B90F29
P 4700 6000
F 0 "#PWR05" H 4700 5750 50  0001 C CNN
F 1 "GNDREF" H 4705 5827 50  0001 C CNN
F 2 "" H 4700 6000 50  0001 C CNN
F 3 "" H 4700 6000 50  0001 C CNN
	1    4700 6000
	1    0    0    -1  
$EndComp
Text GLabel 4950 5950 0    50   Input ~ 0
RS
Text GLabel 4950 5750 0    50   Input ~ 0
EN
Text GLabel 4950 6950 0    50   Input ~ 0
D7
Text GLabel 4950 6850 0    50   Input ~ 0
D6
Text GLabel 4950 6750 0    50   Input ~ 0
D5
Text GLabel 4950 6650 0    50   Input ~ 0
D4
$Comp
L power:+5V #PWR03
U 1 1 60BB6F7E
P 5450 5450
F 0 "#PWR03" H 5450 5300 50  0001 C CNN
F 1 "+5V" H 5465 5623 50  0000 C CNN
F 2 "" H 5450 5450 50  0001 C CNN
F 3 "" H 5450 5450 50  0001 C CNN
	1    5450 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR04
U 1 1 60BB79AC
P 5450 7250
F 0 "#PWR04" H 5450 7000 50  0001 C CNN
F 1 "GNDREF" H 5455 7077 50  0001 C CNN
F 2 "" H 5450 7250 50  0001 C CNN
F 3 "" H 5450 7250 50  0001 C CNN
	1    5450 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 5550 9600 5550
Wire Wire Line
	9600 5650 9350 5650
NoConn ~ 9900 1400
NoConn ~ 9900 3300
NoConn ~ 2200 3900
NoConn ~ 2200 2600
NoConn ~ 2200 2700
NoConn ~ 1000 1500
$Comp
L Device:CP C5
U 1 1 60DA4821
P 2900 7150
F 0 "C5" H 3018 7196 50  0000 L CNN
F 1 "100u" H 3018 7105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P5.00mm" H 2938 7000 50  0001 C CNN
F 3 "~" H 2900 7150 50  0001 C CNN
	1    2900 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 60DA7E75
P 2500 7150
F 0 "C4" H 2615 7196 50  0000 L CNN
F 1 "10n" H 2615 7105 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L9.0mm_W2.5mm_P7.50mm_MKT" H 2538 7000 50  0001 C CNN
F 3 "~" H 2500 7150 50  0001 C CNN
	1    2500 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 60DA8BED
P 8950 5450
F 0 "C1" V 8698 5450 50  0000 C CNN
F 1 "100n" V 8789 5450 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L9.0mm_W2.6mm_P7.50mm_MKT" H 8988 5300 50  0001 C CNN
F 3 "~" H 8950 5450 50  0001 C CNN
	1    8950 5450
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 60DB5BD7
P 3250 1500
F 0 "C2" V 2998 1500 50  0000 C CNN
F 1 "20p" V 3089 1500 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 3288 1350 50  0001 C CNN
F 3 "~" H 3250 1500 50  0001 C CNN
	1    3250 1500
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 60DB675D
P 3250 2000
F 0 "C3" V 3500 2000 50  0000 C CNN
F 1 "20p" V 3400 2000 50  0000 C CNN
F 2 "Capacitor_THT:C_Rect_L4.0mm_W2.5mm_P2.50mm" H 3288 1850 50  0001 C CNN
F 3 "~" H 3250 2000 50  0001 C CNN
	1    3250 2000
	0    1    1    0   
$EndComp
$Comp
L Device:D D9
U 1 1 60DC47DB
P 3300 7150
F 0 "D9" V 3254 7230 50  0000 L CNN
F 1 "D" V 3345 7230 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 3300 7150 50  0001 C CNN
F 3 "~" H 3300 7150 50  0001 C CNN
	1    3300 7150
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR022
U 1 1 60DCD335
P 3300 7400
F 0 "#PWR022" H 3300 7150 50  0001 C CNN
F 1 "GNDREF" H 3305 7227 50  0000 C CNN
F 2 "" H 3300 7400 50  0001 C CNN
F 3 "" H 3300 7400 50  0001 C CNN
	1    3300 7400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 60DCE076
P 3300 6850
F 0 "#PWR021" H 3300 6700 50  0001 C CNN
F 1 "+5V" H 3315 7023 50  0000 C CNN
F 2 "" H 3300 6850 50  0001 C CNN
F 3 "" H 3300 6850 50  0001 C CNN
	1    3300 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 6950 3300 7000
Wire Wire Line
	3300 6850 3300 6950
Connection ~ 3300 6950
Wire Wire Line
	2900 7000 2900 6950
Connection ~ 2900 6950
Wire Wire Line
	2900 6950 3300 6950
Wire Wire Line
	2500 7000 2500 6950
Wire Wire Line
	2500 6950 2900 6950
Wire Wire Line
	3300 7350 3300 7300
Wire Wire Line
	3300 7400 3300 7350
Connection ~ 3300 7350
Wire Wire Line
	2900 7300 2900 7350
Connection ~ 2900 7350
Wire Wire Line
	2900 7350 3300 7350
Wire Wire Line
	2500 7300 2500 7350
Wire Wire Line
	2500 7350 2900 7350
$Comp
L power:PWR_FLAG #FLG01
U 1 1 60E08B17
P 3500 6950
F 0 "#FLG01" H 3500 7025 50  0001 C CNN
F 1 "PWR_FLAG" V 3500 7078 50  0001 L CNN
F 2 "" H 3500 6950 50  0001 C CNN
F 3 "~" H 3500 6950 50  0001 C CNN
	1    3500 6950
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 60E0986C
P 3500 7350
F 0 "#FLG02" H 3500 7425 50  0001 C CNN
F 1 "PWR_FLAG" V 3500 7478 50  0001 L CNN
F 2 "" H 3500 7350 50  0001 C CNN
F 3 "~" H 3500 7350 50  0001 C CNN
	1    3500 7350
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 6950 3300 6950
Wire Wire Line
	3500 7350 3300 7350
$Comp
L Timer_RTC:DS1307+ U2
U 1 1 60F0D346
P 2500 5650
F 0 "U2" H 2800 5250 50  0000 L CNN
F 1 "DS1307+" H 2000 6100 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 2500 5150 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1307.pdf" H 2500 5450 50  0001 C CNN
	1    2500 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y2
U 1 1 60F0DCCD
P 1450 5950
F 0 "Y2" V 1404 6081 50  0000 L CNN
F 1 "32kHz" V 1495 6081 50  0000 L CNN
F 2 "Crystal:Crystal_C26-LF_D2.1mm_L6.5mm_Horizontal" H 1450 5950 50  0001 C CNN
F 3 "~" H 1450 5950 50  0001 C CNN
	1    1450 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 5750 1450 5750
Wire Wire Line
	1450 5750 1450 5800
Wire Wire Line
	2000 5850 1850 5850
Wire Wire Line
	1850 5850 1850 6150
Wire Wire Line
	1850 6150 1450 6150
Wire Wire Line
	1450 6150 1450 6100
Text GLabel 1900 5450 0    50   Input ~ 0
SCL
Text GLabel 1900 5550 0    50   BiDi ~ 0
SDA
Wire Wire Line
	2000 5450 1900 5450
Wire Wire Line
	2000 5550 1900 5550
$Comp
L power:GNDREF #PWR0105
U 1 1 60F3D16B
P 2500 6150
F 0 "#PWR0105" H 2500 5900 50  0001 C CNN
F 1 "GNDREF" H 2505 5977 50  0001 C CNN
F 2 "" H 2500 6150 50  0001 C CNN
F 3 "" H 2500 6150 50  0001 C CNN
	1    2500 6150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 60F3DAC1
P 2400 5150
F 0 "#PWR0106" H 2400 5000 50  0001 C CNN
F 1 "+5V" H 2415 5323 50  0000 C CNN
F 2 "" H 2400 5150 50  0001 C CNN
F 3 "" H 2400 5150 50  0001 C CNN
	1    2400 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5150 2400 5250
Wire Wire Line
	2500 6150 2500 6050
$Comp
L Device:Battery_Cell BT1
U 1 1 60F5189B
P 2750 5100
F 0 "BT1" V 3005 5150 50  0000 C CNN
F 1 "CR2032" V 2914 5150 50  0000 C CNN
F 2 "Battery:BatteryHolder_ComfortableElectronic_CH273-2450_1x2450" V 2750 5160 50  0001 C CNN
F 3 "~" V 2750 5160 50  0001 C CNN
	1    2750 5100
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDREF #PWR0107
U 1 1 60F52E2E
P 2900 5150
F 0 "#PWR0107" H 2900 4900 50  0001 C CNN
F 1 "GNDREF" H 3250 5150 50  0001 C CNN
F 2 "" H 2900 5150 50  0001 C CNN
F 3 "" H 2900 5150 50  0001 C CNN
	1    2900 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5150 2900 5100
Wire Wire Line
	2900 5100 2850 5100
Wire Wire Line
	2550 5100 2500 5100
Wire Wire Line
	2500 5100 2500 5250
NoConn ~ 3000 5650
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 60F9F78B
P 2500 5100
F 0 "#FLG0101" H 2500 5175 50  0001 C CNN
F 1 "PWR_FLAG" H 2500 5273 50  0001 C CNN
F 2 "" H 2500 5100 50  0001 C CNN
F 3 "~" H 2500 5100 50  0001 C CNN
	1    2500 5100
	1    0    0    -1  
$EndComp
Connection ~ 2500 5100
$Comp
L Display_Character:WC1602A DS1
U 1 1 61012FEC
P 5450 6350
F 0 "DS1" H 5700 5550 50  0000 C CNN
F 1 "WC1602A" H 5700 7150 50  0000 C CNN
F 2 "Display:WC1602A" H 5450 5450 50  0001 C CIN
F 3 "http://www.wincomlcd.com/pdf/WC1602A-SFYLYHTC06.pdf" H 6150 6350 50  0001 C CNN
	1    5450 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 6650 5050 6650
Wire Wire Line
	4950 6750 5050 6750
Wire Wire Line
	4950 6850 5050 6850
Wire Wire Line
	4950 6950 5050 6950
Wire Wire Line
	4950 5950 5050 5950
Wire Wire Line
	4950 5750 5050 5750
Wire Wire Line
	5050 5850 4700 5850
Wire Wire Line
	4700 5850 4700 6000
Wire Wire Line
	5450 5450 5450 5500
Wire Wire Line
	5900 5500 5450 5500
Connection ~ 5450 5500
Wire Wire Line
	5450 5500 5450 5550
Wire Wire Line
	5850 6050 5900 6050
Wire Wire Line
	5900 6050 5900 5500
Wire Wire Line
	6100 5750 6100 5650
Wire Wire Line
	5850 5750 6100 5750
Wire Wire Line
	5950 5500 5900 5500
Connection ~ 5900 5500
Wire Wire Line
	5450 7250 5450 7150
$Comp
L power:GNDREF #PWR0108
U 1 1 61096A8A
P 6300 6250
F 0 "#PWR0108" H 6300 6000 50  0001 C CNN
F 1 "GNDREF" H 6305 6077 50  0000 C CNN
F 2 "" H 6300 6250 50  0001 C CNN
F 3 "" H 6300 6250 50  0001 C CNN
	1    6300 6250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5500 6300 5500
Wire Wire Line
	6300 5500 6300 6150
Wire Wire Line
	5850 6150 6300 6150
Connection ~ 6300 6150
Wire Wire Line
	6300 6150 6300 6250
$Comp
L Converter_ACDC:HLK-PM01 PS1
U 1 1 610D6875
P 1800 7200
F 0 "PS1" H 1800 7525 50  0000 C CNN
F 1 "HLK-PM01" H 1800 7434 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 1800 6900 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=54" H 2200 6850 50  0001 C CNN
	1    1800 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 7100 2250 7100
Wire Wire Line
	2250 7100 2250 6950
Wire Wire Line
	2250 6950 2500 6950
Connection ~ 2500 6950
Wire Wire Line
	2200 7300 2250 7300
Wire Wire Line
	2250 7300 2250 7350
Wire Wire Line
	2250 7350 2500 7350
Connection ~ 2500 7350
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 610EB070
P 1100 7250
F 0 "J1" H 1018 6925 50  0000 C CNN
F 1 "AC 90-240" H 1018 7016 50  0000 C CNN
F 2 "Connector_Phoenix_MSTB:PhoenixContact_MSTBA_2,5_2-G-5,08_1x02_P5.08mm_Horizontal" H 1100 7250 50  0001 C CNN
F 3 "~" H 1100 7250 50  0001 C CNN
	1    1100 7250
	-1   0    0    1   
$EndComp
Wire Notes Line
	500  4750 11200 4750
Wire Notes Line
	7450 6500 7450 500 
Wire Notes Line
	500  6400 4050 6400
Wire Notes Line
	4050 500  4050 7800
Wire Wire Line
	1300 7150 1350 7150
Wire Wire Line
	1350 7150 1350 7300
Wire Wire Line
	1350 7300 1400 7300
Wire Wire Line
	1300 7250 1400 7250
Wire Wire Line
	1400 7250 1400 7100
Text Notes 650  700  0    50   ~ 0
Microcontrolador
Text Notes 4250 700  0    50   ~ 0
Entradas
Text Notes 7550 700  0    50   ~ 0
Saídas
Text Notes 7550 4950 0    50   ~ 0
Entrada de programação ISP
Text Notes 650  4950 0    50   ~ 0
Real time clock
Text Notes 4150 4950 0    50   ~ 0
Display LCD 16x2
Text Notes 600  6550 0    50   ~ 0
Conversão ca/cc
$EndSCHEMATC
