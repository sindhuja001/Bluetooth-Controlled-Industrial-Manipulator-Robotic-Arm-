#include <Servo.h>
#include <SoftwareSerial.h>

// Bluetooth Module (HC-05)
SoftwareSerial BT(10, 11); // RX, TX

// Motor Driver Pins
const int IN1 = 7;
const int IN2 = 8;
const int ENA = 5;

const int IN3 = 12;
const int IN4 = 13;
const int ENB = 6;

// Servo Pins
Servo servo1;
Servo servo2;
Servo servo3;

const int SERVO1_PIN = 2;
const int SERVO2_PIN = 3;
const int SERVO3_PIN = 4;

int motorSpeed = 250;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);

  servo1.write(90);
  servo2.write(90);
  servo3.write(30);

  Serial.begin(9600);
  BT.begin(9600);

  stopMotors();

  Serial.println("Bluetooth Robotic Car with Servo Arm Ready");
}

void loop() {

  if (BT.available()) {

    int data = BT.parseInt();

    // Car Movement Commands
    if (data == 1) {
      moveForward();
    }
    else if (data == 2) {
      moveBackward();
    }
    else if (data == 3) {
      turnLeft();
    }
    else if (data == 4) {
      turnRight();
    }
    else if (data == 5) {
      stopMotors();
    }

    // Servo 1 Control (40 - 99)
    else if (data >= 40 && data < 100) {
      int angle1 = map(data, 40, 99, 0, 90);
      servo1.write(angle1);

      Serial.print("Servo1: ");
      Serial.println(angle1);
    }

    // Servo 2 Control (100 - 199)
    else if (data >= 100 && data < 200) {
      int angle2 = map(data, 100, 199, 0, 90);
      servo2.write(angle2);

      Serial.print("Servo2: ");
      Serial.println(angle2);
    }

    // Servo 3 Control (200 - 250)
    else if (data >= 200 && data <= 250) {
      int angle3 = map(data, 200, 250, 0, 60);
      servo3.write(angle3);

      Serial.print("Servo3: ");
      Serial.println(angle3);
    }
  }
}

// ---------------- Motor Functions ----------------

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}