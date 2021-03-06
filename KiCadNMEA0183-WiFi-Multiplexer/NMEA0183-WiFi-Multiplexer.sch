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
L MCU_Module:WeMos_D1_mini U1
U 1 1 604342F8
P 6100 3950
F 0 "U1" H 6100 4900 50  0000 C CNN
F 1 "WeMos_D1_mini" H 6100 5000 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 6100 2800 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 4250 2800 50  0001 C CNN
	1    6100 3950
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 6043679E
P 4850 4550
F 0 "Q1" H 5041 4596 50  0000 L CNN
F 1 "BC547" H 5041 4505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5050 4475 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4850 4550 50  0001 L CNN
	1    4850 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60437DBF
P 4300 4550
F 0 "R1" V 4093 4550 50  0000 C CNN
F 1 "33K" V 4184 4550 50  0000 C CNN
F 2 "" V 4230 4550 50  0001 C CNN
F 3 "~" H 4300 4550 50  0001 C CNN
	1    4300 4550
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 60439978
P 3800 4650
F 0 "J1" H 3718 4325 50  0000 C CNN
F 1 "NMEA In" H 3718 4416 50  0000 C CNN
F 2 "" H 3800 4650 50  0001 C CNN
F 3 "~" H 3800 4650 50  0001 C CNN
	1    3800 4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 4550 4150 4550
Wire Wire Line
	4950 4350 5700 4350
Wire Wire Line
	4450 4550 4550 4550
Wire Wire Line
	4550 4650 4550 4550
Connection ~ 4550 4550
Wire Wire Line
	4550 4550 4650 4550
$Comp
L power:GND #PWR01
U 1 1 6043BBF4
P 6100 4950
F 0 "#PWR01" H 6100 4700 50  0001 C CNN
F 1 "GND" H 6105 4777 50  0000 C CNN
F 2 "" H 6100 4950 50  0001 C CNN
F 3 "" H 6100 4950 50  0001 C CNN
	1    6100 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4750 6100 4950
$Comp
L Device:R R4
U 1 1 6044381A
P 4950 4200
F 0 "R4" H 5020 4246 50  0000 L CNN
F 1 "10K" H 5020 4155 50  0000 L CNN
F 2 "" V 4880 4200 50  0001 C CNN
F 3 "~" H 4950 4200 50  0001 C CNN
	1    4950 4200
	1    0    0    -1  
$EndComp
Connection ~ 4950 4350
Connection ~ 6100 4950
$Comp
L Transistor_BJT:BC547 Q2
U 1 1 6043EAEA
P 4850 3450
F 0 "Q2" H 5041 3496 50  0000 L CNN
F 1 "BC547" H 5041 3405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 5050 3375 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4850 3450 50  0001 L CNN
	1    4850 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6043EAF4
P 4300 3450
F 0 "R2" V 4093 3450 50  0000 C CNN
F 1 "33K" V 4184 3450 50  0000 C CNN
F 2 "" V 4230 3450 50  0001 C CNN
F 3 "~" H 4300 3450 50  0001 C CNN
	1    4300 3450
	0    1    1    0   
$EndComp
$Comp
L Diode:1N4148 D1
U 1 1 6043EAFE
P 4550 3700
F 0 "D1" V 4504 3779 50  0000 L CNN
F 1 "1N4148" V 4595 3779 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4550 3525 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4550 3700 50  0001 C CNN
	1    4550 3700
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 6043EB08
P 3800 3550
F 0 "J2" H 3718 3225 50  0000 C CNN
F 1 "NMEA In" H 3718 3316 50  0000 C CNN
F 2 "" H 3800 3550 50  0001 C CNN
F 3 "~" H 3800 3550 50  0001 C CNN
	1    3800 3550
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 3450 4150 3450
Wire Wire Line
	4000 3550 4000 3850
Wire Wire Line
	4000 3850 4550 3850
Wire Wire Line
	4950 3650 4950 3850
Connection ~ 4550 3850
Wire Wire Line
	4450 3450 4550 3450
Wire Wire Line
	4550 3850 4950 3850
Wire Wire Line
	4550 3550 4550 3450
Connection ~ 4550 3450
Wire Wire Line
	4550 3450 4650 3450
Wire Wire Line
	4950 4950 6100 4950
Wire Wire Line
	4550 4950 4950 4950
Connection ~ 4550 4950
Connection ~ 4950 4950
Wire Wire Line
	4950 4750 4950 4950
Wire Wire Line
	4000 4950 4550 4950
Wire Wire Line
	4000 4650 4000 4950
$Comp
L Diode:1N4148 D2
U 1 1 60438826
P 4550 4800
F 0 "D2" V 4504 4879 50  0000 L CNN
F 1 "1N4148" V 4595 4879 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 4550 4625 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 4550 4800 50  0001 C CNN
	1    4550 4800
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 6044AD30
P 4950 3100
F 0 "R3" H 5020 3146 50  0000 L CNN
F 1 "10K" H 5020 3055 50  0000 L CNN
F 2 "" V 4880 3100 50  0001 C CNN
F 3 "~" H 4950 3100 50  0001 C CNN
	1    4950 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2950 5450 2950
Wire Wire Line
	5450 2950 5450 3150
Wire Wire Line
	5450 3150 6000 3150
Wire Wire Line
	4950 4050 5450 4050
Wire Wire Line
	5450 4050 5450 3150
Connection ~ 5450 3150
Wire Wire Line
	4950 3250 5250 3250
Wire Wire Line
	5250 3250 5250 4250
Wire Wire Line
	5250 4250 5700 4250
Connection ~ 4950 3250
$EndSCHEMATC
