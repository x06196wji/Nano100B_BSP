/******************************************************************************
 * @file     descriptors.c
 * @brief    NANO100 series USBD driver source file
 * @version  2.0.0
 * @date     17, Dec, 2014
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "Nano100Series.h"
#include "vcom_serial.h"

/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
uint8_t gu8DeviceDescriptor[] = {
    LEN_DEVICE,         /* bLength */
    DESC_DEVICE,        /* bDescriptorType */
    0x00, 0x02,		      /* bcdUSB */
    0xEF,               /* bDeviceClass: IAD*/
    0x02,               /* bDeviceSubClass */
    0x01,               /* bDeviceProtocol */
    EP0_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
    /* idVendor */
    USBD_VID & 0x00FF,
    (USBD_VID & 0xFF00) >> 8,
    /* idProduct */
    USBD_PID & 0x00FF,
    (USBD_PID & 0xFF00) >> 8,
    0x00, 0x03,     /* bcdDevice */
    0x01,           /* iManufacture */
    0x02,           /* iProduct */
    0x00,           /* iSerialNumber - no serial */
    0x01            /* bNumConfigurations */
};

/*!<USB Configure Descriptor */
uint8_t gu8ConfigDescriptor[] = {
    LEN_CONFIG,     /* bLength              */
    DESC_CONFIG,    /* bDescriptorType      */
    0x8D, 0x00,     /* wTotalLength         */
    0x04,           /* bNumInterfaces       */
    0x01,           /* bConfigurationValue  */
    0x00,           /* iConfiguration       */
    0xC0,           /* bmAttributes         */
    0x32,           /* MaxPower             */

    // IAD
    0x08,	// bLength: Interface Descriptor size
    0x0B,	// bDescriptorType: IAD
    0x00,	// bFirstInterface
    0x02,	// bInterfaceCount
    0x02,	// bFunctionClass: CDC
    0x02,	// bFunctionSubClass
    0x01,	// bFunctionProtocol 
    0x02,	// iFunction

/* VCOM - 1 */
    /* INTERFACE descriptor */
    LEN_INTERFACE,  /* bLength              */
    DESC_INTERFACE, /* bDescriptorType      */
    0x00,           /* bInterfaceNumber     */
    0x00,           /* bAlternateSetting    */
    0x01,           /* bNumEndpoints        */
    0x02,           /* bInterfaceClass      */
    0x02,           /* bInterfaceSubClass   */
    0x01,           /* bInterfaceProtocol   */
    0x00,           /* iInterface           */

    /* Communication Class Specified INTERFACE descriptor */
    0x05,           /* Size of the descriptor, in bytes */
    0x24,           /* CS_INTERFACE descriptor type */
    0x00,           /* Header functional descriptor subtype */
    0x10, 0x01,     /* Communication device compliant to the communication spec. ver. 1.10 */
    
    /* Communication Class Specified INTERFACE descriptor */
    0x05,           /* Size of the descriptor, in bytes */
    0x24,           /* CS_INTERFACE descriptor type */
    0x01,           /* Call management functional descriptor */
    0x00,           /* BIT0: Whether device handle call management itself. */
                    /* BIT1: Whether device can send/receive call management information over a Data Class Interface 0 */
    0x01,           /* Interface number of data class interface optionally used for call management */

    /* Communication Class Specified INTERFACE descriptor */
    0x04,           /* Size of the descriptor, in bytes */
    0x24,           /* CS_INTERFACE descriptor type */
    0x02,           /* Abstract control management functional descriptor subtype */
    0x00,           /* bmCapabilities       */
    
    /* Communication Class Specified INTERFACE descriptor */
    0x05,           /* bLength              */
    0x24,           /* bDescriptorType: CS_INTERFACE descriptor type */
    0x06,           /* bDescriptorSubType   */
    0x00,           /* bMasterInterface     */
    0x01,           /* bSlaveInterface0     */
    
    /* ENDPOINT descriptor */
    LEN_ENDPOINT,                   /* bLength          */
    DESC_ENDPOINT,                  /* bDescriptorType  */
    (EP_INPUT | INT_IN_EP_NUM),     /* bEndpointAddress */
    EP_INT,                         /* bmAttributes     */
    EP4_MAX_PKT_SIZE, 0x00,             /* wMaxPacketSize   */
    0x01,                           /* bInterval        */
            
    /* INTERFACE descriptor */
    LEN_INTERFACE,  /* bLength              */
    DESC_INTERFACE, /* bDescriptorType      */
    0x01,           /* bInterfaceNumber     */
    0x00,           /* bAlternateSetting    */
    0x02,           /* bNumEndpoints        */
    0x0A,           /* bInterfaceClass      */
    0x00,           /* bInterfaceSubClass   */
    0x00,           /* bInterfaceProtocol   */
    0x00,           /* iInterface           */
            
    /* ENDPOINT descriptor */
    LEN_ENDPOINT,                   /* bLength          */
    DESC_ENDPOINT,                  /* bDescriptorType  */
    (EP_INPUT | BULK_IN_EP_NUM),    /* bEndpointAddress */
    EP_BULK,                        /* bmAttributes     */
    EP2_MAX_PKT_SIZE, 0x00,         /* wMaxPacketSize   */
    0x00,                           /* bInterval        */

    /* ENDPOINT descriptor */
    LEN_ENDPOINT,                   /* bLength          */
    DESC_ENDPOINT,                  /* bDescriptorType  */
    (EP_OUTPUT | BULK_OUT_EP_NUM),  /* bEndpointAddress */
    EP_BULK,                        /* bmAttributes     */
    EP3_MAX_PKT_SIZE, 0x00,         /* wMaxPacketSize   */
    0x00,                           /* bInterval        */

    // IAD
    0x08,	// bLength: Interface Descriptor size
    0x0B,	// bDescriptorType: IAD
    0x02,	// bFirstInterface
    0x02,	// bInterfaceCount
    0x02,	// bFunctionClass: CDC
    0x02,	// bFunctionSubClass
    0x01,	// bFunctionProtocol
    0x02,	// iFunction

/* VCOM - 2 */
    /* INTERFACE descriptor */
    LEN_INTERFACE,  /* bLength              */
    DESC_INTERFACE, /* bDescriptorType      */
    0x02,           /* bInterfaceNumber     */
    0x00,           /* bAlternateSetting    */
    0x01,           /* bNumEndpoints        */
    0x02,           /* bInterfaceClass      */
    0x02,           /* bInterfaceSubClass   */
    0x01,           /* bInterfaceProtocol   */
    0x00,           /* iInterface           */

    /* Communication Class Specified INTERFACE descriptor */
    0x05,           /* Size of the descriptor, in bytes */
    0x24,           /* CS_INTERFACE descriptor type */
    0x00,           /* Header functional descriptor subtype */
    0x10, 0x01,     /* Communication device compliant to the communication spec. ver. 1.10 */
    
    /* Communication Class Specified INTERFACE descriptor */
    0x05,           /* Size of the descriptor, in bytes */
    0x24,           /* CS_INTERFACE descriptor type */
    0x01,           /* Call management functional descriptor */
    0x00,           /* BIT0: Whether device handle call management itself. */
                    /* BIT1: Whether device can send/receive call management information over a Data Class Interface 0 */
    0x01,           /* Interface number of data class interface optionally used for call management */

    /* Communication Class Specified INTERFACE descriptor */
    0x04,           /* Size of the descriptor, in bytes */
    0x24,           /* CS_INTERFACE descriptor type */
    0x02,           /* Abstract control management functional descriptor subtype */
    0x00,           /* bmCapabilities       */
    
    /* Communication Class Specified INTERFACE descriptor */
    0x05,           /* bLength              */
    0x24,           /* bDescriptorType: CS_INTERFACE descriptor type */
    0x06,           /* bDescriptorSubType   */
    0x00,           /* bMasterInterface     */
    0x01,           /* bSlaveInterface0     */
    
    /* ENDPOINT descriptor */
    LEN_ENDPOINT,                   /* bLength          */
    DESC_ENDPOINT,                  /* bDescriptorType  */
    (EP_INPUT | INT_IN_EP_NUM_1),   /* bEndpointAddress */
    EP_INT,                         /* bmAttributes     */
    EP5_MAX_PKT_SIZE, 0x00,         /* wMaxPacketSize   */
    0x01,                           /* bInterval        */
            
    /* INTERFACE descriptor */
    LEN_INTERFACE,  /* bLength              */
    DESC_INTERFACE, /* bDescriptorType      */
    0x03,           /* bInterfaceNumber     */
    0x00,           /* bAlternateSetting    */
    0x02,           /* bNumEndpoints        */
    0x0A,           /* bInterfaceClass      */
    0x00,           /* bInterfaceSubClass   */
    0x00,           /* bInterfaceProtocol   */
    0x00,           /* iInterface           */		
            
		/* ENDPOINT descriptor */
    LEN_ENDPOINT,                    /* bLength          */
    DESC_ENDPOINT,                   /* bDescriptorType  */
    (EP_OUTPUT | BULK_OUT_EP_NUM_1), /* bEndpointAddress */
    EP_BULK,                         /* bmAttributes     */
    EP6_MAX_PKT_SIZE, 0x00,          /* wMaxPacketSize   */
    0x00,                            /* bInterval        */		
		
    /* ENDPOINT descriptor */
    LEN_ENDPOINT,                    /* bLength          */
    DESC_ENDPOINT,                   /* bDescriptorType  */
    (EP_INPUT | BULK_IN_EP_NUM_1),   /* bEndpointAddress */
    EP_BULK,                         /* bmAttributes     */
    EP7_MAX_PKT_SIZE, 0x00,          /* wMaxPacketSize   */
    0x00,                            /* bInterval        */    		
};

/*!<USB Language String Descriptor */
uint8_t gu8StringLang[4] = {
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
uint8_t gu8VendorStringDesc[] = {
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
uint8_t gu8ProductStringDesc[] = {
    32,             /* bLength          */
    DESC_STRING,    /* bDescriptorType  */
    'U', 0, 'S', 0, 'B', 0, ' ', 0, 'V', 0, 'i', 0, 'r', 0, 't', 0, 'u', 0, 'a', 0, 'l', 0, ' ', 0, 'C', 0, 'O', 0, 'M', 0
};

uint8_t *gpu8UsbString[4] = {
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

uint8_t *gu8UsbHidReport[3] = {
    NULL,
    NULL,
    NULL,
};

uint32_t gu32UsbHidReportLen[3] = {
    0,
    0,
    0,
};

uint32_t gu32ConfigHidDescIdx[3] = {
    0,
    0,
    0,
};

S_USBD_INFO_T gsInfo = {
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
    gu32ConfigHidDescIdx,
};

