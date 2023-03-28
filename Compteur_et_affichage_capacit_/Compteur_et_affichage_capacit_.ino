#include <Wire.h>
#include "rgb_lcd.h"
#include "Ultrasonic.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
int count = 0; // compteur qui commence a 0
int capacity = 0; // la capacité de personne dans le batiment qui est a 0
int surface;
Ultrasonic ultrasonic1(8);
Ultrasonic ultrasonic2(10);


void setup() {

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);

}

void loop() {

  {
    capacity = 40; // calculer la capacité de personne avec le moniteur
    surface = capacity / 4 ; // calcul de personne par m²

    long total = 10;
    int depassement = total - capacity;


    long RangeInCentimeters1;
    RangeInCentimeters1 = ultrasonic1.MeasureInCentimeters();

    long RangeInCentimeters2;
    RangeInCentimeters2 = ultrasonic2.MeasureInCentimeters();



    if ((RangeInCentimeters1 < 100 && RangeInCentimeters1 > 200  && RangeInCentimeters2 > 100 && RangeInCentimeters2 < 200)) {
      count = count++; // si le capteur 1 réagit en premier ajouter +1 personne
    }

    Serial.print("Distance entrée :");
    Serial.print(RangeInCentimeters1);

    if ((RangeInCentimeters1 > 100 && RangeInCentimeters1 < 200) && (RangeInCentimeters2 < 100 && RangeInCentimeters2 > 200)) {
      count = count--; // si le capteur 2 réagit en premier ajouter -1 personne
    }

    Serial.print("Distance sortie :");
    Serial.print(RangeInCentimeters2);



    lcd.setCursor(0, 1);
    lcd.print("dans le Batiment :");
    lcd.print(count);

    Serial.print("dans le Batiment :");
    Serial.print(count);

  }
  if ( total > capacity ) {
    lcd.setCursor(1, 1);
    lcd.print("Capacité dépasser de : ");
    lcd.print(depassement); // nombre de personne qui sont en trop dans le LCD

    Serial.print("Capacité dépasser de : ");
    Serial.print(depassement); // nombre de personne qui sont en trop dans le moniteur
  }

  lcd.setCursor(1, 1);
  lcd.print("Capacity est :"); // afficher dans le LCD la capacité de personne dans le batiment
  lcd.print(capacity);

  Serial.print("Capacity est :"); // afficher dans le moniteur la capacité de personne dans le batiment
  Serial.print(capacity);
}
