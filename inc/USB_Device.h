#ifndef __USB_DEVICE_H_
#define __USB_DEVICE_H_

#include  <usbd/usbd_ioreq.h>

typedef struct {
  uint8_t Modifier; /**< Keyboard modifier byte, indicating pressed modifier keys (a combination of
                     *   \c HID_KEYBOARD_MODIFER_* masks).
                     */
  uint8_t Reserved; /**< Reserved for OEM use, always set to 0. */
  uint8_t KeyCode[6]; /**< Key codes of the currently pressed keys. */
} USB_KeyboardReport_Data_t;

typedef enum 
{
	HID_REQ_GetReport       = 0x01, /**< HID class-specific Request to get the current HID report from the device. */
	HID_REQ_GetIdle         = 0x02, /**< HID class-specific Request to get the current device idle count. */
	HID_REQ_GetProtocol     = 0x03, /**< HID class-specific Request to get the current HID report protocol mode. */
	HID_REQ_SetReport       = 0x09, /**< HID class-specific Request to set the current HID report to the device. */
	HID_REQ_SetIdle         = 0x0A, /**< HID class-specific Request to set the device's idle count. */
	HID_REQ_SetProtocol     = 0x0B, /**< HID class-specific Request to set the current HID report protocol mode. */
} HID_ClassRequests_t;

/** Enum for the HID class specific descriptor types. */
typedef enum 
{
	HID_DTYPE_HID           = 0x21, /**< Descriptor header type value, to indicate a HID class HID descriptor. */
	HID_DTYPE_Report        = 0x22, /**< Descriptor header type value, to indicate a HID class HID report descriptor. */
} HID_DescriptorTypes_t;

/** Enum for the different types of HID reports. */
typedef enum 
{
	HID_REPORT_ITEM_In      = 0, /**< Indicates that the item is an IN report type. */
	HID_REPORT_ITEM_Out     = 1, /**< Indicates that the item is an OUT report type. */
	HID_REPORT_ITEM_Feature = 2, /**< Indicates that the item is a FEATURE report type. */
} HID_ReportItemTypes_t;

#define USB_DEV_CONFIG_DESC_SIZ       59

#define USB_REQ_SET_VALUE              1
#define USB_REQ_GET_VALUE              2

/** Constant for a keyboard report modifier byte, indicating that the keyboard's left control key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_LEFTCTRL                    (1 << 0)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's left shift key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_LEFTSHIFT                   (1 << 1)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's left alt key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_LEFTALT                     (1 << 2)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's left GUI key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_LEFTGUI                     (1 << 3)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's right control key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_RIGHTCTRL                   (1 << 4)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's right shift key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_RIGHTSHIFT                  (1 << 5)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's right alt key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_RIGHTALT                    (1 << 6)

/** Constant for a keyboard report modifier byte, indicating that the keyboard's right GUI key is currently pressed. */
#define HID_KEYBOARD_MODIFIER_RIGHTGUI                    (1 << 7)
//@}

/** \name Keyboard Standard Report LED Masks */
//@{
/** Constant for a keyboard output report LED byte, indicating that the host's NUM LOCK mode is currently set. */
#define HID_KEYBOARD_LED_NUMLOCK                          (1 << 0)

/** Constant for a keyboard output report LED byte, indicating that the host's CAPS LOCK mode is currently set. */
#define HID_KEYBOARD_LED_CAPSLOCK                         (1 << 1)

/** Constant for a keyboard output report LED byte, indicating that the host's SCROLL LOCK mode is currently set. */
#define HID_KEYBOARD_LED_SCROLLLOCK                       (1 << 2)

/** Constant for a keyboard output report LED byte, indicating that the host's KATANA mode is currently set. */
#define HID_KEYBOARD_LED_KATANA                           (1 << 3)
//@}

