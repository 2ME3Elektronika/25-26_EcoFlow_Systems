# 🌱 EcoFlow Systems

## Sistema Inteligente de Riego Automatizado con Arquitectura IoT Distribuida

![Estado](https://img.shields.io/badge/Estado-En%20Desarrollo-green)
![Arquitectura](https://img.shields.io/badge/Arquitectura-Distribuida-blue)
![Protocolo](https://img.shields.io/badge/Comunicación-LoRa-orange)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-yellow)
![Licencia](https://img.shields.io/badge/Licencia-Académica-lightgrey)

------------------------------------------------------------------------

# 📖 Resumen Ejecutivo

EcoFlow Systems es un sistema avanzado de riego inteligente basado en
IoT que integra: - Sensórica ambiental - Comunicación LoRa de largo
alcance - Procesamiento distribuido con ESP32 - Plataforma Cloud
(ThingSpeak) - Visualización web en tiempo real

El proyecto combina electrónica, redes, programación, automatización
industrial y análisis de datos, desarrollando una solución tecnológica
escalable, sostenible y preparada para entornos reales.

------------------------------------------------------------------------

# 🎯 Objetivos Estratégicos

-   Optimizar el consumo hídrico mediante automatización inteligente.
-   Reducir intervención manual.
-   Implementar arquitectura distribuida robusta.
-   Integrar almacenamiento y análisis en la nube.
-   Garantizar escalabilidad futura.

------------------------------------------------------------------------

# 🏗 Arquitectura Técnica

## Modelo por Capas

1.  **Capa Física (Sensores)**
2.  **Capa de Comunicación (LoRa)**
3.  **Capa de Plataforma (ThingSpeak Cloud)**
4.  **Capa de Visualización (Web Local + Dashboard)**

```{=html}
<!-- -->
```
    [Sensores] → [ESP32 Emisor] → [Repetidor LoRa] → [ESP32 Receptor]
                                             ↓
                                       ThingSpeak Cloud

------------------------------------------------------------------------

# 🔬 Componentes del Sistema

## 1️⃣ Emisor

-   Heltec WiFi LoRa V3 (ESP32)
-   Sensores:
    -   Humedad del suelo
    -   Oxígeno
    -   Gas
    -   Temperatura
    -   Humedad ambiental

Funciones: - Lectura y procesamiento de datos - Transmisión LoRa - Envío
HTTP a ThingSpeak

------------------------------------------------------------------------

## 2️⃣ Repetidor

-   Retransmisión de señal
-   Ampliación de cobertura
-   Estabilidad ante obstáculos

------------------------------------------------------------------------

## 3️⃣ Receptor

-   Recepción LoRa
-   Dashboard local (Processing)
-   Sincronización Cloud

------------------------------------------------------------------------

# 🔌 Diseño Electrónico

## Alimentación

-   Fuente 9V
-   Regulador 7805 (9V → 5V)
-   Condensadores de filtrado
-   Diodo de protección
-   Tierra común

## Control de Actuadores

-   Puente H
-   Electroválvula 9V
-   Pines digitales ESP32

------------------------------------------------------------------------

# ☁ Integración Cloud

## Plataforma: ThingSpeak

Campos configurados:

1.  Humedad suelo
2.  Oxígeno
3.  Gas
4.  Humedad ambiente
5.  Temperatura

Ejemplo de envío:

    https://api.thingspeak.com/update?api_key=WRITE_API_KEY&field1=VALOR

------------------------------------------------------------------------

# 📊 Visualización

-   Gráficas temporales
-   Indicadores tipo Gauge
-   Iframes embebidos
-   Monitorización histórica

------------------------------------------------------------------------

# 🛡 Validaciones Técnicas

-   Medición previa de tensiones
-   Pruebas sin carga
-   Disipación térmica en regulador
-   Protección ante picos inductivos

------------------------------------------------------------------------

# 🚀 Escalabilidad

Posibles mejoras:

-   Machine Learning para riego predictivo
-   App móvil dedicada
-   Integración domótica
-   Sensores adicionales
-   Panel solar

------------------------------------------------------------------------

# 🌍 Impacto Ambiental

-   Reducción de desperdicio de agua
-   Automatización eficiente
-   Uso racional de recursos
-   Enfoque sostenible

------------------------------------------------------------------------

# 📚 Tecnologías Utilizadas

-   ESP32
-   LoRa
-   IoT
-   ThingSpeak
-   Processing
-   Electrónica analógica y digital

------------------------------------------------------------------------

# 👨‍💻 Contexto Académico

Proyecto desarrollado para el módulo de Digitalización y Sistemas
Inteligentes, integrando:

-   Electrónica aplicada
-   Comunicaciones inalámbricas
-   Computación en la nube
-   Arquitecturas distribuidas
-   Automatización industrial

------------------------------------------------------------------------

# 📌 Conclusión

EcoFlow Systems representa una solución integral IoT que combina
innovación tecnológica, sostenibilidad y arquitectura escalable,
demostrando dominio transversal de múltiples disciplinas técnicas.
