#include <Adafruit_NeoPixel.h>

//led stuff
#define PIN            6
#define NUMPIXELS      60 

#define FADE 3
// two pixelss connected in parallel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

byte add = 0;

void loop() {
  for (byte i = 0; i < NUMPIXELS; i++) {
    uint32_t pcolor = pixels.getPixelColor(i);
    uint8_t red,green,blue;
    blue = pcolor;
    green = pcolor>>8;
    red = pcolor>>16;
    if (red>FADE) {
      red-=FADE;
    } else {
      red = 0;
    }
    if (green>FADE) {
      green-=FADE;
    } else {
      green = 0;
    }
    if (blue>FADE) {
      blue-=FADE;
    } else {
      blue = 0;
    }
    pixels.setPixelColor(i,red,green,blue);
  }

  add++;
  if (add > 1) {
    add = 0;
    pixels.setPixelColor(random(NUMPIXELS),Wheel(random(0xff)));
  }

  pixels.show();
  delay(30);
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
