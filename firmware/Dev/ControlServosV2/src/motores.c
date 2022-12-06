#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

#define objeto_servo(x) PWM_DT_SPEC_GET(DT_NODELABEL(servo##x));

const struct pwm_dt_spec servo0 = objeto_servo(0);
const struct pwm_dt_spec servo1 = objeto_servo(1);


#define MINPULSE PWM_USEC(700)
#define MAXPULSE PWM_USEC(2500)

#define FGRADOS(x) PWM_USEC(x*10)+MINPULSE

#define STEP PWM_USEC(100)

#define LED0_NODE DT_ALIAS(sentido10)

static const struct gpio_dt_spec sen10 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
