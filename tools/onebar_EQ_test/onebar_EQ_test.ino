#include <Adafruit_NeoPixel.h>
#define PIN 0

int ttalpix = 95; // number of pixel
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
  getsample();
  if (val == 0){
    for (a = 0; a < ttalpix; a++){
    strip.setPixelColor(a, 0, 0, 0);
    }
    strip.show();
  }else if (val > 0 && val <= ttalpix){
    for (a = 0; a < val; a++){
      if (g < 250){g += (250 / ttalpix ) * 2;}
      if (g >= 250){g = 250; b += (250 / ttalpix ) * 2; r -= (250 / ttalpix ) * 2;}
      if (b >= 250 && g >= 250){b = 250; r -= (250 / ttalpix ) * 2; g -= (250 / ttalpix ) * 2;}
      if (r <= 0){r = 0;}
    strip.setPixelColor(a, r, g, b);
    }
    strip.show();
  }
  delay(delaytime);
  for (a = 0; a < ttalpix; a++){
  strip.setPixelColor(a, 0, 0, 0);
  r = 200;
  g = 0;
  b = 0;
  s = 0;
  }
}

void getsample(){
  for(int i = 0; i < sampnum; i++){
  if (val <= int(analogRead(music))){
    val = analogRead(music);}
  }
  if (val >= 150){val = 150;}
  val = map(val, 0, 150, 0, ttalpix);
}
