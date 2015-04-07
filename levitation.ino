#define GOAL_VALUE 410
#define MID_PWM 192
#define KP 10

int sensorPin = A0;
int sensorValue = 385;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
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
  ////////////////////////////////////////////
  sensorValue = analogRead(sensorPin);
  Serial.print("Sensor voltage: "); Serial.println(sensorValue);
  ////////////////////////////////////////////
//  Serial.println(duty_cycle);
//  OCR0B = duty_cycle++;
//  if (duty_cycle == 255) {
//    duty_cycle = 32;
//  }
//  delay(10 * 64);
  ////////////////////////////////////////////
  OCR0B = 150;
  ////////////////////////////////////////////
//  OCR0B = MID_PWM + ((GOAL_VALUE - sensorValue) * KP);
  ////////////////////////////////////////////
}
