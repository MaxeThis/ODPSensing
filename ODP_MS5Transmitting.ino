//#include "Enes100.h"
//#include "TankSimulation.h"
#include <math.h>
#include <Enes100.h>
//Un Comment obstacle dodging

/*
 * Note: This sketch contains function defintions that may be useful for writing your navigation code. 
 * You are responsible for writing the code to complete the functions and testing it out on the simulator. 
 * If you're looking for an example of using the simulator libraries, go to File->Examples->navigation_example
 * Enes100.location.y
 * Enes100.location.x
 * Enes100.location.theta
 */

 /*
  * Possible Debug Concern priorities:
  * If statements for progress of clockwise movement
  * OR
  * movement as a whole for goals > 3.14 and <-3.14
  * -Max
  */

  /*
   * Mission Notes:
   * Phase 1-
   *  -Center - (0.35,1)
   * Phase 2-
   *  - Sensors: Front[0(Left),2(Right)]
   *             Side[10(Left),4(Right)]
   *             Enes100.readDistanceSensor(int SensorNumber);
   *    Drives down center and dodges obstacles
   *    Obstacle size: 0.2 x 0.5m
   */

   
boolean phase1 = true;
//Sonar Values Start:
int trigPin=10;
int echoPin1=2;
int echoPin2=3;
int echoPin3=4;
int echoPin4=5;
long duration1;
long duration2;
long duration3;
long duration4;
int distance1;
int distance2;
int distance3;
int distance4;
//Sonar Values End

void setup() {
  initialize(); //Sets up motors
  
  Enes100.begin("ODP", BLACK_BOX, 5, 9, 8);
  Serial.begin(9600);
  Enes100.println("-=xxxXXX[Operation Dark Phoenix]XXXxx=- IN DIS BITS:");
  
  /*
  Enes100.println("");
  Enes100.println("__________________");
  Enes100.println("FaceDir Command:");
  faceDir(0);
  */
  Enes100.println("Clockwise");
  clockwise(255);
  delay(10000);
  Enes100.println("CounterClockwise");
  counterClockwise(255);
  delay(10000);
  Enes100.println("Forward");
  driveForward(255);
  delay(10000);
  phaseOne();
  phaseTwo();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  
}


//Phase 1 - Center Self
void phaseOne(){
  Enes100.println("-=PHASE 1=-"); 
  if(Enes100.location.y > 1){
    driveDestination(false, 255, 0.35, 1);
  }
  else if(Enes100.location.y < 1){
    driveDestination(false, 255, 0.35, 1);
  }
  faceDir(0);
  phase1 = false;
}

void phaseTwo(){
  Enes100.println("-=PHASE 2=-"); 
  driveDestination(true, 255, 3, 1);
}


/*void dodgeObstacle(){
  Enes100.updateLocation();
  boolean drivePast = false;
  float sideDistance = Enes100.readDistanceSensor(4);
  double startPos [] = {Enes100.location.x, Enes100.location.y, Enes100.location.theta};
  Enes100.println("DODGE OBSTACLE: 1A");
  Enes100.println("DODGE OBSTACLE: DRIVE TEST -------");
  Enes100.updateLocation();
  driveDestination(false, 200, (Enes100.location.x + 0.3), (Enes100.location.y + 0.6));
  Enes100.updateLocation();
  Enes100.println("DODGE OBSTACLE: 2-------------------");
  faceDir(0);
  //driveDestination(false, 100, Enes100.location.x+ 0.2, Enes100.location.y);
  Enes100.println("DODGE OBSTACLE: 2 - Face Right-------------------");
  while(!drivePast){
    driveForward(100);
    if(Enes100.readDistanceSensor(4) <= 30){
      drivePast = true;
    }
  }
  ("DODGE OBSTACLE: 3 DRIVEN PAST, NEXT!-------------------");
  Enes100.updateLocation();
  driveDestination(false, 200, (Enes100.location.x + 0.2), (Enes100.location.y));
  Enes100.updateLocation();
  Enes100.println("DODGE OBSTACLE: 3-------------------");
  driveDestination(false, 200, (Enes100.location.x + 0.35), startPos[1]);
  Enes100.updateLocation();
  faceDir(0);
}
*/


