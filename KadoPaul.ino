// defines pins numbers
#define stepPin1 1
#define stepPin2 3
#define dirPin1 2
#define dirPin2 4

#define stepPin3 5
#define stepPin4 7
#define dirPin3 6
#define dirPin4 8

#define analogPin A9
#define homesens1 13
#define homesens2 14
//const int enablePin = 0;

const int posmin = 0;
const int posmax = 10 * 200 * 16;
const int crashamount = 2000;
int relspduringcrash = 20;
int homeoffset = -10000;

int crashendpos1;
int crashendpos2;
int numbercrashes = 0;

int PingPongState = 1;
bool PingPongStarted;
int pingpongpos;
int relspduringPinPong = 44;
int PingPongwait = 500000;

const int maxspeedscaling = 20;

int state = 1;
int ain = 0; // 0..1023 for Teensy 3.6
int song = 0;
int thisNote = 0;

int musiclimit = 20;
int crashlimit = 1015;
int hys = 3;

float speedup = 1;
bool dir = 0;
bool startdir = 0;
bool cancrash  = 1;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


int targetposlist[] = {
  1000 , 5000 , 2000 , 2200 , 4000 , 10000 , 0
};
int targetpos = targetposlist[0];
int itarget;

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

// notes in the melody:
int melody1[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};


// Music notes of the song, 0 is a rest/pulse
int notes[] = {
  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
  NOTE_A4, NOTE_G4, NOTE_A4, 0,

  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
  NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
  NOTE_A4, NOTE_G4, NOTE_A4, 0,

  NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
  NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
  NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
  NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
  NOTE_D5, NOTE_E5, NOTE_A4, 0,
  NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
  NOTE_C5, NOTE_A4, NOTE_B4, 0,

};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int durations[] = {
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,

  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,

  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125,
  250, 125, 250, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

};


