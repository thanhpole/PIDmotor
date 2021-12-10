// #include <Arduino.h>
// //#include "EnableInterrupt.h"
// #include <PID_v1.h>
// #include <L298N.h>

// #define PWM_PIN 4

// #define encoderA 19 // INT4
// #define encoderB 18 // INT5

// unsigned long rpm;     // rpm reading
// volatile byte pulses; // number of pulses
// unsigned long timeold;
// // The number of pulses per revolution
// // depends on your index disc!!
// unsigned int pulsesperturn = 11;

// double kp = 0.1, ki = 0.1, kd = 0.01, input = 0, output = 0, setpoint = 0;
// volatile long encoderPos = 0;
// PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

// const unsigned int IN1 = 50;
// const unsigned int IN2 = 51;

// L298N motor(PWM_PIN, IN1, IN2);

// void readEncoderA()
// {
//   pulses++;
// }

// void readEncoderB()
// {
//   pulses++;
// }

// void setup()
// {
//   Serial.begin(9600);

//   pinMode(encoderA, INPUT_PULLUP);
//   pinMode(encoderB, INPUT_PULLUP);
//   TCCR1A = (TCCR1A & 0b11111000) | 1;
//   attachInterrupt(4, readEncoderA, RISING);
//   attachInterrupt(5, readEncoderB, RISING);
//   motor.setSpeed(255);
//   myPID.SetMode(AUTOMATIC);
//   myPID.SetSampleTime(1);
//   myPID.SetOutputLimits(-255, 255);
// }

// void loop()
// {
//   motor.backwardFor(3000);
//   if (millis() - timeold >= 500)
//   { /*Uptade every one second, this will be equal to reading frecuency (Hz).*/

//     // Don't process interrupts during calculations
//     detachInterrupt(4);
//     detachInterrupt(5);
//     // Note that this would be 60*1000/(millis() - timeold)*pulses if the interrupt
//     // happened once per revolution
//     rpm = (60 * 500 / pulsesperturn) / (millis() - timeold) * pulses;
//     timeold = millis();
//     Serial.print(pulses);
//     pulses = 0;

//     // Write it out to serial port

//     Serial.print(" RPM = ");
//     Serial.println(rpm);
//     // Restart the interrupt processing
//     attachInterrupt(4, readEncoderA, RISING);
//     attachInterrupt(5, readEncoderB, RISING);
//   }
// }