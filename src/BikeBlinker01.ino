// #include <Adafruit_NeoPixel.h>
// #ifdef __AVR__
// #include <avr/power.h>
// #endif
//
// #define PIN 14
// #define PIN2 15
//
// // Parameter 1 = number of pixels in leftstrip
// // Parameter 2 = Arduino pin number (most are valid)
// // Parameter 3 = pixel type flags, add together as needed:
// Adafruit_NeoPixel leftstrip = Adafruit_NeoPixel(15, PIN, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel rightstrip = Adafruit_NeoPixel(15, PIN2, NEO_GRB + NEO_KHZ800);
//
//
// void setup() {
//   Serial.begin(9600);
//   Serial.println("qui");
//   pinMode(PIN, OUTPUT);
//   pinMode(PIN2, OUTPUT);
//
//   pinMode(4, INPUT_PULLUP); //Pushbutton 1
//   pinMode(5, INPUT_PULLUP); //Pushbutton 2
//   pinMode(0, OUTPUT);
//
//   leftstrip.begin();
//   leftstrip.show(); // Initialize all pixels to 'off'
//   rightstrip.begin();
//   rightstrip.show(); // Initialize all pixels to 'off'
//   delay(1); //delays needed to keep ESP2866 stable, not needed for other boards
//   Serial.println("Qui");
// }
//
// void loop() {
//   Serial.println(analogRead(A0));
//   delay(1); //delays needed to keep ESP2866 stable, not needed for other boards
//   digitalWrite(0, LOW);
//   if (analogRead(A0) < 300) {
//     //this mode is traffic indicator lights
//     colorSet(0);
//     digitalWrite(0, LOW);
//     Serial.println(digitalRead(5));
//     //main program option: push buttons for blinkers
//     if (digitalRead(5) == LOW ) {
//       yellowBlink(leftstrip, 800);
//     }
//
//     if (digitalRead(4) == LOW) {
//       yellowBlink(rightstrip, 800);
//     }
//   }
//
//
//   if (analogRead(A0) > 812) {
//
//     if (digitalRead(4) == LOW) {
//
//       digitalWrite(13, HIGH);
//       delay(100);
//       digitalWrite(13, LOW);
//       colorWipe2( 150);
//
//       digitalWrite(0, LOW);
//       digitalWrite(13, LOW);
//     }
//     if (digitalRead(5) == LOW) {
//       softGlow(40);
//
//     }
//   }
//
//   if (analogRead(A0) > 300 && analogRead(A0) < 810) {
//     if (digitalRead(4) == LOW) {
//       digitalWrite(13, HIGH);
//       delay(100);
//       digitalWrite(13, LOW);
//       delay(100);
//       rainbowCycle(50);
//       digitalWrite(0, LOW);
//     }
//   }
// }
