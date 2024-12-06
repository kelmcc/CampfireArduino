#include <FastLED.h>

#define BRIGHTNESS 100   // Set brightness (0-255)
#define LED_TYPE WS2811 // Specify the LED type
#define COLOR_ORDER BRG // Set the color order (BRG is typical for WS2811)

// Configuration for strips
#define NUM_STRIPS 23

// Define the number of LEDs for each strip, their radii, and their data pins
int numLedsPerStrip[NUM_STRIPS] = {36, 36, 36, 32, 32, 30, 32, 30, 32, 16, 24, 20, 28, 20, 20, 24, 20, 28, 16, 24, 20, 28, 16}; // Adjust for your setup

float stripRadii[NUM_STRIPS] = {9, 10, 10, 20, 21, 25, 21, 28, 21, 41, 35, 40, 31, 38, 35, 38, 39, 31, 45, 29, 42, 29, 35}; // Radii for each strip (in cm)
int dataPins[NUM_STRIPS] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 45, 36, 37, 38, 39, 40, 41, 42, 43, 44};    // Data pins for each strip

// Define LED arrays for each strip
CRGB *leds[NUM_STRIPS];

// Fire simulation parameters
#define FireAnimationSpeed 30

// Cooldown
#define FireCooldownBandTopMin 25
#define FireCooldownBandTopMax 30

#define FireCooldownBandPercentage 0.9 // 0 - 1

#define FireCooldownMin 8
#define FireCooldownMax 10

#define FireCooldownRadiusMin 14
#define FireCooldownRadiusMax 18

// Sparks
#define Band1SparkHeatMin 190
#define Band1SparkHeatMax 200

#define Band2SparkHeatMin 40
#define Band2SparkHeatMax 60

#define Band3SparkHeatMin 30
#define Band3SparkHeatMax 40

#define Band1SparkRate 240 // lower value is less chance 0 - 255
#define Band2SparkRate 120 // lower value is less chance 0 - 255
#define Band3SparkRate 100 // lower value is less chance 0 - 255

#define RandomOtherSparkRate 60 // lower value is less chance 0 - 255

float maxRadius;
int Brightness;
float lastNormDist = 1;

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
            FastLED.addLeds<LED_TYPE, 45, COLOR_ORDER>(leds[strip], numLedsPerStrip[strip]).setCorrection(TypicalLEDStrip);
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
    Serial.begin(9600);
    FastLED.clear();
    FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
    static byte **heat = allocateHeatArray();

    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n'); // Read until newline
      int recieved = data.toInt(); // Convert to float
      lastNormDist = recieved/(float)255;
    }
    
    Brightness = map(lastNormDist, 0, 255, 70, 100); // brightness range 70 - 100 alter

    // Update fire simulation with heat transfer
    for (int strip = 0; strip < NUM_STRIPS; strip++)
    {
        if (random8() < Band1SparkRate)
        {
            BandSparks(heat, strip, 0, 11, random8(Band1SparkHeatMin, Band1SparkHeatMax));
        }

        if (random8() < Band2SparkRate)
        {
            BandSparks(heat, strip, 12, 32, random8(Band2SparkHeatMin, Band2SparkHeatMax));
        }

        if (random8() < Band3SparkRate)
        {
            BandSparks(heat, strip, 32, 46, random8(Band3SparkHeatMin, Band3SparkHeatMax));
        }

        fireEffect(strip, heat);
    }

    FastLED.setBrightness(Brightness);
    
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
            heat[stripIndex][i] = qsub8(heat[stripIndex][i], FireCooldownBandTopMin * (1 - i / numLeds));
        }
        else
        {
            heat[stripIndex][i] = qsub8(heat[stripIndex][i], FireCooldownMin * (1 - i / numLeds));
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

void BandSparks(byte **heat, int stripIndex, float bandRaduisMin, float bandRaduisMax, byte sparkHeat)
{
    if (stripRadii[stripIndex] < bandRaduisMax && stripRadii[stripIndex] > bandRaduisMin)
    {
        int randomLEDIndex = random(0, 2);
        heat[stripIndex][randomLEDIndex] = qadd8(heat[stripIndex][randomLEDIndex], sparkHeat);
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
    temperature = constrain(temperature, 0, 255);

    if (temperature > 200)
    {
        // High temperature: reddish-white
        color.r = 230;
        color.g = temperature - 100;
        color.b = temperature - 200;
    }
    else if (temperature > 128)
    {
        // Mid-high temperature: red to orange
        color.r = 255;
        color.g = map(temperature, 128, 200, 60, 120);
        color.b = 0;
    }
    else if (temperature > 64)
    {
        // Mid temperature: red to yellow
        color.r = 255;
        color.g = map(temperature, 64, 128, 0, 50);
        color.b = 0;
    }
    else
    {
        // Low temperature: dim red
        color.r = temperature;
        color.g = 0;
        color.b = 0;
    }

    return color;
}
