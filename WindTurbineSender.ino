#include "arduino_secrets.h"

#include <Wire.h>

const bool Numbers[11][7] = {{1,1,1,1,1,1,0}, //zero
                             {0,1,1,0,0,0,0}, //one
                             {1,1,0,1,1,0,1}, //two
                             {1,1,1,1,0,0,1}, //three
                             {0,1,1,0,0,1,1}, //four
                             {1,0,1,1,0,1,1}, //five
                             {1,0,1,1,1,1,1}, //six
                             {1,1,1,0,0,0,0}, //seven
                             {1,1,1,1,1,1,1}, //eight
                             {1,1,1,0,0,1,1}, //nine
                             {0,0,0,0,0,0,0} //Clear Display
};

#define ClearDisplay 10

int DisplayValue;

void setup() 
{
  Serial.begin(9600);
  //define pin modes
  pinMode(2,OUTPUT); //Segement A
  pinMode(3,OUTPUT); //Segement B
  pinMode(4,OUTPUT); //Segement C
  pinMode(5,OUTPUT); //Segement D
  pinMode(6,OUTPUT); //Segement E
  pinMode(7,OUTPUT); //Segement F
  pinMode(8,OUTPUT); //Segement G
  pinMode(9,OUTPUT); //Segement Decimal Point

  displayNumber(ClearDisplay); //make sure the display is off

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

int displayNumber(int numberToDisplay)
{
  int pin = 2;
  for(int segment = 0;segment<7;segment++)
  {
    digitalWrite(pin, Numbers[numberToDisplay][segment]);
    pin++;
  }
  return numberToDisplay;
}

void loop() 
{
  // first read in the generated voltage
  int GeneratedValue = analogRead(A0);
  // now we map it to a much smaller range, as we only have a single 0-9 display.
  DisplayValue = map(GeneratedValue, 0, 1023, 0, 9);
  displayNumber(DisplayValue);
  String str = "Voltage Generated: ";
  Serial.print(str); Serial.println(DisplayValue); Serial.println();
  // add a small delay so that the number doesnt change to rapidly to read.
  delay(1000);

}


void requestEvent() {
  Wire.write(DisplayValue); // respond with message of 1 byte
  // as expected by master
}
