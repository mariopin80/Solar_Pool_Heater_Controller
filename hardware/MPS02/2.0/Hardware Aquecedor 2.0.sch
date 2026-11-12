EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Controlador de Piscina MPS02"
Date "2021-12-29"
Rev "2.0"
Comp "MP ElectroLabs"
Comment1 "Desenvolvido no Brasil"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 4900 3400 0    50   Output ~ 0
PB1
Wire Wire Line
	5000 3400 4900 3400
Text GLabel 4900 3500 0    50   Output ~ 0
PB2
Wire Wire Line
	5000 3500 4900 3500
Text GLabel 4900 3600 0    50   Output ~ 0
PB3
Wire Wire Line
	5000 3600 4900 3600
$Comp
L Relay:FINDER-36.11 K1
U 1 1 60AA5F7F
P 9950 1700
F 0 "K1" H 10380 1746 50  0000 L CNN
F 1 "AQUECEDOR" H 9600 1300 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Finder_36.11" H 11220 1670 50  0001 C CNN
F 3 "https://gfinder.findernet.com/public/attachments/36/EN/S36EN.pdf" H 9950 1700 50  0001 C CNN
	1    9950 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:D D8
U 1 1 60AA6FA2
P 9050 1700
F 0 "D8" V 9004 1780 50  0000 L CNN
F 1 "1N4148" V 9095 1780 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 9050 1700 50  0001 C CNN
F 3 "~" H 9050 1700 50  0001 C CNN
	1    9050 1700
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N3904 Q1
U 1 1 60AA8565
P 8950 2350
F 0 "Q1" H 9140 2396 50  0000 L CNN
F 1 "2N3904" H 9140 2305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9150 2275 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 8950 2350 50  0001 L CNN
	1    8950 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR026
U 1 1 60AA9A28
P 9050 2650
F 0 "#PWR026" H 9050 2400 50  0001 C CNN
F 1 "GNDREF" H 9055 2477 50  0001 C CNN
F 2 "" H 9050 2650 50  0001 C CNN
F 3 "" H 9050 2650 50  0001 C CNN
	1    9050 2650
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR025
U 1 1 60AAA182
P 9050 1250
F 0 "#PWR025" H 9050 1100 50  0001 C CNN
F 1 "+5V" H 9065 1423 50  0000 C CNN
F 2 "" H 9050 1250 50  0001 C CNN
F 3 "" H 9050 1250 50  0001 C CNN
	1    9050 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 60AAA9B3
P 8750 1500
F 0 "R7" H 8820 1546 50  0000 L CNN
F 1 "330" H 8820 1455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8680 1500 50  0001 C CNN
F 3 "~" H 8750 1500 50  0001 C CNN
	1    8750 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D6
U 1 1 60AAB1A0
P 8750 1850
F 0 "D6" V 8789 1732 50  0000 R CNN
F 1 "LED" V 8698 1732 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8750 1850 50  0001 C CNN
F 3 "~" H 8750 1850 50  0001 C CNN
	1    8750 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 1250 9050 1300
Wire Wire Line
	8750 1350 8750 1300
Wire Wire Line
	8750 1300 9050 1300
Connection ~ 9050 1300
Wire Wire Line
	9050 1300 9050 1550
Wire Wire Line
	9750 1300 9750 1400
Wire Wire Line
	8750 1650 8750 1700
Wire Wire Line
	9050 2150 9050 2050
Wire Wire Line
	8750 2000 8750 2050
Wire Wire Line
	8750 2050 9050 2050
Connection ~ 9050 2050
Wire Wire Line
	9050 2050 9050 1850
Wire Wire Line
	9750 2000 9750 2050
Wire Wire Line
	9050 2650 9050 2550
Wire Wire Line
	9050 1300 9750 1300
Wire Wire Line
	9050 2050 9750 2050
$Comp
L Device:R R5
U 1 1 60ABA795
P 8500 2350
F 0 "R5" V 8293 2350 50  0000 C CNN
F 1 "10k" V 8384 2350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8430 2350 50  0001 C CNN
F 3 "~" H 8500 2350 50  0001 C CNN
	1    8500 2350
	0    1    1    0   
$EndComp
Text GLabel 8250 2350 0    50   Input ~ 0
RLY_AQ
Wire Wire Line
	8250 2350 8350 2350
Wire Wire Line
	8650 2350 8750 2350
$Comp
L Relay:FINDER-36.11 K2
U 1 1 60AC67EF
P 9950 3600
F 0 "K2" H 10380 3646 50  0000 L CNN
F 1 "FILTRO" H 9800 3200 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Finder_36.11" H 11220 3570 50  0001 C CNN
F 3 "https://gfinder.findernet.com/public/attachments/36/EN/S36EN.pdf" H 9950 3600 50  0001 C CNN
	1    9950 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:D D9
U 1 1 60AC67F5
P 9050 3600
F 0 "D9" V 9004 3680 50  0000 L CNN
F 1 "1N4148" V 9095 3680 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 9050 3600 50  0001 C CNN
F 3 "~" H 9050 3600 50  0001 C CNN
	1    9050 3600
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N3904 Q2
U 1 1 60AC67FB
P 8950 4250
F 0 "Q2" H 9140 4296 50  0000 L CNN
F 1 "2N3904" H 9140 4205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9150 4175 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 8950 4250 50  0001 L CNN
	1    8950 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR028
