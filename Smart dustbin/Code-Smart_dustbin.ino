#include <ESP8266WiFi.h>
#include <HCSR04.h>

#include <LiquidCrystal_I2C.h>
#include <CayenneMQTTESP8266.h>

LiquidCrystal_I2C lcd(0x27,16,2);

//Giving the details of my wifi to connect.
char ssid[] = "Bottle Cap"; // your SSID
char password[]="vvnarendra_10";  // your password

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "13504de0-2b63-11ed-baf6-35fab7fd0ac8";
char mqtt_password[] = "eb10ac31d0a629e8424435436bd2ca42a39a03c5";
char client_id[] = "044ae3e0-3c3a-11ed-bf0a-bb4ba43bd3f6";

#define MAX_HEIGHT 20 // your bin height
int Percentage;

UltraSonicDistanceSensor distanceSensor(D5,D6);  //D1 trig, D2=ech

void setup(void)
{
  Serial.begin(115200);
   Cayenne.begin(username,mqtt_password,client_id,ssid,password);// starting cayenne 
  delay(1000);
  lcd.init();                      
  // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
}


void loop()
{
     Cayenne.loop();
    float actualCM=1*distanceSensor.measureDistanceCm();    
   // Serial.println(actualCM); 
    Percentage=(MAX_HEIGHT-actualCM)/(MAX_HEIGHT-5)*100  ;
    Serial.println(Percentage);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" IOT Smart BIN  ");
    lcd.setCursor(0,1);
    lcd.print("Waste Fill:");
    lcd.setCursor(11,1);
    lcd.print(Percentage);
    lcd.setCursor(13,1);
    lcd.print(" % ");
    delay(1000);
    Cayenne.virtualWrite(1, Percentage);
    if(Percentage>=100)
      { 
        lcd.setCursor(11,1);
        lcd.print("FULL  ");             
        delay(1000);
      }      
   }
