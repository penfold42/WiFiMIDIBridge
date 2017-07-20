#include "ESPixelStick.h"

int counter_from_din;

void dinHandleNoteOn(byte channel, byte note, byte velocity) {
    counter_from_din++;
    RouteMidiNoteOn(FROM_DIN, channel, note, velocity);
}
void dinHandleNoteOff(byte channel, byte note, byte velocity) {
    counter_from_din++;
    RouteMidiNoteOff(FROM_DIN, channel, note, velocity);
}

void dinHandleAfterTouchPoly (byte channel, byte note, byte pressure) {
    counter_from_din++;
    RouteMidiAfterTouchPoly(FROM_DIN,  channel,  note,  pressure);
}

void dinHandleControlChange (byte channel, byte number, byte value) {
    counter_from_din++;
    RouteMidiControlChange(FROM_DIN,  channel,  number,  value);
}

void dinHandleProgramChange (byte channel, byte number) {
    counter_from_din++;
    RouteMidiProgramChange(FROM_DIN,  channel,  number);
}

void dinHandleAfterTouchChannel (byte channel, byte pressure) {
    counter_from_din++;
    RouteMidiAfterTouchChannel(FROM_DIN,  channel,  pressure);
}

void dinHandlePitchBend (byte channel, int bend) {
    counter_from_din++;
    RouteMidiPitchBend(FROM_DIN,  channel,  bend);
}

void dinHandleSystemExclusive (byte* array, unsigned size) {
    counter_from_din++;
    RouteMidiSystemExclusive(FROM_DIN, array,  size);
}

void dinHandleTimeCodeQuarterFrame (byte data) {
    counter_from_din++;
    RouteMidiTimeCodeQuarterFrame(FROM_DIN,  data);
}

void dinHandleSongPosition (unsigned beats) {
    counter_from_din++;
    RouteMidiSongPosition(FROM_DIN, beats);
}

void dinHandleSongSelect (byte songnumber) {
    counter_from_din++;
    RouteMidiSongSelect(FROM_DIN,  songnumber);
}

void dinHandleTuneRequest (void) {
    counter_from_din++;
    RouteMidiTuneRequest(FROM_DIN);
}

void dinHandleClock (void) {
    counter_from_din++;
    RouteMidiClock(FROM_DIN);
}

void dinHandleStart (void) {
    counter_from_din++;
    RouteMidiStart(FROM_DIN);
}

void dinHandleContinue (void) {
    counter_from_din++;
    RouteMidiContinue(FROM_DIN);
}

void dinHandleStop (void) {
    counter_from_din++;
    RouteMidiStop(FROM_DIN);
}

void dinHandleActiveSensing (void) {
    counter_from_din++;
    RouteMidiActiveSensing(FROM_DIN);
}

void dinHandleSystemReset (void) {
    counter_from_din++;
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

