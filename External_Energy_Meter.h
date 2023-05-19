/*****************************************************
INCLUDES
*****************************************************/
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_INA219.h>
/*****************************************************
Variables/Defines
*****************************************************/
//Initialization of the INA219
Adafruit_INA219 ina219;

//Initialization of the ADS1115
Adafruit_ADS1115 ads;

//Only 3 measurements being taken (Voltage, Current, Power)
int channels = 3;
float avg_measure[3];

//How long to average the data for (in ms)
#define time_average_msec 100

//Checks time within the counter
long counter_avg;

//R_Sense resister value (in Ohms)
float R_Sense = 10;

//Checks time within the counter
long counter_avg;

//Checks what the time is and saves it
unsigned long time_check_msec;  

//Starts the milli clock
long time_now_msec;

//The time in seconds
float data_time_output_sec = 0.0;

//Change this to set the voltage range (1 - Between 0-5V, 2 - Between 5-10V, 3 - Between 10-15V, 4 - Between 15-20V, 5 - Between 20-25V)
int Voltage_In_Range_V = 1;

//Change this to change the gain of the ADS, (1 - 1x gain, 2 - 2x gain, 3 - 4x gain, 4 - 8x gain, 5 - 16x gain)
int ADS_Gain_Choice = 2;

//Equivalent Resistance of the Voltage Divider
float V_Divider_FixV = 2.0;
float V_Divider_FixA = 2.0;

//The voltage of one bit on the gain of 1 scale
float ADC_V_per_ADU;  
