/********************************************************************************************************
  Parameter 1 = number of pixels in strip
  Parameter 2 = pin number (most are valid)
  Parameter 3 = pixel type flags, add together as needed:
    NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

**********************************************************************************************************/

#include <Adafruit_NeoPixel.h>
#include<stdlib.h>

// the data pin for the NeoPixels
int neoPixelPin = 15;//Change the pin numbers according to your board

int numPixels = 12; //Change it according to the number of pixels in your neopixel
#define BUTTON_PIN1  2 //Change the pin numbers according to your board

// Instatiate the NeoPixel from the ibrary
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numPixels, neoPixelPin, NEO_GRB + NEO_KHZ800);

//Starting pixels for the Google's 4 colours
int start1 = 0; // Same value for Neopixels of all sizes
int start2 = 3; // 2 for 8 neopixel ring, 6 for 24 neopixel ring and so on
int start3 = 6; // 4 for 8 neopixel ring, 12 for 24 neopixel ring and so on
int start4 = 9; // 6 for 8 neopixel ring, 18 for 24 neopixel ring and so on

int brightness = 20;

#define DELAY_TIME (50)

unsigned long startTime;
uint32_t magenta = strip.Color(255, 0, 255);
uint32_t red = strip.Color(255, 0, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t cyan = strip.Color(0, 255, 255);
uint32_t pink = strip.Color(255, 51, 153);
uint32_t orange = strip.Color(255, 128, 0);

uint32_t colors[] = {red, green, blue, magenta, yellow, cyan, pink, orange};

int last = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN1, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  startTime = millis();
}

void loop() {
  bool but1 = digitalRead(BUTTON_PIN1);
  
  if (but1 == HIGH) {
      int position = index();

      if (position > 8) {
        circle();
      } else {
         color(colors[position]);
      }
  }
}

int index() {
  int r = rand() % 15;
      
  if (r == last) {
    r = index();
  }

  last = r;
  return r;
}

void circle() {
  for ( int i = 1; i < 450 + 1; i++ ) {
      delay(10);
      if ( startTime + DELAY_TIME < millis() ) {
        activatecircle();
        startTime = millis();
      }
    }
    allOff(); 
}


void color(uint32_t color) {
  allOff();
  strip.setBrightness(brightness);
  for ( int i = 0; i < numPixels; i++ ) {
    delay(250);
    strip.setPixelColor(i, color);
    strip.show();
  }
  blink(color);
}

void blink(uint32_t color) {
   for ( int i = 0; i < 3; i++ ) {
      allOff();
      delay(500);
      for ( int i = 0; i < numPixels; i++ ) {
        strip.setPixelColor(i, color);
      }
      strip.show();
      delay(500);
   }
   allOff();
}


void allOff() {
    strip.clear();
    uint32_t off = strip.Color(0, 0, 0);
    for( int i = 0; i<numPixels; i++){
        strip.setPixelColor(i, off);
        strip.show();
    }
}

//Circling effect
void activatecircle() {
  strip.setBrightness(brightness);
  adjustStarts();

 // first 3 pixels = color set #1
  for ( int i = start1; i < start1 + 1; i++ ) {
    strip.setPixelColor(i, 23, 107, 239 );
  }

  // next 3 pixels = color set #2
  for ( int i = start2; i < start2 + 1 ; i++ ) {
    strip.setPixelColor(i, 255, 62, 48 );
  }

  // next 3 pixels = color set #3
  for ( int i = start3; i < start3 + 1; i++ ) {
    strip.setPixelColor(i, 247, 181, 41 );
  }
  // last 3 pixels = color set #3
  for ( int i = start4; i < start4 + 1; i++ ) {
    strip.setPixelColor(i, 23, 156, 82 );
  }

  strip.show();
}

void adjustStarts() {
  start1 = incrementStart(start1);
  start2 = incrementStart(start2);
  start3 = incrementStart(start3);
  start4 = incrementStart(start4);
}

int incrementStart(int startValue) {
  startValue = startValue + 1;
  if ( startValue == numPixels  )//Change it according to the number of pixels in your neopixel
    startValue = 0;

  return startValue;
}

void rgbFadeInAndOut(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait) {
  for(uint8_t b = 0; b <255; b++) {
     for(uint8_t i=0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }

     strip.show();
     delay(wait);
  };

  for(uint8_t b=255; b > 0; b--) {
     for(uint8_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, red * b/255, green * b/255, blue * b/255);
     }
     strip.show();
     delay(wait);
  };
};
