/*By Richard Langner, Sheffield, UK, 11 May 2025

Example code using the 'MultiTapButton' class
*************************************************
*     ROTARY ENCODER without interrupts         *
*     GPIO pin numbers are for Wemos D1 mini    *
*     Change pins as required for your device   *
*************************************************

Captures clicks and direction of a rotary encoder
All pins have pull-ups enabled in software
Pins CLK=D7  DAT=D6  BUTTON=D5
Results are sent to the serial port.
*/

#include <Arduino.h>
#include "MultiTapButton.h"
// #include "SimpleTimer.h"

// Set the button and the pin numbers for your microcontroller
#define CLK D7    // Switch is connected between D7 and Ground
#define DAT D6    // Switch is connected between D6 and Ground
#define BUTTON D5 // Switch is connected between D5 and Ground

// Create 3 MultiTapButton objects with active LOW pins,
MultiTapButton C(CLK, LOW, 1), D(DAT, LOW, 1), button(BUTTON, LOW);
// SimpleTimer timer1;
int counter = 0;

void setup()
{
    pinMode(CLK, INPUT_PULLUP); // Set the switched pins as an input with pullup
    pinMode(DAT, INPUT_PULLUP);
    pinMode(BUTTON, INPUT_PULLUP);
    pinMode(D4, OUTPUT);
    Serial.begin(74880); // Start the Serial output
    Serial.println("Ready");
    digitalWrite(D4, HIGH); // OFF
}

bool lastC = C.down();
bool lastD = D.down();

int getCounter () {
  static int counter=0;
  
  bool currC = C.down();
  bool currD = D.down();

  if(currC == lastC) return counter;  // Clock has not changed
  // if(currD == lastD) return counter;  // Data has not changed

  Serial.printf("C= %d  D= %d\n", currC, currD);

  if(currD == currC){
    counter++;}
  else{
    counter--;
  }
  Serial.printf("Counter = %d\n", counter);
  lastC = currC;
  lastD = currD;
  return counter;
}

void loop()
{
  getCounter();
  delay(10);
}
