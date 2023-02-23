// C++ code
#include <Servo.h>
Servo Servo1;
#define sensorPin A0
#define servoPin 7
#define ledPin 13
#define buttonPin 2
bool ledState = false;
bool pressed = false;
void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    digitalWrite(ledPin, LOW);
    Servo1.attach(servoPin);
    pressed = digitalRead(buttonPin);
    attachInterrupt(0, buttonTrigger, FALLING);
}
void loop()
{
    int reading = analogRead(sensorPin);       // read the analog value
    float voltage = reading * (5.0 / 1024.0);  // converting to voltage
    float temperature = (voltage - 0.5) * 100; // convert to Celcius
    int value = map(temperature, 0, 100, 0, 180);
    // Printing to serial monitor
    Serial.print("LEDstate:");
    Serial.print(pressed);
    Serial.print(", Temp: ");
    Serial.print(temperature);
    Serial.print(", LED: ");
    Serial.println(ledState);
    // led turns on if temperature is higher than 29
    if (temperature > 0 && temperature < 100)
    {
        Servo1.write(value);
    }
    else if (temperature < 0)
    {
        Servo1.write(0);
    }
    else if (temperature > 100)
    {
        Servo1.write(180);
    }
    digitalWrite(ledPin, pressed);
    delay(50); // delay for stability
}
void buttonTrigger()
{
    pressed = !pressed;
}
