# zephyrOS rp2040 servo example

Se programo un pwm que variara entre 0 grados y 180 de pasos pequeños en un ciclo

## Deficiones de pines
En el archivo boards/rpi-pico.overlay se encuentra configurado en pwm 0 pero asociado a un serco que corresponde a el gpio 1 y se le puso un alias que es servo que sera el que se llame en el archivo /src/main.c 

## Conexiones
En la imagen se ve las conexiones para ver el funcionamiento del codigo
![](https://github.com/ltherreraro/Wally/blob/main/Imagenes/conexion_servo.png))

