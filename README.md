# 🌱 Sistema Inteligente de Riego Automatizado -- EcoFlowSystems

------------------------------------------------------------------------

# 📌 Descripción del Proyecto

El negocio se centra en la creación y comercialización de un sistema
inteligente de riego automatizado que tiene como objetivo facilitar la
gestión eficiente del agua en jardines, terrazas, huertos urbanos y
pequeños entornos agrícolas.

La propuesta de valor se basa en combinar tecnología accesible con una
necesidad cotidiana: regar adecuadamente sin depender del tiempo, la
experiencia o la disponibilidad del usuario. El producto transforma una
tarea tradicionalmente repetitiva y poco precisa en un proceso
totalmente automatizado, optimizado y sostenible.

------------------------------------------------------------------------

# 🎯 Justificación y Elección del Proyecto

A la hora de valorar diferentes ideas para desarrollar durante el
proyecto, se analizaron propuestas relacionadas con:

-   Domótica\
-   Automatización industrial\
-   Energías renovables\
-   Aplicaciones móviles\
-   Dispositivos electrónicos de consumo

Finalmente se seleccionó el desarrollo del sistema inteligente de riego
automatizado debido a una combinación de factores estratégicos,
comerciales y de viabilidad.

## Necesidad Real del Mercado

La optimización del consumo de agua y la automatización de tareas
cotidianas se han convertido en prioridades tanto para particulares como
para empresas. Este proyecto ofrece:

-   Beneficio directo y medible\
-   Fácil comunicación al cliente final\
-   Impacto en sostenibilidad y eficiencia energética

## Diferenciación

Existen sistemas de riego automatizado en el mercado, pero muchos son
complejos, caros o poco intuitivos. Nuestra propuesta destaca por:

-   Sencillez de uso\
-   Bajo coste\
-   Escalabilidad\
-   Personalización

## Viabilidad Técnica y Económica

-   Componentes accesibles\
-   Montaje asumible\
-   Desarrollo compatible con recursos formativos\
-   Relación equilibrada entre coste, esfuerzo y funcionalidad

## Escalabilidad

Posibilidad de evolución hacia:

-   Sensores adicionales\
-   Integración con plataformas domóticas\
-   Versiones para agricultura profesional\
-   Aplicaciones en hostelería y comunidades

## Motivación del Equipo

La combinación de tecnología, sostenibilidad y automatización generó un
fuerte compromiso con la idea, facilitando el desarrollo y aumentando su
viabilidad real.

------------------------------------------------------------------------

# 🌐 Programación del Sistema (IoT)

Se desarrolló un sistema de comunicación IoT utilizando placas ESP32
LoRa V3.

## Arquitectura del Sistema

El sistema está compuesto por:

1.  Emisor\
2.  Repetidor\
3.  Receptor

------------------------------------------------------------------------

## 📡 Emisor (Ubicado en la Huerta)

Recoge información mediante sensores de:

-   Humedad del suelo\
-   Oxígeno\
-   Gas\
-   Temperatura\
-   Humedad ambiente

Los sensores están conectados a la placa ESP32 LoRa V3, que:

-   Procesa los datos\
-   Los envía mediante comunicación LoRa\
-   Los sube a la nube (ThingSpeak)

Permite consulta inmediata e histórica para análisis de tendencias.

------------------------------------------------------------------------

## 🔁 Repetidor

Actúa como intermediario cuando la distancia o los obstáculos afectan la
señal:

-   Recibe señal del emisor\
-   La retransmite al receptor\
-   Garantiza comunicación estable y fiable

------------------------------------------------------------------------

## 🖥 Receptor

-   Recibe los datos ambientales\
-   Los muestra en una página web desarrollada con Processing\
-   Permite interpretación sencilla sin conocimientos técnicos\
-   Guarda copia en ThingSpeak para análisis histórico

------------------------------------------------------------------------

# ⚙ Funcionamiento General del Sistema

