This is an example of how to use libesphttpd with the Espressif FreeRTOS SDK. 


The original master repo of this code is http://git.spritesserver.nl/esphttpd-freertos.git/ , 
but it's also mirrored at https://github.com/Spritetm/esphttpd-freertos .

This version was forked to provide updates for the esp8266 Espressif libraries found here:
https://github.com/espressif/ESP8266_RTOS_SDK

Development is being done on linux...

Basic instructions for getting things going:
git clone https://github.com/house-mouse/esphttpd-freertos.git
cd esphttpd-freertos
git submodule update --init --recursive
cd esp8266_rtos_toolchain
source setpath # You will need to do this from every shell you want to have access to the compiler
cd ../esphttpd
make
make flash


