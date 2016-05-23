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

boolean isHigh(int val){ return val<-90; }
//boolean RHigh(int val){ return val<0; }

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
  
  for(int i = 0; i < 1000; i++){
    sumr+=analogRead(PCB_SIGNAL_R);
    suml+=analogRead(PCB_SIGNAL_L);
  }

  sumr/=1000;
  suml/=1000;
}

void loop() {

  analogWrite(PWM2, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(PWM1, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // put your main code here, to run repeatedly:
  int sl = analogRead(PCB_SIGNAL_L);
  int sr = analogRead(PCB_SIGNAL_R);

  sr = map(sr, 0, 1024, 255, 0);
  sl = map(sl, 0, 1024, 255, 0);

  Serial.print("SUM LEFT: ");
  Serial.print(suml);
  Serial.print(" SUM RIGHT: ");
  Serial.println(sumr);

  Serial.print("LEFT: ");
  Serial.print(sl);
  Serial.print(" RIGHT: ");
  Serial.println(sr);

  Serial.print(isHigh(sl));
  Serial.print(" ");
  Serial.println(isHigh(sr));
  
  delay(80);

}