U 1 1 60AC6801
P 9050 4550
F 0 "#PWR028" H 9050 4300 50  0001 C CNN
F 1 "GNDREF" H 9055 4377 50  0001 C CNN
F 2 "" H 9050 4550 50  0001 C CNN
F 3 "" H 9050 4550 50  0001 C CNN
	1    9050 4550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR027
U 1 1 60AC6807
P 9050 3150
F 0 "#PWR027" H 9050 3000 50  0001 C CNN
F 1 "+5V" H 9065 3323 50  0000 C CNN
F 2 "" H 9050 3150 50  0001 C CNN
F 3 "" H 9050 3150 50  0001 C CNN
	1    9050 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 60AC680D
P 8750 3400
F 0 "R8" H 8820 3446 50  0000 L CNN
F 1 "330" H 8820 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8680 3400 50  0001 C CNN
F 3 "~" H 8750 3400 50  0001 C CNN
	1    8750 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D7
U 1 1 60AC6813
P 8750 3750
F 0 "D7" V 8789 3632 50  0000 R CNN
F 1 "LED" V 8698 3632 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 8750 3750 50  0001 C CNN
F 3 "~" H 8750 3750 50  0001 C CNN
	1    8750 3750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 3150 9050 3200
Wire Wire Line
	8750 3250 8750 3200
Wire Wire Line
	8750 3200 9050 3200
Connection ~ 9050 3200
Wire Wire Line
	9050 3200 9050 3450
Wire Wire Line
	9750 3200 9750 3300
Wire Wire Line
	8750 3550 8750 3600
Wire Wire Line
	9050 4050 9050 3950
Wire Wire Line
	8750 3900 8750 3950
Wire Wire Line
	8750 3950 9050 3950
Connection ~ 9050 3950
Wire Wire Line
	9050 3950 9050 3750
Wire Wire Line
	9750 3900 9750 3950
Wire Wire Line
	9050 4550 9050 4450
Wire Wire Line
	9050 3200 9750 3200
Wire Wire Line
	9050 3950 9750 3950
$Comp
L Device:R R6
U 1 1 60AC6829
P 8500 4250
F 0 "R6" V 8293 4250 50  0000 C CNN
F 1 "10k" V 8384 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 8430 4250 50  0001 C CNN
F 3 "~" H 8500 4250 50  0001 C CNN
	1    8500 4250
	0    1    1    0   
$EndComp
Text GLabel 8250 4250 0    50   Input ~ 0
RLY_FL
Wire Wire Line
	8250 4250 8350 4250
Wire Wire Line
	8650 4250 8750 4250
$Comp
L Connector:Screw_Terminal_01x02 J7
U 1 1 60ACFE21
P 10800 1100
F 0 "J7" H 10880 1092 50  0000 L CNN
F 1 "AQC" H 10880 1001 50  0000 L CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_2-G-5.08_1x02_P5.08mm_Horizontal" H 10800 1100 50  0001 C CNN
F 3 "~" H 10800 1100 50  0001 C CNN
	1    10800 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 2000 10150 2050
Wire Wire Line
	10150 2050 10500 2050
Wire Wire Line
	10500 2050 10500 1200
Wire Wire Line
	10500 1200 10600 1200
Wire Wire Line
	10250 1400 10250 1100
Wire Wire Line
	10250 1100 10600 1100
$Comp
L Connector:Screw_Terminal_01x02 J8
U 1 1 60AD7F61
P 10800 3050
F 0 "J8" H 10880 3042 50  0000 L CNN
F 1 "FLT" H 10880 2951 50  0000 L CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_2-G-5.08_1x02_P5.08mm_Horizontal" H 10800 3050 50  0001 C CNN
F 3 "~" H 10800 3050 50  0001 C CNN
	1    10800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3950 10500 3950
Wire Wire Line
	10500 3950 10500 3150
Wire Wire Line
	10500 3150 10600 3150
Wire Wire Line
	10250 3050 10600 3050
Wire Wire Line
	10150 3950 10150 3900
Wire Wire Line
	10250 3050 10250 3300
$Comp
L Device:R R4
U 1 1 60AEA833
P 6600 1250
F 0 "R4" H 6670 1296 50  0000 L CNN
F 1 "10k" H 6670 1205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6530 1250 50  0001 C CNN
F 3 "~" H 6600 1250 50  0001 C CNN
	1    6600 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 60AEB044
P 7400 1500
F 0 "J6" H 7480 1492 50  0000 L CNN
F 1 "CLT" H 7480 1401 50  0000 L CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_2-G-5.08_1x02_P5.08mm_Horizontal" H 7400 1500 50  0001 C CNN
F 3 "~" H 7400 1500 50  0001 C CNN
	1    7400 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D5
