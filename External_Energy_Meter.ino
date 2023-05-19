/*****************************************************
External Energy Meter
By Nathan Mattock and Noah Schwartz

This is the main software for the external energy meter, a way to measure the power consumption of a system with negligible impact on its load. The project aims to measure a system that has
a voltage range of 0-25V and current range of 1-5mA. This code takes an input from the user clarifying the input voltage used. Depending on the input voltage, the ADS gain must also be 
changed so that an accurate measurement may be taken. 
*****************************************************/
#include "External_Energy_Meter.h"
/*****************************************************
System Setup
*****************************************************/
void setup() {
  /* System Setup */
  Serial.begin(115200);
  time_now_msec = millis();  //needed?
  ADS_SetUp();
  ads.setDataRate(RATE_ADS1115_860SPS);

  //Confirming ADS1115 and INA219 are operating as they should
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

   if (! ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
}
/*****************************************************
System Loop
*****************************************************/
void loop(void) {
  /* Main loop */
  Measure_average();
  Print_avg();
}

/*****************************************************
ADS and Measurement Setup
*****************************************************/
void ADS_SetUp() {
  /* Setup for ADC calulations */
  //Changes the value of the equivalent resistance, depending on the input voltage
  switch (Voltage_In_Range_V) {
    case 1://Between 0-5V
      V_Divider_FixA = 2.013;
      V_Divider_FixV = 2;      
      break;

    case 2://Between 5-10V
      V_Divider_FixA = 4.3;
      break;

    case 3://Between 10-15V
      V_Divider_FixA = 6.3;
      break;

    case 4://Between 15-20V
      V_Divider_FixA = 8.6;
      break;

    case 5://Between 20-25V
      V_Divider_FixA = 11;
      break;
  }
  //Changes the gain of the ADS, the higher the case number, the more precise the measurement will be. 
  switch (ADS_Gain_Choice) {
    case 1:
     ads.setGain(GAIN_TWOTHIRDS);// 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
      ADC_V_per_ADU = 0.1875/1000;
      break;

    case 2:
      ads.setGain(GAIN_ONE); // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
       ADC_V_per_ADU = 0.125/1000;
      break;

    case 3:
     ads.setGain(GAIN_TWO); // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
      ADC_V_per_ADU = 0.0625/1000;
      break;

    case 4:
     ads.setGain(GAIN_FOUR);  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
      ADC_V_per_ADU = 0.03125 * 1e-3;
      break;

    case 5:
     ads.setGain(GAIN_EIGHT);  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
      ADC_V_per_ADU = 0.015625 * 1e-3;
      break;
      
    case 6:
     ads.setGain(GAIN_SIXTEEN);  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
      ADC_V_per_ADU = 0.0078125 * 1e-3;
      break;
  }

 
}
