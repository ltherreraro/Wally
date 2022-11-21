#!/bin/bash -e
#						 ↑
# debug [-x -v]:[complete, abbreviated]
# Brief:	agregar variables de entorno para proyecto con zephyr
# Author: Johnny Cubides
# e-mail: jgcubides@gmail.com
# date: Monday 21 September 2020
# source zephyr-env.sh
status=$?

# foreground
BLACK=`tput setaf 0`
RED=`tput setaf 1`
GREEN=`tput setaf 2`
YELLOW=`tput setaf 3`
BLUE=`tput setaf 4`
MAGENTA=`tput setaf 5`
CYAN=`tput setaf 6`
WHITE=`tput setaf 7`
NC=`tput setaf 7`
# background
BLACKB=`tput setab 0`
REDB=`tput setab 1`
GREENB=`tput setab 2`
YELLOWB=`tput setab 3`
BLUEB=`tput setab 4`
MAGENTAB=`tput setab 5`
CYANB=`tput setab 6`
WHITEB=`tput setab 7`
NCB=`tput setab 0`

# if [[ -d ~/zephyr-sdk-0.14.1/ ]];
# then
#   export ZEPHYR_SDK_INSTALL_DIR=~/zephyr-sdk-0.14.1
# elif [[ -d ~/zephyr-sdk-0.13.2/ ]];
# then
#   export ZEPHYR_SDK_INSTALL_DIR=~/zephyr-sdk-0.13.2
# else
#   echo "No fue posible localizar el ZEPHYR_SDK_INSTALL_DIR"
#   exit 1 # terminate and indicate error
# fi

if [[ -L ~/zephyr-sdk ]]; then
  export ZEPHYR_SDK_INSTALL_DIR=~/zephyr-sdk
else
  printf "${RED}No fue posible localizar el enlace simbólico del sdk de zephyr\n\n"
  printf "${CYAN}Solución: instale el SDK de zephyr y cree un enlace simbólico, ejemplo:\n\n"
  printf "${CYAN}ln -sr ~/zephyr-sdk-0.14.1 ~/zephyr-sdk ${NC}\n\n"
  printf "${CYAN}Para instalar el SDK visite el sitio: https://docs.zephyrproject.org/latest/develop/getting_started/index.html\n${NC}"
  return
fi

default() {
  echo '#!/bin/bash
export PATH=$PATH:$HOME/.local/bin/
export ESPRESSIF_TOOLCHAIN_PATH="${HOME}/.espressif/tools/zephyr"
export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk
export ZEPHYR_BASE=$HOME/zephyrproject/zephyr
export ESPRESSIF_TOOLCHAIN_PATH=$HOME/.espressif/tools/zephyr
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr' > environment.bash
  source  environment.bash

  printf "${GREEN}Variebles exportadas para zephyr en la variante compatible con ARM${NC}\n\
Actención: si buscabas otra variante como por ejemplo espressif ejecuta el comando ${CYAN}. zephyr -h ${NC}para más opciones\n"
}

espressif() {
  echo '#!/bin/bash
export PATH=$PATH:$HOME/.local/bin/
#export ESPRESSIF_TOOLCHAIN_PATH="${HOME}/.espressif/tools/zephyr"
export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk
export ZEPHYR_BASE=$HOME/zephyrproject/zephyr
#export ZEPHYR_TOOLCHAIN_VARIANT=espressif
export IDF_PATH=$HOME/zephyrproject/modules/hal/espressif' > environment.bash
  # source  environment.bash
  printf "${GREEN}Variables exportadas para zephyr en la variante compatible con espressif ESP32${NC}\n"
}

# Permite guardar información acerca de comandos usados
if [ "$1" = "esp" ] || [ "$1" = "esp32" ];
then
  espressif
# elif [ "$1" = "def" ] || [ "$1" = "" ];
elif [ "$1" = "def" ];
then
  default
else
  printf "Help for this command zephyr-env.sh\n"
  printf "\tzephyr-env.sh ${YELLOW}commands${NC} options\n"
  printf "\t[${YELLOW}commands${NC}]\n"
  printf "\t\t${YELLOW}def${NC}\tCompatible con arm\n"
  printf "\t\t${YELLOW}esp, esp32${NC}\tZephyr variante para esp32\n"
  printf "\t\t${YELLOW}-h,--help${NC}\tAyuda\n"
  printf "\nRegards Johnny.\n"
fi

