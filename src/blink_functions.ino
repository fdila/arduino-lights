

void yellowBlink(Adafruit_NeoPixel &strip, int wait) {
  for (int k = 0; k < 8; k++) {
    for (uint16_t i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 255, 110, 5); //turn every  pixel on

      //setpixelcolor syntax: (pixelnummer,R,G,B);
      digitalWrite(0, HIGH);
      digitalWrite(13, HIGH);
    }
    strip.show();
    delay(wait);
    for (uint16_t i = 0; i < strip.numPixels(); i = i + 1) {
      strip.setPixelColor(i, 0, 0, 0);    //turn every pixel off
      digitalWrite(0, LOW);
      digitalWrite(13, LOW);
    }
    strip.show();
    delay(wait);

  }
}




// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
    leftstrip.setPixelColor(i, c);
    leftstrip.show();
    delay(wait);
  }
}

// Fill the dots one after the other with a color
void colorWipe2( uint8_t wait) {
  for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
    leftstrip.setPixelColor(i, 255, 255, 255);
    leftstrip.setPixelColor(i - 1, 0, 0, 0);
    leftstrip.show();
    rightstrip.setPixelColor(i, 255, 255, 255);
    rightstrip.setPixelColor(i - 1, 0, 0, 0);
    rightstrip.show();

    delay(wait);
  }
}
// Fill the dots one after the other with a color
void colorWipeRed( uint8_t wait) {
  for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
    leftstrip.setPixelColor(i, 50, 0, 0);
    leftstrip.setPixelColor(i - 1, 125, 0, 0);
    leftstrip.setPixelColor(i - 2, 255, 0, 0);
    leftstrip.setPixelColor(i - 3, 120, 0, 0);
    leftstrip.setPixelColor(i - 4, 50, 0, 0);
    leftstrip.setPixelColor(i - 5, 0, 0, 0);
    leftstrip.show();
    rightstrip.setPixelColor(i, 50, 0, 0);
    rightstrip.setPixelColor(i - 1, 125, 0, 0);
    rightstrip.setPixelColor(i - 2, 255, 0, 0);
    rightstrip.setPixelColor(i - 3, 125, 0, 0);
    rightstrip.setPixelColor(i - 4, 50, 0, 0);
    rightstrip.setPixelColor(i - 5, 0, 0, 0);
    rightstrip.show();

    delay(wait);
  }
    for (uint16_t i = leftstrip.numPixels()-13; i >-4; i--) {
    leftstrip.setPixelColor(i, 50, 0, 0);
    leftstrip.setPixelColor(i + 1, 125, 0, 0);
    leftstrip.setPixelColor(i + 2, 255, 0, 0);
    leftstrip.setPixelColor(i + 3, 120, 0, 0);
    leftstrip.setPixelColor(i + 4, 50, 0, 0);
    leftstrip.setPixelColor(i + 5, 0, 0, 0);
    leftstrip.show();
    rightstrip.setPixelColor(i, 50, 0, 0);
    rightstrip.setPixelColor(i + 1, 125, 0, 0);
    rightstrip.setPixelColor(i + 2, 255, 0, 0);
    rightstrip.setPixelColor(i + 3, 125, 0, 0);
    rightstrip.setPixelColor(i + 4, 50, 0, 0);
    rightstrip.setPixelColor(i + 5, 0, 0, 0);
    rightstrip.show();

    delay(wait);
  }

}
