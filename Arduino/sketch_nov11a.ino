#include <LiquidCrystal.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7

int sensorValue;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
 
const int buzzerPin = 8;
const int ledPin1 = 6;
const int ledPin2 = 13;
const int fotoresistor = 1;
int lightCal;
int lightVal;
 
int counter = 0;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(){  lcd.begin(16, 2);
Serial.begin(9600);   // sets the serial port to 9600
pinMode(buzzerPin, OUTPUT);
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
 lightCal = analogRead(fotoresistor);
 sensors.begin(); 
 
 }


 
void loop(){
  // FOTOREZISTORUL
lightVal = analogRead(fotoresistor);
if (lightVal < lightCal - 50)
{
  // citirea se face la 2 ore
  lcd.setCursor(0,1);
  lcd.print("Noapte");
  delay(100); 
}
else{
  //citirea se face la 15 minute
  sensors.requestTemperatures();
  sensorValue = analogRead(0);       // read analog input pin 0 AIR QUALITY
Serial.print("AirQua=");
Serial.print(sensorValue, DEC);               // prints the value read
Serial.println(" PPM");
lcd.setCursor(0,1);
lcd.print("Zi;     ");
lcd.setCursor(0,0);
lcd.print(sensorValue,DEC);
lcd.print("PPM, ");
lcd.println(int(sensors.getTempCByIndex(0))); 

if (sensorValue <400){
  //tone(buzzerPin, 500,500); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
 digitalWrite(6,HIGH);
 digitalWrite(13, LOW);
 delay(1000);
 //delay(7200000); //delay de 2 ore
  }
else {
 tone(buzzerPin, 1000,500); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
 digitalWrite(6, LOW);
 digitalWrite(13, HIGH);
 delay(1000);
  }

  delay(100); // wait 100ms for next reading pe asta il pui in if cu conditie lumina/intuneric si il modifici la fie la 15 minute fie la 2 ore
//delay(900000); //delay de 15 minute
}

// FRANA FOTOREZISTOR
  
  
                                   
}
void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 20); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
}
