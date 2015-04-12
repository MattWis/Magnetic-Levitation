#define GOAL_VALUE 410
#define MID_PWM 192
#define KP 10

int sensor_pin = A0;
int sensor_value = 385;
int error = 0;
int last_error = 0;  // Will be used for lead compensation
int output = 0;
int last_output = 0;  // Will be used for lead compensation

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

uint8_t counter = 0;
uint8_t duty_cycle = 32;

void loop() {
  sensorValue = analogRead(sensor_pin);
  error = GOAL_VALUE - sensorValue;
  // Serial.print("Sensor voltage: "); Serial.println(sensor_value);  // Uncomment for debugging

  // Lead compensation for 50 rad/s hump at 0.001 sampling period
  output = 9.341 * error - 9.194 * last_error + 0.8535 * last_output;
  OCR0B = MID_PWM + output;

  last_error = error;
  last_output = output;
}
