/* ClickButton library demo

  Blinks a LED according to different clicks on one button.
  
  Short clicks:

    Single click - Toggle LED on/off
    Double click - Blink      (Toggles LED 2 times/second)
    Triple click - Fast blink (Toggles LED 5 times/second)
    
  Long clicks (hold button for one second or longer on last click):
    
    Single-click - Slow blink   (Toggles LED every second)
    Double-click - Sloow blink  (Toggles LED every other second)
    Triple-click - Slooow blink (Toggles LED every three seconds)


  The circuit:
  - LED attached from pin 10 to resistor (say 220-ish ohms), other side of resistor to GND (ground)
  - pushbutton attached from pin 4 to GND
  No pullup resistor needed, using the Arduino's (Atmega's) internal pullup resistor in this example.

  Based on the Arduino Debounce example.

  2010, 2013 raron
 
 GNU GPLv3 license
*/

#include "ClickButton.h"

// the LED
const int ledPin = 13;
int ledState = 0;
int relayHeadMousePin = 2;
int relayHouseMatePin = 3;


// the Button
const int buttonPin1 = 6;
ClickButton button1(buttonPin1, LOW, CLICKBTN_PULLUP);

// Arbitrary LED function 
int LEDfunction = 0;


void setup()
{
  pinMode(ledPin,OUTPUT);  
  pinMode(relayHeadMousePin,OUTPUT);  
  pinMode(relayHouseMatePin,OUTPUT);
  
  Serial.begin(9600);
  // Setup button timers (all in milliseconds / ms)
  // (These are default if not set, but changeable for convenience)
  button1.debounceTime   = 20;   // Debounce timer in ms
  button1.multiclickTime = 500;  // Time limit for multi clicks
  button1.longClickTime  = 1000; // time until "held-down clicks" register

    digitalWrite(relayHouseMatePin, HIGH);
    digitalWrite(relayHouseMatePin, HIGH);

}


void loop()
{
  // Update button state
  button1.Update();
  digitalWrite(relayHeadMousePin,digitalRead(buttonPin1));
  Serial.println(digitalRead(buttonPin1));
  
  if(button1.clicks == 3) houseMateClick();
  
  // update the LED
  digitalWrite(ledPin,ledState);
}
void houseMateClick()
{
  
  digitalWrite(relayHouseMatePin, LOW);
  delay(200);
  digitalWrite(relayHouseMatePin, HIGH);

}
