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
#include "assets/encandilado.h";
#include "assets/vampiro.h";
#include "assets/ahogado.h";
#include "assets/caliente.h";
#include "assets/congelado.h";
#include "assets/seco.h";
#include "assets/sofocado.h";
#include "assets/dashboard.h";
#include "assets/intro.h"
#include "assets/font.h"

void sendData();
void setpointsConfig();
void drawDashboard();
void displayAnimation();

//Client config
String MY_PRIVATE_ID = "1";
String SERVER_ADDRESS = "http://64.227.14.152:3000/api/planta/" + MY_PRIVATE_ID;

// Pin declarations
const byte TEST_LED = 2;
const byte DHT22_PIN = 27;
const byte SOIL_MOISTURE_PIN = 33;
#define SDA_LIGHT 15
#define SCL_LIGHT 5

/*
 * ST7789
 * DC = 2
 * RES = 4
 * SCL = 18
 * SDA = 23
 * CS not implemented, BLK to air
 */


// Object declarations
hw_timer_t * timer = NULL;      // Hardware timer

// Libraries
DHTStable DHT;
BH1750 lightMeter;
TFT_eSPI tft = TFT_eSPI();
WiFiMulti wifiMulti;
WiFiClient wifiClient;
HTTPClient http;

//Global variables
float hum;
float temp;
float light;
float soilMoisture;

bool needsToMeasure = false; // Bandera para tomar medidas
bool showAnimation = false;  // Intercambia entre animacion / estado
bool animationDisplayed = false; // La animacion ya se mostró?
bool measureDisplayed = false; // Las mediciones ya se actualizaron?

const byte INTERRUPT_PIN = 32;
const byte TOUCH_PIN = 12;
const byte INT_LED = 21;
const int DEBOUNCE = 100;
int lastMillis = 0;

void IRAM_ATTR changeState(){
  if(millis() - lastMillis > DEBOUNCE){ // Software debouncing
    showAnimation = !showAnimation;
    digitalWrite(INT_LED, showAnimation);
 }
 lastMillis = millis();
}

void touched(){
  if(millis() - lastMillis > DEBOUNCE){ // Software debouncing
    showAnimation = !showAnimation;
    digitalWrite(INT_LED, showAnimation);
 }
 lastMillis = millis();
}

void IRAM_ATTR onTimer(){
  needsToMeasure = true;
}

void initInterrupt(){
  //Timer init
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 2500000, true);
  timerAlarmEnable(timer);
  
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), changeState, FALLING);
  touchAttachInterrupt(TOUCH_PIN, touched, 20);
}


//Set points
double max_hum = 80.0f, min_hum = 20.0f, 
       max_temp = 32.0f, min_temp = 20.0f, 
       max_lum = 1000.0f, min_lum = 5.0F, 
       max_humt = 80.0f, min_humt = 10.0f;

// Plant statuses
enum EstadoPlanta{
  E_congelado,
  E_caliente,
  E_seco,
  E_sofocado,
  E_ahogado,
  E_vampiro,
  E_encandilado,
  E_feliz
};

char * estados[8] = {
  "Congelado",
  "Caliente",
  "Seco",
  "Sofocado",
  "Ahogado",
  "Vampiro",
  "Encandilado",
  "Feliz"
};

EstadoPlanta estado = E_feliz;
EstadoPlanta estadoDibujado = E_feliz;

// Networks
char *redes[3][2] = {
  {"TheCoolestWiFiLM", "LopezMurillo128"},
  {"WifiLM", "LopezMurillo128"},
  {"Honor 10 Lite", "tommywashere"}
};

void updateStatus(){
  if(temp > max_temp){
    estado = E_caliente;
  }else if(temp < min_temp){
    estado = E_congelado;
  }else if(light > max_lum){
    estado = E_encandilado;
  }else if(light < min_lum){
    estado = E_vampiro;
  }else if(hum < min_hum || soilMoisture < min_humt){
    estado = E_seco;
  }else if(hum > max_hum){
    estado = E_sofocado;
  }else if(soilMoisture > max_humt){
    estado = E_ahogado;
  }else{
    estado = E_feliz;
  }
  Serial.print("Estado: ");
  Serial.println(estados[estado]);
}

void takeMeasurement(){
  int soilRead = analogRead(SOIL_MOISTURE_PIN);
  DHT.read22(DHT22_PIN);
  hum = DHT.getHumidity();
  temp = DHT.getTemperature();
  light = lightMeter.readLightLevel();
  soilMoisture = map(soilRead, 0, 4095, 100, 0);
  Serial.println("Humedad: " + String(soilMoisture) + "%\t\t" + String(soilRead));
  Serial.println("Temperatura: " + String(temp) + "°C\t\tHumedad: " + String(hum) + "%\t\tLuminosidad: " + String(light) + "lx");

  measureDisplayed = false;
  updateStatus();
  sendData();
}

void setup() {
  // Pin modes
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(TEST_LED, OUTPUT);
  pinMode(INT_LED, OUTPUT);
  digitalWrite(TEST_LED, LOW);
  digitalWrite(INT_LED, LOW);
  
  // Init Serial port
  Serial.begin(115200);
  Serial.println("Init...");

  //Init screen
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.pushImage(INTRO_OFFSET_X, INTRO_OFFSET_Y, INTRO_WIDTH, INTRO_HEIGHT, INTRO_SPRITE);
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setCursor(0, 205);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.println("Sensors setup...");
  
  // Init I2C
  Wire.begin(SDA_LIGHT, SCL_LIGHT);
  //Init light meter
  while(! lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2, 0x23, &Wire) ){
    Serial.println("Error on BH1750 init...");
    digitalWrite(TEST_LED, HIGH);
    delay(500);
    digitalWrite(TEST_LED, LOW);
    delay(500);
  }

  initInterrupt();
  
  tft.print("WiFi setup.");
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
    tft.print(".");
  }

  http.begin(wifiClient, SERVER_ADDRESS);  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  //setpointsConfig();
}

