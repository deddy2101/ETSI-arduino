#include <Arduino.h>
#include "arduinoFFT.h"

#define SAMPLES 128
#define SAMPLING_FREQUENCY 1280

arduinoFFT FFT = arduinoFFT();

unsigned int sampling_period_us;
unsigned long microseconds;

const double signalFrequency1 = 40;
const double signalFrequency2 = 340;

double vReal[SAMPLES];
double vImag[SAMPLES];
double vTemp[SAMPLES];

void setup()
{
    Serial.begin(9600);
    sampling_period_us = round(1.0e6 * (1.0 / SAMPLING_FREQUENCY));
}

void loop()
{
    for (int i = 0; i < SAMPLES; i++)
    {
        microseconds = micros();
        // vReal[i] = analogRead(A1);
        vReal[i] = sin(2 * PI * signalFrequency1 * (microseconds / 1.0e6)) + 0.2 * sin(2 * PI * signalFrequency2 * (microseconds / 1.0e6));
        vTemp[i] = vReal[i];
        vImag[i] = 0;
        while (micros() < (microseconds + sampling_period_us)) {};
    }
    
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    Serial.print(">Peak:");
    Serial.println(peak);

    for (int i = 0; i < SAMPLES / 2; i++)
    {
        // Serial.print(i);
        Serial.print(">vTemp:");
        Serial.println(vTemp[i], 1);
        Serial.print(">vReal:");
        Serial.println(vReal[i], 1);
        Serial.print(">vImag:");
        Serial.println(vImag[i], 1);
    }
    while (1);
}