
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include "esp8266/esp8266.h"
#include "esp_wifi.h"
#include "driver/gpio.h"
#include <stdio.h>

#define LEDGPIO GPIO_NUM_2
#define BTNGPIO GPIO_NUM_0

#ifndef ESP32
static os_timer_t resetBtntimer;
#endif

void ioLed(int ena) {
#ifndef ESP32
	gpio_set_level(LEDGPIO, ena ? 1 : 0);
#endif
}

#ifndef ESP32
static void resetBtnTimerCb(void *arg) {
	static int resetCnt=0;
	if (gpio_get_level(BTNGPIO)) {
		resetCnt++;
	} else {
		if (resetCnt>=6) { //3 sec pressed
			esp_wifi_disconnect();
			esp_wifi_set_mode(WIFI_MODE_APSTA); //reset to AP+STA mode
			printf("Reset to AP mode. Restarting system...\n");
//			system_restart(); // TODO: do we want to do this?
		}
		resetCnt=0;
	}
}
#endif


void ioInit() {
#ifndef ESP32
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
//	gpio_output_set(0, 0, (1<<LEDGPIO), (1<<BTNGPIO)); // BTNGPIO is an output??
	gpio_set_direction(BTNGPIO, GPIO_MODE_DEF_INPUT);
	gpio_set_direction(LEDGPIO, GPIO_MODE_DEF_OUTPUT);
	gpio_set_level(LEDGPIO, 0);
	gpio_set_level(BTNGPIO, 0);
	os_timer_disarm(&resetBtntimer);
	os_timer_setfn(&resetBtntimer, resetBtnTimerCb, NULL);
	os_timer_arm(&resetBtntimer, 500, 1);

#endif
}