1.  Los sensores miden condiciones ambientales.\
2.  El emisor procesa la información y la envía vía LoRa.\
3.  El repetidor retransmite la señal.\
4.  El receptor recibe y muestra los datos.\
5.  Los datos se almacenan en la nube para consulta remota e histórica.

------------------------------------------------------------------------

# 🔧 Proceso de Montaje y Desarrollo del Hardware

## Componentes Utilizados

-   Heltec WiFi LoRa V3\
-   Electroválvula 9V\
-   Puente H\
-   Fuente de alimentación 9V\
-   Regulador de voltaje 7805\
-   Condensadores\
-   Diodo de protección\
-   PCB y cableado

------------------------------------------------------------------------

## Alimentación

-   Entrada principal de 9V\
-   Regulador 7805 reduce de 9V a 5V\
-   Condensadores antes y después del regulador para estabilidad\
-   5V alimentan el Heltec

------------------------------------------------------------------------

## Conexión al Heltec

-   5V → Pin VCC\
-   GND → Pin GND (masa común del circuito)

------------------------------------------------------------------------

## Control de Electroválvula

### Del Heltec al Puente H

-   Pin digital → AIN1\
-   Pin digital → AIN2

### Del Puente H a la Válvula

-   Salidas A1 y A2 → extremos de la electroválvula

Permite invertir dirección de corriente para abrir o cerrar la válvula.

### Protección

Diodo en paralelo con la válvula para absorber picos de tensión al
apagarse.

------------------------------------------------------------------------

## Organización en PCB

1.  Sección alimentación cerca de entrada 9V\
2.  Separación de líneas de señal y potencia\
3.  Pistas anchas para línea de 9V\
4.  Masa común correctamente distribuida

------------------------------------------------------------------------

## Controles Finales

-   Verificar conexiones antes de alimentar\
-   Medir 5V antes de conectar válvula\
-   Añadir disipador si el 7805 se calienta\
-   Etiquetar pines (VCC, GND, AIN1, AIN2, A1, A2)\
-   Probar primero sin válvula

------------------------------------------------------------------------

# ☁ Desarrollo Web con ThingSpeak

## Crear Cuenta

-   Registro en plataforma\
-   Activación por correo

## Crear Canal

Campos:

-   Field 1 → Humedad suelo\
-   Field 2 → Oxígeno\
-   Field 3 → Gas\
-   Field 4 → Humedad ambiente\
-   Field 5 → Temperatura ambiente

Marcar como público.

## API Keys

-   Write API Key (envío de datos)\
-   Read API Key (visualización)

## Envío de Datos

https://api.thingspeak.com/update?api_key=TU_WRITE_API_KEY&field1=VALOR1&field2=VALOR2

## Visualizaciones

-   TimeChart\
-   Gauge\
-   Number Display

## Insertar en Web

Uso de iframe dentro del archivo HTML.

## Acceso Público

https://thingspeak.mathworks.com/channels/3228028

------------------------------------------------------------------------

# 🌐 Configuración de Red -- Router

## Acceso

IP: 192.168.1.1\
Usuario: admin\
Contraseña: admin

(Recomendado cambiar tras primera conexión)

## Configuración Wi-Fi

-   Definir SSID\
-   Seguridad WPA2-PSK o WPA3\
-   Contraseña segura

## Configuración Avanzada

-   Activar DHCP\
-   Ajustar canal\
-   Filtrado MAC\
-   Actualizar firmware

------------------------------------------------------------------------

# 🏡 Proceso de Montaje en la Huerta

Instalación física del sistema:

-   Ubicación protegida para el emisor\
-   Protección contra humedad\
-   Instalación segura de electroválvula\
-   Comprobación de cobertura LoRa\
-   Verificación de envío de datos en tiempo real

------------------------------------------------------------------------

# 📈 Conclusión

EcoFlowSystems integra:

-   Electrónica\
-   IoT\
-   Comunicación LoRa\
-   Automatización\
-   Sostenibilidad

Es un sistema escalable, replicable y técnicamente viable que permite
optimizar el uso del agua y automatizar la gestión agrícola de pequeña
escala.
