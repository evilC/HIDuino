// Button test circuit: https://www.arduino.cc/en/Tutorial/DigitalReadSerial
// Joystick library: https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>

// Create the Joystick
Joystick_ Joystick;

// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 2;

void setup() {
  Serial.begin(9600);
  // Initialize Button Pins
  pinMode(pinToButtonMap, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}

// Last state of the button
int lastButtonState = 0;

void loop() {
  // Read pin values
  int currentButtonState = digitalRead(pinToButtonMap);
  if (currentButtonState != lastButtonState)
  {
    Joystick.setButton(0, currentButtonState);
    lastButtonState = currentButtonState;
  }

  if (Serial.available() > 0) {
    char inChar = Serial.read();
    Serial.println((String)"Input: " + inChar);
    switch (inChar) {
      case 'u':
        // Release joystick button
        Joystick.setButton(1, 0);
        break;
      case 'd':
        // Press joystick button
        Joystick.setButton(1, 1);
        break;
    }
  }

  delay(50);
}
