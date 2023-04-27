#include <Arduino.h>
uint32_t SIG_LENGHT = 320;
extern double InputSignal_1kHz_15kHz[320];

double signal_mean(const double *signal, uint32_t signal_lenght)
{
  double mean = 0;
  for (uint32_t i = 0; i < signal_lenght; i++)
  {
    mean += signal[i];
  }
  mean /= signal_lenght;
  return mean;
}

double signal_variance(const double *signal, double sig_mean,  uint32_t signal_lenght)
{
  double variance = 0;
  for (uint32_t i = 0; i < signal_lenght; i++)
  {
    variance += pow(signal[i] - sig_mean, 2);
  }
  variance /= signal_lenght;
  return variance;
}

void plot_signal(const double *sig_src_arr, double *sig_conv_arr, uint32_t sig_lenght, bool motion)
{
  for (uint32_t i = 0; i < sig_lenght; i++)
  {
    Serial.print(F("signal:"));
    Serial.print(sig_src_arr[i]);
    Serial.print(",convolution:");
    Serial.println(sig_conv_arr[i]);
    if (motion) {
      if (i == (sig_lenght - 1)) i=0;
    }
    delay(200);
  }
}

double signal_std(double variance)
{
  return sqrt(variance);
}


void setup()
{
  Serial.begin(115200);

  double mean = signal_mean(&InputSignal_1kHz_15kHz[0], SIG_LENGHT);
  Serial.print(F("Mean: "));
  Serial.println(mean);

  double variance = signal_variance(&InputSignal_1kHz_15kHz[0], mean, SIG_LENGHT);
  Serial.print(F("Variance: "));
  Serial.println(variance);

  double std = signal_std(variance);
  Serial.print(F("Standard deviation: "));
  Serial.println(std);
}

void loop()
{}