// The melody array
int melody_TakeonMe[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5,
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

// The note duration, 8 = 8th note, 4 = quarter note, etc.
int tempo_TakeonMe[] = {
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8
};


#include <AccelStepper.h>
// AccelStepper::DRIVER means a stepper driver (with Step and Direction pins)
AccelStepper stepper1(AccelStepper::DRIVER, stepPin1, dirPin1);
AccelStepper stepper2(AccelStepper::DRIVER, stepPin2, dirPin2);
AccelStepper stepper3(AccelStepper::DRIVER, stepPin3, dirPin3);
AccelStepper stepper4(AccelStepper::DRIVER, stepPin4, dirPin4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  stepper1.setAcceleration(30000000);
  stepper2.setAcceleration(30000000);
  stepper3.setAcceleration(30000000);
  stepper4.setAcceleration(30000000);
  pinMode( homesens1 , INPUT_PULLUP );
  pinMode( homesens2 , INPUT_PULLUP );
//  pinMode( enablePin , OUTPUT );
}

void loop() {
  ain = analogRead( A9);

  switch (state) {
    case 1: // Boot
      state = 10;

      break;

    case 10: { // Init
//        digitalWrite( enablePin , HIGH);
        if ( !digitalRead( homesens1 ) || !digitalRead( homesens2 ) ) {
          while ( !move( 10000 , 10000 , 5000 )) {}; // Move out of home sensors
        }
        state = 11;
      }

    case 11: { // Home
        // Home sequence
        // Set positions

        bool homedone = home();

        if ( homedone ) {
          if (ain < musiclimit) {
            state = 20;
          }
          else { // Never start with crash
            state = 30;
          }
        }
      }
      break;

    case 20: { //Music
        if ( sing(song) ) {
          song += 1;
          if (song > 3) {
            song = 0;
            startdir = !startdir;
            dir = startdir; //Prevent long term drift
          }
        }
        if (ain > musiclimit + hys) {
          state = 30;
        }
      }
      break;

    case 30: { //Move

        if (move( targetpos , targetpos , ain * maxspeedscaling)) {
          //Setpoint done
          if (ain > crashlimit - 200 ) { // When aproaching speed limit, only do full setpoints, increase acceleration and no waiting
            if (targetpos == 0) {
              targetpos = posmax;
            }
            else {
              targetpos = 0;
            }
            stepper1.setAcceleration(300000);
            stepper2.setAcceleration(300000);
            stepper3.setAcceleration(300000);
            stepper4.setAcceleration(300000);         
          }
          else {
            itarget++;
            if ( itarget == sizeof(targetposlist) / sizeof(int)) {
              itarget = 0;
            }
            targetpos = targetposlist[ itarget ];
            stepper1.setAcceleration(30000);
            stepper2.setAcceleration(30000);            
            stepper3.setAcceleration(30000);
            stepper4.setAcceleration(30000);
            delay(500);
          }
        }

        if (ain < musiclimit - hys) {
          state = 20;
        }
        else if (ain > crashlimit + hys) {
          if (abs( stepper1.distanceToGo()) > crashamount * 1  && (abs( stepper1.distanceToGo()) < posmax -  crashamount * 1   )) { // To make sure we have some margin
            if (abs( stepper1.speed()) >= ain * maxspeedscaling) {
              state = 40;
            }
          }
        }
      }
      break;

    case 40: //Crash
      {
        int crashpos = stepper1.currentPosition();
        if ( cancrash ) {
          while ( !crash( crashpos ) );
          crashendpos1 = stepper1.currentPosition();
          crashendpos2 = stepper2.currentPosition();
          //        Serial.println( stepper1.currentPosition() );
          //        Serial.println( stepper2.currentPosition() );
        }
        else { //has crashed
          if (move( crashendpos1 , crashendpos2 + relspduringcrash , 200)) {
            relspduringcrash *= -1;
          }
        }
        cancrash = 0;

        if (ain < crashlimit - hys) { // Recover from crash when you reduce speed
          state = 30;
          cancrash = 1;
          while ( !move( crashpos , crashpos , 500 )); // Make straight
          delay(200);

          //        Serial.println( stepper1.currentPosition() );
          //        Serial.println( stepper2.currentPosition() );
          numbercrashes ++;
          if (numbercrashes <= 2) {
            playrecoversound();
          }
          else {
            state = 50;
            numbercrashes = 0;
          }
        }
      }
      break;

    case 50: //Ping Pong
      {
        if ( !PingPongStarted ) {
          PingPongStarted = true;
          pingpongpos = stepper1.currentPosition();
          stepper1.setAcceleration(30000000);
          stepper2.setAcceleration(30000000);          
          stepper3.setAcceleration(30000000);
          stepper4.setAcceleration(30000000);
        }

        bool doDelay = false;
        switch (PingPongState ) {
          case 1:
            if (move( pingpongpos , pingpongpos + relspduringPinPong , 459)) {
              PingPongState = 2;
              doDelay = true;
            }
            break;
          case 2:
            if (move( pingpongpos + relspduringPinPong * 2 , pingpongpos + relspduringPinPong , 2 * 459)) {
              PingPongState = 3;
              doDelay = true;
            }
            break;
          case 3:
            if (move( pingpongpos + relspduringPinPong * 2 , pingpongpos  , 459)) {
              PingPongState = 4;
              doDelay = true;
            }
            break;
          case 4:
            if (move( pingpongpos , pingpongpos  , 2 * 459)) {
              PingPongState = 1;
              doDelay = true;
              PingPongwait *= 0.85;
            }
            break;
        }

        if (doDelay) {
          delayMicroseconds( PingPongwait );
          if (PingPongwait <= 500) {
            delay(500);
            PingPongwait = 500000;
            PingPongStarted = false;
            while ( !move( pingpongpos , pingpongpos , 500 )) {}; // Make straight
            state = 30; //Only get out of Ping Pong when done
          }
        }

      }

      break;
    default: {
        state = 1;
      }
  }

}

bool crash( int crashpos ) {
  bool crashdone = false;
  if (crashpos < targetpos) {
    crashdone = move( crashpos , crashpos + crashamount , ain * maxspeedscaling);
  }
  else {
    crashdone = move( crashpos , crashpos - crashamount , ain * maxspeedscaling);
  }
  return crashdone;
}

bool move( int targetpos1 , int targetpos2 ,  int speed  ) {

  stepper1.moveTo( targetpos1 );
  stepper2.moveTo( targetpos2);
  stepper3.moveTo( targetpos2 );
  stepper4.moveTo( targetpos1);
  
  stepper1.setMaxSpeed( speed );
  stepper2.setMaxSpeed( speed );
  stepper3.setMaxSpeed( speed );
  stepper4.setMaxSpeed( speed );
  stepper1.run();
  stepper2.run();  
  stepper3.run();
  stepper4.run();

  bool movedone = 0;
  if ( stepper1.currentPosition() == targetpos1 && stepper2.currentPosition() == targetpos2 ) {
    movedone = 1;
  }
  return movedone;
}

bool sing(int s) {
  // iterate over the notes of the melody:
  thisNote++;
  int size = 0;
  int noteDuration = 0;
  if (s == 0) {
    size = sizeof(melody) / sizeof(int);
    noteDuration = 1000 / tempo[thisNote];
    buzz(melody[thisNote], noteDuration);
  }
  else if (s == 1) {
    size = sizeof(underworld_melody) / sizeof(int);
    noteDuration = 1000 / underworld_tempo[thisNote];
    buzz(underworld_melody[thisNote], noteDuration);
  }
  else if (s == 2) {
    size = sizeof(melody_TakeonMe) / sizeof(int);
    noteDuration = 1000 / tempo_TakeonMe[thisNote];
    buzz(melody_TakeonMe[thisNote], noteDuration);
  }
  else if (s == 3) {
    size = sizeof(notes) / sizeof(int);
    noteDuration = durations[thisNote];
    buzz(notes[thisNote], noteDuration);
  }
  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes / speedup);
  bool songdone = false;
  if (thisNote == size) {
    thisNote = 0;
    songdone = true;
  }
  return songdone;
}

