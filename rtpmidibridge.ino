// These need to be included when using standard Ethernet
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <AppleMidi.h>
#include <MIDI.h>
#include <SPI.h>

#define DBG_PORT Debug

#define USE_SPI_VS1053
#define VS1053_RESET 15
#define VS1053_MOSI 13
#define VS1053_MISO 12
#define VS1053_SCK 14
#define VS1053_XDCS 5    // 16 doesnt work very well

#include <RemoteDebug.h>
RemoteDebug Debug;

MIDI_CREATE_DEFAULT_INSTANCE();

#include "c:/creds.h"
char ssid[] = MY_SSID; //  your network SSID (name)
char pass[] = MY_PASS;    // your network password (use for WPA, or use as key for WEP)

unsigned long t0 = millis();
bool isConnected = false;

APPLEMIDI_CREATE_INSTANCE(WiFiUDP, AppleMIDI); // see definition in AppleMidi_Defs.h

void dinHandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (isConnected) AppleMIDI.noteOn(pitch, velocity, channel);    
}
void dinHandleNoteOff(byte channel, byte pitch, byte velocity) {
  if (isConnected) AppleMIDI.noteOff(pitch, velocity, channel);
}

void dinHandleAfterTouchPoly (byte channel, byte note, byte pressure) {
  if (isConnected) AppleMIDI.polyPressure(note, pressure, channel);
}

void dinHandleControlChange (byte channel, byte number, byte value) {
  if (isConnected) AppleMIDI.controlChange(number, value, channel);
}
void dinHandleProgramChange (byte channel, byte number) {
  if (isConnected) AppleMIDI.programChange( number, channel);
}
void dinHandleAfterTouchChannel (byte channel, byte pressure) {
  if (isConnected) AppleMIDI.afterTouch(pressure, channel);
}
void dinHandlePitchBend (byte channel, int bend) {
  if (isConnected) AppleMIDI.pitchBend(bend, channel);
}
void dinHandleSystemExclusive (byte* array, unsigned size) {
  if (isConnected) AppleMIDI.sysEx(size, array, true); // check this
}
void dinHandleTimeCodeQuarterFrame (byte data) {
  if (isConnected) AppleMIDI.timeCodeQuarterFrame(data);
}
void dinHandleSongPosition (unsigned beats) {
  if (isConnected) AppleMIDI.songPosition(beats);
}
void dinHandleSongSelect (byte songnumber) {
  if (isConnected) AppleMIDI.songSelect(songnumber);
}
void dinHandleTuneRequest (void) {
  if (isConnected) AppleMIDI.tuneRequest();
}
void dinHandleClock (void) {
  if (isConnected) AppleMIDI.clock();
}
void dinHandleStart (void) {
  if (isConnected) AppleMIDI.start();
}
void dinHandleContinue (void) {
  if (isConnected) AppleMIDI._continue();
}
void dinHandleStop (void) {
  if (isConnected) AppleMIDI.stop();
}
void dinHandleActiveSensing (void) {
  if (isConnected) AppleMIDI.activeSensing();
}
void dinHandleSystemReset (void) {
  if (isConnected) AppleMIDI.systemReset();
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void setup()
{


#ifdef USE_SPI_VS1053
  SPI.begin();
  pinMode(VS1053_XDCS,OUTPUT);
  digitalWrite(VS1053_XDCS,HIGH);

  pinMode(VS1053_RESET,OUTPUT);
  digitalWrite(VS1053_RESET,LOW);
  delay(10);
  digitalWrite(VS1053_RESET,HIGH);

#endif


#if DBG_PORT == Serial
    // Serial communications and wait for port to open:
    Serial.begin(31250);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
#endif
  
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

    setup_SerialMIDI();
    setup_AppleMIDI();

}

void setup_SerialMIDI() {
    MIDI.setHandleNoteOn(dinHandleNoteOn);  // Put only the name of the function
    MIDI.setHandleNoteOff(dinHandleNoteOff);
    MIDI.setHandleAfterTouchPoly(dinHandleAfterTouchPoly);
    MIDI.setHandleControlChange(dinHandleControlChange);
    MIDI.setHandleProgramChange(dinHandleProgramChange);
    MIDI.setHandleAfterTouchChannel(dinHandleAfterTouchChannel);
    MIDI.setHandlePitchBend(dinHandlePitchBend);
    MIDI.setHandleSystemExclusive(dinHandleSystemExclusive);
    MIDI.setHandleTimeCodeQuarterFrame(dinHandleTimeCodeQuarterFrame);
    MIDI.setHandleSongPosition(dinHandleSongPosition);
    MIDI.setHandleSongSelect(dinHandleSongSelect);
    MIDI.setHandleTuneRequest(dinHandleTuneRequest);
    MIDI.setHandleClock(dinHandleClock);
    MIDI.setHandleStart(dinHandleStart);
    MIDI.setHandleContinue(dinHandleContinue);
    MIDI.setHandleStop(dinHandleStop);
    MIDI.setHandleActiveSensing(dinHandleActiveSensing);
    MIDI.setHandleSystemReset(dinHandleSystemReset);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);

    MIDI.turnThruOff();
}

