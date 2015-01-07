#include <SoftwareSerial.h> //display library

SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)


void setup() 
{
Serial.begin(9600);
Serial.println("Ready!");
mySerial.begin(9600); 
splashScreen(); //Displays "Bee Sensor" on startup
screenClear();
}



void loop()
{

 
  
 while (Serial.available() > 0)
 {
   mySerial.print((char)Serial.read());
 }
}




void splashScreen() //quick "bee sensor" splash screen intro
{
    mySerial.print("                "); // clear display
    mySerial.print("                ");
    mySerial.write(254); // move cursor to beginning of first line
    mySerial.write(128);
    mySerial.print("   Bee ");
    mySerial.print("Sensor   ");
    delay(2000);
delay(1000);
}

void screenClear () //clears lcd screen
{
  mySerial.print("                "); // clear display
  mySerial.print("                ");
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);
}





