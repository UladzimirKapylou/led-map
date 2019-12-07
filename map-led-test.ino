////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// Fast Adressable Bitbang LED Library
/// Copyright (c)2015, 2017 Dan Truong
///
/// This is the simplest exmple to use the library.
///
/// This example is for an Arduino Uno board with a LED strip connected to
/// port D6. Targetting any other board requires you to change something.
/// The program sends an array of pixels to display on the strip.
/// "strip" represents the hardware: LED types and port configuration,
/// "pixels" represents the data sent to the LEDs: a series of colors.
///
/// Wiring:
///
/// The LED strip DI (data input) line should be on port D6 (Digital pin 6 on
/// Arduino Uno). If you need to change the port, change all declarations below
/// from, for example from "ws2812b<D,6> myWs2812" to "ws2812b<B,4> myWs2812"
/// if you wanted to use port B4.
/// The LED power (GND) and (+5V) should be connected on the Arduino Uno's GND
/// and +5V.
///
/// Visual results:
///
/// If the hardware you use matches this program you will see the LEDs blink
/// repeatedly red, green, blue, white, in that order.
///
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#include <FAB_LED.h>

// Declare the LED protocol and the port
sk6812<D,6>  strip;

// How many pixels to control
const uint8_t numPixels = 10;

const byte brightnessPin = A0;
const byte lengthPin = A1;

// How bright the LEDs will be (max 255)
uint8_t maxBrightness;
int length;

// The pixel array to display
rgbw pixels[numPixels] = {};


////////////////////////////////////////////////////////////////////////////////
// Sets the array to specified color
////////////////////////////////////////////////////////////////////////////////
void updateColors(char r, char g, char b, char w)
{
  for(int i = 0; i < numPixels; i++)
  {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
    pixels[i].w = w;
  }
}

void updateBar(int brightness, int length)
{
  int redWidth = 100;
  int pointsPerPixel = 100;
  
  for(int i = 0; i < numPixels; i++)
  {
    if (length < 0) {
      pixels[i].r = 0;
      pixels[i].g = 0;
      pixels[i].b = 0;
      pixels[i].w = 0;
      continue;
    }

    if (length > redWidth + pointsPerPixel) {
      pixels[i].r = 0;
      pixels[i].g = 0;
      pixels[i].b = 0;
      pixels[i].w = brightness;
      
    } else if (length <= redWidth) {
      pixels[i].r = 0;
      pixels[i].g = map(length, 0, redWidth, 0, brightness);
      pixels[i].b = 0;
      pixels[i].w = 0;
      Serial.print(i);
      Serial.print(": ");
      Serial.print(pixels[i].g);
      Serial.print(" ");
      
    } else {
      byte val = map(length - redWidth, 0, redWidth, 0, brightness);
      pixels[i].r = 0;
      pixels[i].g = brightness - val;
      pixels[i].b = 0;
      pixels[i].w = val;
      Serial.print(i);
      Serial.print(": ");
      Serial.print(pixels[i].w);
      Serial.print(" ");
    }

    length -= pointsPerPixel;

  }
  Serial.println();
}

////////////////////////////////////////////////////////////////////////////////
// This method is automatically called once when the board boots.
////////////////////////////////////////////////////////////////////////////////
void setup()
{
  // Turn off the LEDs
  strip.clear(2 * numPixels);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  Serial.begin(9600);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief This method is automatically called repeatedly after setup() has run.
/// It is the main loop.
////////////////////////////////////////////////////////////////////////////////
void loop()
{
  maxBrightness = map(analogRead(brightnessPin), 0, 1023, 0, 255);
  length = map(analogRead(lengthPin), 0, 1023, 0, 1000);

  updateBar(maxBrightness, length);
  strip.sendPixels(numPixels, pixels);
  

//  int colorTime = 3000;
//  
//  // Write the pixel array red
//  updateColors(maxBrightness, 0 , 0, 0);
//  // Display the pixels on the LED strip
//  strip.sendPixels(numPixels, pixels);
//  // Wait 0.1 seconds
//  delay(colorTime);
//
//  // Turn off the LEDs
//  strip.clear(numPixels);
//  delay(1000);
//
//  // Write the pixel array green
//  updateColors(0, maxBrightness, 0, 0);
//  // Display the pixels on the LED strip
//  strip.sendPixels(numPixels, pixels);
//  // Wait 0.1 seconds
//  delay(colorTime);
//
//  // Turn off the LEDs
//  strip.clear(numPixels);
//  delay(1000);
//
//  // Write the pixel array blue
//  updateColors(0, 0, maxBrightness, 0);
//  // Display the pixels on the LED strip
//  strip.sendPixels(numPixels, pixels);
//  // Wait 0.1 seconds
//  delay(colorTime);
//
//  // Turn off the LEDs
//  strip.clear(numPixels);
//  delay(1000);
//
//  // Write the pixel array white
//  updateColors( maxBrightness, maxBrightness, maxBrightness, 0);
//  // Display the pixels on the LED strip
//  strip.sendPixels(numPixels, pixels);
//  // Wait 0.1 seconds
//  delay(colorTime);
//
//  // Turn off the LEDs
//  strip.clear(numPixels);
//  delay(1000);
//
//  // Write the pixel array warm white
//  updateColors( 0, 0, 0, maxBrightness);
//  // Display the pixels on the LED strip
//  strip.sendPixels(numPixels, pixels);
//  // Wait 0.1 seconds
//  delay(colorTime);
//
//  // Turn off the LEDs
//  strip.clear(10);
//  delay(1000);
}
