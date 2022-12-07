/**
 * @file ultrasonido.c
 * @author {Maicol Fontecha} ({mdfontechad})
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "ultrasonido.h"
#include <stdio.h>

static const struct gpio_dt_spec Echo1 = GPIO_DT_SPEC_GET_OR(ECHO_PIN5, gpios, {0});
static const struct gpio_dt_spec Trig1 = GPIO_DT_SPEC_GET_OR(TRIG_PIN6, gpios, {0});
static const struct gpio_dt_spec Echo2 = GPIO_DT_SPEC_GET_OR(ECHO_PIN7, gpios, {0});
static const struct gpio_dt_spec Trig2 = GPIO_DT_SPEC_GET_OR(TRIG_PIN8, gpios, {0});
static const struct gpio_dt_spec Echo3 = GPIO_DT_SPEC_GET_OR(ECHO_PIN9, gpios, {0});
static const struct gpio_dt_spec Trig3 = GPIO_DT_SPEC_GET_OR(TRIG_PIN10, gpios, {0});
static const struct gpio_dt_spec Echo4 = GPIO_DT_SPEC_GET_OR(ECHO_PIN18, gpios, {0});
static const struct gpio_dt_spec Trig4 = GPIO_DT_SPEC_GET_OR(TRIG_PIN26, gpios, {0});

int ConfGpio5;
int ConfGpio6;
int ConfGpio7;
int ConfGpio8;
int ConfGpio9;
int ConfGpio10;
int ConfGpio18;
int ConfGpio26;
bool trig1signal;
/**
 * @brief Calcula la distancia del objeto
 * 
 * @param distance out, Indica la distancia en cm
 */
void getDistance(float* distance)
{

    if (!device_is_ready(Echo1.port) || !device_is_ready(Trig1.port) || !device_is_ready(Echo2.port) || !device_is_ready(Trig2.port) || !device_is_ready(Echo3.port) || !device_is_ready(Trig3.port) || !device_is_ready(Echo4.port) || !device_is_ready(Trig4.port))
    {
        return;
    }

    ConfGpio5 = gpio_pin_configure_dt(&Echo1, GPIO_INPUT);
    ConfGpio6 = gpio_pin_configure_dt(&Trig1, GPIO_OUTPUT_ACTIVE);
    ConfGpio7 = gpio_pin_configure_dt(&Echo2, GPIO_INPUT);
    ConfGpio8 = gpio_pin_configure_dt(&Trig2, GPIO_OUTPUT_ACTIVE);
    ConfGpio9 = gpio_pin_configure_dt(&Echo3, GPIO_INPUT);
    ConfGpio10 = gpio_pin_configure_dt(&Trig3, GPIO_OUTPUT_ACTIVE);
    ConfGpio18 = gpio_pin_configure_dt(&Echo4, GPIO_INPUT);
    ConfGpio26 = gpio_pin_configure_dt(&Trig4, GPIO_OUTPUT_ACTIVE);

    if (ConfGpio5 < 0 || ConfGpio6 < 0 || ConfGpio7 < 0 || ConfGpio8 < 0 || ConfGpio9 < 0 || ConfGpio10 < 0 || ConfGpio18 < 0 || ConfGpio26 < 0)
    {
        return;
    }

    while (1)
    {
        uint32_t stop_time = 0;
        uint32_t start_time = 0;
        uint32_t cycles_spent = 0;
        float time;
        
        int val;
        int aux = 0;
        // TRIGG SIGNAL , pulso de 10u
        trig1signal = 0;
        gpio_pin_set_dt(&Trig1, !trig1signal);
        uscounter(10);
        gpio_pin_set_dt(&Trig1, trig1signal);

        // Echo lecture
        start_time = k_cycle_get_32(); // tiempo inicial
        while (1)
        {

            val = gpio_pin_get_dt(&Echo1);

            if (gpio_pin_get_dt(&Echo1) == 0)
            {
                stop_time = k_cycle_get_32();
                cycles_spent = stop_time - start_time;
                if (cycles_spent > 1064000)
                {
                    printk("entre aca %d \n", cycles_spent);
                    break; // si es más de 3 metros, busque otra lectura.
                }
                continue;
            }
            else
            {
                start_time = k_cycle_get_32(); // reestableciendo el start time.
                while (gpio_pin_get_dt(&Echo1) == 1)
                {
                    stop_time = k_cycle_get_32();
                    cycles_spent = stop_time - start_time; // contando los ciclos
                }
                printk("Lectura en ciclos: %d<<\n ", cycles_spent);
                time = cycles_spent * 0.00000000751 / 2;
                *distance = time * 343.3 * 100;

                printf("distancia en cm: %.3f cm <<", *distance);
                break;
            }
        }

        if (ConfGpio5 < 0 || ConfGpio6 < 0 || ConfGpio7 < 0 || ConfGpio8 < 0 || ConfGpio9 < 0 || ConfGpio10 < 0 || ConfGpio18 < 0 || ConfGpio26 < 0)
        {
            printk("fail");
            return;
        }

        k_msleep(1000);
    }
}


/**
 * @brief 
 * 
 * @param tiempo en milisegundos 
 */
void uscounter(uint8_t us)
{
	uint32_t stop_time = 0;
	uint32_t start_time = 0;
	uint32_t cycles_spent = 0;
	start_time = k_cycle_get_32();
	do
	{
		stop_time = k_cycle_get_32();
		cycles_spent = stop_time - start_time;
	} while (cycles_spent <= 133 * us); // 133 ciclos es un us.

	/*//clock-frequency = <133000000>;
	  //1 ciclo : 00000000751s
	printk("ciclos usados: %d <<<\n", cycles_spent);
	printk("start: %d <<<\n", start_time);
	printk("stop:  %d <<<\n", stop_time); */
}

//###definición funciones usadas

/*static inline int gpio_pin_set_dt(const struct gpio_dt_spec *spec, int value)
{
	return gpio_pin_set(spec->port, spec->pin, value);
}*/

/*  Current hardware clock up-counter (in cycles).
static inline uint32_t k_cycle_get_32(void)
{
return arch_k_cycle_get_32();
}      */