# HID (Human Interface Devices)

## Report Template

Bits | Offset | Value
-|-|-
0x8 | 0x0 | bitfield for [L CTRL, L Shift, L Alt, L Gui, R Ctrl, R Shift, R Alt, R Gui] 
0x5 | 0x8 | bitfield for LED output [Kana, Compose, ScrollLock, CapsLock, NumLock]
0x3 | 0xc | padding for byte alignment
0x30 | 0x10 | Array of six keycode (8 bits) for down key

## Consumer Control

This a a report type that may contain the signals in the following section. This report type could be usefull to remove the media control from the keyboard report. 

```
// Power Control
HID_USAGE_CONSUMER_POWER                             = 0x0030,
HID_USAGE_CONSUMER_RESET                             = 0x0031,
HID_USAGE_CONSUMER_SLEEP                             = 0x0032,

// Screen Brightness
HID_USAGE_CONSUMER_BRIGHTNESS_INCREMENT              = 0x006F,
HID_USAGE_CONSUMER_BRIGHTNESS_DECREMENT              = 0x0070,

// These HID usages operate only on mobile systems (battery powered) and
// require Windows 8 (build 8302 or greater).
HID_USAGE_CONSUMER_WIRELESS_RADIO_CONTROLS           = 0x000C,
HID_USAGE_CONSUMER_WIRELESS_RADIO_BUTTONS            = 0x00C6,
HID_USAGE_CONSUMER_WIRELESS_RADIO_LED                = 0x00C7,
HID_USAGE_CONSUMER_WIRELESS_RADIO_SLIDER_SWITCH      = 0x00C8,

// Media Control
HID_USAGE_CONSUMER_PLAY_PAUSE                        = 0x00CD,
HID_USAGE_CONSUMER_SCAN_NEXT                         = 0x00B5,
HID_USAGE_CONSUMER_SCAN_PREVIOUS                     = 0x00B6,
HID_USAGE_CONSUMER_STOP                              = 0x00B7,
HID_USAGE_CONSUMER_VOLUME                            = 0x00E0,
HID_USAGE_CONSUMER_MUTE                              = 0x00E2,
HID_USAGE_CONSUMER_BASS                              = 0x00E3,
HID_USAGE_CONSUMER_TREBLE                            = 0x00E4,
HID_USAGE_CONSUMER_BASS_BOOST                        = 0x00E5,
HID_USAGE_CONSUMER_VOLUME_INCREMENT                  = 0x00E9,
HID_USAGE_CONSUMER_VOLUME_DECREMENT                  = 0x00EA,
HID_USAGE_CONSUMER_BASS_INCREMENT                    = 0x0152,
HID_USAGE_CONSUMER_BASS_DECREMENT                    = 0x0153,
HID_USAGE_CONSUMER_TREBLE_INCREMENT                  = 0x0154,
HID_USAGE_CONSUMER_TREBLE_DECREMENT                  = 0x0155,

// Application Launcher
HID_USAGE_CONSUMER_AL_CONSUMER_CONTROL_CONFIGURATION = 0x0183,
HID_USAGE_CONSUMER_AL_EMAIL_READER                   = 0x018A,
HID_USAGE_CONSUMER_AL_CALCULATOR                     = 0x0192,
HID_USAGE_CONSUMER_AL_LOCAL_BROWSER                  = 0x0194,

// Browser/Explorer Specific
HID_USAGE_CONSUMER_AC_SEARCH                         = 0x0221,
HID_USAGE_CONSUMER_AC_HOME                           = 0x0223,
HID_USAGE_CONSUMER_AC_BACK                           = 0x0224,
HID_USAGE_CONSUMER_AC_FORWARD                        = 0x0225,
HID_USAGE_CONSUMER_AC_STOP                           = 0x0226,
HID_USAGE_CONSUMER_AC_REFRESH                        = 0x0227,
HID_USAGE_CONSUMER_AC_BOOKMARKS                      = 0x022A,

// Mouse Horizontal scroll
HID_USAGE_CONSUMER_AC_PAN                            = 0x0238,
```

# Custom Report Template

For all key rollover [0x04, 0xe7], but [0xa5, 0xdf] are reserved. Therefor, `(0xe8 - 0x04) - (0xdf - 0xa5) = 169` actual bits are required for all the keys on any keyboard. With byte alignment, that adds up to 176 bits (22 bytes). Then let's say we add the 5 bits for the ligths. 1 byte with alignment. 

Total size of the report is 27 bytes (216 bits)

## Problem 1

The default report format must be use for bios access, since dynamic format may not be supported. There has to be a way of detecting an error in format and falling back to the default.

## Solution ish

For the moment being a keyboard with 6 key ghosting is going to be good enough. Once everything else is done. I will come back to this issue


# Build & Run

# Building

Here `keyboard` is the target which is defined in CMakeLists.txt

```bash
export PICO_SDK_PATH=../../pico-sdk
mkdir build
cd build
cmake .
make keyboard
```

# Running

Copy the `.uf2` file into the pico pi's storage

```bash
cp keyboard.uf2 /run/media/simonlaureti/RPI-RP2
```