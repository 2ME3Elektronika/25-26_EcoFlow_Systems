#include <RadioLib.h>
#include <SPI.h>

#define LORA_CS 8
#define LORA_RST 12
#define LORA_BUSY 13
#define LORA_DIO1 14
#define FRECUENCIA 866.3

SX1262 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);

void setup() {
  Serial.begin(9600);
  delay(1000);

  SPI.begin();
  if (radio.begin(FRECUENCIA) != RADIOLIB_ERR_NONE) {
    Serial.println("Error LoRa RX");
    while (1);
  }
  Serial.println("RECEPTOR listo");
}

// =======================
// Parsear "CLAVE=VALOR"
// =======================
int getValue(String data, String key) {
  int start = data.indexOf(key + "=");
  if (start == -1) return 0;
  start += key.length() + 1;
  int end = data.indexOf(",", start);
  if (end == -1) end = data.length();
  return data.substring(start, end).toInt();
}

void loop() {
  String mensaje;
  int state = radio.receive(mensaje);

  if (state == RADIOLIB_ERR_NONE) {

    int hTi     = getValue(mensaje, "HUMEDAD_TIERRA");
    int pH      = getValue(mensaje, "pH");
    int o2      = getValue(mensaje, "O2");
    int gas     = getValue(mensaje, "GAS");
    int humA    = getValue(mensaje, "HUM_AIRE");
    int tempA   = getValue(mensaje, "TEMP_AIRE");

    // 🔋 NUEVO: batería
    int vbat    = getValue(mensaje, "VBAT");       // voltaje *100
    int vbatPct = getValue(mensaje, "VBAT_PCT");   // %

    // =======================
    // Envío a Processing (CSV)
    // =======================
    Serial.print(tempA / 100.0);   Serial.print(",");
    Serial.print(gas / 100.0);     Serial.print(",");
    Serial.print(humA / 100.0);    Serial.print(",");
    Serial.print(hTi / 100.0);     Serial.print(",");
    Serial.print(pH / 100.0);      Serial.print(",");
    Serial.print(o2 / 100.0);      Serial.print(",");
    Serial.print(vbat / 100.0);    Serial.print(",");   // Voltios
    Serial.println(vbatPct);                        // %

  }
}

