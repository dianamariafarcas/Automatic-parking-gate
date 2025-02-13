#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <NewPing.h>

#define trigPin 6
#define echoPin 7
#define LED_PIN_G 3
#define LED_PIN_R 2 

Servo myservo;   
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

int pos = 0;
int cm = 0;
int numarMasini = 0;

int distanceUltra()
{
  float distance=0;
  int duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  return distance;
}
void setup() {
  Serial.begin(9600); ///initializeaza comunicarea 
  myservo.attach(9); ///servo attached to the pin 9
  myservo.write(0);
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2, 0);
  lcd.print("Parcare"); 
  lcd.setCursor(2,1);
  lcd.print("disponibila");

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  pinMode(LED_PIN_G, OUTPUT);
  pinMode(LED_PIN_R, OUTPUT);

  digitalWrite(LED_PIN_G, HIGH);  // Inițial, LED-ul verde este aprins
  delay(500);
}

void loop() {
  cm =distanceUltra();
  
  delay(1000);


  if (cm < 5) {
    Serial.print(cm);
    Serial.println("cm");

    for (pos = 0; pos <= 120; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    delay(500);

    for (pos = 120; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    delay(15);
    
    numarMasini++;

    // Actualizare LED-uri și mesaj pe LCD în funcție de numărul de mașini
    if (numarMasini < 3) {
      digitalWrite(LED_PIN_G, HIGH);  // LED verde aprins
      delay(500);
      digitalWrite(LED_PIN_R, LOW);    // LED roșu stins
      delay(500);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Parcare"); 
      lcd.setCursor(2,1);
      lcd.print("disponibila");

    } else {
      digitalWrite(LED_PIN_G, LOW);    // LED verde stins
      delay(500);
      digitalWrite(LED_PIN_R, HIGH);    // LED roșu aprins
      delay(500);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Parcare"); 
      lcd.setCursor(2,1);
      lcd.print("plina");
      myservo.attach(0);
    }
    Serial.println(numarMasini);
    delay(1000);
  }
}