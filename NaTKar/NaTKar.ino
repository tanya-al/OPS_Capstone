#define PCB_SIGNAL 14
#define PWM1 3
#define PWM2 4
#define IN1 5
#define IN2 6
#define IN3 7
#define IN4 8

int sum = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PCB_SIGNAL, INPUT);
  
  int numOfSamples = 1000;
  for(int i = 0; i < numOfSamples; i++){
    int val = analogRead(PCB_SIGNAL);
    sum+=val;
  }
  sum /= numOfSamples;
}

void loop() {
  analogWrite(PWM2, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  Serial.println(sum);
  // put your main code here, to run repeatedly:
  int s = analogRead(PCB_SIGNAL);
  Serial.println(s);
  s = map(s, 0, sum, 255, 0);
  Serial.println(s);
  delay(100);

  analogWrite(PWM1, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
}