void initialize(){
  //Motors Start:
  pinMode(12, OUTPUT); 
  pinMode(13, OUTPUT); 
  //Motors End

  //Sonar Start:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);
  //Sonar End
}
void driveDestination(boolean sensing, float defaultOsvSpeed, float x, float y){ //maybe add boolean for gradual speed
  int debugTicker = 0;
  double debug1 = 0;
  double debug2 = 2;
  Enes100.updateLocation();
  double osvSpeed = defaultOsvSpeed;
  double startPos [] = {Enes100.location.x, Enes100.location.y, Enes100.location.theta};
  double tAdjacent = x - Enes100.location.x;
  double tOpposite = y - Enes100.location.y;
  float angleChange = atan2(tOpposite, tAdjacent) - startPos[2];
  Enes100.print("arcTan( tOpposite: ");
  Enes100.print(tOpposite);
  Enes100.print("/ tAdjacent:");
  Enes100.print(tAdjacent);
  Enes100.print(") = ");
  Enes100.println(angleChange);
  float distance = sqrt(pow(tAdjacent,2) + pow(tOpposite,2));
  float distanceTraveled = 0;
  float travelPercent = 0;
  Enes100.print("Location: ");
  Enes100.print("(");
  Enes100.print(Enes100.location.x);
  Enes100.print(", ");
  Enes100.print(Enes100.location.y);
  Enes100.println(")");
  Enes100.print("Destination: ");
  Enes100.print("(");
  Enes100.print(x);
  Enes100.print(", ");
  Enes100.print(y);
  Enes100.println(")");
  Enes100.print("Angle Change: ");
  Enes100.println(angleChange);
  Enes100.print("Distance: ");
  Enes100.println(distance);
  Enes100.print("tOpposite: ");
  Enes100.println(tOpposite);
  Enes100.print("tAdjacent: ");
  Enes100.println(tAdjacent);
  Enes100.println(angleChange);
  Enes100.println(angleChange);
  Enes100.println(angleChange);
  faceDir(Enes100.location.theta + angleChange);
  while(distanceTraveled < distance){
    /*if(sensing == true){
      Enes100.updateLocation();
      Enes100.print("Sensor[0]: ");
      Enes100.println(Enes100.readDistanceSensor(0));
      Enes100.print("Sensor[2]: ");
      Enes100.println(Enes100.readDistanceSensor(2));
      if(Enes100.readDistanceSensor(0) <= 40 || Enes100.readDistanceSensor(2) <= 40){
        if(debugTicker % 60 == 0){
          debug1 = Enes100.readDistanceSensor(0);
        }
        else if(debugTicker % 30 == 0){
          debug2 = Enes100.readDistanceSensor(0);
        }
        if(debug1 == debug2){
          Enes100.println("!!!STUCK GLITCH!!!");
          dodgeObstacle();
        }
        osvSpeed = osvSpeed/1.5;
        if(Enes100.readDistanceSensor(0) <= 24.5 || Enes100.readDistanceSensor(2) <= 24.5){
          Enes100.println("-= DODGING OBSTACLE! =-");
          dodgeObstacle();
        }
      }
      else{
        osvSpeed = defaultOsvSpeed;
      }
    }*/
    Enes100.print("Driving: ");
    Enes100.print(distanceTraveled);
    Enes100.print("/");
    Enes100.println(distance);
    Enes100.updateLocation();
    distanceTraveled = sqrt(pow(floatDiff(startPos[0],Enes100.location.x),2) + pow(floatDiff(startPos[1],Enes100.location.y),2));
    travelPercent = distanceTraveled / distance;
    if(travelPercent <= .9){
      driveForward(osvSpeed);
    }
    else if(travelPercent <= .95){
      driveForward(osvSpeed / 2);
    }
    else{
      driveForward(osvSpeed / 2.5);
    }
  }
  driveForward(0);
  Enes100.print(distance);
  Enes100.print("/");
  Enes100.println(distanceTraveled);
  Enes100.println("STOP! - Driving");
}






float floatDiff(float x, float y){ //float difference function
  if(x >= y){
    return x - y;
  }
  else if(x < y){
    return y - x;
  }
}

