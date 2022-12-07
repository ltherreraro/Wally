# zephyrOS rp2040 Control motores carro arduino

## Pines
Motor A
GPIO 16 ALIASES_OVERLEAY led1 -> CONS ctr1A FWD
GPIO 17 ALIASES_OVERLEAY led2 -> CONS ctr2A REV
GPIO 3  ALIASES_OVERLEAY led5 -> CONS enA ENABLE

Motor B
GPIO 14 ALIASES_OVERLEAY led3 -> CONS ctr1B FWD
GPIO 15 ALIASES_OVERLEAY led4 -> CONS ctr2B REV
GPIO 4 ALIASES_OVERLEAY led6 -> CONS enB ENABLE

## Formulas 

### Variables
r radio de la rueda = 3.25cm
d diamentro de la rueda = 6cm
dr distancia de los centros rueda = 14
rr radio de la distancia de centros = 7

### Ecuaciones

Se debe encontrar la relacion entre el perimetro de la distancia de las ruedas y el perimetro de la rueda
ya que posteriormente se usara esta relacion para calcular los giros y las distancias.

P(giro)= 2*pi*dr = 2*3,14*3.25 = 43.98cm
P(rueda)= 2*pi*r = 2*3,14*3.25 = 20.42cm
Relacion = p(giro)/p(rueda) = 43.98/20.41 = 2.15


## Funcionamiento

### Giro
Con la velocidad maxima es decir enviando a enable el valor maximo (255) se debe determinar con esa 
velocidad maxima cuanto ms tardan en dar un solo giro, para esto se realizo una funcion llamada calibracion
que va mostrando en consola los milisegundos y se debe observar en que punto la rueda da un solo giro.

En este caso en particular con enable maximo y motores conectados a 5V se obtuvo que tardo 0.4 seg en 
dar un giro completo, ahora usando la relacion se tendria:

360 grados -> 0.4*2.15

Ahora aplicando una de 3 siemple se puede usar el tiempo que tarda en realizar los diferentes angulo de giro
llegando a la siguiente formula donde tgirocom es el tiempo de giro completo es decir 0.4 s y x son los grados que se quiere girar el carro.
``
#define PGRADOS(x) K_SECONDS(2.15*TGIROCOM*(x/360))
``
### Distancia

De manera similar se realizo la distancia y sabiendo que la rueda tiene 2.15 cm de radio en 0.4 seg habra recorrido 2.15 cm
se obtuvo la siguiente formula para obtener la distancia en cm.

```
#define PCENTI(x) K_SECONDS(TGIROCOM/2.15)
```

## Implementacion

Finalmente se crecaron dos funciones la primera es giro que recibe 3 parametros direccion del motor es un enum que puede ser
LEFTG o RIGHG indicando el sentido lo que internamente enviara la combinacion  10 o 01 en los pines correspondientes a
fwd y rwd para determinar en que sentido giran las ruedas es decir si se quiere girar a la derecha el motor de situado a la derecha giraria hacia atras y el motor de la izquierda adelante.

El otro parametro que recibe es cuantos grados se quiere girar en la direccion dada usando la formula explicada anteriormente
y finalmente la velocidad.

```
void giro(enum direction_mot dir, int grados, int vel)
``

Por otro lado esta la funcion distancia que recibe 3 parametros la direccion en la que se quiere mover el carro, se pueden usar
los valores FWD para adelante y RWD para atras, la otra entrada es velocidad y finalmente los cm que se quiere recorrer en la 
direccion indicada
```
void distancia(enum direction_mot dir, int vel, int cm)
```
