#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

DHT dht;
LiquidCrystal_I2C lcd(0x27, 16, 2);
String status = "Off";
int humidity = 0;
int relay = 13;

void setup()
{
  Serial.begin(9600);
  //*------------ตั้งค่าจอ lcd-------------*
  lcd.begin();
  lcd.backlight();
  //*------------กำหนด relay ว่าเป็น output-------------*
  pinMode(relay, OUTPUT);
  //*------------สั่ง relay ให้หยุดการทำงาน-------------*
  digitalWrite(relay, LOW);
  //*------------ตั้งค่าจอ lcd แสดงผล-------------*
  lcd.setCursor(5, 0); 
  lcd.print("Setting ");
  lcd.setCursor(4, 1); 
  lcd.print("the Sensor"); 
  //*------------บอกหน้าที่ของ dht ว่ามาจาก pin 12-------------*
  dht.setup(12);
  //*------------ตั้งค่าหน่วงเวลา 3 วิ-------------*
  delay(3000);
  //*------------เคลียจอ lcd-------------*
  lcd.clear();
  lcd.setCursor(1, 0); 
  lcd.print("Matchine Start!"); 
  delay(3000);
  lcd.clear();
}
void loop() {
  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  Serial.println(humidity);
  lcd.setCursor(0, 0); 
  lcd.print("Fan Status:" + status); 
  if(humidity >= 50){
    lcd.clear();
    digitalWrite(relay, HIGH);
    status = "On";
  }
  if(humidity < 50){
    lcd.clear();
    digitalWrite(relay, LOW);
    status = "Off";
  }
}


