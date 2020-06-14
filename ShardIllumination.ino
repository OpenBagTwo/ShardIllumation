const int color_palette[9][3] = {{255,   0,   0}, // red
                                 {255, 117,  56}, // orange
                                 {255, 255,  51}, // yellow
                                 {  0, 255,   0}, // green
                                 {  0,   0, 255}, // blue 
                                 { 75,   0, 130}, // indigo
                                 {148,   0, 211}, // violet
                                 {255, 255, 255}, // white
                                 {  0,   0,   0}, // black
                                };

const int rgb_pins[3] = {3, 5, 6};
const int color_control_pins[3] = {A0, A1, A2};
const int push_button = 1;

const int animation_wait_time = 500;

int iter;
bool demoMode;
unsigned long lastPress;                       // last time the button was pressed (in ms since bootup)

void setup() {
  for (int i=0; i<3; i++){
    pinMode(rgb_pins[i], OUTPUT);
    pinMode(color_control_pins, INPUT);
  }
  pinMode(push_button, INPUT);
  iter = 0;
  demoMode = true;
  lastPress = 0;
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
void displayDemo() {
  for (int i=0; i<3; i++){
    analogWrite(rgb_pins[i], analogRead(color_control_pins[i]) / 4);
  }
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
