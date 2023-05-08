#include <Arduino.h>

#define SIG_LENGTH 320
#define SHORT_SIG_LENGTH 88
#define OFFSET 5

extern double InputSignal_1kHz_15kHz[SIG_LENGTH];
extern double short_InputSignal_1kHz_15Hz[SHORT_SIG_LENGTH];

double output_first_diff_arr[SHORT_SIG_LENGTH];
double output_central_diff_arr[SHORT_SIG_LENGTH];

void plot_signal(double *sig_src_arr, uint32_t signal_length);
void plot_both(void);
void calc_running_sum(double *sig_src_arr, double *sig_dest_arr,uint32_t sig_length);
void calc_first_difference(double *sig_src_arr, double *sig_dest_arr,uint32_t sig_length);
void calc_central_difference(double *sig_src_arr, double *sig_dest_arr,uint32_t sig_length);

void setup() {
  Serial.begin(115200);

  //calc_running_sum(&short_InputSignal_1kHz_15Hz[0],&output_signal_arr[0],SHORT_SIG_LENGTH);
  calc_first_difference(&short_InputSignal_1kHz_15Hz[0],&output_first_diff_arr[0],SHORT_SIG_LENGTH);
  calc_central_difference(&short_InputSignal_1kHz_15Hz[0],&output_central_diff_arr[0],SHORT_SIG_LENGTH);
  plot_both();

}

void loop() {

}

void plot_both()
{
  uint32_t i;
  for(i=0;i<SHORT_SIG_LENGTH;i++){
    //Serial.print(short_InputSignal_1kHz_15Hz[i]+OFFSET);
    //Serial.print(",");
    Serial.print(output_first_diff_arr[i]);
    Serial.print(",");
    Serial.print(output_central_diff_arr[i]);
    Serial.println("");
    delay(10);
  }
}

void plot_signal(double *sig_src_arr, uint32_t signal_length)
{
  uint32_t i;
  for(i=0;i<signal_length;i++)
  {
    Serial.println(sig_src_arr[i]);
    delay(10);

  }

}


void calc_running_sum(double *sig_src_arr, double *sig_dest_arr,uint32_t sig_length)
{
  uint32_t i;

  for(i=0;i<sig_length;i++)
  {
    sig_dest_arr[i] = sig_dest_arr[i-1] + sig_src_arr[i];
  }
}

void calc_first_difference(double *sig_src_arr, double *sig_dest_arr,uint32_t sig_length)
{
  uint32_t i;
  for(i=0;i<sig_length;i++)
  {
    sig_dest_arr[i] = sig_src_arr[i] - sig_src_arr[i-1];
  }
}

void calc_central_difference(double *sig_src_arr, double *sig_dest_arr,uint32_t sig_length)
{
  uint32_t i;
  for(i=1;i<sig_length-1;i++)
  {
    sig_dest_arr[i] = (sig_src_arr[i+1] - sig_src_arr[i-2])/2;
  }
}
