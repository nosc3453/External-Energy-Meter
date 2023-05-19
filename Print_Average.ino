/*****************************************************
Print Average Function
*****************************************************/
void Print_avg() {
  /* Prints the results from the Measure Average function to the serial monitor */
  //Get the time in ms, convert it to seconds
  data_time_output_sec = millis();
  data_time_output_sec=data_time_output_sec/1000;

  //Printing averages to the serial monitor
  Serial.print(data_time_output_sec);
  Serial.print(",");
  
  for (int i = 0; i < channels-1; i++) 
  {
    Serial.print(avg_measure[i],5);
    Serial.print(",");
  }
  
  Serial.print(avg_measure[channels-1],5);
  Serial.println();
}
