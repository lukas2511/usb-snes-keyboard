#include <USB_Device.h>
#include <USB_DeviceDescriptor.h>
#include <usbd/usbd_req.h>

#include <stdio.h>

static uint8_t USBD_DEV_Init(void *pdev, uint8_t cfgidx);
static uint8_t USBD_DEV_DeInit(void *pdev, uint8_t cfgidx);
static uint8_t USBD_DEV_Setup(void *pdev, USB_SETUP_REQ *req);
static uint8_t *USBD_DEV_GetCfgDesc(uint8_t speed, uint16_t *length);

USBD_Class_cb_TypeDef USBD_DEV_cb =
{
  USBD_DEV_Init,
  USBD_DEV_DeInit,
  USBD_DEV_Setup,
  NULL, /*EP0_TxSent*/
  NULL, /*EP0_RxReady*/
  NULL, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL,
  USBD_DEV_GetCfgDesc
};

__ALIGN_BEGIN static uint8_t USBD_DEV_CfgDesc[USB_DEV_CONFIG_DESC_SIZ] __ALIGN_END =
{
  // 0x09, /* bLength: Configuration Descriptor size */
  // USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
  // USB_DEV_CONFIG_DESC_SIZ, 0x00, /* wTotalLength: Bytes returned */
  // 0x01,         /*bNumInterfaces: 1 interface*/
  // 0x01,         /*bConfigurationValue: Configuration value*/
  // USBD_IDX_CONFIG_STR,         /*iConfiguration: Index of string descriptor describing the configuration*/
  // 0xC0,         /*bmAttributes: bus powered */
  // 0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/

  // ************* Interface descriptor ***************
  // /* 09 */
  // 0x09,         /*bLength: Interface Descriptor size*/
  // USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
  // 0x00,         /*bInterfaceNumber: Number of Interface*/
  // 0x00,         /*bAlternateSetting: Alternate setting*/
  // 0x00,         /*bNumEndpoints*/
  // 0x03,         /*bInterfaceClass*/
  // 0x01,         /*bInterfaceSubClass*/
  // 0x01,         /*nInterfaceProtocol*/
  // USBD_IDX_INTERFACE_STR,         /*iInterface: Index of string descriptor*/
  // /* 18 */
  0x09,
  0x02,
  0x3B,
  0x00,
  0x02,
  0x01,
  0x00,
  0xC0,
  0x32,
  0x09,
  0x04,
  0x00,
  0x00,
  0x01,
  0x03,
  0x01,
  0x01,
  0x00,
  0x09,
  0x21,
  0x11,
  0x01,
  0x00,
  0x01,
  0x22,
  0x41,
  0x00,
  0x07,
  0x05,
  0x81,
  0x03,
  0x08,
  0x00,
  0x0A,
  0x09,
  0x04,
  0x01,
  0x00,
  0x01,
  0x03,
  0x00,
  0x00,
  0x00,
  0x09,
  0x21,
  0x11,
  0x01,
  0x00,
  0x01,
  0x22,
  0x92,
  0x00,
  0x07,
  0x05,
  0x82,
  0x03,
  0x04,
  0x00,
  0x0A
};

static uint8_t USBD_DEV_Init (void  *pdev, uint8_t cfgidx)
{
  printf("USB DEV Init. cfgidx: %u\r\n", cfgidx);
  return USBD_OK;
}

static uint8_t USBD_DEV_DeInit(void *pdev, uint8_t cfgidx)
{
  printf("USB DEV DeInit. cfgidx: %u\r\n", cfgidx);
  return USBD_OK;
}

uint16_t value = 0;
static uint8_t USBD_DEV_Setup(void *pdev, USB_SETUP_REQ *req)
{
  printf("USB SETUP request: bmRequest: 0x%x, bRequest: 0x%x, wValue: 0x%x, wIndex: 0x%x, wLength: 0x%x\r\n",
      req->bmRequest,
      req->bRequest,
      req->wValue,
      req->wIndex,
      req->wLength
  );

  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
    case USB_REQ_TYPE_CLASS:
      switch(req->bRequest)
      {
        // case HID_REQ_GetReport: {
        //   USB_KeyboardReport_Data_t keyboardData;
        //   keyboardData.Modifier = 0;
        //   keyboardData.Reserved = 0;
        //   keyboardData.KeyCode[0] = HID_KEYBOARD_SC_S;

        //   uint8_t usingReportProtocol = 1;
        //   USBD_CtlSendData(pdev, &usingReportProtocol, sizeof(usingReportProtocol));
        // break;
        // }

        case HID_REQ_GetIdle:
        break;

        case HID_REQ_GetProtocol: {
          uint8_t usingReportProtocol = 1;
          USBD_CtlSendData(pdev, &usingReportProtocol, sizeof(usingReportProtocol));
        break;
        }

        case HID_REQ_SetReport:
        break;

        case HID_REQ_SetIdle:
        break;

        case HID_REQ_SetProtocol:
        break;
        // case USB_REQ_SET:
        //   value = req->wValue;
        //   break;

        // case USB_REQ_GET_VALUE:
        //   USBD_CtlSendData(pdev, (uint8_t*)&value, sizeof(value));
        //   break;

        default:
          USBD_CtlError(pdev, req);
          return USBD_FAIL;
      }
  }

  return USBD_OK;
}

static uint8_t *USBD_DEV_GetCfgDesc(uint8_t speed, uint16_t *length)
{
  printf("USB DEV GetCfgDesc. speed: %u\r\n", speed);
  *length = sizeof(USBD_DEV_CfgDesc);
  return USBD_DEV_CfgDesc;
}
