#include <FastLED.h>

#define BRIGHTNESS 10   // Set brightness (0-255)
#define LED_TYPE WS2811 // Specify the LED type
#define COLOR_ORDER BRG // Set the color order (BRG is typical for WS2811)

// Configuration for strips
#define NUM_STRIPS 23

// Define the number of LEDs for each strip, their radii, and their data pins
int numLedsPerStrip[NUM_STRIPS] = {36, 36, 36, 32, 32, 30, 32, 30, 32, 16, 24, 20, 28, 20, 20, 24, 20, 28, 16, 24, 20, 28, 16}; // Adjust for your setup

float stripRadii[NUM_STRIPS] = {9, 10, 10, 20, 21, 25, 21, 28, 21, 41, 35, 40, 31, 38, 35, 38, 39, 33, 45, 29, 42, 29, 35}; // Radii for each strip (in cm)
int dataPins[NUM_STRIPS] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};    // Data pins for each strip

// Define LED arrays for each strip
CRGB *leds[NUM_STRIPS];

// Fire simulation parameters
#define FireAnimationSpeed 30

// Cooldown
#define FireCooldownBandTopMin 15
#define FireCooldownBandTopMax 20

#define FireCooldownBandPercentage 0.9 // 0 - 1
#define FireCooldownBandPercentage 0.9 // 0 - 1

#define FireCooldownMin 5
#define FireCooldownMax 10

#define FireCooldownRadiusMin 14
#define FireCooldownRadiusMax 18

// Sparks
#define SparkStartingHeatMin 190
#define SparkStartingHeatMax 200

#define Band1SparkRate 5      // lower value is less chance 0 - 255
#define Band2SparkRate 120      // lower value is less chance 0 - 255
#define Band3SparkRate 60       // lower value is less chance 0 - 255
#define RandomOtherSparkRate 60 // lower value is less chance 0 - 255

#define TIMER_INTERVAL 500

float maxRadius;
unsigned long previousMillis = 0;

void setup()
{
    // Allocate LED arrays dynamically and initialize strips
    for (int strip = 0; strip < NUM_STRIPS; strip++)
    {
        leds[strip] = new CRGB[numLedsPerStrip[strip]];
        // Initialize each strip with its corresponding data pin and LED count
        switch (dataPins[strip])
        {
        case 22:
            FastLED.addLeds<LED_TYPE, 22, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 23:
            FastLED.addLeds<LED_TYPE, 23, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 24:
            FastLED.addLeds<LED_TYPE, 24, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 25:
            FastLED.addLeds<LED_TYPE, 25, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 26:
            FastLED.addLeds<LED_TYPE, 26, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 27:
            FastLED.addLeds<LED_TYPE, 27, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 28:
            FastLED.addLeds<LED_TYPE, 28, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 29:
            FastLED.addLeds<LED_TYPE, 29, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 30:
            FastLED.addLeds<LED_TYPE, 30, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 31:
            FastLED.addLeds<LED_TYPE, 31, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 32:
            FastLED.addLeds<LED_TYPE, 32, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 33:
            FastLED.addLeds<LED_TYPE, 33, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 34:
            FastLED.addLeds<LED_TYPE, 34, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 35:
            FastLED.addLeds<LED_TYPE, 35, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 36:
            FastLED.addLeds<LED_TYPE, 36, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 37:
            FastLED.addLeds<LED_TYPE, 37, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 38:
            FastLED.addLeds<LED_TYPE, 38, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 39:
            FastLED.addLeds<LED_TYPE, 39, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 40:
            FastLED.addLeds<LED_TYPE, 40, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 41:
            FastLED.addLeds<LED_TYPE, 41, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 42:
            FastLED.addLeds<LED_TYPE, 42, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 43:
            FastLED.addLeds<LED_TYPE, 43, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        case 44:
            FastLED.addLeds<LED_TYPE, 44, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
            break;
        }
    }

    findMaxRadius();

    FastLED.clear();
    FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
    unsigned long currentMillis = millis();
    static byte **heat = allocateHeatArray();

//    // Random spark somewhere else
//    if (random8() < RandomOtherSparkRate)
//    {
//        int randomStrip = random(0, NUM_STRIPS);
//        int ledSpark = random(0, 5);
//        heat[randomStrip][ledSpark] = qadd8(heat[randomStrip][ledSpark], random8(SparkStartingHeatMin, SparkStartingHeatMax));
//    }

//    // Update fire simulation with heat transfer
//    for (int strip = 0; strip < NUM_STRIPS; strip++)
//    {
//        if (random8() < Band1SparkRate)
//        {
//            BandSparks(heat, strip, 0, 11);
//        }
//
//        if (random8() < Band2SparkRate)
//        {
//            BandSparks(heat, strip, 12, 32);
//        }
//
//        if (random8() < Band3SparkRate)
//        {
//            BandSparks(heat, strip, 32, 46);
//        }
//
//        //fireEffect(strip, heat);
//    }

    if (currentMillis - previousMillis >= TIMER_INTERVAL) {
        previousMillis = currentMillis; // Update the last timer event time

        // Perform the timed operation
        BandSparks(heat, 0, 0, 11);
    }
    fireEffect(0, heat);

    // Display LEDs
    FastLED.show();
    delay(FireAnimationSpeed);
}

