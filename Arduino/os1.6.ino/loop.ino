
void loop () {

  theMillis = millis();
  theMicros =  micros();

  // ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  CLAP

  if ( (theMillis - clapTimer) >= clapInterval) {
    prevClapStates = clapStates;
    clapStates = (clapStates >> 1);

    byte clapTState = bitRead(clapStates, 0);
    clapInterval = (clapTState << 3) + 4;

    if (clapStates + prevClapStates > 0) {
      gateOffTimeTab[0] = veloShiftTab[0] + (theMicros + (max(0, (veloTab[0] - velocityMod)) * veloMulsTab[0] ));

      if (clapStates == 0 ) {
        clapTailT = 1;
        gateOffTimeTab[1] =  veloShiftTab[1] + (theMicros + (max(0, (veloTab[0] - velocityMod)) * veloMulsTab[1] ));
        PlayVoice(0, 1 );
      } else {
        PlayVoice(0, clapTState );
      }

    }
    clapTimer = theMillis;
  }

  // ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  CABASA

  if ( (theMillis - cabasaTimer) >= cabasaInterval) {
    prevCabasaStates = cabasaStates;
    cabasaStates = (cabasaStates >> 1);
    if (veloTab[9] > 10) {
      cabasaInterval *= cabasaTimeMod;
      veloTab[9] -= 10;
    }
    if (cabasaStates + prevCabasaStates > 0) {
      gateOffTimeTab[9] = veloShiftTab[9] + (theMicros + (max(0, (veloTab[9] - velocityMod)) * veloMulsTab[9] ) );
      PlayVoice(9, bitRead(cabasaStates, 0) );
    }
    cabasaTimer = theMillis;
  }

  // ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  CABASA 2

  if ( (theMillis - cabTimer) >= cabInterval) {
    prevCabStates = cabStates;
    cabStates = (cabStates >> 1);
    if (veloTab[10] > 5) {
      cabInterval *= cabTimeMod;
      veloTab[10] -= 2;
    }
    if (cabStates + prevCabStates > 0 ) {
      gateOffTimeTab[10] = veloShiftTab[10] + (theMicros + (max(0, (veloTab[10] - velocityMod) * veloMulsTab[10] ) >> 6 ));
      PlayVoice(10, bitRead(cabStates, 0) );
    }
    cabTimer = theMillis;
  }

  // ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  GUIRO

  if ( (theMicros - guiroTimer) >= guiroInterval) {
    prevGuiroStates = guiroStates;
    guiroStates = (guiroStates >> 1);

    if (veloTab[8] > 10) {
      guiroInterval -= 10;
      veloTab[8] -= 10;
    }

    if (guiroStates + prevGuiroStates > 0) {
      gateOffTimeTab[8] = veloShiftTab[8] + (theMicros + (max(0, (veloTab[8] - velocityMod)) * veloMulsTab[8] ) );
      PlayVoice(8, bitRead(guiroStates, 0) );
    }
    guiroTimer = theMicros;
  }

  // ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  CH

  if ( (theMicros - chTimer) >= chInterval) {
    prevChStates = chStates;
    chStates = (chStates >> 1);
    
    byte chTState = bitRead(chStates, 0);
    chInterval = 1700 + (veloTab[4] << 3) - (chTState << 4);
    
    if (chStates + prevChStates > 0) {
      gateOffTimeTab[4] = veloShiftTab[4] + (theMicros + (max(0, (veloTab[4] - velocityMod)) * veloMulsTab[4] ) );
      PlayVoice(4, chTState);
    }
    chTimer = theMicros;
  }

  byte chStates = 0;
  byte prevChStates = 0;
  byte chInterval = 220;
  unsigned long chTimer = 0;

  // ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  ==  == OTHER VOICES

  if (prevMicros != theMicros) {
    for (byte ii = 0; ii < 12; ii++) {
      if (gateOffTimeTab[ii] != 0 && gateOffTimeTab[ii] <= theMicros) {
        PlayVoice(ii, 0);
        gateOffTimeTab[ii] = 0;
      }
    }
  }
  prevMicros = theMicros;

  ///  ==  ==  == PITCH BEND BIT MASKING  ==  ==  ==

  if ( (theMillis - maskTimer) >= maskInterval) {
    for (byte ii = 0; ii < 12; ii++) {
      //handle pitch bend masking
      if ( pbMaskTabFlop[ii] != pbMaskTab[ii] ) {
        PlayVoice(ii, bitRead(pbMaskTab[ii], 0) );
      }
      //
      pbMaskTabFlop[ii] = pbMaskTab[ii];
    }
    maskTimer = theMillis;
  }

  // ==  ==  ==  MIDI reception  ==  ==  ==

  MIDI.read();

  prevMillis = theMillis;

}


