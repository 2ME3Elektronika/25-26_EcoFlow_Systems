# 🌱 EcoFlow Systems

## Sistema Inteligente de Riego Automatizado con Arquitectura IoT Distribuida basada en LoRa

![Estado](https://img.shields.io/badge/Estado-Proyecto%20Académico%20Avanzado-blue)
![Arquitectura](https://img.shields.io/badge/Arquitectura-IoT%20Distribuida-green)
![Comunicación](https://img.shields.io/badge/Protocolo-LoRa-orange)
![Microcontrolador](https://img.shields.io/badge/ESP32-Heltec-yellow)
![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak-lightgrey)

------------------------------------------------------------------------

# 📖 1. Introducción General

EcoFlow Systems es un sistema inteligente de riego automatizado diseñado
para optimizar el consumo de agua en jardines, huertos urbanos, terrazas
y pequeños entornos agrícolas.

El sistema automatiza completamente el proceso de monitorización y
control del riego, combinando:

-   Sensores ambientales
-   Comunicación LoRa de largo alcance
-   Procesamiento distribuido con ESP32
-   Plataforma en la nube (ThingSpeak)
-   Visualización web local
-   Control electrónico de electroválvula

Este documento sirve como guía técnica completa para que cualquier
persona pueda reproducir el proyecto desde cero.

------------------------------------------------------------------------

# 🎯 2. Objetivos del Proyecto

-   Optimizar el uso del agua.
-   Automatizar tareas repetitivas.
-   Permitir supervisión remota.
-   Facilitar análisis histórico de datos.
-   Crear un sistema escalable y sostenible.
-   Integrar hardware, software y comunicaciones en un único ecosistema
    funcional.

------------------------------------------------------------------------

# 🏗 3. Arquitectura Completa del Sistema

El sistema está compuesto por tres dispositivos principales:

    [SENSORES] 
         ↓
    [ESP32 EMISOR] 
         ↓ (LoRa)
    [REPETIDOR] 
         ↓ (LoRa)
    [ESP32 RECEPTOR] 
         ↓
    [Visualización Web Local]
         ↓
    [ThingSpeak Cloud]

## Modelo por Capas

1.  Capa Física (Sensores y Actuadores)
2.  Capa de Procesamiento (ESP32)
3.  Capa de Comunicación (LoRa)
4.  Capa de Plataforma (ThingSpeak)
5.  Capa de Visualización (Web Local)

------------------------------------------------------------------------

# 📡 4. Dispositivos del Sistema

## 4.1 Emisor (Ubicado en la Huerta)

### Sensores utilizados:

-   Humedad del suelo
-   Oxígeno
-   Gas
-   Temperatura
-   Humedad ambiente

### Hardware:

-   Heltec WiFi LoRa V3 (ESP32 con módulo LoRa integrado)

### Funciones:

-   Lectura periódica de sensores
-   Procesamiento básico de datos
-   Envío mediante LoRa
-   Envío HTTP a ThingSpeak

------------------------------------------------------------------------

## 4.2 Repetidor

### Función principal:

-   Recibir señal LoRa del emisor
-   Retransmitir señal al receptor
-   Aumentar alcance y estabilidad

Se utiliza cuando existen obstáculos o grandes distancias.

------------------------------------------------------------------------

## 4.3 Receptor

### Funciones:

-   Recibir datos LoRa
-   Mostrar datos en interfaz web (Processing)
-   Sincronizar datos con ThingSpeak
-   Permitir visualización histórica

------------------------------------------------------------------------

# 🔌 5. Hardware Utilizado

  Componente            Función
  --------------------- ----------------------------
  Heltec WiFi LoRa V3   Microcontrolador principal
  Electroválvula 9V     Control de paso de agua
  Puente H              Permite invertir polaridad
  Regulador 7805        Conversión 9V → 5V
  Fuente 9V             Alimentación principal
  Diodo                 Protección contra picos
  Condensadores         Estabilidad eléctrica
  PCB                   Integración del circuito

------------------------------------------------------------------------

# 🔋 6. Sistema de Alimentación

## Esquema General

    Fuente 9V
       ↓
    Regulador 7805
       ↓
    5V → ESP32
    9V → Electroválvula (vía Puente H)

### Recomendaciones Técnicas:

-   Añadir condensador de entrada y salida al 7805.
-   Usar disipador térmico si el consumo es elevado.
-   Colocar diodo en paralelo con la electroválvula.
-   Asegurar tierra común compartida.

------------------------------------------------------------------------

# ⚙ 7. Control de Electroválvula

## Conexión ESP32 → Puente H

  ESP32           Puente H
  --------------- ----------
  Pin Digital 1   AIN1
  Pin Digital 2   AIN2

## Conexión Puente H → Electroválvula

  Puente H   Electroválvula
  ---------- ----------------
  A1         Terminal 1
  A2         Terminal 2

El cambio de estado en los pines permite abrir o cerrar el paso de agua.

------------------------------------------------------------------------

# ☁ 8. Integración Cloud -- ThingSpeak

## Configuración Paso a Paso

1.  Crear cuenta en ThingSpeak.
2.  Crear nuevo canal.
3.  Añadir campos:
    -   Field 1: Humedad suelo
    -   Field 2: Oxígeno
    -   Field 3: Gas
    -   Field 4: Humedad ambiente
    -   Field 5: Temperatura
4.  Obtener API Keys.

### Ejemplo de envío:

    https://api.thingspeak.com/update?api_key=TU_WRITE_API_KEY&field1=VALOR1

------------------------------------------------------------------------

# 📊 9. Visualización de Datos

Se utilizan:

-   Gráficas temporales (TimeChart)
-   Indicadores tipo Gauge
-   Visualización numérica
-   Iframes embebidos

Ejemplo:

``` html
<iframe width="450" height="260"
src="https://thingspeak.com/channels/XXXX/charts/1?dynamic=true&results=60&type=line">
</iframe>
```

------------------------------------------------------------------------

# 🛡 10. Validaciones Técnicas y Pruebas

-   Verificar tensiones antes de conectar la válvula.
-   Medir salida 5V del regulador.
-   Probar sin carga inicialmente.
-   Comprobar temperatura del regulador.
-   Verificar continuidad en PCB.

------------------------------------------------------------------------

# 🚀 11. Escalabilidad y Mejoras Futuras

-   Integración domótica
-   Algoritmos predictivos (Machine Learning)
-   Panel solar
-   App móvil
-   Sensores adicionales
-   Control automático basado en humedad mínima configurable

------------------------------------------------------------------------

# 📚 12. Tecnologías Utilizadas

-   ESP32
-   LoRa
-   IoT
-   ThingSpeak
-   Processing
-   Electrónica analógica y digital
-   Reguladores lineales
-   Puente H

------------------------------------------------------------------------

# 👨‍💻 13. Contexto Académico

Proyecto desarrollado dentro del módulo de Digitalización y Sistemas
Inteligentes.

Integra:

-   Electrónica aplicada
-   Comunicaciones inalámbricas
-   Cloud Computing
-   Arquitecturas distribuidas
-   Automatización industrial

------------------------------------------------------------------------

# 📌 14. Conclusión

EcoFlow Systems demuestra cómo la combinación de IoT, automatización y
sostenibilidad puede transformar una tarea tradicional en un sistema
inteligente, eficiente y escalable.

Este README está diseñado como guía completa para reproducir el proyecto
desde cero, comprendiendo tanto la parte técnica como la arquitectura
global del sistema.
