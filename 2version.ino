#include <Adafruit_NeoPixel.h>

#define LED_PIN 4
#define NUM_LEDS 64 
#define PIR_PIN 5

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  leds.begin();
  leds.setBrightness(30); 
  leds.show();
}

void loop() {
  int mov = digitalRead(PIR_PIN);

  if (mov == 1) {
    Serial.println("Movimiento detectado");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixelColor(i, leds.Color(255, 150, 50)); 
    }
  } else {
    Serial.println("Nada...");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixelColor(i, 0); 
    }
  }

  leds.show();
  delay(200);
}