void loop() {
  if(needsToMeasure){
    takeMeasurement();
    needsToMeasure = false;
  }

  Serial.println(showAnimation);
  
  if(showAnimation){
    displayAnimation();
  }else{
    drawDashboard();
  }
}

void sendData(){
  String body = "temperatura=" + String(temp) + "&humedad_ambiente=" + String(hum) + "&luminosidad=" + String(light) + "&humedad_tierra=" + String(soilMoisture);
  Serial.println(body); 
  
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
  animationDisplayed = false;
  if(measureDisplayed){
    return;
  }
  
  tft.setSwapBytes(true);
  tft.setFreeFont(&Arimo_Regular_24);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillScreen(TFT_BLACK);

  tft.pushImage(TEMP_OFFSET_X, TEMP_OFFSET_Y, TEMP_WIDTH, TEMP_HEIGHT, TEMP_SPRITE);
  tft.setCursor(20, 90);
  tft.print(String(temp) + "°C");
  if(temp > max_temp){
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("*");
  }else if(temp < min_temp){
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.print("*");
  }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.pushImage(SUN_OFFSET_X, SUN_OFFSET_Y, SUN_WIDTH, SUN_HEIGHT, SUN_SPRITE);
  String luminosidad = String(light);
  int offsetX = (luminosidad.length() - 3) * 10;
  if(light > max_lum){
    offsetX += 10;
  }
  tft.setCursor(160 - offsetX, 90);
  tft.print(luminosidad + "lx");
  if(light > max_lum){
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("*");
  }else if(light < min_lum){
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.print("*");
  }
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.pushImage(HUM_OFFSET_X, HUM_OFFSET_Y, HUM_WIDTH, HUM_HEIGHT, HUM_SPRITE);
  tft.setCursor(20, 210);
  tft.print(String(hum) + "%");
  if(hum > max_hum){
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("*");
  }else if(hum < min_hum){
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.print("*");
  }

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.pushImage(HUMT_OFFSET_X, HUMT_OFFSET_Y, HUMT_WIDTH, HUMT_HEIGHT, HUMT_SPRITE);
  if(soilMoisture > max_humt){
    offsetX = 10;
  }else{
    offsetX = 0;
  }
  tft.setCursor(140 - offsetX, 210);
  tft.print(String(soilMoisture) + "%");
  if(soilMoisture > max_humt){
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.print("*");
  }else if(soilMoisture < min_humt){
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.print("*");
  }

  measureDisplayed = true;
}

void displayAnimation(){
  measureDisplayed = false;
  if(animationDisplayed && estado == estadoDibujado){
    return;
  }
  
  tft.fillScreen(TFT_BLACK);
  switch(estado){
    case E_feliz:
      tft.pushImage(OK_OFFSET_X, OK_OFFSET_Y, OK_WIDTH, OK_HEIGHT, OK_SPRITE);
      break;
    case E_encandilado:
      tft.pushImage(ENCANDILADO_OFFSET_X, ENCANDILADO_OFFSET_Y, ENCANDILADO_WIDTH, ENCANDILADO_HEIGHT, ENCANDILADO_SPRITE);
      break;
    case E_vampiro:
      tft.pushImage(VAMPIRO_OFFSET_X, VAMPIRO_OFFSET_Y, VAMPIRO_WIDTH, VAMPIRO_HEIGHT, VAMPIRO_SPRITE);
      break;
    case E_ahogado:
      tft.pushImage(AHOGADO1_OFFSET_X, AHOGADO1_OFFSET_Y, AHOGADO1_WIDTH, AHOGADO1_HEIGHT, AHOGADO1_SPRITE);
      tft.pushImage(AHOGADO2_OFFSET_X, AHOGADO2_OFFSET_Y, AHOGADO2_WIDTH, AHOGADO2_HEIGHT, AHOGADO2_SPRITE);
      break;
    case E_caliente:
      tft.pushImage(CALIENTE_OFFSET_X, CALIENTE_OFFSET_Y, CALIENTE_WIDTH, CALIENTE_HEIGHT, CALIENTE_SPRITE);
      break;
    case E_congelado:
      tft.pushImage(CONGELADO_OFFSET_X, CONGELADO_OFFSET_Y, CONGELADO_WIDTH, CONGELADO_HEIGHT, CONGELADO_SPRITE);
      break;
    case E_seco:
      tft.pushImage(SECO_OFFSET_X, SECO_OFFSET_Y, SECO_WIDTH, SECO_HEIGHT, SECO_SPRITE);
      break;
    case E_sofocado:
      tft.pushImage(SOFOCADO_OFFSET_X, SOFOCADO_OFFSET_Y, SOFOCADO_WIDTH, SOFOCADO_HEIGHT, SOFOCADO_SPRITE);
      break;
    default:
      tft.pushImage(INTRO_OFFSET_X, INTRO_OFFSET_Y, INTRO_WIDTH, INTRO_HEIGHT, INTRO_SPRITE);
      break;    
  }
  
  estadoDibujado = estado;
  animationDisplayed = true;
  
}
