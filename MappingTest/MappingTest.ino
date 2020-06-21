/*
  MappingTest

  Sketch for trying out a color map to see how it looks. Simulates all 1024 analogRead
  values and then calculates the corresponding intensity values for each LED output pin.

  This demo sketch should apply to a wide variety of simple setups, from three 5mm
  diodes powered directly by each GPIO pin, to sending signals to a trio of transitors
  or MOSFETs, controlling the intensity of high-powered LEDs or even an LED strip.

  The only requirement is that your microcontroller must have at least three PWM output
  pins.

  You don't even need to connect anything to your microcontroller if you instead want
  to take the SerialMonitor output and feed it into a computerized color renderer. My
  caveat here would be that the colors produced by your physical LEDs may not match
  the colors rendered on your screen.
  
  Created 20 June 2020
  By Gili (OpenBagTwo) Barlev

*/

#include <illumination_utils.h>

// set constants
const LinearColorMap color_mappings[3] = {  // mapping of input values to analogWrite intensity (0-255) 
  LinearColorMap(500, 1024),                // red
  LinearColorMap(100,  500),                // green
  LinearColorMap(250, 750)};                //blue
                                    
const int wait_time = 10;                   // time between frames in millis

// set GPIO pins
const int rgb_pins[3] = {3, 9, 11};         // LED output pins (R, G, B)

// declare global variables 
int iter;                                   // current frame

void setup() {
  Serial.begin(9600);

  for (int i=0; i<3; i++){
    pinMode(rgb_pins[i], OUTPUT);
    analogWrite(rgb_pins[i], 0);
  }                                 
  iter = 0;
}

void loop() {
  int value = iter % 1024;
  String message = String(value);
  for (int i=0; i<3; i++){
    int intensity = color_mappings[i].getIntensity(value);
    message += " " + String(intensity);
    analogWrite(rgb_pins[i], intensity);
  }
  Serial.println(message);
  delay(wait_time);
  iter++;
}
  
