#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);
int motor=10;
int sensorpin=A0;
int moisture;
int percentage;
int map_low=1023;
int map_high=200;

void setup() 
{
  pinMode(sensorpin,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(motor,OUTPUT);
}

void loop() 
{
  moisture=analogRead(sensorpin);

  lcd.setCursor(0,0);
  lcd.print("RV:");
  lcd.setCursor(4,0);
  lcd.print(moisture);

  percentage=map(moisture,map_low,map_high,0,100);

  lcd.setCursor(0,1);
  lcd.print("Per:");
  lcd.print(percentage);
  lcd.print("%");

 
  delay(1000);
  lcd.clear();
  while(percentage>=0 && percentage<50)
  {
    
   motoron();

  }

}  



void motoron()
{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Motor On");
  delay(1000);
  while(percentage <=70)
  {
    
    digitalWrite(motor,HIGH);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Motor on");
    lcd.setCursor(0,1);
    lcd.print("PER:");
    lcd.print(percentage);    
    delay(500);
    moisture=analogRead(sensorpin);
    percentage=map(moisture,map_low,map_high,0,100);
  }
    digitalWrite(motor,LOW);
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Motor OFF");    
    delay(1000);
  

}
