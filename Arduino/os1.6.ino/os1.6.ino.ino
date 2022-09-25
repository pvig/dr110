#include <MIDI.h>
#include <digitalWriteFast.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define  statusLed 16
#define  midiChannel 8

byte incomingByte;
byte note;
byte velocity;
byte action;

byte velocityMod = 0;

byte lastPlayedVoice;
//
unsigned long theMillis = 0;
unsigned long prevMillis = 0;

unsigned long theMicros = 0;
unsigned long prevMicros = 0;

// sequence :
word tickCount = 0;

// drum map :
// cp, ac, sn, bd, ch, oh, cy
byte drumMap[12] = {
  3, 1, 7, 0, 2, 10, 4, 8, 5, 9, 6, 7
};
byte clapStates = 0;
byte clapTailT = 0;
byte prevClapStates = 0;
word clapInterval = 8;
unsigned long clapTimer = 0;
byte clapIMod[8] = {1, 2, 3, 3, 4, 7, 8, 9};

byte cabasaStates = 0;
byte prevCabasaStates = 0;
word cabasaInterval = 5;
float cabasaTimeMod = 1.1;
unsigned long cabasaTimer = 0;

byte cabStates = 0;
byte prevCabStates = 0;
word cabInterval = 5;
float cabTimeMod = 0.7;
unsigned long cabTimer = 0;

word guiroStates = 0;
word prevGuiroStates = 0;
word guiroInterval = 220;
unsigned long guiroTimer = 0;

byte chStates = 0;
byte prevChStates = 0;
word chInterval = 220;
unsigned long chTimer = 0;

byte gatesByte = 1;

byte prevGatesByte = 0;
//
byte pbMaskTab[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte pbMaskTabFlop[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned long gateOffTimeTab[12] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
byte veloTab[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int veloShiftTab[12] = {85, 10, 30, 130, 10, 100, 100, 2, 20, 20, 2, 400};
int veloMulsTab[12] = {5, 6, 6, 6, 4, 4, 2, 1, 6, 8, 2, 6};

byte maskInterval = 12;
unsigned long maskTimer = 0;
