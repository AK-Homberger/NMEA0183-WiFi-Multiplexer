# NMEA0183 WiFi Multiplexer with ESP8266 (D1 Mini)
Reads NMEA0183 messages from two serial lines and forwards multiplexed messages to USB-Serial and WLAN as UDP broadcast.

ESP8266 is using Software Serial on ports D7 and D8.

![Schematics](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/NMEA0183-WiFi-Multiplexer.png)

Just change the settings in the [programm](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/NMEA083-WiFi-Multiplexer/NMEA083-WiFi-Multiplexer.ino) according to your needs:

```
// ------------------------------------------------------------------------
#define AP 0             // Set to 1 to act as Access Point, 0 as client 

const char *ssid      = "ssid";           // Set WLAN name
const char *password  = "password";      // Set password

const char *udpAddress = "192.168.4.255"; // Set network address for broadcast
const int udpPort = 4444;                 // UDP port

#define BaudRate1 4800   // Baud rate for serial#1
#define BaudRate2 38400  // Baud rate for serial#1

// -------------------------------------------------------------------------

```

If you only need one serial line ignore the parts for line two. If you need mor ports add lines and extend the code accordingly.

## Updates
- 06.03.2021 - Version 0.1: Initial version
