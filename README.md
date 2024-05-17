This was a project I put together to test my knowledge in various arduino programs and acts like a small-scale version for a real climate control project. I used a DHT11, DC Motor, 3 buttons, an I2C LCD, and an LED to act as a heater since I don't own a real heater.

The ports go as the following, though you could likely figure out by looking at the code:
**LED**
Pin 6 and GND
**DHT11**
Pin 2, GND, and 5V
**I2C LCD**
SCL -> A5
SDA -> A4
GND and 5V
**DC MOTOR**
A -> 11
B -> 10
GND and VIN
**COOLING BUTTON**
13, GND, and 5V
**HEATING BUTTON**
12, GND, and 5V
**MODE CHANGE BUTTON**
4, GND, and 5V
