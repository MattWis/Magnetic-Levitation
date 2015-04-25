#define GOAL_VALUE 409
#define MID_PWM 210

int sensor_pin = A0;
int sensor_value = 385;
int error = 0;
int last_error = 0;  // Will be used for lead compensation
int output = 0;
int pwm_value = 0;
int last_output = 0;  // Will be used for lead compensation
uint8_t test_output = 0;  // For testing loop cycle time

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
  error = sensor_value - GOAL_VALUE;

  // Lead compensation hump at 0.0002 sampling period
//output =  (1) * error -   (2) * last_error +  (3) * last_output;
  output = 9.671 * error - 9.598 * last_error + 0.9269 * last_output;
  pwm_value = MID_PWM + output;
  if (pwm_value > 255) {
    OCR0B = 255;
  } else if (pwm_value < 0) {
    OCR0B = 0;
  } else {
    OCR0B = pwm_value;
  }

//  Serial.print("Sensor voltage: "); Serial.println(sensor_value);  // Uncomment for debugging
//  Serial.print("output: "); Serial.println(output);  // Uncomment for debugging
//  Serial.print("PWM Value: "); Serial.println(pwm_value);  // Uncomment for debugging
//  Serial.println();

  last_error = error;
  last_output = output;
}
