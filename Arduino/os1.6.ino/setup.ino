
void setup() {

  for (byte i = 2; i < 20; i++) {
    digitalWrite(i, HIGH);
    pinMode(i, OUTPUT);
  }

  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  //midi.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  //midi.setHandleStop(handleStop);
  MIDI.setHandleControlChange(handleControlChange);
  MIDI.setHandlePitchBend(handlePitchBend);
  //midi.setThruFilterMode(midi::Full);
  //midi.turnThruOn();

  MIDI.begin(midiChannel);
}


