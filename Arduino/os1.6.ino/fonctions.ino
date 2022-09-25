
void processNote(byte note, byte velocity) {
  byte voiceNum = getInstrNum(note);
  byte isOn = (velocity > 0) ? 1 : 0;
  bitWrite(gatesByte, voiceNum, isOn);
  gateOffTimeTab[voiceNum] = veloShiftTab[voiceNum] + (theMicros + (max(0, (velocity - velocityMod)) * veloMulsTab[voiceNum] ));

  if (velocity > 0) {
    switch (voiceNum) {
      case 4:
        //ch
        chStates = 10;
        chInterval = 1700 + (velocity << 3);
        break;
      case 10:
        //fast cabasa
        cabStates = 214;
        cabInterval = (18 - (velocity >> 4));
        break;
      case 8:
        // guiro
        guiroStates = 42;
        guiroInterval = (32000 - (velocity << 6 ));
        break;
      case 9:
        // cabasa :
        cabasaStates = 20;
        cabasaTimeMod = 1.2;
        cabasaInterval = (8 - (velocity >> 4));
        break;
      case 7:
        // accent gated :
        gateOffTimeTab[voiceNum] = 0;
        break;
      case 0:
        //clap
        clapStates = 10;
        clapTailT = 0;
        clapInterval = clapIMod[ velocity >> 4 ];
        break;
    }
    veloTab[voiceNum] = velocity;
    PlayVoice(voiceNum, 1);
  } else {
    switch (voiceNum) {
      case 10:
        cabStates = 1;
        gateOffTimeTab[voiceNum] = 1;
        break;
      case 7:
        // accent off :
        gateOffTimeTab[voiceNum] += 200;
        break;
    }
  }

  lastPlayedVoice = voiceNum;
}

byte getInstrNum(byte notenum) {
  return drumMap[notenum % 12];
}

void PlayVoice(byte voiceNum, byte gate) {
  switch (voiceNum) {
    case 10:
      //fast cabasa
      digitalWriteFast(9, !gate);
      break;
    case 8:
      // guiro
      digitalWriteFast(3, !gate);
      break;
    case 9:
      // cabasa
      digitalWriteFast(5, !gate);
      break;
    case 7:
      // accent :
      digitalWriteFast(2, !gate);
      break;
    case 1:
      //cp crack
      digitalWriteFast(3, !gate);
      break;
    case 0:
      //clap
      if (clapTailT > 0) {
        digitalWriteFast(4, !gate);
      } else {
        digitalWriteFast(3, !gate);
      }
      break;
    default:
      digitalWriteFast(3 + (voiceNum), !gate);
  }

}

void allNotesOff() {
  clapStates = 0;
  clapTailT = 0;
  for (byte ii = 0; ii < 12; ii++) {
    pbMaskTab[ii] = 0;
    digitalWriteFast(2 + ii, 1);
  }
}

