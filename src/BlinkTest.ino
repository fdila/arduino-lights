#include <Adafruit_NeoPixel.h>
#include <Ticker.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1 14
#define PIN2 15

Adafruit_NeoPixel leftstrip = Adafruit_NeoPixel(15, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightstrip = Adafruit_NeoPixel(15, PIN2, NEO_GRB + NEO_KHZ800);

void setBrightLed(){
  int brightness;
  brightness = map(analogRead(A0),0,1024,0,255);
  Serial.println(brightness);
  rightstrip.setBrightness(brightness);
  leftstrip.setBrightness(brightness);
}

Ticker timerBright(setBrightLed, 200);

void setup(){
  Serial.begin(9600);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(4, INPUT_PULLUP); //Pushbutton 1
  pinMode(5, INPUT_PULLUP); //Pushbutton 2
  pinMode(0, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(4), incMode, FALLING);
  attachInterrupt(digitalPinToInterrupt(5), decMode, FALLING);


  timerBright.start();

  leftstrip.begin();
  leftstrip.show(); // Initialize all pixels to 'off'
  rightstrip.begin();
  rightstrip.show(); // Initialize all pixels to 'off'
  delay(1); //delays needed to keep ESP2866 stable, not needed for other boards
  rightstrip.setBrightness(10);
  leftstrip.setBrightness(10);
  digitalWrite(0, LOW);
}
volatile byte blinkMode = 0;
volatile boolean testInterrupt = 0;
volatile unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
volatile unsigned long debounceDelay = 200;    // the debounce time; increase if the output flickers


void incMode(){
  if(millis()-lastDebounceTime > debounceDelay){
    blinkMode++;
    testInterrupt = 1;
    lastDebounceTime = millis();
    Serial.println(blinkMode);
  }
}

void decMode(){
  if(millis()-lastDebounceTime > debounceDelay){
    blinkMode--;
    testInterrupt = 1;
    lastDebounceTime = millis();
    Serial.println(blinkMode);
  }
}



void loop(){
  delay(1);
  testInterrupt=0;
  //Serial.println(analogRead(A0));

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
  else{
    // Rainbow Wheel
    if(blinkMode>1 && !testInterrupt){
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
          delay(40);
        }
      }
    }
  }
}