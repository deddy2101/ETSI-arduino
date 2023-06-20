#include <Arduino.h>

//sketch to create a 50Hz PWM signal with 50% duty cycle
//the signal is generated on pin 9
//the signal is generated using the timer1 of the arduino

void setup() {

  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);
  TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM20);
TCCR2B = _BV(WGM22) | _BV(CS21) | _BV(CS20);
OCR2A = 249;
OCR2B = 124;
}

void loop() {


}

