#include <Arduino.h>
#define  SIG_LENGTH 320
#define SHORT_SIG_LENGTH 88



extern double InputSignal_1kHz_15kHz[SIG_LENGTH];
extern double short_InputSignal_1kHz_15Hz[SHORT_SIG_LENGTH];

double output_sig_arr[SHORT_SIG_LENGTH];
double output_sig_arr2[SHORT_SIG_LENGTH];
void plot_signal(double *sig_src_arr, uint32_t signal_length);

void moving_average(double *sig_src_arr, double *sig_out_arr, uint32_t sig_length, uint32_t filter_pts);
void plot_2_signals(double * sig_src1_arr,double *sig_src2_arr,uint32_t sig_length);
void plot_3_signals(double * sig_src1_arr,double *sig_src2_arr,double *sig_src3_arr,uint32_t sig_length);
 void recursive_moving_average(double *sig_src_arr, double *sig_out_arr, uint32_t sig_length, uint32_t filter_pts);


/**@note USE full signal length for DUE demo**/

void setup() {
Serial.begin(115200);
 recursive_moving_average(&short_InputSignal_1kHz_15Hz[0],&output_sig_arr[0],SHORT_SIG_LENGTH,11);
 moving_average(&short_InputSignal_1kHz_15Hz[0],&output_sig_arr2[0],SHORT_SIG_LENGTH,11);
 plot_3_signals(short_InputSignal_1kHz_15Hz,output_sig_arr,output_sig_arr2,SHORT_SIG_LENGTH);
}

void loop() {


}




void plot_2_signals(double *sig_src1_arr,double *sig_src2_arr,uint32_t sig_length)
{
  uint32_t i;
  for (i=0;i<sig_length;i++)
  {
    Serial.print(">sig_src1_arr:");
    Serial.print((sig_src1_arr[i]*1000)+2000);
    Serial.print("\n>sig_src2_arr:");
    Serial.println(sig_src2_arr[i]*1000);
  }
}
void plot_3_signals(double *sig_src1_arr,double *sig_src2_arr,double *sig_src3_arr,uint32_t sig_length)
{
  uint32_t i;
  for (i=0;i<sig_length;i++)
  {
    Serial.print(">sig_src1_arr:");
    Serial.print((sig_src1_arr[i]*1000)+2000);
    Serial.print("\n>sig_src2_arr:");
    Serial.println(sig_src2_arr[i]*1000);
    Serial.print("\n>sig_src3_arr:");
    Serial.println(sig_src3_arr[i]*1000);
  }
}

void plot_signal(double *sig_src_arr, uint32_t signal_length)
{
  unsigned int i;
   for( i=0;i<signal_length;i++){

    Serial.println(sig_src_arr[i]*1000);

 delay(10);

  }
}

void moving_average(double *sig_src_arr, double *sig_out_arr, uint32_t sig_length, uint32_t filter_pts)
{
  uint32_t i,j;
  for(i= floor(filter_pts/2);i<sig_length-floor(filter_pts/2)-1;i++){
  sig_out_arr[i]=0;
    for(j=-floor(filter_pts/2);j<floor(filter_pts/2);j++)
  {
    sig_out_arr[i] = sig_out_arr[i] + sig_src_arr[i+j]; 
  }

  sig_out_arr[i] = sig_out_arr[i]/filter_pts;
  }
}

 void recursive_moving_average(double *sig_src_arr, double *sig_out_arr, uint32_t sig_length, uint32_t filter_pts)
{
  uint32_t i,j;
  double ACC;
  ACC=0;
    for(i=0;i<filter_pts;i++)
    {
      ACC = ACC + sig_src_arr[i];
    }

   sig_out_arr[(filter_pts-1/2)]  = ACC/filter_pts;

      for(i= ceil(filter_pts/2);i<sig_length-ceil(filter_pts/2);i++)
      {
         ACC =ACC + sig_src_arr[i+(filter_pts-1)/2]- sig_src_arr[i-(uint32_t)ceil(filter_pts/2)];
         sig_out_arr[i]  = ACC/filter_pts;
      }
  
  
}


