#include <System.h>

#include <stdio.h>
#include <string.h>
#include <SNES.h>

#include <usbd_hid_core.h>
#include <USB_DeviceEvents.h>
#include <USB_DeviceDescriptor.h>
#include <USB_HID_Constants.h>

#include <usb/usb_dcd_int.h>
#include <usbd/usbd_core.h>

USB_OTG_CORE_HANDLE  USB_OTG_dev;

uint8_t HID_Buffer[8];
int pushedbuttons = 0;

void main()
{
	InitializeSnesController();
	InitializeTimer();
	EnableDebugOutput(DEBUG_USART);

	USBD_Init(&USB_OTG_dev,
	               USB_OTG_FS_CORE_ID,
	               &USR_desc,
	               &USBD_HID_cb,
	               &USR_cb);

	while(1){
		snes_button_state_t controller_state = GetControllerState1();
		pushedbuttons = 0;
		for(int i=0;i<=7;i++) HID_Buffer[i] = 0;

		if (pushedbuttons<4 && controller_state.buttons.A) {
			HID_Buffer[2+pushedbuttons]=0x04;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.B) {
			HID_Buffer[2+pushedbuttons]=0x05;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.X) {
			HID_Buffer[2+pushedbuttons]=0x1B;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Y) {
			HID_Buffer[2+pushedbuttons]=0x1C;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.L) {
			HID_Buffer[2+pushedbuttons]=0x0F;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.R) {
			HID_Buffer[2+pushedbuttons]=0x15;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Start) {
			HID_Buffer[2+pushedbuttons]=0x28; // Enter
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Select) {
			HID_Buffer[2+pushedbuttons]=0x2C; // Space
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Right) {
			HID_Buffer[2+pushedbuttons]=0x4F;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Left) {
			HID_Buffer[2+pushedbuttons]=0x50;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Down) {
			HID_Buffer[2+pushedbuttons]=0x51;
			pushedbuttons++;
		}
		if (pushedbuttons<4 && controller_state.buttons.Up) {
			HID_Buffer[2+pushedbuttons]=0x52;
			pushedbuttons++;
		}
		USBD_HID_SendReport (&USB_OTG_dev,HID_Buffer,8);
	}
}

void OTG_FS_IRQHandler(void)
{
    USBD_OTG_ISR_Handler(&USB_OTG_dev);
}


