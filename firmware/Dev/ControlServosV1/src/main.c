/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based servomotor control
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

static const struct pwm_dt_spec servo = PWM_DT_SPEC_GET(DT_NODELABEL(servo0));
static const uint32_t min_pulse = DT_PROP(DT_NODELABEL(servo0), min_pulse);
static const uint32_t max_pulse = DT_PROP(DT_NODELABEL(servo0), max_pulse);

static const struct pwm_dt_spec servo1 = PWM_DT_SPEC_GET(DT_NODELABEL(servo1));
static const uint32_t min_pulse1 = DT_PROP(DT_NODELABEL(servo1), min_pulse);
static const uint32_t max_pulse1 = DT_PROP(DT_NODELABEL(servo1), max_pulse);
#define STEP PWM_USEC(100)
#define STEP1 PWM_USEC(100)
enum direction {
	DOWN,
	UP,
};
enum direction1 {
	DOWN1,
	UP1,
};


void main(void)
{
	uint32_t pulse_width = min_pulse;
	uint32_t pulse_width1 = min_pulse1;
	enum direction dir = UP;
	enum direction1 dir1 = UP1;
	int ret;
	int ret1;
	

	printk("Servomotor control\n");

	if (!device_is_ready(servo.dev)) {
		printk("Error: PWM device %s is not ready\n", servo.dev->name);
		return;
	}
	if (!device_is_ready(servo1.dev)) {
		printk("Error: PWM device %s is not ready\n", servo1.dev->name);
		return;
	}

	while (1) {
		ret = pwm_set_pulse_dt(&servo, pulse_width);
		ret1 = pwm_set_pulse_dt(&servo1, pulse_width);
		if (ret < 0) {
			printk("Error %d: failed to set pulse width\n", ret);
			return;
		}
		if (ret1 < 0) {
			printk("Error %d: failed to set pulse width\n", ret1);
			return;
		}
		if (dir == DOWN) {
			if (pulse_width <= min_pulse) {
				dir = UP;
				pulse_width = min_pulse;
			} else {
				pulse_width -= STEP;
			}
		} else {
			pulse_width += STEP;

			if (pulse_width >= max_pulse) {
				dir = DOWN;
				pulse_width = max_pulse;
			}
		}
		if (dir == DOWN1) {
			if (pulse_width1 <= min_pulse1) {
				dir1 = UP1;
				pulse_width1 = min_pulse1;
			} else {
				pulse_width1 -= STEP1;
			}
		} else {
			pulse_width1 += STEP1;

			if (pulse_width1 >= max_pulse1) {
				dir1 = DOWN1;
				pulse_width1 = max_pulse1;
			}
		}

		k_sleep(K_SECONDS(1));
	}
}
