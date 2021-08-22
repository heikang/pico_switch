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
#include "tusb.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/structs/sio.h"

#include "bsp/board.h"
#include "bsp/rp2040/board.h"

#include "usb_descriptors.h"

#include "lvgl/lvgl.h"
#include "img/ns.h"
//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/*********************
 *      DEFINES
 *********************/
#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

//-----------------LCD端口定义---------------- 
#define LCD_RES_Clr()  gpio_put(20, 0)//RES
#define LCD_RES_Set()  gpio_put(20, 1)

#define LCD_DC_Clr()   gpio_put(21, 0)//DC
#define LCD_DC_Set()   gpio_put(21, 1)

#define LCD_BLK_Clr()  gpio_put(22, 0)//BLK
#define LCD_BLK_Set()  gpio_put(22, 1)

static repeating_timer_t timer;
static repeating_timer_t timer_led;
static uint dma_chan;
static dma_channel_config c;
static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
static lv_disp_draw_buf_t draw_buf_dsc_1;
static lv_color_t buf_1[115200/4];                          /*A buffer for 10 rows*/
static lv_color_t buf_2[115200/4];                          /*A buffer for 10 rows*/

static bool timer_callback(repeating_timer_t *t) {
	lv_tick_inc(1);
	return true;
}
static bool timer_led_callback(repeating_timer_t *t) {
	static bool ledflag = false;
	board_led_write(ledflag);
	ledflag = !ledflag;

	return true;
}

const lv_img_dsc_t img_cogwheel_argb = {
	.header.always_zero = 0,
	.header.w = 240,
	.header.h = 240,
	.data_size = 115200,
	.header.cf = LV_IMG_CF_TRUE_COLOR,
	//.header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA,
	.data = gImage_ns,
};


static void LCD_Writ_Bus(uint8_t dat) 
{
	spi_write_blocking(spi_default, &dat, 1);
}
static void LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}
static void LCD_WR_DATA(uint16_t dat)
{
	LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}
static void LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//   gpio_put(11, 0)//DC //写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}
static void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	if(USE_HORIZONTAL==0){
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}else if(USE_HORIZONTAL==1){
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1+80);
		LCD_WR_DATA(y2+80);
		LCD_WR_REG(0x2c);//储存器写
	}else if(USE_HORIZONTAL==2){
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1);
		LCD_WR_DATA(x2);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}else{
		LCD_WR_REG(0x2a);//列地址设置
		LCD_WR_DATA(x1+80);
		LCD_WR_DATA(x2+80);
		LCD_WR_REG(0x2b);//行地址设置
		LCD_WR_DATA(y1);
		LCD_WR_DATA(y2);
		LCD_WR_REG(0x2c);//储存器写
	}
}

static void disp_init(void)
{
	LCD_RES_Clr();//  gpio_put(10, 0)//RES //复位
	sleep_ms(100);
	LCD_RES_Set();
	sleep_ms(100);

	LCD_BLK_Set();//打开背光
	sleep_ms(100);

	//************* Start Initial Sequence **********//
	LCD_WR_REG(0x11); //Sleep out 
	sleep_ms(120);              //Delay 120ms 
	//************* Start Initial Sequence **********// 
	LCD_WR_REG(0x36);
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A); 
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);
	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29); 
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
int fcnt = 0;
int start, end, flush1, flush2;
void dma_irq_handler()
{
	flush1 = board_millis();
	dma_hw->ints0 = 1u << dma_chan;
	/*IMPORTANT!!! *Inform the graphics library that you are ready with the flushing*/
	fcnt++;
	lv_disp_flush_ready(&disp_drv);
	flush2 = board_millis();
}

static void disp_flush(lv_disp_drv_t * disp_drv1, const lv_area_t * area, lv_color_t * color_p)
{
	/*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
	start = board_millis();
	LCD_Address_Set(area->x1, area->y1, area->x2, area->y2);

	channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
	channel_config_set_dreq(&c, spi_get_index(spi_default) ? DREQ_SPI1_TX : DREQ_SPI0_TX);
	dma_channel_configure(dma_chan, &c,
			&spi_get_hw(spi_default)->dr, // write address
			(uint8_t *)color_p, // read address
			(area->x2 - area->x1 + 1)*(area->y2 - area->y1 + 1)*2, // element count (each element is of size transfer_data_size)
			false); // not start yet
	dma_channel_set_irq0_enabled(dma_chan, true);
	irq_set_exclusive_handler(DMA_IRQ_0, dma_irq_handler);
	irq_set_enabled(DMA_IRQ_0, true);
	dma_start_channel_mask((1u << dma_chan));

	end = board_millis();
}

void lv_port_disp_init(void)
{
	disp_init();

	lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, buf_2, 115200/4);   /*Initialize the display buffer*/

	lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

	/*Set the resolution of the display*/
	disp_drv.hor_res = 240;
	disp_drv.ver_res = 240;

	/*Used to copy the buffer's content to the display*/
	disp_drv.flush_cb = disp_flush;

	/*Set a display buffer*/
	disp_drv.draw_buf = &draw_buf_dsc_1;

	/*Finally register the driver*/
	lv_disp_drv_register(&disp_drv);
}
uint32_t off=0;
static void lvgl_loop(void)
{
	lv_obj_t * img1 = lv_img_create(lv_scr_act());
	lv_img_set_src(img1, &img_cogwheel_argb);
	lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_size(img1, 240, 240);
	//lv_img_set_offset_y(img1, -1);

	while(1){
		sleep_ms(1);
		lv_task_handler();
		//lv_obj_invalidate(img1);
		lv_img_set_offset_y(img1, off%240);
		off++;
	}
}

/*------------- MAIN -------------*/
void main1(void) //control lcd
{
	add_repeating_timer_ms(1, timer_callback, NULL, &timer);
	add_repeating_timer_ms(250, timer_led_callback, NULL, &timer_led);

	printf("--------core1 start--------\n");
	//init spi
	spi_init(spi_default, 63*1000 * 1000); //62.5M

	//init pins
	gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI); //GP16
	gpio_set_function(PICO_DEFAULT_SPI_CSN_PIN, GPIO_FUNC_SPI); //GP17
	gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI); //GP18
	gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI); //GP19

	gpio_init(20);
	gpio_set_dir(20, GPIO_OUT); //RES
	gpio_init(21);
	gpio_set_dir(21, GPIO_OUT); //DC
	gpio_init(22);
	gpio_set_dir(22, GPIO_OUT); //BLK

	dma_chan = dma_claim_unused_channel(true);
	c = dma_channel_get_default_config(dma_chan);
	//dma_channel_unclaim(dma_chan);

	lv_init();
	lv_port_disp_init();

	lvgl_loop();
}
