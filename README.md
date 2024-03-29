# NMEA0183 WiFi Multiplexer with ESP8266 (D1 Mini)

# Caution! 
# ----------------------------
This is an updated version (0.2) with pins changed from D7/D8 to D6/D7 to avoid boot problems (see Issues).
If you ordered already a version 1.0 PCB, then just cut the connection to D8 (e.g. with a knife) and solder a wire to D6 pin on D1 Mini. The updated software (version 0.2) will work then. But with changed serial line numbers from #1 to #2 and vice versa.
# ----------------------------

The project reads NMEA0183 messages from two serial (RS232) inputs and forwards multiplexed messages to USB-Serial and WLAN as UDP broadcast.

The multiplexer is powered either from USB connection or with 12 Volt via DC-DC converter.
ESP8266 is using Software Serial on ports D6 and D7.

Main purpose is to provide GPS and AIS information wirelessly to a tablet/smartphone for navigation.
Works with Navionics app (configure UDP connection with Host: x.y.z.255 and Port: 4444).

There is also a [software version](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/tree/main/NMEA083-Parser-WiFi-Multiplexer) that is parsing the messages and can suppress certain messages. This version needs this additional NMEA0183 libray: https://github.com/ttlappalainen/NMEA0183

![Schematics](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/NMEA0183-WiFi-Multiplexer.png)

Just change the settings in the [programm](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/NMEA083-WiFi-Multiplexer/NMEA083-WiFi-Multiplexer.ino) according to your needs:

```
// Change these values only
// ------------------------------------------------------------------------
#define AP 0             // Set to 1 to act as Access Point, 0 as client 

const char *ssid      = "ssid";           // Set WLAN name
const char *password  = "password";      // Set password

const char *udpAddress = "192.168.4.255"; // Set network address for broadcast
const int udpPort = 4444;                 // UDP port

#define BaudRate1 4800   // Baud rate for serial#1
#define BaudRate2 38400  // Baud rate for serial#2

// -------------------------------------------------------------------------

```

KiCad files are available to change/extend and to create a [PCB](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/KiCadNMEA0183-WiFi-Multiplexer/PCB.pdf).

![Board](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/KiCadNMEA0183-WiFi-Multiplexer/NMEA0183-WiFi-Multiplexer.png)


## Parts

- U1: [ESP8266 (D1Mini)](https://www.reichelt.de/de/en/d1-mini-esp8266-v3-0-d1-mini-p253978.html?&nbc=1)
- U2: [Max232](https://www.reichelt.de/de/en/rs232-driver-dil-16-max-232-cpe-p11216.html?&nbc=1)
- C1-C4: 4* [Capacitor 1µF](https://www.reichelt.de/de/en/tantalum-capacitor-rm-2-5-1-0-f-35-v-tantal-1-0-35-p20330.html?&nbc=1)
- J1-J3: 3* [Connector](https://www.reichelt.de/de/en/2-pin-terminal-strip-spacing-5-08-akl-101-02-p36605.html?&nbc=1)
- U3: [DC-DC Converter](https://www.reichelt.de/de/en/dc-dc-converter-5-v-1-a-single-r-78e50-10-p177268.html?&nbc=1)
- [Board](https://aisler.net/p/EZUNBBJG) @Aisler.net

## Updates
- 10.11.2022 - Version 0.3: Corrected line end handling to avaid duplication of messages sent (see Issues).
- 01.10.2021 - Version 0.2: Changed pins from D/D8 to D6/D7 to avoid boot problems (see Issues).
- 06.03.2021 - Version 0.1: Initial version
