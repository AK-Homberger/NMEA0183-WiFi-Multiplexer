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
// NMEA0183 WiFi Multiplexer with NME0183 Message Parser to suppress certain messges

// Reads NMEA0183 messages from serial connected to D6 and D7.
// Forwards multiplexed messages to USB-Serial and WLAN as UDP broadcast.
// Needs this NMEA0183 libray: https://github.com/ttlappalainen/NMEA0183

// Version 0.1, 10.11.2022, AK-Homberger

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SoftwareSerial.h>
#include <NMEA0183.h> 

// Change these values only
// ------------------------------------------------------------------------
#define AP 0             // Set to 1 to act as Access Point, 0 as client 

const char *ssid      = "ssid";           // Set WLAN name
const char *password  = "password";       // Set password

const char *udpAddress = "192.168.4.255"; // Set network address for broadcast
const int udpPort = 4444;                 // UDP port

#define BaudRate1 4800   // Baud rate for serial#1
#define BaudRate2 38400  // Baud rate for serial#2

// -------------------------------------------------------------------------


#define MAX_NMEA0183_MESSAGE_SIZE 150
char buf[MAX_NMEA0183_MESSAGE_SIZE] = "";  // Buffer for message to send

// Create software serial objects
SoftwareSerial swSer1;
SoftwareSerial swSer2;

// NMEA streams for NMEA0183 receiving
tNMEA0183 NMEA0183_1;
tNMEA0183 NMEA0183_2;

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
  swSer1.begin(BaudRate1, SWSERIAL_8N1, D6, D6, false, 256);
  swSer1.enableIntTx(false);
  NMEA0183_1.SetMessageStream(&swSer1, 1);
  NMEA0183_1.Open();

  swSer2.begin(BaudRate2, SWSERIAL_8N1, D7, D7, false, 256);
  swSer2.enableIntTx(false);
  NMEA0183_2.SetMessageStream(&swSer2, 2);
  NMEA0183_2.Open();
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
void SendNMEA0183Message(char *buf) {

  udp.beginPacket(udpAddress, udpPort);   // Send to UDP
  udp.println(buf);
  udp.endPacket();

  Serial.println(buf);    // Send to USB-Serial
}


//*****************************************************************************
void loop(void) {
  tNMEA0183Msg NMEA0183Msg;  // Create message container

  Check_WiFi();

  // Receive and check message codes to suppress
  if (NMEA0183_1.GetMessage(NMEA0183Msg)) {    // Get NMEA sentences from serial#1
    
    if (!((strcmp(NMEA0183Msg.Sender(), "GP") == 0) && NMEA0183Msg.IsMessageCode("GSV") ||
          (strcmp(NMEA0183Msg.Sender(), "GL") == 0) && NMEA0183Msg.IsMessageCode("GSV"))) { 

      if (NMEA0183Msg.GetMessage(buf, MAX_NMEA0183_MESSAGE_SIZE - 1)) {
        strcat(buf, "\n");
        SendNMEA0183Message(buf);    // Send to clients
      }
    }
  }

  // Receive and send without modification
  if (NMEA0183_2.GetMessage(NMEA0183Msg)) {    // Get NMEA sentences from serial#2
    if (NMEA0183Msg.GetMessage(buf, MAX_NMEA0183_MESSAGE_SIZE - 1)) {
      strcat(buf, "\n");
      SendNMEA0183Message(buf);    // Send to clients
    }
  }
}
