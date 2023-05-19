/*****************************************************
Average Measure Function
*****************************************************/
void Measure_average() {
  /* Measures the average voltage, current, and power, in a given timeframe */
  //Reset avg_measure for clean results
  for (int i = 0; i <= 2; i++) 
  {
    avg_measure[i] = 0.0;
  }
  
  //Reset counter and initialize the time
  counter_avg = 0;
  time_check_msec = millis();
  //Averaging loop
  while (millis()<=time_check_msec+time_average_msec) {
      //Reading Voltage (V)
      avg_measure[0] = ads.readADC_Differential_0_1() * ADC_V_per_ADU * V_Divider_FixV + avg_measure[0];
      //Reading Current (A)
      avg_measure[1] = ina219.getCurrent_mA()/1000+ avg_measure[1];
      //Reading Power (W)
      avg_measure[2] = ads.readADC_Differential_0_1() * ADC_V_per_ADU * V_Divider_FixV * ina219.getCurrent_mA()/1000 +avg_measure[2];

      //Increment the counter, for it what each measurement will be divided by to get the average
      counter_avg++;
  }
  for (int i = 0; i < channels; i++) {
    avg_measure[i] = avg_measure[i] / (counter_avg * 1.0);
  }

}
