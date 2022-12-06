PATH_TOOLS?=

BOARD=rpi_pico
DTS_OVERLAY?=./boards/rpi_pico.overlay
SERIAL?=/dev/ttyUSB0
include ../tools/Makefile
environment:
	/bin/bash $(PATH_TOOLS)/zephyr-env.sh default

flash:
	cp build/zephyr/zephyr.uf2 /media/maik/RPI-RP21/
