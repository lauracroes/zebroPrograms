#include <Servo.h>

enum {rightFront = 0, rightCenter, rightBack, leftFront, leftCenter, leftBack};
const int servo[] = {[rightFront] = 46, [rightCenter] = 45, [rightBack] = 44, [leftFront] = 6, [leftCenter] = 7, [leftBack] = 8};
const int hallPin[] = {[rightFront] = 34, [rightCenter] = 33, [rightBack] = 32, [leftFront] = 37, [leftCenter] = 36, [leftBack] = 35};
const int numberOfLegs = 6;
int i, j, k, Speed, introTaps = 5, repetitionsPart1 = 2, repetitionsPart2 = 3, timeOfTwirling = 5000, numberOfBounces = 10;

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

  // We wait 3 sec for the song to start
  delay(3800);


}




// *******************************************************************************************************************************************************
// LOOP
//********************************************************************************************************************************************************


void loop() {

  // All the legs on the right side must turn towards 0 in order for the robot to go forward and all the legs on the left toward 180
  // The more we go to the extremes, the faster the leg will move

  // INTRO

  for (k = 0; k < introTaps; k++)
  {
    leg[rightFront].write(60);
    delay(400);
    leg[rightFront].write(110);
    delay(500);
  }

  // PART 1
  for (j = 0; j < repetitionsPart1; j++) {
    for (i = 0; i < numberOfLegs; i++)
    {
      legTurnForward(i, 90);

      delay(150);


      initiateLeg(i);


      delay(100);
    }
  }
  // PART 2
  for (k = 0; k < repetitionsPart2; k++)
  {
    for (i = rightFront, j = leftFront; i < leftFront; i++, j++)
    {
      // It is necessary for the leg to be given a speed so that when the loop restarts the legs aren't still already
      legTurnForward(i, 30);
      legTurnForward(j, 30);

      delay(500);


      // When the hallpin does not detect the magnet it will give an output 1, if this is the case the legs must keep spinning
      while (digitalRead(hallPin[i]) && digitalRead(hallPin[j]))
      {
        legTurnForward(i, 30);
        legTurnForward(j, 30);
      }
      // Once the magnet is detected the leg must stop
      legTurnForward(i, 0);
      legTurnForward(j, 0);

      delay(400);
    }
  }

  delay(50);

  // PART 3, The twirling
  for (i = rightFront; i <= leftBack; i++)
  {
    leg[i].write(150);
  }

  delay(timeOfTwirling);

  for (i = rightFront; i <= leftBack; i++)
  {
    initiateLeg(i);
  }

  delay(1000);

  // PART 4, bouncing
  for ( k = 0; k < numberOfBounces; k++)
  {
    for (i = rightFront, j = leftFront; i < leftFront; i++, j++)
    {
      legTurnBackward(i, 30);
      legTurnBackward(j, 30);

    }
    delay(500);
    for (i = rightFront, j = leftFront; i < leftFront; i++, j++)
    {
      legTurnForward(i, 30);
      legTurnForward(j, 30);

    }
    delay(500);
  }

  delay(750);

  for (i = rightFront; i <= leftBack; i++)
  {
    initiateLeg(i);
  }

delay(50);

  // SPRINT
  for (i = rightFront, j = leftFront; i < leftFront && j <= leftBack; i++, j++)
  {
    legTurnBackward(i, 30);
    legTurnBackward(j, 30);

  }

  delay(3000);
  
  for (i = rightFront, j = leftFront; i < leftFront && j <= leftBack; i++, j++)
  {
    legTurnForward(i, 30);
    legTurnForward(j, 30);

  }

  delay(3000);

  for (i = rightFront; i <= leftBack; i++)
  {
    initiateLeg(i);
  }

  delay(500);

  // ENDING
  for (j = 0; j < 1; j++) {
    for (i = 0; i < numberOfLegs; i++)
    {
      legTurnForward(i, 80);

      delay(150);


      initiateLeg(i);



   
    }
  }


  delay(3000);
}
