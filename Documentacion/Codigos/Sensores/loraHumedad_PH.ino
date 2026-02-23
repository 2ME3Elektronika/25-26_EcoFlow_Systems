#include <RadioLib.h>
#include <SPI.h>

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

// --- Configuración LoRa ---
#define FRECUENCIA 866.3
#define POTENCIA 22       // dBm

#define PAUSA 5000  // ms
unsigned long lastSend = 0;

// Crear objeto LoRa
SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);

void setup() {
    Serial.begin(115200);
    delay(1000);

    SPI.begin();  // SPI hardware

    Serial.println("Iniciando LoRa TX...");

    int state = radio.begin(FRECUENCIA);
    if (state != RADIOLIB_ERR_NONE) {
        Serial.print("Error LoRa: ");
        Serial.println(state);
        while (true) {}
    }

    radio.setOutputPower(POTENCIA);

    Serial.println("LoRa TX listo");
}

void loop() {
    if (millis() - lastSend >= PAUSA) {
        lastSend = millis();

        // --- Leer humedad ---
        int valorAnalogico = analogRead(HUMEDAD_PIN);
        float humedadPorcentaje = map(valorAnalogico, VALOR_SECO, VALOR_HUMEDO, 0, 100);
        humedadPorcentaje = constrain(humedadPorcentaje, 0, 100);

        // Multiplicamos por 100 para enviar como entero
        int humedadSend = (int)(humedadPorcentaje * 100);

        // --- Leer pH ---
        int adcPH = analogRead(PH_PIN);
        float voltajePH = adcPH * (PH_VOLTAGE_REF / 4095.0);
        float pH = 7.0 + (1.5 - voltajePH) / 0.18;
        pH = constrain(pH, 0.0, 14.0);
        int pHSend = (int)(pH * 100);

        // --- Mostrar por Serial ---
        Serial.print("Humedad: "); Serial.print(humedadPorcentaje); Serial.print("% | ");
        Serial.print("pH: "); Serial.println(pH, 2);

        // --- Enviar por LoRa ---
        String mensaje = "H=" + String(humedadSend) + ",pH=" + String(pHSend);
        int txState = radio.transmit(mensaje);
        if (txState == RADIOLIB_ERR_NONE) {
            Serial.println("Enviado por LoRa: " + mensaje);
        } else {
            Serial.print("Error envío: ");
            Serial.println(txState);
        }
    }
}