/** \name Keyboard Standard Report Key Scan-codes */
//@{
#define HID_KEYBOARD_SC_ERROR_ROLLOVER                    0x01
#define HID_KEYBOARD_SC_POST_FAIL                         0x02
#define HID_KEYBOARD_SC_ERROR_UNDEFINED                   0x03
#define HID_KEYBOARD_SC_A                                 0x04
#define HID_KEYBOARD_SC_B                                 0x05
#define HID_KEYBOARD_SC_C                                 0x06
#define HID_KEYBOARD_SC_D                                 0x07
#define HID_KEYBOARD_SC_E                                 0x08
#define HID_KEYBOARD_SC_F                                 0x09
#define HID_KEYBOARD_SC_G                                 0x0A
#define HID_KEYBOARD_SC_H                                 0x0B
#define HID_KEYBOARD_SC_I                                 0x0C
#define HID_KEYBOARD_SC_J                                 0x0D
#define HID_KEYBOARD_SC_K                                 0x0E
#define HID_KEYBOARD_SC_L                                 0x0F
#define HID_KEYBOARD_SC_M                                 0x10
#define HID_KEYBOARD_SC_N                                 0x11
#define HID_KEYBOARD_SC_O                                 0x12
#define HID_KEYBOARD_SC_P                                 0x13
#define HID_KEYBOARD_SC_Q                                 0x14
#define HID_KEYBOARD_SC_R                                 0x15
#define HID_KEYBOARD_SC_S                                 0x16
#define HID_KEYBOARD_SC_T                                 0x17
#define HID_KEYBOARD_SC_U                                 0x18
#define HID_KEYBOARD_SC_V                                 0x19
#define HID_KEYBOARD_SC_W                                 0x1A
#define HID_KEYBOARD_SC_X                                 0x1B
#define HID_KEYBOARD_SC_Y                                 0x1C
#define HID_KEYBOARD_SC_Z                                 0x1D
#define HID_KEYBOARD_SC_1_AND_EXCLAMATION                 0x1E
#define HID_KEYBOARD_SC_2_AND_AT                          0x1F
#define HID_KEYBOARD_SC_3_AND_HASHMARK                    0x20
#define HID_KEYBOARD_SC_4_AND_DOLLAR                      0x21
#define HID_KEYBOARD_SC_5_AND_PERCENTAGE                  0x22
#define HID_KEYBOARD_SC_6_AND_CARET                       0x23
#define HID_KEYBOARD_SC_7_AND_AND_AMPERSAND               0x24
#define HID_KEYBOARD_SC_8_AND_ASTERISK                    0x25
#define HID_KEYBOARD_SC_9_AND_OPENING_PARENTHESIS         0x26
#define HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS         0x27
#define HID_KEYBOARD_SC_ENTER                             0x28
#define HID_KEYBOARD_SC_ESCAPE                            0x29
#define HID_KEYBOARD_SC_BACKSPACE                         0x2A
#define HID_KEYBOARD_SC_TAB                               0x2B
#define HID_KEYBOARD_SC_SPACE                             0x2C
#define HID_KEYBOARD_SC_MINUS_AND_UNDERSCORE              0x2D
#define HID_KEYBOARD_SC_EQUAL_AND_PLUS                    0x2E
#define HID_KEYBOARD_SC_OPENING_BRACKET_AND_OPENING_BRACE 0x2F
#define HID_KEYBOARD_SC_CLOSING_BRACKET_AND_CLOSING_BRACE 0x30
#define HID_KEYBOARD_SC_BACKSLASH_AND_PIPE                0x31
#define HID_KEYBOARD_SC_NON_US_HASHMARK_AND_TILDE         0x32
#define HID_KEYBOARD_SC_SEMICOLON_AND_COLON               0x33
#define HID_KEYBOARD_SC_APOSTROPHE_AND_QUOTE              0x34
#define HID_KEYBOARD_SC_GRAVE_ACCENT_AND_TILDE            0x35
#define HID_KEYBOARD_SC_COMMA_AND_LESS_THAN_SIGN          0x36
#define HID_KEYBOARD_SC_DOT_AND_GREATER_THAN_SIGN         0x37
#define HID_KEYBOARD_SC_SLASH_AND_QUESTION_MARK           0x38
#define HID_KEYBOARD_SC_CAPS_LOCK                         0x39
#define HID_KEYBOARD_SC_F1                                0x3A
#define HID_KEYBOARD_SC_F2                                0x3B
#define HID_KEYBOARD_SC_F3                                0x3C
#define HID_KEYBOARD_SC_F4                                0x3D
#define HID_KEYBOARD_SC_F5                                0x3E
#define HID_KEYBOARD_SC_F6                                0x3F
#define HID_KEYBOARD_SC_F7                                0x40
#define HID_KEYBOARD_SC_F8                                0x41
#define HID_KEYBOARD_SC_F9                                0x42
#define HID_KEYBOARD_SC_F10                               0x43
#define HID_KEYBOARD_SC_F11                               0x44
#define HID_KEYBOARD_SC_F12                               0x45
#define HID_KEYBOARD_SC_PRINT_SCREEN                      0x46
#define HID_KEYBOARD_SC_SCROLL_LOCK                       0x47
#define HID_KEYBOARD_SC_PAUSE                             0x48
#define HID_KEYBOARD_SC_INSERT                            0x49
#define HID_KEYBOARD_SC_HOME                              0x4A
#define HID_KEYBOARD_SC_PAGE_UP                           0x4B
#define HID_KEYBOARD_SC_DELETE                            0x4C
#define HID_KEYBOARD_SC_END                               0x4D
#define HID_KEYBOARD_SC_PAGE_DOWN                         0x4E
#define HID_KEYBOARD_SC_RIGHT_ARROW                       0x4F
#define HID_KEYBOARD_SC_LEFT_ARROW                        0x50
#define HID_KEYBOARD_SC_DOWN_ARROW                        0x51
#define HID_KEYBOARD_SC_UP_ARROW                          0x52
#define HID_KEYBOARD_SC_NUM_LOCK                          0x53
#define HID_KEYBOARD_SC_KEYPAD_SLASH                      0x54
#define HID_KEYBOARD_SC_KEYPAD_ASTERISK                   0x55
#define HID_KEYBOARD_SC_KEYPAD_MINUS                      0x56
#define HID_KEYBOARD_SC_KEYPAD_PLUS                       0x57
#define HID_KEYBOARD_SC_KEYPAD_ENTER                      0x58
#define HID_KEYBOARD_SC_KEYPAD_1_AND_END                  0x59
#define HID_KEYBOARD_SC_KEYPAD_2_AND_DOWN_ARROW           0x5A
#define HID_KEYBOARD_SC_KEYPAD_3_AND_PAGE_DOWN            0x5B
#define HID_KEYBOARD_SC_KEYPAD_4_AND_LEFT_ARROW           0x5C
#define HID_KEYBOARD_SC_KEYPAD_5                          0x5D
#define HID_KEYBOARD_SC_KEYPAD_6_AND_RIGHT_ARROW          0x5E
#define HID_KEYBOARD_SC_KEYPAD_7_AND_HOME                 0x5F
#define HID_KEYBOARD_SC_KEYPAD_8_AND_UP_ARROW             0x60
#define HID_KEYBOARD_SC_KEYPAD_9_AND_PAGE_UP              0x61
#define HID_KEYBOARD_SC_KEYPAD_0_AND_INSERT               0x62
#define HID_KEYBOARD_SC_KEYPAD_DOT_AND_DELETE             0x63
#define HID_KEYBOARD_SC_NON_US_BACKSLASH_AND_PIPE         0x64
#define HID_KEYBOARD_SC_POWER                             0x66
#define HID_KEYBOARD_SC_EQUAL_SIGN                        0x67
#define HID_KEYBOARD_SC_F13                               0x68
#define HID_KEYBOARD_SC_F14                               0x69
#define HID_KEYBOARD_SC_F15                               0x6A
#define HID_KEYBOARD_SC_F16                               0x6B
#define HID_KEYBOARD_SC_F17                               0x6C
#define HID_KEYBOARD_SC_F18                               0x6D
#define HID_KEYBOARD_SC_F19                               0x6E
#define HID_KEYBOARD_SC_F20                               0x6F
#define HID_KEYBOARD_SC_F21                               0x70
#define HID_KEYBOARD_SC_F22                               0x71
#define HID_KEYBOARD_SC_F23                               0x72
#define HID_KEYBOARD_SC_F24                               0x73
#define HID_KEYBOARD_SC_EXECUTE                           0x74
#define HID_KEYBOARD_SC_HELP                              0x75
#define HID_KEYBOARD_SC_MANU                              0x76
#define HID_KEYBOARD_SC_SELECT                            0x77
#define HID_KEYBOARD_SC_STOP                              0x78
#define HID_KEYBOARD_SC_AGAIN                             0x79
#define HID_KEYBOARD_SC_UNDO                              0x7A
#define HID_KEYBOARD_SC_CUT                               0x7B
#define HID_KEYBOARD_SC_COPY                              0x7C
#define HID_KEYBOARD_SC_PASTE                             0x7D
#define HID_KEYBOARD_SC_FIND                              0x7E
#define HID_KEYBOARD_SC_MUTE                              0x7F
#define HID_KEYBOARD_SC_VOLUME_UP                         0x80
#define HID_KEYBOARD_SC_VOLUME_DOWN                       0x81
#define HID_KEYBOARD_SC_LOCKING_CAPS_LOCK                 0x82
#define HID_KEYBOARD_SC_LOCKING_NUM_LOCK                  0x83
#define HID_KEYBOARD_SC_LOCKING_SCROLL_LOCK               0x84
#define HID_KEYBOARD_SC_KEYPAD_COMMA                      0x85
#define HID_KEYBOARD_SC_KEYPAD_EQUAL_SIGN                 0x86
#define HID_KEYBOARD_SC_INTERNATIONAL1                    0x87
#define HID_KEYBOARD_SC_INTERNATIONAL2                    0x88
#define HID_KEYBOARD_SC_INTERNATIONAL3                    0x89
#define HID_KEYBOARD_SC_INTERNATIONAL4                    0x8A
#define HID_KEYBOARD_SC_INTERNATIONAL5                    0x8B
#define HID_KEYBOARD_SC_INTERNATIONAL6                    0x8C
#define HID_KEYBOARD_SC_INTERNATIONAL7                    0x8D
#define HID_KEYBOARD_SC_INTERNATIONAL8                    0x8E
#define HID_KEYBOARD_SC_INTERNATIONAL9                    0x8F
#define HID_KEYBOARD_SC_LANG1                             0x90
#define HID_KEYBOARD_SC_LANG2                             0x91
#define HID_KEYBOARD_SC_LANG3                             0x92
#define HID_KEYBOARD_SC_LANG4                             0x93
#define HID_KEYBOARD_SC_LANG5                             0x94
#define HID_KEYBOARD_SC_LANG6                             0x95
#define HID_KEYBOARD_SC_LANG7                             0x96
#define HID_KEYBOARD_SC_LANG8                             0x97
#define HID_KEYBOARD_SC_LANG9                             0x98
#define HID_KEYBOARD_SC_ALTERNATE_ERASE                   0x99
#define HID_KEYBOARD_SC_SISREQ                            0x9A
#define HID_KEYBOARD_SC_CANCEL                            0x9B
#define HID_KEYBOARD_SC_CLEAR                             0x9C
#define HID_KEYBOARD_SC_PRIOR                             0x9D
#define HID_KEYBOARD_SC_RETURN                            0x9E
#define HID_KEYBOARD_SC_SEPARATOR                         0x9F
#define HID_KEYBOARD_SC_OUT                               0xA0
#define HID_KEYBOARD_SC_OPER                              0xA1
#define HID_KEYBOARD_SC_CLEAR_AND_AGAIN                   0xA2
#define HID_KEYBOARD_SC_CRSEL_ANDPROPS                    0xA3
#define HID_KEYBOARD_SC_EXSEL                             0xA4
#define HID_KEYBOARD_SC_KEYPAD_00                         0xB0
#define HID_KEYBOARD_SC_KEYPAD_000                        0xB1
#define HID_KEYBOARD_SC_THOUSANDS_SEPARATOR               0xB2
#define HID_KEYBOARD_SC_DECIMAL_SEPARATOR                 0xB3
#define HID_KEYBOARD_SC_CURRENCY_UNIT                     0xB4
#define HID_KEYBOARD_SC_CURRENCY_SUB_UNIT                 0xB5
#define HID_KEYBOARD_SC_KEYPAD_OPENING_PARENTHESIS        0xB6
#define HID_KEYBOARD_SC_KEYPAD_CLOSING_PARENTHESIS        0xB7
#define HID_KEYBOARD_SC_KEYPAD_OPENING_BRACE              0xB8
#define HID_KEYBOARD_SC_KEYPAD_CLOSING_BRACE              0xB9
#define HID_KEYBOARD_SC_KEYPAD_TAB                        0xBA
#define HID_KEYBOARD_SC_KEYPAD_BACKSPACE                  0xBB
#define HID_KEYBOARD_SC_KEYPAD_A                          0xBC
#define HID_KEYBOARD_SC_KEYPAD_B                          0xBD
#define HID_KEYBOARD_SC_KEYPAD_C                          0xBE
#define HID_KEYBOARD_SC_KEYPAD_D                          0xBF
#define HID_KEYBOARD_SC_KEYPAD_E                          0xC0
#define HID_KEYBOARD_SC_KEYPAD_F                          0xC1
#define HID_KEYBOARD_SC_KEYPAD_XOR                        0xC2
#define HID_KEYBOARD_SC_KEYPAD_CARET                      0xC3
#define HID_KEYBOARD_SC_KEYPAD_PERCENTAGE                 0xC4
#define HID_KEYBOARD_SC_KEYPAD_LESS_THAN_SIGN             0xC5
#define HID_KEYBOARD_SC_KEYPAD_GREATER_THAN_SIGN          0xC6
#define HID_KEYBOARD_SC_KEYPAD_AMP                        0xC7
#define HID_KEYBOARD_SC_KEYPAD_AMP_AMP                    0xC8
#define HID_KEYBOARD_SC_KEYPAD_PIPE                       0xC9
#define HID_KEYBOARD_SC_KEYPAD_PIPE_PIPE                  0xCA
#define HID_KEYBOARD_SC_KEYPAD_COLON                      0xCB
#define HID_KEYBOARD_SC_KEYPAD_HASHMARK                   0xCC
#define HID_KEYBOARD_SC_KEYPAD_SPACE                      0xCD
#define HID_KEYBOARD_SC_KEYPAD_AT                         0xCE
#define HID_KEYBOARD_SC_KEYPAD_EXCLAMATION_SIGN           0xCF
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_STORE               0xD0
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_RECALL              0xD1
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_CLEAR               0xD2
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_ADD                 0xD3
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_SUBTRACT            0xD4
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_MULTIPLY            0xD5
#define HID_KEYBOARD_SC_KEYPAD_MEMORY_DIVIDE              0xD6
#define HID_KEYBOARD_SC_KEYPAD_PLUS_AND_MINUS             0xD7
#define HID_KEYBOARD_SC_KEYPAD_CLEAR                      0xD8
#define HID_KEYBOARD_SC_KEYPAD_CLEAR_ENTRY                0xD9
#define HID_KEYBOARD_SC_KEYPAD_BINARY                     0xDA
#define HID_KEYBOARD_SC_KEYPAD_OCTAL                      0xDB
#define HID_KEYBOARD_SC_KEYPAD_DECIMAL                    0xDC
#define HID_KEYBOARD_SC_KEYPAD_HEXADECIMAL                0xDD
#define HID_KEYBOARD_SC_LEFT_CONTROL                      0xE0
#define HID_KEYBOARD_SC_LEFT_SHIFT                        0xE1
#define HID_KEYBOARD_SC_LEFT_ALT                          0xE2
#define HID_KEYBOARD_SC_LEFT_GUI                          0xE3
#define HID_KEYBOARD_SC_RIGHT_CONTROL                     0xE4
#define HID_KEYBOARD_SC_RIGHT_SHIFT                       0xE5
#define HID_KEYBOARD_SC_RIGHT_ALT                         0xE6
#define HID_KEYBOARD_SC_RIGHT_GUI                         0xE7

extern USBD_Class_cb_TypeDef  USBD_DEV_cb;

#endif  // __USB_DEVICE_H_
