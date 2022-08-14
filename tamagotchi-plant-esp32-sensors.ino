//Libraries
#include <DHTStable.h>
#include <BH1750.h>
#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>

// Pin declarations
const byte TEST_LED = 2;
const byte DHT22_PIN = 27;
const byte SOIL_MOISTURE_PIN = 13;

// Object declarations
DHTStable DHT;
BH1750 lightMeter;
TFT_eSPI tft = TFT_eSPI(); 

void takeMeasurement(){
  DHT.read22(DHT22_PIN);
  float hum = DHT.getHumidity();
  float temp = DHT.getTemperature();
  float light = lightMeter.readLightLevel();
  int soilRead = analogRead(SOIL_MOISTURE_PIN);
  float soilMoisture = map(soilRead, 0, 4095, 100, 0);
  Serial.println("Humedad: " + String(soilMoisture) + "%\t\t" + String(soilRead));
  Serial.println("Temperatura: " + String(temp) + "°C\t\tHumedad: " + String(hum) + "%\t\tLuminosidad: " + String(light) + "lx");
  
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 40);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.println("Temperatura: " + String(temp) + "°C");
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.println("Humedad aire: " + String(hum) + "%");
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.println("Luminosidad: " + String(light) + "lx");
  
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  tft.println("Humedad tierra: " + String(soilMoisture) + "%");
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

  //Init screen
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);
  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 40);
  // Set the font colour to be white with a black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // We can now plot text on screen using the "print" class
  tft.println("Hola mundo :)\n");
}

void loop() {
  delay(2500);
  takeMeasurement();
}
