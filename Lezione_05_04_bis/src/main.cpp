#include <Arduino.h>
#define  SIG_LENGTH 320
#define SHORT_SIG_LENGTH 88

extern double InputSignal_1kHz_15kHz[SIG_LENGTH];
extern double short_InputSignal_1kHz_15Hz[SHORT_SIG_LENGTH];

double REX[SHORT_SIG_LENGTH/2];
double IMX[SHORT_SIG_LENGTH/2];

void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, uint32_t sig_length);
void plot_signal(double *sig_src_arr, uint32_t signal_length);
void plot_both(void);
void get_dft_output_mag();


/**@note USE full signal length for DUE demo**/

void setup() {
Serial.begin(115200);


  calc_sig_dft(&short_InputSignal_1kHz_15Hz[0],&REX[0], &IMX[0],SHORT_SIG_LENGTH);
  get_dft_output_mag();

 plot_signal(REX, SHORT_SIG_LENGTH/2);

}

void loop() {


}

void calc_sig_dft(double *sig_src_arr, double *sig_dest_rex_arr, double *sig_dest_imx_arr, uint32_t sig_length)
{
  int i,k,j;
  for(j=0;j<(sig_length/2);j++)
  {
     sig_dest_rex_arr[j] =0;
      sig_dest_imx_arr[j] =0;
  }
  
   for(k=0;k<(sig_length/2);k++)
  {
    for(i=0;i<sig_length;i++)
    {
               sig_dest_rex_arr[k] =  sig_dest_rex_arr[k] + sig_src_arr[i]*cos(2*PI*k*i/sig_length);
               sig_dest_imx_arr[k] =  sig_dest_imx_arr[k] - sig_src_arr[i]*sin(2*PI*k*i/sig_length);


    }
  }
}

void get_dft_output_mag(void)
{
  uint32_t k;
  for(k=0;k<SHORT_SIG_LENGTH/2;k++)
  {
    REX[k] = sqrt(pow(REX[k],2)+pow(IMX[k],2));
  }
}


void plot_signal(double *sig_src_arr, uint32_t signal_length)
{
  int i;
   for( i=0;i<signal_length;i++){
  Serial.println(sig_src_arr[i]);
 delay(10);

  }
}

