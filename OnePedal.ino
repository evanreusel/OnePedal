/*
 * OnePedal
 * By Erik Van Reusel
 * A sketch which will send a mouse click (or click and hold) using a relay, and send a short pulse to another relay to turn on a smart home device (HouseMate)
 */

#include "ClickButton.h"

// the LED

int relayHeadMousePin = 2;
int relayHouseMatePin = 3;


// the Pin where the pedal is connected to
const int pedalPin = 6;
//define as a clickbutton/input.
ClickButton pedalButton(pedalPin, LOW, CLICKBTN_PULLUP);

void setup()
{
  //the void 'setup' will execute when the arduino powers on, so basically once
  //define the relays as output
  pinMode(relayHeadMousePin,OUTPUT);  
  pinMode(relayHouseMatePin,OUTPUT);
  //
  Serial.begin(9600);
  // Setup button timers (all in milliseconds / ms)
  pedalButton.debounceTime   = 20;   // Debounce timer in ms
  pedalButton.multiclickTime = 500;  // Time limit for multi clicks
  pedalButton.longClickTime  = 1000; // time until "held-down clicks" register
  //send a "HIGH" signal to the relays (The relay is then turned off)
    digitalWrite(relayHouseMatePin, HIGH);
    digitalWrite(relayHouseMatePin, HIGH);

}


void loop()
{
  //This code will run over and over again after the setup is done.
  // Update button/pedal state
  pedalButton.Update();
  //set the signal of the relay to the state of the pedal pin
  digitalWrite(relayHeadMousePin,digitalRead(pedalPin));
  
  if(pedalButton.clicks == 3) houseMateClick();
}
void houseMateClick()
{
  // set the relay to LOW, which will turn it on
  digitalWrite(relayHouseMatePin, LOW);
  //wait for 200 milliseconds
  delay(200);
  //give a HIGH signal to the housemate relay, causing the relay to turn off.
  digitalWrite(relayHouseMatePin, HIGH);

}
