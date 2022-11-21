# zephyrOS rp2040 pwm
Se programo un pwm que varia el ancho de pulso desde el minimo hasta llegar al maximo en el gpio 1

## Deficiones de pines
En el archivo boards/rpi-pico.overlay se encuentra configurado el pwm 0 que corresponde al gpio 1 y se le puso un alias que es pwm_led1 que sera el que se llame en el archivo /src/main.c 

## Conexiones
En la imagen se ve las conexiones para ver el funcionamiento del codigo
![](https://github.com/ltherreraro/Wally/blob/main/Imagenes/conexion_pwm.png))


