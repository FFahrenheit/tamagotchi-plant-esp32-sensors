//Libraries
#include <DHTStable.h>
#include <BH1750.h>
#include <Wire.h>

// Pin declarations
const byte TEST_LED = 2;
const byte DHT22_PIN = 15;
const byte SOIL_MOISTURE_PIN = 13;

// Object declarations
DHTStable DHT;
BH1750 lightMeter;

void takeMeasurement(){
  DHT.read22(DHT22_PIN);
  float hum = DHT.getHumidity();
  float temp = DHT.getTemperature();
  float light = lightMeter.readLightLevel();
  int soilRead = analogRead(SOIL_MOISTURE_PIN);
  float soilMoisture = map(soilRead, 0, 4095, 100, 0);
  Serial.println("Humedad: " + String(soilMoisture) + "%\t\t" + String(soilRead));
  //Serial.println("Temperatura: " + String(temp) + "°C\t\tHumedad: " + String(hum) + "%\t\tLuminosidad: " + String(light) + "lx");
}

void setup() {
  // Pin modes
  pinMode(TEST_LED, OUTPUT);
  digitalWrite(TEST_LED, LOW);
  
  // Init Serial port
  Serial.begin(115200);
  Serial.println("Init...");

  // Init I2C
  Wire.begin();

  //Init light meter
  while(!lightMeter.begin()){
    Serial.println("Error on BH1750 init...");
    digitalWrite(TEST_LED, HIGH);
    delay(500);
    digitalWrite(TEST_LED, LOW);
    delay(500);
  }
}

void loop() {
  delay(2500);
  takeMeasurement();
}
