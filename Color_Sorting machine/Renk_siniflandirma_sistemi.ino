#include <Servo.h>
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12

Servo m1;
Servo m2;
int frequency = 0;
int color = 0;
int i = 45;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  m1.attach(2);
  m2.attach(3);
  Serial.begin(9600);
}
// Custom Function - readColor()
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  if (R<25 & R>10 & G<40 & G>20) {
    color = 1; // Red
  }
  if (R<27 & R>15 & G<20 & G>10) {
    color = 2; // Green
  }
  if (R<15 & R>5 & G<17 & G>7) {
    color = 3; // Yellow
  }
  if (G<25 & G>12 & B<15 & B>7) {
    color = 4; // Blue
  }
  return color;
}
void loop() {
   m1.write (115);
  delay (1000);
  m1.write (65);
  delay (3000);
   color = readColor();
 if (color != 0){ 
  delay(10);
  switch (color) {
    case 1:
      m2.write(45);
        delay (500);
  m1.write (10);
  delay (500);
      break;
    case 2:
      m2.write(80);
        delay (500);
  m1.write (10);
  delay (500);
      break;
    case 3:
      m2.write(115);
        delay (500);
  m1.write (10);
  delay (500);
      break;
    case 4:
      m2.write(150);
        delay (500);
  m1.write (10);
  delay (500);
      break;}
  color = 0;}
  else {m1.write (115);
  delay (5000);}
}
