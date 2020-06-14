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
const int wait_time = 500;

int iter;

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
