#pragma once
#include "FreeRTOS.h"
#include <stdint.h>
#include <cstddef>

void* operator new(size_t size){
    return pvPortMalloc(size);
}

void* operator new[](size_t size){
    return pvPortMalloc(size);
}

void operator delete(void* ptr){
    vPortFree(ptr);
}

void operator delete[](void* ptr){
    vPortFree(ptr);
}

const uint32_t TEMP_PROBE_PIN = 9;
const uint32_t HEATER_PWM_PIN = 8;