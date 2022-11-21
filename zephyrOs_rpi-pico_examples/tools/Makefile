PATH_TOOLS?=
BOARD?=
DTS_OVERLAY?=
SERIAL?=
BAUD?=115200
# ADDRESS?=0x40000000
SERIALMONITOR?=picocom
SERIALMONITOR_GUI?=gtkterm

commands:
	@echo "make build [b]: compilar y enlazar"
	@echo "make flash [f]: flashear memoria del dispositivo"
	@echo "make terminal [t]: ver salida por puerto serial"
	@echo "make clean [c]: borrar la carpeta build (proyecto compilado y enlazado) "
	@echo "make environment: crea las variables de entorno para ubicar las herramientas de zephyr"
	@echo "make clean-cache-zephyr [ccz]: limpiar cache de compilaciones con zephyr"
	@echo "make compile [cc]: compilar"

cc:compile
b:build
f:flash
t:terminal
gt:gtkterm
c:clean
ccz:clean-cache-zephyr
help:commands

compile:
	rm -rf build
	. ./environment.bash && \
	cmake -B build -DBOARD=$(BOARD) \
	-DDTC_OVERLAY_FILE=$(DTS_OVERLAY) ./

build:
	. ./environment.bash && \
	west build -p auto -b $(BOARD) -- -DDTC_OVERLAY_FILE=$(DTS_OVERLAY) . || \
		(echo "\nFalla la construcción del firmware\n")

flash:
	. ./environment.bash && \
	west flash || \
		(echo "\nNo fue posible flashear el dispositivo\n")

terminal:
	$(SERIALMONITOR) $(SERIAL) -b $(BAUD) || \
		(printf "No tiene instalado el monitor serial picocom, puede instalarlo como sigue:\nsudo apt install picocom")

gtkterm:
	$(SERIALMONITOR_GUI) --port $(SERIAL) --speed $(BAUD) || \
		(printf "No tiene instalado el monitor serial picocom, puede instalarlo como sigue:\nsudo apt install gtkterm")

clean:
	rm -rf build/

clean-cache-zephyr:
	rm -rf ~/.cache/zephyr/

# compile:
# 	make -C build/ -f Makefile all

# litex_term: build/zephyr/zephyr.bin
# 	@echo "Para salir oprime ctrl+cbc (sin soltar el ctrl)"
# 	litex_term $(SERIAL) --kernel build/zephyr/zephyr.bin \
# 		--kernel-adr $(ADDRESS) \
# 		--speed $(BAUD)

.PHONY: build remove-build
