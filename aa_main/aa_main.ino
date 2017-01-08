#include <Shape.h>
#include <FastLED.h>
#include <SoftwareSerial.h>


#define ROWS 20
#define COLUMNS 20
#define NUM_LEDS ROWS*COLUMNS
#define DATA_PIN 30

#define L(x,y,z) leds[x+ROWS*y]=c[z]
#define Ll(x,y) leds[x+ROWS*y]
#define SHOW FastLED.show()

String cmd;

CRGB leds[NUM_LEDS];
SoftwareSerial bt(10, 11);
CRGB c[9];



void setup() {
  randomSeed(analogRead(A0));
  bt.begin(9600);
  //bt.setTimeout(3000);
  Serial.begin(115200);
  Serial.println(F("<Arduino is ready>"));
  c[7]=CRGB::Red;
  c[8]=CRGB::White;
  c[6]=CRGB::Green;
  c[5]=CRGB::Blue;
  c[4]=CRGB::Pink;
  c[3]=CRGB::Yellow;
  c[2]=CRGB::Purple;
  c[1]=CRGB::Cyan;
  c[0]=CRGB::Black;
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);
  //3.1.1 FastLED.setMaxPowerInVoltsAndMilliamps(5,15000);
  
  fillColor(0);
  SHOW;
  bt.print("main:");
}
void loop() {
  if(btreceive()){
    command();
  }
}
bool btreceive() {
  if (bt.available() > 0) {
    cmd = bt.readStringUntil(':');
    Serial.print(F("Received : "));
    Serial.println(cmd);
    return true;
  }
  return false;
}
void rect(byte x1, byte y1, byte x2, byte y2,byte col){
  for(byte x = x1;x<=x2;x++){
    for(byte y = y1;y<=y2;y++){
      L(x,y,col);
    }
  }
}
void command(){
  if(cmd.substring(0,3)==F("led")){
    Serial.println(F("LEDDD"));

    byte x = cmd.substring(3,5).toInt();
    byte y = cmd.substring(5,7).toInt();
    byte col = cmd.substring(7).toInt();
    Serial.print(F("x = "));
    Serial.print(x);
    Serial.print(F(" y = "));
    Serial.print(y);
    Serial.print(F(" col = "));
    Serial.println(col);
    L(x,y,col);
    SHOW;
  }
  else if(cmd==F("red")){
    fillColor(7);
  }
  else if(cmd==F("blue")){
    fillColor(5);
  }
  else if(cmd==F("green")){
    fillColor(6);
  }
  else if(cmd==F("pong")){
    pong2(500);
  }
  else if(cmd==F("tetris")){
    tetris(700);
  }
  else if(cmd==F("snake")){
    snake(700);
  }
  else if(cmd==F("off")){
    off();
  }
  else if(cmd.substring(0,4)==F("test")){
    bt.print(cmd.substring(4));
    bt.print(":");
  }
  else if(cmd==F("simple")){
    simpleEffect();
  }
  else{
    Serial.print(cmd);
    Serial.println(F(" Erreur lecture !"));
  }
  Serial.println(F("Menu principale !"));
}
void fillColor(byte col){
  for(byte y = 0; y<20; y++){
    for(byte x = 0; x<20 ; x++){
      L(x,y,col);
    }
  }
  SHOW;
}
void off(){
  fillColor(0);
}
void pause(){
  
  Serial.println(F("Paused"));
  while(cmd!=F("end") && cmd!=F("go") && cmd!=F("up") && cmd!=F("down")){
            btreceive();
            delay(100);
   }
  if(cmd!=F("end")){
    cmd="";
  }
  
}


