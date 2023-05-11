#include <Arduino.h>
#define POT   A0
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}
//log2(1024) = 10 bits
void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(POT);
  //convert to voltage the value read, the ADC has 10 bits and vref is 5v
  float voltage = (value * 5.0) / 1023.0;

  Serial.print(">Potentiometer value:");
  Serial.println(value);
  Serial.print(">Voltage value:");
  Serial.println(voltage);
  if(value < 512 ) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
}
delay(10);
}
