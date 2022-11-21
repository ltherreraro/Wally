# RP2040 zephyr example

## Referencias

https://docs.zephyrproject.org/latest/boards/arm/rpi_pico/doc/index.html

https://docs.zephyrproject.org/3.0.0/reference/kconfig/CONFIG_BUILD_OUTPUT_UF2.html

##Pasos proyectos

pasos son para crear apps zephyros:
1. Crear pp
2. compilar
3. flash
%--------------------------crear app---------------------------------------------------------------------
Los archivos base que se pueden copiar de los ejemplos son:
1. Carpeta src
2. CMakeLists.txt	->usualmente no se debe cambiar y aqui va projecto, paquete zephyr , etc
3. prj.conf 		-> si se copia de un ejemplo usualmente no se cambia y debe contener que tipo de configuracion tiene
			ejemplo si se usa gpio entonces tiene CONFIG_GPIO=y y si tiene pwm pues el correpsondiente
4.sample.yml 		-> usualmente tampoco se cambia pero ahi contiene info de los dispositivos usados
Ahora se deben copiar los archivos
1. enveriomente.bash	-> No se cambia nunca, este archivo pone todo lo necesario y si se usa make b antes de activarlo sale 					
			error
2. Makefile		-> No se cambia nunca, este archivo esta enlazado con rp2040.mk que se encuentra en una carpeta anterior
			en la carpeta tools en este archivo se pone en nombre de la board, el pat serial y el archivo dts es
			decir el archivo que se encuentra en boards/rpi_pico.overlay donde se define todos los disposivitos usados
			usando superposicion, a su vez este archivo esta enlazado con el archivo makefile de tools 
Finalmente se debe crear:
1. Una carpeta que se llame boards (si o si se debe llamar asi)
2. Adentro de la carpeta creada (boards) se debe crea un archivo llamado:
rpi_pico.overlay	-> aqui se debe poner todo lo concerniente para enlazar los pines fisico de la tarjeta con las 
			definiciones concernientes de la tarjeta

%-------------------------compilar------------------------------------------------------------------
para genera el .uf2
1. bash environment.bash ejecutar 1 vez en la carpeta de la app que previamente copiamos
2. make b
%-------------------------flash------------------------------------------------------------------
1. Con la tarjeta desconectada presionar el boton fisico de la rpi_pico (bootset) tenerlo presioado
y conectar con el boton presionado la tarjeta al pc esperar 1 seg y soltar el boton
2. esperar hasta que salga la carpeta /media/RPI-RP2
3. Ejecutar el comando make f

******************************************EXTRAS******************************************
--------------------------------------------------------------------------------------------
comando que se ejecuta en make b donde $(BOARD) es rpi_pico y $(DTS_OVERLAY) es donde esta el archivo overlay donde se modificaron o se hizo superposicion de la definicion de los dispositivos

west build -p auto -b $(BOARD) -- -DDTC_OVERLAY_FILE=$(DTS_OVERLAY)

-----------------------------------------------------------------------------------------------------
En el archivo configPin.txt esta como llamar los diferentes pines segun su proposito		
................PWM.........................................................................

#include </home/tatiana/zephyrproject/zephyr/include/zephyr/dt-bindings/pinctrl/rpi-pico-rp2040-pinctrl.h>

/ {
	pwm_leds1 {
		compatible = "pwm-leds";
		pwm_led1: pwm_led_1 {
			status = "okay";
			pwms = <&pwm 1 PWM_MSEC(20) PWM_POLARITY_NORMAL>;
			label = "PWM_LED1";
		};
	};

	aliases {
		pwm-led1 = &pwm_led1;
	};
};


&pwm {
	pinctrl-0 = <&pwm_ch0b_default>;
	pinctrl-names = "default";
	divider-int-0 = <255>;
	status = "okay";
	divider-frac-4 = <255>;
	divider-int-4 = <255>;
};
&pinctrl {
	pwm_ch0b_default: pwm_ch0b_default {
		group1 {
			pinmux = <PWM_0B_P1>;
		};
	};
};
_____________________ viene de zepthyrproject/zephyr:________________________________________________________________
/boards/arm/rpi_pico/rpi_pico.dts y de /dts/binding/gpio_pwm.yaml para saber numero de pwm
pwm_leds {
		compatible = "pwm-leds";
		pwm_led0: pwm_led_0 {
			status = "disabled";
			pwms = <&pwm 9 PWM_MSEC(20) PWM_POLARITY_NORMAL>;
			label = "PWM_LED";
		};
	};

	aliases {
		led0 = &led0;
		watchdog0 = &wdt0;
		pwm-led0 = &pwm_led0;
	};


&pwm {
	pinctrl-0 = <&pwm_ch4b_default>;
	pinctrl-names = "default";
	divider-int-0 = <255>;

/boards/arm/rpi_pico/
	pwm_ch4b_default: pwm_ch4b_default {
		group1 {
			pinmux = <PWM_4B_P25>;
		};
	};
	
	#define PWM_4B_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_PWM) en include/zephyr/dt-bings/pinctrl
.......................................................................................................................
		


