/**
 * @file motores.c
 * @author {Lisseth Herrera} ({ltherreraro})
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>


/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* 
Motor A
GPIO 16 ALIASES_OVERLEAY led1 -> CONS ctr1A FWD
GPIO 17 ALIASES_OVERLEAY led2 -> CONS ctr2A REV
GPIO 3  ALIASES_OVERLEAY led5 -> CONS enA ENABLE

Motor B
GPIO 14 ALIASES_OVERLEAY led3 -> CONS ctr1B FWD
GPIO 15 ALIASES_OVERLEAY led4 -> CONS ctr2B REV
GPIO 4 ALIASES_OVERLEAY led6 -> CONS enB ENABLE

ADELANTE
   gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
	gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_HIGH);
	gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_LOW);
	gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_HIGH);
    gpio_pin_set(enA.port, PINEA , GPIO_ACTIVE_HIGH);
	gpio_pin_set(enB.port, PINEB, GPIO_ACTIVE_HIGH);

FORMULAS:
r radio de la rueda = 3.25cm
d diamentro de la rueda = 6cm
dr distancia de los centros rueda = 14
rr radio de la distancia de centros = 7

P(giro)= 2*pi*dr = 2*3,14*3.25 = 43.98cm
P(giro)= 2*pi*r = 2*3,14*3.25 = 20.42cm
Relacion = p(giro)/p(rueda) = 43.98/20.41 = 2.15

5V
vel maxima  tiempo de 5.5 mili sef func PWM_MSEC(5.5) giro completo
360 grados -> 0.4*2.15
12V
velocidad(0.5,0.5,MOTA);
velocidad(0.5,0.5,MOTB);
stop 0.4MSEC


*/
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define LED4_NODE DT_ALIAS(led4)
#define LED5_NODE DT_ALIAS(led5)
#define LED6_NODE DT_ALIAS(led6)

#define PINC1A DT_GPIO_PIN(LED1_NODE, gpios)
#define PINC2A DT_GPIO_PIN(LED2_NODE, gpios)
#define PINC1B DT_GPIO_PIN(LED3_NODE, gpios)
#define PINC2B DT_GPIO_PIN(LED4_NODE, gpios)
#define PINEA DT_GPIO_PIN(LED5_NODE, gpios)
#define PINEB DT_GPIO_PIN(LED6_NODE, gpios)

static const struct gpio_dt_spec ctr1A = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec ctr2A = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec ctr1B = GPIO_DT_SPEC_GET(LED3_NODE, gpios);
static const struct gpio_dt_spec ctr2B = GPIO_DT_SPEC_GET(LED4_NODE, gpios);


static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
static const struct pwm_dt_spec pwm_led1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));
#define MIN_PERIOD PWM_SEC(1U) / 128U
#define MAX_PERIOD PWM_SEC(1U)
//#define MIN_PERIOD PWM_USEC(700)
//#define MAX_PERIOD PWM_USEC(2500)
#define TGIROCOM 0.4
#define PGRADOS(x) K_SECONDS(2.15*TGIROCOM*(x/360))
#define PCENTI(x) K_SECONDS(TGIROCOM/2.15)
/**
 * @brief Direccion de los motores
 * 
 */
enum direction_mot {
	RIGTHG,
	FWD,
	LEFTG,
	RWD,
};
/**
 * @brief motor a implementar
 * 
 */
enum motor {
	MOTA,
	MOTB,
};

/**
 * @brief Inicia los puertos de los motores y  los pone todo en LOW
 * 
 */
void inicio_motores(){
  	int ret, ret1, ret2, ret3, ret4, ret5;
	int dr1a, dr2a, dr1b, dr2b;  
	int d0, d1;
	d0 = device_is_ready(pwm_led0.dev);
	d1 = device_is_ready(pwm_led1.dev);

	if (!d0 || !d1 ) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
			   printk("Error: PWM device %s is not ready\n",
		       pwm_led1.dev->name);
		return;
	}


	dr1a = device_is_ready(ctr1A.port);
	dr2a = device_is_ready(ctr2A.port);
	dr1b = device_is_ready(ctr1B.port);
	dr2b = device_is_ready(ctr2B.port);
    

	if (!dr1a || !dr2a || !dr1b ||!dr2b ) {
		return;
	}
	

	ret = gpio_pin_configure_dt(&ctr1A, GPIO_OUTPUT_ACTIVE);
	ret1 = gpio_pin_configure_dt(&ctr2A, GPIO_OUTPUT_ACTIVE);
	ret2 = gpio_pin_configure_dt(&ctr1B, GPIO_OUTPUT_ACTIVE);
	ret3 = gpio_pin_configure_dt(&ctr2B, GPIO_OUTPUT_ACTIVE);
        
	
	if (ret < 0 || ret1 < 0 ||ret2 < 0 ||ret3 < 0 ||ret4 < 0 ||ret5 < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
		printk("Error %d: failed to set pulse width\n", ret1);
		printk("Error %d: failed to set pulse width\n", ret2);
		printk("Error %d: failed to set pulse width\n", ret3);
        printk("Error %d: failed to set pulse width\n", ret4);
		printk("Error %d: failed to set pulse width\n", ret5);

		return;
	}
	
	

	gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
	gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_LOW);
	gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_LOW);
	gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_LOW);
    

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}
        if (!device_is_ready(pwm_led1.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}
}


