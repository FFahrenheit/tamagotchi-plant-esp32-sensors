//Libraries
#include <Arduino_JSON.h>
#include <DHTStable.h>
#include <BH1750.h>
#include <Wire.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#include "assets/ok.h";
#include "assets/dashboard.h";
#include "assets/font.h"

void sendData();
void setpointsConfig();
void drawDashboard();

//Client config
String MY_PRIVATE_ID = "1";
String SERVER_ADDRESS = "http://64.227.14.152:3000/api/planta/" + MY_PRIVATE_ID;

// Pin declarations
const byte TEST_LED = 2;
const byte DHT22_PIN = 27;
const byte SOIL_MOISTURE_PIN = 33;

// Object declarations
hw_timer_t * timer = NULL;      // Hardware timer
DHTStable DHT;
BH1750 lightMeter;
TFT_eSPI tft = TFT_eSPI();
WiFiMulti wifiMulti;
WiFiClient wifiClient;


//Global variables
float hum;
float temp;
float light;
float soilMoisture;
bool needsToMeasure = false;

//Set points
double max_hum = 0.0f, min_hum = 0.0f, max_temp = 0.0f, min_temp = 0.0f;

char *redes[2][2] = {
  {"TheCoolestWiFiLM", "LopezMurillo128"},
  {"WifiLM", "LopezMurillo128"}
};

void takeMeasurement(){
  int soilRead = analogRead(SOIL_MOISTURE_PIN);
  DHT.read22(DHT22_PIN);
  hum = DHT.getHumidity();
  temp = DHT.getTemperature();
  light = lightMeter.readLightLevel();
  soilMoisture = map(soilRead, 0, 4095, 100, 0);
  Serial.println("Humedad: " + String(soilMoisture) + "%\t\t" + String(soilRead));
  Serial.println("Temperatura: " + String(temp) + "°C\t\tHumedad: " + String(hum) + "%\t\tLuminosidad: " + String(light) + "lx");

  drawDashboard();
  sendData();
}

void IRAM_ATTR onTimer(){
  needsToMeasure = true;
}

void setup() {
  // Pin modes
  
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  
  pinMode(TEST_LED, OUTPUT);
  digitalWrite(TEST_LED, LOW);
  
  // Init Serial port
  Serial.begin(115200);
  Serial.println("Init...");

  //Init screen
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(&Arimo_Regular_24);
  // Set "cursor" at top left corner of display (0,0) and select font 4
  tft.setCursor(0, 40);
  // Set the font colour to be white with a black background
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  // We can now plot text on screen using the "print" class
  
  //tft.println("Hola mundo :)\n");
  //tft.println("Inicializando...");

  tft.pushImage(OK_OFFSET_X, OK_OFFSET_Y, OK_WIDTH, OK_HEIGHT, OK_SPRITE);
  //drawDashboard();
  delay(2500);

  // Init I2C
  Wire.begin(15, 5);
  //Init light meter
  
  while(! lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2, 0x23, &Wire) ){
    Serial.println("Error on BH1750 init...");
    digitalWrite(TEST_LED, HIGH);
    delay(500);
    digitalWrite(TEST_LED, LOW);
    delay(500);
  }

  //Timer init
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 2500000, true);
  timerAlarmEnable(timer);

  //WiFi Init
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  for(auto red : redes){
    Serial.print("SSID: ");
    Serial.print(red[0]);
    Serial.print("\t\tPassword: ");
    Serial.println(red[1]);

    wifiMulti.addAP(red[0], red[1]);
  }

  Serial.println("Connecting to WiFi...");
  int i = 0;

  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1250);
    Serial.print(++i); Serial.print(' ');
  }
  
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  setpointsConfig();
}

void loop() {
  if(needsToMeasure){
    takeMeasurement();
    needsToMeasure = false;
  }
}

void sendData(){
  HTTPClient http;
  String body = "temperatura=" + String(temp) + "&humedad_ambiente=" + String(hum) + "&luminosidad=" + String(light) + "&humedad_tierra=" + String(soilMoisture);
  Serial.println(body); 

  http.begin(wifiClient, SERVER_ADDRESS);  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.PUT(body);               //Send the request
  Serial.println("Response: " + String(httpCode));


  if (httpCode > 0) { //Check the returning code
 
    String payload = http.getString();   //Get the request response payload
    JSONVar response = JSON.parse(payload);

    if (JSON.typeof(response) != "undefined" && response.hasOwnProperty("title"))
    {
      Serial.println(response["title"]);
    }
    else
    {
      Serial.println(response);
    }
  }
 
  http.end();   //Close connection
}

void setpointsConfig(){
  HTTPClient http;
  http.begin(wifiClient, SERVER_ADDRESS + "/config");  //Specify request destination
  int httpCode;
  
  do{
    httpCode = http.GET();                  //Send the request
    Serial.println("Response: " + String(httpCode));

  if (httpCode > 0) { //Check the returning code
 
    String payload = http.getString();   //Get the request response payload
    JSONVar response = JSON.parse(payload);

    if (JSON.typeof(response) != "undefined" && response.hasOwnProperty("max_temp"))
    {
      max_temp = (double) response["max_temp"];
      min_temp = (double) response["min_temp"];
      max_hum = (double) response["max_hum"];
      min_hum = (double) response["min_hum"];

      Serial.println("Maxima temperatura: " + String(max_temp));
      Serial.println("Minima temperatura: " + String(min_temp));
      Serial.println("Maxima humedad: " + String(max_hum));
      Serial.println("Minima humedad: " + String(min_hum));
    }
    else
    {
      Serial.println(response);
    }
  }
 
  }while(httpCode < 0);
  
  http.end();   //Close connection
}

void drawDashboard(){
  tft.setSwapBytes(true);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);
  
  tft.pushImage(TEMP_OFFSET_X, TEMP_OFFSET_Y, TEMP_WIDTH, TEMP_HEIGHT, TEMP_SPRITE);
  tft.setCursor(20, 90);
  tft.print(String(temp) + "°C");
  
  tft.pushImage(SUN_OFFSET_X, SUN_OFFSET_Y, SUN_WIDTH, SUN_HEIGHT, SUN_SPRITE);
  String luminosidad = String(light);
  int offsetX = (luminosidad.length() - 3) * 10;
  tft.setCursor(160 - offsetX, 90);
  tft.print(luminosidad + "lx");
  
  tft.pushImage(HUM_OFFSET_X, HUM_OFFSET_Y, HUM_WIDTH, HUM_HEIGHT, HUM_SPRITE);
  tft.setCursor(20, 210);
  tft.print(String(hum) + "%");
  
  tft.pushImage(HUMT_OFFSET_X, HUMT_OFFSET_Y, HUMT_WIDTH, HUMT_HEIGHT, HUMT_SPRITE);
  tft.setCursor(140, 210);
  tft.print(String(soilMoisture) + "%");
}
