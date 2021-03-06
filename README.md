# NMEA0183 WiFi Multiplexer with ESP8266 (D1 Mini)
Reads NMEA0183 messages from two serial (RS232) inputs and forwards multiplexed messages to USB-Serial and WLAN as UDP broadcast.

The mupltiplexer is powered from USB connection.
ESP8266 is using Software Serial on ports D7 and D8.

Works also with Navionics devices on tablets (configure UDP connection with Host: x.y.z.255 and Port: 4444).

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

KiCad files are available to change/extend and to create a PCB.

## Parts

- [ESP8266 (D1Mini)](https://www.reichelt.de/de/en/d1-mini-esp8266-v3-0-d1-mini-p253978.html?&nbc=1)
- [Max232](https://www.reichelt.de/de/en/rs232-driver-dil-16-max-232-cpe-p11216.html?&nbc=1)
- 4* [Capacitor 1µF](https://www.reichelt.de/de/en/tantalum-capacitor-rm-2-5-1-0-f-35-v-tantal-1-0-35-p20330.html?&nbc=1)
- 2* [Connector](https://www.reichelt.de/de/en/2-pin-terminal-strip-spacing-5-08-akl-101-02-p36605.html?&nbc=1)

## Updates
- 06.03.2021 - Version 0.1: Initial version
