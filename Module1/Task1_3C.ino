// C++ code
#include <Servo.h>
Servo Servo1;
#define sensorPin A0
#define servoPin 7
#define motionPin 3
#define ledPin 13
#define buttonPin 2
bool ledState = false;
bool sensed = false;
bool pressed = false;
void setup()
{
    Serial.begin(9600);
    pinMode(motionPin, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    digitalWrite(ledPin, LOW);
    Servo1.attach(servoPin);
    pressed = digitalRead(buttonPin);
    sensed = digitalRead(motionPin);
    attachInterrupt(digitalPinToInterrupt(motionPin), motionTrigger, CHANGE);
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonTrigger, RISING);
}
void loop()
{
    int reading = analogRead(sensorPin);       // read the analog value
    float voltage = reading * (5.0 / 1024.0);  // converting to voltage
    float temperature = (voltage - 0.5) * 100; // convert to Celcius
    int value = map(temperature, 0, 100, 0, 180);
    // Printing to serial monitor
    Serial.print("Motion: ");
    Serial.print(digitalRead(motionPin));
    Serial.print(", Temp: ");
    Serial.print(temperature);
    Serial.print(", LED: ");
    Serial.print(ledState);
    Serial.print(", BUtton: ");
    Serial.println(digitalRead(buttonPin));
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
    if (pressed)
    {
        ledState = !ledState;
        pressed = false;
    }
    if (sensed)
    {
        ledState = !ledState;
        sensed = false;
    }
    digitalWrite(ledPin, ledState);
    delay(50); // delay for stability
}
void motionTrigger()
{
    sensed = true;
}
void buttonTrigger()
{
    pressed = true;
}
