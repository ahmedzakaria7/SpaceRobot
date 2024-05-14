#include <Servo.h>
#include <NewPing.h> 
#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTTYPE DHT11 
#define DHTPIN 12   
LiquidCrystal lcd(1, 2, 8, 9, 10, 11);
DHT dht(DHTPIN, DHTTYPE); 
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;
#define trig_pin A1 
#define echo_pin A2 
#define maximum_distance 2000
boolean goesForward = false;
int distance = 1000;
NewPing sonar(trig_pin, echo_pin, maximum_distance); 
Servo servo_motor; 
void setup(){
pinMode(RightMotorForward, OUTPUT);
pinMode(LeftMotorForward, OUTPUT);
pinMode(LeftMotorBackward, OUTPUT);
pinMode(RightMotorBackward, OUTPUT);
servo_motor.attach(9); 
servo_motor.write(115);
delay(2000);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
distance = readPing();
delay(100);
dht.begin();
lcd.begin(16, 2);
lcd.print("temp: 33.20 C");
lcd.setCursor(0, 1);
lcd.print("Humidity: 48.20%");
}
void loop(){
int distanceRight = 0;
int distanceLeft = 0;
delay(50);
if (distance <= 50){
moveStop();
delay(0);
moveBackward();
delay(0);
moveStop();
delay(0);
distanceRight = lookRight();
delay(0);
distanceLeft = lookLeft();
delay(0);
if (distance >= distanceLeft){
  turnRight();
  moveStop();
}
else{
  turnLeft();
  moveStop();
}
}
else{
moveForward();
}
distance = readPing();
}
int lookRight(){
servo_motor.write(0);
delay(500);
int distance = readPing();
delay(100);
servo_motor.write(85);
return distance;
}
int lookLeft(){
servo_motor.write(170);
delay(500);
int distance = readPing();
delay(100);
servo_motor.write(85);
return distance;
delay(100);
}
int readPing(){
delay(70);
int cm = sonar.ping_cm();
if (cm==0){
cm=10;
}
return cm;
delay(1000); 
	float H = dht.readHumidity();     
	float T = dht.readTemperature();    
	  if (isnan(H) || isnan(T)) {
		lcd.print("Failed to read from DHT sensor!");
		return;
	}
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Humidity:"); 
	lcd.print(H);
	lcd.print("%");
	lcd.setCursor(0, 1);
	lcd.print("Temp.:"); 
	lcd.print(T);
	lcd.print((char)223);
	lcd.print("C");
}
void moveStop(){
digitalWrite(RightMotorForward, LOW);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(RightMotorBackward, LOW);
digitalWrite(LeftMotorBackward, LOW);
}
void moveForward(){
if(!goesForward){
goesForward=true;
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorBackward, LOW); 
}
}
void moveBackward(){
goesForward=false;
digitalWrite(LeftMotorBackward, HIGH);
digitalWrite(RightMotorBackward, HIGH);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(RightMotorForward, LOW);
}
void turnRight(){
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorBackward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorForward, LOW);
delay(500);
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorBackward, LOW);
}
void turnLeft(){
digitalWrite(LeftMotorBackward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorForward, LOW);
digitalWrite(RightMotorBackward, LOW);
delay(500);
digitalWrite(LeftMotorForward, HIGH);
digitalWrite(RightMotorForward, HIGH);
digitalWrite(LeftMotorBackward, LOW);
digitalWrite(RightMotorBackward, LOW);
}
