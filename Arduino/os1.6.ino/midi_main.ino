
void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
  processNote(inNote, inVelocity);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
  processNote(inNote, 0);
  pbMaskTab[lastPlayedVoice] = 0;

  if (gatesByte == 0) {
    allNotesOff();
  }
}

void handleControlChange(byte inChannel, byte inNumber, byte inValue)
{
  if (inNumber == 1) {
    velocityMod = inValue;
  } else   if (inNumber == 123) {
    //all notes off
    allNotesOff();
  }
}

void handlePitchBend(byte inChannel, int val) {
  pbMaskTab[lastPlayedVoice] = val >> 10;
}

void handleStart() {
  allNotesOff();
}

