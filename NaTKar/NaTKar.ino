#define PCB_SIGNAL_R 14
#define PCB_SIGNAL_L 15
#define PWM1 3    // control the speed of the motors
#define PWM2 4
#define IN1 5   // control the motors
#define IN2 6   //
#define IN3 7
#define IN4 8

int suml = 0;    
int sumr = 0;

// Declare parameters of the robot to measure and control
  int leftSpeed = 0;
  int rightSpeed = 0;

  int rightRead = 0;
  int leftRead = 0;

  int rightBaseline = 0;
  int leftBaseline = 0;

  // Parameters for the controller
  int rightError = 0;
  int leftError = 0;
  int prevRightError = 0;
  int prevLeftError = 0;
  int prevTotalError = 0;
  int totalError = 0;
  int tolerance = 0;
  int defaultSpeed = 120;
  int derivative = 0; 
  

  int time;
  int integral;
  double kp = 0.8;
  double ki = 0; 
  double kd = 0;

boolean isHigh(int val){ return val<50; }
//int acquireSensor(int pin);
void move();
void moveStraight();
void turnRight();
void turnLeft();
void stopMoving();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PCB_SIGNAL_L, INPUT);
  pinMode(PCB_SIGNAL_R, INPUT);
  delay(100);
  for(int i = 0; i < 1000; i++){
    sumr+=analogRead(PCB_SIGNAL_R);
    suml+=analogRead(PCB_SIGNAL_L);
  }

  sumr/=1000;
  suml/=1000;

  // is this right?? IDK

  rightBaseline = sumr;
  leftBaseline = suml;
  //

  time = 10;
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);

    analogWrite(PWM1, 255);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    delay(3000);
}

void loop() {

  // Cullen's Whiteboard Code <3
  rightRead = analogRead(PCB_SIGNAL_R);
  leftRead = analogRead(PCB_SIGNAL_L);
  rightError = rightRead - rightBaseline;
  leftError = leftRead - leftBaseline;

  rightError*=(255/1023);
  leftError*=(255/1023);

  totalError = leftError - rightError;

  derivative = totalError - prevTotalError;
  prevTotalError = totalError;
  int tspeed;
  tspeed = kp*totalError + kd*derivative; 

  leftSpeed = defaultSpeed - tspeed;
  rightSpeed = defaultSpeed + tspeed;

  // don't need to go backwards ever so just set the parts of the motor that make it go forward to high 
  // and set the part that makes the motor go backward to low all the time

    analogWrite(PWM2, rightSpeed);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(PWM1, leftSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  
}
////    turnRight();
//  moveStraight(); 
//  // put your main code here, to run repeatedly:
//  int sl = analogRead(PCB_SIGNAL_L);
//  int sr = analogRead(PCB_SIGNAL_R);
//
//  sr = map(sr, 0, 1024, 255, 0);
//  sl = map(sl, 0, 1024, 255, 0);
//
////  Serial.print("LEFT: "); Serial.print(sl); Serial.print(" RIGHT: "); Serial.println(sr);
//
//  while(sl>95&&sr>95)
//  {
//    moveStraight();  // or should we call move()??
//    sl = analogRead(PCB_SIGNAL_L);
//    sr = analogRead(PCB_SIGNAL_R);
//  
//    sr = map(sr, 0, 1024, 255, 0);
//    sl = map(sl, 0, 1024, 255, 0);
//
//    delay(100);
//  }
//  
//  stopMoving();
//    
//  // decide which direction to move in
//  if (sl < suml)
//    turnLeft();
//  else if (sr < sumr)
//    turnRight();
////    move();

//int acquireSensor(int pin){
//  int sum = 0;
//  for(int i = 0; i < 1000; i++){
//    sum+=analogRead(pin);
//  }
//  return sum/1000;
//}

//void move(){
//  rightRead = analogRead(PCB_SIGNAL_R);
//  leftRead = analogRead(PCB_SIGNAL_L);
//  rightError = rightRead - rightBaseline;
//  leftError = leftRead - leftBaseline;
//
//  rightError*=(255/1023);
//  leftError*=(255/1023);
//
//  if(rightError > tolerance){
//    rightSpeed -= abs(kp*rightError);  // shift right
//    leftSpeed += abs(kp*rightError);
//  }
//  if(leftError > tolerance){
//      rightSpeed += abs(kp*leftError); // shift left
//      leftSpeed -= abs(kp*leftError);
//  }
//  
//  else {
//      
//  }
//    // Normalize speeds if they exceed the system limit
//    if (rightSpeed < 0)
//      rightSpeed = 0;
//    if (leftSpeed < 0)
//      leftSpeed = 0;
//    if (rightSpeed > 255)
//      rightSpeed = 255;
//    if (leftSpeed > 255)
//      leftSpeed = 255;
//  
//    
//    // Set motor control signals
//    analogWrite(PWM2, rightSpeed);
//    digitalWrite(IN3, HIGH);
//    digitalWrite(IN4, LOW);
//
//    analogWrite(PWM1, leftSpeed);
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, LOW);
//
//       // call function to determine which direction
//}
//
//void stopMoving(){
//  // write IN1, IN2, IN3, IN4 as high for all
//    analogWrite(PWM2, 255);
//    digitalWrite(IN3, HIGH);
//    digitalWrite(IN4, HIGH);
//
//    analogWrite(PWM1, 255);
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, HIGH);
//}
//
//void moveStraight()
//{
//  // add more checking stuff
//    analogWrite(PWM2, 255);
//    digitalWrite(IN3, HIGH);
//    digitalWrite(IN4, LOW);
//
//    analogWrite(PWM1, 255);
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, LOW);
//}
//
//void turnRight()
//{
//    // right motor backwards
//    digitalWrite(IN3, LOW);
//    digitalWrite(IN4, HIGH);
//    // left motor forward
//    digitalWrite(IN1, HIGH);
//    digitalWrite(IN2, LOW);
//    // delay
//    delay(80);
//    // move straight again
//}
//
//void turnLeft()
//{
//    // right motor forwards
//    digitalWrite(IN3, HIGH);
//    digitalWrite(IN4, LOW);
//    // left motor backward
//    digitalWrite(IN1, LOW);
//    digitalWrite(IN2, HIGH);
//    // delay
//    delay(80);
//    // move straight again
//}
//
//// if one of the sensors reads below 95 then we are on the line = HIGH
//// above 95 is LOW (not on the line which is good)
//
////
