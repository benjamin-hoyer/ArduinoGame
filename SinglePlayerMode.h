#include <PololuLedStrip.h>

PololuLedStrip<12> ledStrip;

#define PIEZO_PIN  (13)
int UP = 11;
int DOWN = 6;


// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 24
rgb_color colors[LED_COUNT];
// 0, 1, 2, 3
// yellow, blue, pink, green 
rgb_color colorArray[4] = {rgb_color(250, 250, 0),rgb_color(0, 0, 250), rgb_color(250, 0, 0),rgb_color(0, 250, 0)};

 //turns off all Lights
 void lightModeOff(){
  for(int i; i<LED_COUNT; i++)
  {
      colors[i] = rgb_color(0, 0, 0);
   }  
     ledStrip.write(colors, LED_COUNT);
   
 }

void playWinningSound(){
 tone(13,660,100);
delay(150);
tone(13,660,100);
delay(300);
tone(13,660,100);
delay(300);
tone(13,510,100);
delay(100);
tone(13,660,100);
delay(300);
tone(13,770,100);
delay(550);
tone(13,380,100);
delay(575);

}

//alle lichter
 int lightModeAll(rgb_color colorRGB)
 {for(int j = 0; j<10; j++){
  for (int i=0; i<LED_COUNT; i++){
    colors[i]= colorRGB;
  }
  ledStrip.write(colors,LED_COUNT);
  delay(50);
  lightModeOff();
  delay(10);
  }
 }

//party Mode 
void lightModeParty()
{
  int j = 0;
  while(j<200){
  j++;
  for(int i = 0; i < 24; i++){
  colors[random(0, 24)] = rgb_color(random(0, 25), random(0, 25), random(0, 25));
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);
  delay(0);
  colors[i] = rgb_color(0, 0, 0);}
  }
  lightModeAll(rgb_color(50,100,200));
 }


//BUtton get pressed
 int ButtonPressed(){
  Serial.print("ButtonPressed: ");
  while(true){
  if (!digitalRead(4))
  {
    Serial.println("pink");
    tone(PIEZO_PIN, 660, 100);
    while(!digitalRead(4)){delay(10);}
    return 2;
  }
  else if (!digitalRead(5))
  {
    Serial.println("grün");
        tone(PIEZO_PIN, 510, 100);

    while(!digitalRead(5)){ delay(10);}
    return 3;
  }
 
  else if(!digitalRead(2))
  {
    Serial.println("gelb");
    tone(PIEZO_PIN, 770, 100);
    while(!digitalRead(2)){delay(10);}
    return 0;
  }
  else if (!digitalRead(3))
  {
    Serial.println("blau");
    tone(PIEZO_PIN, 380, 100);

    while(!digitalRead(3)){delay(10);}
    return 1;
  }
  delay(10);
  }
 }

 //colors gets sets and returned in array
void setColors(int colorNumber[], int levelCounter){
  //neue farbe random
  colorNumber[levelCounter] = random(4);
  Serial.print("New Number: ");
  Serial.println(colorNumber[levelCounter]);
  for (int i = 0; i <= levelCounter; i++)
  {
  colors[i] = colorArray[colorNumber[i]];
  ledStrip.write(colors, LED_COUNT);
    delay(300);
    lightModeOff();
  }
}



// check Button orders
int checkButtons(int colorNumber[], int levelCounter){
    for(int i=0; i <= levelCounter; i++)
    {
      int buttonNumber = ButtonPressed();
      
      if (buttonNumber != colorNumber[i])
      {lightModeAll(rgb_color(100, 0,0));
      return 0;
      }
      colors[i] = colorArray[buttonNumber];
      ledStrip.write(colors, LED_COUNT);
    }
    return 1;
  }


void soundModeLoosing(){
  Serial.println("sound loosing");
  int melody[] = {
  262, 196,196, 220, 196,0, 247, 262};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {4, 8, 8, 4,4,4,4,4 };

 for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(13, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(13);
    }
}


//start new Level
void startLevelSinglePlayer()
{ 
 int levelCounter = 0;
 while(true)
 //game Loop
 {
  Serial.print("Level");
  Serial.println(levelCounter);
  int colorNumber[LED_COUNT];
  setColors(colorNumber, levelCounter);
  if (checkButtons(colorNumber, levelCounter))
  {
    //winning
    Serial.println("Success");
    levelCounter++;
    digitalWrite(UP, HIGH);
    delay(400);
    digitalWrite(UP, LOW);
    lightModeAll(rgb_color(0, 100,0));

  }
  else 
  {
    //loosing
    soundModeLoosing();   
    digitalWrite(DOWN, HIGH);
    delay(400*levelCounter);
    digitalWrite(DOWN, LOW);
    lightModeAll(rgb_color(100,0,0)); 

    return;
  }
  //wait for new LevelStart
    if(levelCounter == 13)
  {
    digitalWrite(UP, HIGH);
    delay(1500);
    digitalWrite(UP, LOW); 
    playWinningSound();
    lightModeParty();
    ButtonPressed();
    digitalWrite(DOWN, HIGH);
    delay(300*levelCounter);
    delay(1500);
    digitalWrite(DOWN, LOW); 
   
    return;
    
  }
  delay(200);
 }}
