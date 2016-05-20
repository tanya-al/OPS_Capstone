#define PCB_SIGNAL_R 14
#define PCB_SIGNAL_L 15
#define PWM1 3
#define PWM2 4
#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8

int sum = 0;

boolean LHigh(int val){ return val<0; }
boolean RHigh(int val){ return val<-20; }

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
  
  int numOfSamples = 1000;
  for(int i = 0; i < numOfSamples; i++)
    sum+=analogRead(PCB_SIGNAL_L)+analogRead(PCB_SIGNAL_R);

  sum /= numOfSamples*2;
}

void loop() {
  analogWrite(PWM2, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  // put your main code here, to run repeatedly:
  int sl = analogRead(PCB_SIGNAL_L);
  int sr = analogRead(PCB_SIGNAL_R);
  
  sr = map(sr, 0, sum, 255, 0);
  sl = map(sl, 0, sum, 255, 0);

//  Serial.print(sl);
//  Serial.print(" ");
//  Serial.println(sr);
  
  Serial.print(LHigh(sl));
  Serial.print(" ");
  Serial.println(RHigh(sr));
  
  delay(80);

  analogWrite(PWM1, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
}
