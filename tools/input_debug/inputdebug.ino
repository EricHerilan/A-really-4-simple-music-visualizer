#include <Adafruit_NeoPixel.h>
#define PIN 0

int ttalpix = 100; // number of pixel
int val, pinpl, a;
int n = 0;
int r, g, b, s;
int music = 2;
int delaytime = 50;
int sampnum = 100; //anasample times
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ttalpix, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  s = 1;
  g = 10;
  r = 0;
  b = 100;
  strip.begin();
  for (a = 0; a < ttalpix; a++){
  strip.setPixelColor(a, r, g, b);
  if (g >= 250){s = -1;}
  else if (g <= 0){s = 1;}
  g += 10 * s;
  strip.show();
  delay(delaytime);
  }
  for (a = 0; a < ttalpix; a++){
  strip.setPixelColor(a, 0, 0, 0);
  strip.show();
  delay(delaytime);
  }
  s = 0;
}

void loop() {
  if (analogRead(1) > 50){strip.setPixelColor(0, 0, 0, 120);}
  if (analogRead(2) > 50){strip.setPixelColor(1, 0, 0, 120);}
  if (analogRead(3) > 50){strip.setPixelColor(2, 0, 0, 120);}
  if (analogRead(4) > 50){strip.setPixelColor(3, 0, 0, 120);}
  if (analogRead(5) > 50){strip.setPixelColor(4, 0, 0, 120);}
  strip.show();
  delay(10);
  for (a = 0; a < ttalpix; a++){
  strip.setPixelColor(a, 0, 0, 0);
  }
  strip.show();
}
