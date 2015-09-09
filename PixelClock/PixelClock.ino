#include <Adafruit_NeoPixel.h>


//led stuff
#define PIN            6
#define NUMPIXELS      60 
// two pixelss connected in parallel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

byte maindiv = 1, backdiv = 64; // divide colors to make them dimmer

byte seconds = 56,minutes = 50,hours = 5;
byte j; // color cycle thing

void loop() {
  delay(1000);
  seconds++;
  if (seconds > 59) {
    seconds = 0;
    minutes++;
  }
  if (minutes > 59) {
    minutes = 0;
    hours++;
  }
  if (hours > 11) {
    hours = 0;
  }
  j--;
  uint32_t color;
  for (byte i = 0; i < 60; i++) {
    byte red = 0,grn = 0,blu = 0;
    if (seconds == i) {
      blu = 255;
      grn = 128;
      red = 128;
    }
    if (minutes == i) {
      grn = 255;
    }
    if ((hours * 5 + minutes/12) == i) {
      red = 255;
    }
    color = pixels.Color(red/maindiv,grn/maindiv,blu/maindiv);
    if (!color) color = Wheel(((i * 256 / pixels.numPixels()) + j) & 255);
    pixels.setPixelColor(59-i,color);  // i mounted my strip backwards
  }
  pixels.show();
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color((255 - WheelPos * 3)/backdiv, 0, (WheelPos * 3)/backdiv);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, (WheelPos * 3)/backdiv, (255 - WheelPos * 3)/backdiv);
  } else {
   WheelPos -= 170;
   return pixels.Color((WheelPos * 3)/backdiv, (255 - WheelPos * 3)/backdiv, 0);
  }
}
