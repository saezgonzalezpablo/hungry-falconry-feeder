#include <math.h>
//Maximun voltaje for ADC measuring
#define MAXVOLT 3.3
//ADC resolution
#define ADCRES 4095.0

//PINOUT DEFINED
#define COLDSENS A0
#define HOTSENS A1
#define PELTIER 30

//range values for overheating
#define MAXOVERHEAT 70.0
#define MINOVERHEAT 60.0
//range values for cooling
#define MINCOLD 5.0
#define MAXCOLD 10.0

// Aux resistor for thermistors
float RHOT = 22000;   // for values near 60º
float RCOLD = 200000; //for values near 10º

//for values: https://www.thinksrs.com/downloads/programs/Therm%20Calc/NTCCalibrator/NTCcalculator.htm
float A = 0.7504758677E-3;
float B = 2.101040115E-4;
float C = 1.210003217E-7;

bool overheat = false;
bool cooling = true;

float thermistor(int RawADC, float RAux)
{
  long resistor;
  float temp;

  resistor = RAux * ((1024.0 / RawADC) - 1); // termistor resistor from analogic reading

  temp = log(resistor);
  temp = 1 / (A + (B * temp) + (C * temp * temp * temp));
  temp = temp - 273.15; // Kelvin to centigrades

  return temp;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{

  float coldtemp;
  float hottemp;

  coldtemp = thermistor(analogRead(COLDSENS), RCOLD);
  hottemp = thermistor(analogRead(HOTSENS), RHOT);

  //checking if peltier is overheating, if it is, wait to min overheating value
  if (hottemp > MAXOVERHEAT)
  {
    overheat = true;
  }
  if (overheat && hottemp < MINOVERHEAT)
  {
    overheat = false;
  }

  //If peltier is overheating, disconnect
  if (overheat)
  {
    digitalWrite(PELTIER, LOW);
  }
  else
  {

    // If cold temp is less than MINCOLD, disconnect peltier until cold temp is more than MAXCOLD
    if (coldtemp < MINCOLD)
    {
      cooling = false;
    }

    if (cooling == false)
    {
      if (coldtemp > MAXCOLD)
      {
        cooling = true;
        digitalWrite(PELTIER, HIGH);
      }
      else
      {
        digitalWrite(PELTIER, LOW);
      }
    }
    else
    {
      digitalWrite(PELTIER, HIGH);
    }
  }
}
