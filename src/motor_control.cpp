#include "motor_control.h"

MotorControl::MotorControl(int stepPin, int dirPin, int stepsPerRevolution)
{
    StepX = stepPin;
    DirX = dirPin;
    this->stepsPerRevolution = stepsPerRevolution;
}
void MotorControl::setup()
{
    Serial.begin(9600);
    pinMode(StepX, OUTPUT);
    pinMode(DirX, OUTPUT);
    digitalWrite(DirX, LOW);
}
void MotorControl::spinForSteps(int steps, bool dir)
{
    if (dir)
        digitalWrite(DirX, LOW);
    else
        digitalWrite(DirX, HIGH);

    for (int x = 0; x < steps; x++)
    {
        digitalWrite(StepX, HIGH);
        delayMicroseconds(500);
        digitalWrite(StepX, LOW);
        delayMicroseconds(500);
        if (dir)
            currentPosition++;
        else
            currentPosition--;
    }
}
void MotorControl::spinToTarget()
{
}
void MotorControl::spinForRotation(int rotations)
{
    int steps = rotations * stepsPerRevolution;
    spinForSteps(steps);
}
void MotorControl::setSpeed(float speed)
{
    int delayMicros = round(1000000 / (stepsPerRevolution * speed)); // Calculate delay in microseconds

    for (int x = 0; x < stepsPerRevolution; x++)
    {
        digitalWrite(StepX, HIGH);
        delayMicroseconds(delayMicros);
        digitalWrite(StepX, LOW);
        delayMicroseconds(delayMicros);
    }
}

void MotorControl::setAcceleration(float acceleration, float targetSpeed)
{
    int delayMicros = 0; // Initialize delay to zero

    // Calculate initial delay based on target speed
    int initialDelayMicros = round(1000000 / (stepsPerRevolution * targetSpeed));

    // Calculate delay increment based on acceleration
    int delayIncrement = round(1000000 / (stepsPerRevolution * acceleration));

    // Increase delay gradually until reaching the target speed
    while (delayMicros < initialDelayMicros)
    {
        delayMicros += delayIncrement;

        digitalWrite(StepX, HIGH);
        delayMicroseconds(delayMicros);
        digitalWrite(StepX, LOW);
        delayMicroseconds(delayMicros);
    }

    // Call the setStepperMotorSpeed method to maintain the target speed
    setSpeed(targetSpeed);
}
int currentPosition = 0; // Variable to track the current position

// void MotorControl::spinRelative(int steps)
// {
//     int remainingSteps = abs(steps); // Number of steps remaining to reach the target

//     // Determine the direction based on the sign of 'steps'
//     int direction = (steps < 0) ? -1 : 1;

//     // Perform the required steps
//     for (int x = 0; x < remainingSteps; x++)
//     {
//         currentPosition += direction;

//         digitalWrite(StepX, HIGH);
//         delayMicroseconds(500);
//         digitalWrite(StepX, LOW);
//         delayMicroseconds(500);
//     }
// }
// void MotorControl::spinForDist(double inches, bool dir)
// {
//     if (dir)
//     {
//         digitalWrite(DirX, LOW); // cw
//     }
//     else
//     {
//         digitalWrite(DirX, HIGH); // ccw
//     }
//     int steps = inches * revsPerInch * stepsPerRevolution;
//     for (int x = 0; x < steps; x++)
//     {
//         digitalWrite(StepX, HIGH);
//         delayMicroseconds(500);
//         digitalWrite(StepX, LOW);
//         delayMicroseconds(500);
//     }
// }
