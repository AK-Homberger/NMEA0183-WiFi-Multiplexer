# NMEA0183-WiFi-Multiplexer
Reads NMEA0183 messages from two serial lines and forwards multiplexed messages to USB-Serial and WLAN as UDP broadcast.

![Schematics](https://github.com/AK-Homberger/NMEA0183-WiFi-Multiplexer/blob/main/NMEA0183-WiFi-Multiplexer.png)

Just change the settings in the programm according to your needs:

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

## Updates
- 06.03.2021 - Version 0.1: Initial version
