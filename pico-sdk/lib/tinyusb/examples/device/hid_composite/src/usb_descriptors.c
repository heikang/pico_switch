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

#include "tusb.h"
#include "usb_descriptors.h"


#if 0 //delete at end
typedef enum
{
	TUSB_DESC_DEVICE                = 0x01,
	TUSB_DESC_CONFIGURATION         = 0x02,
	TUSB_DESC_STRING                = 0x03,
	TUSB_DESC_INTERFACE             = 0x04,
	TUSB_DESC_ENDPOINT              = 0x05,
	TUSB_DESC_DEVICE_QUALIFIER      = 0x06,
	TUSB_DESC_OTHER_SPEED_CONFIG    = 0x07,
	TUSB_DESC_INTERFACE_POWER       = 0x08,
	TUSB_DESC_OTG                   = 0x09,
	TUSB_DESC_DEBUG                 = 0x0A,
	TUSB_DESC_INTERFACE_ASSOCIATION = 0x0B,

	TUSB_DESC_BOS                   = 0x0F,
	TUSB_DESC_DEVICE_CAPABILITY     = 0x10,

	TUSB_DESC_FUNCTIONAL            = 0x21,

	// Class Specific Descriptor
	TUSB_DESC_CS_DEVICE             = 0x21,
	TUSB_DESC_CS_CONFIGURATION      = 0x22,
	TUSB_DESC_CS_STRING             = 0x23,
	TUSB_DESC_CS_INTERFACE          = 0x24,
	TUSB_DESC_CS_ENDPOINT           = 0x25,

	TUSB_DESC_SUPERSPEED_ENDPOINT_COMPANION     = 0x30,
	TUSB_DESC_SUPERSPEED_ISO_ENDPOINT_COMPANION = 0x31
}tusb_desc_type_t;
#endif

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]         HID | MSC | CDC          [LSB]
 */