void fireEffect(int stripIndex, byte **heat)
{
    int numLeds = numLedsPerStrip[stripIndex];

    int coolDownTopBand = numLeds * FireCooldownBandPercentage;

    // Cool down each LED
    for (int i = numLeds - 1; i >= 0; i--)
    {
        if (i >= coolDownTopBand)
        {
            heat[stripIndex][i] = qsub8(heat[stripIndex][i], random(FireCooldownBandTopMin,FireCooldownBandTopMax) * (1-i/numLeds));
        }
        else
        {
            heat[stripIndex][i] = qsub8(heat[stripIndex][i], random(FireCooldownMin,FireCooldownMax) * (1-i/numLeds));
        }
    }

    // Heat drifts upward and diffuses within the strip
    for (int i = numLeds - 1; i >= 1; i--)
    {
        heat[stripIndex][i] = (heat[stripIndex][i - 1] + heat[stripIndex][i - 1]) / 2;
    }

    // Map heat to colors
    for (int i = 0; i < numLeds; i++)
    {
        leds[stripIndex][i] = MyHeatColor(heat[stripIndex][i]);
    }
}

void BandSparks(byte **heat, int stripIndex, float bandRaduisMin, float bandRaduisMax)
{
    if (stripRadii[stripIndex] < bandRaduisMax && stripRadii[stripIndex] > bandRaduisMin)
    {
        int randomLEDIndex = random(0, 0);
        heat[stripIndex][randomLEDIndex] = SparkStartingHeatMin;
    }
}

byte **allocateHeatArray()
{
    byte **heat = new byte *[NUM_STRIPS];
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        heat[i] = new byte[numLedsPerStrip[i]];
        memset(heat[i], 0, numLedsPerStrip[i]); // Initialize to zero
    }
    return heat;
}

void findMaxRadius()
{
    maxRadius = stripRadii[0]; // Initialize to the first element of the array

    for (int i = 1; i < NUM_STRIPS; i++)
    {
        if (stripRadii[i] > maxRadius)
        {
            maxRadius = stripRadii[i];
        }
    }
}

CRGB MyHeatColor(byte temperature)
{
    // Map heat values to RGB colors
    CRGB color = CRGB::Black;

    if (temperature > 200)
    {
        color.r = 255;
        color.g = 255;
        color.b = temperature - 128;
    }
    else if (temperature > 128)
    {
        color.r = 255;
        color.g = temperature - 128;
    }
    else
    {
        color.r = temperature;
    }

    return color;
}
