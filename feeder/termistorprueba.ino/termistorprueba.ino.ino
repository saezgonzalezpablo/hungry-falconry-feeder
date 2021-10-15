#include <math.h>

#define PIN A0  //Entrada analogica

float R2 = 22000;      //Valor medido de R2, no exactamente 10K, cambialo por el valor que uses tu.

float A = 0.7504758677E-3; //¡¡¡Datos calculados para un caso concreto...
float B = 2.101040115E-4;  //...debes cambiarlos por los que calcules tu...
float C = 1.210003217E-7;  //...de tu propio termistor NTC!!!

float termistor(int RawADC) {
  
  long resistencia;  
  
  float temp;

  resistencia = R2*((1024.0 / RawADC) - 1); //Calculamos R1 mediante la lectura analogica
  
  temp = log(resistencia);
  
  temp = 1 / (A + (B * temp) + (C * temp * temp * temp));
  
  temp = temp - 273.15;  // Kelvin a grados centigrados                      

  return temp;
  
}

void setup() {
  
  Serial.begin(57600);
  
}

void loop() {
  
  float temp;
  
  temp = termistor(analogRead(PIN));
  
  Serial.print("Temperatura: ");

  Serial.print(temp,1);
  
  Serial.println();
  
  delay(1000);
  
}
