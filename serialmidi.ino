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


