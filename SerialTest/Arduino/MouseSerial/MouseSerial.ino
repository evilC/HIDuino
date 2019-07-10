// Button test circuit: https://www.arduino.cc/en/Tutorial/DigitalReadSerial
// Plus mouse tester: https://www.arduino.cc/en/Tutorial/KeyboardAndMouseControl?from=Tutorial.KeybaordAndMouseControl
#include <Mouse.h>

// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 2;
int lastState = -1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Mouse.begin();
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
  //delay(1000);
  //Serial.println("Initialized");
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(pushButton);

  if (buttonState != lastState){
    // print out the state of the button:
    Serial.println(buttonState);
  }

  if (Serial.available() > 0) {
    char inChar = Serial.read();
    Serial.println((String)"Input: " + inChar);
    switch (inChar) {
      case 'u':
        // move mouse up
        Mouse.move(0, -40);
        break;
      case 'd':
        // move mouse down
        Mouse.move(0, 40);
        break;
      case 'l':
        // move mouse left
        Mouse.move(-40, 0);
        break;
      case 'r':
        // move mouse right
        Mouse.move(40, 0);
        break;
      case 'm':
        // perform mouse left click
        Mouse.click(MOUSE_LEFT);
        break;
    }
  }
  lastState = buttonState;
  delay(1);        // delay in between reads for stability
}
