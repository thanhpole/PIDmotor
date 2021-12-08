#include "motor.h"


motor::motor()
{
    pinMode(LEFT_PIN, OUTPUT);
    pinMode(RIGHT_PIN, OUTPUT);
    
    PID motorPID(&this->recentSpeed, &this->outputPWM, &this->targetSpeed, this->Kp, this->Ki, this->Kd, DIRECT);
}

void motor::setSpeed(double speed){
    this->targetSpeed = speed;
}


/* Set PID parameter */
void motor::setPID(double IKp, double IKi, double IKd){
    this->Kp = IKp;
    this->Ki = IKi;
    this->Kd = IKd;
}

void motor::turnLeft(){
    digitalWrite(RIGHT_PIN, LOW);
    delay(100);
    digitalWrite(LEFT_PIN, HIGH);
}

void motor::turnRight(){
    digitalWrite(LEFT_PIN, LOW);
    delay(100);
    digitalWrite(RIGHT_PIN, HIGH);
}

void motor::stop(){
    digitalWrite(LEFT_PIN, LOW);
    digitalWrite(RIGHT_PIN, LOW);
    
}

void motor::run(){
    
    this->recentSpeed = (double)readingSpeed();

}

int motor::readingSpeed(){


    return 0;
}