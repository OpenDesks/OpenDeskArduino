// Include the Stepper library:
#include <Arduino.h>
#include <Stepper.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
// Define number of steps per revolution:
const int StepX = 2;
const int DirX = 5;

const int stepsPerRevolution = 200;
const int revsPerInch = 1;

void spinForDist(double inches, bool dir)
{
  if (dir)
  {
    digitalWrite(DirX, LOW);
  }
  else
  {
    digitalWrite(DirX, HIGH);
  }
  int steps = inches * revsPerInch * stepsPerRevolution;
  for (int x = 0; x < steps; x++)
  {
    digitalWrite(StepX, HIGH);
    delayMicroseconds(500);
    digitalWrite(StepX, LOW);
    delayMicroseconds(500);
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(StepX, OUTPUT);
  pinMode(DirX, OUTPUT);
}

void loop()
{
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    data.trim(); // Remove leading/trailing whitespace

    if (data.length() > 0)
    {
      // Process the received data here
      Serial.println("Received data: " + data);

      // Remove quotes from the string
      if (data.startsWith("\"") && data.endsWith("\""))
      {
        data = data.substring(1, data.length() - 1);
      }

      // Convert the string to a double
      double inches = data.toDouble();

      if (inches != 0.0)
      {
        // Print the converted value
        Serial.print("Inches: ");
        Serial.println(inches);

        // Perform the desired action using the converted value
        spinForDist(inches, true);
      }
      else
      {
        Serial.println("Invalid input. Please provide a valid number.");
      }
    }
  }

  // Serial.println(Serial.readString());
  delay(1000); // delay for 1 second
}