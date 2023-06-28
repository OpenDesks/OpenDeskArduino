#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <motor_control.h>
class DataProcessing
{
public:
    DataProcessing();
    bool allDataCollected = false;
    bool calibrationDataGrabbing(String data);
    bool isAllDataCollected();
    MotorControl::UnitOfMeasure getUnitOfMeasure();
    // Data Getters----------------
    String getUnitOfMeasurement();
    String getCrankDirection();
    float getLowestSetting();
    float getHighestSetting();
    float getCurrentHeight();
    float getCalibratedHeight();

protected:
    // Required data----------------
    String unitOfMeasurement = "";
    String crankDirection = "";
    float lowestSetting = 0;
    float highestSetting = 0;
    float currentHeight = 0;
    float calibratedHeight = 0;
    // Data Setters----------------
    void setUnitOfMeasurement(String unitOfMeasurement);
    void setCrankDirection(String crankDirection);
    void setLowestSetting(float lowestSetting);
    void setHighestSetting(float highestSetting);
    void setCurrentHeight(float currentHeight);
    void setCalibratedHeight(float calibratedHeight);
};
