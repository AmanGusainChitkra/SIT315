// C++ code
//
#define sensorPin A0
const int ledPin = 8;
bool ledState = false;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); 
}

void loop()
{
  int reading = analogRead(sensorPin); //read the analog value         
  float voltage = reading * (5.0 / 1024.0);//converting to voltage

  float temperature = (voltage - 0.5) * 100;//convert to Celcius
  
  //Printing to serial monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(", LED: ");
  Serial.println(ledState);
  
  //led turns on if temperature is higher than 29
  if(temperature > 29){
    digitalWrite(ledPin, HIGH);
    ledState = true;} 
  else {
    digitalWrite(ledPin, LOW);
    ledState = false;}
  
  delay(50);  //delay for stability

}