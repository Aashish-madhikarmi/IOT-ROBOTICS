#include <Servo.h>
#include <math.h>

// Arm link lengths (cm)
const float L1 = 10.0;
const float L2 = 15.0;
const float L3 = 10.0;
const float wristPitchRad = 0.227;  // ≈13°

Servo base, shoulder, elbow, wrist;
Servo gripper;  // Gripper servo

// Gripper angles 
int gripperOpen = 20;
int gripperClosed = 70;

// Home positions
int baseHome = 90, shoulderHome = 45, elbowHome = 45, wristHome = 13;

void setup() {
  Serial.begin(9600);

  base.attach(3);
  shoulder.attach(5);
  elbow.attach(6);
  wrist.attach(9);
  gripper.attach(10);  // Gripper control

  moveToHomePosition();
}

void loop() {
  // ---- First Position ----
  moveToIK(5.0, 10.0, 18.0); // Move to position 1
  openGripper();             // Gripper open
  delay(2000);

  // ---- Second Position ----
  moveToIK(10.0, 5.0, 22.0);  // Move to position 2
  closeGripper();            // Gripper close (picking something)
  delay(2000);

  // ---- Third Position ----
  moveToIK(4.0, 8.0, 25.0);  // Move to drop location
  openGripper();             // Drop object
  delay(2000);

  moveToHomePosition();      // Optional: return to home
  delay(5000);               // Wait before repeating
}

// ----- Gripper Control -----
void openGripper() {
  gripper.write(gripperOpen);
  Serial.println("Gripper opened");
}

void closeGripper() {
  gripper.write(gripperClosed);
  Serial.println("Gripper closed");
}

// ----- Move to Home -----
void moveToHomePosition() {
  base.write(baseHome);
  shoulder.write(shoulderHome);
  elbow.write(elbowHome);
  wrist.write(wristHome);
  openGripper();
}

// ----- Inverse Kinematics -----
void moveToIK(float px, float py, float pz) {
  float theta1 = atan2(py, px);
  float r = sqrt(px * px + py * py);
  float wx = r - L3 * cos(wristPitchRad);
  float wz = pz - L3 * sin(wristPitchRad);

  float D = (wx * wx + wz * wz - L1 * L1 - L2 * L2) / (2 * L1 * L2);
  if (D < -1.0 || D > 1.0) {
    Serial.println("Target unreachable");
    return;
  }

  float theta3 = acos(D);
  float k1 = L1 + L2 * cos(theta3);
  float k2 = L2 * sin(theta3);
  float theta2 = atan2(wz, wx) - atan2(k2, k1);
  float theta4 = wristPitchRad;

  int baseDeg     = constrain(degrees(theta1), 0, 180);
  int shoulderDeg = constrain(degrees(theta2), 0, 180);
  int elbowDeg    = constrain(degrees(theta3), 0, 180);
  int wristDeg    = constrain(degrees(theta4), 0, 180);

  Serial.print("Move to: Base="); Serial.print(baseDeg);
  Serial.print(", Shoulder="); Serial.print(shoulderDeg);
  Serial.print(", Elbow="); Serial.print(elbowDeg);
  Serial.print(", Wrist="); Serial.println(wristDeg);

  base.write(baseDeg);
  shoulder.write(shoulderDeg);
  elbow.write(elbowDeg);
  wrist.write(wristDeg);
}
