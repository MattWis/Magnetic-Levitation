#define GOAL_VALUE ((int) (2.6 / 5 * 1023))
#define MID_PWM 175     // 205 has been double checked to just barely hold the magnet with the 1/4 inch spacer - the weight of the spacer was supported separately
                        // This was done with power supply in series, 12.1 volts each side

int sensor_pin = A0;  int sensor_value = 0;
int error = 0;        int last_error = 0;  // Will be used for lead compensation
int output = 0;       int last_output = 0;  // Will be used for lead compensation
uint16_t test_output = 0;  // For testing loop cycle time
int pwm_value = 0;

void setup() {
  //Serial.begin(9600);  // Uncomment for debugging
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
//      OCR0B = MID_PWM;   
//}
//
//void nullness() {
  sensor_value = analogRead(sensor_pin);

  if (sensor_value > 330) {
    error = sensor_value - GOAL_VALUE;
  
    // Lead compensation hump at 0.0002 sampling period
  //output =  (1) * error -   (2) * last_error +  (3) * last_output;
    //output = 9.671 * error - 9.598 * last_error + 0.9269 * last_output;  // hump = 120, K = 1
//    output = 4.835 * error - 4.799 * last_error + 0.9269 * last_output;  // hump = 120, K = 0.5
//    output = 19.34 * error - 19.2 * last_error + 0.9269 * last_output;   // hump = 120, K = 2
//    output = 37.46 * error - 36.9 * last_error + 0.8589 * last_output;   // hump = 240, K = 4
//    output = 18.73 * error - 18.45 * last_error + 0.8589 * last_output;  // hump = 240, K = 2
//    output = 74.92 * error - 73.79 * last_error + 0.8589 * last_output;  // hump = 240, K = 8
//    output = 9.365 * error - 9.224 * last_error + 0.8589 * last_output;  // hump = 240, K = 1
//    output = 28.1 * error - 27.67 * last_error + 0.8589 * last_output;  // hump = 240, K = 3
//    output = 14.05 * error - 13.84 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.5
//    output = 2.341 * error - 2.306 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.25
//    output = 2.81 * error - 2.767 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.3
//    output = 3.278 * error - 3.228 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.35
//    output = 3.746 * error - 3.69 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.4
//    output = 4.214 * error - 4.151 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.45
//    output = 4.683 * error - 4.612 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.5
//    output = 5.619 * error - 5.534 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.6
//    output = 6.321 * error - 6.226 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.675
//    output = 6.462 * error - 6.365 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.69
            // Takes a VERY long time to go unstable - LET'S CALL THIS STABLE IF YOU GET THE VERY CALM INITIAL CONDITIONS
//    output = 6.556 * error - 6.457 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.7
//    output = 6.649 * error - 6.549 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.71
//    output = 7.024 * error - 6.918 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.75
//    output = 7.492 * error - 7.379 * last_error + 0.8589 * last_output;  // hump = 240, K = 0.8

//    output = 23.41 * error - 23.06 * last_error + 0.8589 * last_output;  // hump = 240, K = 2.5
//    output = 21.07 * error - 20.75 * last_error + 0.8589 * last_output;  // hump = 240, K = 2.25
//    output = 19.9 * error - 19.6 * last_error + 0.8589 * last_output;  // hump = 240, K = 2.125
          // CALL THIS THE UPPER EDGE
//    output = 20.51 * error - 20.2 * last_error + 0.8589 * last_output;  // hump = 240, K = 2.19
//    output = 19.29 * error - 19 * last_error + 0.8589 * last_output;  // hump = 240, K = 2.06
//    output = 17.79 * error - 17.53 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.9
//    output = 16.86 * error - 16.6 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.8
//    output = 15.92 * error - 15.68 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.7
//    output = 14.98 * error - 14.76 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.6
//    output = 14.05 * error - 13.84 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.5

// GEOMETRIC MEAN OF EDGES
    output = 11.33 * error - 11.16 * last_error + 0.8589 * last_output;  // hump = 240, K = 1.21
//    output = 42.66 * error - 41.38 * last_error + 0.7364 * last_output;  // hump = 480, K = 4.84
//    output = 85.32 * error - 82.77 * last_error + 0.7364 * last_output;  // hump = 480, K = 9.68
//    output = 21.33 * error - 20.69 * last_error + 0.7364 * last_output;  // hump = 480, K = 2.42
//    output = 24.72 * error - 24.16 * last_error + 0.7956 * last_output;  // hump = 360, K = 2.7225
//    output = 17.43 * error - 17.1 * last_error + 0.8267 * last_output;  // hump = 300, K = 3.025
//    output = 85.32 * error - 82.77 * last_error + 0.7364 * last_output;  // hump = 480, K = 9.68
//    output = 85.32 * error - 82.77 * last_error + 0.7364 * last_output;  // hump = 480, K = 9.68
//    output = 85.32 * error - 82.77 * last_error + 0.7364 * last_output;  // hump = 480, K = 9.68




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

//  test_output++;
//  if (test_output == 10000) {
//    test_output = 0;
//    Serial.print("Sensor voltage: "); Serial.println(sensor_value);  // Uncomment for debugging
//  }
  last_error = error;
  last_output = output;
}
