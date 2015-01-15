//Project and code created by Cody Knutson  
    
#include <Wire.h> //I2C library
#include <LowPower.h> //Arduino sleep library https://github.com/rocketscream/Low-Power

byte fetch_humidity_temperature(unsigned int *p_Humidity, unsigned int *p_Temperature);
void print_float(float f, int num_digits);

#define TRUE 1   //Lowpower.h commands
#define FALSE 0 
#define XBEE_SLEEP_PIN 9
#define XBEE_DELAY 40
#define SLEEP_INTERVAL SLEEP_8S

void setup(void)
{  
   Serial.begin(9600); //Everything at 9600
   
   Wire.begin(); //starts the i2c communication
   
   pinMode(4, OUTPUT);
   digitalWrite(4, HIGH); // this turns on the HIH3610
   
   delay(1000); //allowing things to boot/warm up
}
    
    
void loop(void)
{
   byte _status;
   unsigned int H_dat, T_dat;
   float RH, T_C;
   
   while(1) 
   {
      _status = fetch_humidity_temperature(&H_dat, &T_dat);
      
         
    
      RH = (float) H_dat * 6.10e-3;
      T_C = (float) T_dat * 1.007e-2 - 40.0;
      
      xbeeWake(); //wakes up xbee

      Serial.print("Humidity:   "); //sending sensor info to reciever over serial
      print_float(RH, 1);           //characters are spaced for good apearence on a 16x2 lcd display
      Serial.print("Temp:      ");
      print_float(T_C * 9 / 5 + 32, 2);
   
      xbeeSleep(); //sleeps the xbee
      
      LowPower.powerDown(SLEEP_INTERVAL, ADC_OFF, BOD_OFF); //sleeps the arduino fio for 8 seconds
   }
}



byte fetch_humidity_temperature(unsigned int *p_H_dat, unsigned int *p_T_dat)
{
      byte address, Hum_H, Hum_L, Temp_H, Temp_L, _status;
      unsigned int H_dat, T_dat;
      address = 0x27;;
      Wire.beginTransmission(address); 
      Wire.endTransmission();
      delay(100);
      
      Wire.requestFrom((int)address, (int) 4);
      Hum_H = Wire.read();
      Hum_L = Wire.read();
      Temp_H = Wire.read();
      Temp_L = Wire.read();
      Wire.endTransmission();
      
      _status = (Hum_H >> 6) & 0x03;
      Hum_H = Hum_H & 0x3f;
      H_dat = (((unsigned int)Hum_H) << 8) | Hum_L;
      T_dat = (((unsigned int)Temp_H) << 8) | Temp_L;
      T_dat = T_dat / 4;
      *p_H_dat = H_dat;
      *p_T_dat = T_dat;
      return(_status);
}
   
void print_float(float f, int num_digits)
{
    int f_int;
    int pows_of_ten[4] = {1, 10, 100, 1000};
    int multiplier, whole, fract, d, n;

    multiplier = pows_of_ten[num_digits];
    if (f < 0.0)
    {
        f = -f;
        Serial.print("-");
    }
    whole = (int) f;
    fract = (int) (multiplier * (f - (float)whole));

    Serial.print(whole);
    Serial.print(".");

    for (n=num_digits-1; n>=0; n--) // print each digit with no leading zero suppression
    {
         d = fract / pows_of_ten[n];
         Serial.print(d);
         fract = fract % pows_of_ten[n];
    }
}      

void xbeeSleep() 
{
    delay(XBEE_DELAY);
    digitalWrite(XBEE_SLEEP_PIN, HIGH); //xbee sleeps when it senses pin 9 as high
}

void xbeeWake() 
{
    digitalWrite(XBEE_SLEEP_PIN, LOW); //xbee wakes when it senses pin 9 as low
    delay(XBEE_DELAY);
}
