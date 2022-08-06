#include <Wire.h>
#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11); //SIM800L Tx & Rx is connected to Arduino #10 & #11



String number1 = "+94xxxxxxxxx"; // +94 is the country code & add Emergency Department number
String number2 = "+94xxxxxxxxx"; // +94 is the country code & add fire Emergency Department number
int pirsensor = 6; // PIR is connected with the digital pin 6 of the Arduino
int ldrsensor = A1; // LDR is connected with the analog pin A1 of the Arduino
int flame = 7; //flame sensor is connected with the digital pin 7 of the Arduino
int data = 0;
int Motions = 8; //LED attach digital pin 8
int fire =9; //LED attach digital pin 9
void setup() {
  Serial.begin(9600);
  Serial.println("Wait few seconds...");
  delay(5000);
  Serial.println("System Started..");
  sim.begin(9600);
  delay(1000);
  pinMode(pirsensor, INPUT);
  pinMode(ldrsensor, INPUT);
  pinMode(flame, INPUT);
  pinMode(Motions, OUTPUT);
   pinMode(fire, OUTPUT);
  delay(1000);
}

void loop() {

  data = analogRead(ldrsensor);
  Serial.println(data);


  if ( digitalRead(flame) == LOW)
  {
    Serial.println("sending sms");

    digitalWrite(fire, HIGH);
    


    // send a message to the Emergency Department.
    SendMessage2();
    Serial.println("message sent.");
    delay(15000);

     digitalWrite(fire, LOW);

  }

  else if ( data < 120)  // changing value "120" using Serial moniter data 
  {

    if ( digitalRead(pirsensor) == HIGH)
    {
      Serial.println("sending sms");

    digitalWrite(Motions, HIGH);

      // send a message to the Emergency Department.
      SendMessage1();
      Serial.println("message sent.");
      delay(30000);

     
    }
    if (sim.available() > 0)
      Serial.write(sim.read());
      
  }
  
 digitalWrite(Motions, LOW);
}

void SendMessage1()
{
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number1 + "\"\r");
  delay(1000);
  String SMS = "Detected Presence of Movement";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(1000);
}

void SendMessage2()
{
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number2 + "\"\r");
  delay(1000);
  String SMS = "Detected flame";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(1000);
}
