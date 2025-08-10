#include <FastLED.h>

#define CAMERA_TRIGGER_PIN 6
#define LED_PIN 8
#define NUM_LEDS 672

CRGB leds[NUM_LEDS];

void colorWipe(CRGB color, int wait);
int calculateAverageBrightness();

void setup() {
  pinMode(CAMERA_TRIGGER_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(9600);
}

void loop() {
  // Trigger the camera
  digitalWrite(CAMERA_TRIGGER_PIN, HIGH);
  delay(200); // Adjust delay as needed to trigger the camera, increased to 200ms
  digitalWrite(CAMERA_TRIGGER_PIN, LOW);

  // Control WS2812B LED strip for illumination
  colorWipe(CRGB::White, 50); // Red color with a speed of 50ms per step
  
  // Calculate average brightness
  int avgBrightness = calculateAverageBrightness();
  Serial.print("Average Brightness: ");
  Serial.println(avgBrightness);

  // Add a delay to prevent flooding the serial monitor
  delay(500);
}

void colorWipe(CRGB color, int wait) {
  for(int i=0; i<NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
    delay(wait);
  }
}

int calculateAverageBrightness() {
  uint32_t totalBrightness = 0;
  for(int i=0; i<NUM_LEDS; i++) {
    totalBrightness += leds[i].getAverageLight();
  }
  return totalBrightness / NUM_LEDS;
}