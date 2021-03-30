#include <AFMotor.h>
#include <Servo.h>

int pos = 90;
int maxSpeed = 255;
long duration, distanceCm;

int sensor[] = {A0, A1}; // echoPin and trigPin

//initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo myservo;
char command;

void setup()
{
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  myservo.attach(10);
  myservo.write(pos);
}

void loop() {
  int sensorVal = measureDistance(sensor);
  
  if (Serial.available() > 0) {
    command = Serial.read();
    stop(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.
    int distanceR = 0;
    int distanceL =  0;

    if (sensorVal <= 10)
    {
      stop();
      back();
      delay(100);
      stop();
      distanceR = lookRight();
      distanceL = lookLeft();
    }
    else {
      switch (command) {
        case 'F':
          forward();
          break;
        case 'B':
          back();
          break;
        case 'L':
          left();
          break;
        case 'R':
          right();
          break;
      }
    }
  }
}

// servo motor look right
int lookRight()
{
  myservo.write(0);
  delay(500);
  myservo.write(pos);
  delay(200);
  //  return distance;
}

// servo motor look left
int lookLeft()
{
  myservo.write(180);
  delay(500);
  myservo.write(pos);
  delay(200);
}

// dc motor forward
void forward()
{
  motor1.setSpeed(maxSpeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(maxSpeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(maxSpeed);//Define maximum velocity
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.setSpeed(maxSpeed);//Define maximum velocity
  motor4.run(FORWARD); //rotate the motor clockwise
}

// dc motor backward
void back()
{
  motor1.setSpeed(maxSpeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(maxSpeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(maxSpeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(maxSpeed); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

// dc motor left
void left()
{
  motor1.setSpeed(maxSpeed); //Define maximum velocity
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.setSpeed(maxSpeed); //Define maximum velocity
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.setSpeed(maxSpeed); //Define maximum velocity
  motor3.run(FORWARD);  //rotate the motor clockwise
  motor4.setSpeed(maxSpeed); //Define maximum velocity
  motor4.run(FORWARD);  //rotate the motor clockwise
}

// dc motor right
void right()
{
  motor1.setSpeed(maxSpeed); //Define maximum velocity
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.setSpeed(maxSpeed); //Define maximum velocity
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.setSpeed(maxSpeed); //Define maximum velocity
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.setSpeed(255); //Define maximum velocity
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

// dc motor stop
void stop()
{
  motor1.setSpeed(0); //Define minimum velocity
  motor1.run(RELEASE); //stop the motor when release the button
  motor2.setSpeed(0); //Define minimum velocity
  motor2.run(RELEASE); //rotate the motor clockwise
  motor3.setSpeed(0); //Define minimum velocity
  motor3.run(RELEASE); //stop the motor when release the button
  motor4.setSpeed(0); //Define minimum velocity
  motor4.run(RELEASE); //stop the motor when release the button
}

// ************************************
// measure the distance and convert into cm
int measureDistance(int pin[]) {
  pinMode(pin[1], OUTPUT); // pin[1] is trigPin where pin[0] is echoPin
  pinMode(pin[0], INPUT); // pin[0] is echoPin

  digitalWrite(pin[1], LOW);
  delayMicroseconds(2);
  digitalWrite(pin[1], HIGH);
  delayMicroseconds(10);
  digitalWrite(pin[1], LOW);
  duration = pulseIn(pin[0], HIGH);
  distanceCm = duration / 29 / 2;
  return distanceCm;
}
