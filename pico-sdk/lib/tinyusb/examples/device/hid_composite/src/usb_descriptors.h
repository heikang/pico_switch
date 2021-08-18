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
 */

#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

enum
{
  REPORT_ID_KEYBOARD = 1,
  REPORT_ID_MOUSE,
  REPORT_ID_CONSUMER_CONTROL,
  REPORT_ID_GAMEPAD,
  REPORT_ID_COUNT
};

typedef struct TU_ATTR_PACKED
{
	uint8_t Size; /**< Size of the descriptor, in bytes. */
	uint8_t Type; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
		       *   given by the specific class.
		       */
}USB_Descriptor_Header_t;

typedef struct TU_ATTR_PACKED
{
	USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

	uint16_t TotalConfigurationSize; /**< Size of the configuration descriptor header,
					  *   and all sub descriptors inside the configuration.
					  */
	uint8_t  TotalInterfaces; /**< Total number of interfaces in the configuration. */

	uint8_t  ConfigurationNumber; /**< Configuration index of the current configuration. */
	uint8_t  ConfigurationStrIndex; /**< Index of a string descriptor describing the configuration. */

	uint8_t  ConfigAttributes; /**< Configuration attributes, comprised of a mask of \c USB_CONFIG_ATTR_* masks.
				    *   On all devices, this should include USB_CONFIG_ATTR_RESERVED at a minimum.
				    */

	uint8_t  MaxPowerConsumption; /**< Maximum power consumption of the device while in the
				       *   current configuration, calculated by the \ref USB_CONFIG_POWER_MA()
				       *   macro.
				       */
}USB_Descriptor_Configuration_Header_t;

typedef struct TU_ATTR_PACKED
{
	USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

	uint8_t InterfaceNumber; /**< Index of the interface in the current configuration. */
	uint8_t AlternateSetting; /**< Alternate setting for the interface number. The same
				   *   interface number can have multiple alternate settings
				   *   with different endpoint configurations, which can be
				   *   selected by the host.
				   */
	uint8_t TotalEndpoints; /**< Total number of endpoints in the interface. */

	uint8_t Class; /**< Interface class ID. */
	uint8_t SubClass; /**< Interface subclass ID. */
	uint8_t Protocol; /**< Interface protocol ID. */

	uint8_t InterfaceStrIndex; /**< Index of the string descriptor describing the interface. */
}USB_Descriptor_Interface_t;

typedef struct TU_ATTR_PACKED
{
	USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */

	uint16_t                HIDSpec; /**< BCD encoded version that the HID descriptor and device complies to.
					  *
					  *   \see \ref VERSION_BCD() utility macro.
					  */
	uint8_t                 CountryCode; /**< Country code of the localized device, or zero if universal. */

	uint8_t                 TotalReportDescriptors; /**< Total number of HID report descriptors for the interface. */

	uint8_t                 HIDReportType; /**< Type of HID report, set to \ref HID_DTYPE_Report. */
	uint16_t                HIDReportLength; /**< Length of the associated HID report descriptor, in bytes. */
}USB_HID_Descriptor_HID_t;

typedef struct TU_ATTR_PACKED
{
	USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */

	uint8_t  EndpointAddress; /**< Logical address of the endpoint within the device for the current
				   *   configuration, including direction mask.
				   */
	uint8_t  Attributes; /**< Endpoint attributes, comprised of a mask of the endpoint type (EP_TYPE_*)
			      *   and attributes (ENDPOINT_ATTR_*) masks.
			      */
	uint16_t EndpointSize; /**< Size of the endpoint bank, in bytes. This indicates the maximum packet
				*   size that the endpoint can receive at a time.
				*/
	uint8_t  PollingIntervalMS; /**< Polling interval in milliseconds for the endpoint if it is an INTERRUPT
				     *   or ISOCHRONOUS type.
				     */
}USB_Descriptor_Endpoint_t;

typedef struct TU_ATTR_PACKED
{
	USB_Descriptor_Configuration_Header_t Config;

	// Joystick HID Interface
	USB_Descriptor_Interface_t            HID_Interface;
	USB_HID_Descriptor_HID_t              HID_JoystickHID;
	USB_Descriptor_Endpoint_t             HID_ReportOUTEndpoint;
	USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
}USB_Descriptor_Configuration_t;

