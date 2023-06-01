// Include the Stepper library:
#include <Arduino.h>
#include <Stepper.h>
#include <stdlib.h>
#include <string.h>
// using namespace std;
// Define number of steps per revolution:
const int StepX = 2;
const int DirX = 5;

const int stepsPerRevolution = 200;
const int revsPerInch = 1;
void spinForSteps(int steps)
{
  digitalWrite(DirX, LOW);

  for (int x = 0; x < steps; x++)
  {
    digitalWrite(StepX, HIGH);
    delayMicroseconds(500);
    digitalWrite(StepX, LOW);
    delayMicroseconds(500);
  }
}
void spinForRotation(int rotations)
{
  int steps = rotations * stepsPerRevolution;
  spinForSteps(steps);
}
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
    const char *foundCalibrationData = strstr(data.c_str(), "calibration");
    const char *foundIsCalibrating = strstr(data.c_str(), "desk/activeCalibration/status:true");
    if (foundCalibrationData)
    {
      Serial.println("Received data: " + data);
    }
    else if (foundIsCalibrating)
    {
      spinForRotation(10);
      Serial.println("desk/activeCalibration/status:false");
    }
  }
}