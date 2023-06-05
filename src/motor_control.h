
#include <Arduino.h>
#include <Stepper.h>
#include <stdlib.h>
#include <string.h>

class MotorControl
{
protected:
    int StepX;
    int DirX;
    int stepsPerRevolution;
    int currentPosition = 0; // Variable to track the current position

public:
    MotorControl(int stepPin, int dirPin, int stepsPerRevolution);
    void spinForSteps(int steps, bool dir = true);
    void spinToTarget();
    void spinForRotation(int rotations);
    void setSpeed(float speed);
    void setAcceleration(float acceleration, float targetSpeed);
    void setup();
};