#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVO_MIN 150   // Pulse for 0 degrees
#define SERVO_MAX 600   // Pulse for 180 degrees
#define SERVO_NEUTRAL 375 // Neutral position for Servo 0

int angleToPulse(int angle) {
  return map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
}

void smoothMove(int servo, int startAngle, int endAngle, int stepDelay) {
  if (startAngle < endAngle) {
    for (int angle = startAngle; angle <= endAngle; angle += 5) {
      pwm.setPWM(servo, 0, angleToPulse(angle));
      delay(stepDelay);
    }
  } else {
    for (int angle = startAngle; angle >= endAngle; angle -= 5) {
      pwm.setPWM(servo, 0, angleToPulse(angle));
      delay(stepDelay);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);

  smoothMove(0, 90, 0, 15);
  smoothMove(1, 90, 40, 15);
  smoothMove(2, 90, 100, 15);  // Updated max to 100
  smoothMove(3, 90, 50, 15);   // Updated min to 50
  smoothMove(4, 90, 20, 15);
}

void loop() {
  smoothMove(0, 0, 180, 20);
  smoothMove(0, 180, 0, 20);

  for (int angle = 50; angle <= 100; angle += 5) {  // Updated min to 50, max to 100
    pwm.setPWM(2, 0, angleToPulse(angle));
    pwm.setPWM(3, 0, angleToPulse(angle));
    delay(20);
  }

  for (int angle = 100; angle >= 50; angle -= 5) {  // Updated max to 100, min to 50
    pwm.setPWM(2, 0, angleToPulse(angle));
    pwm.setPWM(3, 0, angleToPulse(angle));
    delay(20);
  }

  smoothMove(3, 50, 100, 20); // Updated min to 50, max to 100
  smoothMove(4, 20, 100, 20);

  smoothMove(3, 100, 50, 20); // Updated max to 100, min to 50
  smoothMove(0, 0, 180, 20);
  smoothMove(0, 180, 0, 20);

  for (int angle = 50; angle <= 100; angle += 5) {  // Updated min to 50, max to 100
    pwm.setPWM(2, 0, angleToPulse(angle));
    pwm.setPWM(3, 0, angleToPulse(angle));
    delay(20);
  }

  for (int angle = 100; angle >= 50; angle -= 5) {  // Updated max to 100, min to 50
    pwm.setPWM(2, 0, angleToPulse(angle));
    pwm.setPWM(3, 0, angleToPulse(angle));
    delay(20);
  }

  smoothMove(3, 50, 100, 20); // Updated min to 50, max to 100
  smoothMove(4, 100, 20, 20);
  smoothMove(3, 100, 50, 20); // Updated max to 100, min to 50
}
