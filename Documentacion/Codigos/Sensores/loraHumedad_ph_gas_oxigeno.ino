#include <RadioLib.h>
#include <SPI.h>
#include <Wire.h>
#include "DFRobot_OxygenSensor.h"

// --- Pines LoRa Heltec V3 (SX1262) ---
#define LORA_SCK    9
#define LORA_MISO   11
#define LORA_MOSI   10
#define LORA_CS     8
#define LORA_RST    12
#define LORA_BUSY   13
#define LORA_DIO1   14

// --- Sensor de humedad ---
#define HUMEDAD_PIN A0
#define VALOR_SECO 3000
#define VALOR_HUMEDO 1000

// --- Sensor de pH ---
#define PH_PIN A1
#define PH_VOLTAGE_REF 3.3  // Voltaje de referencia ADC

// --- Sensor de gas ---
#define GAS_PIN A2
#define GAS_MAX 4095   // Valor máximo ADC

// --- Sensor de oxígeno I2C ---
#define SDA_PIN 4
#define SCL_PIN 5
#define O2_I2C_ADDRESS ADDRESS_3  // Dirección por defecto del sensor (0x73)
#define O2_COLLECT_NUMBER 10      // Número de lecturas para promediar

DFRobot_OxygenSensor oxygenSensor;

// --- Configuración LoRa ---
#define FRECUENCIA 866.3
#define POTENCIA 22       // dBm
#define PAUSA 5000        // ms

unsigned long lastSend = 0;

// Crear objeto LoRa
SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);

void setup() {
    Serial.begin(115200);
    delay(1000);

    SPI.begin();  // Inicializa SPI

    Serial.println("Iniciando LoRa TX...");
    int state = radio.begin(FRECUENCIA);
    if (state != RADIOLIB_ERR_NONE) {
        Serial.print("Error LoRa: ");
        Serial.println(state);
        while (true) {}
    }
    radio.setOutputPower(POTENCIA);

    // --- Inicializar I2C y sensor de oxígeno ---
    Wire.begin(SDA_PIN, SCL_PIN);
    oxygenSensor.begin(O2_I2C_ADDRESS);  // inicializa sin validación

    Serial.println("Setup completo: LoRa y sensor de oxígeno inicializados");
}

void loop() {
    if (millis() - lastSend >= PAUSA) {
        lastSend = millis();

        // --- Leer humedad ---
        int valorAnalogico = analogRead(HUMEDAD_PIN);
        float humedadPorcentaje = map(valorAnalogico, VALOR_SECO, VALOR_HUMEDO, 0, 100);
        humedadPorcentaje = constrain(humedadPorcentaje, 0, 100);
        int humedadSend = (int)(humedadPorcentaje * 100);

        // --- Leer pH ---
        int adcPH = analogRead(PH_PIN);
        float voltajePH = adcPH * (PH_VOLTAGE_REF / 4095.0);
        float pH = 7.0 + (1.5 - voltajePH) / 0.18;
        pH = constrain(pH, 0.0, 14.0);
        int pHSend = (int)(pH * 100);

        // --- Leer oxígeno ---
        float oxigenoValor = oxygenSensor.getOxygenData(O2_COLLECT_NUMBER);
        float oxigenoPorcentaje = constrain(oxigenoValor, 0.0, 25.0);  // rango típico sensor
        int oxigenoSend = (int)(oxigenoPorcentaje * 100);

        // --- Leer gas ---
        int gasValor = analogRead(GAS_PIN);
        float gasPorcentaje = map(gasValor, 0, GAS_MAX, 0, 100);
        gasPorcentaje = constrain(gasPorcentaje, 0, 100);
        int gasSend = (int)(gasPorcentaje * 100);

        // --- Mostrar por Serial ---
        Serial.print("Humedad: "); Serial.print(humedadPorcentaje); Serial.print("% | ");
        Serial.print("pH: "); Serial.print(pH, 2); Serial.print(" | ");
        Serial.print("O2: "); Serial.print(oxigenoPorcentaje, 2); Serial.print(" %vol | ");
        Serial.print("Gas: "); Serial.print(gasPorcentaje, 2); Serial.println("%");

        // --- Enviar por LoRa ---
        String mensaje = "H=" + String(humedadSend) +
                         ",pH=" + String(pHSend) +
                         ",O2=" + String(oxigenoSend) +
                         ",G=" + String(gasSend);
        int txState = radio.transmit(mensaje);
        if (txState == RADIOLIB_ERR_NONE) {
            Serial.println("Enviado por LoRa: " + mensaje);
        } else {
            Serial.print("Error envío: ");
            Serial.println(txState);
        }
    }
}

