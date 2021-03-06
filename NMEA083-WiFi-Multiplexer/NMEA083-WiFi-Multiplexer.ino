/*
  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
// NMEA0183 WiFi Multiplexer
// Reads NMEA0183 messages from serial connected to D7 and D8.
// Forwards multiplexed messages to USB-Serial and WLAN as UDP broadcast.

// Version 0.1, 06.03.2021, AK-Homberger

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>


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


#define MAX_NMEA0183_MESSAGE_SIZE 150
char buf1[MAX_NMEA0183_MESSAGE_SIZE] = "";  // Buffer for serial#1
char buf2[MAX_NMEA0183_MESSAGE_SIZE] = "";  // Buffer for serial#2

// Create software serial objects
SoftwareSerial swSer1;
SoftwareSerial swSer2;

boolean wifiConnected = false;

// Create UDP instance
WiFiUDP udp;


//*****************************************************************************
void setup(void) {

  Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();            // Connect to WLAN or start AP

  if (!wifiConnected) {
    Serial.println("Cannot connect to WiFi. Please check data. Reset the ESP now.");
    delay(3000);
    ESP.restart();
  }

  // Initialise software serial set baud rate to 4800 or 38400
  swSer1.begin(BaudRate1, SWSERIAL_8N1, D7, D7, false, 256);
  swSer1.enableIntTx(false);

  swSer2.begin(BaudRate2, SWSERIAL_8N1, D8, D8, false, 256);
  swSer2.enableIntTx(false);
}


//*****************************************************************************
// Connect to wifi or start AP – returns true if successful or false if not

boolean connectWifi() {
  boolean state = true;
  int i = 0;

  if (AP == 0) {
    WiFi.mode(WIFI_STA);
    WiFi.hostname("NMEA0183Multiplexer");
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi");
    // Wait for connection
    Serial.print("Connecting...");
    // Initialise wifi connection

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      if (i > 10) {
        state = false; break;
      }
      i++;
    }
    Serial.println("");
    if (state) {
      Serial.print("Connected to ");
      Serial.println(ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }
    else {
      Serial.println("Connection failed.");
    }
    return state;
  }  else {

    Serial.println("Start WLAN AP");         // WiFi Mode AP
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    delay(100);
    IPAddress IP = WiFi.softAPIP();
    Serial.println("");
    Serial.print("AP IP address: ");
    Serial.println(IP);
    return true;
  }
}


//*****************************************************************************
// Check WiFi connection

void Check_WiFi(void) {
  boolean wifiConnected = false;

  if (AP != 0) return;   // We are acting as AP. Connection check not necessary

  if (WiFi.status() != WL_CONNECTED) { // Wifi restart
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_STA);

    Serial.println("Reconnect!");
    wifiConnected = connectWifi();

    if (!wifiConnected) {
      Serial.println("Cannot connect to WiFi. Please check data. Reset the ESP now.");
      delay(2500);
      ESP.restart();
    }
  }
}


//*****************************************************************************
bool GetNMEA0183Message1() {
  static unsigned int ReceivedChars = 0;
  unsigned char Char = 0;

  while (swSer1.available()) {
    Char = swSer1.read();

    if ( (Char == '\n') || (Char == '\r') ) {
      ReceivedChars = 0;
      return true;
    }

    buf1[ReceivedChars] = Char;
    buf1[ReceivedChars + 1] = 0;
    ReceivedChars++;
    if (ReceivedChars >= MAX_NMEA0183_MESSAGE_SIZE - 2) {
      ReceivedChars = 0;
      buf1[0] = 0;
      return false;
    }
  }
  return false;
}

//*****************************************************************************
bool GetNMEA0183Message2() {
  static unsigned int ReceivedChars = 0;
  unsigned char Char = 0;

  while (swSer2.available()) {
    Char = swSer2.read();

    if ( (Char == '\n') || (Char == '\r') ) {
      ReceivedChars = 0;
      return true;
    }

    buf2[ReceivedChars] = Char;
    buf2[ReceivedChars + 1] = 0;
    ReceivedChars++;
    if (ReceivedChars >= MAX_NMEA0183_MESSAGE_SIZE - 2) {
      ReceivedChars = 0;
      buf2[0] = 0;
      return false;
    }
  }
  return false;
}


//*****************************************************************************
void SendNMEA0183Message(char *buf) {

  udp.beginPacket(udpAddress, udpPort);   // Send to UDP
  udp.println(buf);
  udp.endPacket();

  Serial.println(buf);    // Send to USB-Serial
}


//*****************************************************************************
void loop(void) {

  Check_WiFi();

  if (GetNMEA0183Message1() == true) {    // Get NMEA sentences from serial#1
    SendNMEA0183Message(buf1);    // Send to clients
  }

  if (GetNMEA0183Message2() == true) {    // Get NMEA sentences from serial#2
    SendNMEA0183Message(buf2);    // Send to clients
  }
}
