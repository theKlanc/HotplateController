cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
# Pull in FreeRTOS
include(FreeRTOS_Kernel_import.cmake)

project(HotplateController C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_library(HotplateController INTERFACE)
target_sources(HotplateController INTERFACE
        src/main.c
        src/heater.cpp
        src/tempProbe.cpp
        src/pidController.cpp
        deps/PID/cpp/PID.cpp
        )

target_include_directories(HotplateController INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
        deps/PID/cpp
        )
target_link_libraries(HotplateController INTERFACE
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap1
        pico_adc
        pico_stdlib
        pico_multicore
        )

add_executable(hotplateController)
target_link_libraries(hotplateController HotplateController)
pico_add_extra_outputs(hotplateController)
pico_enable_stdio_usb(hotplateController 1)