/**
 * @brief 
 * 
 * @param dir  in, Se debe indicar hacia que direccion se realizara el giro LEFT, RIGH
 * @param grados in, Se indica en numero entero los grados que se quiere girar ejemplo 10 si son 10 grados
 * @param vel Se in, indica en numero entero la velocidad del grio
 */
void giro(enum direction_mot dir, int grados, int vel){

    switch (dir)
    {
    case LEFTG:
        gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_LOW);
		velocidad(vel,vel,MOTA);
		velocidad(vel,vel,MOTB);
		k_sleep(PGRADOS(grados));
		paradatotal();
        break;
    case RIGTHG:
        gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_HIGH);
		velocidad(vel,vel,MOTA);
		velocidad(vel,vel,MOTB);
		k_sleep(PGRADOS(grados));
		paradatotal();
        break;
    default:
        break;
    }
}

/**
 * @brief Para los dos motores, pone en bajo todos los pines
 * 
 */
void paradatotal(){
		gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr1A.port, PINC1B , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2B, GPIO_ACTIVE_LOW);

}

/**
 * @brief 
 * 
 * @param dir in, Se indica en que direccion se quiere mover adelante FWD o atras RWD 
 * @param vel in, Se indica la velocidad a la que se quiere mover en numeros enteros
 * @param cm in, Se indica la distancia en cm que se quiere recorrer
 */
void distancia(enum direction_mot dir, int vel, int cm){

	switch (dir)
	{
	case FWD:
		gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_HIGH);
		velocidad(vel,vel,MOTA);
		velocidad(vel,vel,MOTB);
		k_sleep(PCENTI(cm));
		paradatotal();
		break;
	case RWD:
		gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_LOW);
		velocidad(vel,vel,MOTA);
		velocidad(vel,vel,MOTB);
		k_sleep(PCENTI(cm));
		paradatotal();

		break;
	
	default:
		break;
	}

}
/**
 * @brief 
 * 
 * @param a Periodo
 * @param b Pulso
 * @param mot se debe escoger el motor MOTORA o MOTORB
 */
void velocidad (int a, int b, enum motor mot){
	switch (mot)
	{
	case MOTA:
		pwm_set_dt(&pwm_led0, PWM_MSEC(a), PWM_MSEC(a));
		break;
	case MOTB:
		pwm_set_dt(&pwm_led1, PWM_MSEC(a), PWM_MSEC(a));
		break;
	default:
		break;
	}
	
    
}

/**
 * @brief Funcion para calibrar los motores, se realiza variacion de tiempos de parada
 * 		  de tal manera que cuando de un giro completo se detenga y ese valor de segundos 
 *        es el que se usa como TGIROCOM
 * 
 */
void calibracio_mot(){
	int seg;
	int i;
	for (i = 1; i < 10; i++)
	{
		gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_HIGH);
		gpio_pin_set(ctr1B.port, PINC1B , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2B.port, PINC2B, GPIO_ACTIVE_HIGH);
		velocidad(5.5,5.5,MOTA);
		velocidad(5.5,5.5,MOTB);

		seg = i/10;
		k_sleep(K_SECONDS(seg));
		printk("la i:%d\n",i);
		printk("segunods:%d\n",seg);
		
		gpio_pin_set(ctr1A.port, PINC1A , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2A, GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr1A.port, PINC1B , GPIO_ACTIVE_LOW);
		gpio_pin_set(ctr2A.port, PINC2B, GPIO_ACTIVE_LOW);

		k_sleep(K_SECONDS(5));
	}
	
}
