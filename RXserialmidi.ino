#include "ESPixelStick.h"

void dinHandleNoteOn(byte channel, byte note, byte velocity) {
    RouteMidiNoteOn(FROM_DIN, channel, note, velocity);
}
void dinHandleNoteOff(byte channel, byte note, byte velocity) {
    RouteMidiNoteOff(FROM_DIN, channel, note, velocity);
}

void dinHandleAfterTouchPoly (byte channel, byte note, byte pressure) {
    RouteMidiAfterTouchPoly(FROM_DIN,  channel,  note,  pressure);
}

void dinHandleControlChange (byte channel, byte number, byte value) {
    RouteMidiControlChange(FROM_DIN,  channel,  number,  value);
}

void dinHandleProgramChange (byte channel, byte number) {
    RouteMidiProgramChange(FROM_DIN,  channel,  number);
}

void dinHandleAfterTouchChannel (byte channel, byte pressure) {
    RouteMidiAfterTouchChannel(FROM_DIN,  channel,  pressure);
}

void dinHandlePitchBend (byte channel, int bend) {
    RouteMidiPitchBend(FROM_DIN,  channel,  bend);
}

void dinHandleSystemExclusive (byte* array, unsigned size) {
    RouteMidiSystemExclusive(FROM_DIN, array,  size);
}

void dinHandleTimeCodeQuarterFrame (byte data) {
    RouteMidiTimeCodeQuarterFrame(FROM_DIN,  data);
}

void dinHandleSongPosition (unsigned beats) {
    RouteMidiSongPosition(FROM_DIN, beats);
}

void dinHandleSongSelect (byte songnumber) {
    RouteMidiSongSelect(FROM_DIN,  songnumber);
}

void dinHandleTuneRequest (void) {
    RouteMidiTuneRequest(FROM_DIN);
}

void dinHandleClock (void) {
    RouteMidiClock(FROM_DIN);
}

void dinHandleStart (void) {
    RouteMidiStart(FROM_DIN);
}

void dinHandleContinue (void) {
    RouteMidiContinue(FROM_DIN);
}

void dinHandleStop (void) {
    RouteMidiStop(FROM_DIN);
}

void dinHandleActiveSensing (void) {
    RouteMidiActiveSensing(FROM_DIN);
}

void dinHandleSystemReset (void) {
    RouteMidiSystemReset(FROM_DIN);
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
}

