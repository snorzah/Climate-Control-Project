// AUTHOR: SNORZAH
// Import Libraries
#include <LiquidCrystal_I2C.h>
#include <Adeept_DHT11.h>
#include <Wire.h>
// Setup w/ Variables
// DHT11
Adeept_DHT11 Adeept_dht11;
#define DHT11PIN 2 // DHT pin connected to pin 2
int tempThreshold = 27; // Set the ideal temperature to 27 degrees Celsius. Can be changed later

// DC Motor
int APin = 11; // DC motor A pin connected to pin 11
int BPin = 10; // DC motor B pin connected to pin 10
int DCmotorspeed = 200; // Speed of DC Motor is 200/255

// Heater
int heaterPin = 6; // Heater pin connected to pin 6

// Buttons
int HbtnPin = 12; // Button to increase Temperature connected to pin 13
int CbtnPin = 13; // Button to decrease Temperature connected to pin 12
int sChangeBtn = 4; // Button to change mode from Heating and Cooling connected to pin 4
volatile int state = LOW;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set LCD address to 0x27 with 16 columns and 2 rows

// Setting up for all the devices and Serial Monitor
void setup()
{ 
     
     // Setup for DC Motor
     pinMode(APin,OUTPUT);
     pinMode(BPin,OUTPUT);
     
     // Setup for Heater 
     pinMode(heaterPin, OUTPUT);
     
     // Setup for Buttons
     pinMode(HbtnPin, INPUT);
     pinMode(CbtnPin, INPUT);
     
     // Serial Begin
     Serial.begin(9600);

     // LCD Setup
     lcd.init();
     lcd.backlight();
     lcd.noBlink();
     lcd.setCursor(0,0);
}
void loop()
{
    // Read the DHT11 and set the temperature to the variable temp
    Adeept_dht11.read(DHT11PIN);
    int temp = Adeept_dht11.temperature;
    
    // Detect for Button Presses and add/subtract from the temperature threshold if respective button is pressed
    if(digitalRead(HbtnPin)==LOW){
      delay(20);
      if(digitalRead(HbtnPin)==LOW){
        delay(20);
        if(digitalRead(HbtnPin)==LOW){
          tempThreshold++;
        }
      }
    }
    if(digitalRead(CbtnPin)==LOW){
        delay(20);
        if(digitalRead(CbtnPin)==LOW){
          delay(20);
          if(digitalRead(CbtnPin)==LOW){
            tempThreshold--;
          }
        }
      }
      // Change state based on whether the setting change button (sChangeBtn) was pressed
      if(digitalRead(sChangeBtn)==LOW){
        delay(20);
        if(digitalRead(sChangeBtn)==LOW){
          delay(20);
          if(digitalRead(sChangeBtn)==LOW){
            state = !state;
            
          }
        }
      }
      // If State is set low, then set it to cold and vice versa
      if (state == LOW){
        // if it's too hot, turn on the fan
          if(temp>tempThreshold){
            analogWrite(APin, DCmotorspeed);
          } else {
            analogWrite(APin, 0);
          }
      }
      if (state == HIGH){
        // if it's too cold, turn on the heater
          if(temp<tempThreshold){
            digitalWrite(heaterPin, HIGH);
          } else {
            digitalWrite(heaterPin, LOW);
          }
      }
      
      // Print info on LCD Display
      lcd.print("Room:" + String(temp) + "C");
      lcd.setCursor(0,1);
      lcd.print("Ideal:" + String(tempThreshold) + "C");
      lcd.setCursor(12,1);
      
      // Display State based on whether its hot or cold
      if (state == LOW){
        lcd.print("COLD");
        Serial.println(state);
      }
      if (state == HIGH){
        lcd.print("HOT ");
        Serial.println(state);
      }
      // Reset the LCD cursor
      lcd.setCursor(0, 0);
}
