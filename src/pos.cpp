// #include <Arduino.h>
// #include <Encoder.h>
// #include <PID_v1.h>
// #include <DCMotorServo.h>

// #define pin_dcmoto_dir1 50
// #define pin_dcmoto_dir2 51
// #define pin_dcmoto_pwm_out 4
// #define pin_dcmoto_encode1 19
// #define pin_dcmoto_encode2 18
// //Determined by experimentation, depends on your encoder, and your belt/gearing ratios:
// long dcmoto_encoder_1_inch = 426*3;

// DCMotorServo servo = DCMotorServo(pin_dcmoto_dir1, pin_dcmoto_dir2, pin_dcmoto_pwm_out, pin_dcmoto_encode1, pin_dcmoto_encode2);

// void setup() {

//   //Tune the servo feedback
//   //Determined by trial and error
//   Serial.begin(9600);
//   servo.myPID->SetTunings(0.13,0.15,0.1);
//   servo.setPWMSkip(50);
//   servo.setAccuracy(11);
//   //Un-necessary, initializes to 0:
//   //servo.setCurrentPosition(0);
// }


// void loop() {
//   //wait 1s before starting
//   static unsigned long motor_timeout = millis() + 1000;
//   static bool motor_go = 0;

//   servo.run();
  
//   if (servo.finished()) {
//     if(motor_go) {
//       //stop disengages the motor feedback system, in which case if you moved the motor, it would fight you if you didn't "stop" it first (provided you were still running servo.run() operations)
//       servo.stop();
//       motor_timeout = millis() + 3000;
//       motor_go = 0;
//     }
//     if(motor_timeout < millis()) {
//       //Setting a move operation will ensure that servo.finished() no longer returns true
//       if(dcmoto_encoder_1_inch>0) dcmoto_encoder_1_inch*=-1;
//       else dcmoto_encoder_1_inch*=(-1);
//       servo.move(dcmoto_encoder_1_inch);
//       Serial.println(servo.getActualPosition());
//       Serial.println(servo.getRequestedPosition());
//       motor_go = 1;
//     }
//   }
// }