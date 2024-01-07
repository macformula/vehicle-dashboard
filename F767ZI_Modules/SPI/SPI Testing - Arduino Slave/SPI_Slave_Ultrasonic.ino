//SPI SLAVE (ARDUINO)
//SPI COMMUNICATION BETWEEN TWO ARDUINO 
//CIRCUIT DIGEST
//Pramoth.T

#include<SPI.h>
#define LEDpin 7

// defines pins numbers
const int trigPin = 5;
const int echoPin = 6;
// defines variables
long duration;
int distance;

volatile boolean received;
volatile byte Slavereceived,Slavesend;

int x = 0;


void setup()

{
  Serial.begin(115200);
  
  pinMode(LEDpin,OUTPUT);                 // Setting pin 7 as OUTPUT

  pinMode(MISO,OUTPUT);                   //Sets MISO as OUTPUT (Have to Send data to Master IN 

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  SPCR |= _BV(SPE);                       //Turn on SPI in Slave Mode
  received = false;

  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  
}

ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPDR;         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
  
}

void loop()
{ 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  if (distance>255)
  {
    distance = 255;
  }
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  
  if(received)                            //Logic to SET LED ON OR OFF depending upon the value received from master
   {
     if(Slavereceived)
     {
      digitalWrite(LEDpin,HIGH);         //Sets pin 7 as HIGH LED ON
     }
      
  Slavesend = distance;                             
  SPDR = Slavesend;                           //Sends the x value to master via SPDR 
  delay(10);
}
}