U 1 1 60AEBE97
P 6900 1850
F 0 "D5" V 6854 1930 50  0000 L CNN
F 1 "1N4735" V 6945 1930 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6900 1850 50  0001 C CNN
F 3 "~" H 6900 1850 50  0001 C CNN
	1    6900 1850
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D4
U 1 1 60AED0EA
P 6900 1250
F 0 "D4" V 6854 1330 50  0000 L CNN
F 1 "1N4735" V 6945 1330 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6900 1250 50  0001 C CNN
F 3 "~" H 6900 1250 50  0001 C CNN
	1    6900 1250
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR022
U 1 1 60AF34ED
P 6900 2150
F 0 "#PWR022" H 6900 1900 50  0001 C CNN
F 1 "GNDREF" H 6905 1977 50  0001 C CNN
F 2 "" H 6900 2150 50  0001 C CNN
F 3 "" H 6900 2150 50  0001 C CNN
	1    6900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1400 6600 1500
Wire Wire Line
	6600 1500 6900 1500
Wire Wire Line
	6900 1400 6900 1500
Connection ~ 6900 1500
Wire Wire Line
	6900 1500 7200 1500
Wire Wire Line
	6900 1700 6900 1500
Wire Wire Line
	6900 2150 6900 2000
$Comp
L power:GNDREF #PWR024
U 1 1 60B01608
P 7150 1650
F 0 "#PWR024" H 7150 1400 50  0001 C CNN
F 1 "GNDREF" H 7350 1550 50  0001 C CNN
F 2 "" H 7150 1650 50  0001 C CNN
F 3 "" H 7150 1650 50  0001 C CNN
	1    7150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 1600 7150 1600
Wire Wire Line
	7150 1600 7150 1650
Wire Wire Line
	6600 1100 6600 1050
Wire Wire Line
	6600 1050 6900 1050
Connection ~ 6900 1050
Wire Wire Line
	6900 1050 6900 1100
Text GLabel 6450 1500 0    50   Output ~ 0
CLT_TMP
Wire Wire Line
	6450 1500 6600 1500
Connection ~ 6600 1500
$Comp
L Device:R R3
U 1 1 60B11F29
P 6550 3400
F 0 "R3" H 6620 3446 50  0000 L CNN
F 1 "10k" H 6620 3355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 6480 3400 50  0001 C CNN
F 3 "~" H 6550 3400 50  0001 C CNN
	1    6550 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J5
U 1 1 60B11F2F
P 7350 3650
F 0 "J5" H 7430 3642 50  0000 L CNN
F 1 "PSC" H 7430 3551 50  0000 L CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_2-G-5.08_1x02_P5.08mm_Horizontal" H 7350 3650 50  0001 C CNN
F 3 "~" H 7350 3650 50  0001 C CNN
	1    7350 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D3
U 1 1 60B11F35
P 6850 4000
F 0 "D3" V 6804 4080 50  0000 L CNN
F 1 "1N4735" V 6895 4080 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6850 4000 50  0001 C CNN
F 3 "~" H 6850 4000 50  0001 C CNN
	1    6850 4000
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 60B11F3B
P 6850 3400
F 0 "D2" V 6804 3480 50  0000 L CNN
F 1 "1N4735" V 6895 3480 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 6850 3400 50  0001 C CNN
F 3 "~" H 6850 3400 50  0001 C CNN
	1    6850 3400
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR020
U 1 1 60B11F41
P 6850 4300
F 0 "#PWR020" H 6850 4050 50  0001 C CNN
F 1 "GNDREF" H 6855 4127 50  0001 C CNN
F 2 "" H 6850 4300 50  0001 C CNN
F 3 "" H 6850 4300 50  0001 C CNN
	1    6850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3550 6550 3650
Wire Wire Line
	6550 3650 6850 3650
Wire Wire Line
	6850 3550 6850 3650
Connection ~ 6850 3650
Wire Wire Line
	6850 3650 7150 3650
Wire Wire Line
	6850 3850 6850 3650
Wire Wire Line
	6850 4300 6850 4150
$Comp
L power:GNDREF #PWR023
U 1 1 60B11F4E
P 7100 3800
F 0 "#PWR023" H 7100 3550 50  0001 C CNN
F 1 "GNDREF" H 7300 3700 50  0001 C CNN
F 2 "" H 7100 3800 50  0001 C CNN
F 3 "" H 7100 3800 50  0001 C CNN
	1    7100 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 3750 7100 3750
Wire Wire Line
	7100 3750 7100 3800
Wire Wire Line
	6550 3250 6550 3200
Wire Wire Line
	6550 3200 6850 3200
Connection ~ 6850 3200
Wire Wire Line
	6850 3200 6850 3250
Text GLabel 6400 3650 0    50   Output ~ 0
PSC_TMP
Wire Wire Line
	6400 3650 6550 3650
Connection ~ 6550 3650
$Comp
L Connector:Conn_01x06_Female J4
U 1 1 60B2656A
P 6800 5450
F 0 "J4" H 6828 5426 50  0000 L CNN
F 1 "FTDI" H 6828 5335 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 6800 5450 50  0001 C CNN
F 3 "~" H 6800 5450 50  0001 C CNN
	1    6800 5450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR018
