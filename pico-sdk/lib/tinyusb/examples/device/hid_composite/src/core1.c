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

uint8_t flag = 0; //0: no task , 1: task

struct cpu1_task task;

void core1_entry(void)
{
	while(1){
		board_led_write(true);
		sleep_ms(500);
		board_led_write(false);
		sleep_ms(500);

		if(flag){
			if(task.func){
				task.func();
			}

			flag = 0;
		}
	}
}

