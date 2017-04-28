#include <Servo.h>

enum {rightFront = 0, rightCenter, rightBack, leftFront, leftCenter, leftBack};
const int servo[] = {[rightFront] = 46, [rightCenter] = 45, [rightBack] = 44, [leftFront] = 6, [leftCenter] = 7, [leftBack] = 8};
const int hallPin[] = {[rightFront] = 34, [rightCenter] = 33, [rightBack] = 32, [leftFront] = 37, [leftCenter] = 36, [leftBack] = 35};
const int numberOfLegs = 6;
int i, j, k, Speed, timeOfTurning = 1500, distance;
// Each leg must be called a servo
Servo leg [numberOfLegs];


//********************************************************************************************************************************************************
//FUNCTIONS
//********************************************************************************************************************************************************

// This is a function that'll make the legs turn the desired speed the direction that makes the robot walk forward
void legTurnForward(int i, int Speed) {
  // All the legs on the right side have to have a value below 90
  if (i == rightFront || i == rightCenter || i == rightBack)
  {
    leg[i].write(90 - Speed);
  }
  // All the legs on the right side have to have a a value above 90
  else
  {
    leg[i].write(90 + Speed);
  }
}

//**********************************************************************************************************************************************************

// This is a function that'll make the legs turn the desired speed the direction that makes the robot walk forward
void legTurnBackward(int i, int Speed) {
  // All the legs on the right side have to have a value above 90
  if (i == rightFront || i == rightCenter || i == rightBack)
  {
    leg[i].write(90 + Speed);
  }
  // All the legs on the right side have to have a a value below 90
  else
  {
    leg[i].write(90 - Speed);
  }
}

//********************************************************************************************************************************************************

// This is a function that initiates the leg at a certain position and stops it

void initiateLeg(int i)
{
  // When the hallpin does not detect the magnet it will give an output 1, if this is the case the leg must keep spinning
  while (digitalRead(hallPin[i]))
  {
    legTurnForward(i, 90);
  }
  // Once the magnet is detected the leg must stop
  leg[i].write(90);
}
//*******************************************************************************************************************************************************
void sonarfunction()
{
  const int trig = 5;
  const int echo = 3;
  long duration;


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration * 0.034 / 2;
}
// *******************************************************************************************************************************************************
// SETUP
//********************************************************************************************************************************************************

void setup() {

  // The setup is done in one loop so each leg gets their hallpin assigned and servo attached
  for (i = 0; i < numberOfLegs; i++)
  {
    // Seting up the hallpins as inputs
    pinMode (hallPin[i], INPUT_PULLUP);
    // Attaching servos to pins
    leg[i].attach(servo[i]);
  }

  // To make the arduino return information to the Serial Monitor
  Serial.begin(9600);

  // Some legs tend to rotate even we nothing is sent to them and so this will initialize leg i to stand still for i is 0 till numberOfLegs
  for (i = 0; i < numberOfLegs; i++)
  {
    leg[i].write(90);
  }

  //All legs will be set into the same position in order to make the routine always start correctly
  for (i = 0; i < numberOfLegs; i++)
  {
    initiateLeg(i);
  }


}

void loop() {

  for (i = rightFront; i <= leftBack; i++)
  {
    legTurnForward(i, 20);
  }

sonarfunction();
  if (distance < 5)
  {
    // make all legs stand still
  for (i = 0; i < numberOfLegs; i++)
  {
    leg[i].write(90);
  }

    // Raging
    for (i = 0; i < 5; i++)
    {
      legTurnForward(rightFront, 80);
      legTurnForward(leftFront, 80);

      delay(250);

      legTurnBackward(rightFront, 80);
      legTurnBackward(leftFront, 80);

      delay(250);
    }

 
    // Turning
    for (i = rightFront; i <= leftBack; i++)
    {
      leg[i].write(150);
    }

    delay(timeOfTurning);

    for (i = rightFront; i <= leftBack; i++)
    {
      initiateLeg(i);
    }
  }

}
