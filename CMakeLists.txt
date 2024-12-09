cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(wifi_sta C CXX ASM)

pico_sdk_init()

add_executable(wifi_sta
        src/main.c
        )

# pull in common dependencies
target_link_libraries(wifi_sta 
                pico_stdlib
                pico_binary_info
                hardware_i2c
                hardware_uart
)

target_include_directories(wifi_sta PRIVATE
                src
                src/header
                src/ssd1306
)
            
target_sources(wifi_sta PUBLIC
        src/wifi_sta.c
        src/uart.c
        src/led.c
        src/ssd1306/i2c.c
)

# create map/bin/hex file etc.
pico_add_extra_outputs(wifi_sta)