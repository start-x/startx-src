/**
 * Standard library fo BikeX using Arduino.
 * 
 * Dependencies:
 * 		Install https://code.google.com/p/ebl-arduino/ library to could use
 * 		the ButtonEvent
 * 
 */

#include <Servo.h>
#include <ButtonEvent.h>


/**
 * Macros to define the output
 * from sensor
 */

#define ALL_VALUES '0'
#define DIRECTION_MSP '1'
#define VELOCITY_MSP '2'
#define BREAK_MSP '3'

#define SERVO_PIN 9
#define VELOCITY_PIN 12
#define DIRECTION_PIN A0

/**
 * Sad globals variables
 * 
 */
Servo servo;
int bike_interval_seconds=0;

void onDown(ButtonInformation* Sender);
void onUp(ButtonInformation* Sender);
void onHold(ButtonInformation* Sender);
void onDouble(ButtonInformation* Sender);
int direction();
int velocity();
int readline();


void setup()
{
    Serial.begin(9600);
    Serial.println("Device ready");
    servo.attach(SERVO_PIN);  // attaches the servo on pin 9 to the servo object 
	ButtonEvent.addButton(VELOCITY_PIN,       //button pin
	                onDown,   //onDown event function
	                onUp,     //onUp event function
	                onHold,   //onHold event function
	                1000,     //hold time in milliseconds
	                onDouble, //onDouble event function
	                200);     //double time interval

}

void loop()
{

    int input = 0;
    char buffer[80];

	if (Serial.available() > 0)
	{
                        
			// input = Serial.read();
			readline(Serial.read(), buffer, 80);
			Serial.println(buffer);
			switch(input)
			{
				case ALL_VALUES:
					Serial.print(direction());
					Serial.print(' ');
					Serial.print(velocity());
					Serial.print(' ');
					Serial.println(servo.read()); // return the angle of the servo (0<servo<180)
					break;

				case DIRECTION_MSP: //1
					Serial.println(direction());
					break;
				case VELOCITY_MSP: //2
					Serial.println(velocity());
					break;
				// case BREAK_MSP: // 3
				// 	Serial.flush();
				// 	Serial.print("Enter the new servo angle: ");
				// 	input = Serial.read();
				// 	Serial.println(breaker(input));
				// 	break;
				default:
					Serial.print("new servo angle: ");
                    Serial.println(breaker(input));
			}
		
	}
}

int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}

int direction()
{
	int pot_direction = analogRead(DIRECTION_PIN);
	pot_direction = map(pot_direction, 0, 1023, 0, 179); // 0 <= pot_direction <= 179
	return pot_direction;
}

int velocity()
{
	return bike_interval_seconds;
}

int breaker(int value)
{
	servo.write(value);
	return servo.read();
}

void onDown(ButtonInformation* Sender){}

void onUp(ButtonInformation* Sender){}

void onHold(ButtonInformation* Sender){}

void onDouble(ButtonInformation* Sender){}

