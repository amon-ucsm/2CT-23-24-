/*
 *This code is 2CT project code of Line following and obstacle avoiding car using arduino
 *2023-2024 AY
 *University of Computer Studies, Mandalay(UCSM)
 
*/
//Define motor
#define enA 5 //To set speed of left motors
#define in1 6 //Left motors are forward in HIGH
#define in2 7 //Left motors are backward in HIGH
#define in3 8 //Right motors are forward in HIGH
#define in4 9 //Right motors are backward in HIGH
#define enB 10 //To set speed of right motors

//Define ultrasonic
#define trig A0 //Tramsmit
#define echo 3 //Receive
long duration;
int distance;

//Define ir sensor
#define ir_left A1 //Receive data of left IR sensor
#define ir_right A3 //Receive data of right IR sensor

//Set nrmal speed
int speed=200;

//Set rotata speed
int rot_speed=255; 

//Delay a time
int wati_millis=100; 

//Reading distance and return distance
int ulteasonic()
{
  //This function will return distance
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration=pulseIn(echo, HIGH);
  distance=duration * 0.0344 / 2;
  //Serial.println(distance);
  return distance;
}

//Reding left IR sensor value 1 or 0
int get_left_ir_value()
{
  //This function will return left sensor value
  int value=digitalRead(ir_left);
  return value;
}

//Read right IR sensor value 1 or 0 
int get_right_ir_value()
{
  //This function will return right sensor value
  int value=digitalRead(ir_right);
  return value;
}

void setup() {
  // put your setup code here, to run once:

  //Set motor driver pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Set ultrasonic sensor pins
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //Set IR sensor pins
  pinMode(A1, INPUT); //Left IR
  pinMode(A3, INPUT); //Right IR

  //Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dis=ulteasonic();
  Serial.println(dis);
  //delay(100);
  if(dis < 8)
  {
    //Serial.println("less Than 30");
    avoid();
    delay(100);
  }
  //if
  //{
    int val_left=get_left_ir_value();
    int val_right=get_right_ir_value();
    //Serial.print(val_left);
    //Serial.print(" ");
    //Serial.println(val_right);
    if(val_left == LOW && val_right == LOW){
      //Serial.println("Forward");
      forward();
      delay(50);
    }
    else if(val_left == HIGH && val_right == LOW){
      //Serial.println("Adjust to left");
      adj_left();
      delay(50);
    }
    else if(val_left == LOW && val_right == HIGH){
      //Serial.println("Adjust to right");
      adj_right();
      delay(50);
    }
    else if (val_left == HIGH && val_right == HIGH){
      //Serial.println("Stop");
      stop();
    }
    delay(100);
  //}
  //delay(100);
}

//Function forward
void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA ,speed);
  analogWrite(enB, speed);
  delay(wati_millis);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(wati_millis);
}

//Function backward
void backward()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA ,speed);
  analogWrite(enB, speed);
  delay(wati_millis);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(wati_millis);
}

//Function adjust to left
void adj_left()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA ,speed);
  analogWrite(enB, speed);
  delay(wati_millis);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(wati_millis);
}

//Function adjust to right
void adj_right()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(wati_millis);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(wati_millis);
}

//Function stop
void stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA ,0);
  analogWrite(enB, 0);
}

//Break
void Break(int time)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA ,0);
  analogWrite(enB, 0);
  delay(time);
}

//Function avoid
void avoid()
{
  Break(100);
  backward();
  delay(200);
  Break(100);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  delay(550);
  Break(50);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  delay(550);
  Break(50);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  delay(900);
  Break(50);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 150);
  analogWrite(enB, 150);
  delay(100);
}
