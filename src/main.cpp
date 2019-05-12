#include <Arduino.h>

#include <SPI.h>

#include <Adafruit_GFX.h>

#include <GxEPD.h>
#include <GxGDEW042T2/GxGDEW042T2.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

#include "config.h"

// BUSY -> 4, RST -> 16, DC -> 17, CS -> SS(5), CLK -> SCK(18), DIN -> MOSI(23), GND -> GND, 3.3V -> 3.3V

// GxIO_Class  io(SPI, CS, MOSI, RST, BL);
// GxEPD_Class display(io, rst, busy);

GxIO_Class     io(SPI, SS, 17, 16);
GxEPD_Class    display(io, 16, 4);

void setup() {
  delay(500);

  Serial.begin(115200);
  Serial.println("Hello world");

  display.init(115200);
  display.setRotation(0);

  Serial.println("eink setup done");
}

static int iterations = 0;

#define SCREEN_DELAY 1000 * 60 * 3

void loop() {
  display.fillScreen(GxEPD_WHITE);
  display.update();
  delay(SCREEN_DELAY);

  display.fillScreen(GxEPD_BLACK);
  display.update();
  delay(SCREEN_DELAY);

  display.fillScreen(GxEPD_WHITE);
  display.update();
  delay(SCREEN_DELAY);

  // checkerboard
  for(int x = 0; x < 400;  x += 10)
    for(int y = 0; y < 300; y += 10) {
      for(int i = 0; i < 5; i++)
	for(int j = 0; j < 5 ; j++)
	  display.drawPixel(x+i, y+j, GxEPD_WHITE);

      for(int i = 0; i < 5; i++)
	for(int j = 0; j < 5 ; j++)
	  display.drawPixel(x+i+5, y+j+5, GxEPD_BLACK);
    }
  display.update();
  delay(SCREEN_DELAY);

  // reverse checkerboard
  for(int x = 0; x < 400;  x += 10)
    for(int y = 0; y < 300; y += 10) {
      for(int i = 0; i < 5; i++)
	for(int j = 0; j < 5 ; j++)
	  display.drawPixel(x+i, y+j, GxEPD_BLACK);

      for(int i = 0; i < 5; i++)
	for(int j = 0; j < 5 ; j++)
	  display.drawPixel(x+i+5, y+j+5, GxEPD_WHITE);
    }
  display.update();
  delay(SCREEN_DELAY);

  display.fillScreen(GxEPD_WHITE);
  display.printf("iteration %d\n", iterations++);
  display.update();
  delay(SCREEN_DELAY);
}