U 1 1 60B278B9
P 6500 5850
F 0 "#PWR018" H 6500 5600 50  0001 C CNN
F 1 "GNDREF" H 6505 5677 50  0001 C CNN
F 2 "" H 6500 5850 50  0001 C CNN
F 3 "" H 6500 5850 50  0001 C CNN
	1    6500 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 5650 6500 5650
Wire Wire Line
	6500 5650 6500 5750
Wire Wire Line
	6600 5750 6500 5750
Connection ~ 6500 5750
Wire Wire Line
	6500 5750 6500 5850
$Comp
L power:+5V #PWR017
U 1 1 60B2FD30
P 6500 5150
F 0 "#PWR017" H 6500 5000 50  0001 C CNN
F 1 "+5V" H 6515 5323 50  0000 C CNN
F 2 "" H 6500 5150 50  0001 C CNN
F 3 "" H 6500 5150 50  0001 C CNN
	1    6500 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 5550 6500 5550
Wire Wire Line
	6500 5550 6500 5150
Text GLabel 6350 5450 0    50   Output ~ 0
RX
Text GLabel 6350 5350 0    50   Input ~ 0
TX
Text GLabel 5700 5250 0    50   Output ~ 0
RTS
Wire Wire Line
	6100 5250 6600 5250
Wire Wire Line
	5700 5250 5800 5250
$Comp
L Device:R_POT_TRIM RV1
U 1 1 60B81F92
P 4500 1450
F 0 "RV1" V 4293 1450 50  0000 C CNN
F 1 "10k" V 4384 1450 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Runtron_RM-065_Vertical" H 4500 1450 50  0001 C CNN
F 3 "~" H 4500 1450 50  0001 C CNN
	1    4500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR013
U 1 1 60B90F29
P 4500 1750
F 0 "#PWR013" H 4500 1500 50  0001 C CNN
F 1 "GNDREF" H 4505 1577 50  0001 C CNN
F 2 "" H 4500 1750 50  0001 C CNN
F 3 "" H 4500 1750 50  0001 C CNN
	1    4500 1750
	1    0    0    -1  
$EndComp
Text GLabel 4950 1550 0    50   Input ~ 0
RS
Text GLabel 4950 1750 0    50   Input ~ 0
EN
Text GLabel 4950 2150 0    50   Input ~ 0
D7
Text GLabel 4950 2050 0    50   Input ~ 0
D6
Text GLabel 4950 1950 0    50   Input ~ 0
D5
Text GLabel 4950 1850 0    50   Input ~ 0
D4
$Comp
L power:GNDREF #PWR015
U 1 1 60BB79AC
P 4650 2450
F 0 "#PWR015" H 4650 2200 50  0001 C CNN
F 1 "GNDREF" H 4655 2277 50  0001 C CNN
F 2 "" H 4650 2450 50  0001 C CNN
F 3 "" H 4650 2450 50  0001 C CNN
	1    4650 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 5350 6600 5350
Wire Wire Line
	6600 5450 6350 5450
NoConn ~ 10050 1400
NoConn ~ 10050 3300
$Comp
L Device:CP C4
U 1 1 60DA4821
P 3400 7150
F 0 "C4" H 3518 7196 50  0000 L CNN
F 1 "100u" H 3518 7105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 3438 7000 50  0001 C CNN
F 3 "~" H 3400 7150 50  0001 C CNN
	1    3400 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 60DA7E75
P 3000 7150
F 0 "C2" H 3115 7196 50  0000 L CNN
F 1 "10n" H 3115 7105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3038 7000 50  0001 C CNN
F 3 "~" H 3000 7150 50  0001 C CNN
	1    3000 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 60DA8BED
P 5950 5250
F 0 "C7" V 5698 5250 50  0000 C CNN
F 1 "100n" V 5789 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 5988 5100 50  0001 C CNN
F 3 "~" H 5950 5250 50  0001 C CNN
	1    5950 5250
	0    1    1    0   
$EndComp
$Comp
L Device:D D1
U 1 1 60DC47DB
P 3800 7150
F 0 "D1" V 3754 7230 50  0000 L CNN
F 1 "D" V 3845 7230 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P7.62mm_Horizontal" H 3800 7150 50  0001 C CNN
F 3 "~" H 3800 7150 50  0001 C CNN
	1    3800 7150
	0    1    1    0   
$EndComp
$Comp
L power:GNDREF #PWR011
U 1 1 60DCD335
P 3800 7400
F 0 "#PWR011" H 3800 7150 50  0001 C CNN
F 1 "GNDREF" H 3805 7227 50  0001 C CNN
F 2 "" H 3800 7400 50  0001 C CNN
F 3 "" H 3800 7400 50  0001 C CNN
	1    3800 7400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 60DCE076
P 3800 6850
F 0 "#PWR010" H 3800 6700 50  0001 C CNN
F 1 "+5V" H 3815 7023 50  0000 C CNN
F 2 "" H 3800 6850 50  0001 C CNN
F 3 "" H 3800 6850 50  0001 C CNN
	1    3800 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 6950 3800 7000
Wire Wire Line
	3800 6850 3800 6950