void buzz( long frequency, long length ) {
  dir = !dir;
  digitalWrite(dirPin1, dir);
  digitalWrite(dirPin2, dir);
  digitalWrite(dirPin3, dir);
  digitalWrite(dirPin4, dir);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(stepPin1, HIGH); // write the buzzer pin high to push out the diaphram
    digitalWrite(stepPin2, HIGH); // write the buzzer pin high to push out the diaphram
    digitalWrite(stepPin3, HIGH); // write the buzzer pin high to push out the diaphram
    digitalWrite(stepPin4, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue / speedup); // wait for the calculated delay value
    digitalWrite(stepPin1, LOW); // write the buzzer pin low to pull back the diaphram
    digitalWrite(stepPin2, LOW); // write the buzzer pin low to pull back the diaphram
    digitalWrite(stepPin3, LOW); // write the buzzer pin low to pull back the diaphram
    digitalWrite(stepPin4, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue / speedup); // wait again or the calculated delay value


    if (dir) { //Not checked if these are the right directions! Maybe needs to swap?
      stepper1.setCurrentPosition(stepper1.currentPosition() + 1);
      stepper2.setCurrentPosition(stepper2.currentPosition() + 1);
      stepper3.setCurrentPosition(stepper3.currentPosition() + 1);
      stepper4.setCurrentPosition(stepper4.currentPosition() + 1);
    }
    else {
      stepper1.setCurrentPosition(stepper1.currentPosition() - 1);
      stepper2.setCurrentPosition(stepper2.currentPosition() - 1);
      stepper3.setCurrentPosition(stepper3.currentPosition() - 1);
      stepper4.setCurrentPosition(stepper4.currentPosition() - 1);
    }
  }
}

bool home() {

  bool static homedone1 = false;
  bool static homedone2 = false;

  stepper1.setMaxSpeed(10000);
  stepper1.setAcceleration(30000);
  stepper2.setMaxSpeed(10000);
  stepper2.setAcceleration(30000);
  stepper3.setMaxSpeed(10000);
  stepper3.setAcceleration(30000);
  stepper4.setMaxSpeed(10000);
  stepper4.setAcceleration(30000);

  stepper1.moveTo( -1000000 );
  stepper2.moveTo( -1000000 );  
  stepper3.moveTo( -1000000 );
  stepper4.moveTo( -1000000 );

  if ( digitalRead( homesens1 ) && !homedone1 ) {
    stepper1.run();
    stepper4.run();
  }
  else {
    homedone1 = true;
    stepper1.setCurrentPosition(homeoffset);
    stepper4.setCurrentPosition(homeoffset);
  }

  if ( digitalRead( homesens2 ) && !homedone2 ) {
    stepper2.run();
    stepper3.run();
  }
  else {
    homedone2 = true;
    stepper2.setCurrentPosition(homeoffset);
    stepper3.setCurrentPosition(homeoffset);
  }

  if ( homedone1 && homedone2 ) {
    while ( !move( 0 , 0 , 10000 )) {};
  }

  return homedone1 && homedone2;
}



void playrecoversound() {
  static bool welke = false;
  if ( welke ) {
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations1[thisNote];
      buzz(melody1[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }
  }
  else {
    buzz(NOTE_B5, 100);
    delay(100);
    buzz(NOTE_E6, 850);
    delay(600);
    buzz(NOTE_E6, 125);
    delay(100);
    buzz(NOTE_G6, 125);
    delay(100);
    buzz(NOTE_E7, 125);
    delay(100);
    buzz(NOTE_C7, 125);
    delay(100);
    buzz(NOTE_D7, 125);
    delay(100);
    buzz(NOTE_G7, 125);
    delay(1000);
  }
  welke = !welke;
}
