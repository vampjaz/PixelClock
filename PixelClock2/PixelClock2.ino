#include <Adafruit_NeoPixel.h>

//led stuff
#define PIN            6
#define NUMPIXELS      60 

#define SPEED          1000

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte red[NUMPIXELS];
byte green[NUMPIXELS];
byte blue[NUMPIXELS];


byte maindiv = 1, backdiv = 32; // divide colors to make them dimmer

byte seconds = 56,minutes = 38,hours = 9;

// for fading:
byte cseconds, cminutes, chours;

long lastmillis;

void setup() {
  pixels.begin();
  lastmillis = millis() + SPEED;
}

void loop() {
  delay(10);
  if (lastmillis < millis()) {
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
    lastmillis = millis() + SPEED;
  }
  cseconds = map(constrain(lastmillis-millis(),0,SPEED),SPEED,0,0,255);
  cminutes = map(seconds,0,60,0,255);
  chours   = map((minutes*5)%60,0,60,0,255);

  fadeColor(seconds,128,128,255,cseconds);
  fadeColor(minutes,0,255,0,cminutes);
  fadeColor(hours*5+minutes/12,255,0,0,chours);
  
  for (byte i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(59-i,red[i],green[i],blue[i]);
    red[i] = 0; green[i] = 0; blue[i] = 0;
  }
  pixels.show();
}

void fadeColor(byte pixel, byte rd, byte gn, byte bl, byte fade) {
  // fades from one pixel to the next
  byte pixel2 = (pixel + 1) % NUMPIXELS;
  
  red[pixel2] = (red[pixel2] + map(rd,0,255,0,fade))/2;
  green[pixel2] = (green[pixel2] + map(gn,0,255,0,fade))/2;
  blue[pixel2] = (blue[pixel2] + map(bl,0,255,0,fade))/2;
  
  fade = 255-fade;
  red[pixel] = (red[pixel] + map(rd,0,255,0,fade))/2;
  green[pixel] = (green[pixel] + map(gn,0,255,0,fade))/2;
  blue[pixel] = (blue[pixel] + map(bl,0,255,0,fade))/2;
}

