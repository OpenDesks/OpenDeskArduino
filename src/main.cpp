// Include the Stepper library:
#include <Arduino.h>

#include <motor_control.h>

MotorControl motorControl(2, 5, 200);

void setup()
{
  Serial.begin(9600);
  motorControl.setup();
}

bool activeCalibration(String data)
{
  return strstr(data.c_str(), "desk/activeCalibration/status:true");
}

void loop()
{
}