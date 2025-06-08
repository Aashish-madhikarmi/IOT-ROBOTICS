#include <Servo.h>
#include <math.h>

// Define link lengths (measure your arm!)
const float L1 = 10.0;  // Base to shoulder (cm)
const float L2 = 15.0;  // Shoulder to elbow
const float L3 = 7.0;  // Elbow to wrist

Servo base, shoulder, elbow, wrist;

void setup() {
  Serial.begin(9600);
  base.attach(9);      // Attach servos to PWM pins
  shoulder.attach(10);
  elbow.attach(11);
  wrist.attach(6);
}

void loop() {
  // Read current servo angles (0-180° → radians)
  float theta1 = radians(base.read());
  float theta2 = radians(shoulder.read());
  float theta3 = radians(elbow.read());

  // Compute FK
  float x = (L1 + L2*cos(theta2) + L3*cos(theta2 + theta3)) * cos(theta1);
  float y = (L1 + L2*cos(theta2) + L3*cos(theta2 + theta3)) * sin(theta1);
  float z = L2*sin(theta2) + L3*sin(theta2 + theta3);

  Serial.print("End-effector position (cm): ");
  Serial.print("X="); Serial.print(x);
  Serial.print(", Y="); Serial.print(y);
  Serial.print(", Z="); Serial.println(z);
  
  delay(1000);  // Update every second
}