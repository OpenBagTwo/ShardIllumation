/*
  MicCalibrate

  Sketch for calibrating the signal from an input mic, e.g. an
  Electret consenser amplified via a MAX4466 amplifier.

  Takes in analog signal and prints the following to Serial:
  * raw measurement
  * "smoothed" measurement
  * average value over window period

  This sketch was tested using an Arduino Nano, but it really
  should work with *any* microcontroller with an analog input
  pin.
  
  Created 21 June 2020
  By Gili (OpenBagTwo) Barlev

*/

# include <illumination_utils.h>


// set constants
const int n_readings = 5;                       // number of analogRead measurements to average (noise reduction)
const int window = 100;                         // number of records to average to arrive at input intensity

// set GPIO pins
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
}

void loop() {

  int raw_measurement = analogRead(mic_pin) - 512;
  raw_measurement = abs(raw_measurement);
  
  int measurement = measureSignal(mic_pin, 512, n_readings);
  history[idx++ % window] = measurement;

  int rolling_average = calculateAverage(history, window);

  Serial.println(String(raw_measurement)
                 + " " + String(measurement)
                 + " " + String(rolling_average)
                 );

  delay(1);
}
