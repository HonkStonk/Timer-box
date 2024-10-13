#include <Servo.h>

Servo arrowServo;
Servo doorServo;

#define SERVO_MIN 560
#define SERVO_MAX 2420

#define DOOR_CLOSED_PERCENT 4
#define DOOR_OPEN_PERCENT 75

#define ARROW_FIVE_MINUTES 100
#define ARROW_HALF_TIME 50
#define ARROW_ZERO_MINUTES 0

void setup() {
  doorServo.attach(10);
  setServoPosition(doorServo, DOOR_CLOSED_PERCENT);

  arrowServo.attach(9);
  setServoPosition(arrowServo, ARROW_HALF_TIME);
  delay(3500);
  setServoPosition(arrowServo, ARROW_FIVE_MINUTES);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Step 1: Move arrowServo from ARROW_FIVE_MINUTES to ARROW_ZERO_MINUTES in 5 minutes
  moveServoToPosition(arrowServo, ARROW_FIVE_MINUTES, ARROW_ZERO_MINUTES, 300000);

  // Step 2: Move doorServo from DOOR_CLOSED_PERCENT to DOOR_OPEN_PERCENT in 30 seconds
  moveServoToPosition(doorServo, DOOR_CLOSED_PERCENT, DOOR_OPEN_PERCENT, 30000);

  // After both movements are complete - the MCU will become 
  // unpowered since it releases a micro switch placed under the box
}

// Function to set the servo position based on percentage
void setServoPosition(Servo servo, int percentage) {
  int position = map(percentage, 0, 100, SERVO_MAX, SERVO_MIN);
  servo.writeMicroseconds(position);
}

// Function to move the servo to a target position over a specified time
void moveServoToPosition(Servo servo, int startPosition, int endPosition, long timeMs) {
  unsigned long startTime = millis();
  int currentPosition = startPosition;

  while (millis() - startTime < timeMs) {
    currentPosition = map(millis() - startTime, 0, timeMs, startPosition, endPosition);
    setServoPosition(servo, currentPosition);
  }

  setServoPosition(servo, endPosition);
}

