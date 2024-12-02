#include <FastLED.h>

#define BRIGHTNESS 10     // Set brightness (0-255)
#define LED_TYPE WS2811   // Specify the LED type
#define COLOR_ORDER BRG   // Set the color order (BRG is typical for WS2811)

// Configuration for strips
#define NUM_STRIPS 4

// Define the number of LEDs for each strip and their radii
int numLedsPerStrip[NUM_STRIPS] = {15, 20, 18, 25};  // Adjust for your setup
float stripRadii[NUM_STRIPS] = {10.0, 20.0, 30.0, 40.0}; // Radii for each strip (in cm)
float stripAngles[NUM_STRIPS] = {0, 90, 180, 270};   // Angles for each strip (degrees)

// Define LED arrays for each strip
CRGB* leds[NUM_STRIPS];

// Fire simulation parameters
#define FireAnimationSpeed 200
#define FireCooldownMin 8
#define FireCooldownMax 45
#define SparkStartingHeatMin 130
#define SparkStartingHeatMax 150

#define CenterSparkRate 120
#define MAX_DISTANCE 10.0 // Maximum distance for heat transfer

void setup() {
  // Allocate LED arrays dynamically and initialize strips
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    leds[strip] = new CRGB[numLedsPerStrip[strip]];
    switch (strip) {
      case 0:
        FastLED.addLeds<LED_TYPE, 7, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
        break;
      case 1:
        FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
        break;
      case 2:
        FastLED.addLeds<LED_TYPE, 5, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
        break;
      case 3:
        FastLED.addLeds<LED_TYPE, 4, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
        break;
    }
  }

  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  static byte** heat = allocateHeatArray();

  // Ignite sparks on center strips (strip 1 and 2 in this example)
  for (int strip = 1; strip <= 2; strip++) {
    if (random8() < CenterSparkRate) {
      int sparkIndex = random8(5); // Sparks at the bottom LEDs
      heat[strip][sparkIndex] = qadd8(heat[strip][sparkIndex], random8(SparkStartingHeatMin, SparkStartingHeatMax));
    }
  }

  // Update fire simulation with heat transfer
  for (int strip = 0; strip < NUM_STRIPS; strip++) {
    fireEffect(strip, heat);
  }

  // Display LEDs
  FastLED.show();
  delay(FireAnimationSpeed);
}

void fireEffect(int stripIndex, byte** heat) {
  int numLeds = numLedsPerStrip[stripIndex];

  // Cool down each LED
  for (int i = 0; i < numLeds; i++) {
    heat[stripIndex][i] = qsub8(heat[stripIndex][i], random8(FireCooldownMin, FireCooldownMax));
  }

  // Heat drifts upward and diffuses within the strip
  for (int i = numLeds - 1; i >= 2; i--) {
    heat[stripIndex][i] = (heat[stripIndex][i - 1] + heat[stripIndex][i - 2] + heat[stripIndex][i - 2]) / 3;
  }

  // Heat transfer between strips based on distances
  for (int otherStrip = 0; otherStrip < NUM_STRIPS; otherStrip++) {
    if (otherStrip == stripIndex) continue; // Skip self

    for (int i = 0; i < numLeds; i++) {
      for (int j = 0; j < numLedsPerStrip[otherStrip]; j++) {
        float dist = calculateDistance(stripIndex, i, otherStrip, j);
        if (dist < MAX_DISTANCE) {
          byte transferAmount = heat[otherStrip][j] / 10; // Scale transfer based on distance
          heat[stripIndex][i] = qadd8(heat[stripIndex][i], transferAmount);
        }
      }
    }
  }

  // Map heat to colors
  for (int i = 0; i < numLeds; i++) {
    leds[stripIndex][i] = HeatColor(heat[stripIndex][i]);
  }
}

float calculateDistance(int strip1, int led1, int strip2, int led2) {
  // Calculate positions in 2D space for each LED
  float angle1 = radians(stripAngles[strip1]);
  float angle2 = radians(stripAngles[strip2]);

  float x1 = stripRadii[strip1] * cos(angle1) + led1 * (stripRadii[strip1] / numLedsPerStrip[strip1]);
  float y1 = stripRadii[strip1] * sin(angle1);

  float x2 = stripRadii[strip2] * cos(angle2) + led2 * (stripRadii[strip2] / numLedsPerStrip[strip2]);
  float y2 = stripRadii[strip2] * sin(angle2);

  // Euclidean distance
  return sqrt(sq(x2 - x1) + sq(y2 - y1));
}

byte** allocateHeatArray() {
  byte** heat = new byte*[NUM_STRIPS];
  for (int i = 0; i < NUM_STRIPS; i++) {
    heat[i] = new byte[numLedsPerStrip[i]];
    memset(heat[i], 0, numLedsPerStrip[i]); // Initialize to zero
  }
  return heat;
}

CRGB HeatColor(byte temperature) {
  // Map heat values to RGB colors
  CRGB color = CRGB::Black;

  if (temperature > 128) {
    color.r = 255;
    color.g = 255;
    color.b = temperature - 128;
  } else if (temperature > 64) {
    color.r = 255;
    color.g = temperature - 64;
  } else {
    color.r = temperature;
  }

  return color;
}
