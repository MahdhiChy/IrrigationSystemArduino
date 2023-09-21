//This is the arduino code for the project smart irrigation system using Arduino and GSM module

//This code is written by Golam Mahdhi Chowdhury

//Helps taken from different online sources


#include <Servo.h>    //including the servo library
#include <SoftwareSerial.h>

SoftwareSerial mGSM(9, 10);
Servo mahdhi;
char msg;
char call;
int Relay = 9;
int m;
int n;
int pos = 0;
int check = 0;

void setup()
{
  mGSM.begin(9600);   
  pinMode(Relay, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  Serial.begin(9600);
  mahdhi.attach(8);
  mahdhi.write(pos);
  Serial.println("GSM SIM900A BEGIN:");
  Serial.println("Characters for controlling:");
  Serial.println("h: to disconnect a call");
  Serial.println("i: to receive a call");
  Serial.println("s: to send message");
  Serial.println("c: to make a call");
  Serial.println("e: to redial");  
  delay(100);
}

void loop()
{
  m = analogRead(A0);
  Serial.println(m);
  n = analogRead(A1);
  Serial.println(n);
  if(m >= 650)
  {
    mahdhi.write(45);
    pos = 45;
    digitalWrite(Relay, LOW);
    if(check == 0)
    {
      SendMessage();
      check = 1;
      delay(1000);
    }
    Serial.println(m);
    delay(5000);
  }
  else if(m <= 649 && n <= 649)
  {
    digitalWrite(Relay, HIGH);
    Serial.println(m);
  }
  else if(m <= 649 && n >= 650)
  {
    digitalWrite(Relay, LOW);
    if(check == 0)
    {
      SendMessage();
      check = 1;
      delay(1000);
    }
    Serial.println(m);
  }
  
  if(n >= 650)
  {
    mahdhi.write(135);
    pos = 135;
    digitalWrite(Relay, LOW);
    if(check == 0)
    {
      SendMessage();
      check = 1;
      delay(1000);
    }
    Serial.println(n);
    delay(5000);
  }
  else if(n <= 649 && m <= 649)
  {
    digitalWrite(Relay, HIGH);
    Serial.println(n);
  }
  else if(n <= 649 && m>= 650)
  {
    digitalWrite(Relay, LOW);
    if(check == 0)
    {
      SendMessage();
      check = 1;
      delay(1000);
    }
    Serial.println(n);
  }
}

void SendMessage()
{
  mGSM.println("AT+CMGF=1");
  delay(1000);
  mGSM.println("AT+CMGS=\"+8801571211893\"\r");
  delay(1000);
  mGSM.println("Pump on");
  delay(100);
  mGSM.println((char)26);
  delay(1000);      
}

void ReceiveMessage()
{
  mGSM.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mGSM.available()>0)
  {
    msg=mGSM.read();
    Serial.print(msg);
  }
}
