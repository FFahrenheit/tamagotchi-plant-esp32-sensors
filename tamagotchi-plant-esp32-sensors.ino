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
#include <SoftwareSerial.h>

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
#include "assets/pitches.h"

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
const byte BUZZER_PIN = 32;
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
SoftwareSerial mySerial;
const byte MY_RX = 13;
const byte MY_TX  = 14;

// Networks
char *redes[4][2] = {
  {"TheCoolestWiFiLM", "LopezMurillo128"},
  {"WifiLM", "LopezMurillo128"},
  {"Honor 10 Lite", "tommywashere"},
  {"redMolina2.4G", "Molina_2021"}
};

//Global variables
float hum;
float temp;
float light;
float soilMoisture;

String cameraIP="";
String plantName = "";

bool needsToMeasure = false;      // Bandera para tomar medidas
bool showAnimation = false;       // Intercambia entre animacion / estado
bool animationDisplayed = false;  // La animacion ya se mostró?
bool measureDisplayed = false;    // Las mediciones ya se actualizaron?
bool spritesDisplayed = false;
int measuresCounter = 0;
int lastGreeting = 0;

/*   INTERRUPCIONES    */
const byte INTERRUPT_PIN = 32;
const byte TOUCH_PIN = 12;
const byte INT_LED = 21;
const int DEBOUNCE = 100;
int lastMillis = 0;

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
  
  touchAttachInterrupt(TOUCH_PIN, touched, 20);
}

/*     DUAL CORE PROCESSING    */
TaskHandle_t TaskSensors;
TaskHandle_t TaskScreen;

void taskSensorCode(void * pvParameter){
  Serial.print("Sensor Task running on core ");
  Serial.println(xPortGetCoreID());
  
  
  while(true){
    if(needsToMeasure){
      takeMeasurement();
      needsToMeasure = false;
      measuresCounter += 1;
    }
    if(measuresCounter >= 6){
      setpointsConfig();
      measuresCounter = 0;
    }
    delay(20);
  }
}

void logOnScreen(String message){
  if((millis() - lastGreeting)< 5000){
    return;
  }
  tft.fillRect(10, 215, 230, 25, TFT_BLACK);
  tft.setCursor(10, 230);
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.print("> " + message);
  Serial.println("> " + message);
}

void processMessage(String message){
  message.trim();
  if(message == ""){
    return;
  }
  
  String tipo = message.substring(0, 4);
  Serial.println("New message: " + message);
  
  if(tipo == "wifi"){
    String ssid = WiFi.SSID();
    String password;
    for(auto red : redes){
      if(String(red[0]) == ssid){
        password = String(red[1]);
        break;
      }
    }

    String payload = ssid + '\x0' + password;
    Serial.println(payload);
    Serial.println(payload.indexOf('\x0'));

  }else if(tipo == "myip"){
    cameraIP = message.substring(4);
    Serial.println("Camera IP: " + cameraIP);
  }else if(tipo == "hola"){
    // TODO carita saludando
    String greeting = message.substring(4);
    tft.fillRect(10, 215, 230, 25, TFT_BLACK);
    tft.setCursor(10, 230);
    tft.setFreeFont(&FreeSans9pt7b);
    tft.setTextColor(TFT_PINK, TFT_BLACK);
    tft.print("Hola " + greeting + "! :)");
    Serial.println("Saludo a " + greeting);
    lastGreeting = millis();
  }
  else{
    logOnScreen(message);
  }
}

void taskScreenCode(void * pvParameter){
  Serial.print("Screen Task running on core ");
  Serial.println(xPortGetCoreID());
  
  while(true){
    if(Serial.available() > 0){
      String message = Serial.readString();
      processMessage(message);
    }
    if(mySerial.available() > 0){
      String msg = mySerial.readString();
      Serial.println(msg);
      processMessage(msg);
    }
    
    if(showAnimation){
      displayAnimation();
    }else{
      drawDashboard();
    }
    delay(20);
  }
}

