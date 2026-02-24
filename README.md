# 🌱 Sistema Inteligente de Riego Automatizado -- EcoFlowSystems

## 📌 Descripción del Proyecto

El negocio se centra en la creación y comercialización de un **sistema
inteligente de riego automatizado** cuyo objetivo es facilitar la
gestión eficiente del agua en:

-   Jardines\
-   Terrazas\
-   Huertos urbanos\
-   Pequeños entornos agrícolas

La propuesta de valor combina **tecnología accesible** con una necesidad
cotidiana: regar adecuadamente sin depender del tiempo, la experiencia o
la disponibilidad del usuario.

------------------------------------------------------------------------

# 📊 Tabla de Especificaciones Técnicas

  -----------------------------------------------------------------------
  Categoría                      Especificación
  ------------------------------ ----------------------------------------
  Microcontrolador               ESP32 LoRa V3

  Comunicación                   LoRa (larga distancia)

  Plataforma IoT                 ThingSpeak

  Sensores                       Humedad suelo, Oxígeno, Gas,
                                 Temperatura, Humedad ambiente

  Actuador                       Electroválvula 9V

  Control de potencia            Puente H

  Alimentación principal         9V

  Regulación de voltaje          7805 (9V → 5V)

  Protección                     Diodo antiparalelo

  Visualización local            Página web desarrollada con Processing

  Almacenamiento en nube         ThingSpeak (histórico de datos)

  Escalabilidad                  Integración domótica y ampliación
                                 modular
  -----------------------------------------------------------------------

------------------------------------------------------------------------

# 🌐 Arquitectura del Sistema

## 🏗 Componentes Principales

1.  **Emisor**
2.  **Repetidor**
3.  **Receptor**

### 📡 Emisor

-   Recoge datos ambientales.
-   Envía datos vía LoRa.
-   Sube información a ThingSpeak.

### 🔁 Repetidor

-   Recibe señal del emisor.
-   La retransmite para garantizar estabilidad.

### 🖥 Receptor

-   Muestra datos en web local.
-   Permite consulta remota en la nube.

------------------------------------------------------------------------

# ⚙ Funcionamiento General

1.  Los sensores miden condiciones ambientales.
2.  El emisor procesa y envía datos vía LoRa.
3.  El repetidor retransmite señal.
4.  El receptor muestra datos en web local.
5.  Los datos se almacenan en ThingSpeak.

------------------------------------------------------------------------

# 🔧 Hardware Utilizado

## 🧩 Componentes

-   Heltec WiFi LoRa V3\
-   Electroválvula 9V\
-   Puente H\
-   Fuente 9V\
-   Regulador 7805\
-   Condensadores\
-   Diodo de protección\
-   PCB y cableado

------------------------------------------------------------------------

# ☁ Integración con ThingSpeak

## Configuración del Canal

Campos utilizados:

-   Field 1 → Humedad del suelo\
-   Field 2 → Oxígeno\
-   Field 3 → Gas\
-   Field 4 → Humedad ambiente\
-   Field 5 → Temperatura ambiente

### Envío de datos:

https://api.thingspeak.com/update?api_key=TU_WRITE_API_KEY&field1=VALOR1&field2=VALOR2

------------------------------------------------------------------------

# 🌐 Configuración de Red

Router configurado mediante:

IP: 192.168.1.1\
Usuario: admin\
Contraseña: admin

(Recomendado cambiar tras la primera conexión)

------------------------------------------------------------------------

# 📈 Conclusión

EcoFlowSystems integra:

-   Electrónica\
-   IoT\
-   Comunicación LoRa\
-   Automatización\
-   Sostenibilidad

Ofrece una solución escalable, eficiente y orientada al ahorro
inteligente de agua.