void faceDir(float dir){
  Enes100.updateLocation();
  float rotateRad = rotateRadians(dir);
  float rotateGoal = Enes100.location.theta + rotateRad;
  float rotateStart = Enes100.location.theta;
  float rotateProgress = Enes100.location.theta;
  float rotateDiff = floatDiff(rotateGoal,rotateProgress);
  float percentDone = (abs(abs(rotateStart) + rotateProgress) / rotateDiff);
  Enes100.print("From ");
  Enes100.print(Enes100.location.theta);
  Enes100.print(" To ");
  Enes100.println(rotateGoal);
  Enes100.print("Radian Distance: ");
  Enes100.println(rotateRad);
  //Enes100.println("Radians to turn: " + rotateRad);
  if(rotateDiff <= 0.05){
    //nothing
    Enes100.println("NOT ROTATING, < 0.05");
  }
  else if(rotateRad > 0){
    //rotat counterClockwise
    while(rotateProgress < rotateGoal){
      Enes100.updateLocation();
      if(rotateGoal > PI){
        if(Enes100.location.theta >= 0){
          rotateProgress = Enes100.location.theta;
        }
        else{
          rotateProgress = PI + floatDiff(Enes100.location.theta, -PI);
        }
      }
      else{
        rotateProgress = Enes100.location.theta;
      }
      Enes100.print("Rotation Progress: "); 
      Enes100.print(rotateProgress); 
      Enes100.print("/");
      Enes100.println(rotateGoal);
      Enes100.print("Percent: "); //Artificial percent for speed
      percentDone = (floatDiff(rotateProgress, rotateStart) / rotateDiff);
      Enes100.println(percentDone);
      if(percentDone >= 0.99){
        break;
      }
      //ROTATE DIFF
      if(rotateDiff <= 0.1){
        percentDone = .97;
      }
      if(rotateDiff <= 0.3 && percentDone < 0.8){
        percentDone = .8;
      }
      else if(rotateDiff <= 0.1 && percentDone < 0.8){
        percentDone = .9;
      }
      //PERCEBT DONES
      if(percentDone <= .8){ //Motor Speeds
        counterClockwise(100); 
      }
      else if(percentDone <= .95){
        counterClockwise(50);
      }
      else{
        counterClockwise(40);
      }
    }
    Enes100.println("STOP! - turning");
    counterClockwise(0);
  }
  else if(rotateRad < 0){ //CLOCKWISE ROTATION
    //rotate clockwise
    while(rotateProgress > rotateGoal){
      Enes100.updateLocation();
      if(rotateGoal < -PI){
        if(Enes100.location.theta <= 0){
          rotateProgress = Enes100.location.theta;
        }
        else{
          rotateProgress = -PI - floatDiff(Enes100.location.theta, PI);
        }
      }
      else{
        rotateProgress = Enes100.location.theta;
      }
      Enes100.print("Rotation Progress: "); 
      Enes100.print(rotateProgress); 
      Enes100.print("/");
      Enes100.println(rotateGoal);
      Enes100.print("Percent: "); //Artificial percent for speed
      percentDone = (floatDiff(rotateProgress, rotateStart) / rotateDiff);
      Enes100.println(percentDone);
      if(percentDone >= 0.99){
        break;
      }
      //ROTATE DIFF
      if(rotateDiff <= 0.1){
        percentDone = .97;
      }
      if(rotateDiff <= 0.3 && percentDone < 0.8){
        percentDone = .8;
      }
      else if(rotateDiff <= 0.1 && percentDone < 0.8){
        percentDone = .9;
      }
      //PERCEBT DONES
      if(percentDone <= .8){ //Motor Speeds
        clockwise(100); 
      }
      else if(percentDone <= .95){
        clockwise(50);
      }
      else{
        clockwise(5);
      }
    }
    Enes100.print("STOP! - Rotating");
    clockwise(0);
  }
  else{
    Enes100.print("_____NOT ROTATING!_____");
  }
}