Connection ~ 3800 6950
Wire Wire Line
	3400 7000 3400 6950
Connection ~ 3400 6950
Wire Wire Line
	3400 6950 3800 6950
Wire Wire Line
	3000 7000 3000 6950
Wire Wire Line
	3000 6950 3400 6950
Wire Wire Line
	3800 7350 3800 7300
Wire Wire Line
	3800 7400 3800 7350
Connection ~ 3800 7350
Wire Wire Line
	3400 7300 3400 7350
Connection ~ 3400 7350
Wire Wire Line
	3400 7350 3800 7350
Wire Wire Line
	3000 7300 3000 7350
Wire Wire Line
	3000 7350 3400 7350
Wire Wire Line
	4000 6950 3800 6950
Wire Wire Line
	4950 1850 5050 1850
Wire Wire Line
	4950 1950 5050 1950
Wire Wire Line
	4950 2050 5050 2050
Wire Wire Line
	4950 2150 5050 2150
Wire Wire Line
	4950 1550 5050 1550
Wire Wire Line
	4950 1750 5050 1750
Wire Wire Line
	4650 2450 4650 2350
$Comp
L Converter_ACDC:HLK-PM01 PS1
U 1 1 610D6875
P 2300 7200
F 0 "PS1" H 2300 7525 50  0000 C CNN
F 1 "HLK-PM01" H 2300 7434 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 2300 6900 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=54" H 2700 6850 50  0001 C CNN
	1    2300 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 7100 2750 7100
Wire Wire Line
	2750 7100 2750 6950
Wire Wire Line
	2750 6950 3000 6950
Connection ~ 3000 6950
Wire Wire Line
	2700 7300 2750 7300
Wire Wire Line
	2750 7300 2750 7350
Wire Wire Line
	2750 7350 3000 7350
Connection ~ 3000 7350
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 610EB070
P 1600 7250
F 0 "J1" H 1518 6925 50  0000 C CNN
F 1 "AC 90-240" H 1518 7016 50  0000 C CNN
F 2 "Connector_Phoenix_MC_HighVoltage:PhoenixContact_MC_1,5_2-G-5.08_1x02_P5.08mm_Horizontal" H 1600 7250 50  0001 C CNN
F 3 "~" H 1600 7250 50  0001 C CNN
	1    1600 7250
	-1   0    0    1   
$EndComp
Wire Notes Line
	500  4750 11200 4750
Wire Wire Line
	1800 7150 1850 7150
Wire Wire Line
	1850 7150 1850 7300
Wire Wire Line
	1850 7300 1900 7300
Wire Wire Line
	1800 7250 1900 7250
Wire Wire Line
	1900 7250 1900 7100
Text Notes 650  700  0    50   ~ 0
Microcontrolador
Text Notes 6050 700  0    50   ~ 0
Entradas
Text Notes 8000 700  0    50   ~ 0
Saídas
Text Notes 4300 4950 0    50   ~ 0
Entrada de programação ISP
Text Notes 650  4950 0    50   ~ 0
Real time clock
Text Notes 4200 700  0    50   ~ 0
Conexões internas\n
Text Notes 600  6550 0    50   ~ 0
Alimentação\n
$Comp
L Timer_RTC:DS3231M U2
U 1 1 61D0F29B
P 2200 5650
F 0 "U2" H 2550 5150 50  0000 C CNN
F 1 "DS3231M" H 2650 5250 50  0000 C CNN
F 2 "Package_SO:SOIC-16W_7.5x10.3mm_P1.27mm" H 2200 5050 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS3231.pdf" H 2470 5700 50  0001 C CNN
	1    2200 5650
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR06
U 1 1 61D0FCCD
P 2200 6150
F 0 "#PWR06" H 2200 5900 50  0001 C CNN
F 1 "GNDREF" H 2205 5977 50  0001 C CNN
F 2 "" H 2200 6150 50  0001 C CNN
F 3 "" H 2200 6150 50  0001 C CNN
	1    2200 6150
	1    0    0    -1  
$EndComp
Text GLabel 1600 5450 0    50   Input ~ 0
SCL
Text GLabel 1600 5550 0    50   BiDi ~ 0
SDA
Wire Wire Line
	1700 5450 1600 5450
Wire Wire Line
	1700 5550 1600 5550
$Comp
L power:+5V #PWR05
U 1 1 61D1A43C
P 2100 5150
F 0 "#PWR05" H 2100 5000 50  0001 C CNN
F 1 "+5V" H 2115 5323 50  0000 C CNN
F 2 "" H 2100 5150 50  0001 C CNN
F 3 "" H 2100 5150 50  0001 C CNN
	1    2100 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6150 2200 6050
Wire Wire Line
	2100 5250 2100 5150
$Comp
L Device:Battery_Cell BT1
U 1 1 61D385DB
P 2550 5150
F 0 "BT1" V 2800 5100 50  0000 C CNN
F 1 "Battery_Cell" V 2700 4950 50  0000 C CNN
F 2 "Battery:BatteryHolder_Keystone_103_1x20mm" V 2550 5210 50  0001 C CNN
F 3 "~" V 2550 5210 50  0001 C CNN
	1    2550 5150
	0    -1   -1   0   
