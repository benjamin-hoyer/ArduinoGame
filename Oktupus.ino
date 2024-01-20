
//#include "SinglePlayerMode.h"
//#include "MultiPlayerMode.h"
#include "ReactionMode.h"
#include "Tetris.h"
#define PIEZO_PIN (13)


void setup()
{
    Serial.begin(9600);
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    pinMode(PIEZO_PIN, OUTPUT);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    pinMode(10, INPUT_PULLUP);
    pinMode(11, OUTPUT);
    pinMode(6, OUTPUT);

    randomSeed(analogRead(0));
}

void loop()
{
   if(digitalRead(7) == LOW && digitalRead(8) == LOW && digitalRead(9) ==LOW && digitalRead(10) == LOW){
      startMultiPlayer();
     }
   if(digitalRead(2) == LOW && digitalRead(5) == LOW && digitalRead(3) ==LOW && digitalRead(4) == LOW){
    startLevelSinglePlayer();
  }
  else if (digitalRead(2) == LOW && digitalRead(7) == LOW)
  {
    playWinningSound();
  }
  
}
