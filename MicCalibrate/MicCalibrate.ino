/*
  MicCalibrate

  Sketch for calibrating the signal from an input mic, e.g. an
  Electret consenser amplified via a MAX4466 amplifier.

  Takes in analog signal and prints the following to Serial:
  * raw measurement
  * "smoothed" measurement (average of difference from "zero" for n_readings, discarding max and min)
  * amplitude measurement (peak-to-peak measurement for n_readings, discarding max and min)
  * average smoothed over window period
  * average amplitude measurement over window period

  This sketch was tested using an Arduino Nano, but it really
  should work with *any* microcontroller with an analog input
  pin.
  
  Created 21 June 2020
  By Gili (OpenBagTwo) Barlev

*/

# include <illumination_utils.h>


// set constants
const int n_readings = 11;                       // number of analogRead measurements to average (noise reduction)
const int window = 100;                         // number of records to average to arrive at input intensity

// set GPIO pins
const int mic_pin = A5;                         // microphone input pin

// declare global variables
int idx;                                        // current iteration
int history_smoothed[window];                   // history of smoothed readings
int history_amplitude[window];                  // history of amplitude readings

void setup() {
  pinMode(mic_pin, INPUT);
  Serial.begin(9600);
  idx = 0;
  for (int i=0; i<window; i++){
    history_smoothed[i] = 0;
    history_amplitude[i] = 0;
  }
}

void loop() {

  int raw_measurement = analogRead(mic_pin);
  
  int smoothed_measurement = measureSignal(mic_pin, 512, n_readings);
  history_smoothed[idx % window] = smoothed_measurement;
  int amplitude_measurement = measureAmplitude(mic_pin, n_readings);
  history_amplitude[idx % window] = amplitude_measurement;

  idx ++;

  int rolling_average_smoothed = calculateAverage(history_smoothed, window);
  int rolling_average_amplitude = calculateAverage(history_amplitude, window);

  Serial.println(String(raw_measurement)
                 + " " + String(smoothed_measurement)
                 + " " + String(amplitude_measurement)
                 + " " + String(rolling_average_smoothed)
                 + " " + String(rolling_average_amplitude)
                 );

  delay(1);
}
