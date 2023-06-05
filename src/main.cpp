// Include the Stepper library:
#include <Arduino.h>
#include <Stepper.h>
#include <stdlib.h>
#include <string.h>
#include <motor_control.h>
// using namespace std;
// Define number of steps per revolution:
// const int StepX = 2;
// const int DirX = 5;
// const int stepsPerRevolution = 200;
// const int revsPerInch = 1;
MotorControl motorControl(2, 5, 200);

void setup()
{
  Serial.begin(9600);
  motorControl.setup();
}

void loop()
{
  // motorControl.spinForRotation(3);
  // delay(2000);
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

      Serial.println("desk/activeCalibration/status:false");
    }
  }
}