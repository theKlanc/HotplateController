#include "FreeRTOS.h"
#include "heater.hpp"
#include "task.h"
#include "pico/multicore.h"
#include <cstdio>

TaskHandle_t heater_task_handle;

void HEATER_TASK(){
    while(1){ 
        printf("HEATER %d\n", get_core_num());
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}