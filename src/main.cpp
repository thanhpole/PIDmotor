#include "Arduino.h"
#include <PID_v1.h>

#define ENC_COUNT_REV 107
#define CCW 50
#define CW 51

#define ENC_IN_RIGHT_A 19

#define ENC_IN_RIGHT_B 18

// True = Forward; False = Reverse
boolean Direction_right = true;

// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;

int interval = 120;

double pwm_output;
double target_speed = 300;

// Counters for milliseconds during interval
long previousMillis = 0;
long currentMillis = 0;

// Variable for RPM measuerment
double rpm_right = 0;

void right_wheel_pulse();
void motor_run(double speed);

PID myPID(&rpm_right, &pwm_output, &target_speed, .1, .2, .1, DIRECT);

void setup()
{

  Serial.begin(115200);
  myPID.SetSampleTime(50);
  myPID.SetOutputLimits(50, 255);
  myPID.SetMode(AUTOMATIC);

  pinMode(ENC_IN_RIGHT_A, INPUT_PULLUP);
  pinMode(ENC_IN_RIGHT_B, INPUT);
  Serial.setTimeout(1000);
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
}
char c;
String s, lastS;

void loop()
{
  if (Serial.available())
  {
    // c = Serial.read();
    s = Serial.readStringUntil('\n');

    // Serial.println(s);
    switch (s.toInt())
    {
    case 2:
      s = "";
      s += '1';
      s += '2';
      lastS = s;
      Serial.print(s.toInt());
      break;

    case 3:
      s = "";
      s += '1';
      s += '3';
      lastS = s;
      Serial.print(s.toInt());
      break;

    case 0:
      s = "";
      s += '0';
      s += '0';
      lastS = s;
      Serial.print(s.toInt());
      break;
    }
    if (s.toInt() >= 100 && s.toInt() <= 600)
    {
      target_speed = s.toDouble();
    }

    //Serial.println(target_speed);
    // s="";
  }

  if (target_speed <= 300)
  {
    myPID.SetTunings(0.16, 0.07, 0.04);
  }
  else
  {
    myPID.SetTunings(0.19, 0.13, 0.05);
  }

  // target_speed=200;
  if (s.toInt() == 12 || s.toInt() == 13)
  {
    if (s[1] == '2')
    {
      digitalWrite(CW, LOW);
      digitalWrite(CCW, HIGH);
    }
    else if (s[1] == '3')
    {
      digitalWrite(CCW, LOW);
      digitalWrite(CW, HIGH);
    }

    currentMillis = millis();
    // target_speed = 200;
    if (currentMillis - previousMillis >= interval)
    {

      previousMillis = currentMillis;

      rpm_right = (float)(right_wheel_pulse_count * 486.36 / ENC_COUNT_REV);

      // Serial.print(" Pulses: ");
      // Serial.println(right_wheel_pulse_count);
      // Serial.print(" Speed: ");
      rpm_right = abs(rpm_right);
      Serial.print(rpm_right);

      Serial.println();

      right_wheel_pulse_count = 0;
      myPID.Compute();
    }
    analogWrite(4, pwm_output);
    // s="";
  }

  else if (s[0] == '0')
  {
    digitalWrite(CCW, LOW);
    digitalWrite(CW, LOW);
    analogWrite(4, 0);
    s = "";
    Serial.println("0");
  }
}

void motor_run(double speed)
{
  currentMillis = millis();
  target_speed = speed;
  if (currentMillis - previousMillis >= interval)
  {

    previousMillis = currentMillis;

    rpm_right = (float)(right_wheel_pulse_count * 486.36 / ENC_COUNT_REV);

    // Serial.print(" Pulses: ");
    // Serial.println(right_wheel_pulse_count);
    // Serial.print(" Speed: ");
    rpm_right = abs(rpm_right);
    Serial.print(rpm_right);

    Serial.println();

    right_wheel_pulse_count = 0;
    myPID.Compute();
  }
  analogWrite(4, pwm_output);
}

void right_wheel_pulse()
{

  int val = digitalRead(ENC_IN_RIGHT_B);

  if (val == LOW)
  {
    Direction_right = false;
  }
  else
  {
    Direction_right = true;
  }

  if (Direction_right)
  {
    right_wheel_pulse_count++;
  }
  else
  {
    right_wheel_pulse_count--;
  }
}