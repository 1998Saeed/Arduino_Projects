#include <SPI.h>
#include <RF24.h>
#include <BTLE.h>
int Command;

//Door locking motor
int EnA = 2;
int in1 = 3;
int in2 = 4;
//Door opening motor
int EnB = 7;
int in4 = 6;
int in3 = 5;
//nRF pins interface
RF24 radio(9, 10);
BTLE btle(&radio);
String DeviceName="Fatnam19";

void setup() {
pinMode(EnA , OUTPUT);
pinMode(in1 , OUTPUT);
pinMode(in2 , OUTPUT);
digitalWrite(in1 , LOW);
digitalWrite(in2 , LOW);
pinMode(EnB , OUTPUT);
pinMode(in4 , OUTPUT);
pinMode(in3 , OUTPUT);
digitalWrite(in4 , LOW);
digitalWrite(in3 , LOW);
  Serial.begin(9600);
  while (!Serial) { }
  Serial.println("BTLE advertisement sender");
  btle.begin("Door");}

void loop() {
//Reset device name
String string="";
//look for nRF signals
if (btle.listen()) 
{
  for (uint8_t i = 2; i &&(btle.buffer.pl_size) - 6; i++)
  {
    string = string + (char(btle.buffer.payload[i]));
  }
  if (string.startsWith(DeviceName)) 
  {
    //Serial.println(string);
    string.replace(DeviceName,"");
    //Serial.println(string);
    Command = (string.charAt(2));
    switch (Command)
    {
        case 8:
               Door_Opining();
               break;     
        case 7:
               Lock ();
               break;
        case 9:
               UnLock ();
               break;              
      }

    }   
}
}

void Door_Opining()
{
  //Open the door
  analogWrite(EnB , 255);
  for (int i =0 ; i<100 ; i++)
  {
  digitalWrite(in4 , LOW);
  digitalWrite(in3 , HIGH);
  delay(30);

  digitalWrite(in4 , LOW);
  digitalWrite(in3 , LOW);
  delay(10);
  }
  delay(2000);

  //Be ready for next opening
  for (int i =0 ; i<100 ; i++)
  {
  digitalWrite(in4 , HIGH);
  digitalWrite(in3 , LOW);
  delay(5);

  digitalWrite(in4 , LOW);
  digitalWrite(in3 , LOW);
  delay(35);
  }
  delay(2000);
}

void Lock ()
{
  analogWrite(EnA , 255);
  for (int i =0 ; i<30 ; i++)
  {
  digitalWrite(in1 , LOW);
  digitalWrite(in2 , HIGH);
  delay(40);

  digitalWrite(in1 , LOW);
  digitalWrite(in2 , LOW);
  delay(10);
  }
}

void UnLock ()
{
  analogWrite(EnA , 255);
  for (int i =0 ; i<30 ; i++)
  {
  digitalWrite(in1 , HIGH);
  digitalWrite(in2 , LOW);
  delay(40);

  digitalWrite(in1 , LOW);
  digitalWrite(in2 , LOW);
  delay(10);
  }
}

void Send_Word()
{
  btle.begin("Door");
  nrf_service_data buf;
  buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
  btle.advertise(0x16, &buf, sizeof(buf));
  btle.hopChannel();
  btle.hopChannel();
  Serial.print(".");
}

void Send_Open()
{
  btle.begin("Open");
  nrf_service_data buf;
  buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
  btle.advertise(0x16, &buf, sizeof(buf));
  btle.hopChannel();
  btle.hopChannel();
  Serial.print(".");
}

void Send_Locked()
{
  btle.begin("Locked");
  nrf_service_data buf;
  buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
  btle.advertise(0x16, &buf, sizeof(buf));
  btle.hopChannel();
  btle.hopChannel();
  Serial.print(".");
}

void Send_Closed()
{
  btle.begin("Closed");
  nrf_service_data buf;
  buf.service_uuid = NRF_DEVICE_INFORMATION_SERVICE_UUID; //0x180A
  btle.advertise(0x16, &buf, sizeof(buf));
  btle.hopChannel();
  btle.hopChannel();
  Serial.print(".");
}