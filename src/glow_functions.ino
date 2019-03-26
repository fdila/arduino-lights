
void softGlowRed(int wait) {
int bval =20;
int amp=70;
  for (uint16_t h = 0; h < amp; h = h + 1) {
    for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 1) {
      leftstrip.setPixelColor(i, bval + h, 0, 0); //turn every  pixel on
      rightstrip.setPixelColor(i, bval + h, 0, 0); //turn every  pixel on

      //setpixelcolor syntax: (pixelnummer,R,G,B);
      digitalWrite(0, HIGH);
      digitalWrite(13, HIGH);
    }
    leftstrip.show();
    rightstrip.show();
    delay(50);
    Serial.println("qui");
  }

  for (uint16_t h = 0; h < amp; h = h + 1) {
    for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 1) {
      leftstrip.setPixelColor(i, bval+amp - h, 0, 0); //turn every  pixel on
      rightstrip.setPixelColor(i, bval+amp - h, 0, 0); //turn every  pixel on

      //setpixelcolor syntax: (pixelnummer,R,G,B);
      digitalWrite(0, HIGH);
      digitalWrite(13, HIGH);
    }
    leftstrip.show();
    rightstrip.show();
    delay(50);
  }

}




void softGlow(int wait) {
  int bval = 80;
  for (uint16_t h = 0; h < 55; h = h + 1) {
    for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 1) {
      leftstrip.setPixelColor(i, bval + h, bval + h, bval + h); //turn every  pixel on
      rightstrip.setPixelColor(i, bval + h, bval + h, bval + h); //turn every  pixel on

      //setpixelcolor syntax: (pixelnummer,R,G,B);
      digitalWrite(0, HIGH);
      digitalWrite(13, HIGH);
    }
    leftstrip.show();
    rightstrip.show();
    delay(wait);

  }

}
