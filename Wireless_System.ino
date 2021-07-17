#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
SoftwareSerial GPRS(9, 10);
String textMessage;
int currentRate = 13.0;
const int Buzzer = 9;    // Alarm connected to digital pin 9
const int highestPin = 13;
const int sensorRead = A2;
int resistance = 100;
double voltage = 0;
double Vrms = 0;
const int relay = 8;  // this pin is connected to the relay
const int LDR = A0;
int LDRR;
int LDRR1;

void setup() {
  Serial.begin(9600);
  GPRS.begin(9600);
Serial.print("GPRS ready...\r\n");
GPRS.print("AT+CMGF=1\r\n");
delay(1000);
GPRS.print("AT+CNMI=2,2,0,0,0\r\n");
delay(1000);
   lcd.init();                      // initialize the lcd 
  lcd.init();
  lcd.backlight();
  pinMode(relay,OUTPUT);
  // for (int thisPin = lowestPin; thisPin <= highestPin; thisPin++) {//this code is for the alarm, it has been modified but not tested
    digitalWrite(relay,HIGH);
    noTone(Buzzer);  
}

void loop() {
  if(GPRS.available()>0){
textMessage = GPRS.readString();
Serial.print(textMessage);
delay(10);
}
  LDRR = analogRead(LDR);
  int LDRR1 = map(LDRR,0,1023,0,100);
  Serial.println(LDRR1);
  digitalWrite(relay,LOW);
  voltage = peak_to_peak();
  Vrms = (voltage/2.0)*0.7071;
  double Irms = (Vrms*1000)/resistance;
  Irms -= 0.17;
  lcd.setCursor(0,0);
  lcd.print("Detected Current: ");
  lcd.setCursor(0,1);
  lcd.print(Irms);
  lcd.print(" A");
  if (Irms<0.09){
    AC();
    
  }
 if (LDRR1<50){
     LD();
  }
}

float peak_to_peak()
{
  float peak;
  int sensorValue;
  int maxPeak = 0; //maximum peak is stored here
  int minPeak = 1024; // minimum peak is stored here
  uint32_t begin_time = millis();
  while(millis() - begin_time <1000)
  {
    sensorValue = analogRead(sensorRead);
    if(sensorValue > maxPeak){
      maxPeak =sensorValue;
    }
    if(sensorValue < minPeak){
      minPeak =sensorValue;
    }
  }
  peak =((maxPeak-minPeak)*5.0)/1024.0;
  return peak;
  
}
void LD(){
  lcd.clear();
  int ld = 1;
  while(ld = 1){
   LDRR = analogRead(LDR);
  LDRR1 = map(LDRR,0,1023,0,100);
  Serial.println(LDRR1);
  digitalWrite(relay,LOW);
  voltage = peak_to_peak();
  Vrms = (voltage/2.0)*0.7071;
  double Irms = (Vrms*1000)/resistance;
  Irms -= 0.17;
lcd.setCursor(0,1);
Serial.println ("Light Damaged");
lcd.print("Light Damaged");
textMessage = "";
GPRS.println("AT+CMGS=\"+233548330366\"");
delay(500);
GPRS.print("Bulb is OFF: bulb is damaged. System requires the replacement of bulb\r");
GPRS.write(0x1a);
delay(1000);
LD1();
  }
  
}
void AC(){
  lcd.clear();
  int ld = 1;
  while(ld = 1){
   LDRR = analogRead(LDR);
  LDRR1 = map(LDRR,0,1023,0,100);
  Serial.println(LDRR1);
  digitalWrite(relay,LOW);
  voltage = peak_to_peak();
  Vrms = (voltage/2.0)*0.7071;
  double Irms = (Vrms*1000)/resistance;
  Irms -= 0.17;
lcd.setCursor(0,1);
Serial.println ("Light Damaged");
lcd.print("Faulty AC Supply");
textMessage = "";
GPRS.println("AT+CMGS=\"+233548330366\"");
delay(500);
GPRS.print("Bulb OFF: Power is disconnected. Maintenance required on power supply \r");
GPRS.write(0x1a);
delay(1000);
 AC1();
  }
  
}
void AC1(){
  lcd.clear();
  int ld = 1;
  while(ld = 1){
   LDRR = analogRead(LDR);
  LDRR1 = map(LDRR,0,1023,0,100);
  Serial.println(LDRR1);
  digitalWrite(relay,LOW);
  voltage = peak_to_peak();
  Vrms = (voltage/2.0)*0.7071;
  double Irms = (Vrms*1000)/resistance;
  Irms -= 0.17;
lcd.setCursor(0,1);
Serial.println ("Light Damaged");
lcd.print("Faulty AC Supply");
if (Irms>=0.06){
    lcd.clear();
    loop();
  }
  }
  
}
void LD1(){
  lcd.clear();
  int ld = 1;
  while(ld = 1){
   LDRR = analogRead(LDR);
  LDRR1 = map(LDRR,0,1023,0,100);
  Serial.println(LDRR1);
  digitalWrite(relay,LOW);
  voltage = peak_to_peak();
  Vrms = (voltage/2.0)*0.7071;
  double Irms = (Vrms*1000)/resistance;
  Irms -= 0.17;
lcd.setCursor(0,1);
Serial.println ("Light Damaged");
lcd.print("Light Damaged");
if (LDRR1>=50){
    lcd.clear();
    loop();
  }
  }
  
}