void createTasks(){
    //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    taskSensorCode,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &TaskSensors,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    taskScreenCode,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &TaskScreen,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500);
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

void notificationSound(){
  tone(BUZZER_PIN, NOTE_F6, 100);
  delay(120);
  noTone(BUZZER_PIN);
  tone(BUZZER_PIN, NOTE_A6, 150);
  delay(170);
  noTone(BUZZER_PIN);
  
}

void updateStatus(){
  EstadoPlanta anterior = estado;
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
  if(estado != E_feliz && anterior != estado){
   notificationSound(); 
  }
  Serial.print("Estado: ");
  Serial.println(estados[estado]);
}

void takeMeasurement(){
  int soilRead = analogRead(SOIL_MOISTURE_PIN);
  DHT.read22(DHT22_PIN);
  float temporary_hum = DHT.getHumidity();
  float temporary_temp = DHT.getTemperature();
  float temporary_light = lightMeter.readLightLevel();
  
  if(temporary_hum > 0){
    hum = temporary_hum;
  }
  if(temporary_light > 0){
    light = temporary_light;
  }
  if(temporary_temp > -10 && temporary_temp <= 125){
    temp = temporary_temp;
  }
  
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
  pinMode(BUZZER_PIN, OUTPUT);
  notificationSound();
  digitalWrite(TEST_LED, LOW);
  digitalWrite(INT_LED, LOW);
  
  // Init Serial port
  Serial.begin(115200);
  Serial.println("Init...");
  mySerial.begin(9600, SWSERIAL_8N1, MY_RX, MY_TX, false);

  //Init screen
  tft.init();
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.pushImage(INTRO_OFFSET_X, INTRO_OFFSET_Y, INTRO_WIDTH, INTRO_HEIGHT, INTRO_SPRITE);
  tft.setFreeFont(&FreeSans9pt7b);
  tft.setCursor(0, 185);
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
  notificationSound();
  
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
  tft.println();

  http.begin(wifiClient, SERVER_ADDRESS);  //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  initInterrupt();
  
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  notificationSound();

  setpointsConfig();
  createTasks();
}

void loop() {
  digitalWrite(INT_LED, showAnimation);
}

void sendData(){
  String body = "temperatura=" + String(temp) + "&humedad_ambiente=" + String(hum) + "&luminosidad=" + String(light) + "&humedad_tierra=" + String(soilMoisture);
  if(cameraIP != ""){
    body += "&camera_ip=" + cameraIP;
  }
  
  Serial.println(body); 
  
  int httpCode = http.PUT(body);                    //Send the request
  Serial.println("Response: " + String(httpCode));


  if (httpCode > 0) { //Check the returning code
    logOnScreen("Ok: " + String(httpCode));
  }else{
    logOnScreen("Error: " + String(httpCode));
  }
 
  //http.end();   //Close connection
}

double json2double(JSONVar jsonVar){
  if(JSON.typeof(jsonVar) == "string"){
    String value = String((const char*)jsonVar);
  
    if(value.indexOf(0) == '"'){
      value.remove(0, 1);
      value.remove(value.length() - 1, 1);
    }
    return value.toDouble(); 
  }

  return (double) jsonVar;
}

void setpointsConfig(){
  HTTPClient http2;
  http2.begin(wifiClient, SERVER_ADDRESS + "/config");  //Specify request destination
  int httpCode;
  int tries = 0;
  
  do{
    httpCode = http2.GET();                  //Send the request
    Serial.println("Response: " + String(httpCode));
    
    tries += 1;
    if (httpCode > 0) { //Check the returning code
   
      String payload = http2.getString();   //Get the request response payload
      JSONVar response = JSON.parse(payload);
  
      Serial.println(response);  
      
      if (JSON.typeof(response) != "undefined")
      {
        Serial.println(JSON.typeof(response)); // prints: object
        Serial.println(response["max_temp"]);
        Serial.println(json2double(response["max_temp"]));
        
        if(response.hasOwnProperty("max_temp")){
          max_temp = json2double(response["max_temp"]);
        }
        if(response.hasOwnProperty("min_temp")){
          min_temp = json2double(response["min_temp"]);
        }
        if(response.hasOwnProperty("max_hum")){
          max_hum = json2double(response["max_hum"]);
        }
        if(response.hasOwnProperty("min_hum")){
          min_hum = json2double(response["min_hum"]);
        }
        if(response.hasOwnProperty("max_lum")){
          max_lum = json2double(response["max_lum"]);
        }
        if(response.hasOwnProperty("min_lum")){
          min_lum = json2double(response["min_lum"]);
        }
        if(response.hasOwnProperty("max_humt")){
          max_humt = json2double(response["max_humt"]);
        }
        if(response.hasOwnProperty("min_humt")){
          min_humt = json2double(response["min_humt"]);
        }
        if(response.hasOwnProperty("name")){
          plantName = response["name"];
        }

        Serial.println("Maxima temperatura: " + String(max_temp));
        Serial.println("Minima temperatura: " + String(min_temp));
        Serial.println("Maxima humedad: " + String(max_hum));
        Serial.println("Minima humedad: " + String(min_hum));
        Serial.println("Maxima lumonisidad: " + String(max_lum));
        Serial.println("Minima luminosidad: " + String(min_lum));
        Serial.println("Maxima humedad tierra: " + String(max_humt));
        Serial.println("Minima humedad tierra: " + String(min_humt));
      }
      else
      {
        Serial.println(response);
      }
    }
  }while(httpCode < 0 && tries < 3);
  
  http2.end();   //Close connection
}

void drawDashboard(){
  animationDisplayed = false;
  if(measureDisplayed){
    return;
  }

  tft.setSwapBytes(true);
  tft.setFreeFont(&Arimo_Regular_24);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  
  if(!spritesDisplayed){
    tft.fillScreen(TFT_BLACK);
    tft.pushImage(TEMP_OFFSET_X, TEMP_OFFSET_Y, TEMP_WIDTH, TEMP_HEIGHT, TEMP_SPRITE);
    tft.pushImage(SUN_OFFSET_X, SUN_OFFSET_Y, SUN_WIDTH, SUN_HEIGHT, SUN_SPRITE);
    tft.pushImage(HUM_OFFSET_X, HUM_OFFSET_Y, HUM_WIDTH, HUM_HEIGHT, HUM_SPRITE);
    tft.pushImage(HUMT_OFFSET_X, HUMT_OFFSET_Y, HUMT_WIDTH, HUMT_HEIGHT, HUMT_SPRITE);
    spritesDisplayed = true;
  }

  tft.fillRect(20, 70, 210, 60, TFT_BLACK);
  tft.fillRect(20, 190, 210, 25, TFT_BLACK);
  
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

  if(plantName != ""){
   tft.setTextColor(TFT_WHITE, TFT_BLACK);
   tft.setCursor(120 - plantName.length()*7, 120);
   tft.setTextDatum(MC_DATUM);
   tft.drawCentreString(plantName, 120, 110, 2); 
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
  spritesDisplayed = false;
}
