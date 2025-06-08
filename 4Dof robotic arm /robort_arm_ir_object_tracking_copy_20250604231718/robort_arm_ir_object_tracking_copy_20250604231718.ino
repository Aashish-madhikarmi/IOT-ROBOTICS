#include <Servo.h>

// Define servos
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristServo;

// IR sensor pin
const int IRsensorPin = A0;

// Link lengths (cm)
const float l1 = 12.0;
const float l2 = 12.0;

// Function prototypes
void performIK(float x, float y, float z, float &theta0, float &theta1, float &theta2);
void moveArm(float theta0, float theta1, float theta2);

void setup() {
  // Attach servos to pins
  baseServo.attach(9);     // Base rotation
  shoulderServo.attach(10); // Shoulder joint
  elbowServo.attach(11);    // Elbow joint
  wristServo.attach(12);    // Wrist joint

  // Initialize servos to default position
  baseServo.write(90);
  shoulderServo.write(90);
  elbowServo.write(90);
  wristServo.write(90);

  Serial.begin(9600); // For debugging
}

void loop() {
  // Read IR sensor
  int sensorReading = analogRead(IRsensorPin);

  // Map sensor reading to distance (adjust calibration as needed)
  float distance = map(sensorReading, 0, 1023, 10, 100); // example range

  // For this example, assume object moves along x-axis at fixed y and z
  float targetX = distance;  // in cm
  float targetY = 0;         // fixed y
  float targetZ = 20;        // fixed height in cm

  float theta0, theta1, theta2;

  // Compute inverse kinematics
  performIK(targetX, targetY, targetZ, theta0, theta1, theta2);

  // Move arm to the position
  moveArm(theta0, theta1, theta2);

  // Debug output
  Serial.print("Sensor: ");
  Serial.print(sensorReading);
  Serial.print("  Distance: ");
  Serial.print(distance);
  Serial.print(" cm  |  Angles: ");
  Serial.print(theta0);
  Serial.print(", ");
  Serial.print(theta1);
  Serial.print(", ");
  Serial.println(theta2);

  delay(200); // Adjust delay for responsiveness
}

// Inverse kinematics function
void performIK(float x, float y, float z, float &theta0, float &theta1, float &theta2) {
  // Calculate base rotation angle
  theta0 = atan2(y, x) * 180.0 / PI; // in degrees

  // Convert to radians for calculations
  float x1 = x;
  float y1 = y;

  // Calculate planar distance to the arm's shoulder
  float r = sqrt(x1 * x1 + y1 * y1);
  float s = z; // height

  // Compute the distance from shoulder to target
  float D = (r*r + s*s - l1*l1 - l2*l2) / (2 * l1 * l2);
  if (D > 1) D = 1; // avoid invalid input to acos
  if (D < -1) D = -1;

  float angle2 = acos(D); // Elbow angle
  theta2 = angle2 * 180.0 / PI; // convert to degrees

  // Calculate shoulder angle
  float angle1 = atan2(s, r) - atan2(l2 * sin(angle2), l1 + l2 * cos(angle2));
  theta1 = angle1 * 180.0 / PI;

  // Adjust angles to servo limits if necessary
  // (Add limits based on your servo's range)
}

// Function to move servos
void moveArm(float theta0, float theta1, float theta2) {
  // Map angles to servo positions (adjust if needed)
  baseServo.write(constrain(theta0 + 90, 0, 180));
  shoulderServo.write(constrain(theta1 + 90, 0, 180));
  elbowServo.write(constrain(theta2 + 90, 0, 180));
  // For simplicity, keep wrist at neutral
  wristServo.write(90);
}