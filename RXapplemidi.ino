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

