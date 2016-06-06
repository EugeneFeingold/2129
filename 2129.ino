// This #include statement was automatically added by the Particle IDE.
#include "StripUtils.h"

// This #include statement was automatically added by the Particle IDE.
#include "application.h"

#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);


#define PIXEL_PIN D0
#define PIXEL_TYPE WS2812B
#define PIXEL_COUNT 47

#define BUTTON_PIN D1
#define POT_PIN A0
#define PHOTO_PIN A1



Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);



void setup() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'

    pinMode(PIXEL_PIN, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
    pinMode(PHOTO_PIN, INPUT);


}

void loop() {
    rainbow(100);
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  float brightness;




  for(j=0; j<256; j++) {
    brightness = (analogRead(POT_PIN) / 4096.0) * (analogRead(PHOTO_PIN) / 4096.0);


    for(i=0; i<strip.numPixels(); i++) {
      //strip.setPixelColor(i, Wheel((i+j) & 255));

        strip.setPixelColor(i, StripUtils().getWheelColor(brightness, (j) & 255));
    }
    strip.show();
    delay(wait);

  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
