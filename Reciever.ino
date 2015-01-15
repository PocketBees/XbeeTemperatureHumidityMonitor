#include <SoftwareSerial.h> //display library

SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)


void setup() 
{
Serial.begin(9600); //initializing serial COMs
Serial.println("Ready!");
mySerial.begin(9600); 
splashScreen(); //Displays "Bee Sensor" on startup
screenClear();  //Clears the LCD screen
}



void loop()
{

 while (Serial.available() > 0) //if there's serial data coming into the serial lines from the Xbee 
 
 {
  
   mySerial.print((char)Serial.read()); //then it will be printed to the LCD screen
   
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





