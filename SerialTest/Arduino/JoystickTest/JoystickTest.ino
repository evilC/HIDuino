// Button test circuit: https://www.arduino.cc/en/Tutorial/DigitalReadSerial
// Joystick library: https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>

// Create the Joystick
Joystick_ joystick;

// Constant that maps the phyical pin to the joystick button.
const int pin_to_button_map = 2;

void setup()
{
	Serial.begin(115200);
	// Initialize Button Pins
	pinMode(pin_to_button_map, INPUT_PULLUP);

	// Initialize Joystick Library
	joystick.begin();
}

// Last state of the button
int last_button_state = 0;

void loop()
{
	// Read pin values
	const auto current_button_state = digitalRead(pin_to_button_map);
	if (current_button_state != last_button_state)
	{
		joystick.setButton(0, current_button_state);
		last_button_state = current_button_state;
	}

	if (Serial.available() > 0)
	{
		const char in_char = Serial.read();
		Serial.println(static_cast<String>("Input: ") + in_char);
		switch (in_char)
		{
		case 'u':
			// Release joystick button
			joystick.setButton(1, 0);
			Serial.println("Setting Button 1 to released");
			break;
		case 'd':
			// Press joystick button
			joystick.setButton(1, 1);
			Serial.println("Setting Button 1 to pressed");
			break;
		default: ;
		}
	}

	delay(50);
}
