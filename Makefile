# Target file name.
TARGET = usb_snes_keyboard

# List C source files here.
CCSOURCES = SNES.c main.c \
USB_DeviceEvents.c USB_DeviceDescriptor.c USB_HID_Constants.c usbd_hid_core.c

# Additional local static libs to link against
LIBS = system stm32f4xx usbcore usbdevice

# Folder for object files
OBJDIR = obj

# Folder for sourcecode
SRCDIR = src

# Additional defines
DEFINES := -DRGB8Pixels

# Root dir (enables use for different target/folder names)
TARGET_ROOT_DIR := $(SELF_DIR)

-include $(ROOT)/build/firmware.mak