//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device =
{
	.bLength            = sizeof(tusb_desc_device_t),
	.bDescriptorType    = TUSB_DESC_DEVICE,
	.bcdUSB             = 0x0200,
	.bDeviceClass       = 0x00,
	.bDeviceSubClass    = 0x00,
	.bDeviceProtocol    = 0x00,
	.bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

	.idVendor           = 0x0F0D,
	.idProduct          = 0x0092,
	.bcdDevice          = 0x0100,

	.iManufacturer      = 0x01,
	.iProduct           = 0x02,
	.iSerialNumber      = 0x00,

	.bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const * tud_descriptor_device_cb(void)
{
	return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+
uint8_t const JoystickReport[] = {
	HID_RI_USAGE_PAGE(8,1), /* Generic Desktop */
	HID_RI_USAGE(8,5), /* Joystick */
	HID_RI_COLLECTION(8,1), /* Application */
	// Buttons (2 bytes)
	HID_RI_LOGICAL_MINIMUM(8,0),
	HID_RI_LOGICAL_MAXIMUM(8,1),
	HID_RI_PHYSICAL_MINIMUM(8,0),
	HID_RI_PHYSICAL_MAXIMUM(8,1),
	// The Switch will allow us to expand the original HORI descriptors to a full 16 buttons.
	// The Switch will make use of 14 of those buttons.
	HID_RI_REPORT_SIZE(8,1),
	HID_RI_REPORT_COUNT(8,16),
	HID_RI_USAGE_PAGE(8,9),
	HID_RI_USAGE_MINIMUM(8,1),
	HID_RI_USAGE_MAXIMUM(8,16),
	HID_RI_INPUT(8,2),
	// HAT Switch (1 nibble)
	HID_RI_USAGE_PAGE(8,1),
	HID_RI_LOGICAL_MAXIMUM(8,7),
	HID_RI_PHYSICAL_MAXIMUM(16,315),
	HID_RI_REPORT_SIZE(8,4),
	HID_RI_REPORT_COUNT(8,1),
	HID_RI_UNIT(8,20),
	HID_RI_USAGE(8,57),
	HID_RI_INPUT(8,66),

	// There's an additional nibble here that's utilized as part of the Switch Pro Controller.
	// I believe this -might- be separate U/D/L/R bits on the Switch Pro Controller, as they're utilized as four button descriptors on the Swi
	HID_RI_UNIT(8,0),
	HID_RI_REPORT_COUNT(8,1),
	HID_RI_INPUT(8,1),
	// Joystick (4 bytes)
	HID_RI_LOGICAL_MAXIMUM(16,255),
	HID_RI_PHYSICAL_MAXIMUM(16,255),
	HID_RI_USAGE(8,48),
	HID_RI_USAGE(8,49),
	HID_RI_USAGE(8,50),
	HID_RI_USAGE(8,53),
	HID_RI_REPORT_SIZE(8,8),
	HID_RI_REPORT_COUNT(8,4),
	HID_RI_INPUT(8,2),
	// ??? Vendor Specific (1 byte)
	// This byte requires additional investigation.
	HID_RI_USAGE_PAGE(16,65280),
	HID_RI_USAGE(8,32),
	HID_RI_REPORT_COUNT(8,1),
	HID_RI_INPUT(8,2),
	// Output (8 bytes)
	// Original observation of this suggests it to be a mirror of the inputs that we sent.
	// The Switch requires us to have these descriptors available.
	HID_RI_USAGE(16,9761),
	HID_RI_REPORT_COUNT(8,8),
	HID_RI_OUTPUT(8,2),
	HID_RI_END_COLLECTION(0),
};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_hid_descriptor_report_cb(uint8_t itf)
{
	(void) itf;
	return JoystickReport;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+

const USB_Descriptor_Configuration_t desc_configuration = {
	.Config =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = TUSB_DESC_CONFIGURATION},

		.TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
		.TotalInterfaces        = 1,

		.ConfigurationNumber    = 1,
		.ConfigurationStrIndex  = 0,

		.ConfigAttributes       = 0x80,

		.MaxPowerConsumption    = TUSB_DESC_CONFIG_POWER_MA(500)
	},

	.HID_Interface =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = TUSB_DESC_INTERFACE},

		.InterfaceNumber        = 0,
		.AlternateSetting       = 0x00,

		.TotalEndpoints         = 2,

		.Class                  = 0x03,
		.SubClass               = 0x00,
		.Protocol               = 0x00,

		.InterfaceStrIndex      = 0
	},

	.HID_JoystickHID =
	{
		.Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = 0x21},

		.HIDSpec                = 0x0111,
		.CountryCode            = 0x00,
		.TotalReportDescriptors = 1,
		.HIDReportType          = 0x22,
		.HIDReportLength        = sizeof(JoystickReport)
	},

	.HID_ReportINEndpoint =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = TUSB_DESC_ENDPOINT},

		.EndpointAddress        = 0x80 | 1,
		.Attributes             = (0x3 | (0 << 2) | (0 << 4)),
		.EndpointSize           = 64,
		.PollingIntervalMS      = 0x05
	},

	.HID_ReportOUTEndpoint =
	{
		.Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = TUSB_DESC_ENDPOINT},

		.EndpointAddress        = 0x00 | 2,
		.Attributes             = (0x3 | (0 << 2) | (0 << 4)),
		.EndpointSize           = 64,
		.PollingIntervalMS      = 0x05
	},
};

// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
	(void) index; // for multiple configurations
	return (uint8_t const *)&desc_configuration;
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
char const* string_desc_arr [] =
{
	(const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
	"HORI CO.,LTD.",                     // 1: Manufacturer
	"POKKEN CONTROLLER",              // 2: Product
};

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
	(void) langid;

	uint8_t chr_count;

	if ( index == 0)
	{
		memcpy(&_desc_str[1], string_desc_arr[0], 2);
		chr_count = 1;
	}else
	{
		// Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
		// https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

		if ( !(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) ) return NULL;

		const char* str = string_desc_arr[index];

		// Cap at max char
		chr_count = strlen(str);
		if ( chr_count > 31 ) chr_count = 31;

		// Convert ASCII string into UTF-16
		for(uint8_t i=0; i<chr_count; i++)
		{
			_desc_str[1+i] = str[i];
		}
	}

	// first byte is length (including header), second byte is string type
	_desc_str[0] = (TUSB_DESC_STRING << 8 ) | (2*chr_count + 2);

	return _desc_str;
}
