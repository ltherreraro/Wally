# Wally
##Recolector de basura espacios cerrados usando esp32
Es un dispositivo robótico con capacidad de navegación por  espacios abiertos y cerrados, reconocimiento y transmisión de imagen y video, con la finalidad de ver e identificar objetos del entorno y disponer de ellos (levantarlos, recogerlos y llevarlos a un sitio específico).  Inicialmente pensado para labores de aseo, puede ser fácilmente utilizado en otros entornos que por sus condiciones  representen un riesgo para la vida humana y animal (recintos con riesgos biológicos, edificios al borde del colapso, entre otros), que se puede validar a traves de una aplicacion
### ALCANCE
Durante la primera iteración, estamos trabajando para que Wally pueda recorrer un espacio cerrado relativamente pequeño (por ejemplo, un salón) evitando obstaculos y la identificación de objetos a través de la cámara de manera limitada.
### REQUERIMENTOS FUNCIONALES
Recepción y transmisión de imágenes, streaming video, detección de imágenes vía imagen y sensor ultrasonido, capacidad de navegación, recolección del objeto, conectividad inalámbrica (Wi-Fi, Bluetooth).
###REQUERIMENTOS NO FUNCIONALES
Estabilidad, fiabilidad, precisión el el reconocimiento y recolección de objeto, facilidad de uso.
** MEMORIA SD**
 Esta memoria se empleará para el almacenamiento de las imágenes tomadas por la cámara como informacion necesaria para conocer la posicion De los objetos, La comunicación de la micro SD esta basada en la interfaz de 8 pines(reloj, línea de comandos/ Master Out Slave In (MOSI), líneas 4xData / Master In Slave Out (MISO) y 3xPower). El protocolo SPI (Serial Peripheral Interface) es el protocolo de comunicación que admite la tarjeta para la inicialización. El funcionamiento del sistema se basa en 5 módulos: módulo de inicialización de tarjetas (CINM), módulo de lectura de tarjetas (CRM), módulo inactivo (IM),  módulo de escritura de tarjetas (CWM) y módulo de decisión (DM). Junto a los módulos hay una CU (unidad de control) que supervisar y controlar las actividades de cada módulo. Una microSD responde a una serie de comandos de 48 bits, para un almacenamiento dado de un solo bloque o multi-bloques, un solo bloque de almacenamiento posee un ancho de 512 bytes. 

_CAJA (IN/OUT) Driver micro SD_

![](https://github.com/ltherreraro/CubeRubik/blob/master/HW/03GRUPO3/03document/driver%20SD.png)

_CAJA FUNCIONAL (IN/OUT) micro SD_

![](https://github.com/ltherreraro/CubeRubik/blob/master/HW/03GRUPO3/03document/Diagrama%20funcional%20MICRO%20SD.png)