float rotateRadians(float dir){
  if(dir == Enes100.location.theta){
    return 0;
  }
  boolean Q1 [] = {0,0,0}; // [overall, osv.theta, destination]
  boolean Q2 [] = {0,0,0}; // [overall, osv.theta, destination]
  boolean Q3 [] = {0,0,0}; // [overall, osv.theta, destination]
  boolean Q4 [] = {0,0,0}; // [overall, osv.theta, destination]

  //SETS QUADRANT FOR THE OSV THETA
  if(Enes100.location.theta >= 0 && Enes100.location.theta <= PI/2){
    Q1[0] = true;
    Q1[1] = true;
  }
  else if(Enes100.location.theta <= PI && Enes100.location.theta >= PI/2){
    Q2[0] = true;
    Q2[1] = true;
  }
  else if(Enes100.location.theta >= -PI && Enes100.location.theta <= -PI/2){
    Q3[0] = true;
    Q3[1] = true;
  }
  else if(Enes100.location.theta > -PI/2 && Enes100.location.theta < 0){
    Q4[0] = true;
    Q4[1] = true;
  }
  
  //SETS QUADRANT FOR THE DESTINATION
  if(dir >= 0 && dir <= PI/2){
    Q1[0] = true;
    Q1[2] = true;
  }
  else if(dir >= PI/2 && dir <= PI){
    Q2[0] = true;
    Q2[2] = true;
  }
  else if(dir >= -PI && dir <= -PI/2){
    Q3[0] = true;
    Q3[2] = true;
  }
  else if(dir > -PI/2 && dir < 0){
    Q4[0] = true;
    Q4[2] = true;
  }

  Enes100.print("Q1: ");
  Enes100.print(Q1[0]);
  Enes100.print(Q1[1]);
  Enes100.println(Q1[2]);
  
  Enes100.print("Q2: ");
  Enes100.print(Q2[0]);
  Enes100.print(Q2[1]);
  Enes100.println(Q2[2]);
  
  Enes100.print("Q3: ");
  Enes100.print(Q3[0]);
  Enes100.print(Q3[1]);
  Enes100.println(Q3[2]);
  
  Enes100.print("Q4: ");
  Enes100.print(Q4[0]);
  Enes100.print(Q4[1]);
  Enes100.println(Q4[2]);
  
  //Q1
  if(Q1[1] && Q1[2]){
    if(Enes100.location.theta >= dir){
      return -(floatDiff(Enes100.location.theta,dir));
    }
    else{
      return (floatDiff(Enes100.location.theta,dir));
    }
  }
  else if(Q1[0] && Q2[0]){
    if(Q1[1] && Q2[2]){
      return (floatDiff(Enes100.location.theta,dir));
    }
    else{ // Q1[2] && Q2[1]
      return -(floatDiff(Enes100.location.theta,dir));
    }
  }
  else if(Q1[0] && Q3[0]){
    if(Q1[1] && Q3[2]){
      if(floatDiff(Enes100.location.theta,dir) <= PI){
        return -(floatDiff(Enes100.location.theta,dir));
      }
      else{ // rotate 
        return ((PI * 2) - floatDiff(Enes100.location.theta,dir));
      }
    }
    else{ //Q1[2] && Q3[1]
      if(floatDiff(Enes100.location.theta,dir) <= PI){
        return (floatDiff(Enes100.location.theta,dir));
      }
      else{
        return -(floatDiff(Enes100.location.theta,dir));
      }
    }
  }
  else if(Q1[0] && Q4[0]){
    if(Q1[1] && Q4[2]){
      return -(floatDiff(Enes100.location.theta,dir));
    }
    else{ //Q1[2] && Q4[1]
      return (floatDiff(Enes100.location.theta,dir));
    }
  }
  //Q2
  if(Q2[1] && Q2[2]){
    if(Enes100.location.theta >= dir){
      return -(floatDiff(Enes100.location.theta,dir));
    }
    else{ 
      return (floatDiff(Enes100.location.theta,dir));
    }
  }
  else if(Q2[0] && Q3[0]){
    if(Q2[1] && Q3[2]){
      return ((PI*2) - floatDiff(Enes100.location.theta,dir));
    }
    else{ //Q2[2] && Q3[1]
      return -((PI*2) - floatDiff(Enes100.location.theta,dir));
    }
  }
  else if(Q2[0] && Q4[0]){
    if(Q2[1] && Q4[2]){
      if(floatDiff(Enes100.location.theta,dir) <= PI){
        return -(floatDiff(Enes100.location.theta,dir));
      }
      else{
        return ((PI * 2) - floatDiff(Enes100.location.theta,dir));
      }
    }
    else{ //Q2[2] && Q4[1]
      if(floatDiff(Enes100.location.theta,dir) <= PI){
        return (floatDiff(Enes100.location.theta,dir));
      }
      else{
        return -((PI * 2) - floatDiff(Enes100.location.theta,dir));
      }
    }
  }
  //Q3 / Q4
  else if(Q3[1] && Q3[2]){
    if(Enes100.location.theta <= dir){
      return (floatDiff(Enes100.location.theta,dir));
    }
    else{
      return -(floatDiff(Enes100.location.theta,dir));
    }
  }
  else if(Q3[0] && Q4[0]){
    if(Q3[1] && Q4[2]){
      return (floatDiff(Enes100.location.theta,dir));
    }
    else{ //Q3[2] && Q4[1]
      return -(floatDiff(Enes100.location.theta,dir));
    }
  }
  else if(Q4[1] && Q4[2]){
    if(Enes100.location.theta <= dir){
      return (floatDiff(Enes100.location.theta,dir));
    }
    else{
      return -(floatDiff(Enes100.location.theta,dir));
    }
  }
}

void clockwise(int wheelSpeed){
  int goWheelSpeed = 255;
  //Turning RIGHT
  //Motor A forword @ full speed
  digitalWrite(12, LOW); //Establishes forward direction of Channel A
  analogWrite(3, goWheelSpeed);   //Spins the motor on Channel A at full speed
  //Motor B foreword @ full speed
  digitalWrite(13, LOW);  //Establishes backward direction of Channel B
  analogWrite(11, goWheelSpeed);    //Spins the motor on Channel B at full speed
}
void counterClockwise(int wheelSpeed){
  int goWheelSpeed = 255;
  //Turning LEFT
  //Motor A forword @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  analogWrite(3, goWheelSpeed);   //Spins the motor on Channel A at full speed
  //Motor B foreword @ full speed
  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  analogWrite(11, goWheelSpeed);    //Spins the motor on Channel B at full speed
}
void driveForward(int wheelSpeed){
  int goWheelSpeed = 255;
  //Forwards
  //Motor A forword @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  analogWrite(3, goWheelSpeed);   //Spins the motor on Channel A at full speed
  //Motor B foreword @ full speed
  digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
  analogWrite(11, goWheelSpeed);    //Spins the motor on Channel B at full speed
}
