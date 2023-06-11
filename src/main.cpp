// Include the Stepper library:
#include <Arduino.h>

#include <motor_control.h>

MotorControl motorControl(2, 5, 200);
String calibrationData[6];
bool allDataCollected = false;

void setup()
{
  Serial.begin(9600);
  // motorControl.setSpeed(12);
  motorControl.setup();
}

bool calibrationDataGrabbing(String data)
{
  const char *foundCalibrationData = strstr(data.c_str(), "calibration");
  if (foundCalibrationData)
    for (int i = 0; i < 6; i++)
    {
      if (calibrationData[i] == "")
      {
        calibrationData[i] = data;
        break;
      }
    }
}
bool isAllDataCollected()
{
  int counter = 0;
  for (int i = 0; i < 6; i++)
  {
    if (calibrationData[i] != "")
    {
      counter++;
    }
  }
  if (counter == 6)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void calibrationDataProcessing()
{
  if (!isAllDataCollected())
  {
    for (int i = 0; i < 6; i++)
    {
      if (strstr(calibrationData[i].c_str(), "unitOfMeasurement"))
      {

        int delimiterPos = calibrationData[i].indexOf(":");
        String unitOfMeasurement = calibrationData[i].substring(delimiterPos + 1);
        unitOfMeasurement.trim();
        if (unitOfMeasurement.equalsIgnoreCase("in"))
        {
          Serial.println("in entered");
          motorControl.setUnitOfMeasure(MotorControl::IN);
        }
        else if (unitOfMeasurement.equalsIgnoreCase("cm"))
        {
          motorControl.setUnitOfMeasure(MotorControl::CM);
        }
      }
      String highBound = "";
      String lowBound = "";
      if (strstr(calibrationData[i].c_str(), "lowestSetting"))
      {
        int delimiterPos = calibrationData[i].indexOf(":");
        lowBound = calibrationData[i].substring(delimiterPos + 1);
        lowBound.trim();
      }
      if (strstr(calibrationData[i].c_str(), "highestSetting"))
      {
        int delimiterPos = calibrationData[i].indexOf(":");
        highBound = calibrationData[i].substring(delimiterPos + 1);
        highBound.trim();
      }
      if (!highBound.equals("") && !lowBound.equals(""))
      {
        Serial.println("setMotorBounds entered");
        motorControl.setMotorBounds(lowBound.toInt(), highBound.toInt());
      }
    }
  }
}
bool activeCalibration(String data)
{
  return strstr(data.c_str(), "desk/activeCalibration/status:true");
}

void loop()
{
  calibrationDataProcessing();
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');
    calibrationDataGrabbing(data);
    if (activeCalibration(data))
    {

      Serial.println("desk/activeCalibration/status:false");
    }
  }
}