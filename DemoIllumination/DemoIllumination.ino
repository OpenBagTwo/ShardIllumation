/*
  DemoIllumination

  Demo code for illuiminating an RGB LED strip, cylcling through a palette of nine
  colors.

  This demo sketch should apply to a wide variety of simple setups, from three 5mm
  diodes powered directly by each GPIO pin, to sending signals to a trio of transitors
  or MOSFETs, controlling the intensity of high-powered LEDs or even an LED strip.

  The only requirement is that your microcontroller must have at least three PWM output
  pins.

  Created 13 June 2020
  By Gili (OpenBagTwo) Barlev

*/


// set constants
const int color_palette[9][3] = {                 // colors to cycle through
                                 {255,   0,   0}, // red
                                 {255, 117,  56}, // orange
                                 {255, 255,  51}, // yellow
                                 {  0, 255,   0}, // green
                                 {  0,   0, 255}, // blue 
                                 { 75,   0, 130}, // indigo
                                 {148,   0, 211}, // violet
                                 {255, 255, 255}, // white
                                 {  0,   0,   0}, // black
                                };

const int wait_time = 500;                        // time between frames in millis


// set GPIO pins
const int rgb_pins[3] = {3, 5, 6};                // LED output pins (R, G, B)


// declare global variables 
int iter;                                         // current frame

void setup() {
  for (int i=0; i<3; i++){
    pinMode(rgb_pins[i], OUTPUT);
  }
  iter = 0;

}

void loop() {
  for (int i=0; i<3; i++){
    analogWrite(rgb_pins[i], color_palette[iter % 9][i]);
  }
  delay(wait_time);
  iter++;
}
