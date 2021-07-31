//Maximun voltaje for ADC measuring
#define MAXVOLT 3.3
//ADC resolution
#define ADCRES 4095.0

//PINOUT DEFINED
#define COLDSENS 33
#define HOTSENS 34
#define PELTIER 30

//range values for overheating
#define MAXOVERHEAT 70.0
#define MINOVERHEAT 60.0
//range values for cooling
#define MINCOLD 5.0
#define MAXCOLD 10.0

float coldsens;
float hotsens;
float coldtemp;
float hottemp;
bool overheat = false;
bool cooling = true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {


  //Reading temperature sensors, coldsens and hotsens are in volts
  // coldsens = analogRead(COLDSENS) / ADCRES * MAXVOLT;
  // hotsens = analogRead(HOTSENS) / ADCRES * MAXVOLT;

  // Theorical formula calculated in excel. coldtemp is for 0-15º linealization. hottemp is for 50-60º linealization
  //coldtemp = coldsens / 0.059 - 30;
  //hottemp = hotsens / 0, 045 + 8, 53;
  hottemp = 15;
  //checking if peltier is overheating, if it is, wait to min overheating value
  if (hottemp > MAXOVERHEAT) {
    overheat = true;
  }
  if (overheat && hottemp < MINOVERHEAT) {
    overheat = false;
  }

  //If peltier is overheating, disconnect
  if (overheat) {
    digitalWrite(PELTIER, LOW);
  } else {

    // If cold temp is less than MINCOLD, disconnect peltier until cold temp is more than MAXCOLD
    if (coldtemp < MINCOLD) {
      cooling = false;
    }

    if (cooling == false) {
      if (coldtemp > MAXCOLD) {
        cooling = true;
        digitalWrite(PELTIER, HIGH);
      } else {
        digitalWrite(PELTIER, LOW);

      }
    } else {
      digitalWrite (PELTIER, HIGH);

    }


  }

}




}
