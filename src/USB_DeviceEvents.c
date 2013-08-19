#include <USB_DeviceEvents.h>

#include <System.h>

#include <stdio.h>

USBD_Usr_cb_TypeDef USR_cb =
{
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,

  USBD_USR_DeviceConnected,
  USBD_USR_DeviceDisconnected,
};

void USBD_USR_Init(void)
{
	printf("USB Device Init\r\n");
}

void USBD_USR_DeviceReset(uint8_t speed)
{
	printf("USB Device Reset. speed: %u\r\n", speed);
}

void USBD_USR_DeviceConfigured(void)
{
	printf("USB Device Configured\r\n");
}

void USBD_USR_DeviceConnected(void)
{
	printf("USB Device Connected\r\n");
}

void USBD_USR_DeviceDisconnected(void)
{
	printf("USB Device Disconnected\r\n");
}

void USBD_USR_DeviceSuspended(void)
{
	printf("USB Device Suspended\r\n");
}

void USBD_USR_DeviceResumed(void)
{
	printf("USB Device Resumed\r\n");
}
