cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

include(pico_extras_import_optional.cmake)

project(keyboard C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_executable(keyboard
    main.c
    usb_descriptors.c
)
target_include_directories(keyboard PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

# pull in common dependencies
target_link_libraries(keyboard 
    pico_stdlib
    tinyusb_board # Required for any usb usage
    tinyusb_device # When pi pico is a device
)

# enable usb output
pico_enable_stdio_usb(keyboard 0)
pico_enable_stdio_uart(keyboard 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(keyboard)    


add_executable(matrix
    matrix.c
)

target_link_libraries(matrix pico_stdlib)

# enable uart output
pico_enable_stdio_usb(matrix 1)
pico_enable_stdio_uart(matrix 0)

pico_add_extra_outputs(matrix)


