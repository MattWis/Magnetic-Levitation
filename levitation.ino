#define GOAL_VALUE 409  // 409 has been double checked as a goal value. It is shadow 2/3 of the way up the sensor
#define MID_PWM 205     // 205 has been double checked to just barely hold the magnet with the 1/4 inch spacer - the weight of the spacer was supported separately
                        // This was done with power supply in series, 12.1 volts each side

int sensor_pin = A0;  int sensor_value = 0;
int error = 0;        int last_error = 0;  // Will be used for lead compensation
int output = 0;       int last_output = 0;  // Will be used for lead compensation
uint8_t test_output = 0;  // For testing loop cycle time
int pwm_value = 0;

void setup() {
//  Serial.begin(9600);  // Uncomment for debugging
  //No prescaling on PWM clock
  TCCR0B |= _BV(CS00);
  TCCR0B &= ~(_BV(CS01) | _BV(CS02));
  //Set up phase-correct PWM on OC0B
  TCCR0A |= _BV(COM0B1) | _BV(WGM00);
  TCCR0A &= ~_BV(COM0B0);
  //set OC0B (PE1, pin 10) as output.
  DDRD |= _BV(PD5);
}

void loop() {
  sensor_value = analogRead(sensor_pin);

  if (sensor_value > 330) {
    error = sensor_value - GOAL_VALUE;
  
    // Lead compensation hump at 0.0002 sampling period
  //output =  (1) * error -   (2) * last_error +  (3) * last_output;
//    output = 9.671 * error - 9.598 * last_error + 0.9269 * last_output;  // hump = 120, K = 1
        // Small continuous escillations, ~2mm. Occasionally these grow until it drops. Hangs higher than I'd expect
//    output = 4.835 * error - 4.799 * last_error + 0.9269 * last_output;  // hump = 120, K = 0.5
        // Large oscillations when partially supported by finger. Falls out of the sky on its own, no balancing
//    output = 19.34 * error - 19.2 * last_error + 0.9269 * last_output;   // hump = 120, K = 2
        // Really cool. You can clearly see the small fast oscillations build into slower larger ones before it crashes
//    output = 37.46 * error - 36.9 * last_error + 0.8589 * last_output;   // hump = 240, K = 4
        // Always unstable, medium sized oscillations and then falls
    output = 18.73 * error - 18.45 * last_error + 0.8589 * last_output;  // hump = 240, K = 2
        // Stable! Like, really stable!
//    output = 74.92 * error - 73.79 * last_error + 0.8589 * last_output;  // hump = 240, K = 8
        // Fast, medium sized oscillations, drops as soon as support is removed
//    output = 9.365 * error - 9.224 * last_error + 0.8589 * last_output;  // hump = 240, K = 1
        // Oscillations start of slowish and smallish and grow from there, but they always grow and drop within ~6 seconds
//    output = 28.1 * error - 27.67 * last_error + 0.8589 * last_output;  // hump = 240, K = 3
        // Vibrates constantly small and fast, but stays in place

    pwm_value = MID_PWM + output;
    if (pwm_value > 255) {
      OCR0B = 255;
    } else if (pwm_value < 0) {
      OCR0B = 0;
    } else {
      OCR0B = pwm_value;
    }
  } else {
    // Introduces a non-linearity where if the nut is outside of the sensor view the magnet goes to partial power
    // OCR0B = 125;
    OCR0B = 40;
  }

//  Serial.print("Sensor voltage: "); Serial.println(sensor_value);  // Uncomment for debugging
//  Serial.print("output: "); Serial.println(output);  // Uncomment for debugging
//  Serial.print("PWM Value: "); Serial.println(pwm_value);  // Uncomment for debugging
//  Serial.println();

  last_error = error;
  last_output = output;
}
