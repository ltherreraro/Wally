# zephyrOS rp2040 Servo motores

## Pine

- GPIO 0  ALIASES_OVERLEAY servo0 -
- GPIO 1 ALIASES_OVERLEAY servo 1

## Funcionamiento

### Movimiento
Se tiene la funcion movimiento que recibe como parametros grados y el servo a mover (servo0 o servo1) y se mueve los grados solicitados usando la funcion set pulse de zephyr 
```
movimiento (int grados,struct pwm_dt_spec servo)
```

Se realizado una regla de 3 simple para terminar la relacion entre el ancho de pulso y el giro como se muestr a continuacion donde
x corresponde a los grados que se quiere mover y MINPULSE al pulso minimo del motor

```
#define FGRADOS(x) PWM_USEC(x*10)+MINPULSE
```

Se debe tener presente que se debe calibrar previamente ya que los motores debido al prototipo del carton no necesariamiente
pueden usar el ancho de pulso minimo dado por datasheet de ```PWM_USEC(700)``` por ejemplo en el caso del engranaje
que entra y saca el brazo el giro no puede ser entre 0 y 180 debido al tamaño de los engranajes.

### Servomotor de la camara

Se realizo una funcion que recibe como parametro el servo que va a mover la camara, los segundos que son el tiempo que tardara entre cambio de giro y esta funciona tiene como salida los grados que se movio hasta que se detecto un objeto, en su interior tiene un ciclo for que va moviendo la camara entre 0 y 180 al llegar a 180 grado regresa hasta 0, hasta que la camara le indique
que detecto un objeto, se mueve 10 grados y se demora ahi el tiempo que se indique en segundos.

```
servo_camara(struct pwm_dt_spec servo, int seg, int* grados)
```

### Servomotor del brazo

Se tiene dos servo motores uno que entra y saca el brazo que se mueve en direccion x y otro que levanta  el brazo en direccion y
se tiene una funcion para realizar este movimiento. Recibe el servo que se va a mover y la direccion del movimiento, LEFT RIGHT en el caso del servo que se mueve en el eje X y UP DOWN en el caso del servo que se mueve en direccion y.

```
void servo_tapa(enum direction dir,struct pwm_dt_spec servo){
```
Posteriormente se debe crear otra funcion que realice el control y restringa los movimientos para un uso correcto del brazo
