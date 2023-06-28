#include <data_processing.h>

DataProcessing::DataProcessing()
{
}

String DataProcessing::getUnitOfMeasurement()
{
    return unitOfMeasurement;
}
String DataProcessing::getCrankDirection()
{
    return crankDirection;
}
float DataProcessing::getLowestSetting()
{
    return lowestSetting;
}
float DataProcessing::getHighestSetting()
{
    return highestSetting;
}
float DataProcessing::getCurrentHeight()
{
    return currentHeight;
}
float DataProcessing::getCalibratedHeight()
{
    return calibratedHeight;
}
void DataProcessing::setUnitOfMeasurement(String unitOfMeasurement)
{
    this->unitOfMeasurement = unitOfMeasurement;
}
void DataProcessing::setCrankDirection(String crankDirection)
{
    this->crankDirection = crankDirection;
}
void DataProcessing::setLowestSetting(float lowestSetting)
{
    this->lowestSetting = lowestSetting;
}
void DataProcessing::setHighestSetting(float highestSetting)
{
    this->highestSetting = highestSetting;
}
void DataProcessing::setCurrentHeight(float currentHeight)
{
    this->currentHeight = currentHeight;
}
void DataProcessing::setCalibratedHeight(float calibratedHeight)
{
    this->calibratedHeight = calibratedHeight;
}
bool DataProcessing::calibrationDataGrabbing(String data)
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
bool DataProcessing::isAllDataCollected()
{
    return !unitOfMeasurement.equalsIgnoreCase("") &&
           !crankDirection.equalsIgnoreCase("") &&
           lowestSetting != 0 &&
           highestSetting != 0 &&
           currentHeight != 0 &&
           calibratedHeight != 0;
}

MotorControl::UnitOfMeasure DataProcessing::getUnitOfMeasure()
{
    if (isAllDataCollected())
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
                    return MotorControl::IN;
                }
                else if (unitOfMeasurement.equalsIgnoreCase("cm"))
                {
                    return MotorControl::CM;
                }
            }
        }
    }
}