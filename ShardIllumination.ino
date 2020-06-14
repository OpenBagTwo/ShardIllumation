/*
  ShardIllumination

  Code to control an RGB light strip (single-color, not individually
  addressible) that is used to illuminate a shard of acrylic glass.

  An Arduino Nano was used as the controller for this project,
  as the ESP8266 only has one analog-in pin, but an alternative
  version of this project would replace the potentiometer knobs
  with Wi-Fi controls (read: Blynk app).

  The circuit:
  * 3 2N2222 BJTs
  * 3 10kΩ linear rotary potentiometers
  * 3 220Ω resistors
  * 1 MT3608 boost converter with Micro USB input (the Micro
    USB port is optional, as you could always power the circuit
    through the Arduino Nano)
  * 1 short (3 light) strip of SMD 5050 RGB LEDs

  All components I selected were compatible with either 5V
  or 3.3V logic, so that should give you some freedom as well.

  Created 14 June 2020
  By Gili (OpenBagTwo) Barlev

  http://url/of/online/tutorial.cc

*/

// set constants
const int color_palette[9][3] = {                 // colors to cycle through in demo mode
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

const int animation_wait_time = 500;              // time between frames of the idle / demo animation

// set pins
const int rgb_pins[3] = {3, 5, 6};                // LED output pins (R, G, B)
const int color_control_pins[3] = {A0, A1, A2};   // controller pins (R, G, B)
const int push_button = 1;                        // tactile push button

// global variables
int iter;                                         // frame number of the idle / demo animation
bool demoMode;                                    // whether to deplay demo sequence (true) or set color based
                                                  // on controller values
unsigned long lastPress;                          // last time the button was pressed (in ms since bootup)

void setup() {
  Serial.begin(9600);
  iter = 0;
  demoMode = true;
  lastPress = 0;
  
  for (int i=0; i<3; i++){
    pinMode(rgb_pins[i], OUTPUT);
    pinMode(color_control_pins, INPUT);
  }
  pinMode(push_button, INPUT);
}

void loop() {
  if (isButtonPressed()){
    demoMode = !demoMode;
  }
  if (demoMode) {
    displayDemo();
    delay(animation_wait_time);
  }
  else {
    displayFromControls();
    delay(10);
  }
}

/*
 * Function:  displayDemo
 * ----------------------
 * Cycle through demo animation (while in demo mode) 
 * 
 */
void displayDemo() {
  for (int i=0; i<3; i++){
    analogWrite(rgb_pins[i], color_palette[iter % 9][i]);
  }
  iter++;
}

/*
 * Function:  displayFromControls
 * ------------------------------
 * Set the color based on the controller input values 
 * 
 */
void displayFromControls() {
  String message = "(";
  for (int i=0; i<3; i++){
    int color_value = analogRead(color_control_pins[i]) / 4;
    message += sprintf("%03d", color_value);
    if (i<3){
      message += ",";
    }
    analogWrite(rgb_pins[i], color_value);
  }
  message += ")";
  Serial.println(message);
}


/*
 * Function:  isButtonPressed
 * --------------------------
 * Determine whether the manual tactile button has been pressed, with
 * logic in place to prevent "double clicks" or "long presses" from being
 * registered. This button in my circuit was wired using a pull-up resistor,
 * so the pin would go LOW when the button was pressed, but I could easily
 * have used a pull-down configuration. 
 * 
 * returns: true if the button is pushed, false otherwise
 */
bool isButtonPressed(){
  unsigned int currentTime = millis();
  if (currentTime - lastPress < 200)
    return 0; // prevent double-press
  if (digitalRead(push_button) == LOW){
    Serial.println("Button pressed");
    lastPress = currentTime;
    return 1;
  }
  return 0;
}