#define CONCAT(x, y)            x ## y
#define CONCAT_EXPANDED(x, y)   CONCAT(x, y)

#define HID_RI_DATA_SIZE_MASK                   0x03
#define HID_RI_TYPE_MASK                        0x0C
#define HID_RI_TAG_MASK                         0xF0

#define HID_RI_TYPE_MAIN                        0x00
#define HID_RI_TYPE_GLOBAL                      0x04
#define HID_RI_TYPE_LOCAL                       0x08

#define HID_RI_DATA_BITS_0                      0x00
#define HID_RI_DATA_BITS_8                      0x01
#define HID_RI_DATA_BITS_16                     0x02
#define HID_RI_DATA_BITS_32                     0x03
#define HID_RI_DATA_BITS(DataBits)              CONCAT_EXPANDED(HID_RI_DATA_BITS_, DataBits)

#define _HID_RI_ENCODE_0(Data)
#define _HID_RI_ENCODE_8(Data)                  , (Data & 0xFF)
#define _HID_RI_ENCODE_16(Data)                 _HID_RI_ENCODE_8(Data)  _HID_RI_ENCODE_8(Data >> 8)
#define _HID_RI_ENCODE_32(Data)                 _HID_RI_ENCODE_16(Data) _HID_RI_ENCODE_16(Data >> 16)
#define _HID_RI_ENCODE(DataBits, ...)           CONCAT_EXPANDED(_HID_RI_ENCODE_, DataBits(__VA_ARGS__))

#define _HID_RI_ENTRY(Type, Tag, DataBits, ...) (Type | Tag | HID_RI_DATA_BITS(DataBits)) _HID_RI_ENCODE(DataBits, (__VA_ARGS__))

#define HID_RI_INPUT(DataBits, ...)             _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0x80, DataBits, __VA_ARGS__)
#define HID_RI_OUTPUT(DataBits, ...)            _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0x90, DataBits, __VA_ARGS__)
#define HID_RI_COLLECTION(DataBits, ...)        _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xA0, DataBits, __VA_ARGS__)
#define HID_RI_FEATURE(DataBits, ...)           _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xB0, DataBits, __VA_ARGS__)
#define HID_RI_END_COLLECTION(DataBits, ...)    _HID_RI_ENTRY(HID_RI_TYPE_MAIN  , 0xC0, DataBits, __VA_ARGS__)
#define HID_RI_USAGE_PAGE(DataBits, ...)        _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x00, DataBits, __VA_ARGS__)
#define HID_RI_LOGICAL_MINIMUM(DataBits, ...)   _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x10, DataBits, __VA_ARGS__)
#define HID_RI_LOGICAL_MAXIMUM(DataBits, ...)   _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x20, DataBits, __VA_ARGS__)
#define HID_RI_PHYSICAL_MINIMUM(DataBits, ...)  _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x30, DataBits, __VA_ARGS__)
#define HID_RI_PHYSICAL_MAXIMUM(DataBits, ...)  _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x40, DataBits, __VA_ARGS__)
#define HID_RI_UNIT_EXPONENT(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x50, DataBits, __VA_ARGS__)
#define HID_RI_UNIT(DataBits, ...)              _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x60, DataBits, __VA_ARGS__)
#define HID_RI_REPORT_SIZE(DataBits, ...)       _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x70, DataBits, __VA_ARGS__)
#define HID_RI_REPORT_ID(DataBits, ...)         _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x80, DataBits, __VA_ARGS__)
#define HID_RI_REPORT_COUNT(DataBits, ...)      _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0x90, DataBits, __VA_ARGS__)
#define HID_RI_PUSH(DataBits, ...)              _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0xA0, DataBits, __VA_ARGS__)
#define HID_RI_POP(DataBits, ...)               _HID_RI_ENTRY(HID_RI_TYPE_GLOBAL, 0xB0, DataBits, __VA_ARGS__)
#define HID_RI_USAGE(DataBits, ...)             _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x00, DataBits, __VA_ARGS__)
#define HID_RI_USAGE_MINIMUM(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x10, DataBits, __VA_ARGS__)
#define HID_RI_USAGE_MAXIMUM(DataBits, ...)     _HID_RI_ENTRY(HID_RI_TYPE_LOCAL , 0x20, DataBits, __VA_ARGS__)



#endif /* USB_DESCRIPTORS_H_ */
