/**
 * @file main.c
 * @author {Lisseth Herrera} ({ltherreraro})
 * @brief 
 * @version 0.1
 * @date 2022-12-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include "servo.c"
#include "motores.c"
/**
 * @brief 
 * 
 */

void demo_servos(){
	init_servos();
	
	k_sleep(K_SECONDS(10));
	servo_tapa(RIGTH,servo0);
	k_sleep(K_SECONDS(10));
	servo_tapa(UP,servo1);
	k_sleep(K_SECONDS(10));
	servo_tapa(DOWN,servo1);
	k_sleep(K_SECONDS(10));
	servo_tapa(LEFT,servo0);
	k_sleep(K_SECONDS(10));
	
	//servo camara
	
};





void main(void)
{
	
	int gradoscamara;
	int segesperacamara = 1;
	//servo_camara(servo1, segesperacamara, &gradoscamara);
	//printk("en %d, esta el objeto", gradoscamara);
	//servo_tapa(RIGTH,servo2);
	//servo_tapa(LEFT,servo0);
	//servo_tapa(RIGTH,servo1);
	//servo_tapa(LEFT,servo3);
	//demo_servos();
	//calibracion(1,FGRADOS(90),servo0);
	//calibracion(1,FGRADOS(90),servo2);
	/*movimiento(FGRADOS(0), servo0);
	movimiento(FGRADOS(180), servo1);
	movimiento(FGRADOS(0), servo2);
	movimiento(FGRADOS(180), servo3);
	servo_tapa(RIGTH,servo2);
	servo_tapa(LEFT,servo0);
	servo_tapa(RIGTH,servo1);
	servo_tapa(LEFT,servo3);*/
	
	printk("prueba");
	int ret;
	
	ret = pwm_set_pulse_dt(&servo2, PWM_USEC(700));
	
	if (ret < 0) {
		printk("Error %d: failed to set pulse width\n", ret);
			return;
	}else{
		printk("ok");
	}
	servo_tapa(LEFT,servo0);
	servo_tapa(RIGTH,servo1);
	
	
	
	
	
	

	
	
}
