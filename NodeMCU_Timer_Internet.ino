#include <ESP8266WiFi.h>
#include <time.h>
#include <LiquidCrystal.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int ledPin = 13; //D7
const char* ssid = "benedict";
const char* password = "sitompuls";
int timezone = 7;
int dst = 0;

String HH1 ="23"; //HOUR LED-ON
String MM1 ="20"; //MINUTE LED-ON
String SS1 ="00"; //SECOND LED-ON

String HH2 ="23"; //HOUR LED-OFF
String MM2 ="21"; //MINUTE LED-OFF
String SS2 ="00"; //SECOND LED-OFF





void setup() {
  Wire.begin (D2, D1); //Wire.begin (SDA, SCL);
  lcd.begin();   
  
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(1000);
  }
    
    configTime(timezone * 3600, dst * 0, "pool.ntp.org", "time.nist.gov");
    while (!time(nullptr)) {
    Serial.print(".");
    delay(1000);
    }


  Serial.println("Wait 30' for receiving Inet Time....");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wait 30' receive");

  lcd.setCursor(0,1);
  lcd.print("Internet Time...");
  Serial.print(".");
  delay(30000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PKL ");
  lcd.print(HH1);
  lcd.print(":");
  lcd.print(MM1);
  lcd.print(",LedOn");
  lcd.println("   ");
  
  lcd.setCursor(0,1);
  lcd.print("PKL ");
  lcd.print(HH2);
  lcd.print(":");
  lcd.print(MM2);
  lcd.print(",LedOff");
  lcd.println("   ");
  
  delay(10000); 
}


void loop() {
  time_t now;
  struct tm * timeinfo;
  time(&now);
  timeinfo = localtime(&now);  
  //Serial.println(timeinfo->tm_hour);
  //Serial.println(timeinfo->tm_min);
  //Serial.println(timeinfo->tm_sec);
  
  Serial.print("Local Internet Time = ");
  Serial.print(timeinfo->tm_hour);
  Serial.print(":");
  Serial.print(timeinfo->tm_min);
  Serial.print(":");
  Serial.print(timeinfo->tm_sec);
  Serial.println("              ");

  lcd.clear();
  //Penulisan LCD pada baris 0
  lcd.setCursor(0,0);
  lcd.print("LOCTIME ");
  lcd.print(timeinfo->tm_hour);

  lcd.print(":");
  lcd.print(timeinfo->tm_min);
  lcd.print(":");
  lcd.print(timeinfo->tm_sec);
  lcd.println("   ");

  //Penulisan LCD pada baris 1
  lcd.setCursor(0,1);
  lcd.print(HH1);
  lcd.print(":");
  lcd.print(MM1);

  lcd.print(" >>>> ");
  lcd.print(HH2);
  lcd.print(":");
  lcd.print(MM2);
  delay(1000);//tampil refresh

  // TURN LED ON
  if( (timeinfo->tm_hour == HH1.toInt()) && (timeinfo->tm_min == MM1.toInt())){
      digitalWrite(ledPin,HIGH);
  }


  // TURN LED OFF
  if( (timeinfo->tm_hour == HH2.toInt()) && (timeinfo->tm_min == MM2.toInt())){
      digitalWrite(ledPin,LOW);
  }

  
}
