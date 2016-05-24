#define PCB_SIGNAL_R 14
#define PCB_SIGNAL_L 15
#define PWM1 3
#define PWM2 4
#define IN1 5
#define IN2 6
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
  int tolerance = 0;

  int time;
  double kp;

boolean isHigh(int val){ return val<50; }
//boolean RHigh(int val){ return val<0; }
int acquireSensor(int pin);
void move();
void turnRight();
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

  kp = .25;
  time = 10;
}

void loop() {

  // put your main code here, to run repeatedly:
  int sl = analogRead(PCB_SIGNAL_L);
  int sr = analogRead(PCB_SIGNAL_R);

  sr = map(sr, 0, 1024, 255, 0);
  sl = map(sl, 0, 1024, 255, 0);

  Serial.print("LEFT: "); Serial.print(sl); Serial.print(" RIGHT: "); Serial.println(sr);
  Serial.print(isHigh(sl)); Serial.print(" "); Serial.println(isHigh(sr));

  while(sl>95&&sr>95){
    analogWrite(PWM2, 255);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    analogWrite(PWM1, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  stopMoving();
  
  delay(80);

}

int acquireSensor(int pin){
  int sum = 0;
  for(int i = 0; i < 1000; i++){
    sum+=analogRead(pin);
  }
  return sum/1000;
}

void move(){
  rightRead = analogRead(PCB_SIGNAL_R);
  leftRead = analogRead(PCB_SIGNAL_L);
  rightError = rightRead - rightBaseline;
  leftError = leftRead - leftBaseline;

  rightError*=(255/1023);
  leftError*=(255/1023);

  if(rightError > tolerance){
    rightSpeed -= abs(kp*rightError);
    leftSpeed += abs(kp*rightError);
  }
  if(leftError > tolerance){
      rightSpeed += abs(Kp*leftError); //shift left
      leftSpeed -= abs(Kp*leftError);
  }
  else{
      
  }
    // Normalize speeds if they exceed the system limit
    if speed < 0
      speed = 0
    if speed > 255
      speed = 255
  
    
    // Set motor control signals
    set motors to forward direction
       set right PWM (rightSpeed)
       set left PWM (leftSpeed)
}

void stopMoving(){
  
}
