#include <RadioLib.h>
#include <SPI.h>
#include <Wire.h>
#include "DFRobot_OxygenSensor.h"
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>


// --- Pines LoRa Heltec V3 (SX1262) ---
#define LORA_SCK 9
#define LORA_MISO 11
#define LORA_MOSI 10
#define LORA_CS 8
#define LORA_RST 12
#define LORA_BUSY 13
#define LORA_DIO1 14


// --- Sensores ---
#define HUMEDAD_PIN 1
#define VALOR_SECO 3000
#define VALOR_HUMEDO 1000


#define PH_PIN 2
#define PH_VOLTAGE_REF 3.3


#define GAS_PIN 3
#define GAS_MAX 4095


#define DHT_PIN 6
#define DHT_TYPE DHT11


#define SDA_PIN 4
#define SCL_PIN 5
#define O2_I2C_ADDRESS ADDRESS_3
#define O2_COLLECT_NUMBER 10


#define BAT_PIN 7
#define R1 100000.0
#define R2 100000.0


DFRobot_OxygenSensor oxygenSensor;
DHT dht(DHT_PIN, DHT_TYPE);


#define FRECUENCIA 866.3
#define POTENCIA 22


SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);


// --- ThingSpeak ---
const char* ssid = "EcoFlowSystems";
const char* password = "10122005";
const char* thingSpeakAPIKey = "OXYBIN5FATCU8CV1";


// --- Pines puente H (AIN1 / AIN2) ---
#define H_BRIDGE_AIN1 33
#define H_BRIDGE_AIN2 47


// --- Configuración de pulsos para prueba ---
#define PULSO_PRUEBA 600000UL // 10 minutos
#define PULSO_DURACION 200


// --- Variables de control ---
unsigned long tiempoInicioPrimerPulso = 0;
bool primerPulsoDisparado = false;
bool segundoPulsoDisparado = false;


// --- Funciones ---
float leerBateria() {
  int adc = analogRead(BAT_PIN);
  float voltaje = adc * (3.3 / 4095.0) * ((R1 + R2) / R2);
  return voltaje;
}


int leerPorcentajeBateria(float v) {
  int pct = (v - 3.3) / (4.2 - 3.3) * 100;
  return constrain(pct, 0, 100);
}


