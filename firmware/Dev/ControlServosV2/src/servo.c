#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

#define objeto_servo(x) PWM_DT_SPEC_GET(DT_NODELABEL(servo##x));

const struct pwm_dt_spec servo0 = objeto_servo(0);
const struct pwm_dt_spec servo1 = objeto_servo(1);
const struct pwm_dt_spec servo2 = objeto_servo(2);
const struct pwm_dt_spec servo3 = objeto_servo(3);
//static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(servo0), min_pulse);
//static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(servo0), max_pulse);

#define MINPULSE PWM_USEC(700)
#define MAXPULSE PWM_USEC(2500)

#define FGRADOS(x) PWM_USEC(x*10)+MINPULSE

#define STEP PWM_USEC(100)

enum direction {
	RIGTH,
	DOWN,
	LEFT,
	UP,
};


void calibracion(int pulsador,int grados, struct pwm_dt_spec servo){
	
	printk("entro en claibra");
	int ret;
	
	ret = pwm_set_pulse_dt(&servo, FGRADOS(grados));
	
	if (ret < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
			return;
	}
	
}

/**
 * @brief 
 * 
 * @param servo escoger servo0, servo1 o servo2
 * @param min_pulse out pulso minimo del servo escogido
 * @param max_pulse out pulso maximo del servo escogido
 */
void min_max_pulse(struct pwm_dt_spec servo, int* min_pulse, int* max_pulse){

	*min_pulse = PWM_USEC(700);
	*max_pulse = PWM_USEC(2500);
	
}


/**
 * @brief Funcion para que funciona para los servos de la tapa escoger la direccion del movimiento
 * 
 * @param dir UP DOWN para servo lamina, LEFT RIGH para servo barra
 * @param servo escoger servo0, servo1, servo2
 */
void servo_tapa(enum direction dir,struct pwm_dt_spec servo){
	
		int ret=-1;
		int minpulse, maxpulse;

		min_max_pulse(servo, &minpulse, &maxpulse);
	
		switch (dir)
		{
		case LEFT:
			ret = pwm_set_pulse_dt(&servo, minpulse);
			break;
		case RIGTH:
			ret = pwm_set_pulse_dt(&servo, maxpulse);
			break;
		case DOWN:
			ret = pwm_set_pulse_dt(&servo, minpulse);
			break;
		case UP:
			ret = pwm_set_pulse_dt(&servo, maxpulse);
			break;
		default:
			printk("Error: direction invalid");
			break;
		}
	
		
		if (ret < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
			return;
		}
	
	
	
}
/**
 * @brief Mueve el servo los grados que se indique
 * 
 * @param grados in, grados a mover
 * @param servo	 in, servo a mover
 */
void movimiento (int grados,struct pwm_dt_spec servo){
	
	int ret;
	
	ret = pwm_set_pulse_dt(&servo, FGRADOS(grados));
	
	if (ret < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
			return;
	}

}

void prueba_fun_camara(int* stop){
	*stop = *stop + 1;

	
}
/**
 * @brief Mueve el servo de la camara constantemente de 0 a 180 y de 180 a 0 hasta que la camara detecta un objeto
 * 
 * @param servo in, escoger el servo
 * @param seg 	in, escoger el tiempo de espera para aumentar los grados
 * @param grados out, indica a que grados encontro el objeto
 */
void servo_camara(struct pwm_dt_spec servo, int seg, int* grados){
	
	int stop;
	enum direction dire = UP;
	
	do
	{
		prueba_fun_camara(&stop);	

		movimiento (*grados,servo);
		printk("grados  %d \n", *grados);
		
		if (dire == DOWN) {
			
			if (*grados <= 0) {
				dire = UP;
				*grados=0;
				
			} else {
				*grados = *grados-10;
			}
		} else {
			
			*grados = *grados + 10;
		
			if (*grados >= 150) {
				dire = DOWN;
				*grados=150;
				
			}
		}

		k_sleep(K_SECONDS(seg));	
	
			
	}while (stop <= 20);
	

}
/**
 * @brief Inicializacion de servos
 * 
 */
void init_servos(){
	servo_tapa(LEFT,servo0);
	servo_tapa(DOWN,servo1);
	
	
};

