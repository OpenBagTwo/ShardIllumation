
/*
 * Function:  measureSignal
 * ------------------------
 * Take measurements from the analog input pin, remove
 * the largest and smallest values, then average the
 * remainder.
 * 
 * analog_pin : pin number from which to read the signal
 * n_readings : number of readings to take
 * 
 * returns : average reading, after discarding max and min
 */
int measureSignal(int analog_pin, int n_readings){
  int min_idx = 0;
  int max_idx = 0;
  int readings[n_readings];
  for (int i=0; i<n_readings; i++){
    readings[i] = analogRead(A0);
    if (readings[i] < readings[min_idx]){
      min_idx = i;
    }
    if (readings[i] > readings[max_idx]){
      max_idx = i;
    }
  }
  int sum = 0;
  for (int i=0; i<n_readings; i++){
    if ((i != min_idx) && (i != max_idx)){
      sum += readings[i];
    }
  }
  return sum / (n_readings-2);
}

/*
 * Function:  calculateAverage
 * ---------------------------
 * Calculate the average of an array of provided values
 * 
 * values_to_average : the values to average
 * len : the length of the array
 * 
 * returns : integer average of provided array
 */
int calculateAverage(int values_to_average[], int len){
  int sum = 0;
  for (int i=0; i<len; i++){
    sum += values_to_average[i];
  }
  return sum/len;
}

/*
 * Class: LinearColorMap
 * ----------------------
 * A mapping of analog signal (0-1023) to ananolog intensity (0-255),
 * using given min and max values. The mapping is a triangle function,
 * increasing linearly from 0 at the min_value to 255
 * at the mid-point, then back down to 0 at the max_value.
 * 
 * min_value : min cutoff for intensity map
 * max_value : max cutoff for intensity map. Peak will be halfway
 *             between min_value and max_value
 *
 */
class LinearColorMap{

  int _peak;
  int _half_width;

public:
  LinearColorMap(int min_value, int max_value){
    _peak = (max_value + min_value) / 2;
    _half_width = (max_value - min_value) / 2;
  }

  /*
   * Function:  getIntesnity
   * -----------------------
   * Return the output intensity for the given signal value
   * 
   * signal_value : value read from the analog input
   *
   * returns : value between 0 and 255 to set the intensity of
   *           a PWM output pin
   */
  int getIntensity(int signal_value){
    return max(0, 255 - int(255 * (1.0 * abs(_peak - signal_value) / _half_width)));
  }
};