$EndComp
$Comp
L power:GNDREF #PWR07
U 1 1 61D399C9
P 2800 5200
F 0 "#PWR07" H 2800 4950 50  0001 C CNN
F 1 "GNDREF" H 2805 5027 50  0001 C CNN
F 2 "" H 2800 5200 50  0001 C CNN
F 3 "" H 2800 5200 50  0001 C CNN
	1    2800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5200 2800 5150
Wire Wire Line
	2800 5150 2650 5150
Wire Wire Line
	2350 5150 2300 5150
Wire Wire Line
	2200 5150 2200 5250
Text GLabel 1600 5850 0    50   Input ~ 0
RTS
Wire Wire Line
	1600 5850 1700 5850
NoConn ~ 2700 5450
NoConn ~ 2700 5750
$Comp
L power:PWR_FLAG #FLG01
U 1 1 61DA8905
P 2300 5100
F 0 "#FLG01" H 2300 5175 50  0001 C CNN
F 1 "PWR_FLAG" H 2300 5273 50  0001 C CNN
F 2 "" H 2300 5100 50  0001 C CNN
F 3 "~" H 2300 5100 50  0001 C CNN
	1    2300 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 5100 2300 5150
Connection ~ 2300 5150
Wire Wire Line
	2300 5150 2200 5150
$Comp
L RF_Module:ESP32-WROOM-32D U1
U 1 1 61DAFF00
P 2000 2800
F 0 "U1" H 1650 4150 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 2450 4200 50  0000 C CNN
F 2 "RF_Module:ESP32-WROOM-32" H 2000 1300 50  0001 C CNN
F 3 "https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32d_esp32-wroom-32u_datasheet_en.pdf" H 1700 2850 50  0001 C CNN
	1    2000 2800
	1    0    0    -1  
$EndComp
Text GLabel 2700 3800 2    50   Input ~ 0
PB3
Wire Wire Line
	2600 3800 2700 3800
$Comp
L Switch:SW_Push SW2
U 1 1 61E3C49C
P 3350 1600
F 0 "SW2" H 3450 1850 50  0000 C CNN
F 1 "PRG" H 3450 1750 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 3350 1800 50  0001 C CNN
F 3 "~" H 3350 1800 50  0001 C CNN
	1    3350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 3900 2700 3900
Text GLabel 2700 3900 2    50   Input ~ 0
PB2
Wire Wire Line
	2600 3600 2700 3600
Text GLabel 2700 3600 2    50   Input ~ 0
PB1
Wire Wire Line
	2700 3500 2600 3500
Wire Wire Line
	2700 3400 2600 3400
Wire Wire Line
	2700 2400 2600 2400
Wire Wire Line
	2700 3300 2600 3300
Wire Wire Line
	2700 3700 2600 3700
Text GLabel 2700 2400 2    50   Output ~ 0
EN
Text GLabel 2700 3500 2    50   Output ~ 0
D4
Text GLabel 2700 3400 2    50   Output ~ 0
D5
Text GLabel 2700 3300 2    50   Output ~ 0
D6
Text GLabel 2700 3700 2    50   Output ~ 0
D7
Wire Wire Line
	2600 3000 2700 3000
Wire Wire Line
	2600 3100 2700 3100
Text GLabel 2700 3000 2    50   BiDi ~ 0
SDA
Text GLabel 2700 3100 2    50   Output ~ 0
SCL
$Comp
L Device:C C3
U 1 1 61E6D9DB
P 3350 1800
F 0 "C3" V 3600 1800 50  0000 C CNN
F 1 "C" V 3500 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 3388 1650 50  0001 C CNN
F 3 "~" H 3350 1800 50  0001 C CNN
	1    3350 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 61E6E36D
P 3100 1350
F 0 "R2" H 3170 1396 50  0000 L CNN
F 1 "10k" H 3170 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 3030 1350 50  0001 C CNN
F 3 "~" H 3100 1350 50  0001 C CNN
	1    3100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR09
U 1 1 61E6F7E7
P 3600 1850
F 0 "#PWR09" H 3600 1600 50  0001 C CNN
F 1 "GNDREF" H 3605 1677 50  0001 C CNN
F 2 "" H 3600 1850 50  0001 C CNN
F 3 "" H 3600 1850 50  0001 C CNN
	1    3600 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 1600 3600 1600
Wire Wire Line
	3600 1600 3600 1800
Wire Wire Line
	3500 1800 3600 1800
Connection ~ 3600 1800
Wire Wire Line
	3600 1800 3600 1850
Wire Wire Line
	3150 1600 3100 1600
Wire Wire Line
	3200 1800 3100 1800
Wire Wire Line
	3100 1800 3100 1600
Connection ~ 3100 1600
Wire Wire Line
	3100 1600 3100 1500
$Comp
L power:+3.3V #PWR08
U 1 1 61E9C443
P 3100 1100
F 0 "#PWR08" H 3100 950 50  0001 C CNN
F 1 "+3.3V" H 3115 1273 50  0000 C CNN
F 2 "" H 3100 1100 50  0001 C CNN
F 3 "" H 3100 1100 50  0001 C CNN
	1    3100 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1200 3100 1100
