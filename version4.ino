#include <Adafruit_NeoPixel.h>


#define LED_PIN 4
#define NUM_LEDS 64
#define BUTTON_PIN 0  
#define PIR_PIN 5     


Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


int efecto = 0;
bool lastButton = HIGH;
unsigned long debounce = 0;


void setup() {
  Serial.begin(115200);


  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIR_PIN, INPUT);


  leds.begin();
  leds.setBrightness(40);
  leds.show();


  Serial.println("Sistema listo: BOOT cambia efectos, PIR muestra smiley.");
}


void loop() {



  bool buttonState = digitalRead(BUTTON_PIN);


  if (buttonState == LOW && lastButton == HIGH && millis() - debounce > 250) {
    efecto++;
    if (efecto > 7) efecto = 0;
    Serial.print("Efecto cambiado a: ");
    Serial.println(efecto);
    debounce = millis();
  }
  lastButton = buttonState;



  int mov = digitalRead(PIR_PIN);


  if (mov == HIGH) {
    mostrarSmiley();
    return;   // NO se ejecutan efectos, se muestra smiley
  }


  // ==========================
  //   SIN MOVIMIENTO → efecto normal
  // ==========================
  switch (efecto) {
    case 0: efectoRojo(); break;
    case 1: efectoRespirar(); break;
    case 2: efectoArcoiris(); break;
    case 3: efectoOla(); break;
    case 4: efectoFuego(); break;
    case 5: efectoChispas(); break;
    case 6: efectoBarrido(); break;
    case 7: efectoMeteoro(); break;
  }


  delay(20);
}



void mostrarSmiley() {
  uint32_t Y = leds.Color(255, 200, 0); // amarillo
  uint32_t N = leds.Color(0, 0, 0);     // apagado


  uint32_t smiley[64] = {
    N, N, Y, N, N, Y, N, N,
    N, N, Y, N, N, Y, N, N,
    N, N, N, N, N, N, N, N,
    N, Y, N, N, N, N, Y, N,
    N, N, Y, Y, Y, Y, N, N,
    N, N, N, N, N, N, N, N,
    N, N, N, N, N, N, N, N,
    N, N, N, N, N, N, N, N
  };


  for (int i = 0; i < 64; i++) {
    leds.setPixelColor(i, smiley[i]);
  }


  leds.show();
}



void setColor(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS; i++)
    leds.setPixelColor(i, leds.Color(r, g, b));
}


void efectoRojo() { setColor(255, 0, 0); leds.show(); }


void efectoRespirar() {
  static int b = 0, dir = 1;
  b += dir;
  if (b >= 80) dir = -1;
  if (b <= 5) dir = 1;
  leds.setBrightness(b);
  setColor(0, 0, 255);
  leds.show();
}


void efectoArcoiris() {
  static int hue = 0;
  for (int i = 0; i < NUM_LEDS; i++)
    leds.setPixelColor(i, leds.gamma32(leds.ColorHSV((hue + i * 300) % 65536)));
  leds.show();
  hue += 200;
}


void efectoOla() {
  static int base = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    int inten = (sin((i + base) * 0.2) + 1) * 120;
    leds.setPixelColor(i, leds.Color(0, inten, 40));
  }
  leds.show();
  base++;
}


void efectoFuego() {
  for (int i = 0; i < NUM_LEDS; i++)
    leds.setPixelColor(i, leds.Color(random(150,255), random(0,80), 0));
  leds.show();
}


void efectoChispas() {
  for (int i = 0; i < NUM_LEDS; i++) leds.setPixelColor(i, 0);
  for (int i = 0; i < 5; i++)
    leds.setPixelColor(random(NUM_LEDS), leds.Color(255,255,255));
  leds.show();
}


void efectoBarrido() {
  static int pos = 0, dir = 1;
  for (int i = 0; i < NUM_LEDS; i++) leds.setPixelColor(i, 0);
  leds.setPixelColor(pos, leds.Color(255, 0, 0));
  leds.show();
  pos += dir;
  if (pos >= NUM_LEDS - 1 || pos <= 0) dir = -dir;
}


void efectoMeteoro() {
  static int pos = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    uint32_t c = leds.getPixelColor(i);
    leds.setPixelColor(i,
      leds.Color((uint8_t)(c>>16)*0.7, (uint8_t)(c>>8)*0.7, (uint8_t)c*0.7));
  }
  leds.setPixelColor(pos, leds.Color(255,180,50));
  leds.show();
  pos++;
  if (pos >= NUM_LEDS) pos = 0;
}
