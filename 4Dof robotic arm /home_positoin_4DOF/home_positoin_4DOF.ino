#include <Servo.h>
#include <math.h>

// Define link lengths (cm)
const float L1 = 10.0;  // Base to shoulder
const float L2 = 15.0;  // Shoulder to elbow
const float L3 = 10.0;  // Elbow to wrist to end-effector

// Fixed wrist angle (13 degrees in radians)
const float wristPitchRad = 0.227;

// Servo objects
Servo base, shoulder, elbow, wrist;

// Home positions (in degrees)
int baseHome = 90;
int shoulderHome = 45;
int elbowHome = 45;
int wristHome = 13;

void setup() {
  Serial.begin(9600);
  base.attach(3);
  shoulder.attach(5);
  elbow.attach(6);
  wrist.attach(9);

  moveToHomePosition();
}

void loop() {
  // Forward Kinematics from current angles
  float theta1 = radians(base.read());
  float theta2 = radians(shoulder.read());
  float theta3 = radians(elbow.read());

  float x = (L1 + L2 * cos(theta2) + L3 * cos(theta2 + theta3)) * cos(theta1);
  float y = (L1 + L2 * cos(theta2) + L3 * cos(theta2 + theta3)) * sin(theta1);
  float z = L2 * sin(theta2) + L3 * sin(theta2 + theta3);

  Serial.print("End-effector position (cm): ");
  Serial.print("X="); Serial.print(x);
  Serial.print(", Y="); Serial.print(y);
  Serial.print(", Z="); Serial.println(z);

  delay(1000);  // Print every second

  // Example: Move to a target position
  moveToIK(5.0, 10.0, 24.0);  // Change as needed

  delay(5000);
}

void moveToHomePosition() {
  base.write(baseHome);
  shoulder.write(shoulderHome);
  elbow.write(elbowHome);
  wrist.write(wristHome);
}

// ---------------- Inverse Kinematics Function ----------------
void moveToIK(float px, float py, float pz) {
  float theta1, theta2, theta3, theta4;

  // Step 1: Base rotation
  theta1 = atan2(py, px);  // Radians

  // Step 2: Compute wrist position
  float r = sqrt(px * px + py * py);
  float wx = r - L3 * cos(wristPitchRad);
  float wz = pz - L3 * sin(wristPitchRad);

  // Step 3: Use cosine rule to compute elbow angle
  float D = (wx * wx + wz * wz - L1 * L1 - L2 * L2) / (2 * L1 * L2);
  if (D < -1.0 || D > 1.0) {
    Serial.println("Target unreachable");
    return;
  }

  theta3 = acos(D);

  // Step 4: Shoulder angle
  float k1 = L1 + L2 * cos(theta3);
  float k2 = L2 * sin(theta3);
  theta2 = atan2(wz, wx) - atan2(k2, k1);

  // Step 5: Wrist pitch (fixed)
  theta4 = wristPitchRad;

  // Convert to degrees for servo commands
  int baseDeg     = constrain(degrees(theta1), 0, 180);
  int shoulderDeg = constrain(degrees(theta2), 0, 180);
  int elbowDeg    = constrain(degrees(theta3), 0, 180);
  int wristDeg    = constrain(degrees(theta4), 0, 180);

  // Print calculated angles
  Serial.print("Move to IK position: ");
  Serial.print("Base: "); Serial.print(baseDeg);
  Serial.print(" | Shoulder: "); Serial.print(shoulderDeg);
  Serial.print(" | Elbow: "); Serial.print(elbowDeg);
  Serial.print(" | Wrist: "); Serial.println(wristDeg);

  // Move servos
  base.write(baseDeg);
  shoulder.write(shoulderDeg);
  elbow.write(elbowDeg);
  wrist.write(wristDeg);
}
