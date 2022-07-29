#define BRIGHTNESS_LIMIT 500
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 7     // 디지털 7번핀 사용
#define DHTTYPE DHT11   // DHT 11 모델사용 (DHT21/22 사용 가능)
LiquidCrystal_I2C lcd(0x27,16,2); //LCD 설정 (I2C주소는 LCD의 종류에 따라 다르기때문에 LCD가 0x3F, 0x20, 0x27인지 확인)
DHT dht(DHTPIN, DHTTYPE);
float di;
 
void setup()
{
  lcd.init();
  Serial.begin(9600);
  dht.begin();
  pinMode(2, OUTPUT);
}
 
void loop() {
  
  int brightness = analogRead(A0);
  Serial.println(brightness);  
  float h = dht.readHumidity(); // 습도 측정
  float t = dht.readTemperature(); // 섭씨 온도 측정
   
  lcd.backlight();
  lcd.display();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t,1);
  lcd.print(char(223));
  lcd.print("C");
  delay(100);
  lcd.setCursor(9,0);
  lcd.print("H:");
  lcd.print(h,1);
  lcd.print("%");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("DI:");
  lcd.print(di,1);

  di = 1.8*t-0.55*(1-h/100)*(1.8*t-26)+32;
 
  Serial.print("습도: ");
  Serial.print(h);
  Serial.print(" 온도: ");
  Serial.print(t);
  Serial.print("불쾌지수: ");
  Serial.print(di);
  Serial.println();
  if ( di < 68.0 ){
    Serial.print("좋음");
    Serial.println("");
    if ( brightness < BRIGHTNESS_LIMIT ) // 조도가 높을때 불투명
    {
      digitalWrite(2, HIGH);
    }
    else
    {
      digitalWrite(2, LOW);
    }
  }
  else if ( di > 68.0 && di < 75.0 ){
    Serial.print("보통");.

    Serial.println("");
    if ( brightness < BRIGHTNESS_LIMIT ) // 조도가 높을때 불투명
    {
      digitalWrite(2, HIGH);
    }
    else
    {
      digitalWrite(2, LOW);
    }
  }
  else {
    Serial.print("나쁨");
    Serial.println("");
    if ( brightness < BRIGHTNESS_LIMIT ) // 조도가 높을때 불투명
    {
      if ( h > 30 ){
        digitalWrite(2, LOW);
      }
      else {
        digitalWrite(2, HIGH);
      }
    }
    else
    {
      digitalWrite(2, LOW);
    }
  }
  delay(2000); //10초마다 Refresh
  lcd.clear();
}
