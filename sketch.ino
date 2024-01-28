
#include <math.h>

const float beta = 3650.0;  
const float T0 = 273.15 + 25.0;  
const float R0 = 10000.0;  

const int analogPin = A0;

float calculateTemperature(int rawValue) {
  float R = 10000.0 * (1023.0 / rawValue - 1.0);  
  float T = 1.0 / (1.0 / T0 + 1.0 / beta * log(R / R0));  
  return T - 273.15;  
}

void heat() {
  int rawValue = analogRead(analogPin);  
  float temperature = calculateTemperature(rawValue);  
  if (temperature < 8.0) {
    Serial.println("Нагрев");
  }
}

void setup() {
  Serial.begin(9600); 
}

void loop() {
  heat();  
  delay(1000); 
}
