# Wally
## Recolector de basura espacios cerrados usando esp32
Es un dispositivo robótico con capacidad de navegación por  espacios abiertos y cerrados, reconocimiento y transmisión de imagen y video, con la finalidad de ver e identificar objetos del entorno y disponer de ellos (levantarlos, recogerlos y llevarlos a un sitio específico).  Inicialmente pensado para labores de aseo, puede ser fácilmente utilizado en otros entornos que por sus condiciones  representen un riesgo para la vida humana y animal (recintos con riesgos biológicos, edificios al borde del colapso, entre otros), que se puede validar a traves de una aplicacion
### ALCANCE
Durante la primera iteración, estamos trabajando para que Wally pueda recorrer un espacio cerrado relativamente pequeño (por ejemplo, un salón) evitando obstaculos y la identificación de objetos a través de la cámara de manera limitada.
### REQUERIMENTOS FUNCIONALES
Recepción y transmisión de imágenes, streaming video, detección de imágenes vía imagen y sensor ultrasonido, capacidad de navegación, recolección del objeto, conectividad inalámbrica (Wi-Fi, Bluetooth).
###REQUERIMENTOS NO FUNCIONALES
Estabilidad, fiabilidad, precisión el el reconocimiento y recolección de objeto, facilidad de uso.
### 
| Equipo | Corriente (in)| Voltaje (in)  |
| ------------- | ------------- |------------  |
| ESP32CAM | 500mA  |  3.3V -5V |
| NODEMCU  | 300mA  |  3,3V - 5V |
| SERVOR  | 400mA  |   5V |
| MOTOR  | 400mA  | 6V-9V |
| ULTRASONIO  | 15mA  |  5V  |
| L9110(PUENTE H)  | 0.5mA  | 2.5V-12V |
| MORSUN  | 800mA  |4.5v-36v  |

MORSUN: Salida 2000mA a 5V o 3,3V
### DIAGRAMA CAJA NEGRA
El módulo ESP32-CAM  sera el modulo principal tiene algunas características técnicas como son:

- Conectividad: WiFi 802.11b/g/n + Bluetooth 4.2 con BLE. Soporta carga de imagen por WiFi.
- Conexiones: UART, SPI, I2C, y PWM. Tiene 9 pines GPIO.
- Frecuencia de reloj: hasta 160Mhz.
- Potencia de cómputo del microcontrolador: hasta 600 DMIPS.
- Memoria: 520KB de SRAM +  4MB de PSRAM + SD slot para tarjetas
- Extras: tiene múltiples modos de reposo, firmware actualizable por OTA, y LED para uso de memoria flash built-in.
- Cámara: soporta cámaras OV2640 que pueden venir en el pack o comprarse independientemente. Este tipo de cámaras tienen:
- 2 MP en su sensor
- Tamaño de arreglo UXGA de 1622×1200 px
- Formato de salida YUV422, YUV420, RGB565, RGB555 y compresión de datos de 8-bit.
- Puede transferir imagen entre 15 y 60 FPS.

Adicionalmente se usara un modulo secundario ESP8266 para el control de los motores y **modulo ultrasonido**, el sistema en general tiene diferentes modulos como:
* Modulo de alimentacion: Consta de la bateria y el sistema de regulacion
* Modulo de movimiento: Inicialmente se plantea que se requiere un puente H de dos canales y dos motores.
* Modulo de movimiento detecion: Consta de un servomotor de 360 grados para rotar la camara 360
* Modulo de movimiento recolección: Inicialmente se plantea como dos servomotores
* Modulo de deteccion: Consta de una camara para reconocer basura y ultrasonido para detectar obstaculos tambien la cercania de los objetos
* Modulo de Indicadores y botones: Consta de leds para notificar al usuario conexion con el servidor, encendido, falla y botones de encendido tambien de reset.
 Modulo SD: Que se encargara de guardar las imagenes para ser enviadas en caso de perdida de conexion.

A continuacion se muestra un diagrama general

![](https://github.com/ltherreraro/Wally/blob/main/Imagenes/diag1.PNG))

![](https://github.com/ltherreraro/Wally/blob/main/Imagenes/diag2.PNG))

Finalmente los datasheet de los modulos a usar
- [ESP32](https://github.com/ltherreraro/Wally/blob/main/Datasheet/esp32-sl_specification.pdf)
- [ESP32CAM](https://github.com/ltherreraro/Wally/blob/main/Datasheet/ESP32-CAM%20Product%20Specification.pdf)
- [Nodemcu](https://www.make-it.ca/nodemcu-details-specifications/)
- [ESP8266](https://github.com/ltherreraro/Wally/blob/main/Datasheet/0a-esp8266ex_datasheet_en.pdf)
- [Servo MG90](https://github.com/ltherreraro/Wally/blob/main/Datasheet/MG90S_Tower-Pro%20(1).pdf)
- [Servo SG90](https://github.com/ltherreraro/Wally/blob/main/Datasheet/sg90_datasheet%20(1).pdf)
- [Motor](https://ferretronica.com/products/motorreductor-500-gr-cm-1000-rpm-6v?variant=12391693877341&currency=COP&utm_medium=product_sync&utm_source=google&utm_content=sag_organic&utm_campaign=sag_organic&utm_campaign=gs-2021-10-19&utm_source=google&utm_medium=smart_campaign&gclid=Cj0KCQjwjbyYBhCdARIsAArC6LKaKwvKPRHye8ZWSAgEkHbSm4rjs0Gm-KYxnCncWKSN3TIoLXUkZbEaAqU5EALw_wcB)
- [Ultrasonido](https://github.com/ltherreraro/Wally/blob/main/Datasheet/HCSR04%20(1).pdf)
- [Puente H](https://github.com/ltherreraro/Wally/blob/main/Datasheet/datasheet-l9110%20(1).pdf)
- [Regulador](https://github.com/ltherreraro/Wally/blob/main/Datasheet/2001081204_Shikues-AMS1117-1-2_C475600.pdf)
-[RP2040 pico](https://github.com/ltherreraro/Wally/blob/main/Datasheet/rp2040-datasheet.pdf)
#### MEMORIA SD 
 Esta memoria se empleará para el almacenamiento de las imágenes tomadas por la cámara como informacion necesaria para conocer la posicion De los objetos, La comunicación de la micro SD esta basada en la interfaz de 8 pines(reloj, línea de comandos/ Master Out Slave In (MOSI), líneas 4xData / Master In Slave Out (MISO) y 3xPower). El protocolo SPI (Serial Peripheral Interface) es el protocolo de comunicación que admite la tarjeta para la inicialización. El funcionamiento del sistema se basa en 5 módulos: módulo de inicialización de tarjetas (CINM), módulo de lectura de tarjetas (CRM), módulo inactivo (IM),  módulo de escritura de tarjetas (CWM) y módulo de decisión (DM). Junto a los módulos hay una CU (unidad de control) que supervisar y controlar las actividades de cada módulo. Una microSD responde a una serie de comandos de 48 bits, para un almacenamiento dado de un solo bloque o multi-bloques, un solo bloque de almacenamiento posee un ancho de 512 bytes. 

_CAJA (IN/OUT) Driver micro SD_

![](https://github.com/ltherreraro/CubeRubik/blob/master/HW/03GRUPO3/03document/driver%20SD.png)

_CAJA FUNCIONAL (IN/OUT) micro SD_

![](https://github.com/ltherreraro/CubeRubik/blob/master/HW/03GRUPO3/03document/Diagrama%20funcional%20MICRO%20SD.png)


