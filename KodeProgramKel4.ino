#include <Servo.h>
#define trigPin 11 //pin trig dari ultrasonik ke 11 arduino
#define echoPin 10 //pin echo dari ultrasonik ke 10 arduino
Servo myservo; //mendefinisikan servo

const int inductive = 8; //pin 8 input dari output proximity 
const int LED       = 13;
long duration, distance; 
int jarak = 5;
bool adaSampah = 0;
void setup() {
  myservo.attach(9); 
  pinMode (inductive,INPUT);
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.write(90);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  if (distance < jarak){
    Serial.println("Ada Sampah");
    adaSampah = 1;
    bacaSensor();
  } else {
    Serial.println("Tidak Ada Sampah");
    adaSampah = 0;
  }
  delay(500);
}

void bacaSensor(){
  digitalWrite(LED, HIGH);
  delay (2000);
  digitalWrite(LED, LOW);
  delay(500);
  if (!digitalRead(inductive)){
    Serial.println(" ==> Sampah Logam");
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    myservo.write(180);
    delay(2000);
    myservo.write(90);
  } else {
    Serial.println(" ==> Sampah Non Logam");
    myservo.write(0);
    delay(2000);
    myservo.write(90);
  }
}