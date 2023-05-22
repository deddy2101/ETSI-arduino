#include <Arduino.h>

#define SAMPLES 128
#define SAMPLING_FREQUENCY 1000

unsigned int sampling_period_us;
unsigned long microseconds;
double v[SAMPLES];

// Define 4 pin for DAC output
#define BIT0 2
#define BIT1 4
#define BIT2 7
#define BIT3 8

void setup() {
    Serial.begin(9600);
    
    pinMode(BIT0, OUTPUT);
    pinMode(BIT1, OUTPUT);
    pinMode(BIT2, OUTPUT);
    pinMode(BIT3, OUTPUT);

    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}

void loop() {

    for (int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();
        v[i] = analogRead(A0);
        //convert to voltage v[i]
        //v[i] = (v[i] * 5.0) / 1023.0;

        uint8_t dac = map(v[i], 0, 1023, 0, 16);

        digitalWrite(BIT0, dac & 0x01);
        digitalWrite(BIT1, (dac >> 1) & 0x01);
        digitalWrite(BIT2, (dac >> 2) & 0x01);
        digitalWrite(BIT3, (dac >> 3) & 0x01);

        Serial.print(">val:");
        Serial.println(v[i]);
        Serial.print(">dac:");
        Serial.println(dac);

        while(micros() < (microseconds + sampling_period_us)){
        }
    }
}