$Comp
L Switch:SW_Push SW1
U 1 1 61EB297C
P 1000 1600
F 0 "SW1" H 1000 1885 50  0000 C CNN
F 1 "RST" H 1000 1794 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 1000 1800 50  0001 C CNN
F 3 "~" H 1000 1800 50  0001 C CNN
	1    1000 1600
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61EB2982
P 1000 1800
F 0 "C1" V 1250 1800 50  0000 C CNN
F 1 "C" V 1150 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 1038 1650 50  0001 C CNN
F 3 "~" H 1000 1800 50  0001 C CNN
	1    1000 1800
	0    -1   1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 61EB2988
P 1250 1350
F 0 "R1" H 1180 1396 50  0000 R CNN
F 1 "10k" H 1180 1305 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" V 1180 1350 50  0001 C CNN
F 3 "~" H 1250 1350 50  0001 C CNN
	1    1250 1350
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR01
U 1 1 61EB298E
P 750 1850
F 0 "#PWR01" H 750 1600 50  0001 C CNN
F 1 "GNDREF" H 755 1677 50  0001 C CNN
F 2 "" H 750 1850 50  0001 C CNN
F 3 "" H 750 1850 50  0001 C CNN
	1    750  1850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	800  1600 750  1600
Wire Wire Line
	750  1600 750  1800
Wire Wire Line
	850  1800 750  1800
Connection ~ 750  1800
Wire Wire Line
	750  1800 750  1850
Wire Wire Line
	1200 1600 1250 1600
Wire Wire Line
	1150 1800 1250 1800
Wire Wire Line
	1250 1800 1250 1600
Connection ~ 1250 1600
Wire Wire Line
	1250 1600 1250 1500
$Comp
L power:+3.3V #PWR02
U 1 1 61EB299F
P 1250 1100
F 0 "#PWR02" H 1250 950 50  0001 C CNN
F 1 "+3.3V" H 1265 1273 50  0000 C CNN
F 2 "" H 1250 1100 50  0001 C CNN
F 3 "" H 1250 1100 50  0001 C CNN
	1    1250 1100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1250 1200 1250 1100
Wire Wire Line
	1250 1600 1400 1600
$Comp
L power:+3.3V #PWR03
U 1 1 61EE7BAE
P 2000 1150
F 0 "#PWR03" H 2000 1000 50  0001 C CNN
F 1 "+3.3V" H 2015 1323 50  0000 C CNN
F 2 "" H 2000 1150 50  0001 C CNN
F 3 "" H 2000 1150 50  0001 C CNN
	1    2000 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR04
U 1 1 61EE8CB2
P 2000 4300
F 0 "#PWR04" H 2000 4050 50  0001 C CNN
F 1 "GNDREF" H 2005 4127 50  0000 C CNN
F 2 "" H 2000 4300 50  0001 C CNN
F 3 "" H 2000 4300 50  0001 C CNN
	1    2000 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4300 2000 4200
Wire Wire Line
	2000 1400 2000 1150
Text GLabel 2700 1900 2    50   Input ~ 0
RX
Text GLabel 2700 1700 2    50   Output ~ 0
TX
Wire Wire Line
	2700 1700 2600 1700
Wire Wire Line
	2700 1900 2600 1900
Wire Wire Line
	2700 2200 2600 2200
Text GLabel 2700 2200 2    50   Output ~ 0
RS
$Comp
L Connector:Conn_01x12_Male J3
U 1 1 61FCCE62
P 5250 1750
F 0 "J3" H 5222 1724 50  0000 R CNN
F 1 "Display LCD" H 5222 1633 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B12B-XH-A_1x12_P2.50mm_Vertical" H 5250 1750 50  0001 C CNN
F 3 "~" H 5250 1750 50  0001 C CNN
	1    5250 1750
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 6200EFC6
P 4500 1150
F 0 "#PWR012" H 4500 1000 50  0001 C CNN
F 1 "+5V" H 4515 1323 50  0000 C CNN
F 2 "" H 4500 1150 50  0001 C CNN
F 3 "" H 4500 1150 50  0001 C CNN
	1    4500 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 1450 5050 1450
Wire Wire Line
	4500 1750 4500 1650
Wire Wire Line
	4750 1650 4500 1650
Connection ~ 4500 1650
Wire Wire Line
	4500 1650 4500 1600
$Comp
L power:+5V #PWR014
U 1 1 620BA077
P 4650 2150
F 0 "#PWR014" H 4650 2000 50  0001 C CNN
F 1 "+5V" H 4665 2323 50  0000 C CNN
F 2 "" H 4650 2150 50  0001 C CNN
F 3 "" H 4650 2150 50  0001 C CNN
	1    4650 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 2150 4650 2250
Wire Wire Line
	4650 2250 5050 2250
Wire Wire Line
	4650 2350 5050 2350
Wire Wire Line
	4500 1150 4500 1250
Wire Wire Line
	4750 1250 5050 1250
Wire Wire Line
	4750 1250 4750 1650
Wire Wire Line
	5050 1350 4650 1350
