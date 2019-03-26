
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < leftstrip.numPixels(); i++) {
      leftstrip.setPixelColor(i, Wheel((i + j) & 255));
    }
    leftstrip.show();
    delay(wait);
  }
}



//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 3) {
        leftstrip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      leftstrip.show();

      delay(wait);

      for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 3) {
        leftstrip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}




//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 3) {
        leftstrip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      leftstrip.show();

      delay(wait);

      for (uint16_t i = 0; i < leftstrip.numPixels(); i = i + 3) {
        leftstrip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}




// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < leftstrip.numPixels(); i++) {
      leftstrip.setPixelColor(i, Wheel(((i * 256 / leftstrip.numPixels()) + j) & 255));
      rightstrip.setPixelColor(i, Wheel(((i * 256 / rightstrip.numPixels()) + j) & 255));

    }
    leftstrip.show();
    rightstrip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
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
