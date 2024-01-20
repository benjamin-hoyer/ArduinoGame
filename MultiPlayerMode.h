#include "SinglePlayerMode.h"
 
//colors gets sets and returned in array
void setColorsMultiPlayer(int colorNumber[], int levelCounter){
  //neue farbe random
  colorNumber[levelCounter] = random(4); 
  Serial.print("New Number: ");
  Serial.println(colorNumber[levelCounter]);
  for (int i = 0; i < levelCounter; i++)
  {
  colors[i] = colorArray[colorNumber[i]];
  colors[i+12] = colorArray[colorNumber[i]];

  ledStrip.write(colors, LED_COUNT);
    delay(300);
    lightModeOff();
  }
}

//BUtton get pressed
 int ButtonPressedMultiPlayer(){
  Serial.print("ButtonPressed: ");
  while(true){
  if (!digitalRead(4))
  {
    tone(PIEZO_PIN, 660, 100);
    while(!digitalRead(4)){delay(10);}
    return 4;
  }
  else if (!digitalRead(5))
  {
        tone(PIEZO_PIN, 510, 100);

    while(!digitalRead(5)){ delay(10);}
    return 5;
  }
 
  else if(!digitalRead(2))
  {
    tone(PIEZO_PIN, 380, 100);
    while(!digitalRead(2)){delay(10);}
    return 2;
  }
  else if (!digitalRead(3))
  {
    tone(PIEZO_PIN, 770, 100);

    while(!digitalRead(3)){delay(10);}
    return 3;
  }
  else if (!digitalRead(7))
  {
    tone(PIEZO_PIN, 380, 100);

    while(!digitalRead(7)){delay(10);}
    return 7;
  }

  else if (!digitalRead(8))
  {
    tone(PIEZO_PIN, 770, 100);

    while(!digitalRead(8)){delay(10);}
    return 8;
  }
  
  else if (!digitalRead(9))
  {
    tone(PIEZO_PIN, 660, 100);

    while(!digitalRead(9)){delay(10);}
    return 9;
  }
  
  else if (!digitalRead(10))
  {
    tone(PIEZO_PIN, 510, 100);

    while(!digitalRead(10)){delay(10);}
    return 10;
  }
  delay(10);
  }
 }

// check Button orders
int checkButtonsMultiPlayer(int colorNumber[], int levelCounter){
    for(int i=0; i < levelCounter; i++)
    {
      int buttonNumber = ButtonPressedMultiPlayer();
      int buttonNumberPlayer2 = ButtonPressedMultiPlayer();
      if (buttonNumber-5 >= 0 && buttonNumberPlayer2-5 <= 0)
      {    
         buttonNumber -= 5;
      }
      else if (buttonNumber-5 <= 0 && buttonNumberPlayer2-5 >= 0)
      {    
         buttonNumberPlayer2 -= 5;
      }
      else {
        return 0;
      }
      if ((buttonNumber == buttonNumberPlayer2) && buttonNumber-2 == colorNumber[i])
      {
        colors[i] = colorArray[buttonNumber-2];
        colors[i+12] = colorArray[buttonNumber-2];
        ledStrip.write(colors, LED_COUNT);
      }
      else
      {lightModeAll(rgb_color(100, 0,0));
      return 0;
      }
     
    } return 1;
  }



void startMultiPlayer(){
 int levelCounter = 0;
 while(true)
 //game Loop
 {
  Serial.print("Level");
  Serial.println(levelCounter);
  int colorNumber[LED_COUNT];
  
  setColorsMultiPlayer(colorNumber, levelCounter);
  if (checkButtonsMultiPlayer(colorNumber, levelCounter))
  {
    //winning
    Serial.println("Success");
    levelCounter++;
    digitalWrite(UP, HIGH);
    delay(300);
    digitalWrite(UP, LOW);
    lightModeAll(rgb_color(0, 100,0));

  }
  else 
  {
    //loosing
    lightModeAll(rgb_color(100,0,0)); 
    soundModeLoosing();  
     digitalWrite(DOWN, HIGH);
    delay(400*levelCounter);
    digitalWrite(DOWN, LOW); 
    return;
  }
  //wait for new LevelStart
  if(levelCounter == 9)
  {
    digitalWrite(UP, HIGH);
    delay(1500);
    digitalWrite(UP, LOW);
    playWinningSound();
    lightModeParty();
    ButtonPressedMultiPlayer();
    digitalWrite(DOWN, HIGH);
    delay(400*levelCounter);
    delay(1500);
    digitalWrite(DOWN, LOW); 
    return;
  }
  
  delay(200);
}}
