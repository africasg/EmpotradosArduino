#include <Adafruit_NeoPixel.h>

#define LED_PIN 14       
#define NUM_LEDS 64      

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin();
  leds.setBrightness(50); 
  leds.show();
}

void loop() {
  fillColor(255, 0, 0);
  delay(800);

  fillColor(0, 255, 0);
  delay(800);

  fillColor(0, 0, 255);
  delay(800);

  fillColor(255, 255, 0);
  delay(800);

 
  rainbow();
}

void fillColor(int r, int g, int b) {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i, leds.Color(r, g, b));
  }
  leds.show();
}

void rainbow() {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<leds.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / leds.numPixels());
      leds.setPixelColor(i, leds.gamma32(leds.ColorHSV(pixelHue)));
    }
    leds.show();
    delay(20);
  }
}
