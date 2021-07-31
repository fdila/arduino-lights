#include <Adafruit_NeoPixel.h>
#include <Ticker.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1 14
#define PIN2 15

Adafruit_NeoPixel leftstrip = Adafruit_NeoPixel(15, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightstrip = Adafruit_NeoPixel(15, PIN2, NEO_GRB + NEO_KHZ800);

volatile int brightness;
volatile byte blinkMode = 0;
volatile boolean testInterrupt = 0;
volatile unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
volatile unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers

void setBrightLed(){
  brightness = map(analogRead(A0),0,1024,0,255);
  rightstrip.setBrightness(brightness);
  leftstrip.setBrightness(brightness);
}

Ticker timerBright(setBrightLed, 150);

void IRAM_ATTR incMode(){
  if(millis()-lastDebounceTime > debounceDelay){
    blinkMode++;
    blinkMode = blinkMode % 5;
    if (blinkMode < 0)
    blinkMode = blinkMode + 5;
    testInterrupt = 1;
    lastDebounceTime = millis();
  }
}

void IRAM_ATTR decMode(){
  if(millis()-lastDebounceTime > debounceDelay){
    blinkMode--;
    if (blinkMode == 255)
    blinkMode = 4;
    testInterrupt = 1;
    lastDebounceTime = millis();
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(4, INPUT); //Pushbutton 1
  pinMode(5, INPUT); //Pushbutton 2
  attachInterrupt(digitalPinToInterrupt(4), incMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), decMode, FALLING);


  timerBright.start();

  leftstrip.begin();
  leftstrip.show(); // Initialize all pixels to 'off'
  rightstrip.begin();
  rightstrip.show(); // Initialize all pixels to 'off'
  delay(1); //delays needed to keep ESP2866 stable, not needed for other boards
  rightstrip.setBrightness(255);
  leftstrip.setBrightness(255);
  blinkMode = 4;
  
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return leftstrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return leftstrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leftstrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void loop(){
  delay(1);
  testInterrupt=0;

  int val = digitalRead(4); 

  if (val == HIGH)
    Serial.print("alto \n");
  else if (val == LOW)
    Serial.print("basso \n");
  else 
    Serial.print("WTF \n");

  // light chase
  if(blinkMode==0 && !testInterrupt){
    for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
      if(!testInterrupt){
        timerBright.update();
        leftstrip.setPixelColor(i, 255, 255, 255);
        leftstrip.setPixelColor(i - 1, 0, 0, 0);
        leftstrip.show();
        rightstrip.setPixelColor(i, 255, 255, 255);
        rightstrip.setPixelColor(i - 1, 0, 0, 0);
        rightstrip.show();
        delay(80);
      }
    }
  }
  // Rainbow Wheel
  else if(blinkMode==1 && !testInterrupt){
    uint16_t i, j;
    for (j = 0; j < 255 * 5; j++) { // 5 cycles of all colors on wheel
      if(!testInterrupt){
        for (i = 0; i < leftstrip.numPixels(); i++) {
          timerBright.update();
          leftstrip.setPixelColor(i, Wheel(((i * 256 / leftstrip.numPixels()) + j) & 255));
          rightstrip.setPixelColor(i, Wheel(((i * 256 / rightstrip.numPixels()) + j) & 255));
        }
        leftstrip.show();
        rightstrip.show();
        delay(30);
      }
    }
  }
  // Rainbow Wheel 2
  else if (blinkMode==2 && !testInterrupt){
    for (int j = 0; (j < 256 && !testInterrupt); j++) {   // cycle all 256 colors in the wheel
      for (int q = 0; (q < 3 && !testInterrupt); q++) {
        for (uint16_t i = 0; (i < leftstrip.numPixels() && !testInterrupt); i = i + 3) {
          leftstrip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
          rightstrip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
        }
        leftstrip.show();
        rightstrip.show();

        delay(150);

        for (uint16_t i = 0;( i < leftstrip.numPixels() && !testInterrupt); i = i + 3) {
          leftstrip.setPixelColor(i + q, 0);
          rightstrip.setPixelColor(i + q, 0);     //turn every third pixel off
        }
      }
    }

  }
  // Red Lights
  else if (blinkMode==3 && !testInterrupt){
    for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
      if(!testInterrupt){
        timerBright.update();
        leftstrip.setPixelColor(i, 140, 0, 0);
        leftstrip.show();
        rightstrip.setPixelColor(i, 140, 0, 0);
        rightstrip.show();
        delay(120);
      }
    }
    for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
      if(!testInterrupt){
        timerBright.update();
        leftstrip.setPixelColor(i, 55, 0, 0);
        leftstrip.show();
        rightstrip.setPixelColor(i, 55, 0, 0);
        rightstrip.show();
        delay(120);
      }
    }
  }
  // Fixed lights white
  else if (blinkMode==4 && !testInterrupt){
    for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
      if(!testInterrupt){
        timerBright.update();
        leftstrip.setPixelColor(i, 255, 222, 152);
        leftstrip.show();
        rightstrip.setPixelColor(i, 255, 222, 152);
        rightstrip.show();
      }
    }
  }
}
