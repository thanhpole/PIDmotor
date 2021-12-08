#ifndef _MOTOR_H_

#include <Arduino.h>
#include "PID_v1.h"

#define LEFT_PIN 53
#define RIGHT_PIN 52
#define PWM_PIN 4

class motor
{
private:
    /* data */
    double targetSpeed = 0, recentSpeed = 0, outputPWM = 0;
    double Kp = 0, Ki = 0, Kd = 0;

public:
    
    motor();
    void turnLeft();
    void turnRight();
    void stop();
    void setSpeed(double speed);
    void setPID(double IKp, double IKi, double IKd);
    void run();
    int readingSpeed();
};


#endif // !_MOTOR_H_