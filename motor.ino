#define trigLeft 2
#define echoLeft 3
#define trigRight 4
#define echoRight 5

// === Motor Driver Pins ===
#define IN1 6  // Left Motor Forward
#define IN2 7  // Left Motor Backward
#define IN3 8  // Right Motor Forward
#define IN4 9  // Right Motor Backward
#define ENA 10 // Speed control for left motor
#define ENB 11 // Speed control for right motor

// === Parameters ===
#define THRESHOLD 20   // cm, min safe distance
#define TURN_DELAY 300 // ms, adjust for turn sharpness

void setup() {
  Serial.begin(9600);

  // Ultrasonic setup
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  // Motor driver setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  stopMotors();
}

void loop() {
  int distLeft = getDistance(trigLeft, echoLeft);
  int distRight = getDistance(trigRight, echoRight);

  Serial.print("Left: "); Serial.print(distLeft);
  Serial.print(" cm | Right: "); Serial.println(distRight);

  if (distLeft > THRESHOLD && distRight > THRESHOLD) {
    moveForward();
    Serial.println("Both sides clear. Moving forward.");
  }
  else if (distLeft > THRESHOLD && distRight <= THRESHOLD) {
    turnLeft();
    Serial.println("Turning left to avoid right obstacle.");
  }
  else if (distRight > THRESHOLD && distLeft <= THRESHOLD) {
    turnRight();
    Serial.println("Turning right to avoid left obstacle.");
  }
  else {
    stopMotors();
    Serial.println("Both sides blocked. Stopping.");
  }

  delay(200);
}

// === Get distance from ultrasonic sensor ===
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// === Motor control functions ===
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  delay(TURN_DELAY);
  stopMotors();
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
  delay(TURN_DELAY);
  stopMotors();
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}