/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "hardware/uart.h"
#include "tusb.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/binary_info.h"
#include "pico/unique_id.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "hardware/adc.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

#include "bsp/board.h"
#include "bsp/rp2040/board.h"

#include "usb_descriptors.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+
/* From https://www.kernel.org/doc/html/latest/input/gamepad.html
          ____________________________              __
         / [__ZL__]          [__ZR__] \               |
        / [__ TL __]        [__ TR __] \              | Front Triggers
     __/________________________________\__         __|
    /                                  _   \          |
   /      /\           __             (N)   \         |
  /       ||      __  |MO|  __     _       _ \        | Main Pad
 |    <===DP===> |SE|      |ST|   (W) -|- (E) |       |
  \       ||    ___          ___       _     /        |
  /\      \/   /   \        /   \     (S)   /\      __|
 /  \________ | LS  | ____ |  RS | ________/  \       |
|         /  \ \___/ /    \ \___/ /  \         |      | Control Sticks
|        /    \_____/      \_____/    \        |    __|
|       /                              \       |
 \_____/                                \_____/

     |________|______|    |______|___________|
       D-Pad    Left       Right   Action Pad
               Stick       Stick

                 |_____________|
                    Menu Pad

  Most gamepads have the following features:
  - Action-Pad 4 buttons in diamonds-shape (on the right side) NORTH, SOUTH, WEST and EAST.
  - D-Pad (Direction-pad) 4 buttons (on the left side) that point up, down, left and right.
  - Menu-Pad Different constellations, but most-times 2 buttons: SELECT - START.
  - Analog-Sticks provide freely moveable sticks to control directions, Analog-sticks may also
  provide a digital button if you press them.
  - Triggers are located on the upper-side of the pad in vertical direction. The upper buttons
  are normally named Left- and Right-Triggers, the lower buttons Z-Left and Z-Right.
  - Rumble Many devices provide force-feedback features. But are mostly just simple rumble motors.
 */

// Type Defines
// Enumeration for joystick buttons.
typedef enum {
	SWITCH_Y       = 0x01,
	SWITCH_B       = 0x02,
	SWITCH_A       = 0x04,
	SWITCH_X       = 0x08,
	SWITCH_L       = 0x10,
	SWITCH_R       = 0x20,
	SWITCH_ZL      = 0x40,
	SWITCH_ZR      = 0x80,
	SWITCH_SELECT  = 0x100,
	SWITCH_START   = 0x200,
	SWITCH_LCLICK  = 0x400,
	SWITCH_RCLICK  = 0x800,
	SWITCH_HOME    = 0x1000,
	SWITCH_CAPTURE = 0x2000,
} JoystickButtons_t;

// Joystick HID report structure. We have an input and an output.
typedef struct {
	uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
	uint8_t  HAT;    // HAT switch; one nibble w/ unused nibble
	uint8_t  LX;     // Left  Stick X
	uint8_t  LY;     // Left  Stick Y
	uint8_t  RX;     // Right Stick X
	uint8_t  RY;     // Right Stick Y
	uint8_t  VendorSpec;
} USB_JoystickReport_Input_t;

// The output is structured as a mirror of the input.
// This is based on initial observations of the Pokken Controller.
typedef struct {
	uint16_t Button; // 16 buttons; see JoystickButtons_t for bit mapping
	uint8_t  HAT;    // HAT switch; one nibble w/ unused nibble
	uint8_t  LX;     // Left  Stick X
	uint8_t  LY;     // Left  Stick Y
	uint8_t  RX;     // Right Stick X
	uint8_t  RY;     // Right Stick Y
} USB_JoystickReport_Output_t;

