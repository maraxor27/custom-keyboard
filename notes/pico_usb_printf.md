# Build

```cmake
# enable usb output, disable uart output
pico_enable_stdio_usb(keyboard 1)
pico_enable_stdio_uart(keyboard 0)
```

# How to read this output?

```bash
sudo cat /dev/ttyACM0
```