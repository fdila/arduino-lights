




void colorSet(uint32_t c) {
  for (uint16_t i = 0; i < leftstrip.numPixels(); i++) {
    leftstrip.setPixelColor(i, c);
    leftstrip.show();
    rightstrip.setPixelColor(i, c);
    rightstrip.show();
  }
}



