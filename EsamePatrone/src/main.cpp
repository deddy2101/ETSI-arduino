#include <Arduino.h>

//signal for testing
//extern double Input[128];
           

#define LPF_FREQUENCY 4

//define ADC frequency that is used by arduino to sample the signal
// ADC frequency is calculated in hz we have to convert it to ms in the code
#define ADC_FREQUENCY 100
#define NUMBER_OF_SAMPLES 200
double Input[NUMBER_OF_SAMPLES];
double Output[NUMBER_OF_SAMPLES];


const double frequency1 = 2.0;  // Frequenza della prima sinusoidale (in Hz)
const double frequency2 = 10.0;  // Frequenza della seconda sinusoidale (in Hz)
const double amplitude1 = 0.1;  // Ampiezza della prima sinusoidale
const double amplitude2 = 0.1;  // Ampiezza della seconda sinusoidale
const double samplingPeriod = 1.0 / (float)ADC_FREQUENCY;  // Periodo di campionamento (in secondi)



//function used to test the filter
void generateSamples(){
  for (int i = 0; i < 128; i++) {
    double time = i * samplingPeriod;  // Tempo corrente
    
    // Generazione delle due sinusoidi
    double signal1 = amplitude1 * sin(2 * PI * frequency1 * time);
    double signal2 = amplitude2 * sin(2 * PI * frequency2 * time);
    
    // Somma dei segnali
    double sum = signal1 + signal2;
    
    // Salvataggio del campione nell'array
    Input[i] = sum;
  }
}

//use at the exam
void readFromAnalogPin(){

  //we acquire the signal from the ADC and store it in the Input array using the defined ADC_FREQUENCY
  for (unsigned int i = 0; i < NUMBER_OF_SAMPLES; i++)
  {
    Input[i] = analogRead(A0);
    //we have to convert the ADC_FREQUENCY to ms
    delay(1000 / ADC_FREQUENCY);
  }
}

void setup() {
 

  Serial.begin(115200);
   // calculating frequency ratio as LPF_FREQUENCY/ADC_FREQUENCY
  Serial.println(samplingPeriod, 4);
  double frequency_ratio = (double)LPF_FREQUENCY / (double)ADC_FREQUENCY;
  Serial.println((double)ADC_FREQUENCY);
  Serial.println((double)LPF_FREQUENCY);
  Serial.println(frequency_ratio, 4);
  //we have to calculate the coefficent 
  double coefficent = 1 / (2 * PI * frequency_ratio);
  //then a and b coefficents
  double a = coefficent / (1.0 + coefficent);
  double b = 1.0 - a;
  //print out the coefficents
  Serial.println(a);
  Serial.println(b);
  Serial.println("Starting ADC conversion");
  generateSamples();
  //readFromAnalogPin();

  Serial.println("ADC conversion finished");

  //we print the signal to the serial monitor using teleplot
  for (unsigned int i = 0; i < NUMBER_OF_SAMPLES; i++)
  {
    Serial.print(">Sampled signal:");
    Serial.println(Input[i]);
  }

  //now we have to use the butterworth filter to filter the signal at 4hz
  for (int i=0; i<NUMBER_OF_SAMPLES; i++)
  {
    if (i == 0)
      Output[0] = b * Input[0];
    else
    Output[i] = a * Output[i-1] + b * Input[i] + b * Input[i-1];
  }

  //we print the filtered signal to the serial monitor using teleplot
  for (unsigned int i = 0; i < NUMBER_OF_SAMPLES; i++)
  {
    Serial.print(">Filtered signal:");
    Serial.println(Output[i]);
  }

  //the output signal seems to have a logarithmic shape summed with teh filtered signal
  //this should be ok with the implementation of the butterworth filter
  
}

void loop() {
  // put your main code here, to run repeatedly:
}

