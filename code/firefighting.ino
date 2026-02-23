#include <Servo.h>

// Ultrasonic pins
const int TRIG_LEFT   = 2;
const int ECHO_LEFT   = 3;
const int TRIG_RIGHT  = 4;
const int ECHO_RIGHT  = 12;

// LDR sensors
const int LDR_R       = A0;
const int LDR_C       = A1;
const int LDR_L       = A2;

// Pump and servos
const int LED_PIN     = A5;
const int NOZZLE_SERVO_PIN = A4;
const int STEERING_SERVO_PIN = A3;  // NEW servo for steering

// Motor driver
const int ENA = 10;
const int IN1 = 9;
const int IN2 = 8;
const int ENB = 5;
const int IN3 = 7;
const int IN4 = 6;

Servo nozzle;
Servo steeringServo;

// Thresholds
const int FLAME_TH = 600;
const int OBSTACLE_THRESHOLD = 10;
const int FWD_SPEED = 150;
const int REV_SPEED = 150;
const int TURN_DURATION = 5000; // in ms

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  // Ultrasonic sensors
  pinMode(TRIG_LEFT, OUTPUT); pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT); pinMode(ECHO_RIGHT, INPUT);

  // LDRs
  pinMode(LDR_R, INPUT); pinMode(LDR_C, INPUT); pinMode(LDR_L, INPUT);

  // LED & servos
  pinMode(LED_PIN, OUTPUT); digitalWrite(LED_PIN, LOW);
  nozzle.attach(NOZZLE_SERVO_PIN); nozzle.write(90);
  steeringServo.attach(STEERING_SERVO_PIN); steeringServo.write(90);  // straight
}

// Read distance from ultrasonic
long readDist(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000);
  return duration * 0.034 / 2;
}

void driveForward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, FWD_SPEED);
  analogWrite(ENB, FWD_SPEED);
}

void reverse() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, REV_SPEED);
  analogWrite(ENB, REV_SPEED);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

void loop() {
  // Read flame sensors
  int vR = analogRead(LDR_R);
  int vC = analogRead(LDR_C);
  int vL = analogRead(LDR_L);

  // Read ultrasonic sensors
  long dL = readDist(TRIG_LEFT, ECHO_LEFT);
  long dR = readDist(TRIG_RIGHT, ECHO_RIGHT);

  Serial.print("UL="); Serial.print(dL);
  Serial.print(" | UR="); Serial.print(dR);
  Serial.print(" | LDRs L="); Serial.print(vL);
  Serial.print(" C="); Serial.print(vC);
  Serial.print(" R="); Serial.println(vR);

  // --- FLAME DETECTION LOGIC ---
  if (vR > FLAME_TH) {
    stopMotors();
    steeringServo.write(90);      // Straight
    nozzle.write(0);              // Aim right
    digitalWrite(LED_PIN, HIGH);  // Turn on pump
    delay(5000);
  } 
  else if (vL > FLAME_TH) {
    stopMotors();
    steeringServo.write(90);
    nozzle.write(180);            // Aim left
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
  } 
  else if (vC > FLAME_TH) {
    stopMotors();
    steeringServo.write(90);
    nozzle.write(90);             // Aim center
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
  }

  // --- OBSTACLE AVOIDANCE LOGIC (steering servo based) ---
  else if (dR < OBSTACLE_THRESHOLD && dL >= OBSTACLE_THRESHOLD) {
    stopMotors();
    steeringServo.write(135);  // Turn wheels left
    delay(TURN_DURATION);
    steeringServo.write(90);   // Back to straight
  } 
  else if (dL < OBSTACLE_THRESHOLD && dR >= OBSTACLE_THRESHOLD) {
    stopMotors();
    steeringServo.write(45);   // Turn wheels right
    delay(TURN_DURATION);
    steeringServo.write(90);   // Back to straight
  } 
  else if (dR < OBSTACLE_THRESHOLD && dL < OBSTACLE_THRESHOLD) {
    // Obstacle in front: reverse and u-turn
    stopMotors();
    reverse();
    delay(1500);
    stopMotors();
    steeringServo.write(135);  // Turn full left for U-turn
    driveForward();
    delay(1200);
    steeringServo.write(90);   // Center again
  } 
  else {
    // Normal forward movement
    digitalWrite(LED_PIN, LOW);
    nozzle.write(90);
    steeringServo.write(90);  // Keep straight
    driveForward();
  }

  delay(200);
}
