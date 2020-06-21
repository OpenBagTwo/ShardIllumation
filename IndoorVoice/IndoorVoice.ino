/*
  IndoorVoice

  Sketch for pulsing an RGB LED light strip based on the intensity of measured sound (to
  remind the owner to use their fl*pping indoor voice).
  The input into the circuit is an amplifed condenser mic.

  This demo sketch should apply to a wide variety of simple setups, from three 5mm
  diodes powered directly by each GPIO pin, to sending signals to a trio of transitors
  or MOSFETs, controlling the intensity of high-powered LEDs or even an LED strip.

  The only requirement is that your microcontroller must have at least three PWM output
  pins and one analog input. The following code was written for an Arduino Nano, but really
  pretty any microcontroller will d.o

  The parts used in the circuit this sketch powered were:
  * 1x Arduino Nano
  * 3x 220Ω resistors
  * 1x Electret microphone breakout with built-in MAX4466 amplifier
  * 3x 2N2222 NPN BJTs
  * 1x MT3608 boost converter with Micro USB input (the Micro
    USB port is optional, as you could always power the circuit
    through the microcontroller)
  * 1x short strip of 12V non-addressible SMD 5050 RGB LEDs

  Again, if re-creating this project, I *highly encourage* you to substitute more readily
  available components. If using a controller with a Micro USB port, or if you don't mind the Mini
  USB connector, you can use a 5V (remember: non-addressible) LED strip and omit the step-up board
  altogether.
  
  Created 21 June 2020
  By Gili (OpenBagTwo) Barlev

*/

# include <illumination_utils.h>

// set constants
const int n_readings = 5;                       // number of analogRead measurements to average (noise reduction)
const int window = 100;                         // number of records to average to arrive at input intensity
const LinearColorMap color_mappings[3] = {      // mapping of input values to analogWrite intensity (0-255)
  LinearColorMap(200, 400),                     // red
  LinearColorMap( 25, 200),                     // green
  LinearColorMap(100, 300)                      // blue
};  // note: Arduino Nano compiler allows this array to be const, ESP8266 compiler does not

// set GPIO pins
const int rgb_pins[3] = {3, 9, 11};             // LED output pins (R, G, B)
const int mic_pin = A0;                         // microphone input pin

// declare global variables
int idx;                                        // current iteration
int history[window];                            // history of readings

void setup() {
  pinMode(mic_pin, INPUT);
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
  
  int measurement = measureSignal(mic_pin, 512, n_readings);
  history[idx++ % window] = measurement;

  int rolling_average = calculateAverage(history, window);

  String message = String(measurement) + " " + String(rolling_average);

  for (int i=0; i<3; i++){
   int intensity = color_mappings[i].getIntensity(rolling_average);
   message += " " + String(intensity);
   analogWrite(rgb_pins[i], intensity);
  }
  
  Serial.println(message);
  delay(5);
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
