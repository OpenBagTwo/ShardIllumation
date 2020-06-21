/*
  TooShrill

  Sketch for pulsing an RGB LED light strip based on the intensity of high-pitched sound.
  The input into the circuit is an amplifed condenser mic whose signal is sent through
  a high-pass filter (cut-off frequency for this choice of resistor and capacitor is 800 Hz).

  This demo sketch should apply to a wide variety of simple setups, from three 5mm
  diodes powered directly by each GPIO pin, to sending signals to a trio of transitors
  or MOSFETs, controlling the intensity of high-powered LEDs or even an LED strip.

  The only requirement is that your microcontroller must have at least three PWM output
  pins and one analog input. The following code was written for a WEMOS D1 Mini, but that
  choice was pretty arbitrary and based on the fact that the D1 Mini was the most abundant
  and lowest profile microcontroller in my parts bin. The ESP8266 module was pretty much
  wasted here, as this sketch contains no wifi capability.

  That being said, the parts used in the circuit this sketch powered were:
  * 1x WEMOS D1 Mini
  * 3x 220Ω resistors
  * 1x 20kΩ resistor
  * 1x 100 nF ceramic capacitor
  * 1x Electret microphone breakout with built-in MAX4466 amplifier
  * 3x 2N2222 NPN BJTs
  * 1x short strip of 5V non-addressible SMD 5050 RGB LEDs

  Again, if re-creating this project, I *highly encourage* you to substitute more readily
  available components. As this sketch does not individually address the LEDs, you're better
  off going with a 12V, 3 LED-per-segment strip. And if you do, note that the voltage regulator
  on an Arduino Nano is rated to handle 12V no problem.
  
  Created 21 June 2020
  By Gili (OpenBagTwo) Barlev

*/

# include <illumination_utils.h>

// map pins of the D1 mini
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15


// set constants
const int n_readings = 5;                       // number of analogRead measurements to average (noise reduction)
const int window = 100;                         // number of records to average to arrive at input intensity
/*const*/ LinearColorMap color_mappings[3] = {  // mapping of input values to analogWrite intensity (0-255)
  LinearColorMap(30, 75),                       // red
  LinearColorMap(10, 40),                       // green
  LinearColorMap(25, 75)                        // blue
};  // note: Arduino Nano compiler allows this array to be const, ESP8266 compiler does not

// set GPIO pins
const int rgb_pins[3] = {D1, D2, D3};           // LED output pins (R, G, B)
const int mic_pin = A0;                         // microphone input pin

// declare global variables
int idx;                                        // current iteration
int history[window];                            // history of readings

void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);
  idx = 0;
  for (int i=0; i<window; i++){
    history[i] = 0;
  }
  for (int i=0; i<3; i++){
    pinMode(rgb_pins[i], OUTPUT);
    analogWrite(rgb_pins[i], 0);
  }
  bootUpAnimation(500);
}

void loop() {
  
  int measurement = measureSignal(mic_pin, 0, n_readings);
  history[idx++ % window] = measurement;

  int rolling_average = calculateAverage(history, window);

  String message = String(measurement) + " " + String(rolling_average);

  for (int i=0; i<3; i++){
   int intensity = color_mappings[i].getIntensity(rolling_average);
   message += " " + String(intensity);
   analogWrite(rgb_pins[i], intensity);
  }
  
  Serial.println(message);
  delay(1);
}

/*
 * Function:  bootUpAnimation
 * --------------------------
 * Pulse each color channel at max brightness
 * (to test that they're all working)
 * 
 *  : the time between frames
 */
void bootUpAnimation(int wait_time){
  for (int i=0; i<3; i++){
    digitalWrite(rgb_pins[(i-1) % 3], LOW);
    digitalWrite(rgb_pins[i], HIGH);
    delay(wait_time);
  }
  digitalWrite(rgb_pins[2], LOW);
}
