#include <FastLED.h>

#define BRIGHTNESS 60   // Set brightness (0-255)
#define LED_TYPE WS2811 // Specify the LED type
#define COLOR_ORDER BRG // Set the color order (BRG is typical for WS2811)

// Configuration for strips
#define NUM_STRIPS 23

// Define the number of LEDs for each strip, their radii, and their data pins
int numLedsPerStrip[NUM_STRIPS] = {36, 36, 36, 32, 32, 30, 32, 30, 32, 16, 24, 20, 28, 20, 20, 24, 20, 28, 16, 24, 20, 28, 16}; // Adjust for your setup

float stripRadii[NUM_STRIPS] = {9, 10, 10, 20, 21, 25, 21, 28, 21, 41, 35, 40, 31, 38, 35, 38, 39, 33, 45, 29, 42, 29, 35};                     // Radii for each strip (in cm)
float stripAngles[NUM_STRIPS] = {90, 332, 221, 171, 292, 262, 26, 71, 120, 252, 278, 304, 330, 350, 429, 96, 131, 149, 169, 194, 209, 230, 12}; // Angles for each strip (degrees)
int dataPins[NUM_STRIPS] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};                        // Data pins for each strip

// Define LED arrays for each strip
CRGB *leds[NUM_STRIPS];

// Fire simulation parameters
#define FireAnimationSpeed 30

#define FireCooldownBandTopMin 20
#define FireCooldownBandTopMax 30

#define FireCooldownBandPercentage 0.6 // 0 - 1

#define FireCooldownMin 14
#define FireCooldownMax 18

#define SparkStartingHeatMin 190
#define SparkStartingHeatMax 200

#define BaseHeatTransferPercentageMin 0.03

#define CenterSparkRate 200 // lower value is less chance 0 - 255
#define RandomOtherSpark 60 // lower value is less chance 0 - 255

#define MAX_DISTANCE 40.0 // Maximum distance for heat transfer

float maxRadius;

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
    static byte **heat = allocateHeatArray();

    // Center fuel
    if (random8() < CenterSparkRate)
    {
        int randomLEDIndex_0 = random(0, 4);
        int randomLEDIndex_1 = random(0, 4);
        int randomLEDIndex_2 = random(0, 4);

        heat[0][randomLEDIndex_0] = qadd8(heat[0][randomLEDIndex_0], random8(SparkStartingHeatMin, SparkStartingHeatMax));
        heat[1][randomLEDIndex_1] = qadd8(heat[1][randomLEDIndex_1], random8(SparkStartingHeatMin, SparkStartingHeatMax));
        heat[2][randomLEDIndex_2] = qadd8(heat[2][randomLEDIndex_2], random8(SparkStartingHeatMin, SparkStartingHeatMax));
    }

    // Random spark somewhere else
    if (random8() < RandomOtherSpark)
    {
        int randomStrip = random(0, NUM_STRIPS);
        int ledSpark = random(0, 5);
        heat[randomStrip][ledSpark] = qadd8(heat[randomStrip][ledSpark], random8(SparkStartingHeatMin, SparkStartingHeatMax));
    }

    // Update fire simulation with heat transfer
    for (int strip = 0; strip < NUM_STRIPS; strip++)
    {
        fireEffect(strip, heat);
    }

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
            heat[stripIndex][i] = qsub8(heat[stripIndex][i], random8(FireCooldownBandTopMin, FireCooldownBandTopMax));
        }
        else
        {
            heat[stripIndex][i] = qsub8(heat[stripIndex][i], random8(FireCooldownMin, FireCooldownMax));
        }
    }

    // Heat drifts upward and diffuses within the strip
    for (int i = numLeds - 1; i >= 1; i--)
    {
        heat[stripIndex][i] = (heat[stripIndex][i - 1] + heat[stripIndex][i - 1]) / 2;
    }

    // Simplified heat transfer logic between strips
    for (int otherStrip = 0; otherStrip < NUM_STRIPS; otherStrip++)
    {
        if (otherStrip == stripIndex)
            continue; // Skip self

        // Skip heat transfer if distance exceeds the maximum allowed
        float dist = calculateDistance(stripIndex, otherStrip);
        if (dist >= MAX_DISTANCE)
            continue;

        // Simplify by transferring heat only to the first few LEDs of the other strip
        int transferLimit = min(numLedsPerStrip[stripIndex], numLedsPerStrip[otherStrip]) / 2;

        // Transfer heat for the limited range of LEDs
        for (int i = 0; i < transferLimit; i++)
        {
            float transferFactor = (stripRadii[otherStrip] / maxRadius);
            byte transferAmount = heat[stripIndex][i] * BaseHeatTransferPercentageMin * transferFactor;

            // Add heat to the other strip
            heat[otherStrip][i] = qadd8(heat[otherStrip][i], transferAmount);
        }
    }

    // Map heat to colors
    for (int i = 0; i < numLeds; i++)
    {
        leds[stripIndex][i] = HeatColor(heat[stripIndex][i]);
    }
}

float calculateDistance(int strip1, int strip2)
{
    // Calculate positions in 2D space for each strip's center
    float angle1 = radians(stripAngles[strip1]);
    float angle2 = radians(stripAngles[strip2]);

    float x1 = stripRadii[strip1] * cos(angle1);
    float y1 = stripRadii[strip1] * sin(angle1);

    float x2 = stripRadii[strip2] * cos(angle2);
    float y2 = stripRadii[strip2] * sin(angle2);

    // Euclidean distance between strip centers
    return sqrt(sq(x2 - x1) + sq(y2 - y1));
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

    if (temperature > 128)
    {
        color.r = 255;
        color.g = 255;
        color.b = temperature - 128;
    }
    else if (temperature > 64)
    {
        color.r = 255;
        color.g = temperature - 64;
    }
    else
    {
        color.r = temperature;
    }

    return color;
}
