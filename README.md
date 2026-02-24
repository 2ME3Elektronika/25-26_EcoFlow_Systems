# 🌱 EcoFlow Systems

## Sistema Inteligente de Riego Automatizado con IoT y LoRa

![Estado](https://img.shields.io/badge/Estado-Proyecto%20Académico-blue)
![Tecnología](https://img.shields.io/badge/Tecnología-IoT-green)
![Microcontrolador](https://img.shields.io/badge/ESP32-LoRa-orange)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-yellow)

------------------------------------------------------------------------

# 📑 Tabla de Contenidos

1.  Descripción del Proyecto\
2.  Objetivos\
3.  Arquitectura del Sistema\
4.  Dispositivos\
5.  Hardware Utilizado\
6.  Alimentación y Diseño Electrónico\
7.  Integración Cloud\
8.  Visualización\
9.  Validaciones Técnicas\
10. Escalabilidad\
11. Tecnologías Utilizadas\
12. Contexto Académico

------------------------------------------------------------------------

# 📌 1. Descripción del Proyecto

EcoFlow Systems es un sistema inteligente de riego automatizado diseñado
para optimizar el consumo de agua en jardines, huertos urbanos, terrazas
y pequeños entornos agrícolas.

El sistema automatiza completamente el proceso de monitorización y
control del riego, combinando sensores ambientales, comunicación LoRa de
largo alcance, plataforma en la nube (ThingSpeak) y visualización web
local.

------------------------------------------------------------------------

# 🎯 2. Objetivos

-   Optimizar el uso del agua\
-   Automatizar tareas repetitivas\
-   Permitir supervisión remota\
-   Facilitar análisis histórico de datos\
-   Crear un sistema escalable y sostenible

------------------------------------------------------------------------

# 🏗 3. Arquitectura del Sistema

El sistema está compuesto por tres dispositivos principales:

    [SENSORES] → [EMISOR LoRa] → [REPETIDOR] → [RECEPTOR] → [Web Local + ThingSpeak Cloud]

------------------------------------------------------------------------

# 📡 4. Dispositivos

## 4.1 Emisor (Huerta)

Dispositivo encargado de recoger los datos ambientales.

### Sensores utilizados:

-   Humedad del suelo\
-   Oxígeno\
-   Gas\
-   Temperatura\
-   Humedad ambiente

### Hardware:

-   Heltec WiFi LoRa V3 (ESP32 LoRa)

### Funciones:

-   Procesa datos\
-   Envía datos vía LoRa\
-   Publica datos en ThingSpeak

------------------------------------------------------------------------

## 4.2 Repetidor

Funciones: - Recibe señal del emisor\
- Retransmite señal al receptor\
- Garantiza estabilidad y alcance

------------------------------------------------------------------------

## 4.3 Receptor

Funciones: - Recibe datos LoRa\
- Visualiza datos en web (Processing)\
- Sincroniza con ThingSpeak\
- Permite análisis histórico

------------------------------------------------------------------------

# 🔌 5. Hardware Utilizado

  Componente            Función
  --------------------- -----------------------------------
  Heltec WiFi LoRa V3   Microcontrolador principal
  Electroválvula 9V     Control de agua
  Puente H              Control de dirección de corriente
  Regulador 7805        Conversión 9V → 5V
  Fuente 9V             Alimentación principal
  Diodo                 Protección contra picos
  Condensadores         Estabilidad eléctrica
  PCB                   Integración del circuito

------------------------------------------------------------------------

# 🔋 6. Alimentación y Diseño Electrónico

    Fuente 9V
       ↓
    Regulador 7805
       ↓
    5V → Heltec ESP32
    9V → Electroválvula

-   Condensadores antes y después del regulador\
-   Diodo en paralelo con la válvula\
-   Tierra común compartida

------------------------------------------------------------------------

# ☁ 7. Integración Cloud -- ThingSpeak

## Configuración

1.  Crear cuenta en ThingSpeak\
2.  Crear canal\
3.  Añadir campos:
    -   Field 1: Humedad suelo\
    -   Field 2: Oxígeno\
    -   Field 3: Gas\
    -   Field 4: Humedad ambiente\
    -   Field 5: Temperatura
4.  Obtener API Keys
    -   Write API Key\
    -   Read API Key

### Envío de datos:

    https://api.thingspeak.com/update?api_key=TU_WRITE_API_KEY&field1=VALOR1&field2=VALOR2

------------------------------------------------------------------------

# 📊 8. Visualización

Se utilizan:

-   TimeChart\
-   Gauge\
-   Number Display\
-   Embeds mediante iframe

Ejemplo:

``` html
<iframe width="450" height="260"
src="https://thingspeak.com/channels/XXXX/charts/1?dynamic=true&results=60&type=line">
</iframe>
```

------------------------------------------------------------------------

# 🛡 9. Validaciones Técnicas

-   Verificación de voltaje antes de conectar válvula\
-   Medición de salida 5V\
-   Uso de disipador en 7805 si es necesario\
-   Pruebas sin carga inicial\
-   Etiquetado de pines

------------------------------------------------------------------------

# 🚀 10. Escalabilidad

El sistema puede evolucionar hacia:

-   Integración domótica\
-   Versiones agrícolas avanzadas\
-   Sensores adicionales\
-   Automatización inteligente basada en IA\
-   Integración con apps móviles

------------------------------------------------------------------------

# 📚 11. Tecnologías Utilizadas

-   ESP32\
-   LoRa\
-   IoT\
-   ThingSpeak\
-   Processing\
-   Electrónica analógica y digital\
-   Reguladores lineales\
-   Puente H

------------------------------------------------------------------------

# 👨‍💻 12. Contexto Académico

Proyecto desarrollado como parte del módulo de Digitalización y Sistemas
Inteligentes, integrando:

-   Hardware\
-   Programación\
-   Redes\
-   Cloud Computing\
-   Electrónica aplicada

------------------------------------------------------------------------

# 📌 Conclusión

EcoFlow Systems demuestra cómo la combinación de IoT, automatización y
sostenibilidad puede transformar una tarea tradicional en un sistema
inteligente, eficiente y escalable.