void enviarThingSpeak(int humedadTierra, int pH, int oxigeno, int gasPorcentaje, int humAire, int tempAire) {
  if(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
    int intentos = 0;
    while(WiFi.status() != WL_CONNECTED && intentos < 20){
      delay(500);
      intentos++;
    }
  }
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + String(thingSpeakAPIKey);
    url += "&field1=" + String(humedadTierra);
    url += "&field2=" + String(pH);
    url += "&field3=" + String(oxigeno);
    url += "&field4=" + String(gasPorcentaje);
    url += "&field5=" + String(humAire);
    url += "&field6=" + String(tempAire);
    http.begin(url);
    int httpResponseCode = http.GET();
    if(httpResponseCode > 0){
      Serial.println("Datos enviados a ThingSpeak correctamente");
    } else {
      Serial.print("Error al enviar ThingSpeak: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("No se pudo conectar a WiFi para ThingSpeak");
  }
}


void setup() {
  Serial.begin(9600);
  delay(1000);


  pinMode(H_BRIDGE_AIN1, OUTPUT);
  pinMode(H_BRIDGE_AIN2, OUTPUT);
  digitalWrite(H_BRIDGE_AIN1, LOW);
  digitalWrite(H_BRIDGE_AIN2, LOW);


  SPI.begin();


  Serial.println("Iniciando LoRa TX...");
  if (radio.begin(FRECUENCIA) != RADIOLIB_ERR_NONE) {
    Serial.println("Error LoRa");
    while (1);
  }
  radio.setOutputPower(POTENCIA);


  Wire.begin(SDA_PIN, SCL_PIN);
  oxygenSensor.begin(O2_I2C_ADDRESS);
  dht.begin();


  Serial.println("Setup completo: sensores listos");
}


void loop() {
  // --- Lectura de humedad REAL ---
  int valorAnalogico = analogRead(HUMEDAD_PIN);
  float humedad = (float)(VALOR_SECO - valorAnalogico) / (VALOR_SECO - VALOR_HUMEDO) * 100.0;
  humedad = constrain(humedad, 0.0, 100.0);


  int adcPH = analogRead(PH_PIN);
  float voltajePH = adcPH * (PH_VOLTAGE_REF / 4095.0);
  float pHf = 7.0 + (1.5 - voltajePH) / 0.18;
  pHf = constrain(pHf, 0.0, 14.0);


  float oxigenoF = oxygenSensor.getOxygenData(O2_COLLECT_NUMBER);
  oxigenoF = constrain(oxigenoF, 0.0, 25.0);


  int gasADC = analogRead(GAS_PIN);
  float gasF = (float)gasADC / GAS_MAX * 100.0;
  gasF = constrain(gasF, 0.0, 100.0);


  float humAireF = dht.readHumidity();
  float tempAireF = dht.readTemperature();
  if (isnan(humAireF)) humAireF = 0.0;
  if (isnan(tempAireF)) tempAireF = 0.0;


  float voltBateria = leerBateria();
  int bateriaPct = leerPorcentajeBateria(voltBateria);


  int humedadTierra = (int)(humedad*100);
  int pH = (int)(pHf*100);
  int oxigeno = (int)(oxigenoF*100);
  int gasPorcentaje = (int)(gasF*100);
  int humAire = (int)(humAireF*100);
  int tempAire = (int)(tempAireF*100);
  int vbat = (int)(voltBateria*100);


  String mensaje = "HUMEDAD_TIERRA=" + String(humedadTierra) +
                   ",pH=" + String(pH) +
                   ",O2=" + String(oxigeno) +
                   ",GAS=" + String(gasPorcentaje) +
                   ",HUM_AIRE=" + String(humAire) +
                   ",TEMP_AIRE=" + String(tempAire) +
                   ",VBAT=" + String(vbat) +
                   ",VBAT_PCT=" + String(bateriaPct);


  Serial.println("Enviando datos: " + mensaje);


  int txState = radio.transmit(mensaje);
  if (txState == RADIOLIB_ERR_NONE) {
    Serial.println("Enviado por LoRa correctamente");
  } else {
    Serial.print("Error envío LoRa: ");
    Serial.println(txState);
  }


  enviarThingSpeak(humedadTierra, pH, oxigeno, gasPorcentaje, humAire, tempAire);


  unsigned long ahora = millis();


  if (!primerPulsoDisparado && humedad < 50.0) {
    Serial.println("Primer pulso activado: AIN1 HIGH, AIN2 LOW");
    digitalWrite(H_BRIDGE_AIN1, HIGH);
    digitalWrite(H_BRIDGE_AIN2, LOW);
    delay(PULSO_DURACION);
    digitalWrite(H_BRIDGE_AIN1, LOW);
    tiempoInicioPrimerPulso = ahora;
    primerPulsoDisparado = true;
    segundoPulsoDisparado = false;
  }


  if (primerPulsoDisparado && !segundoPulsoDisparado) {
    unsigned long segundosTranscurridos = (ahora - tiempoInicioPrimerPulso) / 1000;
    Serial.print("Tiempo desde primer pulso: ");
    Serial.print(segundosTranscurridos);
    Serial.println(" segundos");
  }


  if (primerPulsoDisparado && !segundoPulsoDisparado && (ahora - tiempoInicioPrimerPulso >= PULSO_PRUEBA)) {
    Serial.println("Segundo pulso activado: AIN1 LOW, AIN2 HIGH");
    digitalWrite(H_BRIDGE_AIN1, LOW);
    digitalWrite(H_BRIDGE_AIN2, HIGH);
    delay(PULSO_DURACION);
    digitalWrite(H_BRIDGE_AIN2, LOW);
    primerPulsoDisparado = false;
    segundoPulsoDisparado = true;
    Serial.println("Segundo pulso finalizado, listo para siguiente ciclo");
  }


  delay(10000);
}


