#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 16

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 11

// Define the array of leds
CRGB leds[NUM_LEDS];

// Define sensor pins (potentiometers)
int sensorPin0 = A0;
int sensorPin1 = A1;
int sensorPin2 = A2;
int sensorValue0 = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;

int startColor = 0;
int endColor = 0;

int offsetAngle = 0;

// CHSV startColor(CHSV::Blue);
// CHSV endColor(CHSV::Blue);

int startPos=0;
int endPos=NUM_LEDS-1;

void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
     FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    // FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1829, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1812, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1904, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS2903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2852, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<GS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA106, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GE8822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886_8BIT, DATA_PIN, RGB>(leds, NUM_LEDS);
    // ## Clocked (SPI) types ##
    // FastLED.addLeds<LPD6803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    FastLED.setBrightness(255);
}

void loop() { 
  // first potentiometer is read and mapped to Hue value of first LED segment
  sensorValue0 = map(analogRead(sensorPin0),0,1023,0,255);
  // second potentiometer is read and mapped to "length" of single color segments
  sensorValue1 = map(analogRead(sensorPin1),0,1023,0,125);
  // third potentiometer is read and mapped to Value value of all led segments
  sensorValue2 = map(analogRead(sensorPin2),0,1023,0,510);



  offsetAngle = sensorValue1;
  if (offsetAngle + sensorValue0 > 255) {
    offsetAngle -= 255;
  }

  CHSV startColor = CHSV(0 ,0 ,0);
  CHSV endColor = CHSV(0, 0, 0);

  if (sensorValue2 <= 255) {
    startColor = CHSV(sensorValue0,255,sensorValue2);
    endColor = CHSV(sensorValue0 + offsetAngle,255,sensorValue2);
  }
  else {
    sensorValue2 -= 255;
    startColor = CHSV(sensorValue0,255-sensorValue2,255);
    endColor = CHSV(sensorValue0 + offsetAngle,255-sensorValue2,255);
  }
  

  fill_gradient_HSV(leds, startPos, startColor, endPos, endColor);
  FastLED.show();

  // prints potentiometer values to serial monitors
  // Serial.print("sensor 0 : ");
  // Serial.print(sensorValue0);
  // Serial.print("  sensor 1 : ");
  // Serial.print(sensorValue1);
  // Serial.print("  sensor 2 : ");
  // Serial.println(sensorValue2);

  // // Turn the LED on, then pause
  // leds[0] = CRGB::Blue;
  // FastLED.show();
  // delay(500);
  // // Now turn the LED off, then pause
  // leds[0] = CRGB::Black;
  // FastLED.show();
  // delay(500);
}

// void HSVoffsetAngle(){

//   offsetAngle = sensorValue2;
//   if (offsetAngle + sensorValue0 > 255) {
//     offsetAngle -= 255;
//   }


// }
