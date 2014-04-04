#include <Arduino.h>
#include <TinyGPS.h>
#include <LCD5110_Graph.h>

TinyGPS gps;
LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t TinyFont[];
char dataku[10];

void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(TinyFont);
  Serial.begin(4800);
}


void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    myGLCD.print("Longitude",1,0);  dtostrf(flon, 3, 6, dataku); myGLCD.print(dataku,40,0);
    myGLCD.print("Latitude",1,10); dtostrf(flat, 3, 6, dataku); myGLCD.print(dataku,40,10);
    myGLCD.print("Speed(Kmh)",1,20); dtostrf(gps.f_speed_kmph(), 3, 2, dataku); myGLCD.print(dataku,45,20);
    myGLCD.print("Altitude(m)",1,30); dtostrf(gps.f_altitude(), 3, 2, dataku); myGLCD.print(dataku,46,30);
    myGLCD.print("GPS Receiver",1,40);
    myGLCD.update();
  }
    gps.stats(&chars, &sentences, &failed);
  if (chars == 0)
  {

  }
  delay(1000);
}









