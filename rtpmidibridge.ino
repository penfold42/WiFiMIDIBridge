// These need to be included when using standard Ethernet
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <AppleMidi.h>
#include <MIDI.h>
#include <SPI.h>
#include "rtpmidibridge.h"

#define DBG_PORT Serial

#include <RemoteDebug.h>
RemoteDebug Debug;

MIDI_CREATE_DEFAULT_INSTANCE();

#include "c:/creds.h"
char ssid[] = MY_SSID; //  your network SSID (name)
char pass[] = MY_PASS;    // your network password (use for WPA, or use as key for WEP)

unsigned long t0 = millis();
bool isConnected = false;

APPLEMIDI_CREATE_INSTANCE(WiFiUDP, AppleMIDI); // see definition in AppleMidi_Defs.h


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void setup()
{

#if DBG_PORT == Serial
    // Serial communications and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
#endif

    setup_vs1053();

    setup_wifi_config();
//    old_wifi();

    setup_SerialMIDI();
// Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
 
    // Create a session and wait for a remote host to connect to us
    AppleMIDI.begin(WiFi.hostname().c_str());
    setup_AppleMIDI();

}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();

    // Listen to incoming notes
    AppleMIDI.run();

    #if DBG_PORT == Debug
    // Remote debug over telnet
    Debug.handle();
    #endif
}

uint8_t HOTRS_notes[] = {50,65,69,74,69,65,53,69,72,77,72,69,55,71,74,79,74,71,58,70,74,77,74,70};

void old_wifi()
{
    DBG_PORT.print("Getting IP address...");

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
//    DBG_PORT.print(".");
    }

    DBG_PORT.println("");
    DBG_PORT.println("WiFi connected");

    DBG_PORT.println();
    DBG_PORT.print("IP address is ");
    DBG_PORT.println(WiFi.localIP());

    DBG_PORT.print("hostname is ");
    DBG_PORT.println(WiFi.hostname());

    DBG_PORT.println(F("OK, now make sure you an rtpMIDI session that is Enabled"));
    DBG_PORT.print(F("Add device named Arduino with Host/Port "));
    DBG_PORT.print(WiFi.localIP());
    DBG_PORT.println(":5004");
    DBG_PORT.println("Then press the Connect button");
    DBG_PORT.println("Then open a MIDI listener (eg MIDI-OX) and monitor incoming notes");
}

