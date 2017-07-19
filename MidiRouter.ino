#include "ESPixelStick.h"

void RouteMidiNoteOn(int note_from, byte channel, byte note, byte velocity) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.noteOn(note, velocity, channel);    
  if (note_from==FROM_WIFI)  MIDI.sendNoteOn(note,velocity,channel); 
  SPI3(0x90+channel, note, velocity);
}

void RouteMidiNoteOff(int note_from, byte channel, byte note, byte velocity) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.noteOff(note, velocity, channel);
  if (note_from==FROM_WIFI)  MIDI.sendNoteOff(note,velocity,channel);
  SPI3(0x80+channel, note, velocity);
}

void RouteMidiAfterTouchPoly(int note_from, byte channel, byte note, byte pressure) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.polyPressure(note, pressure, channel);
  if (note_from==FROM_WIFI)  MIDI.sendAfterTouch(note, pressure, channel);
  SPI3(0xA0+channel, note, pressure);
}

void RouteMidiControlChange(int note_from, byte channel, byte number, byte value) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.controlChange(number, value, channel);
  if (note_from==FROM_WIFI)  MIDI.sendControlChange(number, value, channel); 
  SPI3(0xB0+channel, number, value);
}

void RouteMidiProgramChange(int note_from, byte channel, byte number) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.programChange( number, channel);
  if (note_from==FROM_WIFI)  MIDI.sendProgramChange(number, channel);
  SPI2(0xC0+channel, number);
}

void RouteMidiAfterTouchChannel(int note_from, byte channel, byte pressure) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.afterTouch(pressure, channel);
  if (note_from==FROM_WIFI)  MIDI.sendAfterTouch(pressure, channel);
  SPI2(0xD0+channel, pressure);
}

void RouteMidiPitchBend(int note_from, byte channel, int bend) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.pitchBend(bend, channel);
  if (note_from==FROM_WIFI)  MIDI.sendPitchBend(bend, channel);
}

void RouteMidiSystemExclusive(int note_from, byte * array, byte size) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.sysEx(size, array, true); // check this
  if (note_from==FROM_WIFI)  MIDI.sendSysEx(size, array, false);
}

void RouteMidiTimeCodeQuarterFrame(int note_from, byte data) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.timeCodeQuarterFrame(data);
  if (note_from==FROM_WIFI)  MIDI.sendTimeCodeQuarterFrame(data);
}

void RouteMidiSongPosition(int note_from, unsigned int beats) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.songPosition(beats);
  if (note_from==FROM_WIFI)  MIDI.sendSongPosition(beats);
}

void RouteMidiSongSelect(int note_from, byte songnumber) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.songSelect(songnumber);
  if (note_from==FROM_WIFI)  MIDI.sendSongSelect(songnumber);
}

void RouteMidiTuneRequest(int note_from) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.tuneRequest();
  if (note_from==FROM_WIFI)  MIDI.sendTuneRequest();
}

void RouteMidiClock(int note_from) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.clock();
  if (note_from==FROM_WIFI)  MIDI.sendRealTime(midi::Clock); 
}

void RouteMidiStart(int note_from) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.start();
  if (note_from==FROM_WIFI)  MIDI.sendRealTime(midi::Start);
}
void RouteMidiContinue(int note_from) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI._continue();
  if (note_from==FROM_WIFI)  MIDI.sendRealTime(midi::Continue);
}

void RouteMidiStop(int note_from) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.stop();
  if (note_from==FROM_WIFI)  MIDI.sendRealTime(midi::Stop); 
}

void RouteMidiActiveSensing(int note_from) {
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.activeSensing();
}

void RouteMidiSystemReset(int note_from) { 
  if (note_from==FROM_DIN)  if (isConnected) AppleMIDI.systemReset();
}