uint32_t tret = 0;
static void send_hid_report(void)
{
	static bool jflag = false;
	USB_JoystickReport_Input_t report = {0};

	if(board_millis() < 10000){
		return;
	}

	// use to avoid send multiple consecutive zero report for keyboard
	if ( !tud_hid_ready() ) {
		tret++;
		if(tret > 100000){
			printf("tret\n");
			if ( tud_suspended() )
			{
				tud_remote_wakeup();
				printf("wakeup\n");
				return;
			}

			tret = 0;
		}
	}

	report.LX = 128;
	report.LY = 128;
	report.RX = 128;
	report.RY = 128;

	if(jflag){
		report.Button |= SWITCH_A;
		printf("A+\n");
	}else{
		printf("none\n");
	}
	jflag = !jflag;

	tud_hid_report(0, &report, sizeof(report));
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t itf, uint8_t const* report, uint8_t len)
{
	(void) itf;
	(void) len;

	//printf("%s\n",__func__);
	//send_hid_report();
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
	// TODO not Implemented
	(void) itf;
	(void) report_id;
	(void) report_type;
	(void) buffer;
	(void) reqlen;

	printf("%s\n",__func__);
	return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
	// TODO set LED based on CAPLOCK, NUMLOCK etc...
	(void) itf;
	(void) report_id;
	(void) report_type;
	(void) buffer;
	(void) bufsize;
	printf("%s\n",__func__);
}
static repeating_timer_t timer_joystick;
static repeating_timer_t timer_hid;
static bool timer_callback_hid(repeating_timer_t *t) {
	send_hid_report();
	return true;
}
struct j_button{
	uint gpio;
	char button;
};
struct j_button A={
	.gpio = 2,
	.button = 'A',
};
struct j_button B={
	.gpio = 3,
	.button = 'B',
};
struct j_button C={
	.gpio = 4,
	.button = 'C',
};
struct j_button D={
	.gpio = 5,
	.button = 'D',
};
static void get_button(struct j_button X)
{
	uint bt;
	bt = gpio_get(X.gpio);
	if(bt)
		printf(" , ");
	else
		printf("%c, ", X.button);
}

static void get_joystick(void)
{

	printf("---------------------------------------\n");
	printf("{ ");
	get_button(A);
	get_button(B);
	get_button(C);
	get_button(D);

	adc_select_input(0);
	uint adc_x_raw = adc_read();
	adc_select_input(1);
	uint adc_y_raw = adc_read();

	// Display the joystick position something like this:
	// X: [            o             ]  Y: [              o         ]
	const uint bar_width = 40;
	const uint adc_max = (1 << 12) - 1;
	uint bar_x_pos = adc_x_raw * bar_width / adc_max;
	uint bar_y_pos = adc_y_raw * bar_width / adc_max;
	printf("\tX: [");
	for (int i = 0; i < bar_width; ++i)
		putchar( i == bar_x_pos ? 'o' : ' ');
	printf("]  Y: [");
	for (int i = 0; i < bar_width; ++i)
		putchar( i == bar_y_pos ? 'o' : ' ');
	printf("]\t");
	printf(" }\n");
}

static bool timer_callback_joystick(repeating_timer_t *t) {
	get_joystick();
	return true;
}

/*------------- MAIN -------------*/
extern void main1(void); //control lcd
extern char __flash_binary_end;
int main(void)
{
	int i;
	char buf;

	board_init();
	stdio_init_all();

	/* gpio for joystick */
	gpio_init(2);
	gpio_set_dir(2, GPIO_IN); //A
	gpio_init(3);
	gpio_set_dir(3, GPIO_IN); //B
	gpio_init(4);
	gpio_set_dir(4, GPIO_IN); //C
	gpio_init(5);
	gpio_set_dir(5, GPIO_IN); //D

	adc_init();
	adc_gpio_init(26);
	adc_gpio_init(27);

	add_repeating_timer_ms(500, timer_callback_joystick, NULL, &timer_joystick);

	/* board UID */
	pico_unique_board_id_t board_id;
	pico_get_unique_board_id(&board_id);
	printf("UID:");
	for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; ++i) {
		printf("%02X", board_id.id[i]);
	}
	printf("\n");

	printf("--------core0 start--------,0x%x\n", (intptr_t)&__flash_binary_end);

	/* call core1 */
	multicore_launch_core1(main1);

	/* USB HID */
	tusb_init();

	//add_repeating_timer_ms(1000, timer_callback_hid, NULL, &timer_hid);

	while (1)
	{
		//tud_task(); // tinyusb device task
	}

	return 0;
}

