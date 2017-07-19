#include <WiFiUdp.h>
#include <AppleMidi.h>
#include "WiFiMIDIBridge.h"


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
  RouteMidiNoteOn(FROM_WIFI, channel,  note,  velocity);
}
void OnAppleMidiNoteOff(byte channel, byte note, byte velocity) {
  RouteMidiNoteOff(FROM_WIFI,  channel,  note,  velocity);
}
void OnAppleMidiAfterTouchPoly(byte channel, byte note, byte pressure) {
  RouteMidiAfterTouchPoly(FROM_WIFI,  channel,  note,  pressure);
}
void OnAppleMidiControlChange(byte channel, byte number, byte value) {
RouteMidiControlChange(FROM_WIFI,  channel,  number,  value);
}
void OnAppleMidiProgramChange(byte channel, byte number) {
RouteMidiProgramChange(FROM_WIFI,  channel,  number);
}
void OnAppleMidiAfterTouchChannel(byte channel, byte pressure) {
RouteMidiAfterTouchChannel(FROM_WIFI,  channel,  pressure);
}

void OnAppleMidiPitchBend(byte channel, int bend) { RouteMidiPitchBend(FROM_WIFI,  channel,  bend); }
void OnAppleMidiSystemExclusive(byte * array, byte size) {RouteMidiSystemExclusive(FROM_WIFI, array,  size); }
void OnAppleMidiTimeCodeQuarterFrame(byte data) { RouteMidiTimeCodeQuarterFrame(FROM_WIFI,  data); }
void OnAppleMidiSongPosition(unsigned int beats) { RouteMidiSongPosition(FROM_WIFI,  beats); }
void OnAppleMidiSongSelect(byte songnumber) { RouteMidiSongSelect(FROM_WIFI,  songnumber); }
void OnAppleMidiTuneRequest(void) { RouteMidiTuneRequest(FROM_WIFI); }

void OnAppleMidiClock(void) { RouteMidiClock(FROM_WIFI); }
void OnAppleMidiStart(void) { RouteMidiStart(FROM_WIFI); }
void OnAppleMidiContinue(void) { RouteMidiContinue(FROM_WIFI); }
void OnAppleMidiStop(void) { RouteMidiStop(FROM_WIFI); }
void OnAppleMidiActiveSensing(void) {RouteMidiActiveSensing(FROM_WIFI);}
void OnAppleMidiSystemReset(void) {RouteMidiSystemReset(FROM_WIFI);}


void setup_AppleMIDI() {

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

