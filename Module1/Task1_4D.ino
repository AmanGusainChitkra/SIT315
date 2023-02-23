// C++ code

#include <Servo.h>

Servo Servo1;

#define sensorPin A0
#define servoPin 7
#define motionPin 3
#define ledPin 13
#define buttonPin 2
#define motionPin2 8
#define ledPin2 12


bool ledState1 = false;
bool ledState2 = false;
bool pressed = false;



void setup()
{
    Serial.begin(9600);

    pinMode(motionPin, INPUT);
    pinMode(motionPin2, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);


    Servo1.attach(servoPin);
    
    //setting up the interrupt for the new motino sensor
    PCICR |= B00000001; //setting the PCICR register to the Pin Group B

    PCMSK0 |= 1<<PCINT0;    //setting the input pin D8 as interrupt

    attachInterrupt(digitalPinToInterrupt(motionPin), motionTrigger, CHANGE);
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonTrigger, RISING);

    //setting up some initial values
    pressed = digitalRead(buttonPin);
    digitalWrite(ledPin, LOW);
}


void loop()
{
    int reading = analogRead(sensorPin);      // read the analog value
    float voltage = reading * (5.0 / 1024.0); // converting to voltage

    float temperature = (voltage - 0.5) * 100; // convert to Celcius
    int value = map(temperature, 0, 100, 0, 180);

    // Printing to serial monitor
    Serial.print("Motion1: ");
    Serial.print(digitalRead(motionPin));
    Serial.print(", Motion2: ");
    Serial.print(digitalRead(motionPin2));
    Serial.print(", Temp: ");
    Serial.print(temperature);
    Serial.print(", LED: ");
    Serial.print(ledState1);
    Serial.print(", Button: ");
    Serial.println(digitalRead(buttonPin));

    // led turns on if temperature is higher than 29
    if(temperature > 0 && temperature < 100){
        Servo1.write(value);
    } else if(temperature < 0){
        Servo1.write(0);
    } else if(temperature > 100){
        Servo1.write(180);
    }

  if(pressed){      //resets the servo for a brief moment after the button is pressed
    Servo1.write(0);
    pressed = false;
    delay(500);
  }
  
    delay(50); // delay for stability
}

ISR (PCINT0_vect){  //this function us triggered after interrupt through pin D8
    ledState2 = !ledState2;
    digitalWrite(ledPin2, ledState2);
}

void motionTrigger(){
    ledState1 = !ledState1;
    digitalWrite(ledPin, ledState1);
}

void buttonTrigger(){
    pressed = true;
}
