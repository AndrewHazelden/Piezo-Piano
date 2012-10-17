#include "PiezoPiano_objects.h"

//--------------------- User code ---------------------//

//----------------- End of User code ------------------//

// Event Handlers

//slow repeat rate in ms
//#define SPEED 250

//normal repeat rate in ms
//#define SPEED 175

//fast repeat rate in ms
#define SPEED 150

//-----------------------------

void ToneA3() {
  Sound_Play( 110, SPEED);
}

void ToneB3() {
  Sound_Play( 123, SPEED);
}

void ToneC3() {
  Sound_Play( 130, SPEED);
}

void ToneD3() {
  Sound_Play( 146, SPEED);
}

void ToneE3() {
  Sound_Play( 164, SPEED);
}

void ToneF3() {
  Sound_Play( 174, SPEED);
}

void ToneG3() {
  Sound_Play( 196, SPEED);
}


//------------------------

void ToneA4() {
  Sound_Play( 220, SPEED);
}

void ToneB4() {
  Sound_Play( 246, SPEED);
}

void ToneC4() {
  Sound_Play( 261, SPEED);
}

void ToneD4() {
  Sound_Play( 293, SPEED);
}

void ToneE4() {
  Sound_Play( 329, SPEED);
}

void ToneF4() {
  Sound_Play( 349, SPEED);
}

void ToneG4() {
  Sound_Play( 392, SPEED);
}

//-----------------------
void ToneA5() {
  Sound_Play( 440, SPEED);
}

void ToneB5() {
  Sound_Play( 493, SPEED);
}

void ToneC5() {
  Sound_Play( 523, SPEED);
}

void ToneD5() {
  Sound_Play( 587, SPEED);
}

void ToneE5() {
  Sound_Play( 659, SPEED);
}

void ToneF5() {
  Sound_Play( 698, SPEED);
}

void ToneG5() {
  Sound_Play( 783, SPEED);
}



//-----------------------


void ToneA6() {
  Sound_Play( 880, SPEED);
}

void ToneB6() {
  Sound_Play( 987, SPEED);
}

void ToneC6() {
  Sound_Play( 1046, SPEED);
}

void ToneD6() {
  Sound_Play( 1174, SPEED);
}

void ToneE6() {
  Sound_Play( 1318, SPEED);
}

void ToneF6() {
  Sound_Play( 1396, SPEED);
}

void ToneG6() {
  Sound_Play( 1567, SPEED);
}


//--------------------------

void ToneFSharp3(){
  Sound_Play( 185, SPEED);
}

void ToneGSharp3(){
  Sound_Play( 207, SPEED);
}

void ToneASharp4(){
  Sound_Play( 233, SPEED);
}


void ToneCSharp4(){
  Sound_Play( 277, SPEED);
}

void ToneDSharp4(){
  Sound_Play( 311, SPEED);
}


//----------------- End of User code ------------------//

// Event Handlers


void FPianoKeyOnPress() {
   ToneF3();
}

void GPianoKeyOnPress() {
   ToneG3();
}

void APianoKeyOnPress() {
   ToneA4();
}

void BPianoKeyOnPress() {
   ToneB4();
}

void CPianoKeyOnPress() {
   ToneC4();
}

void DPianoKeyOnPress() {
   ToneD4();
}

void EPianoKeyOnPress() {
   ToneE4();
}

void FsPianoKeyOnPress() {
   ToneFSharp3();
}

void GsPianoKeyOnPress() {
   ToneGSharp3();
}

void AsPianoKeyOnPress() {
   ToneASharp4();
}

void CsPianoKeyOnPress() {
   ToneCSharp4();
}

void DsPianoKeyOnPress() {
   ToneDSharp4();
}