Wire Wire Line
	4650 1350 4650 1250
Wire Wire Line
	4650 1250 4500 1250
Connection ~ 4500 1250
Wire Wire Line
	4500 1250 4500 1300
Wire Wire Line
	5050 1650 4750 1650
Connection ~ 4750 1650
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 6211338D
P 5200 3500
F 0 "J2" H 5172 3474 50  0000 R CNN
F 1 "Botões" H 5172 3383 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B4B-XH-A_1x04_P2.50mm_Vertical" H 5200 3500 50  0001 C CNN
F 3 "~" H 5200 3500 50  0001 C CNN
	1    5200 3500
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR016
U 1 1 62150507
P 4900 3800
F 0 "#PWR016" H 4900 3550 50  0001 C CNN
F 1 "GNDREF" H 4905 3627 50  0000 C CNN
F 2 "" H 4900 3800 50  0001 C CNN
F 3 "" H 4900 3800 50  0001 C CNN
	1    4900 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3800 4900 3700
Wire Wire Line
	4900 3700 5000 3700
Wire Notes Line
	5900 500  5900 4750
$Comp
L Regulator_Linear:AMS1117-3.3 U3
U 1 1 622397DF
P 4300 6950
F 0 "U3" H 4300 7192 50  0000 C CNN
F 1 "AMS1117-3.3" H 4300 7101 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4300 7150 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4400 6700 50  0001 C CNN
	1    4300 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 62246F3E
P 5200 7150
F 0 "C6" H 5318 7196 50  0000 L CNN
F 1 "100u" H 5318 7105 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 5238 7000 50  0001 C CNN
F 3 "~" H 5200 7150 50  0001 C CNN
	1    5200 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 62246F44
P 4800 7150
F 0 "C5" H 4915 7196 50  0000 L CNN
F 1 "10n" H 4915 7105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 4838 7000 50  0001 C CNN
F 3 "~" H 4800 7150 50  0001 C CNN
	1    4800 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 7000 4800 6950
Connection ~ 4800 6950
Wire Wire Line
	4800 6950 4600 6950
Wire Wire Line
	5200 7000 5200 6950
Connection ~ 5200 6950
Wire Wire Line
	5200 6950 4800 6950
Wire Wire Line
	3800 7350 4300 7350
Wire Wire Line
	4300 7250 4300 7350
Connection ~ 4300 7350
Wire Wire Line
	4300 7350 4800 7350
Wire Wire Line
	4800 7300 4800 7350
Connection ~ 4800 7350
Wire Wire Line
	4800 7350 5200 7350
Wire Wire Line
	5200 7300 5200 7350
Wire Notes Line
	500  6300 7800 6300
Wire Notes Line
	7800 450  7800 6450
Wire Notes Line
	4050 500  4050 6300
$Comp
L power:+3.3V #PWR021
U 1 1 6230D420
P 6900 900
F 0 "#PWR021" H 6900 750 50  0001 C CNN
F 1 "+3.3V" H 6915 1073 50  0000 C CNN
F 2 "" H 6900 900 50  0001 C CNN
F 3 "" H 6900 900 50  0001 C CNN
	1    6900 900 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6900 900  6900 1050
$Comp
L power:+3.3V #PWR019
U 1 1 623192C5
P 6850 3050
F 0 "#PWR019" H 6850 2900 50  0001 C CNN
F 1 "+3.3V" H 6865 3223 50  0000 C CNN
F 2 "" H 6850 3050 50  0001 C CNN
F 3 "" H 6850 3050 50  0001 C CNN
	1    6850 3050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6850 3050 6850 3200
Wire Wire Line
	3100 1600 2600 1600
Text GLabel 2700 1800 2    50   Input ~ 0
PSC_TMP
Wire Wire Line
	2700 1800 2600 1800
Text GLabel 2700 2500 2    50   Input ~ 0
CLT_TMP
Wire Wire Line
	2700 2500 2600 2500
Text GLabel 2700 2600 2    50   Output ~ 0
RLY_AQ
Text GLabel 2700 2700 2    50   Output ~ 0
RLY_FL
Wire Wire Line
	2700 2600 2600 2600
Wire Wire Line
	2700 2700 2600 2700
NoConn ~ 1400 2800
NoConn ~ 1400 2900
NoConn ~ 1400 3000
NoConn ~ 1400 3100
NoConn ~ 1400 3200
NoConn ~ 1400 3300
NoConn ~ 2600 2800
NoConn ~ 2600 2900
NoConn ~ 2600 2300
NoConn ~ 2600 2100
NoConn ~ 2600 2000
NoConn ~ 2600 3200
NoConn ~ 1400 1800
NoConn ~ 1400 1900
$Comp
L power:+3.3V #PWR0101
U 1 1 62478346
P 5200 6800
F 0 "#PWR0101" H 5200 6650 50  0001 C CNN
F 1 "+3.3V" H 5215 6973 50  0000 C CNN
F 2 "" H 5200 6800 50  0001 C CNN
F 3 "" H 5200 6800 50  0001 C CNN
	1    5200 6800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5200 6800 5200 6950
$EndSCHEMATC
