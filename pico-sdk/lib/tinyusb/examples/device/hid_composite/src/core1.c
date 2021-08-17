#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "hardware/uart.h"
#include "tusb.h"

#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

#include "bsp/board.h"
#include "bsp/rp2040/board.h"

#include "lcd.h"
#include "core1.h"

char core1buf[100];
volatile uint8_t core1flag;

void core1_entry(void)
{
#if 0
	board_led_write(true);
	sleep_ms(500);
	board_led_write(false);
	sleep_ms(500);
#endif

	ps("core1\n");
	while(1){
		if(core1flag){
			ps(core1buf);
			core1flag = 0;
		}
	}
}