void setup_AppleMIDI() {

  // Create a session and wait for a remote host to connect to us
  AppleMIDI.begin(WiFi.hostname().c_str());

  AppleMIDI.OnConnected(OnAppleMidiConnected);
  AppleMIDI.OnDisconnected(OnAppleMidiDisconnected);

  AppleMIDI.OnReceiveNoteOn(OnAppleMidiNoteOn);
  AppleMIDI.OnReceiveNoteOff(OnAppleMidiNoteOff);
  AppleMIDI.OnReceiveAfterTouchPoly(OnAppleMidiAfterTouchPoly);
  AppleMIDI.OnReceiveControlChange(OnAppleMidiControlChange);
  AppleMIDI.OnReceiveProgramChange(OnAppleMidiProgramChange);
  AppleMIDI.OnReceiveAfterTouchChannel(OnAppleMidiAfterTouchChannel);
  AppleMIDI.OnReceivePitchBend(OnAppleMidiPitchBend);
  AppleMIDI.OnReceiveSystemExclusive(OnAppleMidiSystemExclusive);
  AppleMIDI.OnReceiveTimeCodeQuarterFrame(OnAppleMidiTimeCodeQuarterFrame);
  AppleMIDI.OnReceiveSongPosition(OnAppleMidiSongPosition);
  AppleMIDI.OnReceiveSongSelect(OnAppleMidiSongSelect);
  AppleMIDI.OnReceiveTuneRequest(OnAppleMidiTuneRequest);
  AppleMIDI.OnReceiveClock(OnAppleMidiClock);
  AppleMIDI.OnReceiveStart(OnAppleMidiStart);
  AppleMIDI.OnReceiveContinue(OnAppleMidiContinue);
  AppleMIDI.OnReceiveStop(OnAppleMidiStop);
  AppleMIDI.OnReceiveActiveSensing(OnAppleMidiActiveSensing);
  AppleMIDI.OnReceiveSystemReset(OnAppleMidiSystemReset);

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

//    #if DBG_PORT == Debug
    // Remote debug over telnet
    Debug.handle();
//    #endif
}


// ====================================================================================
// Event handlers for incoming MIDI messages
// ====================================================================================

// -----------------------------------------------------------------------------
// rtpMIDI session. Device connected
// -----------------------------------------------------------------------------
void OnAppleMidiConnected(uint32_t ssrc, char* name) {
  isConnected  = true;

  DBG_PORT.print("Connected to session ");
  DBG_PORT.println(name);

}

// -----------------------------------------------------------------------------
// rtpMIDI session. Device disconnected
// -----------------------------------------------------------------------------
void OnAppleMidiDisconnected(uint32_t ssrc) {
  isConnected  = false;
  DBG_PORT.println("Disconnected");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

//  SPI3(int cmd, int pitch, int velocity)

void OnAppleMidiNoteOn(byte channel, byte note, byte velocity) {
  MIDI.sendNoteOn(note,velocity,channel); 
  SPI3(0x90+channel, note, velocity);
}
void OnAppleMidiNoteOff(byte channel, byte note, byte velocity) {
  MIDI.sendNoteOff(note,velocity,channel);
  SPI3(0x80+channel, note, velocity);
}
void OnAppleMidiAfterTouchPoly(byte channel, byte note, byte pressure) {
  MIDI.sendAfterTouch(note, pressure, channel);
  SPI3(0xA0+channel, note, pressure);
}
void OnAppleMidiControlChange(byte channel, byte number, byte value) {
  MIDI.sendControlChange(number, value, channel); 
  SPI3(0xB0+channel, number, value);
}
void OnAppleMidiProgramChange(byte channel, byte number) {
  MIDI.sendProgramChange(number, channel);
  SPI2(0xC0+channel, number);
}
void OnAppleMidiAfterTouchChannel(byte channel, byte pressure) {
  MIDI.sendAfterTouch(pressure, channel);
  SPI2(0xD0+channel, pressure);
}
void OnAppleMidiPitchBend(byte channel, int bend) { MIDI.sendPitchBend(bend, channel); }
void OnAppleMidiSystemExclusive(byte * array, byte size) { MIDI.sendSysEx(size, array, false); }
void OnAppleMidiTimeCodeQuarterFrame(byte data) { MIDI.sendTimeCodeQuarterFrame(data); }
void OnAppleMidiSongPosition(unsigned int beats) { MIDI.sendSongPosition(beats); }
void OnAppleMidiSongSelect(byte songnumber) { MIDI.sendSongSelect(songnumber); }
void OnAppleMidiTuneRequest(void) { MIDI.sendTuneRequest(); }

void OnAppleMidiClock(void) { MIDI.sendRealTime(midi::Clock); }
void OnAppleMidiStart(void) { MIDI.sendRealTime(midi::Start); }
void OnAppleMidiContinue(void) { MIDI.sendRealTime(midi::Continue); }
void OnAppleMidiStop(void) { MIDI.sendRealTime(midi::Stop); }
void OnAppleMidiActiveSensing(void) {}
void OnAppleMidiSystemReset(void) {}



uint8_t HOTRS_notes[] = {50,65,69,74,69,65,53,69,72,77,72,69,55,71,74,79,74,71,58,70,74,77,74,70};

void SPI3(int cmd, int one, int two) {
#ifdef USE_SPI_VS1053
  digitalWrite(VS1053_XDCS,LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer16(cmd);
  SPI.transfer16(one);
  SPI.transfer16(two);
  SPI.endTransaction();
  digitalWrite(VS1053_XDCS,HIGH);
#endif
}

void SPI2(int cmd, int one) {
#ifdef USE_SPI_VS1053
  digitalWrite(VS1053_XDCS,LOW);
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer16(cmd);
  SPI.transfer16(one);
  SPI.endTransaction();
  digitalWrite(VS1053_XDCS,HIGH);
#endif
}

