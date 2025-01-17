cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(nrf52dk_firmware)

target_sources(app PRIVATE src/main.c)

#custom files and folders

target_sources(app PRIVATE
    src/temp_sensor_service/ble_comm.c
)

zephyr_library_include_directories(src/temp_sensor_service)